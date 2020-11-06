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

void yearcompare();

void yearcompare() {
	// I will split the code into blocks, so that it is clear what each block of code is doing.
	
	// Block #1. 
	// The purpose of this code is to get the user to input the file they want to analyse,
	// and check that the file can be opened without problems.  
	string fileName;
	cout << "Give the name of the file that you want to analyse." << endl;
	cin >> fileName;
	
	cout << "Checking that this file exists..." << endl; 
	fstream file( fileName.c_str( ) );
	while(!file.is_open())
	{
		cout << "File could not be opened. Here are three reasons why this might have happened. " << endl;
		cout << "(1) You've entered the wrong file name. " << endl;
		cout << "(2) This code is not in the same folder/directory as the file you're trying to open. " << endl;
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
	cout << "please enter year for analysis" << endl ;
	string markyear;
	cin >> markyear;
	cout  << "please enter year for comparison" << endl;
	string markyear2;
	cin >> markyear2;

	vector<string> years;
	vector<string> years2;
	vector<string> months;
	vector<string> days;
	vector<string> hh;
	vector<string> MM;
	vector<string> ss;
	vector<string> months2;
	vector<string> days2;
	vector<string> hh2;
	vector<string> MM2;
	vector<string> ss2;
	vector<float> temp2;
	vector<float> temp3;
	for(Int_t i=0; i<size; i++)
	{
		string datetmp = dates.at(i);
		//cout << datetmp.substr(0,4);
		if (datetmp.substr(0,4) == markyear)
		{
		//cout << "YES";
		years.push_back( datetmp.substr(0,4) );
		months.push_back( datetmp.substr(5,2) );
		days.push_back( datetmp.substr(8,2) );
		string timetmp = time.at(i);
		hh.push_back( timetmp.substr(0,2) );
		MM.push_back( timetmp.substr(3,2) );
		ss.push_back( timetmp.substr(6,2) );
		temp2.push_back( temp.at(i));
		}
		if (datetmp.substr(0,4) == markyear2)
		{
		//cout << "YES";
		years2.push_back( datetmp.substr(0,4) );
		months2.push_back( datetmp.substr(5,2) );
		days2.push_back( datetmp.substr(8,2) );
		string timetmp = time.at(i);
		hh2.push_back( timetmp.substr(0,2) );
		MM2.push_back( timetmp.substr(3,2) );
		ss2.push_back( timetmp.substr(6,2) );
		temp3.push_back( temp.at(i));
		}
	}
	
	
	
	//Setting up times
	
	int span = temp2.size();
	vector<vector <string>> data;
	data.push_back(years);
	data.push_back(months);
	data.push_back(days);
	data.push_back(hh);
	data.push_back(MM);
	data.push_back(ss);
	int span2 = temp3.size();
	vector<vector <string>> data2;
	data2.push_back(years2);
	data2.push_back(months2);
	data2.push_back(days2);
	data2.push_back(hh2);
	data2.push_back(MM2);
	data2.push_back(ss2);
	
	//cout << data[0][0] <<'-'<< data[1][0] << '-' << data[2][0] << ' ' << data[3][0]<<':'<< data[4][0] <<':'<< data[5][0] <<endl;
	
	//Now we make TDatime objects::
	
	float x[span];
	float y[span];
	for(Int_t i = 0; i<span; i++)
	{
		
		TDatime da_tmp(stoi(markyear), stoi(data[1][i]), stoi(data[2][i]), stoi(data[3][i]), stoi(data[4][i]), stoi(data[5][i]));
		x[i] = da_tmp.Convert();
		y[i] = temp2.at(i);
	}
	
	float x2[span2];
	float y2[span2];
	for(Int_t i = 0; i < span2; i++)
	{
		TDatime da_tmp(stoi(markyear), stoi(data2[1][i]), stoi(data2[2][i]), stoi(data2[3][i]), stoi(data2[4][i]), stoi(data2[5][i]));
		x2[i] = da_tmp.Convert();
		y2[i] = temp3.at(i);
	}
	
	
	TGraph* myGraph = new TGraph(span,x,y);
	TGraph* myGraph2 = new TGraph(span2,x2,y2) ;
	myGraph->SetMarkerStyle(20);
	myGraph2->SetMarkerStyle(20);
	myGraph2->SetLineColor(2);
	myGraph->SetTitle("Year comparision ");
	myGraph->GetYaxis()->SetTitle("Air Temperature /Degrees C");
	myGraph->GetXaxis()->SetTitle("Date");
	myGraph->Draw("AC");
	myGraph2->Draw("C");
	
	
	myGraph->GetXaxis()->SetTimeDisplay(1);
	//myGraph->GetXaxis()->SetNdivisions(size);
	myGraph->GetXaxis()->SetTimeFormat("%Y-%m-%d");
	
	myGraph->GetXaxis()->SetTimeOffset(0,"gmt");
	
	cout << "The year " << markyear << " is the black line, and year " << markyear2 << " is the red line" << endl;


}
//rawdatafinal_smhi-opendata_Lund.csv


