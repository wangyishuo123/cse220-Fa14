#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(void)
{
    FILE *stream;
    double a = 1234567.23456789, b = 4567890123.56789012;
    stream = fopen("a.txt", "w");//open the file, and just write in it.
    fprintf(stream, "%16.6f ", a);
    fprintf(stream, "%16.6f ", b);
    fclose(stream);
    
    stream = fopen("a.txt", "r");//open the file, and just read it.
    fscanf(stream, "%lf", &a);
    fscanf(stream, "%lf", &b);
    fclose(stream);
    printf("%f %f\n", a, b);
    return 0;

}

