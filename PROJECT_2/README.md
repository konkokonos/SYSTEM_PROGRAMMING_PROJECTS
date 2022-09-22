The travelMonitor application will be used as follows:
./travelMonitor -m numMonitors -b bufferSize -s sizeOfBloom -i input_dir where:

The numMonitors parameter is the number of Monitor processes the application will create.  
The parameter bufferSize: is the buffer size for reading over pipes.  
The sizeOfBloom parameter specifies the size of the bloom filter in *bytes*. Indicative size of the bloom filter for the exercise data will be of the order of 100Kbytes. This parameter is of exactly the same logic as the corresponding parameter of the first task.  
The parameter input_dir: is a directory containing subdirectories with the files that will be processed by the Monitor processes. Each subdirectory will have the name of a country and will contain one or more files.
For example, input_dir could contain subdirectories China/ Italy/ and Germany/ which have the following files:

/input_dir/China/China-1.txt  
/input_dir/China/China-2.txt  
/input_dir/China/China-3.txt  

/input_dir/Italy/Italy-1.txt  
/input_dir/Italy/Italy-2.txt  

/input_dir/France/France-1.txt  
/input_dir/France/France-2.txt  
/input_dir/France/France-3.txt  

Each file contains a series of citizen records where each line will describe the citizen's vaccination status for a particular virus.
For example, if the contents of the file /input_dir/France/France-1.txt .txt are:  
889 John Papadopoulos France 52 COVID-19 YES 27-12-2020  
889 John Papadopoulos France 52 Η1Ν1 ΝΟ  
776 Maria Tortellini France 36 SARS-1 NO  
125 Jon Dupont France 76 H1N1 YES 30-10-2020  
means that in France we have a citizen (John Papadopoulos) who has been vaccinated for COVID-19 on 27-12-2020 but not for H1N1,
Maria Tortellini who has not yet been vaccinated for SARS-1, and Jon Dupont who was vaccinated for H1N1.
Similarly to the first exercise if there are any lines that are contradicting with previous ones, you can discard the records that create inconsistency
in the same way as in exercise 1.
Specifically, a record is a line of ASCII text that consists of the following elements with it in that order:
- citizenID: a string (can have a single digit) that specifies each such record.  
- firstName: a string consisting of letters without spaces.  
- lastName: a string consisting of letters without spaces.  
- age: a positive (>0), integer <= 120.  
- virusName: a string consisting of letters, numbers, and possibly a a string, a number, a number of characters, a number of letters, and possibly a  hyphen "-" but without spaces.  
- YES or NO: indicates whether the citizen has been vaccinated against the given virus.  
- dateVaccinated: date the citizen was vaccinated. If the previous field is NO , there is no dateVaccinated field in the record.  

To start, the travelMonitor application should create a number of named pipes for communication with numMonitors child processes that it will create. Then it should fork numMonitors child processes. Each child process, will call the exec with an executable program called Monitor that you will write, which will take as arguments the paths of the named pipes that used for communication between the original parent process travelMonitor and each exec'd
Monitor process.Then, the parent process will inform each Monitor via named pipe of the subdirectories that the Monitor will take over. The travelMonitors will be distributed evenly (with round-robin alphabetically) the subdirectories with the countries in the input_dir to the Monitor processes.
Assume that the subdirectories will be flat, that is, they will contain only files, not subdirectories.
When the application (the parent process) finishes its initialization actions, it will expect a series of bloom filters from the Monitor processes (see below) and when it has received all the information, it will be ready to accept input (commands) from the user from the keyboard (see below for commands).Each Monitor process, for each directory assigned to it, will read all its files and fill a series of data structures that it will use to answer queries forwarded to it.
One structure will be the bloom filter which, as in the first task, will be used for a quick check to see if a citizen (with citizenID) has been grafted for that particular virus. Each Monitor process, after it has finished reading the input files, will send via named pipe to the parent process a bloom filter for each virus representing the set of vaccinated of the countries managed by the Monitor process. The choice of the number of named pipes between
the parent process and the Monitor processes, as well as other data structures is up to you design choice. If during file reading, a Monitor process detects a problematic record (e.g. in syntax or an inconsistent record), it will ignore the problematic record.
When the Monitor process has finished reading its files and has sent all Bloom filters to the parent, it notifies the parent process via named pipe that it is ready for the Monitor to accept requests. If a Monitor process receives a SIGINT or SIGQUIT signal then it prints to a file named log_file.xxx
(where xxx is its process ID) with the name of the countries (subdirectories) it manages, the total number of requests it received for entry to the countries it manages, and the total number of requests approved and rejected.Logfile format:  
Italy  
China  
Germany  
TOTAL TRAVEL REQUESTS 29150  
ACCEPTED 25663  
REJECTED 3487  
If a Monitor process receives a SIGUSR1 signal, it means that 1 or more new files in any of the subdirectories assigned to it. We assume that no
new directories with countries and that existing files are not modified. So there will be only new files. The monitor process, will check the subdirectories to find the new files, will read and update the data structures it keeps in memory. After it has finished reading
the new files, it will send the updated bloom filters to the parent process. If a Monitor process suddenly terminates, the parent process should fork a new Monitor process to replace it. Therefore, the parent process should handle the SIGCHLD signal as as well as SIGINT and SIGQUIT.
If the parent process receives SIGINT or SIGQUIT, it must first finish processing the current command from the user and after it has responded to the user, it will send a SIGKILL signal to the Monitors, it will wait for them to finish, and finally print to a file named log_file.xxx where xxx
is its process ID, the name of all the countries (subdirectories) that participated in the application with data, the total number of requests it received for entry into the countries, and the total number of requests approved and denied.
Logfile format:  
Italy  
China  
Germany  
TOTAL TRAVEL REQUESTS 883832  
ACCEPTED 881818  
REJECTED 2014  

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
make  
./travelMonitor -m 4 -b 10000 -s 20000 -i input_dir  
To better organize the application I have created a Makefile. All tables and structures have been dynamically bound by calling malloc or realloc.
The application has been broken into files:  
1)travelMonitor.c  
Here is the main function of our application,in which we check for flags and the values of our parameters. Then we open the input_dir and with the help of the opendirectory function we get the names of the subdirectories and their number. Then I make a full path names table in which I have the paths in input_dir/country format. I create a table of fifos after creating them. With the help of fork() I make numMonitors Monitors and exec the file ./Monitor is made,where for each process-Monitor I pass as arguments the fifos it will need to communicate with its parent. Then I open my fifos for read and write and send each Monitor the subfolders it will need to open to get the txt files from which it will extract our records.(This part of the extraction is not implemented.).Then the fifos are unlinked.  
2)parent_child.h  
In this file are the functions of the father and each Monitor child,where the fifos are used so that the father can send the appropriate files to the correct child.The fifo f0 sends a string with two strings separated by # where you pass the buffsize kai to bloomsizeto the child from the father.  
3)Monitor.c  
In this file each Monitor takes the fifos assigned to it and opens them for either reading or writing.  
4)commands  
Initially a message will be shown to the user to give one of the valid commands. Otherwise, an error message will be displayed and the user will be given the option to command. In case the user presses the /exit command the application will terminate.

THE FOLLOWING LINKS ARE COPY-PASTE FROM PROJECT_1.  
5)array_for_structs  
In this file an array of pointers to structs(records) is created using the create_record function found in the create_record.c file, which creates the
structs. More precisely, by taking one line of our record file with the records and calling create_record we create the pointer to struct eggrafi, then 
with the help of the elexos function we check if our struct is valid and can be put into our array ,and finally by calling insert_to_array_of_structs we put the index into the array. I have included an extra function print_array_of_structs for checking.  
6)array_of_virus_structs  
In this file we create an array of viruses structs. At the beginning we check if we have already created the struct with virus name itself. If yes,then we update the bloom_filter of the given virus. If not, we create a new virus struct and populate the empty bloom_filter. To create a new struct we call the create_virus function,gemisma_tou_bloom_filter function to fill the bloom_filter, and to check the elexos_for_new_virus. In gemisma_tou_bloom_filter we call the function pinakas_me_k_hash function of the hash_i.c file, which creates a table with the 16 positions by calling the ready-made hash_i function.

!!!!!THis PROJECT is not yet finished!!!!!


