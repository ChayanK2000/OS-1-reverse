#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void get_permissions(struct stat buffer, char *filename, char *check, char * msg)
{
    

    if (stat(filename, &buffer)== -1)
    {
        perror("\nError ");
        return;
    }
    // printf("File Type: \n");
    // switch (buffer.st_mode & S_IFMT)
    // {
    // case S_IFBLK:
    //     printf("block device\n");
    //     break;
    // case S_IFCHR:
    //     printf("character device\n");
    //     break;
    // case S_IFDIR:
    //     printf("directory\n");
    //     break;
    // case S_IFIFO:
    //     printf("FIFO/pipe\n");
    //     break;
    // case S_IFLNK:
    //     printf("symlink\n");
    //     break;
    // case S_IFREG:
    //     printf("regular file\n");
    //     break;
    // case S_IFSOCK:
    //     printf("socket\n");
    //     break;
    // default:
    //     printf("unknown?\n");
    //     break;
    // }
    // printf("Mode:                     %lo(octal)\n",
    //        (unsigned long)buffer.st_mode);

    // if (S_ISREG(buffer.st_mode))
    // {
    //     printf("it is a reg file...using th e other way\n");
    // }
    // if (S_ISDIR(buffer.st_mode))
    // {
    //     printf("it is a directory by other way\n");
    // }

//-------------------------

    check = (buffer.st_mode & S_IRUSR) ? "Yes" : "No";
    sprintf(msg, "\nUser has read permission on %s: %s\n",filename, check);
    write(1, msg, strlen(msg));
    check = (buffer.st_mode & S_IWUSR) ? "Yes" : "No";
    sprintf(msg, "User has write permission on %s: %s\n", filename, check);
    write(1, msg, strlen(msg));
    check = (buffer.st_mode & S_IXUSR) ? "Yes" : "No";
    sprintf(msg, "User has execute permission on %s: %s\n\n", filename, check);
    write(1, msg, strlen(msg));
    check = (buffer.st_mode & S_IRGRP) ? "Yes" : "No";
    sprintf(msg, "Group has read permission on %s: %s\n", filename, check);
    write(1, msg, strlen(msg));
    check = (buffer.st_mode & S_IWGRP) ? "Yes" : "No";
    sprintf(msg, "Group has write permission on %s: %s\n", filename, check);
    write(1, msg, strlen(msg));
    check = (buffer.st_mode & S_IXGRP) ? "Yes" : "No";
    sprintf(msg, "Group has execute permission on %s: %s\n\n", filename, check);
    write(1, msg, strlen(msg));
    check = (buffer.st_mode & S_IROTH) ? "Yes" : "No";
    sprintf(msg, "Others has read permission on %s: %s\n", filename, check);
    write(1, msg, strlen(msg));
    check = (buffer.st_mode & S_IWOTH) ? "Yes" : "No";
    sprintf(msg, "Others has write permission on %s: %s\n", filename, check);
    write(1, msg, strlen(msg));
    check = (buffer.st_mode & S_IXOTH) ? "Yes" : "No";
    sprintf(msg, "Others has execute permission on %s: %s\n", filename, check);
    write(1, msg, strlen(msg));
    fflush(stdout);
}
int main(int argc, char *argv[])
{
    struct stat buffer;
    char *check= (char *)malloc(5 * sizeof(char));
    char *msg = (char *)malloc(1000 * sizeof(char));
    // if (stat("Assignment", &buffer) == -1)
    // {
    //     perror("");
    // }
    stat("Assignment", &buffer);
    check = S_ISDIR(buffer.st_mode) ? "Yes" : "No";
    sprintf(msg, "Directory is created: %s\n", check);
    write(1, msg, strlen(msg));
    fflush(stdout);

    char output_file1[50] = "Assignment/1_"; //not writing any definite size causes stack smashing error...as with this line output file has allocated 2 char but after concat it has more and strcat doesnt check for array bounds...hence buffer overflow
    strcat(output_file1, argv[1]);

    char output_file2[50] = "Assignment/2_"; //not writing any definite size causes stack smashing error...as with this line output file has allocated 2 char but after concat it has more and strcat doesnt check for array bounds...hence buffer overflow
    strcat(output_file2, argv[1]);

    char output_file3[50] = "Assignment/"; //not writing any definite size causes stack smashing error...as with this line output file has allocated 2 char but after concat it has more and strcat doesnt check for array bounds...hence buffer overflow

    get_permissions(buffer, output_file1, check, msg);
    get_permissions(buffer, output_file2, check, msg);
    get_permissions(buffer, output_file3, check, msg);

    return 0;
    }