We will write a bash script that creates a test input file that we will use to debug our program. Of course during the development of our program 
we can use a few small files to debug. The testFile.sh script works as follows:
./testFile.sh virusesFile countriesFile numLines duplicatesAllowed

virusesFile: a file with virus names (one per line)
countriesFile: a file with country names (one per line)
numLines: the number of lines that the file to be built will have
duplicatesAllowed: if 0, then the citizenIDs should be unique, otherwise duplicate citizenIDs are allowed.
The script does the following:
1. checks for input numbers
2. Reads the virusesFile and countriesFile files
3. Creates a file called inputFile and places numLines lines following the format of the input file described above. 
For citizenID we can create random numbers with a random length of 1 to 4 digits. 
For name and surname we can create random strings with random length from 3 to 12 characters. 
For country names the script will randomly select one of the countriesFile.
For age it will randomly select an integer in the range [1,120]. 
For virusNames, the script will randomly select one from virusesFile.
4. If the duplicatesAllowed flag is enabled, it should also create some (random) records with duplicate citizenIDs.

Specifically, 3 functions have been implemented and the main one part of the program:
1)get_random_line()
This function is used to select a random line from the files that are stored in the database containing the countries and viruses.
2)monadiko_id()
It is used to generate the unique id for each record
3)get_eggrafi()
Using the above two functions to get the id, country and virus we compose a record. 
For the first and last name we generate random strings with size 3 to 12. 
For the date we take the ready-made date.
For the age we choose a random one,as well as for the YES-NO.
Then in the main program we do some checks on the flags,if we have given the correct number of them,
whether we have put in the correct number of generated record-lines and
whether the value of dublicatedAllowed is equal to 0 or 1.
In the case of a value of 0 we simply call get_eggrafi(), while in the case of 1 we use its code, except that in each
record-line divided by 10 we put the id of its previous one,so that we have dublicate records.
