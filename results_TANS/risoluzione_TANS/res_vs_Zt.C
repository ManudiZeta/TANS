#include <Riostream.h>
#include <string>
#include <math.h>
#include <TH1D.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TGraphErrors.h"
#include <TFile.h>

void res_vs_Zt()
{
    
    TFile myf ("../dat_TANS/residues.root");
    TTree *tree = (TTree*)myf.Get("myTree_res");
    const int n = 10;
    double Zt[n] = {-15.,-12.,-9.,-6.,-3.,3.,6.,9.,12.,15.};
    double res [n];
    double err [n] = {0,0,0,0,0,0,0,0,0,0};
    
    TCanvas *tela = new TCanvas();
    
    tree->Draw("dZ","-16.5<Zt && Zt<-13.5");
    TH1D *htemp = (TH1D*)gPad->GetPrimitive("htemp");
    res[0] = htemp->GetStdDev();
    
    tree->Draw("dZ","-14<Zt && Zt<-10");
    htemp = (TH1D*)gPad->GetPrimitive("htemp");
    res[1] = htemp->GetStdDev();
    
    tree->Draw("dZ","-11<Zt && Zt<-7");
    htemp = (TH1D*)gPad->GetPrimitive("htemp");
    res[2] = htemp->GetStdDev();
    
    tree->Draw("dZ","-7<Zt && Zt<-5");
    htemp = (TH1D*)gPad->GetPrimitive("htemp");
    res[3] = htemp->GetStdDev();
    
    tree->Draw("dZ","-5<Zt && Zt<-1");
    htemp = (TH1D*)gPad->GetPrimitive("htemp");
    res[4] = htemp->GetStdDev();
    
    tree->Draw("dZ","1<Zt && Zt<5");
    htemp = (TH1D*)gPad->GetPrimitive("htemp");
    res[5] = htemp->GetStdDev();
    
    tree->Draw("dZ","5<Zt && Zt<7");
    htemp = (TH1D*)gPad->GetPrimitive("htemp");
    res[6] = htemp->GetStdDev();
    
    tree->Draw("dZ","7<Zt && Zt<11");
    htemp = (TH1D*)gPad->GetPrimitive("htemp");
    res[7] = htemp->GetStdDev();
        
    tree->Draw("dZ","10<Zt && Zt<14");
    htemp = (TH1D*)gPad->GetPrimitive("htemp");
    res[8] = htemp->GetStdDev();
    
    tree->Draw("dZ","13.5<Zt && Zt<16.5");
    htemp = (TH1D*)gPad->GetPrimitive("htemp");
    res[9] = htemp->GetStdDev();
    
    myf.Close();
    delete tela;
    
    TGraphErrors *gr = new TGraphErrors(n,Zt,res,err,err);
    gr->SetTitle("Risoluzione vs Z_vert");
    gr->GetXaxis()->SetTitle("Z_true [cm]");
    gr->GetYaxis()->SetTitle("Risoluzione [um]");
    
    TCanvas *sh = new TCanvas();
    gr->Draw("AP*");
    sh->SaveAs("risoluzione_TANS/ris_vs_Z.pdf");
    sh->SaveAs("../readMe_TANS/images/ris_vs_Z.pdf");
    
    
}

