/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#include <stdio.h>
#include <math.h>

int main() {
    double body[4][2];
    double vAB[2], vBC[2];
    double eps = 1e-8;
    int isRectangle = 1;
    
    for (int i = 0; i<4; i++) {
        printf("Bod #%d:\n", i+1);
        
        if (scanf("%lf%lf", &body[i][0], &body[i][1]) != 2) {
            printf("Nespravny vstup.\n");
            return 1;
        }
        
        if (isRectangle == 1) {
            for (int j=0; j<i; j++) {
                if (body[j][0] == body[i][0] && body[j][1] == body[i][1]) {
                    isRectangle = 0;
                }
            }
        }
    }
    
    if (isRectangle) {
        vAB[0] = body[1][0] - body[0][0]; //x
        vAB[1] = body[1][1] - body[0][1]; //y
        
        vBC[0] = body[2][0] - body[1][0]; //x
        vBC[1] = body[2][1] - body[1][1]; //y
        
        isRectangle = 0;
        
        double t = fabs(body[2][0] - vAB[0] - body[3][0]);
        
        double a = (fabs(body[2][0] - vAB[0] - body[3][0]) <= fabs(eps*vAB[0])) ? 0 : 1;
        double b = (fabs(body[2][1] - vAB[1] - body[3][1]) <= fabs(eps*vAB[1])) ? 0 : 1;
        double c = (fabs(body[3][0] - vBC[0] - body[0][0]) <= fabs(eps*vBC[0])) ? 0 : 1;
        double d = (fabs(body[3][1] - vBC[1] - body[0][1]) <= fabs(eps*vBC[1])) ? 0 : 1;
        double e = (fabs(vAB[0]*vBC[0] + vAB[1]*vBC[1]) <= fabs(eps*vAB[1]*vBC[1])) ? 0 : 1;

        
        if(fabs(body[2][0] - vAB[0] - body[3][0]) <= eps*body[3][0] && // d-x
           fabs(body[2][1] - vAB[1] - body[3][1]) <= eps*body[3][1] && //d-y
           fabs(body[3][0] - vBC[0] - body[0][0]) <= eps*body[0][0] && //a-x
           fabs(body[3][1] - vBC[1] - body[0][1]) <= eps*body[0][1] && // a-y
           fabs(vAB[0]*vBC[0] + vAB[1]*vBC[1]) <= eps // AxB
        ) {
            isRectangle = 1;
        }
    } 
    
    printf("Body %stvori obdelnik.\n", isRectangle == 0 ? "ne" : "");
    
    return 0;
}
