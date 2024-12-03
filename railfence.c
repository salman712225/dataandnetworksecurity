#include <stdio.h>
#include <string.h>

// Function to encrypt the plaintext using Rail Fence Cipher
void encryptRailFence(char plaintext[], int key, char ciphertext[]) {
    int length = strlen(plaintext);
    int i, j, row = 0, dir = 1;
    char rail[key][length];

    // Initialize the rail matrix with spaces
    for (i = 0; i < key; i++) {
        for (j = 0; j < length; j++) {
            rail[i][j] = ' ';
        }
    }

    // Fill the rail matrix with the plaintext characters in zigzag order
    for (i = 0; i < length; i++) {
        rail[row][i] = plaintext[i];
        row += dir;

        if (row == 0 || row == key - 1) {
            dir *= -1; // Change direction when hitting top or bottom
        }
    }

    // Read the ciphertext row by row
    int index = 0;
    for (i = 0; i < key; i++) {
        for (j = 0; j < length; j++) {
            if (rail[i][j] != ' ') {
                ciphertext[index++] = rail[i][j];
            }
        }
    }
    ciphertext[index] = '\0';
}

// Function to decrypt the ciphertext using Rail Fence Cipher
void decryptRailFence(char ciphertext[], int key, char plaintext[]) {
    int length = strlen(ciphertext);
    int i, j, row = 0, dir = 1;
    char rail[key][length];

    // Initialize the rail matrix with spaces
    for (i = 0; i < key; i++) {
        for (j = 0; j < length; j++) {
            rail[i][j] = ' ';
        }
    }

    // Mark positions to be filled in the rail matrix in zigzag order
    for (i = 0; i < length; i++) {
        rail[row][i] = '*';
        row += dir;

        if (row == 0 || row == key - 1) {
            dir *= -1; // Change direction when hitting top or bottom
        }
    }

    // Fill the rail matrix with ciphertext characters
    int index = 0;
    for (i = 0; i < key; i++) {
        for (j = 0; j < length; j++) {
            if (rail[i][j] == '*' && index < length) {
                rail[i][j] = ciphertext[index++];
            }
        }
    }

    // Read the plaintext in zigzag order
    row = 0;
    dir = 1;
    for (i = 0; i < length; i++) {
        plaintext[i] = rail[row][i];
        row += dir;

        if (row == 0 || row == key - 1) {
            dir *= -1; // Change direction when hitting top or bottom
        }
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[100], ciphertext[100];
    int key;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the key (number of rails): ");
    scanf("%d", &key);

    // Encrypt the plaintext
    encryptRailFence(plaintext, key, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);

    // Decrypt the ciphertext
    char decrypted[100];
    decryptRailFence(ciphertext, key, decrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}

