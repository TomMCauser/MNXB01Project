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

void eventanalysis();

void eventanalysis() {
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
		
	// this is all the input data we ask the user for
	int size = dates.size();
	cout << "please enter year of event for analysis" << endl ;
	string markyear;
	cin >> markyear;
	cout << "please enter month of event" << endl;
	string markmonth;
	cin >> markmonth;
	cout << "please enter day of event" << endl;
	string markday;
	cin >> markday;

	cout  << "please enter a start year for the span" << endl;
	string markyear2;
	cin >> markyear2;
	int my2 = stoi(markyear2);
	cout <<"please enter an end year for the span" <<endl;
	string markyear3;
	cin >> markyear3;
	int my3 = stoi(markyear3)	;
	
	//to prevent some breaks if the user enters a start year after the end year we switch variables
	
	if (my3 - my2 < 0)
	{
			cout << "Start year is after the end year, correcting" << endl;
			string markplace = markyear3;
			markyear3 = markyear2;
			markyear2 = markplace;
			int myplace = my3;
			my3 = my2;
			my2 = myplace;
	}
		
	// this is the span we will use or rather the numver of years we want
	int over = my3 - my2+1;
	// here we set up all the vectors we want to use
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
	vector<float> temps;
	vector<vector<float>> tempav;
	
	//This first double for loop we create all the temperature vectors for the different years
	
	for(Int_t k = 0; k<over;k++)
		{	
			int ne = my2 + k;
			string na = to_string(ne);
			temps.clear();
			
			for(Int_t i=0; i<size; i++)
			{
			string datetmp = dates.at(i);
			if (datetmp.substr(0,4) == na)
				{
				temps.push_back( temp.at(i));
				}	
			
			}
			tempav.push_back(temps);
		}	
	
	//This for loop deals with only geting data from the event year
	for(Int_t i=0; i<size; i++)
	{
		string datetmp = dates.at(i);
		

		if (datetmp.substr(0,4) == markyear)
		{
		
		years.push_back( datetmp.substr(0,4) );
		months.push_back( datetmp.substr(5,2) );
		days.push_back( datetmp.substr(8,2) );
		string timetmp = time.at(i);
		hh.push_back( timetmp.substr(0,2) );
		MM.push_back( timetmp.substr(3,2) );
		ss.push_back( timetmp.substr(6,2) );
		temp2.push_back( temp.at(i));
		}
	}
	int minsize = tempav[1].size();
	for( Int_t q=0; q<over;q++ ){
	int si = tempav[i].size();
	if (si  < minsize )
		{ minsize = si;
		}
	}
	vector<float> tempfin;
	//this for loop is what creates the vector of average temperatures
	float over1 = over;
	for (Int_t y=0;y<minsize;y++)
		{
			float sum = 0;
		for(Int_t u=0;u<over;u++)
		{
			sum = sum + tempav[u][y]; 
			
		}
		
		float aver = sum/over1;
		tempfin.push_back(aver);
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
	
	
	
	
	//Now we make TDatime objects::
	//This first part creates the x and y vectors for the event year
	
	float x[span];
	float y[span];
	for(Int_t i = 0; i<span; i++)
	{
		
		TDatime da_tmp(stoi(markyear), stoi(data[1][i]), stoi(data[2][i]), stoi(data[3][i]), stoi(data[4][i]), stoi(data[5][i]));
		x[i] = da_tmp.Convert();
		y[i] = temp2.at(i);
	}
	//This second part creats the x and y vectors for the average temperatures
	float x2[minsize];
	float y2[minsize];
	for(Int_t i = 0; i < minsize; i++)
	{
		TDatime da_tmp(stoi(markyear), stoi(data[1][i]), stoi(data[2][i]), stoi(data[3][i]), stoi(data[4][i]), stoi(data[5][i]));
		x2[i] = da_tmp.Convert();
		y2[i] = tempfin.at(i);
	}
	
	//This last part creates the marker line at the event date
	float x3[2];
	float y3[2];
	
	for (i=0;i<2;i++)
	{
	TDatime da_tmp(stoi(markyear), stoi(markmonth), stoi(markday), stoi(data[3][0]), stoi(data[4][0]), stoi(data[5][0]));
	x3[i] = da_tmp.Convert();
	}
	y3[0]= 30;
	y3[1]= -10;
	
	//Graph stuff
	
	TGraph* myGraph = new TGraph(span,x,y);
	TGraph* myGraph2 = new TGraph(span,x2,y2) ;
	TGraph* myGraph3 = new TGraph(2,x3,y3);
	myGraph->SetMarkerStyle(20);
	myGraph2->SetMarkerStyle(20);
	myGraph2->SetLineColor(2);
	myGraph3->SetLineColor(4);
	myGraph->SetTitle("Year to Average Comparison");
	myGraph->GetYaxis()->SetTitle("Air Temperature /Degrees C");
	myGraph->GetXaxis()->SetTitle("Date");
	myGraph->Draw("AC");
	myGraph2->Draw("C");
	myGraph3->Draw("C");
	
	
	myGraph->GetXaxis()->SetTimeDisplay(1);

	myGraph->GetXaxis()->SetTimeFormat("%Y-%m-%d");
	
	myGraph->GetXaxis()->SetTimeOffset(0,"gmt");
	cout << "The daily temperatures in year " << markyear << " are the black line, and the average daily temperatures between " << markyear2 << " and " << markyear3 << " are the red line and the blue line marks the date " << markyear << "-" << markmonth << "-" << markday << endl ;

}


