#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Task is to take in file names and print their contents in reverse order 
// No helper functions are needed for this assignment 
// Program contains two very similar blocks, one for if no additional command-line arguments are provided and another for if parameters are provided 

// we know that the maximum line length is 255 as stated 
#define MAXLINES 255

// main function with program instructions 
int main(int argc, char ** argv)
{   
    // declare the necessary variables we need here
    // character array of the maximum length
    char lines[MAXLINES]; 
    
    // double pointer to store the whole file
    char **whole_file; 
    
    // size the current number of lines available 
    int size = 0;
    
    // element is an indicator variable for when additional space needs to be added for more lines 
    int element = 0;
    int i, j;
    
    // a file pointer for reading information from the file arguments 
    FILE *file;
    
    // error checking
    if (argc == 2 && !strcmp(argv[1], "-h")) {
        exit(EXIT_FAILURE);
    }

    // if no file is passed in, take input from the standard input
    if (argc == 1)
    {
        // the number of lines available initially is 1
        size = 1;
        
        // allocate memory the size of one character pointer initially
        // pointer is stored within the double pointer whole_file 
        whole_file = malloc(sizeof(char *)); 
        
        // running counter to determine if additional space needs to be allocated via realloc 
        element = 0;
        
        // read in lines from stdin so long as there is something to read 
        while (fgets(lines, MAXLINES, stdin) != NULL) { 
             
            // determine if additional space is needed 
            if (element >= size) {
                
                // increment our size variable
                size++; 
                
                // increase the size of our entire file storage when necessary via realloc
                whole_file = realloc(whole_file, sizeof(char *) * (size + 1)); 
                if (!whole_file) // error checking for realloc
                    return -1;
            }
            
            // assign the lines read to the corresponding spot of the whole file 
            whole_file[element] = strdup(lines); 
            
            // increment our running storage tracker 
            element++; 
        }
        
        // print out the lines of the whole file in reverse order 
        for (j = 0; j < element; j++)
            // formatted output for string 
            printf("%s", whole_file[element-j-1]);
        
        //free the lines of the file
        for (j = 0; j < element; j++)
            free(whole_file[j]);

        //free the whole file
        free(whole_file);

    }
    
    // alternative option if command line arguments in the form of file names are provided 
    // concept is almost identical here, but we read the lines from the files provided via command line arguments
    for (i = argc-1; i > 0; i--) {
        
        size = 1;
        whole_file = malloc(sizeof(char *));
        element = 0;

        // open the corresponding command line file and generate a file stream for each file we want to print out reversed 
        if ((file = fopen(argv[i], "r")) == NULL) {
            exit(EXIT_FAILURE);

        } else {
            
            // read the lines from the file stream into the buffer lines 
            // this loop continues so long as there is something to get 
            while (fgets(lines, MAXLINES, file) != NULL) { 
                
                // determining if additional space is needed 
                if (element>= size) {
                    size++;
                    whole_file = realloc(whole_file, sizeof(char *) * (size + 1));
                    if (!whole_file)
                        return -1;
                }
                
                // storing lines sequentially 
                whole_file[element] = strdup(lines);
                element++;
            }

            fclose(file); // close the file pointer, as it no longer needed 

            // print our entire file in reverse
            for (j = 0; j < element; j++)
                printf("%s", whole_file[element-j-1]);
            
            for (j = 0; j < element; j++)
                free(whole_file[j]);

            free(whole_file);
        }
    }

    return 0;
}
