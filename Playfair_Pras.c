#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30

// Convert 'j' to 'i'
void jtoi(char arr[]) {
    for (int i = 0; i < strlen(arr); i++) {
        if (arr[i] == 'j')
            arr[i] = 'i';
    }
}

// Insert 'x' between consecutive identical characters
void inx(char arr[]) {
    int len = strlen(arr);
    for (int i = 0; i < len - 1; i += 2) {
        if (arr[i] == arr[i + 1]) {
            memmove(&arr[i + 1], &arr[i], len - i);
            arr[i + 1] = 'x';
            len++;
        }
    }
}

// Generate the key table for Playfair Cipher
void genKeyTable(char key[], int kg, char keyT[5][5]) {
    int i, j, k;
    int dicty[26] = {0}; // initialize to zeros

    for (i = 0; i < kg; i++) {
        if (key[i] != 'j')
            dicty[key[i] - 'a'] = 2;
    }
    dicty['j' - 'a'] = 1;

    i = 0;
    j = 0;

    for (k = 0; k < kg; k++) {
        if (dicty[key[k] - 'a'] == 2) {
            dicty[key[k] - 'a'] -= 1;
            keyT[i][j] = key[k];
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }

    for (k = 0; k < 26; k++) {
        if (dicty[k] == 0) {
            keyT[i][j] = (char)(k + 'a');
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }

    printf("Key matrix: \n");

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            printf("%c ", keyT[i][j]);

        printf("\n");
    }
}

// Search for the characters of a digraph in the key square and return their position
void search(char keyT[5][5], char p, char d, int arr[]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyT[i][j] == p) {
                arr[0] = i;
                arr[1] = j;
            } else if (keyT[i][j] == d) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

// Function to perform decryption
void decrypt(char str[], char keyT[5][5], int pd) {
    int a[4];
    for (int i = 0; i < pd; i += 2) {
        search(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][(a[1] - 1 + 5) % 5];
            str[i + 1] = keyT[a[0]][(a[3] - 1 + 5) % 5];
        } else if (a[1] == a[3]) {
            str[i] = keyT[(a[0] - 1 + 5) % 5][a[1]];
            str[i + 1] = keyT[(a[2] - 1 + 5) % 5][a[1]];
        } else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

// Function to call decryption
void decryptByPlayfairCipher(char str[], char key[]) {
    char keyT[5][5];

    jtoi(key);
    printf("key text: %s\n", key);

    inx(str);
    printf("plain text: %s\n", str);

    int pd = strlen(str);
    decrypt(str, keyT, pd);
}

// Function to perform encryption
void encrypt(char str[], char keyT[5][5], int pd) {
    int a[4];
    for (int i = 0; i < pd; i += 2) {
        search(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][(a[1] + 1) % 5];
            str[i + 1] = keyT[a[0]][(a[3] + 1) % 5];
        } else if (a[1] == a[3]) {
            str[i] = keyT[(a[0] + 1) % 5][a[1]];
            str[i + 1] = keyT[(a[2] + 1) % 5][a[1]];
        } else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

// Function to call encryption
void encryptByPlayfairCipher(char str[], char key[]) {
    char keyT[5][5];

    jtoi(key);
    printf("key text: %s\n", key);

    inx(str);
    printf("plain text: %s\n", str);

    int pd = strlen(str);
    pd = makeeven(str, pd);
    
    genKeyTable(key, strlen(key), keyT);

    encrypt(str, keyT, pd);
    printf("cipher text: %s\n", str);
}

int main() {
    char str[SIZE], key[SIZE];

    printf("Enter key value: \n");
    scanf("%s", key);

    printf("Enter plain text: \n");
    scanf("%s", str);

    encryptByPlayfairCipher(str, key);
    decryptByPlayfairCipher(str, key);

    return 0;
}