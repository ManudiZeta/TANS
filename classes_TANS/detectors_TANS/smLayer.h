#ifndef SMLAYER_H
#define SMLAYER_H

#include <Riostream.h>
#include <cmath>
#include "TRandom3.h"
#include "../points_TANS/cilPoint.h"
#include "../detectors_TANS/dLayer.h"

class smLayer
{
 
public:
    
    static cPoint smearPoint (cPoint &pt);
    static cPoint spurPoint (double layer);


    ClassDef(smLayer,1)
};
#endif


