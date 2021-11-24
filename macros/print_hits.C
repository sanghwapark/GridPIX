void print_hits(string fin, double ene)
{

  auto file = new TFile(fin.c_str());
  TTree* T = (TTree*)file->Get("events");
  
  TTreeReader tr(T);
  
  // Truth
  TTreeReaderArray<Int_t>    mcparticles_ID(tr,        "mcparticles.ID");
  TTreeReaderArray<Int_t>    mcparticles_pdgID(tr,     "mcparticles.pdgID");
  TTreeReaderArray<Double_t> mcparticles_psx(tr,       "mcparticles.ps.x");
  TTreeReaderArray<Double_t> mcparticles_psy(tr,       "mcparticles.ps.y");
  TTreeReaderArray<Double_t> mcparticles_psz(tr,       "mcparticles.ps.z");
  TTreeReaderArray<Int_t>    mcparticles_status(tr,    "mcparticles.status");
  TTreeReaderArray<Int_t>    mcparticles_genStatus(tr, "mcparticles.genStatus");
  TTreeReaderArray<Double_t> mcparticles_mass(tr,      "mcparticles.mass");

  //GridPix
  TTreeReaderArray<long>     GridpixHits_cellID(tr,    "GridpixHits.cellID");  
  TTreeReaderArray<Double_t> GridpixHits_x(tr,         "GridpixHits.position.x");
  TTreeReaderArray<Double_t> GridpixHits_y(tr,         "GridpixHits.position.y");
  TTreeReaderArray<Double_t> GridpixHits_z(tr,         "GridpixHits.position.y");
  TTreeReaderArray<Double_t> GridpixHits_px(tr,        "GridpixHits.momentum.x");
  TTreeReaderArray<Double_t> GridpixHits_py(tr,        "GridpixHits.momentum.y");
  TTreeReaderArray<Double_t> GridpixHits_pz(tr,        "GridpixHits.momentum.z");
  TTreeReaderArray<Int_t>    GridpixHits_pid(tr,       "GridpixHits.truth.pdgID");
  TTreeReaderArray<Double_t> GridpixHits_edep(tr,      "GridpixHits.energyDeposit");

  ofstream ofstr(Form("out_pim_%.1fGeV.txt",ene));

  int ievt = 0;
  while(tr.Next())
  {
    ievt = tr.GetCurrentEntry();

    for(int ihit=0; ihit<GridpixHits_cellID.GetSize(); ihit++)
    {
      int pid = GridpixHits_pid[ihit];

      // check pid 
      if(pid != -211) continue;

      double x = GridpixHits_x[ihit];
      double y = GridpixHits_y[ihit];
      double z = GridpixHits_z[ihit];

      double px = GridpixHits_px[ihit];
      double py = GridpixHits_py[ihit];
      double pz = GridpixHits_pz[ihit];
      double p  = sqrt(px*px + py*py + pz*pz);
      double pt = sqrt(px*px + py*py);
      double edep = GridpixHits_edep[ihit];

      ofstr << Form("%d %d %f %f %f %f %f", ievt, ihit, pt, p, x, y, z) << endl;
    }
  }
  ofstr.close();

  file->Close();
}
