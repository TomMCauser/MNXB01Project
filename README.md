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

------------------------------------------------------------------------

Gustaf's Code

------------------------------------------------------------------------

Tim's Code

# Instructions to run "TempCompHist.C"

1. First navigate to the folder "ProgramsAndCode"

2. Open root and compile using .L TempCompHist.C

3. call the function TempCompHist(year1,year2,time,"place") in this you can specify which two years you would like to compare, the time and the place.

E.g "TempCompHist(1965,2005,18,"Lund")" would compare 1965 vs 2005 at time 18:00 in Lund.
