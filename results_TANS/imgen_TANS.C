void imgen_TANS()
{
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
    tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_x_tot.pdf");
    
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
    
    tree->Draw("Hits_cart.punto.ordinata");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Hit [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_y_tot.pdf");
    
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
    
    tree->Draw("Hits_cart.punto.quota");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("Hit [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_z_tot.pdf");
    
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
    
    tree->Draw("Hits_cart.strato");
    htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("R_Layer [cm]");
    htemp->GetYaxis()->SetTitle("counts");
    tela->SaveAs("images_TANS/hits_TANS/hits_sim/S_layers.pdf");
    
    tree->Draw("Angs.phi");
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
    tela->SaveAs("images_TANS/angs_TANS/angs_sim/S_eta.pdf");
    
    
    
    delete tela;
}
