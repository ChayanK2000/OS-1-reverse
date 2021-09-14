#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    printf("%s %s\n", argv[0], argv[1]);
    int fd1, fd2, sz;
    // char *input_file = argv[1];
    // fd1 = open(input_file, O_RDONLY);
    char output_file[50] = "Assignment/1_";        //not writing any definite size causes stack smashing error...as with this line output file has allocated 2 char but after concat it has more and strcat doesnt check for array bounds...hence buffer overflow
    strcat(output_file, argv[1]);

    fd1 = open(argv[1], O_RDONLY);
    
    if (fd1 < 0)
    {
        // printf("error no is: %d\n", errno);
        sz = write(1, ("Error number: %d\n", errno),50);//how to write this
        if (sz == -1)
        {
            perror("yoyo");
        }
        perror("program");
    }
    char *content = (char *)malloc(10000 * sizeof(char));
    sz = read(fd1, content, 10000);//any other way?


    close(fd1);
    fd2 = open(output_file, O_RDWR | O_CREAT, 0664);
    sz = write(fd2, content, strlen(content));
    close(fd2);

    return 0;
}