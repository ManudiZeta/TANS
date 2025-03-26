#include "sConj.h"
ClassImp(sConj)


void sConj::endSim (const int MS, const int n_eve, const int parts, const int *check)
{
    cout<<"\n\n************ END OF SIMULATION ************"<<endl<<endl;
    cout<<"Simulated events: "<<n_eve<<endl;
    cout<<"Total particles: "<<parts<<endl;
    cout<<"Total hits L1: "<<check[0]<<endl;
    cout<<"Total hits L2: "<<check[1]<<endl;
    cout<<"Total hits L3: "<<check[2]<<endl;
    
    if (MS == 1) cout<<"Multiple scattering: ACTIVE \n";
    else cout<<"Multiple scattering: INACTIVE \n";
}

void sConj::endEv(const int k , const int entries, const cPoint &ver, const int mul)
{
    cout<<endl;
    cout<<"Event: "<<k+1<<""<<endl;
    cout<<"Hits: "<<entries<<endl;
    cout<<"Vertex: ";
    ver.print();
    cout<<" | Mult= "<<mul<<endl;
}
