#include <TString.h>
#include <TDatime.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TCanvas.h>

void dataplotter(const char *fin = "CleansedBorasData.txt") {
std::ifstream ifs(fin, std::ifstream::in);
 
TString ymd, hms;
Double_t v;

TGraph *g = new TGraph();

while(ifs >> ymd >> hms >> v)
{
//display output data
// std::cout << ymd << " " << hms << " " << v << std::endl;
TDatime t(ymd + " " + hms); // "yyyy-mm-dd hh:mm:ss"
g->SetPoint(g->GetN(), t.Convert(), v);
}

if (g->GetN() > 1) {
g->GetXaxis()->SetTimeDisplay(1);
g->GetXaxis()->SetTimeFormat("#splitline{%y-%m-%d}{%H:%M:%S}%F1970-01-01 00:00:00");
g->GetXaxis()->SetLabelOffset(0.025);
g->GetXaxis()->SetTitle("Time /yyyy-mm-dd hh:mm:ss");


g->GetYaxis()->SetTitle("Temperature /Degrees C");



TCanvas *c = new TCanvas("c", "c");
g->Draw("A*");
c->Modified(); c->Update();
}
}
