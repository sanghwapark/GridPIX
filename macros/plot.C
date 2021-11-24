void plot(string fin)
{

  TFile *f = new TFile(fin.c_str());
  TTreeReader reader("events", f);
  TTreeReaderArray<int64_t> br_id(reader, "GridpixHits.cellID");
  TTreeReaderArray<int>    br_pid(reader, "GridpixHits.truth.pdgID");
  TTreeReaderArray<double> br_x(reader, "GridpixHits.position.x");
  TTreeReaderArray<double> br_y(reader, "GridpixHits.position.y");
  TTreeReaderArray<double> mc_px(reader, "mcparticles.ps.x");
  TTreeReaderArray<double> mc_py(reader, "mcparticles.ps.y");
  TTreeReaderArray<double> mc_pz(reader, "mcparticles.ps.z");
  TTreeReaderArray<int>    mc_status(reader, "mcparticles.genStatus");

  auto h1 = new TH1F("h1","h1",50,0,50);
  auto hp = new TH1F("hp","hp",100,0,1);

  while(reader.Next()) {
    Long64_t event_number = reader.GetCurrentEntry();
    Long64_t hits_count = br_id.GetSize();

    for(int imc = 0; imc<mc_status.GetSize(); imc++)
      {
	if( mc_status[imc] == 1)
	  {
	    double p = sqrt(mc_px[imc]*mc_px[imc] + mc_py[imc]*mc_py[imc] + mc_pz[imc]*mc_pz[imc]);
	    hp->Fill(p);
	    cout << p << endl;

	  }
      }

    for(int hit_i = 0; hit_i < hits_count; hit_i++) {
      
      if( br_pid[hit_i] != 11) continue;

      Long64_t id = br_id[hit_i];
      Long64_t sector_id = (id>>8)&0xFF;
      double x = br_x[hit_i];
      double y = br_y[hit_i];

      h1->Fill(sector_id);
    }      
  }

    hp->Draw();

      
}
