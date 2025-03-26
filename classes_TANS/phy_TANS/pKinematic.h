#ifndef PKINEMATIC_H
#define PKINEMATIC_H

#include <Riostream.h>
#include <cmath>
#include "../detectors_TANS/dLayer.h"
#include "../points_TANS/cPoint.h"

class pKinematic
{
 
public:

    static cPoint kinPoint (const cPoint &point, const double *ang, const dLayer &nLayer);
    static double tCross (const cPoint &point, const double *ang, const dLayer &nLayer);
    static bool rCheck(const cPoint &point, const dLayer &nLayer);
    static bool lCheck(const cPoint &point, const dLayer &nLayer);
    static bool allCheck (const cPoint &point, const dLayer &nLayer);
    
    
    
    static double c_1 (const double teta, const double phi);
    static double c_2 (const double teta, const double phi);
    static double c_3 (const double teta);

    ClassDef(pKinematic,1)
};
#endif
