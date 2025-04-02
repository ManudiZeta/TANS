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
#include "../classes_TANS/phy_TANS/pKinematic.h"
#include "../classes_TANS/phy_TANS/multS.h"
#include "../classes_TANS/phy_TANS/lHit.h"
#include "../classes_TANS/infrast_TANS/sConj.h"

void simulaz_TANS (int n_eve = 1, bool MS = 0, string mul_sel = "hm")
{
    if (n_eve<1){ cout<<" Invalid # of events \n"; return;}
    //gRandom->SetSeed(253180);  //attivare per l'immediata riproducibilità
    
    TStopwatch speedmaster;
    speedmaster.Start();
    cout<<"Loading simulation ... \n";
    vector<dLayer> layer= dLayer::layerMaker();  //caricamento dei detector
    
    TFile myf ("../dat_TANS/MC_truth.root","recreate"); //TFile incaricato alla manodopera del file "MC_truth.root"
    TTree *tree = new TTree ("myTree_S", "simulaz_tree"); //TTree dataset colonnare
    
    typedef struct //definisco una struct per leggerezza nel recuperare Z_true nella fase dei residui
    {
        double X,Y,Z;
        int mult;
    } VERT;
    
    static VERT point; // creo un oggetto di tipo VERT che si incarica del vertice (posizione + molteplicità)
    
    TClonesArray *ptrhits = new TClonesArray("lHit",100);
    TClonesArray &hits_ptr = *ptrhits;
    
    TClonesArray *ptrcil = new TClonesArray("cilPoint",100);
    TClonesArray &cil_ptr = *ptrcil;
    
    
    TClonesArray *ptrangs = new TClonesArray("pAng",100);
    TClonesArray &angs_ptr = *ptrangs;
    
    tree->Branch("VertMult",&point,"X/D:Y:Z:mult/I"); //incarico i TBranch delle variabili
    tree->Branch("Hits_cart",&ptrhits);
    tree->Branch("Hits_cil",&ptrcil);
    tree->Branch("Angs",&ptrangs);
    
    int mul=0;
    double phi,eta,theta;
    
    int check[3] = {0,0,0}; //check per gli hit totali su ciascun layer
    int parts = 0; // contatore per il totale delle particelle prodotte in tutti gli eventi
    
    TFile *myKin = new TFile("../dat_TANS/kinem.root");
    TFile *myAng = new TFile("../dat_TANS/kinem.root");
    
    for (int k = 0; k<n_eve; k++) //generazioni di n collisioni (eventi). Lo produco uno a uno in un for loop (qua inizia la fisica)
    {
        if(mul_sel == "hm" || mul_sel == "um" )
        {
            TH1F *ptr_mul = (TH1F*)myKin->Get(&mul_sel[0]);
            do
            {
                mul = int(ptr_mul->GetRandom()); //definisco la molteplicità (# di particelle prodotte in una collisione p-p)
            } while (mul == 0);
            //myKin.Close();
        }
        
        else
        {
            try
            {
                mul = stoi(mul_sel); //metodo di std per la conversione da stringa a int
            }
            catch(exception& e) //chech del numero
            {
                cout<<"MUL: invalid value selected. Retry with these inputs: \n";
                cout<<" hm = heta mult | um = unif mult | number in 1-100 range \n ";
                return;
            }
            
            if (mul <=0 || mul>100)
            {
                cout<<"MUL: invalid value selected. Retry with these inputs: \n";
                cout<<" hm = heta mult | um = unif mult | number in 1-100 range \n ";
                return;
            }
            
        }
        
        cPoint ver(gRandom->Gaus(0,0.01),gRandom->Gaus(0,0.01), gRandom->Gaus(0,5.3)); // creazione del vertice gaussiano [cm]
        point.mult = mul;
        point.X = ver.getX();
        point.Y = ver.getY();
        point.Z = ver.getZ();
        
        int in = 0; // riferimento sul TCA per non aver dei buchi nel riempimento (ERRORE)
        parts=parts + mul; //aggiorno il totale delle particelle
        
        double comp [3]; // creo un array di componenti del vettore particella (il k che viene ruotato)
        double *comp_ptr = comp; //puntatore che passa come arogmento della rotazione (se MS = 1)
        
        for (int j = 0; j<mul; j++) //loop su tutte le particelle prodotte per vedere dove colpiscono i rivelatori ed eventualemnte caricare sul TCA
        {
            //cout<<"\n***Particle no "<<j+1<<"| Ev. "<<k<<"***\n";
            //phi
            phi = (gRandom->Rndm())*2.*M_PI; //generazione di phi uniforme da 0 a 2pi
            //eta
            TH1F *ptr_ang = (TH1F*)myAng->Get("heta2");
            
            eta = ptr_ang->GetRandom(); // generazione di ETA da PDF assegnata
            theta  = pAng::EtoT(eta);
            new(angs_ptr[j])pAng(phi,theta);
            
            comp[0] = pKinematic::c_1(theta, phi);
            comp[1] = pKinematic::c_2(theta, phi);
            comp[2] = pKinematic::c_3(theta);
            double rad = 0; // riferimento per la creazione dell'hit
            
            for (int d = 0; d<3; d++)
            {
                pAng angs(phi,theta);
                cPoint pHit = pKinematic::kinPoint(ver,comp_ptr,layer[d]); //particella cinetica (kin) che parte dal vertice, con componenti comp_ptr, e che va verso il d-esimo rivelatore
                
                bool check_all = pKinematic::allCheck(pHit,layer[d]); //vediamo se la j-esima particella è dentro al rivelatore d in raggio e lunghezza
                
                if (check_all == 0 ) //se non è dentro al rivelatore, non la salvo
                {
                    break;
                }
                
                else //altrimenti inserisco gli hit con successo, nel TClones array
                {
                    rad = layer[d].getR();
                    lHit hit(pHit,rad);
                    
                    new(hits_ptr[in])lHit(hit); //sto  mettendo l'hit nella in-esima posizione del TClonesArray pre-allocata righe fa
                    new(cil_ptr[in])cilPoint(pHit);
                    
                    lHit *tst=(lHit*)hits_ptr.At(in); // così perché il TClonesArray() riconosce lHit come un TObject, per il quale NON sono definiti i metodi di lHit! Di seguito, quindi, non potrei usare print()
                    
                    in++; //vado a vanti nel TCA
                    //cout<<d+1<<") Hit in : \n";
                    //angs.print();
                    //tst->print();
                    //cout<<endl;
                    check[d]++;
                    if (MS == 1)
                    {
                        multS::pRotate (phi,theta, comp_ptr); //agisce il multiple scattering
                    }
                }
            }
        }
        tree->Fill();
        //sConj::endEv(k,ptrhits->GetEntries(),ver,mul); //stampe relative al singolo evento
        ptrhits->Clear();
        ptrangs->Clear();
        ptrcil->Clear();
    }
    
    //sConj::endSim(MS,n_eve,parts,check); //stampe relative all'intera simulazione
    
    myf.Write();
    myf.Close();
    
    delete ptrhits;
    delete ptrangs;
    delete ptrcil;
    delete myKin;
    delete myAng;
    
    speedmaster.Stop();
    cout<<"\n  Time [s] : ";
    speedmaster.Print();
    cout<<"  Sim. #event/s [Hz]: ";
    cout<<n_eve/speedmaster.CpuTime()<<endl;
}


