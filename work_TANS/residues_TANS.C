#include <Riostream.h>
#include <string>
#include <math.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include <TFile.h>
#include "simulaz_TANS.C"
#include "dataReal_TANS.C"
#include "ricostruz_TANS.C"

void residues_TANS ()
{
    string in_1 = "../dat_TANS/MC_truth.root";
    string in_2 = "../dat_TANS/ricostruz.root";
    
    ifstream in_f1(in_1);
    ifstream in_f2(in_2);
    
    if(!in_f1 | !in_f2)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    in_f2.close();
    
    typedef struct //struct per prelevare dalla realtà montecarlo
    {
        double X,Y,Z;
        int mult;
    } VTX;
    
    
    static VTX point;
    TFile hfile1(&in_1[0]);
    TTree *tree1 = (TTree*)hfile1.Get("myTree_S");
    TBranch *b1 = tree1->GetBranch("VertMult");
    b1->SetAddress(&point.X);

    
    double zR;
    TFile hfile2(&in_2[0]);
    TTree *tree2 = (TTree*)hfile2.Get("myTree_R");
    TLeaf *l2 = tree2->GetLeaf("z_rec");
    l2->SetAddress(&zR);
    
    int nev = tree2->GetEntries();
    
    TFile myfile ("../dat_TANS/residues.root", "recreate");
    TTree *tree_res = new TTree ("myTree_res", "res_tree");
    
    typedef struct //struct per accorpare residuo e molteplicità
    {
        double Zt, dZ;
        int mul;
    } RES;
    
    static RES res_mul;
    tree_res->Branch("Res",&res_mul,"Zt/D:dZ:mul/I");
  
    double cut = 1000.;
    double DZ=0; //variabile d'appoggio del programma

    for(int ev=0;ev<nev;ev++)
    {
        tree1->GetEvent(ev);
        tree2->GetEvent(ev);
        res_mul.mul = point.mult;
        res_mul.Zt = point.Z;
        
        DZ = double (10000*(point.Z-zR));
        res_mul.dZ = DZ;
        if(isnan(DZ) == 0 && abs(DZ)<cut) // controllo sui NAN presenti nella ricostruzione (vengono così eliminati dal calcolo dei residui). 
        {
            cout<<"EV "<<ev<<" (Z_true = "<<point.Z<<"cm , Z_rec = "<<zR<<"cm )  | dZ = "<<DZ<<" \u03BCm \n";
            tree_res->Fill();
        }

    }

    myfile.Write();
    
}
