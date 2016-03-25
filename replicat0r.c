#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define TIMESTAMPSIZE 11 // 10 + room for a null

int main(int argc, char **argv)
{
    char timestamp[TIMESTAMPSIZE];
    snprintf(timestamp, TIMESTAMPSIZE, "%ld", time(NULL)); 

    char *filename = argv[0];
    char outfilename[TIMESTAMPSIZE];

    strncat(outfilename, timestamp, TIMESTAMPSIZE);
    printf("I am %s\n", filename);
    printf("Gonna write %s\n", outfilename);

    int fin = open(filename, O_RDONLY);
    int fout = open(outfilename, O_WRONLY|O_CREAT, 0755);
    printf("FOUT is %d\n", fout);

    ssize_t ret;
    ssize_t wret;
#define BUFSIZE 4096
    int buffer[BUFSIZE];
    while ( (ret = read(fin, buffer, BUFSIZE)) != 0 ) {
        wret = write(fout, buffer, BUFSIZE);
        if ( wret == -1)
            perror("bleurgh");
    }

    close(fin);
    close(fout);

    sleep(3);
    execl (outfilename, outfilename, NULL);
}
