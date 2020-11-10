# MNXB01Project
This repository's purpose is to contain the presentation project for the MNXB01 course.

In this folder are instructions to use the four student's different codes,
as discussed in the presentation.

As discussed, our codes are fragmented and therefore each student will
give instructions on how to use their code to reproduce their graphs.

------------------------------------------------------------------------

Tom's Code

Program 1: TTreeAnalyser.C

(1) Open Root

(2) .L TTreeAnalyser.C++

(3) This will compile the script. If it doesn't, you might be in the 
wrong directory. Change to ProgramsAndCode to make it simple.

(4) Once the code has compiled, use the function "PlotTempForFile()"

(5) You will be prompted for the file you wish to see all temperatures of.
Provided that a correct directory/file is given (see CleansedData for filenames)
it will then provide a histogram of all the temperatures, as well as the
mean and standard deviation. 

(6) You can reproduce the plot in the report by using the CleansedLuleaData.csv.

Program 2: WeatherAnalyser.C

Instructions are not provided, because this code was not used in the report
and cannot be used with the cleansed files due to the problems discussed
in the presentation.

------------------------------------------------------------------------

Sam's Code

Program 1: datacleaner.sh

(1) Find the 'datacleaner.sh' file within the ProgramsAndCode directory.

(2) Make sure the code is executable (though if everything is correct it 
should be anyway) 

(3) Run the code with raw data, to do this we run it normally but have to 
path to the RawData directory. An example is
./datacleaner.sh ../RawData/uppsala_tm_1722-2013.dat

(4) The code should then prompt the user whether or not they would like the
final form of the data in one file or two, one with date and time and the other
with the temperatures. The user should then answer (y/n).

(5) The code will then determine if the file is of the standard smhi format
or is in uppsala format. If in uppsala format it will change the format to standard
cleansed format. The file should read out basic steps it is taking in its procces.

(6) The code should now output file(s) the names of which it should the user.
The user should keep in mind that the output cleansed file will be in the same
directory as datacleaner.sh

Program 2: yearcompare.C 
This is just the first step of my analysis process where I wanted to be able
to visually compare two years temperatures built off an early version of Gustaf's
code.

*** important *** if at any stage Root does not compile, close Root and open again

(1) Open Root

(2) .L yearcompare.C++

(3) This should compile the script. After this occures in Root run
yearcompare()

(4) The user should be prompted by the code to imput the file that will be
used for analysis. Please note all the cleansed files are in the directory
CleansedData and are named after each town such as CleansedLundData.csv
and example input is.
../CleansedData/CleansedBorasData.csv

(5) The file will then ask for the first year you want to compare. Please be
aware that the library used does not take dates before 1996 and each file only
contains information upto a given year. The year must be given in the format
yyyy 

(6) It will then ask for the second date which has similar constraints to the first. 

(7) After both years have been entered the code will then create a graph to use
for visual analysis and tell the user which year is represented by which line.

Program 2: eventanalysis.C 
This end result of my analysis, this allows the user to put in the date of an event and
show how that event changed the air temperature in a specific location in the year in which
it occured

*** important *** if at any stage Root does not compile, close Root and open again

(1) Open Root

(2) .L eventanalysis.C++

(3) This should compile the script. After this occures in Root run
eventanlaysis()

(4) The user should be prompted by the code to imput the file that will be
used for analysis. Please note all the cleansed files are in the directory
CleansedData and are named after each town such as CleansedLundData.csv
and example input is.
../CleansedData/CleansedBorasData.csv

(5) The file will then ask for the year of the event you want to analyse. Please be
aware that the library used does not take dates before 1996 and each file only
contains information upto a given year. The year must be given in the format
yyyy 

(6) It will then ask for the month of the event which must be in the format mm and then ask for
the day of the event in the format dd. After this it will ask for the two years from which to average
the temperatures between. Again be mindful of the fact it will not accept dates before 1996
and after the last full year of data entries.

(7) After all infomation has been entered the code will then create a graph to use
for visual analysis and tell the user which line is the event year, which is the average
and which represents the date of the event one wants to visually analyse.

------------------------------------------------------------------------

Gustaf's Code

# Instuctions to run WeatherAnalyserWithChoice.C

(1) Navigate to the folder "ProgramsAndCode"

(2) Run Sam's ./datacleaner.sh to make sure the data is cleansed. Choose the option n when it asks if you want seperate files.

(2.1) Suggested to use "./datacleaner.sh ../RawData/CleansedKarlstadData2.csv" and "./datacleaner.sh ../RawData/CleansedSoderarm2.csv"

(3) Open root and run .L WeatherAnalyserWithChoice.C+

(4) run AnalyseWeather()

(5) when asked to give the name of the file you want to analyse, write: ../CleansedData/CleansedSoderarm.csv or similar depending on the city.

(6) You will be asked: "Type 0 to see the a timeline with all recorded temperatures from 1995
                        Type 1 to get a histogram for a given date"
(7) If you type 0 you will get a timeline of all recorded temperatures from and including 1995, but a very clotted graph, however if you if it you will get a slightly postivive slope likely due to global warming, however the choice of 0 is mainly a residue of the original intent of this file.

(8) If you choose 1 you will be asked to pick a month and date

(9) pick a month and date, for example 1 and then 1, for the first of january

(10) A histogram with the first recording of the temperature on that day each year will be shown

//with more time we would likely try to merge all code with this file so that you could make all choices here.

------------------------------------------------------------------------

Tim's Code

# Instructions to run "TempCompHist.C"

1. First navigate to the folder "ProgramsAndCode"

2. Open root and compile using .L TempCompHist.C

3. call the function TempCompHist(year1,year2,time,"place") in this you can specify which two years you would like to compare, the time and the place.

E.g "TempCompHist(1965,2005,18,"Lund")" would compare 1965 vs 2005 at time 18:00 in Lund.
