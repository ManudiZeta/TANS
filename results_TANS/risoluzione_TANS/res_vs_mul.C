#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TGraphErrors.h"

void res_vs_mul ()
{
    const int n = 10;
    double mul[n] = {5,6,8,10,15,20,30,40,50,60};
    double dmul[n];
    double ris[n];
    double dris[n];
    
    for(int j=0; j<n; j++)
    {
        dmul[j] = 0.;
        dris[j] = 0.;
    }
    
    string in ="../dat_TANS/residues.root";
    ifstream in_file(in);
    if(!in_file)
    {
        cout<<"Selected root file doesn't exist.\n";
        return;
    }
    in_file.close();
    
    TFile myf ("../dat_TANS/residues.root");
    
    for(int j=0; j<n; j++)
    {
        string str = to_string(int(mul[j]));
        string histo = "histo_res_" + str;
        
        cout<<"stringa = "<<histo<<endl;
        TH1D *histo_ptr = (TH1D*)myf.Get(&histo[0]);
        ris[j] = histo_ptr->GetStdDev();
        
    }
    
    TGraphErrors *gr = new TGraphErrors(n,mul,ris,dmul,dris);
    gr->SetTitle("Risoluzione vs molteplicita'");
    gr->GetXaxis()->SetTitle("Molteplicita' []");
    gr->GetYaxis()->SetTitle("Risoluzione [um]");
    
    TCanvas *tela = new TCanvas();
    gr->Draw("AP*");
    tela->SaveAs("risoluzione_TANS/ris_vs_mul.pdf");
    tela->SaveAs("../readMe_TANS/images/ris_vs_mul.pdf");
    
}
