#include "pKinematic.h"
ClassImp(pKinematic)

cPoint pKinematic::kinPoint(const cPoint &point, const double *ang, const dLayer &nLayer)
{
    double c1 = ang[0];
    double c2 = ang[1];
    double c3 = ang[2];
    
    
    double t = tCross(point, ang, nLayer);
    double x = point.getX() + c1*t;
    double y = point.getY() + c2*t;
    double z = point.getZ() + c3*t;
    cPoint p (x,y,z);
    return p;
}

double pKinematic::tCross(const cPoint &point, const double *ang, const dLayer &nLayer)

{
    double c1 = ang[0];
    double c2 = ang[1];
    double c3 = ang[2];
    
    double R = nLayer.getR();
    
    double x0 = point.getX();
    double y0 = point.getY();
    double z0 = point.getZ();
    
    
    double delta= (x0*c1 + y0*c2)*(x0*c1 + y0*c2) - (c1*c1 + c2*c2)*(x0*x0 + y0*y0 - R*R);
    
    if (delta<= 0)
    {
        cout<<"DELTA NOT POSITIVE \n";
        
    }
    
    double sqrt_delta=sqrt(delta);
    
    double numP= -(x0*c1 + y0*c2) + sqrt_delta;
    double numM= -(x0*c1 + y0*c2) - sqrt_delta;
    double num;
    
    if(numP<0)
    {
        num=numM;
        
    }
    
    else
    {
        num=numP;
    }
    
    double den = c1*c1 + c2*c2;
    return num/den;
    
}


bool pKinematic::rCheck(const cPoint &point, const dLayer &nLayer)
{
    
    double x = point.getX();
    double y = point.getY();
    double R = sqrt (x*x + y*y);
    
    double radius=nLayer.getR();
    double width=nLayer.getW();
    double dR = R*0.05;
    
    if ((radius - width-dR) < R && R < (radius + width+dR))
    {
        return 1;
    }
    
    else
    {
        return 0;
    }
}


bool pKinematic::lCheck (const cPoint &point, const dLayer &nLayer)
{
    double z = point.getZ();
    double length = nLayer.getL();
    
    if ((-length/2.) < z && z < (length/2.))
    {
        //cout<<" Length check passed \n";
        return 1;

    }
    
    else
    {
        //cout<<"Length check NOT passed \n";
        return 0;
        
    }
    
}

bool pKinematic::allCheck (const cPoint &point, const dLayer &nLayer)
{
    bool checkR_l = rCheck(point,nLayer);
    bool checkL_l = lCheck(point,nLayer);
    
    if (checkR_l == 0 )
    {
        //cout<<"R ERROR: NO hit \n";
        return 0;
    }
    //vediamo se la j-esima particella è dentro alla lunghezza del rivelatore 1  ()
    
    if (checkL_l == 0 )
    {
        
       // cout<<"Over Length "<<d+1<<": NO hit \n";
        return 0;
    }
    
    else
    {
        return 1;
    }
}



double pKinematic::c_1(const double teta, const double phi)
{
    return sin(teta)*cos(phi);
}

double pKinematic::c_2(const double teta, const double phi)
{
    return sin(teta)*sin(phi);
}

double pKinematic::c_3(const double teta)
{
    return cos(teta);
}
