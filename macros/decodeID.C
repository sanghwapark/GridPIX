void decodeID(string fin)
{

  TFile *f = new TFile(fin.c_str());
  TTreeReader reader("events", f);
  TTreeReaderArray<int64_t> br_id(reader, "GridpixHits.cellID");
  TTreeReaderArray<double> br_x(reader, "GridpixHits.position.x");
  TTreeReaderArray<double> br_y(reader, "GridpixHits.position.y");

  while(reader.Next()) {
    Long64_t event_number = reader.GetCurrentEntry();
    Long64_t hits_count = br_id.GetSize();
    
    printf("Event# %lu Hits count %lu\n", event_number, hits_count);
    
    
    for(int hit_i = 0; hit_i < hits_count; hit_i++) {
        
      Long64_t id = br_id[hit_i];
      Long64_t sector_id = (id>>8)&0xFF;
      double x = br_x[hit_i];
      double y = br_y[hit_i];
        
      printf("   id=%-19lu sector_id=%-4lu hit_num=%-2d x=%-10f y=%-10f\n", id, sector_id, hit_i, x, y);
    }
  } 
}
