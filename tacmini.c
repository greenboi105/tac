#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// we know that the maximum line length is 255
#define MAXLINES 255

int main(int argc, char ** argv)
{   
    // declare the necessary variables we need here
    char lines[MAXLINES]; // character array of the maximum length
    char **whole_file; // double pointer to store the whole file
    int size = 0;
    int element = 0;
    int i, j;
    FILE *file;
    
    // error checking
    if (argc == 2 && !strcmp(argv[1], "-h")) {
        exit(EXIT_FAILURE);
    }

    // if no file is passed in, take input from the standard input
    if (argc == 1)
    {
        size = 1;
        whole_file = malloc(sizeof(char *)); // allocate memory the size of one character pointer initially
        element = 0;

        while (fgets(lines, MAXLINES, stdin) != NULL) { // continue to go through the lines so long as there is something to read

            if (element >= size) {
                size++; // increment our size variable
                whole_file = realloc(whole_file, sizeof(char *) * (size + 1)); // increase the size of our entire file storage when necessary via realloc
                if (!whole_file) // error checking for realloc
                    return -1;
            }

            whole_file[element] = strdup(lines); // assign the lines read to the corresponding spot of the whole file 
            element++; // read the next line in
        }
        
        //print out the lines of the whole file in reverse order
        for (j = 0; j < element; j++)
            printf("%s", whole_file[element-j-1]);
        
        //free the lines of the file
        for (j = 0; j < element; j++)
            free(whole_file[j]);

        //free the whole file
        free(whole_file);

    }
    
    // concept is almost identical here, but we read the lines from the files provided via command line arguments
    for (i = argc-1; i > 0; i--) {
        size = 1;
        whole_file = malloc(sizeof(char *));
        element = 0;

        // open the corresponding command line file and generate a file stream
        if ((file = fopen(argv[i], "r")) == NULL) {
            exit(EXIT_FAILURE);

        } else {

            while (fgets(lines, MAXLINES, file) != NULL) { // read the lines into the line buffer

                if (element>= size) {
                    size++;
                    whole_file = realloc(whole_file, sizeof(char *) * (size + 1));
                    if (!whole_file)
                        return -1;
                }
                whole_file[element] = strdup(lines);
                element++;
            }

            fclose(file); // close the file pointer

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
