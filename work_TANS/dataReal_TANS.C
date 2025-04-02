#include <Riostream.h>
#include <string>
#include <TH1D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include <TFile.h>
#include <vector>
#include "TStopwatch.h"

#include "../classes_TANS/detectors_TANS/dLayer.h"
#include "../classes_TANS/points_TANS/pAng.h"
#include "../classes_TANS/points_TANS/cPoint.h"
#include "../classes_TANS/points_TANS/cilPoint.h"
#include "../classes_TANS/detectors_TANS/smLayer.h"
#include "../classes_TANS/phy_TANS/pKinematic.h"
#include "../classes_TANS/phy_TANS/lHit.h"


void dataReal_TANS (bool spur = 0, double noise = 0.005)
{
    TStopwatch speedmaster;
    speedmaster.Start();
    cout<<"Loading detection ... \n";
    
    string in ="../dat_TANS/MC_truth.root";
    ifstream in_file(in);
    if(!in_file)
    {
        cout<<"Selected root file doesn't exist. Please, generate it with 'simulaz_TANS.C' or insert an existing one \n";
        return;
    }
    in_file.close();
    
    string out = "../dat_TANS/data.root";
    TFile myf (&out[0],"recreate"); //TFile incaricato alla manodopera del file "ricostruz.root"
    TTree *tree_out = new TTree ("myTree_data", "data_tree"); //TTree dataset colonnare
    
    TClonesArray *ptrhits_out = new TClonesArray("lHit",100);
    TClonesArray &hits_ptr_out = *ptrhits_out;
    tree_out->Branch("Hits_cart",&ptrhits_out);
    
    TClonesArray *ptrcil_out = new TClonesArray("cilPoint",100);
    TClonesArray &cil_ptr_out = *ptrcil_out;
    tree_out->Branch("Hits_cil",&ptrcil_out);
    
    
    //gRandom->SetSeed(253180);
    
    TFile hfile(&in[0]);
    TClonesArray *ptrhits_in = new TClonesArray("lHit",100);
    TClonesArray *ptrcil_in = new TClonesArray("cilPoint",100);
    TTree *tree_in = (TTree*)hfile.Get("myTree_S");
    
    if (!tree_in)
    {
        cout<< "Tree not found in file!" <<endl;
        return;
    }
    
    TBranch *b1_in = tree_in->GetBranch("Hits_cart");
    b1_in->SetAddress(&ptrhits_in);
    int counter = 0; //counter per riempire bene i TCA
    int tot_hits = 0; //counter per gli hit totali fra tutti gli eventi (compresi quelli spuri, se ci sono)
    int n_eve = tree_in->GetEntries();
    
    for(int ev=0;ev<n_eve;ev++)
    {
        //cout<<"********** EVENT "<<ev+1<<"********** \n";
        tree_in->GetEvent(ev);
        int num=ptrhits_in->GetEntries(); //numero di hit in un ev-esimo evento
        
        for (int j=0; j<ptrhits_in->GetEntries(); j++)
        {
            lHit *tst=(lHit*)ptrhits_in->At(j);
            cPoint old_P (tst->getPoint());
            cPoint P(smLayer::smearPoint(old_P));
            cilPoint cil_P = cilPoint(P);
            
            double R = tst->getLayer();
            if(R != 3)
            {
                lHit new_hit(P,R);
                new(hits_ptr_out[counter])lHit(new_hit);
                //new_hit.print();
                new(cil_ptr_out[counter])cilPoint(cil_P);
                counter++;
                tot_hits++;
            }
            
            if(spur == 1 && gRandom->Rndm () < noise)
            {
                double layer;
                if (gRandom->Rndm()<0.5) {layer = 4.;}
                else {layer=7.;}
                
                cPoint spur_p (smLayer::spurPoint(layer));
                lHit spur_hit (spur_p,layer);
                new(hits_ptr_out[counter])lHit(spur_hit);
                //spur_hit.print();
                
                cilPoint cil_spur = cilPoint(spur_p);
                new(cil_ptr_out[counter])cilPoint(cil_spur);
                counter++;
                tot_hits++;
            }
            
            
        }
        tree_out->Fill();
        counter = 0;
        //cout<<"\n*****Total hits in ev "<<ev+1<<" = "<<ptrhits_out->GetEntries()<<" *****\n";
        
        ptrhits_in->Clear();
        ptrhits_out->Clear();

        ptrcil_in->Clear();
        ptrcil_out->Clear();

    }
    myf.Write();
    myf.Close();
    
    delete ptrhits_in;
    delete ptrcil_in;
    
    delete ptrhits_out;
    delete ptrcil_out;
    
    //cout<< "\nTotal hits recorded : "<<tot_hits<<endl;
    speedmaster.Stop();
    cout<<"\n  Time [s] : ";
    speedmaster.Print();
    cout<<"  Processed events x s [Hz]: ";
    cout<<n_eve/speedmaster.CpuTime()<<endl;
}
