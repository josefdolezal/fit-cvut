#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void put( char *text, unsigned char* hash, int length ) {
  int i;
  /* Vypsani vysledneho hashe */
  printf("Hash textu \"%s\" je: ", text);
  for(i = 0; i < length; i++){
    printf("%02x", hash[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]){
  int c = 0;
  char hashFunction[] = "sha256";  // zvolena hashovaci funkce ("sha1", "md5" ...)
 
  EVP_MD_CTX ctx;  // struktura kontextu
  const EVP_MD *type; // typ pouzite hashovaci funkce
  unsigned char hash[EVP_MAX_MD_SIZE]; // char pole pro hash - 64 bytu (max pro sha 512)
  int length;  // vysledna delka hashe
 
  /* Inicializace OpenSSL hash funkci */
  OpenSSL_add_all_digests();
  /* Zjisteni, jaka hashovaci funkce ma byt pouzita */
  type = EVP_get_digestbyname(hashFunction);
 
  /* Pokud predchozi prirazeni vratilo -1, tak nebyla zadana spravne hashovaci funkce */
  if(!type) {
    printf("Hash %s neexistuje.\n", hashFunction);
    exit(1);
  }

  while(1) {
    char text[15];
    sprintf(text, "%d", c++ );

    /* Provedeni hashovani */
    EVP_DigestInit(&ctx, type);  // nastaveni kontextu
    EVP_DigestUpdate(&ctx, text, strlen(text));  // zahashuje text a ulozi do kontextu
    EVP_DigestFinal(&ctx, hash, (unsigned int *) &length);  // ziskani hashe z kontextu

    if( hash[0] == 170 && hash[1] == 187 ) {
      put( text, hash, length );
      break;
    }
  }
 
  exit(0);
}
