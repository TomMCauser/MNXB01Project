#include <iostream>
#include <fstream>
#include <string>
#include <TH1.h> 
#include <TH2.h> 
#include <TCanvas.h> 
#include <TLatex.h>
#include <TSystem.h>
#include <TLegend.h>
#include <TGaxis.h>
#include <TGraph.h>

using namespace std;

void TempCompHist(Int_t year1, Int_t year2, Int_t hour, const char* place){

string fileName = Form("../CleansedData/Data%s.csv", place);

ifstream tempo(fileName);
tempo.close();
ifstream file(fileName);

TH1D *h1 = new TH1D("Data", Form("%s daily temp at %d:00 UTC in %d and %d; Day; Temperature [#circC]",place,hour,year1,year2), 
			366, 0, 366);
TH1D *h2 = new TH1D("h1", "h2", 366, 0, 366);

Int_t Year;
Int_t month;
Int_t day;
Int_t time;
Double_t temp;
Int_t dayno;

while (file >> Year >> month >> day >> time >> temp >> dayno){

	if (Year == year1 && time == hour) {
	
	h1->SetBinContent(dayno,temp); 
	}
	
	if (Year == year2 && time == hour) {
	
	h2->SetBinContent(dayno,temp); 
	}
	else {
	
	continue;
	} 
} 

file.close();

TCanvas* c1 = new TCanvas("c1", "histogram", 900, 600);
h1->SetLineColor(1);
h2->SetLineColor(2);

auto myfit1 = new TF1("myfit1","pol4");
auto myfit2 = new TF1("myfit2","pol4");
myfit1->SetLineColor(1);
myfit2->SetLineColor(2);

h1->Fit("myfit1");
h1->SetLineStyle(9);
h2->Fit("myfit2");
h2->SetLineStyle(9);

TLegend* legend = new TLegend(0.1,0.7,0.3,0.9,"Data Legend");
legend->AddEntry(h1,Form("Hist %d",year1),"l");
legend->AddEntry(h2,Form("Hist %d",year2),"l");
legend->AddEntry(myfit1,Form("Fit %d",year1),"l");
legend->AddEntry(myfit2,Form("Fit %d",year2),"l");

h1->Draw();
h2->Draw("same");
legend->Draw();

c1->SaveAs("hist.png");

}
