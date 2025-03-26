#ifndef SCONJ_H
#define SCONJ_H

#include <Riostream.h>
#include <cmath>
#include "TRandom3.h"
#include "../points_TANS/cPoint.h"

class sConj
{
 
public:

    static void endSim(const int MS , const int n_eve, const int parts, const int *check);
    static void endEv(const int k , const int entries, const cPoint &ver, const int mul);
    ClassDef(sConj,1)
};
#endif

