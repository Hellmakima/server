#include <stdio.h>

int main(){
    FILE *file = fopen("text.txt", "r");
    if(file == NULL){
        printf("File not found\n");
        return 1;
    }
    char buffer[8];
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        printf("byte: %s\n", buffer);
    }
    fclose(file);
    return 0;
}