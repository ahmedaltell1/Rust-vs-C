#include <stdio.h>
#include <stdlib.h>
#include "sha256_digest.h"
#include "sha256_digest.c"

#define MAX_FILE_SIZE 100000 // this defines a maximum file size

int main() {
    char file_path[256]; // a buffer to hold the file path

    char expected_hash[65]; // another buffer to hold the expected hash which we are comparing

    printf("Enter the path to the file: ");
    // get filepath from user to read file
    if (fgets(file_path, sizeof(file_path), stdin) == NULL) {
        fprintf(stderr, "Error reading file path\n");
        return 1;
    }

    file_path[strcspn(file_path, "\n")] = 0;

    printf("Enter the expected hash digest of the file contents: ");
    if (fgets(expected_hash, sizeof(expected_hash), stdin) == NULL) {
        fprintf(stderr, "Error reading expected hash\n");
        return 1;
    }

    expected_hash[strcspn(expected_hash, "\n")] = 0;

    // open the file and read it
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Error opening file");  // error if null
        return 1;
    }
    printf("Attempting to open file at path: '%s'\n", file_path);

    char file_contents[MAX_FILE_SIZE];
    size_t bytes_read = fread(file_contents, 1, MAX_FILE_SIZE, file);
    if (bytes_read == 0 && !feof(file)) { // Check for reading error
        fprintf(stderr, "Error reading file\n");
        fclose(file);
        return 1;
    }
    fclose(file);

    // initialize the SHA-256 handler
    struct sha256_base *handler = sha256_init();
    if (!handler) {
        fprintf(stderr, "Error initializing SHA-256 handler\n");
        return 1;
    }

    // create sha256_message from file contents
    struct sha256_message *msg = sha256_message_create_from_buffer(file_contents, bytes_read * 8, handler);
    if (!msg) {
        fprintf(stderr, "Error creating sha256_message\n");
        sha256_free(handler);
        return 1;
    }

    // digest the message
    sha256_message_preprocess(msg);
    sha256_message_digest(msg, handler);

    // get the calculated hash
    char *hash = sha256_message_get_hash(msg);
    if (!hash) {
        fprintf(stderr, "Error getting hash\n");
        sha256_free(handler);
        return 1;
    }

    // prints the hash
    printf("Hash digest of the file : %s\n", hash);

    // compare the calculated hash with the expected hash from the user
    if (strcmp(hash, expected_hash) == 0) {
        printf("Success: The calculated hash matches the expected hash.\n");
    } else {
        printf("Failure: The calculated hash does not match the expected hash.\n");
    }

    // free memory!!!
    free(hash);
    sha256_free(handler);

    return 0;
}
