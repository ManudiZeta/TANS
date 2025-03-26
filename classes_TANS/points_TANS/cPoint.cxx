#include "cPoint.h"

ClassImp(cPoint)

cPoint::cPoint(): TObject(),
ascissa(0.),
ordinata(0.),
quota(0.)
{
}

cPoint::cPoint (double x0, double y0, double z0): TObject (),
ascissa(x0),
ordinata(y0),
quota(z0)
{
}

cPoint::cPoint(const cPoint &source): TObject (),

ascissa(source.getX()),
ordinata(source.getY()),
quota(source.getZ())
{
    
}

void cPoint::print() const
{
    cout<<"(x = "<<ascissa<<"cm, y = "<<ordinata<<"cm, z = "<<quota<<"cm ) ";
    
}

