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

void all_residues()
{
    const int n = 10;
    string cas_mul[n] = {"5","6","8","10","15","20","30","40","50","60"};
    double num_s [n];
    double num_i [n];
    
    string lim_s [n];
    string lim_i [n];
    
    for(int j=1; j<n; j++)
    {
        
        num_s [j] = 1000 - 12*stoi(cas_mul[j]);
        num_i [j] = -1000 + 12*stoi(cas_mul[j]);
        
        lim_s [j] = to_string(num_s[j]);
        lim_i [j] = to_string(num_i[j]);
    }
    
    
    string in ="../dat_TANS/residues.root";
    ifstream in_file(in);
    if(!in_file)
    {
        cout<<"Selected root file doesn't exist. \n";
        return;
    }
    in_file.close();
    
    TFile myf ("../dat_TANS/residues.root","update");
    TTree *tree = (TTree*)myf.Get("myTree_res");
    
    for(int j=0; j<n; j++)
    {
        string name = "histo_res_"+cas_mul[j];
        string prefix = "Res.dZ>>"+ name+ "(100,"+lim_i[j]+","+ lim_s[j]+")";
        string choice = "Res.mul ==" + cas_mul[j];
        TCanvas *side = new TCanvas();
        tree->Draw(&prefix[0], &choice[0]);
        delete side;
        
        TH1D *histo_res = (TH1D*)gDirectory->Get(&name[0]);
        TF1 *myfunc = new TF1 ("myfunc","gaus", num_i[j],num_s[j]);
        histo_res->GetXaxis()->SetTitle("Z_true - Z_rec [um]");
        histo_res->GetYaxis()->SetTitle("Counts");
        
        TCanvas *tela = new TCanvas();
        histo_res->Draw("same");
        histo_res->Fit("myfunc","q","",num_i[j],num_s[j]);
        myfunc->Draw("same");
        string save_name = "residui_TANS/" + cas_mul[j] +".pdf";
        string save_name_1 = "../readMe_TANS/images/" + cas_mul[j] +".pdf";
        tela->SaveAs(&save_name[0]);
        tela->SaveAs(&save_name_1[0]);
        myf.Write("",TObject::kOverwrite);
        delete tela;
        delete myfunc;
    }
    
}
