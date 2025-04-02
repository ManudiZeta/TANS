void imgen_TANS()
{
    
    //*********************************************** SIMULAZIONE
    ifstream in_file("../dat_TANS/MC_truth.root");
    
    if(!in_file)
    {
        cout<<"The root file doesn't exist. Generate it. \n";
        return;
    }
    in_file.close();
    TFile mys("../dat_TANS/MC_truth.root");
    
    TTree *tree = (TTree*)mys.Get("myTree_S");
    TCanvas *tela = new TCanvas();
    
    tree->Draw("Hits_cart.punto.ascissa");
    TH2F *htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Hit [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("../readME_TANS/images/S_x_tot.pdf");
    
    tree->Draw("Hits_cart.punto.ordinata");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Hit [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("../readME_TANS/images/S_y_tot.pdf");
    
    tree->Draw("Hits_cart.punto.quota");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Hit [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("../readME_TANS/images/S_z_tot.pdf");
    
    tree->Draw("Hits_cart.strato");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("R_Layer [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("../readME_TANS/images/S_layers.pdf");
    
   /* tree->Draw("Angs.phi");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("phi [rad]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("images_TANS/angs_TANS/angs_sim/S_phi.pdf");
    
    tree->Draw("Angs.teta");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("theta [rad]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("images_TANS/angs_TANS/angs_sim/S_theta.pdf");
    
    tree->Draw("Angs.eta");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("eta []");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("images_TANS/angs_TANS/angs_sim/S_eta.pdf"); */
    
    tree->Draw("VertMult.Z");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Z_true [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("../readME_TANS/images/S_z_true.pdf");
    
    tree->Draw("VertMult.mult");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Mult[]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("../readME_TANS/images/S_mult.pdf");
    
    mys.Close();
    delete tela;
    //*********************************************** DATA
    
    ifstream in_file_d("../dat_TANS/data.root");
    
    if(!in_file_d)
    {
        cout<<"The root file doesn't exist. Generate it. \n";
        return;
    }
    in_file_d.close();
    TFile mys_d("../dat_TANS/data.root");
    
    TTree *tree_d = (TTree*)mys_d.Get("myTree_data");
    TCanvas *tela_d = new TCanvas();
    
    tree_d->Draw("Hits_cart.punto.ascissa");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Hit [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela_d->SaveAs("../readME_TANS/images/D_x_tot.pdf");
    
    tree_d->Draw("Hits_cart.punto.ordinata");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Hit [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela_d->SaveAs("../readME_TANS/images/D_y_tot.pdf");
    
    tree_d->Draw("Hits_cart.punto.quota");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Hit [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela_d->SaveAs("../readME_TANS/images/D_z_tot.pdf");
    
    tree_d->Draw("Hits_cart.strato");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("R_Layer [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela_d->SaveAs("../readME_TANS/images/D_layers.pdf");
    
    delete tela_d;
    
    //*********************************************** RICOSTRUZIONE
    ifstream in_file_r("../dat_TANS/ricostruz.root");
    
    if(!in_file_r)
    {
        cout<<"The root file doesn't exist. Generate it. \n";
        return;
    }
    in_file_r.close();
    TFile mys_r("../dat_TANS/ricostruz.root");
    
    TTree *tree_r = (TTree*)mys_r.Get("myTree_R");
    TCanvas *tela_r = new TCanvas();
    
    tree_r->Draw("z_rec");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Z_rec [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela_r->SaveAs("../readME_TANS/images/R_z_rec.pdf");
    
    delete tela_r;
    
    
    //*********************************************** RESIDUI
    ifstream in_file_res("../dat_TANS/residues.root");
    
    if(!in_file_res)
    {
        cout<<"The root file doesn't exist. Generate it. \n";
        return;
    }
    in_file_res.close();
    TFile mys_res("../dat_TANS/residues.root");
    
    TTree *tree_res = (TTree*)mys_res.Get("myTree_res");
    TCanvas *tela_res = new TCanvas();
    
    tree_res->Draw("Res.dZ");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("dZ [um]");
    htemp->GetYaxis()->SetTitle("counts");
    tela_res->SaveAs("../readME_TANS/images/res_dz.pdf");
    
    tree_res->Draw("Res.Zt");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Z_true [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela_res->SaveAs("../readME_TANS/images/res_Zt.pdf");
    
    delete tela_res;
}


/*
 tree->Draw("Hits_cart.punto.ascissa", "Hits.strato==3");
 htemp = (TH2F*)gPad->GetPrimitive("htemp");
 htemp->GetXaxis()->SetTitle("Hit [cm]");
 htemp->GetYaxis()->SetTitle("counts");
 tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_x_l0.pdf");
 
 tree->Draw("Hits_cart.punto.ascissa", "Hits.strato==4");
 htemp = (TH2F*)gPad->GetPrimitive("htemp");
 htemp->GetXaxis()->SetTitle("Hit [cm]");
 htemp->GetYaxis()->SetTitle("counts");
 tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_x_l1.pdf");
 
 tree->Draw("Hits_cart.punto.ascissa", "Hits.strato==7");
 htemp = (TH2F*)gPad->GetPrimitive("htemp");
 htemp->GetXaxis()->SetTitle("Hit [cm]");
 htemp->GetYaxis()->SetTitle("counts");
 tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_x_l2.pdf");
 
 tree->Draw("Hits_cart.punto.ordinata", "Hits.strato==3");
 htemp = (TH2F*)gPad->GetPrimitive("htemp");
 htemp->GetXaxis()->SetTitle("Hit [cm]");
 htemp->GetYaxis()->SetTitle("counts");
 tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_y_l0.pdf");
 
 tree->Draw("Hits_cart.punto.ordinata", "Hits.strato==4");
 htemp = (TH2F*)gPad->GetPrimitive("htemp");
 htemp->GetXaxis()->SetTitle("Hit [cm]");
 htemp->GetYaxis()->SetTitle("counts");
 tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_y_l1.pdf");
 
 tree->Draw("Hits_cart.punto.ordinata", "Hits.strato==7");
 htemp = (TH2F*)gPad->GetPrimitive("htemp");
 htemp->GetXaxis()->SetTitle("Hit [cm]");
 htemp->GetYaxis()->SetTitle("counts");
 tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_y_l2.pdf");
 
 tree->Draw("Hits_cart.punto.quota", "Hits.strato==3");
 htemp = (TH2F*)gPad->GetPrimitive("htemp");
 htemp->GetXaxis()->SetTitle("Hit [cm]");
 htemp->GetYaxis()->SetTitle("counts");
 tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_z_l0.pdf");
 
 tree->Draw("Hits_cart.punto.quota", "Hits.strato==4");
 htemp = (TH2F*)gPad->GetPrimitive("htemp");
 htemp->GetXaxis()->SetTitle("Hit [cm]");
 htemp->GetYaxis()->SetTitle("counts");
 tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_z_l1.pdf");
 
 tree->Draw("Hits_cart.punto.quota", "Hits.strato==7");
 htemp = (TH2F*)gPad->GetPrimitive("htemp");
 htemp->GetXaxis()->SetTitle("Hit [cm]");
 htemp->GetYaxis()->SetTitle("counts");
 tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_z_l2.pdf");
 
 tree->Draw("Hits_cart.punto.quota");
 htemp = (TH2F*)gPad->GetPrimitive("htemp");
 htemp->GetXaxis()->SetTitle("Hit [cm]");
 htemp->GetYaxis()->SetTitle("counts");
 tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_z_tot.pdf");
 
 
 
 
 
 */
