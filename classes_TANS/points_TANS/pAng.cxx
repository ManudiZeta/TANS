#include "pAng.h"
static int inf = std::numeric_limits<int>::max();

ClassImp(pAng)

pAng::pAng(): TObject(),
phi(0),
teta(0),
eta(inf)

{
    
}

pAng::pAng(double p, double t): TObject (),
phi(p),
teta(t),
eta(TtoE(t))

{
    
}

double pAng::getT() const
{
    return teta;
}

double pAng::getP() const
{
    return phi;
}

double pAng::getE() const
{
    
    return eta;
}

double pAng::TtoE(const double t)
{
    if(t == 0)
    {
        return inf;
    }
    if (t>0 && t <= M_PI/2)
    {
        double T = tan(t/2);
        return -log(T);
    }
    
    else
    {
        double t1 = (t-M_PI);
        double T = tan(t1/2);
        return log(-T);
    }
    

}

double pAng::EtoT(const double e)
{
    
    double expo = exp(-e);
    return 2.*atan(expo);
}

void pAng::print() const
{
    cout<<"(\u03C6 = "<<phi<<", \u03B7 = "<<eta<<", \u0398 = "<<teta<<") \n";
    
}






