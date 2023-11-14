#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE * term = popen("ssh user@server-address /bin/bash > remoteoutput.txt", "w");
    if (! term) {
        perror("Connection ssh failed");
        exit(EXIT_FAILURE);
    }
    fprintf(term, "your bash command here");
    pclose(term);

    return 0;
}