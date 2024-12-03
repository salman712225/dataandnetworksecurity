#include <stdio.h>
#include <string.h>
#include <math.h>

// Function to encrypt the message
void encrypt(char plaintext[], int key) {
    int i, j, length = strlen(plaintext), rows, cols;
    char grid[10][10]; // Adjust size if larger key is needed

    // Calculate rows and columns
    cols = key;
    rows = (int)ceil((double)length / cols);

    // Fill the grid with plaintext, padding with 'X' if necessary
    int pos = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (pos < length) {
                grid[i][j] = plaintext[pos++];
            } else {
                grid[i][j] = 'X'; // Padding
            }
        }
    }

    // Print the ciphertext column by column
    printf("Encrypted Text: ");
    for (j = 0; j < cols; j++) {
        for (i = 0; i < rows; i++) {
            printf("%c", grid[i][j]);
        }
    }
    printf("\n");
}

// Function to decrypt the message
void decrypt(char ciphertext[], int key) {
    int i, j, length = strlen(ciphertext), rows, cols;
    char grid[10][10]; // Adjust size if larger key is needed

    // Calculate rows and columns
    cols = key;
    rows = (int)ceil((double)length / cols);

    // Fill the grid with ciphertext column by column
    int pos = 0;
    for (j = 0; j < cols; j++) {
        for (i = 0; i < rows; i++) {
            if (pos < length) {
                grid[i][j] = ciphertext[pos++];
            }
        }
    }

    // Print the plaintext row by row
    printf("Decrypted Text: ");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (grid[i][j] != 'X') { // Skip padding
                printf("%c", grid[i][j]);
            }
        }
    }
    printf("\n");
}

int main() {
    char message[100];
    int key;

    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the key (number of columns): ");
    scanf("%d", &key);

    // Encrypt the message
    encrypt(message, key);

    // Prepare ciphertext for decryption
    printf("Enter the ciphertext to decrypt: ");
    scanf("%s", message);

    // Decrypt the message
    decrypt(message, key);

    return 0;
}

