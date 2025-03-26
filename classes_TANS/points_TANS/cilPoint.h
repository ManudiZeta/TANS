#ifndef CILPOINT_H
#define CILPOINT_H
#include <Riostream.h>
#include <cmath>
#include "TObject.h"
#include "cPoint.h"

class cilPoint : public TObject
{
 
public:
    
    cilPoint(); //default constructor
    cilPoint(double R, double P, double Z); // std costructor
    cilPoint(const cilPoint& source); // copy constructor
    cilPoint(const cPoint& source); // constructor from cPoint
    
    double getR () const {return raggio;}
    double getP () const {return phi;}
    double getZ () const {return quota;}
    
    static double cPgetP (const cPoint& source);
        
    void print () const;
    
private:
    
    double raggio;
    double phi;
    double quota;
    
    ClassDef(cilPoint,1)
    
};
#endif


