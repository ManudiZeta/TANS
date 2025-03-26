#include "lHit.h"

ClassImp(lHit)

lHit::lHit(): TObject(),
punto(0.,0.,0.),
strato(0.)
{
}

lHit::lHit(cPoint &p, double l): TObject (),
punto(p),
strato(l)
{
}

lHit::lHit(const lHit &source): TObject (),

punto(source.getPoint()),
strato(source.getLayer())
{
    
}

void lHit::print() const
{
    punto.cPoint::print();
    cout<<"| R = "<<strato<<endl;
    
}


