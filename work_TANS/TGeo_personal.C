#include "TGeoManager.h"
#include "TPolyLine3D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TText.h"
#include "TClonesArray.h"
#include "TView.h"
#include <TFile.h>
#include <vector>

#include "../classes_TANS/detectors_TANS/dLayer.h"
#include "../classes_TANS/points_TANS/pAng.h"
#include "../classes_TANS/points_TANS/cPoint.h"
#include "../classes_TANS/phy_TANS/pKinematic.h"
#include "../classes_TANS/phy_TANS/multS.h"
#include "../classes_TANS/phy_TANS/lHit.h"

double ret_Zrec (const int ev);

void TGeo_personal(int ev =25)
{
    //gRandom->SetSeed(253180);
    string mem = "../dat_TANS/MC_truth.root";
    ifstream in_file(mem);
    if(!in_file) //se il file non esiste, lo creo
    {
        cout<<"Selected root file doesn't exist. Please, generate it.\n";
        return;
        
    }
    in_file.close();
    TFile hfile(&mem[0]);
    
    TGeoVolume *chamber = dLayer::chamberMaker();
    vector<dLayer> layer= dLayer::layerMaker();
    
    // prendo i tree e gli eventi da disegnare
    
    typedef struct
    {
        double X,Y,Z;
        int mult;
    } VTX;
    static VTX point;
    
    TClonesArray *ptrhits = new TClonesArray("lHit",100); //array di 100 lHit, che sono gli hit sui rivelatori. è un oggetto sull'heap, puntato da ptrhits che sta sullo stack
    
    
    TTree *tree = (TTree*)hfile.Get("myTree_S");
    
    if (!tree)
    {
        cout<< "Tree not found in file!" <<endl;
        return;
    }
    
    
    TBranch *b1 = tree->GetBranch("VertMult");
    TBranch *b2 = tree->GetBranch("Hits_cart");
    
    
    
    b1->SetAddress(&point.X);
    b2->SetAddress(&ptrhits);
    
    
    double x[4];
    double y[4];
    double z[4];
    
    int num_ev = tree->GetEntries();
    cout<<"\n# of EVENTS p-p = "<<num_ev<<endl;
    if(ev<0 || ev>num_ev-1)
    {
        ev= int(gRandom->Rndm()*tree->GetEntries()); //prendo un evento a caso tra quelli presenti nel tree
        cout<<"Invalid event selected. Random one. \n";
    }
    tree->GetEvent(ev);
    x[0]=point.X;
    y[0]=point.Y;
    z[0]=point.Z;
    cout<<"# Ev = "<<ev<<" | Mul = "<<point.mult<<endl;
    cout<<"Z_ver = ("<<x[0]<<"cm, "<<y[0]<<"cm, "<<z[0]<<"cm) \n";
    
    int num=ptrhits->GetEntries();
    cout<<"Number of hits: "<<num<<endl;
    
    double raggio=0;
    double z_rec = ret_Zrec (ev);
    
    TClonesArray &hits_ptr = *ptrhits;
    vector <TPolyLine3D*> poly;
    int track=0;
    
    int j=num-1;
    while(j>=0)
    {
        
        lHit *tst=(lHit*)hits_ptr.At(j);
        raggio = tst->getLayer();
        
        if(raggio == layer[0].getR())
        {
            cPoint p1 =tst->getPoint();
            p1.print();
            cout<<endl;
            TPolyLine3D *line = new TPolyLine3D(2);
            line->SetPoint(0, x[0], y[0], z[0]);
            x[1]=p1.getX();
            y[1]=p1.getY();
            z[1]=p1.getZ();
            line->SetPoint(1, x[1], y[1], z[1]);
            line->SetLineColor(2);
            line->SetLineWidth(2);
            poly.push_back(line);
            
            j=j-1;
            track++;
        }
        
        if(raggio == layer[1].getR())
        {
            cPoint p1 =tst->getPoint();
            p1.print();
            cout<<endl;

            lHit *tst_1=(lHit*)hits_ptr.At(j-1);
            cPoint p2 =tst->getPoint();
            
            p2.print();
            cout<<endl;

            TPolyLine3D *line = new TPolyLine3D(3);
            line->SetPoint(0, x[0], y[0], z[0]);
            x[1]=p1.getX();
            y[1]=p1.getY();
            z[1]=p1.getZ();
            line->SetPoint(1, x[1], y[1], z[1]);
            x[2]=p2.getX();
            y[2]=p2.getY();
            z[2]=p2.getZ();
            line->SetPoint(2, x[2], y[2], z[2]);
            line->SetLineColor(4);
            line->SetLineWidth(2);
            poly.push_back(line);
            
            j=j-2;
            track++;
        }
        
        if(raggio == layer[2].getR())
        {

            cPoint p1 =tst->getPoint();
            p1.print();
            cout<<endl;

            
            lHit *tst_1=(lHit*)hits_ptr.At(j-1);
            cPoint p2 =tst->getPoint();
            p2.print();
            cout<<endl;

            lHit *tst_2=(lHit*)hits_ptr.At(j-2);
            cPoint p3 =tst->getPoint();
            p3.print();
            cout<<endl;

            
            TPolyLine3D *line = new TPolyLine3D(3);
            line->SetPoint(0, x[0], y[0], z[0]);
            x[1]=p1.getX();
            y[1]=p1.getY();
            z[1]=p1.getZ();
            line->SetPoint(1, x[1], y[1], z[1]);
            x[2]=p2.getX();
            y[2]=p2.getY();
            z[2]=p2.getZ();
            line->SetPoint(2, x[2], y[2], z[2]);
            x[3]=p3.getX();
            y[3]=p3.getY();
            z[3]=p3.getZ();
            line->SetPoint(3, x[3], y[3], z[3]);
            line->SetLineColor(6);
            line->SetLineWidth(2);
            poly.push_back(line);
            
            j=j-3;
            track++;
        }
        
    }
    
    cout<<"\nZ_true = "<<z[0]<<endl;
    cout<<"Z_rec = "<<z_rec<<endl;
    
    chamber->Draw();
    
    for (auto &line : poly)
    {
        line->Draw("same");
    }
    
    cout<<"Event :"<<ev<<endl;
    cout<<"Total tracks : "<<track<<endl;
    
    ptrhits->Clear();
    
}


double ret_Zrec (const int ev)
{
    double zR;
    TFile f ("../dat_TANS/ricostruz.root");
    TTree *tree2 = (TTree*)f.Get("myTree_R");
    TLeaf *l2 = tree2->GetLeaf("z_rec");
    l2->SetAddress(&zR);
    tree2->GetEvent(ev);
    
    return zR;
}
