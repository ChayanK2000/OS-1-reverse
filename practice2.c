#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    char *buffer = (char *)malloc(1000*sizeof(char));
    int fd = open("B.txt", O_RDONLY);
    int total_length = lseek(fd, 0, SEEK_END);
    printf("%d\n", total_length);
    int offset = lseek(fd, 0, SEEK_SET);
    if (read(fd, buffer,0)<0)
    {// print which type of error have in a code
    printf("Error Number % d\n", errno);

    // print program detail "Success or failure"
    perror("Program");
    }
    printf("%d %s\n", offset, buffer);
    return 0;
}