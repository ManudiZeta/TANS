#ifndef DLAYER_H
#define DLAYER_H
#include "TGeoManager.h"
#include <vector>
#include <Riostream.h>
#include "TObject.h"


class dLayer : public TObject
{
 
public:
    dLayer(); //default constructor
    dLayer(double r, double l, double w); // std costructor
    dLayer(const dLayer& source); // copy constructor
    
    double getR () const;
    double getL () const;
    double getW () const;
    
    static TGeoVolume* chamberMaker();
    static vector<dLayer> layerMaker();
    
    void print() const;
    
private:
    
    double raggio;
    double lunghezza;
    double spessore;
    
    ClassDef(dLayer,1)
    
};
#endif


