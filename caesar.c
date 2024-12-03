#include <stdio.h>
#include <string.h>

// Function to encrypt the message
void encrypt(char message[], int key) {
    int i;
    for (i = 0; i < strlen(message); i++) {
        char ch = message[i];
        if (ch >= 'A' && ch <= 'Z') {
            message[i] = ((ch - 'A' + key) % 26) + 'A'; // Uppercase letters
        } else if (ch >= 'a' && ch <= 'z') {
            message[i] = ((ch - 'a' + key) % 26) + 'a'; // Lowercase letters
        }
    }
}

// Function to decrypt the message
void decrypt(char message[], int key) {
    int i;
    for (i = 0; i < strlen(message); i++) {
        char ch = message[i];
        if (ch >= 'A' && ch <= 'Z') {
            message[i] = ((ch - 'A' - key + 26) % 26) + 'A'; // Uppercase letters
        } else if (ch >= 'a' && ch <= 'z') {
            message[i] = ((ch - 'a' - key + 26) % 26) + 'a'; // Lowercase letters
        }
    }
}

int main() {
    char message[100];
    int key;

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the key (1-25): ");
    scanf("%d", &key);

    // Ensure the key is within range
    key = key % 26;

    // Encrypt the message
    encrypt(message, key);
    printf("Encrypted message: %s\n", message);

    // Decrypt the message
    decrypt(message, key);
    printf("Decrypted message: %s\n", message);

    return 0;
}

