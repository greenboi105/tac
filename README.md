# tac
A C program to reverse the lines in a text file.

cat is a common UNIX command that reads files sequentially and prints them out to the standard output. 

It is used via cat [options] [file names].

The assignment task was to create a C program to take a number of files via command line arguments, with the option of passing in no command line arguments in which case input would be read from stdin. The program will named tacmini as a reference to the command cat, which prints out the lines in normal order. 

Task establishes that the maximum length for a line from a given file is 255, so buffers involving reading lines will have a space of 255. 

Program accomplishes its task by reading in the lines from the file provided, using a buffer to store each line read in before assigning the buffer to the corresponding spot in a double pointer representing the entire file. 

Program reallocates memory whenever storage for additional lines is needed. 

Once the program no longer reads any lines from the file, it prints out the file line by line in reverse from the lines stored in the double pointer representing the entire file. 

Program performs garbage collection after the allocated memory has served its purpose. Pointers within the double pointer are first deallocated, before the overall double pointer is deallocated. 
