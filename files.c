#include <stdio.h>
#include "files.h"

/*
    save text to file
*/
int save_to_file(char * path,char * output)
{
    FILE *file = fopen("example.txt", "w");
    
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;  
    }
    
    fprintf(file, output);
    fprintf(file, "\n");
    
    fclose(file);
    
    return 0;
}
