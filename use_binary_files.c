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

    /* Déclaration des deux varibles de taille */
    int size;
    int size2;

    /* Récupération de la taille da la prochaine chaine contenu dans le fichier */
    fread(&size, sizeof(int), 1, file);
    char buffer[size];
    /* Récupération de la 1ère chaine */
    fread(buffer, sizeof(char), size, file);
    buffer[size] = '\0'; /* Gestion de l'erreur de taille */


    /* Récupération de la taille da la prochaine chaine contenu dans le fichier */
    fread(&size2, sizeof(int), 1, file);
    char buffer2[size2];
    /* Récupération de la 2e chaine */
    fread(buffer2, sizeof(char), size2, file);
    buffer2[size2] = '\0'; /* Gestion de l'erreur de taille */


    /* Affichage des deux chaines */
    printf("%s\n", buffer);
    printf("%s\n", buffer2);

    fclose(fic);

    return 0;
}