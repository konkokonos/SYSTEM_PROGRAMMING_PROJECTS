We will write a bash script that creates test subdirectories and input files that you will use for debugging our program. 
Of course, during the development of our program we can use a few small files to debug. The create_infiles.sh script works as follows:
./create_infiles.sh inputFile input_dir numFilesPerDirectory  
- inputFile: a file which has the same format as the citizenRecordsFile input file of first Project(PROJECT_1). 
- Recall the sample example we gave:  
889 John Papadopoulos Greece 52 COVID-19 YES 27-12-2020  
889 John Papadopoulos Greece 52 H1N1 NO  
776 Maria Tortellini Italy 36 SARS-1 NO  
125 Jon Dupont USA 76 H1N1 YES 30-10-2020  
- input_dir: the name of a directory where the subdirectories and input files will be placed  
- numFilesPerDirectory: the number of files to be created in each subdirectory  
The script does the following:  
1. It checks for input numbers.  
2. Creates a directory with a name given in the second argument input_dir . If the directory exists an error message is printed and it terminates.  
3. Reads the inputFile.  
4. Within the input_dir directory it creates subdirectories, one for each country name it locates within inputFile.  
5. In each subdirectory, creates numFilesPerDirectory files named country-n.txt where n is a positive integer. 
6. As it processes the inputFile it will locate all lines corresponding to a country and will allocate the round robin lines to the files named country-n.txt.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

The bash script has been successfully implemented, i.e. it creates a directory with the name given in the second argument input_dir.
If the directory exists an error message is printed and it terminates.
If not, it creates a directory with the name given in the second input_dir argument.
Then it reads the inputFile,within the input_dir directory it creates subdirectories, one for each country name that it locates within inputFile.
In each subdirectory, it creates numFilesPerDirectory files named country-n.txt where n is a positive integer.
As it processes the inputFile, it will identify all lines corresponding to a country and allocate the round robin lines to the files named country-n.txt.
