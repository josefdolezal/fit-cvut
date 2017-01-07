
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#include <string>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/ssl.h>
#include <openssl/pem.h>

#define IP_ADDRESS "147.32.232.248"

#define BUFF_SIZE 1024

using namespace std;

sockaddr_in initSocket() {
    sockaddr_in serveraddr;
    
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr(IP_ADDRESS); //ip address
    serveraddr.sin_port=htons(443); // port
    
    return serveraddr;
}

int error(const string & err, int code) {
    perror(err.c_str());
    
    return code;
}

int main()
{
    char buff[BUFF_SIZE];
    
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servaddr = initSocket();
    
    if( connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0 ) return error("connect", -1);
    
    SSL_library_init();
    
    /* Vytvoreni contextu */
    SSL_CTX * ssl_ctx = SSL_CTX_new(SSLv23_client_method());
    if(!ssl_ctx) return error("SSL_CTX_new", -2);
    
    /* Zakazani deravych protokolu */
    SSL_CTX_set_options(ssl_ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1);
    
    /* Vytvoreni SSL struktury */
    SSL * ssl = SSL_new(ssl_ctx);
    if(!ssl) return error("SSL_new", -3);
    
    /* Otevreni spojeni */
    if( !SSL_set_fd(ssl,sockfd) ) return error("SSL_set_fd", -4);
    
    /* Zahajeni SSL komunikace */
    const SSL_CIPHER * sc = SSL_get_current_cipher(ssl);
    string disable_cipher = "ALL:!";
    disable_cipher += SSL_CIPHER_get_name(sc);
    
    /* Zakazani pouzite sifry */
    // cout << "Zakazuji sifru: " << disable_cipher << endl;
    SSL_set_cipher_list(ssl, disable_cipher.c_str());
    if( SSL_connect(ssl) <= 0 ) return error("SSL_connect", -5);
    
    /* Ziskani certifikatu ze serveru */
    X509 * cert = SSL_get_peer_certificate(ssl);
    if(!cert) return error("SSL_get_cert", -7);
    
    /* Zapsani certifikatu do souboru */
    FILE * fPEM = fopen("SERVER_CERT", "w");
    if( !PEM_write_X509(fPEM,cert) ) return error("PEM_write", -8);
    fclose(fPEM);
    
    string request = "GET /student/odkazy HTTP/1.1\r\nConnection: close\r\nHost: fit.cvut.cz\r\n\r\n";
    
    /* Odeslani pozadavku po SSL */
    if(SSL_write(ssl, request.c_str(), request.length() + 1) <= 0) return error("SSL_write", -6);
    
    /* Cekani na odpoved */
    int res;
    FILE * fOutput = fopen("RESPONSE", "w");
    
    while((res = SSL_read(ssl,buff,BUFF_SIZE)) > 0)
        fwrite(buff,sizeof(char), res, fOutput);
    
    fprintf(fOutput, "\n");
    fclose(fOutput);
    
    cout << "Pouzita sifra:" << endl;
    const SSL_CIPHER * sc_ = SSL_get_current_cipher(ssl);
    cout << SSL_CIPHER_get_name(sc_) << endl;
    cout << endl;
    
    cout << "Sifry dostupne na klientovi:" << endl;
    int prior = 0;
    const char * available_cipher;
    while((available_cipher = SSL_get_cipher_list(ssl, prior++)))
        cout << available_cipher << endl;
    
    /* Uvolneni prostredku */
    SSL_shutdown(ssl);
    close(sockfd);
    SSL_free(ssl);
    SSL_CTX_free(ssl_ctx);
    
    return 0;
}
