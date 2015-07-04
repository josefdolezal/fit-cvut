/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#include <stdio.h>

int naMinuty(int h, int m);
int kontrolaCasu(int h, int m);

int main() {
    int spoje[3][2];
    int c, d = 0, ival1, ival2, odjezd, bejk = 0, p = 10000;
    long s1[10000], s2[10000], t = 0;
    
    for (c = 0; c < 2; c++) {
        printf("Interval spoje #%d:\n", c+1);
        if (scanf("%d:%d", &spoje[c][0], &spoje[c][1]) != 2 || kontrolaCasu(spoje[c][0], spoje[c][1]) == 0 || naMinuty(spoje[c][0], spoje[c][1]) == 0) {
            printf("Nespravny vstup.\n");
            return 1;
        }
    }
    
    ival1  = naMinuty(spoje[0][0], spoje[0][1]);
    ival2  = naMinuty(spoje[1][0], spoje[1][1]);
    
    printf("Cas od odjezdu spoje #2:\n");
    if (scanf("%d:%d", &spoje[2][0], &spoje[2][1]) != 2 || kontrolaCasu(spoje[2][0], spoje[2][1]) == 0 || (naMinuty(spoje[2][0], spoje[2][1]) > ival2) || (naMinuty(spoje[2][0], spoje[2][1]) == ival2)) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    
    
    s2[0] = odjezd = ival2 - naMinuty(spoje[2][0], spoje[2][1]);

    for (c = 1; c < p; c++) {
        s1[c-1] = c * ival1;
        s2[c]   = odjezd + (c * ival2);
    }
    
    
    for (c = 0; c < p; c++) {
        for (d = 0; d < p; d++) {
            if (s2[c] == s1[d] + 1) {
                bejk = 1;
                t = s1[d];
                break;
            }
        }
        
        if (bejk == 1) break;
    }
    
    
    if(bejk == 1) {
        if (t == 0) printf("Spoj #2 bude odjizdet 1 minutu po prijezdu spoje #1 prave nyni.\n");
        else printf("Spoj #2 bude odjizdet 1 minutu po prijezdu spoje #1 za %ld:%02ld.\n", t/60, t%60);
    }
    else printf("Spoj #2 nikdy nebude odjizdet 1 minutu po prijezdu spoje #1.\n");
    
    return 0;
}

int kontrolaCasu(int h, int m) {
    if (h < 0 || m < 0 || m > 59) {
        return 0;
    }
    
    return 1;
}

int naMinuty(int h, int m){
    return 60*h + m;
}
