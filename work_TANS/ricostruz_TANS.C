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
#include "../classes_TANS/phy_TANS/rTklet.h"


void ricostruz_TANS (const double window = 1) // finestra di window*dev_std rispetto alla media svolta sui Z_rec che hanno passato il provino
{

    TStopwatch speedmaster;
    speedmaster.Start();
    cout<<"Loading reconstruction ... \n";
    
    string in = "../dat_TANS/data.root";
    
    ifstream in_file(in);
    if(!in_file)
    {
        cout<<"Selected root file doesn't exist. Please, generate it with 'dataReal_TANS.C' or insert another root file \n";
        return;
    }
    in_file.close();
    
    string out = "../dat_TANS/ricostruz.root";
    
    TFile myf (&out[0],"recreate"); //TFile incaricato alla manodopera del file "ricostruz.root"
    TTree *tree_out = new TTree ("myTree_R", "ricostruz_tree"); //TTree dataset colonnare
    
    double z_rec;
    tree_out->Branch("z_rec",&z_rec,"z_rec/D");
    
    //gRandom->SetSeed(253180);
   
    TFile hfile(&in[0]);
    TClonesArray *ptrcil_in = new TClonesArray("cilPoint",100);
    TTree *tree_in = (TTree*)hfile.Get("myTree_data");
    
    if (!tree_in)
    {
        cout<< "Tree not found in file!" <<endl;
        return;
    }
    
    TBranch *b1_in = tree_in->GetBranch("Hits_cil");
    b1_in->SetAddress(&ptrcil_in);
    int counter = 0;
    vector<cilPoint> phi_2;
    vector<cilPoint> phi_3;
    vector<double> z_rec_vec;
    int n_eve =tree_in->GetEntries();
    
    for(int ev=0;ev<n_eve;ev++)
    {
        phi_2.clear();
        phi_3.clear();
        //cout<<"\n********** EVENT "<<ev+1<<"********** \n";
        tree_in->GetEvent(ev);
        int num=ptrcil_in->GetEntries(); //numero di hit in un ev-esimo evento (lo prendo dal branch)
        
        for (int j=0; j<num; j++)
        {
            cilPoint *tst=(cilPoint*)ptrcil_in->At(j);
            double R = tst->getR();
            if (R < 4.5) {phi_2.push_back(*tst);}
            else {phi_3.push_back(*tst);}
        }
        
        /*cout<<" Dim 2 = "<<phi_2.size()<<endl;
        cout<<" Dim 3 = "<<phi_3.size()<<endl;*/
        
        rTklet::phiCoupler(phi_2, phi_3,z_rec_vec);
        sort(z_rec_vec.begin(), z_rec_vec.end());

        z_rec =  rTklet::ZREC(z_rec_vec, window);
        //cout<<"\n * Z_REC  = "<<z_rec<<endl;
        if(isnan(z_rec) != 0) //controllo sull'inefficienza di ricostruzione
        {
            //cout<<"NAN alert \n";
        }
        tree_out->Fill();
        phi_2.clear();
        phi_3.clear();
        z_rec_vec.clear();
    }
    
    myf.Write();
    myf.Close();
    delete ptrcil_in;
    
    speedmaster.Stop();
    cout<<"\n  Time [s] : ";
    speedmaster.Print();
    cout<<"  Rec. #event/s [Hz]: ";
    cout<<n_eve/speedmaster.CpuTime()<<endl;
}
