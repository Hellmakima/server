#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **get_lines(FILE *f)
{
    char **result = malloc(10 * sizeof(char *)); // assume 10 lines
    int result_index = 0;
    char line[100] = "";
    /*
    If a line is longer than 99 chars, will write past memory.
    use realloc() later as requierd.
    */
    int index = 0;
    char buffer[8];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, 8, f)) > 0)
    {
        for (int i = 0; i < bytes_read; i++)
        {
            if (buffer[i] == '\n')
            {
                line[index] = '\0';

                result[result_index] = malloc(sizeof(char) * index);
                strcpy(result[result_index], line);

                result_index++;
                index = 0;
            }
            else
            {
                line[index++] = buffer[i];
            }
        }
    }
    if (strlen(line) > 0)
    {
        line[index] = '\0';

        result[result_index] = malloc(sizeof(char) * index);
        strcpy(result[result_index], line);

        result[result_index + 1] = NULL;
    }
    return result;
}

int main()
{
    FILE *file = fopen("text.txt", "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    char **lines = get_lines(file);
    fclose(file);

    for (int i = 0; lines[i] != NULL; i++)
    {
        printf("%s\n", lines[i]);
    }

    return 0;
}