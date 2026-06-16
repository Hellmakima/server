#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **get_lines(FILE *f)
// add a callback function for all the lines if needed,
// right now, im not clear on the requirements
{
    char **result = malloc(10 * sizeof(char *)); // assume 10 lines
    int result_index = 0;
    int line_length = 100;
    char* line = malloc(line_length*sizeof(char));
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
                if (line_length <= index + 1){
                    char* new_line = realloc(line, 2*line_length*sizeof(char));
                    if (new_line != NULL){
                        line = new_line;
                        line_length *= 2;
                    }
                    else {
                        perror("Failed to allocate buffer");
                    }
                }
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