#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    FILE* f = fopen(argv[1], "rb");
    int first = fgetc(f);
    int count = 0;
    int sig1 = 0xff;
    int sig2 = 0xd8;
    int sig3 = 0xd9;
    int add1, add2;
    char *name = "";
    while ((first = fgetc(f)) != EOF)
    {
        if (first == 0xff && fgetc(f) == 0xd8 && fgetc(f) == 0xff)
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
            //printf("%s\n", name);
            FILE* picture = fopen(name, "w");
            fputc(sig1, picture);
            fputc(sig2, picture);
            fputc(sig1, picture);
            fputc(sig3, picture);
            while(!((add1 = fgetc(f)) == 0xff && (add2 = fgetc(f)) == 0xd9))
            {
                fputc(add1, picture);
                fputc(add2, picture);
            }
            fclose(picture);
            //printf("first byte = %x\n", (unsigned)first);
            free(name);
            count++;
        }
    }
    FILE* test = fopen("001.jpg", "r");
    while ((first = fgetc(test)) != EOF)
    {
         printf("first byte = %x\n", (unsigned)first);
    }
    /* TODO else read failed, empty file?? */
    fclose(test);
    fclose(f);
}