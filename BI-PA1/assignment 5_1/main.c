/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#include <stdio.h>
#include <stdlib.h>
#define A_SIZE 20

/* VSTUPY
    id
    cas
    prichod(1)/odchod(0)
*/

/* SMENY
    id
    smena
*/


typedef int Pole[3];

int seradVstupy(const void *a, const void *b);
int seradSmeny(const void *a, const void *b);

int main(int argc, const char * argv[]) {
    /* int vstupy[1000][3]; */
    /* int smeny[1000][2]; */
    Pole *smeny = NULL, *vstupy = NULL;

    vstupy = (Pole *)malloc(A_SIZE * sizeof(Pole));
    smeny  = (Pole *)malloc(A_SIZE * sizeof(Pole));
    
    char prichod = '#';
    int h = 0, m = 0, s = 0, id = 0, pocet = 0, turniket = 0;
    
    
    printf("Zaznamy o dochazce:\n");
    
    while (scanf(" %c", &prichod) == 1) {
        
        if (prichod == '#') { turniket = 0; continue; }
        
        if ((prichod == '-' || prichod == '+') && scanf("%2d:%2d:%2d %d", &h, &m, &s, &id) == 4) {
            
            if((prichod != '+' && prichod != '-') || h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59 || id < 1 || id > 100000) {
                free(smeny);
                free(vstupy);
                printf("Nespravny vstup.\n");
                return 1;
            } else {
                
                if (pocet > 0 && pocet % A_SIZE == 0 && (vstupy = (Pole *) realloc(vstupy, (pocet/A_SIZE + 1) * A_SIZE * sizeof(Pole))) == NULL) { free(smeny); free(vstupy); return 1; }
                
                vstupy[pocet][0] = id;
                vstupy[pocet][1] = h*3600 + m*60 + s;
                vstupy[pocet][2] = prichod == '+' ? 1 : 0;
                
                if (turniket == 1 && pocet > 0 && vstupy[pocet][1] == vstupy[pocet-1][1]) {
                    free(smeny);
                    free(vstupy);
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                
                pocet++;
            }
            
            turniket = 1;
            
        } else {
            free(smeny);
            free(vstupy);
            printf("Nespravny vstup.\n");
            return 1;
        }
    }
    
    if(pocet%2 != 0 || pocet < 2) {
        free(smeny);
        free(vstupy);
        printf("Nespravny vstup.\n");
        return 1;
    }
    
    qsort(vstupy, pocet, sizeof(Pole), seradVstupy);
    
    /* kontrola vstupu */
    for (h = 0; h < pocet; h++) {
        if((h%2 != 0 || vstupy[h][2] != 1) && (h%2 != 1 || vstupy[h][2] != 0 || (h > 0 && (vstupy[h][1] == vstupy[h-1][1])))) {
            free(smeny);
            free(vstupy);
            printf("Nespravny vstup.\n");
            return 1;
        }
    }
    
    m = 0; /* pocet zamestnancu */
    s = 0; /* posledni id */
    
    for (h = 0; h < pocet; h++) {
        if(vstupy[h][0] == s) {
            smeny[m-1][1] += (vstupy[h][2] == 0 ? 1 : -1) * vstupy[h][1];
        }
        else {
            if (m > 0 && m % A_SIZE == 0 && (smeny = (Pole *) realloc(smeny, (m/A_SIZE + 1) * A_SIZE * sizeof(Pole))) == NULL) { free(smeny); free(vstupy); return 1; }
            
            s = smeny[m][0] = vstupy[h][0];
            smeny[m][1] = -vstupy[h][1];
            m++;
        }
        
    }
    
    qsort(smeny, m, sizeof(Pole), seradSmeny);
    printf("Nejdelsi pracovni doba: %d:%02d:%02d\n", smeny[0][1]/3600, (smeny[0][1]%3600)/60, (smeny[0][1]%3600)%60);
    printf("%s dne: ", ((m > 1 && smeny[0][1] == smeny[1][1]) ? "Pracovnici" : "Pracovnik"));
    
    for (s = 0; s < m; s++) {
        if (s == 0)
            printf("%d", smeny[s][0]);
        else if(s > 0 && (smeny[s][1] == smeny[s-1][1]))
            printf(", %d", smeny[s][0]);
        else
            break;
    }
    
    printf("\n");
    
    free(smeny);
    free(vstupy);
    
    return 0;
}

int seradVstupy(const void *a, const void *b) {
    const int *aR = (const int *)a;
    const int *bR = (const int *)b;
    
    if (aR[0] == bR[0]) return aR[1] - bR[1];
    
    return aR[0] - bR[0];
}

int seradSmeny(const void *a, const void *b) {
    const int *aR = (const int *)a;
    const int *bR = (const int *)b;
    
    if (aR[1] == bR[1]) return aR[0] - bR[0];
    
    return bR[1] - aR[1];
}
