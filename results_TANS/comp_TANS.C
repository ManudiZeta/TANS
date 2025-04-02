void comp_TANS(TString myopt="fast")

{
    TStopwatch speedmaster;
    speedmaster.Start();
    
  TString opt;
    
  if(myopt.Contains("force"))
  {
    opt = "kfg"; //k= ottimizzazione, g= codice che permete di usare i debugger, f= forza la compilazione (è come mettere ++ quando lo faccio a mano...equivale a force)
  }
    
  else
  {
    opt = "kg"; //qua non c'è force, quindi compla solo se ce n'è bisogno...
  }
    //compilo le classi
    gSystem->CompileMacro("../classes_TANS/detectors_TANS/dLayer.cxx",opt.Data());
    gSystem->CompileMacro("../classes_TANS/points_TANS/pAng.cxx",opt.Data());
    gSystem->CompileMacro("../classes_TANS/points_TANS/cPoint.cxx",opt.Data());
    gSystem->CompileMacro("../classes_TANS/points_TANS/cilPoint.cxx",opt.Data());
    gSystem->CompileMacro("../classes_TANS/detectors_TANS/smLayer.cxx",opt.Data());
    gSystem->CompileMacro("../classes_TANS/phy_TANS/pKinematic.cxx",opt.Data());
    gSystem->CompileMacro("../classes_TANS/phy_TANS/multS.cxx",opt.Data());
    gSystem->CompileMacro("../classes_TANS/phy_TANS/rTklet.cxx",opt.Data());
    gSystem->CompileMacro("../classes_TANS/phy_TANS/lHit.cxx",opt.Data());
    gSystem->CompileMacro("../classes_TANS/infrast_TANS/sConj.cxx",opt.Data());
    
    
    gSystem->CompileMacro("all_residues.C",opt.Data());
    gSystem->CompileMacro("risoluzione_TANS/res_vs_mul.C",opt.Data());
    gSystem->CompileMacro("risoluzione_TANS/res_vs_mul.C",opt.Data());
    gSystem->CompileMacro("risoluzione_TANS/res_vs_Zt.C",opt.Data());
    gSystem->CompileMacro("efficienza_TANS/eff_vs_mul.C",opt.Data());
    gSystem->CompileMacro("efficienza_TANS/eff_vs_Zt.C",opt.Data());
    
    speedmaster.Stop();
    speedmaster.Print();
    
    

}

