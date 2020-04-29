{
  TFile *_file0 = TFile::Open("/Users/meridian/cernbox/www/plots/COVID19_DA/graphsAREU.root");
  TF1 * f = new TF1("f","[&](double*x, double *p){ return p[0]*eccesso_chiamateps_normalised_bergamo_brescia_smoothed->Eval(x[0]); }", 20, 80, 1);
  f->SetParameter(0,1);
  f->Draw();


  TF1* fDieTime = new TF1("fDieTime","[&](double*x, double *p){ if (x[0]>2 && x[0]<25) return TMath::LogNormal(x[0],p[0],0.,p[1]); else return 0.; }",0,50,2);
  fDieTime->SetParameter(0,0.3);
  fDieTime->SetParameter(1,9.5);
  fDieTime->Draw();

  TF1Convolution* psconv= new TF1Convolution(f,fDieTime,0,125);
  TF1* fPSConv= new TF1("fPSConv",psconv,20,80,psconv->GetNpar());
  fPSConv->SetParameter(0,500);
  fPSConv->SetParLimits(0,0,10000);
  fPSConv->FixParameter(1,0.3);
  fPSConv->SetParLimits(2,6,15.);
  fPSConv->FixParameter(2,9.5);
  
  fPSConv->Draw();

  eccesso_deceduti_giornalieri_Brescia->Fit("fPSConv","VEX0R","",20,80);
  eccesso_deceduti_giornalieri_Brescia->Draw("AP");

  TF1 * f1 = new TF1("f1","[&](double*x, double *p){ return p[0]*eccesso_chiamateps_normalised_milano_brianza_smoothed->Eval(x[0]); }", 20, 80, 1);
  f->SetParameter(0,1);
  f->Draw();

  TF1Convolution* psconv1= new TF1Convolution(f1,fDieTime,0,125);
  TF1* fPSConv1= new TF1("fPSConv1",psconv1,20,80,psconv1->GetNpar());
  fPSConv1->SetParameter(0,500);
  fPSConv1->SetParLimits(0,0,10000);
  fPSConv1->FixParameter(1,0.3);
  fPSConv1->SetParLimits(2,6,15.);
  fPSConv1->FixParameter(2,9.5);

  eccesso_deceduti_giornalieri_Milano->Fit("fPSConv1","VEX0R","",20,80);
  eccesso_deceduti_giornalieri_Milano->Draw("AP");
}
