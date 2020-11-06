#!/bin/bash

SMHIINPUT=$1

if [[ $# -lt 1 ]]; then
   echo "Missing input file parameter, exiting"
   exit 1;
fi

DATAFILE=$(basename $SMHIINPUT)

[[ -e ${DATAFILE} ]]
status=$?
if [[ $status != 0 ]]; then
   echo "Error finding file, please check syntax and location, exiting"
   exit 1;
fi

echo "Would you like datetimes and temperatures in two separate files?(y/n)"
read ANS
 
echo "Finding the first line containing 'Datum'..."
STARTLINE=$(grep -n "Datum" ${DATAFILE} | cut -f1 -d:)

STARTLINE=$(( $STARTLINE + 1 ))



if [[ $STARTLINE == 1 ]]; then
	
	echo "'Datum' was not found this is the Uppsala file"
	
	echo "Turning time format into standard, resulting in rawdata_${DATAFILE}"
	sed  's/  */-/' ${DATAFILE} > rawdata_${DATAFILE}
	sed -i 's/  */-/' rawdata_${DATAFILE}
	
	echo "As time of day is not given we assume it to be 00:00:00 for convenience and to fit with existing data"
	sed -i 's/  */ 00:00:00 /' rawdata_${DATAFILE}
	
	echo "Selecting only relevant columns and copying to new file rawdatafinal_${DATAFILE}"
	cut -d " " -f 1-3 rawdata_${DATAFILE} > rawdatafinal_${DATAFILE}

else
	
	
	echo "Datum found, removing the first $STARTLINE lines and copying to new file rawdata_${DATAFILE} "
	tail -n +$STARTLINE ${DATAFILE} > rawdata_${DATAFILE}

	echo "Selecting only relevant columns and copying to new file"
	cut -d ";" -f 1-3 rawdata_${DATAFILE} > rawdatanext_${DATAFILE}
	echo "Deleteing rawdata_${DATAFILE}"
	rm rawdata_${DATAFILE}

	echo "Substituting the ; with spaces, result in a final rawdatafinal_${DATAFILE}"
	sed 's/;/ /g' rawdatanext_${DATAFILE} > rawdatafinal_${DATAFILE}
	rm rawdatanext_${DATAFILE}

fi
if [[ $ANS == "y" ]]; then
	echo "Now splitting original file rawdatafinal_${DATAFILE} into two files with date time (rawdatafinaldate_${DATAFILE}) and temperature (rawdatafinaltemp_${DATAFILE})"
	cut -d " " -f 1-2 rawdatafinal_${DATAFILE} > rawdatafinaldate_${DATAFILE}
	cut -d " " -f 3 rawdatafinal_${DATAFILE} > rawdatafinaltemp_${DATAFILE}
	rm rawdatafinal_${DATAFILE} 
	exit 0;
else
	exit 0;
fi

