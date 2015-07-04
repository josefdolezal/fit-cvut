/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#include <stdio.h>
#include <stdlib.h>

int serad(const void * a, const void * b);
int *odstranDuplicity(int *p, int delka, int *size);


int main(int argc, const char * argv[]) {
    int vstupy[1000], predchozi[] = {0, 0, 0}, pocetNosniku = 0, konverze = 1, pocetTrojuhelniku = 0, i = 0, j = 0, k = 0;
    int *nosniky = NULL;
    
    printf("Delky nosniku:\n");
    
    while ((konverze = scanf("%d", &vstupy[pocetNosniku])) == 1 && pocetNosniku < 1000) {
        if (vstupy[pocetNosniku] <= 0) {
            printf("Nespravny vstup.\n");
            return 1;
        }
        pocetNosniku++;
    }
    
    if (konverze == 0 || pocetNosniku == 1000 || pocetNosniku < 3) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    
    qsort(vstupy, pocetNosniku, sizeof(int), serad);
    nosniky = odstranDuplicity(vstupy, pocetNosniku, &pocetNosniku);
    
    for (i = 0; i < pocetNosniku -2; i++) {
        j = i + 1;
        if (i > 0 && nosniky[i] == nosniky[i-1]) { /*printf("preskakuji (i - %d): %d %d %d\n", i, nosniky[i], nosniky[j], nosniky[k]);*/ continue;}
        
        for (j = 1+i; j < pocetNosniku-1; j++) {
            k = j + 1;
            if (j > 1+i && nosniky[j] == nosniky[j-1]) { /*printf("preskakuji (j - %d): %d %d %d\n", j, nosniky[i], nosniky[j], nosniky[k]);*/ continue;}
            
            for (k = 1+j; k < pocetNosniku; k++) {
                if (k > (1 + j) && nosniky[k] == nosniky[k-1]) { /*printf("preskakuji (k - %d, j - %d): %d %d %d\n", k, j, nosniky[i], nosniky[j], nosniky[k]);*/ continue;}
    
                if ((predchozi[0] != nosniky[i] || predchozi[1] != nosniky[j] || predchozi[2] != nosniky[k]) && (nosniky[i] + nosniky[j] > nosniky[k])) {
                    predchozi[0] = nosniky[i]; predchozi[1] = nosniky[j]; predchozi[2] = nosniky[k];
                    
                    /*printf("%d %d %d\n", predchozi[0], predchozi[1], predchozi[2]);*/
                    
                    pocetTrojuhelniku++;
                }
                
                
                if (nosniky[i] + nosniky[j] <= nosniky[k]) break;
            }
        }
    }
    
    
    printf("Trojuhelniku: %d\n", pocetTrojuhelniku);
    
    free(nosniky);
    return 0;
}

int *odstranDuplicity(int p[], int delka, int *size) {
    int pocet = 1, i, celkem = 1;
    int *n = NULL;
    
    if((n = (int *) malloc(delka * sizeof(int))) == NULL) return NULL;
    
    n[0] = p[0];
    
    for (i = 1; i < delka; i++) {
        if (p[i] != p[i-1]) pocet = 0;
        
        pocet++;
        
        if(pocet < 4) n[celkem++] = p[i];
    }
    
    *size = celkem;
    
    return n;
}

int serad (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}
