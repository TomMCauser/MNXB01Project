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

// I am unfortunately retiring this code because it isn't suitable for what
// I wanted to use it for. The idea was to create a "central program", however
// this failed in light of the fact that TH1 does not accept files as direct inputs.
// I should have checked this beforehand, however lesson learned!
//
// - Tom

using namespace std;

string ColumnCreator(int desiredColumnA, int desiredColumnB, int numberOfColumns)
	// This is a function used inside the "main" function, which is AnalyseWeather
	// In essence, this entire function exists to allow the user to choose which columns they plot.
	// It creates a string which feeds into the Root plotter. 
	{
		string emptyColumnString = "";
		for (int k = 0; k < numberOfColumns; k++)
			{
				if (k == desiredColumnA || k == desiredColumnB)
					{
						emptyColumnString += "%lg ";
					}
				else
					{
						emptyColumnString += "%*lg ";
					}
			}
		int stringLength = emptyColumnString.size();
		emptyColumnString = emptyColumnString.substr(0, stringLength - 1);
		//cout << emptyColumnString << endl;
		return emptyColumnString;
	}
	
int positionFinder(vector<string> sampleVector, string desiredString)
	// I spent an hour or so trying to find a function that could easily do this
	// like in Python, but just ended up giving up and writing it instead.
	{
		int vectorLength = sampleVector.size();
		int Position = -1;
		for (int position = 0; position < vectorLength; position++)
			{
				if (desiredString == sampleVector[position])
					{
						Position = position;
					}
			}
		return Position;
	}

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
	fstream file( fileName.c_str( ) ); // This solves a problem where the code wasn't compiling the string entered by the user.
	if (!file)
		{
			cout << "File could not be opened. Here are three reasons why this might have happened. " << endl;
			cout << "(1) You've entered the wrong file name. " << endl;
			cout << "(2) This code is not in the same folder/directory as the file you're trying to open. " << endl;
			cout << "(3) Tom is bad at programming and the code is wrong, not you. " << endl;
			return;
		}
	else
		{
			cout << "File found." << endl;
		}
	cout << "Opening " << fileName << "... " << endl;
	
	// Block #2.
	// The purpose of this section is to get the names of the column names of the files, so that the
	// user can later choose which columns they want to plot against each other.
	
	string firstLine;
	getline(file, firstLine);
	int firstLineLength = firstLine.size();
	cout << "The columns on this file appear to be... " << firstLine << endl; 
	vector<string> allColumnNames; // This vector (like a list in Python) will contain all the column names
	string Delimiter = " ";
	string helpString = firstLine;
	string columnName;
	int helpStringSize = helpString.size();
	int delimPosition = 0;
	while (delimPosition != -1) // In pseudocode, "while the delimiter can be found in the string, continue doing the while loop".
		{
			delimPosition = helpString.find(Delimiter);
			columnName = helpString.substr(0, delimPosition);
			// cout << columnName << endl;
			allColumnNames.push_back(columnName);
			helpString = helpString.substr(delimPosition+1, helpStringSize);	
			helpStringSize = helpString.size();
		}
	
	// Block #3.
	// The purpose of this section will be to use the headers found in the previous section
	// to allow the user to plot whatever they want. 
	
	cout << "Please enter the variable that you would like to put on the X axis. (cAsE sEnSiTiVe)" << endl;
	cout << "X Axis Variable: ";
	string graphColumn1;
	cin >> graphColumn1;
	int XcolumnVerifier = -1;
	while (XcolumnVerifier == -1)
		{
			while (positionFinder(allColumnNames, graphColumn1) == -1)
				{
					cout << "Your X axis column name does not exist. Please re-enter it. (cAsE sEnSiTiVe): ";
					cin >> graphColumn1;
				}
			cout << "Column with name \"" << graphColumn1 << "\" has been assigned to X axis." << endl;
			XcolumnVerifier = 0;
		}
		
	cout << "Now, select the variable that you would like to put on the Y axis. (cAsE sEnSiTiVe)" << endl;
	cout << "Y Axis Variable: ";
	string graphColumn2;
	cin >> graphColumn2;
	int YcolumnVerifier = -1;
	while (YcolumnVerifier == -1)
		{
			while (positionFinder(allColumnNames, graphColumn2) == -1)
				{
					cout << "Your Y axis column name does not exist. Please re-enter it. (cAsE sEnSiTiVe): ";
					cin >> graphColumn2;
				}
			cout << "Column with name \"" << graphColumn2 << "\" has been assigned to Y axis." << endl;
			YcolumnVerifier = 0;
		}
	
	int numberOfColumns = allColumnNames.size();
	int firstChoice = positionFinder(allColumnNames, graphColumn1);
	int secondChoice = positionFinder(allColumnNames, graphColumn2);
	string columnChoices = ColumnCreator(firstChoice, secondChoice, numberOfColumns);
	
	// Block #4.
	// Now that the user has chosen the columns they want to plot, we plot them. 
	
	
	
	TGraph* ChosenGraph = new TGraph(fileName.c_str(), columnChoices.c_str());
	ChosenGraph->Draw();
	
	
	
	

	file.close();
}


