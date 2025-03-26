#ifndef CPOINT_H
#define CPOINT_H
#include <Riostream.h>
#include <cmath>
#include "TObject.h"


class cPoint : public TObject
{
 
public:
    
    cPoint(); //default constructor
    cPoint(double x0, double y0, double z0); // std costructor
    cPoint(const cPoint& source); // copy constructor
    
    double getX () const {return ascissa;}
    double getY () const {return ordinata;}
    double getZ () const {return quota;}
        
    void print () const;
    
private:
    
    double ascissa;
    double ordinata;
    double quota;
    
    ClassDef(cPoint,1)
    
};
#endif

