#include <bits/stdc++.h>
using namespace std;

// Convert char to number (A=0 ... Z=25)
int charToNum(char c) {
    return toupper(c) - 'A';
}

// Convert number to char
char numToChar(int n) {
    return 'A' + (n % 26);
}

// Clean string: remove non-letters & uppercase
string cleanText(string s) {
    string res = "";
    for (char c : s) {
        if (isalpha(c)) res += toupper(c);
    }
    return res;
}
 

string encryptRunningKey(string plaintext, string key) {
    plaintext = cleanText(plaintext);
    key = cleanText(key);

    if (key.length() < plaintext.length()) {
        cout << "Key must be at least as long as plaintext\n";
        return "";
    }

    string ciphertext = "";

    for (int i = 0; i < plaintext.length(); i++) {
        int p = charToNum(plaintext[i]);
        int k = charToNum(key[i]);

        int c = (p + k) % 26;
        ciphertext += numToChar(c);
    }

    return ciphertext;
}

// 🔓 Decryption
string decryptRunningKey(string ciphertext, string key) {
    ciphertext = cleanText(ciphertext);
    key = cleanText(key);

    string plaintext = "";

    for (int i = 0; i < ciphertext.length(); i++) {
        int c = charToNum(ciphertext[i]);
        int k = charToNum(key[i]);

        int p = (c - k + 26) % 26;
        plaintext += numToChar(p);
    }

    return plaintext;
}


// 🔑 Simple Hash Function
long long simpleHash(string text) {
    const int base = 31;
    const int MOD = 1e9 + 7;

    long long hash = 0;

    for (char c : text) {
        if (isalpha(c)) {
            int val = toupper(c) - 'A' + 1;
            hash = (hash * base + val) % MOD;
        }
    }

    return hash;
}

int main() {
    string plaintext = "HELLO WORLD";
    string key = "KLRAHULISTHEBESTPLAYER"; // must be long

    string encrypted = encryptRunningKey(plaintext, key);
    cout << "Ciphertext: " << encrypted << endl;

    string decrypted = decryptRunningKey(encrypted, key);
    cout << "Decrypted: " << decrypted << endl;

    // Hash values
    cout << "Hash of plaintext: " << simpleHash(plaintext) << endl;
    cout << "Hash of ciphertext: " << simpleHash(encrypted) << endl;

    return 0;
}