The application will be called vaccineMonitor and will be used as follows:
./vaccineMonitor -c citizenRecordsFile -b bloomSize where:
- The bloomSize parameter specifies the size of the bloom filter in *bytes*. Indicative size of the bloom filter for the exercise data will be 
of the order of 100Kbytes.
- The citizenRecordsFile (or some other file name) is a file containing a set of citizen records to be processed. 
Each line of this file describes the status vaccination status of a citizen for a particular virus. 
For example, if the contents of the file
are:
889 John Papadopoulos Greece 52 COVID-19 YES 27-12-2020
889 John Papadopoulos Greece 52 H1N1 NO
776 Maria Tortellini Italy 36 SARS-1 NO
125 Jon Dupont USA 76 H1N1 YES 30-10-2020

means we have four records describing three citizens in three different countries (Greece, Italy, USA). 
YES indicates that the citizen has been vaccinated (on the date below) while NO indicates the opposite. 
Specifically, a record is a line of ASCII text consisting of the following elements in that order:
- citizenID: a string (may have a single digit) that identifies each such record.
- firstName: a string consisting of letters without spaces.
- lastName: a string consisting of letters without spaces.
- country: a string consisting of letters without spaces.
- age: a positive (>0), integer <= 120.
- virusName: a string consisting of letters, numbers, and possibly a a string, a number, a number of characters, a number of letters,  and possibly a hyphen "-" but without spaces.
- YES or NO: indicates whether the citizen has been vaccinated against the given virus.
- dateVaccinated: date the citizen was vaccinated. If the previous field is NO , no there is no dateVaccinated field in the record.

Starting, our application should open the citizenRecordsFile to read one by one the lines and initialize and store in memory 
the data structures it will use during when executing queries. 
We should check that the data in the records is valid. For example, if in the citizenRecordsFile, there are two inconsistent records 
with the same citizenID, we should ignore the second record. Also, if we detect a record with a NO that has a date vaccination date, 
the record should be discarded. Incorrect records are ignored when reading the file by printing the message: ERROR IN RECORD theRecord 
where theRecord is the problematic record.

