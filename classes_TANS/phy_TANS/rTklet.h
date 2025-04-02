#ifndef RTKLET_H
#define RTKLET_H

#include <Riostream.h>
#include <cmath>
#include <vector>
#include <numeric>
#include "TObject.h"
#include "../points_TANS/cilPoint.h"

using namespace std;



class rTklet : public TObject
{
 
public:
    
    static double tkGen (const cilPoint &p_2, const cilPoint &p_3);
    static void phiCoupler (const vector<cilPoint> &vec_2, const vector<cilPoint> &vec_3, vector<double> &z_rec_vec);

    static double mean_vec(const vector<double> &z_rec_vec);
    static double sdev_vec(const vector<double> &z_rec_vec, const double mean);
    
    static double ZREC (const vector<double> &z_rec_vec, const double &window);
    
    ClassDef(rTklet,1)
};
#endif


