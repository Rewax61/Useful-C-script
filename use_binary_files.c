#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int i;
    FILE * fic = NULL;

    char tab[] = "Hello World!";
    char tab2[] = "Welcome";
    int taille = strlen(tab);
    int taille2 = strlen(tab2);

    fic = fopen("file.dat", "wb");
    if (fic == NULL) {
        fprintf(stderr, "Error: cannot open file\n");
        exit(EXIT_FAILURE);
    }
    
    fwrite(&taille, sizeof(int), 1, fic);
    fwrite(tab, sizeof(char), taille, fic);

    fwrite(&taille2, sizeof(int), 1, fic);
    fwrite(tab2, sizeof(char), taille2, fic);

    fclose(fic);


    FILE * file = fopen("file.dat", "rb");

    printf("Values :\n\n");

    /* Declaration of both size variable */
    int size;
    int size2;

    /* Get the size of the next string contained in the file*/
    fread(&size, sizeof(int), 1, file);
    char buffer[size];
    /* Get the first string */
    fread(buffer, sizeof(char), size, file);
    buffer[size] = '\0'; /* Size error management */


    /* Get the size of the next string contained in the file*/
    fread(&size2, sizeof(int), 1, file);
    char buffer2[size2];
    /* Get the second string */
    fread(buffer2, sizeof(char), size2, file);
    buffer2[size2] = '\0'; /* Size error management */


    /* Show both strings */
    printf("%s\n", buffer);
    printf("%s\n", buffer2);

    fclose(fic);

    return 0;
}