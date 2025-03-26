#include "rTklet.h"

ClassImp(rTklet)


double rTklet::tkGen (const cilPoint &p_2, const cilPoint &p_3)

{
    double num = (p_2.getZ()-p_3.getZ())*p_2.getR();
    double den = p_3.getR()-p_2.getR();
    return num/den + p_2.getZ();
    
}

void rTklet::phiCoupler (const vector<cilPoint> &vec_2, const vector<cilPoint> &vec_3, vector<double> &z_rec_vec)
{
    for (vector<cilPoint>::size_type it = 0; it != vec_2.size(); it++)
    {
        for (vector<cilPoint>::size_type j = 0; j != vec_3.size(); j++)
        {
            if (abs(vec_2[it].getP() - vec_3[j].getP()) < 0.01)
            {
                //cout<<" coppia "<<it<< " = "<<vec_2[it].getP()<<" , "<<vec_3[j].getP();
                double z_rec = tkGen (vec_2[it],vec_3[j]);
                z_rec_vec.push_back(z_rec);
                //cout<<" | Z_rec = "<<z_rec<<"cm "<<endl;
            }
        }
        
    }
    
}

double rTklet::ZREC (const vector<double> &z_rec_vec, const double &window)
{
    vector <double> rw;
    
    double mean = accumulate(z_rec_vec.begin(), z_rec_vec.end(), 0.0) / z_rec_vec.size(); // metodo di std per calcolare la media  su un vec
    
    double sq_sum = inner_product(z_rec_vec.begin(), z_rec_vec.end(), z_rec_vec.begin(), 0.0);
    double stdev = sqrt(sq_sum / z_rec_vec.size() - mean * mean);
    
    for (vector<double>::size_type j = 0; j != z_rec_vec.size(); j++) //elimino i dati troppo esterni, ovvero quelli fuori da window*stdev
    {
        if(abs(z_rec_vec[j] - mean) < window*stdev)
        {
            rw.push_back(z_rec_vec[j]);
        }
    }
    
    return accumulate(rw.begin(), rw.end(), 0.0) / rw.size();
    
}





