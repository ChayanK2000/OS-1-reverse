#include <stdio.h>

int main()
{
    char *test = (char *)malloc(100 * sizeof(char));
    test = "hiby";
    printf("%s %d", test, strlen(test));
    test = "ab";
    printf("%s %d", test, strlen(test));
    fflush(stdout);
}
