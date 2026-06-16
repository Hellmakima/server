#include <stdio.h>

int main(){
    FILE *file = fopen("text.txt", "r");
    if(file == NULL){
        printf("File not found\n");
        return 1;
    }
    char c;
    while((c = fgetc(file)) != EOF){
        printf("byte: %c\n", c);
    }
    fclose(file);
    return 0;
}