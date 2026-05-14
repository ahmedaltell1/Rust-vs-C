/* This program uses two separate libraries, one implementing the AES 128 Decryption function,
 * the other implements the base64 decoding function */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.c"
#include "base64.c"

#define BUFFER_SIZE 100000

void remove_newlines(char *str); // Function declaration for removing newline

int main() {
    char file_path[256]; // Buffer to store the path to the encrypted file
    baseencode_error_t err; // Variable to hold any error code returned by decoding function

    // Prompt user to enter the encrypted file's path
    printf("Enter the path to the encrypted file: ");
    if (!fgets(file_path, sizeof(file_path), stdin)) {
        fprintf(stderr, "Error reading file path\n"); // Error handling in reading input
        return 1;
    }
    file_path[strcspn(file_path, "\n")] = 0; // Remove newline character from the input path

    // Open the file given by the user
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Error opening file"); // Error handling in file opening
        return 1;
    }

    // Allocate memory for storing the encoded base64 message
    char *base64EncodedMessage = malloc(BUFFER_SIZE);
    if (base64EncodedMessage == NULL) {
        fprintf(stderr, "Memory allocation failed\n"); // Handle memory allocation failure
        return 1;
    }
    memset(base64EncodedMessage, 0, BUFFER_SIZE); // Initialize the memory area to zeros

    // Read lines from the file into the base64EncodedMessage buffer
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Ensure no buffer overflow
        if ((strlen(base64EncodedMessage) + strlen(line)) < BUFFER_SIZE) {
            strcat(base64EncodedMessage, line);
        }
    }
    fclose(file); // Close file after reading

    // Remove newline characters from the base64 encoded message string
    remove_newlines(base64EncodedMessage);

    // Decode the base64 encoded message
    unsigned char *decoded = base64_decode(base64EncodedMessage, strlen(base64EncodedMessage), &err);
    free(base64EncodedMessage); // Free the base64 message buffer
    if (err != SUCCESS || !decoded) {
        fprintf(stderr, "Failed to decode base64. Error code: %d\n", err); // Handle decoding failure
        return 1;
    }

    // Determine the length of the decoded message
    size_t decodedLen = strlen((char*)decoded);

    // Prepare the key for AES decryption
    uint8_t key[16] = "ThisPasswordBad!"; // Pre-known key converted to ASCII
    uint8_t *decrypted = malloc(decodedLen); // Allocate memory for the decrypted message
    if (decrypted == NULL) {
        fprintf(stderr, "Memory allocation failed\n"); // Handle memory allocation failure
        free(decoded); // Ensure to free the decoded memory if decryption buffer allocation fails
        return 1;
    }

    // Perform AES decryption block by block
    for (size_t i = 0; i < decodedLen; i += 16) {
        aes_decrypt(decrypted + i, key, decoded + i);
    }

    // Print decrypted message
    printf("Decrypted message: ");
    for (size_t i = 0; i < decodedLen; i++) {
        printf("%c", decrypted[i]);
    }
    printf("\n");

    // Free manually allocated memory
    free(decoded);
    free(decrypted);

    return 0;
}

// Function to remove newline characters from a string
void remove_newlines(char *str) {
    char *dst = str; // Destination pointer for the cleaned string
    for (const char *src = str; *src != '\0'; ++src) {
        *dst = *src; // Copy character by character
        if (*dst != '\n' && *dst != '\r') dst++; // Increment destination if character is not a newline
    }
    *dst = '\0'; // Null termination
}