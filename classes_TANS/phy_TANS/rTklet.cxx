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
            if (abs(vec_2[it].getP() - vec_3[j].getP()) < 0.005)
            {
                //cout<<" coppia "<<it<< " = "<<vec_2[it].getP()<<" , "<<vec_3[j].getP();
                double z_rec = tkGen (vec_2[it],vec_3[j]);
                z_rec_vec.push_back(z_rec);
                //cout<<" | Z_rec = "<<z_rec<<"cm "<<endl;
            }
        }
        
    }
    
}

double rTklet::mean_vec (const vector<double> &z_rec_vec)
{
    double counter = 0.;
    int N = int (z_rec_vec.size());
    
    for (vector<double>::size_type j = 0; j != z_rec_vec.size(); j++)
    {
        counter = counter + z_rec_vec[j];
    }
    
    return counter/N;
    
}

double rTklet::sdev_vec (const vector<double> &z_rec_vec, const double mean)
{
    double counter = 0.;
    int N = int (z_rec_vec.size());
    
    for (vector<double>::size_type j = 0; j != z_rec_vec.size(); j++)
    {
        counter = counter + (z_rec_vec[j] - mean)*(z_rec_vec[j] - mean);
    }
    
    return sqrt(counter/(N-1));
    
}


double rTklet::ZREC (const vector<double> &z_rec_vec, const double &window)
{
    vector <double> rw;
    
    double mean = mean_vec(z_rec_vec); // metodo di std per calcolare la media  su un vec
    double stdev = sdev_vec(z_rec_vec, mean);
    
    for (vector<double>::size_type j = 0; j != z_rec_vec.size(); j++) //elimino i dati troppo esterni, ovvero quelli fuori da window*stdev
    {
        if(abs(z_rec_vec[j] - mean) < window*stdev)
        {
            rw.push_back(z_rec_vec[j]);
        }
    }
    
    return mean_vec(rw);
    
}





