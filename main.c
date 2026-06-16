#include <stdio.h>
#include <string.h>

int main(){
    FILE *file = fopen("text.txt", "r");
    if(file == NULL){
        printf("File not found\n");
        return 1;
    }
    char line[100] = "";
    int index = 0;
    char buffer[8];
    size_t bytes_read;
    while((bytes_read = fread(buffer, 1, 8, file)) > 0){
        /*
        fread takes destination, size, count, source,
        returns no of things it read
        in this case we want to make sure we capture even if there is 1 byte left in file
        */
        // buffer[bytes_read] = '\0';
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                line[index] = '\0';
                printf("READ: %s\n", line);
                index = 0;
            } else {
                line[index] = buffer[i];
                index++;
            }
        }
    }
    if (strlen(line) > 0) {
        line[index] = '\0';
        printf("READ: %s\n", line);
    }
    fclose(file);
    return 0;
}