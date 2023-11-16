#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>
#include "cJSON.h"

#define MAX_CMD_SIZE 100

FILE * jsonfile_write = NULL;

void quit_with_error(char *message);
void visual();
void test_command(char *command);
static size_t write_curl_data(void *ptr, size_t size, size_t nmemb);
void init();

int main(int argc, char **argv)
{
    (void) argv[0][0];
    if (argc < 2)
        quit_with_error("Incorrect number of arguments");

    init();
    
    if (! strcmp(argv[1], "--visual") || ! strcmp(argv[1], "-v"))
    {
        visual();
    }
    else
    {
        test_command(argv[1]);
    }

    return 0;
}

void quit_with_error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

void init()
{
    /* Création du fichier JSON */
    jsonfile_write = fopen("received.json", "w");
    if (! jsonfile_write)
        quit_with_error("Impossible d'ouvrir le fichier received.json pour l'ecriture");

    /* Obtenir l'arbre de travaille github */
    struct curl_slist * chunk = NULL;
    CURL *curl_handle;
    curl_handle = curl_easy_init();
    if (! curl_handle)
        quit_with_error("Erreur de création de curl_handle");

    chunk = curl_slist_append(chunk, "Accept: application/vnd.github+json");
    chunk = curl_slist_append(chunk, "User-Agent: rewax61");
    chunk = curl_slist_append(chunk, "Authorization: Bearer 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");
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl_handle, CURLOPT_URL, "https://api.github.com/repos/rewax61/Useful-C-script/branches/main");
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_curl_data);

    CURLcode res =  curl_easy_perform(curl_handle);
    if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl_handle);

    fclose(jsonfile_write);
    
    FILE * jsonfile_read = NULL;
    jsonfile_read = fopen("received.json", "r");
    if (! jsonfile_read)
        quit_with_error("Impossible d'ouvrir le fichier received.json pour la lecture");
    char * response_string = malloc(sizeof(char) * 1);
    if (! response_string)
        quit_with_error("Erreur malloc");
    char c = '\0';
    for (int i = 1; c != EOF; i++)
    {
        c = fgetc(jsonfile_read);
        //printf("%c", c);
        response_string = realloc(response_string, sizeof(char) * i+1);
        if (! response_string)
            quit_with_error("Erreur malloc");
        response_string[i-1] = c;
        response_string[i] = '\0';
    }
    fclose(jsonfile_read);

    const cJSON * commit_1 = NULL;
    const cJSON * commit_2 = NULL;
    const cJSON * tree = NULL;
    const cJSON * sha = NULL;
    char working_tree_sha[41];
    working_tree_sha[0] = '\0';
    cJSON * response_json = cJSON_Parse(response_string);
    if (! response_json)
    {
        char *error_ptr = (char *) cJSON_GetErrorPtr();
        quit_with_error(error_ptr);
    }

    commit_1 = cJSON_GetObjectItemCaseSensitive(response_json, "commit");
    if (cJSON_IsObject(commit_1))
    {
        printf("OK !\n");
        commit_2 = cJSON_GetObjectItemCaseSensitive(commit_1, "commit");
        if (cJSON_IsObject(commit_2))
        {
            printf("OK OK !\n");
            tree = cJSON_GetObjectItemCaseSensitive(commit_2, "tree");
            if (cJSON_IsObject(tree))
            {
                printf("OK OK OK !\n");
                sha = cJSON_GetObjectItemCaseSensitive(tree, "sha");
                if (cJSON_IsString(sha))
                {
                    printf("LET'S GOOOOO !!!\n");
                    strcpy(working_tree_sha, sha->valuestring);
                    printf("%s -- %lu\n", working_tree_sha, strlen(working_tree_sha));
                }
                else
                    quit_with_error("Erreur de parsing niveau 4\n");
            }
            else
                quit_with_error("Erreur de parsing niveau 3\n");
        }
        else
            quit_with_error("Erreur de parsing niveau 2");
    }
    else
        quit_with_error("Erreur de parsing niveau 1");

    cJSON_Delete(response_json);
    free(response_string);
}

void test_command(char *command)
{
    if (! strcmp(command, "help"))
    {
        printf("You can use these commands:\n\thelp: show more information\n\texit: quit the programm\n\tlist: show a list of available files\n");
    }
    else if (! strcmp(command, "exit"))
    {
        exit(EXIT_SUCCESS);
    }
    else if (! strcmp(command, "list"))
    {
        printf("LIST...\n");

    }
}

void visual()
{
    printf("==================\n# Welcome on UCS #\n==================\n");
    printf("Type help for more information\n");
    while (true)
    {
        printf("> ");
        char command[MAX_CMD_SIZE];
        fgets(command, MAX_CMD_SIZE, stdin);
        size_t len = strlen(command);
        command[len-1] = '\0';
        len--;

        test_command(command);
        
    }
}

static size_t write_curl_data(void *ptr, size_t size, size_t nmemb)
{
    size_t written = fwrite(ptr, size, nmemb, jsonfile_write);
    return written;
}
