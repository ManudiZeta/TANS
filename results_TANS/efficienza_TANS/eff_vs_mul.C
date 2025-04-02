#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TBranch.h"
#include "TGraphErrors.h"
#include "TEfficiency.h"

void eff_vs_mul()
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
    TFile hfile1("../dat_TANS/MC_truth.root");
    TTree *tree1 = (TTree*)hfile1.Get("myTree_S");
    TBranch *b1 = tree1->GetBranch("VertMult");
    b1->SetAddress(&point.X);

    
    double zR;
    TFile hfile2("../dat_TANS/ricostruz.root");
    TTree *tree2 = (TTree*)hfile2.Get("myTree_R");
    TLeaf *l2 = tree2->GetLeaf("z_rec");
    l2->SetAddress(&zR);
    
    double mul;
    TEfficiency* pEff = new TEfficiency("eff","#epsilon vs Multiplicity ;mul;#epsilon",20,0,60);
    int nev = tree1->GetEntries();

    for(int ev=0;ev<nev;ev++)
    {
        tree1->GetEvent(ev);
        tree2->GetEvent(ev);
        
        mul = point.mult;
        
        pEff->Fill(!isnan(zR),mul);

    }

    TCanvas *sh = new TCanvas();
    pEff->Draw("AP");
    sh->SaveAs("efficienza_TANS/eff_vs_mul.pdf");
    sh->SaveAs("../readMe_TANS/images/eff_vs_mul.pdf");
    
}
