#include <Riostream.h>
#include <string>
#include <math.h>
#include <TH1D.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include <TFile.h>


void residues_TANS (const string histo_name = "hm", const string choice = "recreate")
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
    
    typedef struct
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
    
    TFile myfile ("../dat_TANS/fin_histos.root", &choice[0]);
    
    char nome_histo[20];
    int cx;
    cx = snprintf (nome_histo, 20, "histo_%s", &histo_name[0]);
    
    char mul_histo[20];
    int dx;
    dx = snprintf (mul_histo, 20, " mul = %s", &histo_name[0]);

    TH1D *histo_res = new TH1D(nome_histo, mul_histo, 100, -1000, +1000);
    histo_res->GetXaxis()->SetTitle("Z_true - Z_rec [um]");
    histo_res->GetYaxis()->SetTitle("Counts");
    double dZ = 0.;
    
    for(int ev=0;ev<tree2->GetEntries();ev++)
    {
        tree1->GetEvent(ev);
        tree2->GetEvent(ev);
        dZ = double (10000*point.Z-10000*zR);
        cout<<"EV "<<ev<<" (Z_true = "<<10000*point.Z<<"um , Z_rec = "<<10000*zR<<"um )  | dZ = "<<dZ<<" um \n";
        if(isnan(dZ) == 0)
        {
            histo_res->Fill(dZ);
        }

    }

    myfile.Write();
    
}
