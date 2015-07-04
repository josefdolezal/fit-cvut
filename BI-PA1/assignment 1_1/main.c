/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int jeNaStene(int bod[3], int hrana);
int minimum(int seznam[], int pocet, int chciIndex);
double minimumd(double seznam[], int pocet, int chciIndex);

int main() {
    int body[2][3], hrana, protejsi = 0, potrubi = 0, i;
    double hadice = 0;
    
    printf("Zadejte rozmer mistnosti:\n");
    if (scanf("%d", &hrana) != 1 || hrana < 0) {
        printf("Nespravny vstup.\n");
        return 0;
    }
    
    for (i = 0; i<2; i++) {
        printf("Bod #%d:\n", i+1); /* OK pokud se provede konverze a bod je na stene */
        if(scanf("%d%d%d", &body[i][0], &body[i][1], &body[i][2]) != 3 || jeNaStene(body[i], hrana) == 0) {
            printf("Nespravny vstup.\n");
            return 0;
        }
    }
    
    for (i = 0; i<3; i++) { /* pokud je jedna souradnice bodu 0 a odpovidajici souradnice druheho bodu max-20 a naopak, pak jsou body proti sobe */
        if((body[0][i] == 0 && body[1][i] == hrana) ||
           (body[0][i] == hrana && body[1][i] == 0)
           ) {
            protejsi = 1;
            break;
        }
    }
    
    
    int stn = 0;
    
    if(protejsi) { /* protejsi strany */
        /* vyber varianty */
        for(i = 0; i<3; i++) { if(body[0][i] == hrana || body[0][i] == 0) { stn = i; break; } }
        
        int delky[3][2][4] = {
            {   /* stena x */
                {   /* rovnobezne */
                    hrana - body[0][1] + hrana + hrana - body[1][1], /* nahoru */
                    hrana - body[0][2] + hrana + hrana - body[1][2], /* doleva */
                    body[0][1] + hrana + body[1][1], /* dolu */
                    body[0][2] + hrana + body[1][2] /* doprava */
                },
                {   /* porovnani */
                    abs(body[0][2] - body[1][2]), abs(body[0][1] - body[1][1]), abs(body[0][2]-body[1][2]), abs(body[0][1]-body[1][1])
                }
            },
            {   /* stena y (spodni/horni) */
                {
                    hrana - body[0][0] + hrana + hrana - body[1][0], /* doprava */
                    hrana - body[0][2] + hrana + hrana - body[1][2], /* od sebe */
                    body[0][2] + hrana + body[1][2], /* k sobe */
                    body[0][0] + hrana + body[1][0] /* doleva */
                },
                {
                    abs(body[0][2] - body[1][2]), abs(body[0][0] - body[1][0]), abs(body[0][0] - body[1][0]), abs(body[0][2] - body[1][2])
                }
            },
            {   /* stena z */
                {   /* delky rovnobezne */
                    hrana - body[0][1] + hrana + hrana - body[1][1], /* nahoru */
                    hrana - body[0][0] + hrana + hrana - body[1][0], /* doprava */
                    body[0][1] + hrana + body[1][1], /* dolu */
                    body[0][0] + hrana + body[1][0] /* doleva */
                },
                {   /* porovnani na stene */
                    abs(body[0][0] - body[1][0]), abs(body[0][1] - body[1][1]), abs(body[0][0]-body[1][0]), abs(body[0][1]-body[1][1])
                }
            }
        };
        
        /* vypocet delky (obvody) */
        int c[] = { delky[stn][0][0] + delky[stn][1][0], delky[stn][0][1] + delky[stn][1][1], delky[stn][0][2] + delky[stn][1][2], delky[stn][0][3] + delky[stn][1][3] };
        
        double t[] = { /* prepony */
            sqrt(pow(delky[stn][0][0], 2.0) + pow(delky[stn][1][0], 2.0)),
            sqrt(pow(delky[stn][0][1], 2.0) + pow(delky[stn][1][1], 2.0)),
            sqrt(pow(delky[stn][0][2], 2.0) + pow(delky[stn][1][2], 2.0)),
            sqrt(pow(delky[stn][0][3], 2.0) + pow(delky[stn][1][3], 2.0)),
        };
        
        potrubi = minimum(c, 4, 0); /* minimalni obvod */
        hadice  = minimumd(t, 4, 0); /* minimalni prepona */
        
    } else { /* vedlejsi strany */
        if (body[0][0] != 0 && body[0][0] != hrana && body[1][0] != 0 && body[1][0] != hrana)
            hadice = sqrt((body[1][0] - body[0][0]) * (body[1][0] - body[0][0]) + (abs(body[1][1] - body[0][1]) + abs(body[1][2] - body[0][2])) * (abs(body[1][1] - body[0][1]) + abs(body[1][2] - body[0][2])));
        
        else if (body[1][1] != 0 && body[1][1] != hrana && body[0][1] != 0 && body[0][1] != hrana)
            hadice = sqrt((body[1][1] - body[0][1]) * (body[1][1] - body[0][1]) + (abs(body[1][0] - body[0][0]) + abs(body[1][2] - body[0][2])) * (abs(body[1][0] - body[0][0]) + abs(body[1][2] - body[0][2])));
        
        else if (body[1][2] != 0 && body[1][2] != hrana && body[0][2] != 0 && body[0][2] != hrana)
            hadice = sqrt((body[1][2] - body[0][2]) * (body[1][2] - body[0][2]) + (abs(body[1][0] - body[0][0]) + abs(body[1][1] - body[0][1])) * (abs(body[1][0] - body[0][0]) + abs(body[1][1] - body[0][1])));
        
        potrubi = abs(body[0][0] - body[1][0]) + abs(body[0][1] - body[1][1]) + abs(body[0][2] - body[1][2]);
        
    }
    
    printf("Delka potrubi: %d\nDelka hadice: %lf\n", potrubi, hadice);
    
    
    return 0;
}

/* jedna souradnice je 0 nebo max a ostatni jsou z intervalu <20, max-20> */
int jeNaStene(int bod[3], int hrana) {
    if (((bod[0] == 0 || bod[0] == hrana) && bod[1] >= 20 && bod[1] <= hrana-20 && bod[2] >= 20 && bod[2] <= hrana-20) ||
        ((bod[1] == 0 || bod[1] == hrana) && bod[0] >= 20 && bod[0] <= hrana-20 && bod[2] >= 20 && bod[2] <= hrana-20) ||
        ((bod[2] == 0 || bod[2] == hrana) && bod[1] >= 20 && bod[1] <= hrana-20 && bod[0] >= 20 && bod[0] <= hrana-20)
        ) {
        return 1;
    }
    
    return 0;
}

/* vrati minimum ze zadaneho pole */
int minimum(int seznam[], int pocet, int chciIndex) {
    int minimum = seznam[0], min_in = 0, i = 0;
    for (i = 0; i < pocet; i++) {
        if(seznam[i] < minimum) {
            minimum = seznam[i];
            min_in  = i;
        }
    }
    
    return chciIndex ? min_in : minimum;
}

double minimumd(double seznam[], int pocet, int chciIndex) {
    double minimum = seznam[0];
    int min_in = 0, i = 0;
    for (i = 0; i < pocet; i++) {
        if(seznam[i] < minimum) {
            minimum = seznam[i];
            min_in  = i;
        }
    }
    
    return chciIndex ? min_in : minimum;
}
