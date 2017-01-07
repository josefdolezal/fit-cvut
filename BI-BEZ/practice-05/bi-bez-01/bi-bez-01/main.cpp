#include <stdlib.h>
#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>

#define BUFFER_SIZE 512

char *fileName(char *name, char *end, char *out) {
  memset(out, 0, sizeof(*out));
  strcat(out, name);
  strcat(out, end);

  return out;
}

int main(int argc, char *argv[]) {
  unsigned char ot[1024];
  unsigned char st[1024];
  char soubor[30] = "Mad_scientist";
  char tmpSoubor[60] = "";
  unsigned defSize = 20;

  // klic
  unsigned char key[EVP_MAX_KEY_LENGTH] = "fdsfsdf324324fdf";
  // vektor
  unsigned char iv[EVP_MAX_IV_LENGTH] = "xcvvb";

  OpenSSL_add_all_ciphers();

  int DelkaST = 0;
  int DelkaOT = 0;

  // kontext
  EVP_CIPHER_CTX ctx;

  FILE *souborIN = fopen(fileName(soubor, (char *)".bmp", tmpSoubor), "r");

  if (!souborIN) {
    char err[80] = "Error when attempting to read file ";
    perror(strcat(err, fileName(soubor, (char *)".bmp./n", tmpSoubor)));
    return 1;
  }

  unsigned char *hlava =
      (unsigned char *)malloc(sizeof(unsigned char) * defSize);

  unsigned long count = 0;

  fread(hlava, sizeof(unsigned char), count = 14, souborIN);
  unsigned long zac = *(unsigned long *)(hlava + 10);

  if (zac > defSize)
    hlava = (unsigned char *)realloc(hlava, sizeof(unsigned char) * zac);

  fread(hlava + count, sizeof(unsigned char), zac - count, souborIN);
  count = zac;

  // * SIFROVANI
  // * ==========================
  EVP_EncryptInit(&ctx, EVP_des_cbc(), key, iv);

  unsigned char *buff =
      (unsigned char *)malloc(sizeof(unsigned char) * BUFFER_SIZE);
  unsigned long st_read_count = 0, st_count = 0, ot_read_count = 0,
                ot_count = 0;
  int vysledek;

  FILE *souborOut = fopen(fileName(soubor, (char *)"_cbc.bmp", tmpSoubor), "w");
  fwrite(hlava, sizeof(unsigned char), zac, souborOut);
  fseek(souborIN, zac, SEEK_SET);

  while ((vysledek =
              (int)fread(buff, sizeof(unsigned char), BUFFER_SIZE, souborIN)))
  {
    ot_read_count += vysledek;

    EVP_EncryptUpdate(&ctx, st, &DelkaST, buff, vysledek);
    st_count += DelkaST;
    fwrite(st, sizeof(unsigned char), DelkaST, souborOut);
  }

  EVP_EncryptFinal(&ctx, st, &DelkaST);
  st_count += DelkaST;

  fwrite(st, sizeof(unsigned char), DelkaST, souborOut);
  fclose(souborOut);
  fclose(souborIN);

  // * DESIFROVANI
  // * ==========================
  EVP_DecryptInit(&ctx, EVP_des_cbc(), key, iv);

  souborIN = fopen(fileName(soubor, (char *)"_cbc.bmp", tmpSoubor), "r");
  souborOut =
      fopen(fileName(soubor, (char *)"_DES_MODE_dec.bmp", tmpSoubor), "w");

  fseek(souborIN, zac, SEEK_SET); // posunu
  fwrite(hlava, sizeof(unsigned char), count, souborOut);

  while ((vysledek =
              (int)fread(buff, sizeof(unsigned char), BUFFER_SIZE, souborIN)))
  {
    st_read_count += vysledek;

    EVP_DecryptUpdate(&ctx, ot, &DelkaOT, buff, vysledek);
    ot_count += DelkaOT;
    fwrite(ot, sizeof(unsigned char), DelkaOT, souborOut);
  }

  EVP_DecryptFinal(&ctx, ot, &DelkaOT);
  ot_count += DelkaOT;
  fwrite(ot, sizeof(unsigned char), DelkaOT, souborOut);

  fclose(souborOut);
  fclose(souborIN);
  free(hlava);
  free(buff);

  return 0;
}
