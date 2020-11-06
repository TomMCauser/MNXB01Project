#include <iostream>
#include <fstream>
#include <string>
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <vector>
#include <TGraphPainter.h>
#include <TGraph.h>
#include <TFile.h>
#include <TTree.h>

using namespace std;

void PlotTempForFile()
	{
		string FileName;
		fstream file;
		cout << "Enter file name (if not in the same location, write path and filename)." << endl;
		cout << "As an example, \"../CleansedData/CleansedLundData.csv\" (not including speech marks) will plot the Lund data." << endl;
		cout << "Desired file name: ";
		cin >> FileName;
			
		file.open( FileName.c_str() , ios::in);
		int YYYY, MM, DD, hh, mm, ss;
		double Temp;
		char t, f;
		
		TFile *output = new TFile("Test.root", "RECREATE");
		
		TTree *tree = new TTree("tree", "tree");
		
		tree->Branch("YYYY", &YYYY, "YYYY/I");
		tree->Branch("MM", &MM, "MM/I");
		tree->Branch("DD", &DD, "DD/I");
		tree->Branch("mm", &mm, "mm/I");
		tree->Branch("hh", &hh, "hh/I");
		tree->Branch("ss", &ss, "ss/I");
		tree->Branch("Temp", &Temp, "Temp/D");
				
		while (1)
			{
				file >> YYYY >> t >> MM >> t >> DD >> hh >> f >> mm >> f >> ss >> Temp;
				if(file.eof()) break;
				//cout << YYYY << t << MM << t << DD << " " << hh << ":" << mm << ":" << ss << " " << Temp << endl;
				tree->Fill();		
			}
		
		tree->Draw("Temp");
			
		output->Write();
		output->Close();		
		file.close();		
	}
