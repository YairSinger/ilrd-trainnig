#include <stdio.h>
#include <string.h>

void Swap(char *str, size_t first_i, size_t sec_i)
{
    char temp = str[first_i];
    str[first_i] = str[sec_i];
    str[sec_i] = temp;
}



void Permutations(char *str,size_t start_i)
{
    size_t runner = start_i;
    size_t len = strlen(str);

    if (len - 1 == start_i)
    {
        printf("%s\n", str);
    }

    while (runner <= len)
    {
       Swap(str, start_i, runner);
       Permutations(str, start_i + 1);
       Swap(str, start_i, runner);
       ++runner;
    }
}

void StringPermutations(char *str)
{
    Permutations(str, 0);
}

int main()
{
    char srt[] = {'A', 'B', 'C', 'D'};
    StringPermutations(srt);
    return 0;
}
