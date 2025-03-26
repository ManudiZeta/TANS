#include "dLayer.h"

ClassImp(dLayer)
double r_m[3] ={3.,4.,7.};
double r_M[3] = {3.008, 4.002, 7.002};
double lung_D[3]={100.,27.,27.};

dLayer::dLayer(): TObject(),

raggio(0.),
lunghezza(0.),
spessore(0.)

{

}

dLayer::dLayer(double r, double l, double w): TObject (),

raggio(r),
lunghezza(l),
spessore(w)

{
    
}

dLayer::dLayer(const dLayer &source): TObject (),

raggio(source.getR()),
lunghezza(source.getL()),
spessore(source.getW())

{
    
}

double dLayer::getR() const
{
    return raggio;
}

double dLayer::getL() const
{
    return lunghezza;
}

double dLayer::getW() const
{
    return spessore;
}

TGeoVolume* dLayer::chamberMaker()
{
    TGeoManager *geom = new TGeoManager("simple1", "Simple geometry");
    
    // definisco i materiali
    TGeoMaterial *matVacuum = new TGeoMaterial("Vacuum", 0, 0, 0); //creo il materiale del vuoto
    
    TGeoMaterial *matBe = new TGeoMaterial("Be", 9.01, 4, 1.85); // creo il materiale berillio con numero di massa= 9.01, numero atomico = 4 e densità = 1.85 g/cm^3
    
    TGeoMaterial *matSi = new TGeoMaterial("Si", 28, 14, 2.32); // creo il materiale silicio con numero di massa= 28, numero atomico = 14 e densità = 2.32 g/cm^3
    
    //definisco i mezzi fatti dei suddetti materiali
    
    TGeoMedium *Vacuum = new TGeoMedium("Vacuum", 1, matVacuum); //creo il mezzo del vuoto (usando il materiale del vuoto)
    TGeoMedium *Be = new TGeoMedium("Be", 1, matBe); //creo il mezzo Berillio (usando il materiale Berilio)
    TGeoMedium *Si = new TGeoMedium("Root Material", 1, matSi); //creo il mezzo Silicio (usando il materiale Silicio)
    
    
    // definisco la scatola in cui infilerò il mio hardware
    
    TGeoVolume *chamber = geom->MakeBox("Chamber",Vacuum, 50.,50.,50.);
    gGeoManager->SetTopVolume(chamber);
    
    //definisco il mio hardware
    
    TGeoVolume *l_Be = geom->MakeTube("l_Be", Be, r_m[0], r_M[0], lung_D[0]/2.);
    TGeoVolume *l_1 = geom->MakeTube("l_1", Si, r_m[1], r_M[1], lung_D[1]/2.);
    TGeoVolume *l_2 = geom->MakeTube("l_2", Si, r_m[2], r_M[2], lung_D[2]/2.);
    
    l_Be->SetLineColor(30);
    l_1->SetLineColor(41);
    l_2->SetLineColor(41);
    
     /*l_Be->SetTransparency(10);
     l_1->SetTransparency(10);
     l_2->SetTransparency(10);*/
    
    chamber->AddNode(l_Be, 1);
    chamber->AddNode(l_1, 1);
    chamber->AddNode(l_2, 1);
    
    geom->CloseGeometry();
    
    return chamber;
}

vector<dLayer> dLayer::layerMaker()
{
    const dLayer lBe (r_m[0],lung_D[0],r_M[0]-r_m[0]); // beam pipe di berilio
    const dLayer l1 (r_m[1],lung_D[1],r_M[1]-r_m[1]); // layer 1 di silicio
    const dLayer l2 (r_m[2],lung_D[2],r_M[2]-r_m[2]); // layer 2 di silicio
    
    vector<dLayer> layer;
    layer.push_back(lBe);
    layer.push_back(l1);
    layer.push_back(l2);
    
    return layer;
}

void dLayer::print() const
{
    
    cout<<"radius = "<<raggio<<"cm | length = "<<lunghezza<<"cm | width = "<<spessore<<"cm \n";
    
}





