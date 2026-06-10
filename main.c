#include "quantum_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_apple_copyright() {
    FILE *file = fopen("APPLE_COPYRIGHT", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: APPLE_COPYRIGHT file not found. Native execution aborted.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fprintf(stderr, "Error: APPLE_COPYRIGHT file is empty. Native execution aborted.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Check for the new copyright notice format
    if (strstr(buffer, "Copyright: (©) 2026 by Apple Computer, Inc., All Rights Reserved.") == NULL) {
        fprintf(stderr, "Error: Invalid Apple Copyright notice. Native execution aborted.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    printf("[NATIVE CHECK] Apple Copyright Verified.\n\n");
}

int main() {
    check_apple_copyright();
    
    quantum_engine engine;
    qe_init(&engine);
    qe_run_report(&engine);
    qe_clear(&engine);
    
    return 0;
}
