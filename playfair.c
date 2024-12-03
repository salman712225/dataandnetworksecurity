#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to remove duplicate characters from the key
void prepareKey(char key[], char keyTable[SIZE][SIZE]) {
    int i, j, k, alphabetUsed[26] = {0};
    char ch;

    k = 0;
    // Fill the key table with the unique characters from the key
    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; // Replace J with I
        if (!alphabetUsed[ch - 'A'] && isalpha(ch)) {
            keyTable[k / SIZE][k % SIZE] = ch;
            alphabetUsed[ch - 'A'] = 1;
            k++;
        }
    }

    // Fill remaining cells with unused letters
    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip J
        if (!alphabetUsed[ch - 'A']) {
            keyTable[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }
}

// Function to prepare the plaintext for encryption
void prepareText(char text[]) {
    int i, j = 0;
    char result[100];

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            result[j++] = toupper(text[i]);
        }
    }
    result[j] = '\0';

    for (i = 0; result[i] != '\0'; i++) {
        if (result[i] == 'J') result[i] = 'I'; // Replace J with I
    }

    // Insert 'X' between duplicate letters and make length even
    j = 0;
    for (i = 0; result[i] != '\0'; i++) {
        text[j++] = result[i];
        if (result[i] == result[i + 1]) {
            text[j++] = 'X';
        }
    }
    if (j % 2 != 0) text[j++] = 'X'; // Append 'X' if length is odd
    text[j] = '\0';
}

// Function to find the position of a character in the key table
void findPosition(char ch, char keyTable[SIZE][SIZE], int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt or decrypt a pair of characters
void processPair(char a, char b, char keyTable[SIZE][SIZE], char *result, int encrypt) {
    int row1, col1, row2, col2;

    findPosition(a, keyTable, &row1, &col1);
    findPosition(b, keyTable, &row2, &col2);

    if (row1 == row2) {
        // Same row
        result[0] = keyTable[row1][(col1 + (encrypt ? 1 : -1) + SIZE) % SIZE];
        result[1] = keyTable[row2][(col2 + (encrypt ? 1 : -1) + SIZE) % SIZE];
    } else if (col1 == col2) {
        // Same column
        result[0] = keyTable[(row1 + (encrypt ? 1 : -1) + SIZE) % SIZE][col1];
        result[1] = keyTable[(row2 + (encrypt ? 1 : -1) + SIZE) % SIZE][col2];
    } else {
        // Rectangle rule
        result[0] = keyTable[row1][col2];
        result[1] = keyTable[row2][col1];
    }
}

// Function to encrypt or decrypt a text
void playfairCipher(char text[], char keyTable[SIZE][SIZE], int encrypt) {
    int i;
    char result[2];

    for (i = 0; text[i] != '\0'; i += 2) {
        processPair(text[i], text[i + 1], keyTable, result, encrypt);
        text[i] = result[0];
        text[i + 1] = result[1];
    }
}

int main() {
    char key[100], plaintext[100], keyTable[SIZE][SIZE];
    int i, j;

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline

    // Prepare the key table
    prepareKey(key, keyTable);

    // Display the key table
    printf("\nKey Table:\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%c ", keyTable[i][j]);
        }
        printf("\n");
    }

    // Prepare the plaintext
    prepareText(plaintext);
    printf("\nPrepared Plaintext: %s\n", plaintext);

    // Encrypt the plaintext
    playfairCipher(plaintext, keyTable, 1);
    printf("\nEncrypted Text: %s\n", plaintext);

    // Decrypt the ciphertext
    playfairCipher(plaintext, keyTable, 0);
    printf("Decrypted Text: %s\n", plaintext);

    return 0;
}

