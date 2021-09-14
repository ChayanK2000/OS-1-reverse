//reading char by char will generate many syscalls and slow computer...thus shud take atleast > 1KB or 1MB chunk size

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void reverse(long long int chunk_moving_length, char *chunk, char *chunk_copy, int fd2)
{
    //to reverse the chunk

    long long int i, j;
    for (i = 0, j = chunk_moving_length - 1; i < chunk_moving_length; i++, j--) //-1 to account for null char at last
    {
        chunk_copy[i] = chunk[j];
    }
    chunk_copy[i] = '\0'; //to add null at last
    write(fd2, chunk_copy, strlen(chunk_copy));
}

void print_progress(float progress,long long int total_length, long long int cur_offset, char *prog_output)
{
    progress = (float)((total_length - cur_offset) / (float)total_length) * 100;
    sprintf(prog_output, "\r%.2f%%", progress); 
    write(1, prog_output, strlen(prog_output));
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    int fd1, fd2, sz;
    // char *input_file = argv[1];
    // fd1 = open(input_file, O_RDONLY);
    char output_file[50] = "Assignment/1_"; //not writing any definite size causes stack smashing error...as with this line output file has allocated 2 char but after concat it has more and strcat doesnt check for array bounds...hence buffer overflow
    strcat(output_file, argv[1]);

    //to check is Assignment folder is present or not.
    struct stat buffer;
    int check_dir;
    if (stat("Assignment", &buffer) == -1)
    {
        mkdir("Assignment", 0775);
    }
    else
    { 
        check_dir = S_ISDIR(buffer.st_mode) ? 1 : 0;
        if (check_dir == 0)
        {
            mkdir("Assignment", 0775);
        }
    }

    //to open the files
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(output_file, O_CREAT | O_RDWR | O_TRUNC, 0664);

    if (fd1 < 0)
    {
        perror("Input file");
        return 1;
    }
    if (fd2 < 0)
    {
        perror("Output file");
        return 1;
    }

    long long int chunk_size = 5000000; // ~5MB chunk size
    long long int chunk_moving_length;
    long long int count = -1;
    float progress;
    char *chunk = (char *)malloc((chunk_size + 1) * sizeof(char));
    char *chunk_copy = (char *)malloc((chunk_size + 1) * sizeof(char));
    char *prog_output = (char *)malloc(100 * sizeof(char));
    long long int total_length = lseek(fd1, 0, SEEK_END);
    long long int cur_offset = total_length;
    while (1)
    {
        // printf("cur offset at starting of while loop is: %d\n", cur_offset);
        if (cur_offset <= chunk_size)
        {

            chunk_moving_length = cur_offset;
            cur_offset = lseek(fd1, 0, SEEK_SET);
            if(read(fd1, chunk, chunk_moving_length)<0)
            {
                perror("Error in reading");
                return 1;
            }

            reverse(chunk_moving_length, chunk, chunk_copy, fd2);
            print_progress(progress, total_length, cur_offset, prog_output);
            break;
        }
        else
        {
            chunk_moving_length = chunk_size;
            cur_offset = lseek(fd1, chunk_size * count, SEEK_END);
            if (cur_offset < 0) //essentially of no use
            {
                perror("Error in cur_offset");
                return 1;
            }
            if(read(fd1, chunk, chunk_moving_length)<0)
            {
                perror("Error in reading");
                return 1;
            }
            reverse(chunk_moving_length, chunk, chunk_copy, fd2);

            //to print progress
            print_progress(progress, total_length, cur_offset, prog_output);
            count--;
        }

        
    }

    write(1, "\nReversing task is completed!\n", 30);
    fflush(stdout);
    close(fd1);
    close(fd2);
    return 0;
}