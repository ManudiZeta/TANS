#include "multS.h"
ClassImp(multS)


void multS::pRotate (double &ph, double &th, double *cd)
{
    double thp = gRandom->Gaus(0,0.001);
    double php = gRandom->Gaus(0,0.001);
    th = th + thp;
    ph = ph + php;
    
    double mr[3][3];
    mr[0][0] = -sin(ph);
    mr[1][0] = cos(ph);
    mr[2][0] = 0.;
    
    mr[0][1] = cos(ph)*cos(th);
    mr[1][1] = cos(th)*sin(ph);
    mr[2][1] = sin(th);
    
    mr[0][2] = sin(th)*cos(ph);
    mr[1][2] = sin(th)*sin(ph);
    mr[2][2] = cos(th);
    
    double cdp[3];
    cdp[0] = sin(thp)*cos(php);
    cdp[1] = sin(thp)*sin(php);
    cdp[2] = cos(thp);
    
    for (int i=0; i<3; i++)
    {
        cd[i]=0.;
        for(int j=0; j<3;j++)
        {
            cd[i] = cd[i] + mr[i][j]*cdp[j];
        }
    }
    
}

