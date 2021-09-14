//reading char by char will generate many syscalls and slow computer...thus shud take atleast > 1KB or 1MB chunk size

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd1, fd2, sz;
    // char *input_file = argv[1];
    // fd1 = open(input_file, O_RDONLY);
    char output_file[50] = "Assignment/1_"; //not writing any definite size causes stack smashing error...as with this line output file has allocated 2 char but after concat it has more and strcat doesnt check for array bounds...hence buffer overflow
    strcat(output_file, argv[1]);

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(output_file, O_CREAT | O_RDWR | O_TRUNC, 0664);

    if (fd1 < 0)
    {
        // print which type of error have in a code
        printf("Error Number % d\n", errno);

        // print program detail "Success or failure"
        perror("Program");
    }
    if (fd2<0)
    {
        // print which type of error have in a code
        printf("Error Number % d\n", errno);

        // print program detail "Success or failure"
        perror("Program");
    }

    // int var = 0;
    // int offset;
    // int total_length = lseek(fd1, 0, SEEK_END); //this works!
    // var = total_length;
    // var -= 1;
    // while (1) 
    // {

        
    //     char atom;
    //     offset = lseek(fd1, var, SEEK_SET);
        
    //     read(fd1, &atom, 1);
    //     sz = write(fd2, &atom, 1);
    //     if (sz == -1)
    //     {
    //         // print which type of error have in a code
    //         printf("Error Number % d\n", errno);

    //         // print program detail "Success or failure"
    //         perror("Program");
    //     }
    //     // printf("%c", atom);

    //     if (offset == 0)
    //     {
    //         break;
    //     }
    //     var--;
    // }


//-------------
    int chunk_size = 10;
    int total_length = lseek(fd1, 0, SEEK_END);
    
    char *chunk = (char *)malloc((chunk_size+1) * sizeof(char));
    char *chunk_copy = (char *)malloc((chunk_size+1) * sizeof(char));

    int count = -1;
    int last_offset = total_length, cur_offset;
    while (1)
    {
        
        if (last_offset < chunk_size)
        {
            lseek(fd1, 0, SEEK_SET);
            read(fd1, chunk, last_offset);
            //now to reverse the chunk
            int i, j;
            for (i = 0, j = strlen(chunk) - 1; i < strlen(chunk) - 1; i++, j--) //-1 to account for null char at last
            {
                chunk_copy[i] = chunk[j];
            }
            chunk_copy[i] = '\0'; //to add null at last
            
            write(fd2, chunk_copy, strlen(chunk_copy));
            break;
        }

        cur_offset = lseek(fd1, count * chunk_size, SEEK_END);
        if (cur_offset < 0)
        {
            break;
        }
        

        read(fd1, chunk, chunk_size);
        
        last_offset = lseek(fd1, 0, SEEK_CUR);
        
        //now to revrse the chunk
        int i, j;
        for (i = 0, j = strlen(chunk) - 1; i < strlen(chunk); i++, j--) //-1 to account for null char at last
        {
            chunk_copy[i] = chunk[j];
        }
        chunk_copy[i] = '\0'; //toadd null at last
        
        write(fd2, chunk_copy, strlen(chunk_copy));

        count--;
    }

    close(fd1);
    close(fd2);
    return 0;
}