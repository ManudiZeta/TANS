#ifndef MULTS_H
#define MULTS_H

#include <Riostream.h>
#include <cmath>
#include "TRandom3.h"
#include "../detectors_TANS/dLayer.h"
#include "../points_TANS/cPoint.h"

class multS
{
 
public:


    static void pRotate (double &ph, double &th, double *cd);
    

    ClassDef(multS,1)
};
#endif

