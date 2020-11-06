#include <iostream>
#include <fstream>
#include <string>
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TGraph.h>
#include <vector>
#include <TDatime.h>

using namespace std;

void Weather( const char* town) {
	// I will split the code into blocks, so that it is clear what each block of code is doing.
	
	// Block #1. 
	// The purpose of this code is to get the user to input the file they want to analyse,
	// and check that the file can be opened without problems.  
	string fileName = Form("../CleansedData/Cleansed%sData.csv", town);
	
	cout << "Checking that this file exists..." << endl; 
	fstream file( fileName.c_str( ) );
	while(!file.is_open())
	{
		cout << "File could not be opened. Here are three reasons why this might have happened. " << endl;
		cout << "(1) You've entered the wrong file name. " << endl;
		cout << "(2) This code is not in the same folder/directory as the file you're trying to open. " << endl;
		cout << "(3) Tom is bad at programming and the code is wrong, not you. " << endl;
		cout << "Try again" << endl;
		return;
	}
	cout << fileName << "Is opened " << endl;
	
	
	
	
	// Block #2. Splitting up the data into vectors
	string line;
	vector<string> dates;
	vector<string> time;
	vector<float> temp;
	//while splitting into date,time and temperature
	while(getline(file, line))
	{
		int space1 = line.find(' ');
		dates.push_back(line.substr(0,space1));
		int space2 = line.find(' ', space1+1);
		time.push_back(line.substr(space1+1,space2-space1));
		
		//temperature
		string temp_tmp = line.substr(space2+1);
		temp.push_back(stof(temp_tmp));
	}
	Int_t i = 0;
		
	int size = dates.size();

	vector<string> years;
	vector<string> months;
	vector<string> days;
	for(Int_t i=0; i<size; i++)
	{
		string datetmp = dates.at(i);
		years.push_back( datetmp.substr(0,4) );
		months.push_back( datetmp.substr(5,2) );
		days.push_back( datetmp.substr(8,2) );
	}
	
	//Setting up times
	vector<string> hh;
	vector<string> MM;
	vector<string> ss;
	for(Int_t i=0; i<size; i++)
	{
		string timetmp = time.at(i);
		hh.push_back( timetmp.substr(0,2) );
		MM.push_back( timetmp.substr(3,2) );
		ss.push_back( timetmp.substr(6,2) );
	}
	
	vector<vector <string>> data;
	data.push_back(years);
	data.push_back(months);
	data.push_back(days);
	data.push_back(hh);
	data.push_back(MM);
	data.push_back(ss);
	
	//cout << data[0][0] <<'-'<< data[1][0] << '-' << data[2][0] << ' ' << data[3][0]<<':'<< data[4][0] <<':'<< data[5][0] <<endl;
	
	//Now we make TDatime objects::
	
	float x[size];
	float y[size];
	for(Int_t i = 0; i<size; i++)
	{
		TDatime da_tmp(stoi(data[0][i]), stoi(data[1][i]), stoi(data[2][i]), stoi(data[3][i]), stoi(data[4][i]), stoi(data[5][i]));
		x[i] = da_tmp.Convert();
		y[i] = temp.at(i);
	}
	
	TGraph* myGraph = new TGraph(size,x,y);
	
	//myGraph->SetMarkerStyle(20);
	myGraph->Draw();
	myGraph->GetXaxis()->SetTimeDisplay(1);
	//myGraph->GetXaxis()->SetNdivisions(size);
	myGraph->GetXaxis()->SetTimeFormat("%Y-%m-%d");
	myGraph->GetXaxis()->SetTimeOffset(0,"gmt");
	//myGraph->SetTitle(Form("Temp. since 1995 per day in %s", town));
	myGraph->SetTitle((Form("Temp. 1995 - 2015 per day in %s; Time /y-m-d; Temperature [#circC]", town)));

	//Define fit function
	
	
	//TF1* fit1 = new TF1("fit1", "pol2",788905000,820451000);
	//TF1 *f1 = myGraph->GetListOfFunctions()->FindObject("pol2");
    //fit1->SetLineColor(4);
	//myGraph->Fit("pol2","V","E1",820451000,851997000);
	//myGraph->Fit("pol2","V","E1",851997000,883543000);
	//myGraph->Fit("pol2","V","E1",883543000,915089000);
	//myGraph->Fit(fit1)
	//rawdatafinal_smhi-opendata_Lund.csv

}
