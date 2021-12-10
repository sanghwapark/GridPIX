void pt(string flist, int pid)
{

  auto fout = new TFile("fout.root", "RECREATE");
  // histograms
  auto h2 = new TH2F("h2","Pt vs rapidity", 400, -4, 4, 1000, 0, 100);
  auto hpt = new TH1F("hpt", "pt", 1000, 0, 100);

  // read files
  TChain* chain = new TChain("events");

  ifstream ifstr(flist.c_str());
  string fname;
  while( ifstr >> fname )
    {
      chain->Add(fname.c_str());
    }

  TTreeReader reader(chain);

  TTreeReaderArray<double> mc_px(reader, "mcparticles.ps.x");
  TTreeReaderArray<double> mc_py(reader, "mcparticles.ps.y");
  TTreeReaderArray<double> mc_pz(reader, "mcparticles.ps.z");
  TTreeReaderArray<double> mc_mass(reader,   "mcparticles.mass");
  TTreeReaderArray<int>    mc_pid(reader,    "mcparticles.pdgID");
  TTreeReaderArray<int>    mc_status(reader, "mcparticles.genStatus");

  int nhadrons = 0;
  int naccept = 0;
  int nlowp = 0;
  while(reader.Next()) {

    Long64_t event_number = reader.GetCurrentEntry();
    
    for(int imc = 0; imc<mc_status.GetSize(); imc++)
      {
	// genStatus 1: final state particle
        if( mc_status[imc] == 1 && mc_pid[imc] == pid )
	  {
	    nhadrons++;
	    double p = sqrt(mc_px[imc]*mc_px[imc] + mc_py[imc]*mc_py[imc] + mc_pz[imc]*mc_pz[imc]);
	    double pt = sqrt(mc_px[imc]*mc_px[imc] + mc_py[imc]*mc_py[imc]);
	    double mass = mc_mass[imc];
	    double e = sqrt(p*p + mass*mass);

	    TLorentzVector mc_part;
	    mc_part.SetPxPyPzE(mc_px[imc], mc_py[imc], mc_pz[imc], e);

	    double rapidity = mc_part.Eta();
	    if(abs(rapidity) < 1.1)
	      {
		naccept++;
		if(p < 0.5)
		  nlowp++;
	      }


	    h2->Fill(rapidity, p);
	    hpt->Fill(rapidity, pt);
          }
      }//mc loop
  }//event loop

  cout << nhadrons << " " << naccept << " " << double(naccept)/nhadrons << " " << double(nlowp)/naccept << endl;

  fout->cd();
  h2->Write();
  hpt->Write();
  fout->Close();

}

