#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 512 //Set the size of buffer to 512 bytes

int main(int argc, char *argv[])
{
    
    //Manage initializations
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)//Handles the exception : Bad source file
    {
        return 1;
    }
    FILE *picture = NULL;
    unsigned char buffer[BUFFER_SIZE];
    char *name = "";
    int name_count = 0;
    int picture_found = 0;
    
    //Processing
    while (fread(buffer, BUFFER_SIZE, 1, f) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (picture_found == 1)//Check if it's a picture (or the new picture for the other cases)
            {
                fclose(picture);
            }
            else
            {
                picture_found = 1;
            }
            
            //Manages the output file name
            name = (char *) malloc(3 * (sizeof(int)));
            if (name_count >= 10)
            {
                strcat(name, "0");
            }
            else
            {
                strcat(name, "00");
            }
            sprintf(name, "%s%d.jpg", name, name_count);
            picture = fopen(name, "w");
            free(name);
            name_count++;
        }
        
        if (picture_found == 1)//If there's a picture,write the recovered buffer into it
        {
            fwrite(&buffer, BUFFER_SIZE, 1, picture);
        }
    }
    
    //Manage return and closures
    fclose(picture);
    fclose(f);
    return 0;
}