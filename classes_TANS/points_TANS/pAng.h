#ifndef PANG_H
#define PANG_H
#include <Riostream.h>
#include <cmath>
#include "TRandom3.h"
#include "TObject.h"


class pAng : public TObject
{
 
public:
    pAng(); //default constructor
    pAng(double p, double t); // std costructor
    
    double getT () const;
    double getP () const;
    double getE () const;
    
   static double TtoE (const double t);
   static double EtoT (const double e);
    
    void print () const;
    
private:
    

    double phi;
    double teta;
    double eta;
    
    ClassDef(pAng,1)
    
};
#endif


