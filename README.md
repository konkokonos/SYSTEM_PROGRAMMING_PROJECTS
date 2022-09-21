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
When the application finishes processing the citizenRecordsFile, it will wait for input from the user from the keyboard. 
The user will be able to issue the following commands:
● /vaccineStatusBloom citizenID virusName
The application will check the bloom filter associated with virusName and print a message indicating whether the citizen with citizenID has received the vaccine against virusName. Output format: NOT VACCINATED OR MAYBE
● /exit
Exit the application. Make sure that we correctly release all the allocated memory.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Starting, our application should open the citizenRecordsFile to read one by one the lines and initialize and store in memory 
the data structures it will use during when executing queries. 
We should check that the data in the records is valid. For example, if in the citizenRecordsFile, there are two inconsistent records 
with the same citizenID, we should ignore the second record. Also, if we detect a record with a NO that has a date vaccination date, 
the record should be discarded. Incorrect records are ignored when reading the file by printing the message: ERROR IN RECORD theRecord 
where theRecord is the problematic record.

To better organize the application I have created a Makefile. All tables and structures have been dynamically bound by calling malloc or realloc.
The application has been broken into files:
1. main.c
Here is the main function of our application,in which we check for flags and the values of our parameters. 
Then I call the create_array_of_structs function which is found in the array_for_structs.c file,the create_array_of_virus_structs function and finally
the commands function. These functions are explained below.
2. array_for_structs
In this file an array is created from pointers to structs(records) using the create_record function found in the create_record.c file, which creates the
structs. More precisely, by taking a line by line of our record file with the records and calling create_record we create the pointer to struct eggrafi, then with the help of the elexos function we check if our struct is valid and can be put into our array ,and finally by calling insert_to_array_of_structs we put the index into the array. I have included an extra function print_array_of_structs for checking.
3. array_of_virus_structs
In this file we create an array of viruses structs. At the beginning we check if we have already created the struct with virus name itself. 
If yes,then we update the bloom_filter of the given virus. If not, we create a new virus struct and populate the empty bloom_filter. 
To create a new struct we call the create_virus function, the gemisma_tou_bloom_filter function to fill the bloom_filter, and to check the
elexos_for_new_virus. In gemisma_tou_bloom_filter we call the function pinakas_me_k_hash function of the hash_i.c file, 
which creates a table with the 16 positions by calling the ready-made hash_i function.
4. commands
Initially a message will be displayed to the user to give one of the valid commands. 
Otherwise, an error message will be displayed and the user will be given the option to command.

In case the user presses the /exit command the application will terminate.

In the case of /vaccineStatusBloom after the necessary checks are done,we check if in all positions of the bloom_filter is 1. 
If yes then the message MAYBE is displayed otherwise the message NOT VACCINATED. 
In case the virus we put does not exist it is printed message to reinsert command.
