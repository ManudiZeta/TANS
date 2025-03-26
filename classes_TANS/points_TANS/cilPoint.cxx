#include "cilPoint.h"

ClassImp(cilPoint)

cilPoint::cilPoint(): TObject(),
raggio(0.),
phi(0.),
quota(0.)
{
}

cilPoint::cilPoint(double R, double P, double Z): TObject (),
raggio(R),
phi(P),
quota(Z)
{
}

cilPoint::cilPoint(const cilPoint &source): TObject (),

raggio(source.getR()),
phi(source.getP()),
quota(source.getZ())
{
    
}

cilPoint::cilPoint(const cPoint &source): TObject ()
{
    double x = source.cPoint::getX();
    double y = source.cPoint::getY();
    double z = source.cPoint::getZ();
    
    raggio = sqrt(x*x + y*y);
    quota = z;
    if (x==0)
    {
        if(y>0)
        {
            phi= M_PI/2.;
        }
        
        if(y<0)
        {
            phi = 1.5*M_PI;
        }
        
        else
        {
            cout<<" \u03C6 not defined. 0 will be assigned \n";
            phi = 0.;
        }
    
        
    }
    
    
    if (x > 0)
    {
        if (y >= 0) {phi = atan(y/x);}
        else {phi= atan(y/x)+ 2.*M_PI;}
    }
    
    else
    {
        phi = atan(y/x)+ M_PI;
    }
    
    
}

double cilPoint::cPgetP(const cPoint &source)
{
    double x = source.cPoint::getX();
    double y = source.cPoint::getY();
    
    if (x==0)
    {
        if(y>0)
        {
            return M_PI/2.;
        }
        
        if(y<0)
        {
            return 1.5*M_PI;
        }
        
        else
        {
            cout<<" \u03C6 not defined. 0 will be assigned \n";
            return 0.;
        }
    
        
    }
    
    
    if (x > 0)
    {
        if (y >= 0) {return atan(y/x);}
        else { return atan(y/x)+ 2.*M_PI;}
    }
    
    else
    {
        return atan(y/x)+ M_PI;
    }
    
}


void cilPoint::print() const
{
    cout<<"(R = "<<raggio<<"cm ,\u03C6 = "<<phi<<"rad, Z = "<<quota<<"cm) ";
    
}


