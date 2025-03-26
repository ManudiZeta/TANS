#ifndef LHIT_H
#define LHIT_H
#include <Riostream.h>
#include <cmath>
#include "../points_TANS/cPoint.h"
#include "../detectors_TANS/dLayer.h"
#include "TObject.h"


class lHit : public TObject
{
 
public:
    
    lHit(); //default constructor
    lHit(cPoint &p, double l); // std costructor
    lHit(const lHit& source); // copy constructor
    
    cPoint getPoint () const {return punto;}
    double getLayer () const {return strato;}
    
        
    void print () const;
    
private:
    
    cPoint punto;
    double strato;
    
    
    ClassDef(lHit,1)
    
};
#endif


