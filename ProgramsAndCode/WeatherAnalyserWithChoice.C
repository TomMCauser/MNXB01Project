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

void AnalyseWeather();

void AnalyseWeather() {
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
		//cout <<"hello"<< temp_tmp;
		temp.push_back( stof(temp_tmp) );
	}
		
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
	//Here we ask the user what data they want
	
	vector<float> x;
	vector<float> y;
	string tmp;
	Bool_t choice;
	string monthChoice;
	string dayChoice;
	cout << " Type 0 to see the a timeline with all recorded temperatures from 1995 \n Type 1 to get a histogram for a given date" << endl;
	cin >> tmp;
	if(tmp !="0" && tmp != "1")
	{
		cout <<"Error, you did not choose one of the appropriate choices" << endl;
		return;
	}
	else
	{
		choice = stoi(tmp);
	}
	
	if(choice == 1)
	{
		cout << "pick a month" << endl;
		cin >> monthChoice;
		cout << "pick a day" << endl;
		cin >> dayChoice;
		if(stoi(monthChoice) < 1 || stoi(monthChoice) >12)
		{
			cout << "Error, invalid month" << endl;
			return;
		}
		else if(stoi(dayChoice) < 1 || stoi(dayChoice) >31)
		{
			cout << "Error, invalid day" << endl;
			return;
		}
		//There can still be errors if you pick 31 on a day that doesnt have 31st or picking a late day in february
	}
	
	TH1D* hist = new TH1D("hist", "Temperature histogram for given date; Temperature C; Entries", 
							75, -35, 40);

	
	Int_t axissize = 0;
	Int_t old = 0;
	for(Int_t i = 0; i<size; i++)
	{
		
		Int_t Y = stoi(data[0][i]);
		Int_t M = stoi(data[1][i]);
		Int_t D = stoi(data[2][i]);
		Int_t h = stoi(data[3][i]);
		Int_t m = stoi(data[4][i]);
		Int_t s = stoi(data[5][i]);

		if (choice == 0)
		{
			if(Y >= 1995)
			{
				TDatime da_tmp(Y,M,D,h,m,s);
				x.push_back( da_tmp.Convert() );
				y.push_back( temp.at(i) );
				axissize++;	
			}
		}
		else if(choice == 1)
		{
			if(M==stoi(monthChoice) && D == stoi(dayChoice) && old != Y) //the last check is so that we don't take several temperatures from the same day into the histogram, instead we only take the first recording from each day
			{					
				hist->Fill(temp.at(i));
				old = Y;
			}
		}
	}	
	if(choice == 0)
	{
		float xaxis[axissize];
		float yaxis[axissize];
		//Filling arrays
		for(Int_t i = 0; i<axissize; i++)
		{
			xaxis[i] = x[i];
			yaxis[i] = y[i];
		}
		

		TGraph* myGraph = new TGraph(axissize,xaxis,yaxis);
		myGraph->SetMarkerStyle(1);
		myGraph->Draw();
		myGraph->GetXaxis()->SetTimeDisplay(1);
		//myGraph->GetXaxis()->SetNdivisions(size);
		myGraph->GetXaxis()->SetTimeFormat("%Y-%m-%d");
		myGraph->GetXaxis()->SetTimeOffset(0,"gmt");
	}
	else if(choice == 1)
	{
		hist->SetFillColor(kRed + 1);
		TCanvas* c1 = new TCanvas("c1", "temp on day", 900, 600);
		hist->GetXaxis()->CenterTitle(true);
		hist->GetYaxis()->CenterTitle(true);
		double mean = hist->GetMean(); //The mean of the distribution
		double stdev = hist->GetRMS(); //The standard deviation
		hist->Draw();

	}


}
/*
 * 
CleansedKarlstadData2.csv
CleansedLundData2.csv
CleansedSoderarm2.csv
* 
* */


