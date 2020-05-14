#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 512
int main(int argc, char *argv[])
{
    FILE* f = fopen(argv[1], "r");
    int count = 0;
    int i = 0;
    unsigned char buffer[BUFFER_SIZE];
    char *name = "";
    while (fread(buffer, BUFFER_SIZE, 1, f) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            name =  (char*) malloc(3*(sizeof(int)));
            if(count >= 10)
            {
                strcat(name, "0");
            }else
            {
                strcat(name, "00");
            }
            sprintf(name, "%s%d.jpg", name, count);
            printf("%s\n", name);
            FILE* picture = fopen(name, "w");
            fwrite(&buffer, BUFFER_SIZE, 1, picture);
            fclose(picture);
            //printf("first byte = %x\n", (unsigned)first);
            free(name);
            count++;
        }
    }
    fclose(f);
}