#include "smLayer.h"
ClassImp(smLayer)


cPoint smLayer::smearPoint(cPoint &pt)
{
    double x = pt.getX();
    double y = pt.getY();
    double z = pt.getZ();
    double Phi = cilPoint::cPgetP(pt);
    
    double R = sqrt(x*x + y*y);
    double dPhi = gRandom->Gaus(0,0.003);
    
    double x_s = R*cos(Phi + dPhi);
    double y_s = R*sin(Phi + dPhi);
    double z_s = z+gRandom->Gaus(0,0.0120);
    cPoint pt_s(x_s,y_s,z_s);
    
    return pt_s;
    
}

cPoint smLayer::spurPoint (double layer)
{
    
    double segno_x = gRandom->Rndm();
    double segno_y = gRandom->Rndm();
    double segno_z = gRandom->Rndm();
    
    double x,y,z;
    if (segno_x <0.5)
    {
        x = (gRandom->Rndm())*layer;
    }
    else
    {
        x = -(gRandom->Rndm())*layer;
    }
    
    if (segno_y <0.5)
    {
        y = sqrt(layer*layer - x*x);
    }
    else
    {
        y = -sqrt(layer*layer - x*x);
    }
    
    
    if (segno_y <0.5)
    {
        y = sqrt(layer*layer - x*x);
    }
    else
    {
        y = -sqrt(layer*layer - x*x);
    }
    
    if (segno_z <0.5)
    {
        z = (gRandom->Rndm())*13.5;
    }
    else
    {
        z = (gRandom->Rndm())*13.5;
    }
   
    cPoint spur (x,y,z);
    return spur;


    
}


