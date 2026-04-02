#include <bits/stdc++.h>
using namespace std;

// Convert character to number (A=0 ... Z=25)
int charToNum(char c)
{
    return toupper(c) - 'A';
}

// Convert number to character
char numToChar(int n)
{
    return 'A' + (n % 26);
}

// Clean text
string cleanText(string s)
{
    string res = "";
    for (char c : s)
    {
        if (isalpha(c))
            res += toupper(c);
    }
    return res;
}

// Encryption
string encryptRunningKey(string plaintext, string key)
{
    plaintext = cleanText(plaintext);
    key = cleanText(key);

    if (key.length() < plaintext.length())
    {
        cout << "Error: Key must be at least as long as plaintext\n";
        return "";
    }

    string ciphertext = "";

    for (int i = 0; i < plaintext.length(); i++)
    {
        int p = charToNum(plaintext[i]);
        int k = charToNum(key[i]);

        ciphertext += numToChar((p + k) % 26);
    }

    return ciphertext;
}

// Decryption
string decryptRunningKey(string ciphertext, string key)
{
    string plaintext = "";

    for (int i = 0; i < ciphertext.length(); i++)
    {
        int c = charToNum(ciphertext[i]);
        int k = charToNum(key[i]);

        plaintext += numToChar((c - k + 26) % 26);
    }

    return plaintext;
}

// FNV-1a Hash
uint32_t fnv1a(string text)
{
    uint32_t hash = 2166136261u;
    const uint32_t prime = 16777619u;

    for (char c : text)
    {
        hash ^= (unsigned char)c;
        hash *= prime;
    }

    return hash;
}

int main()
{
    string plaintext, key;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter running key (must be >= plaintext length): ";
    getline(cin, key);

    string ciphertext = encryptRunningKey(plaintext, key);

    if (ciphertext == "")
        return 0;

    cout << "\nCiphertext: " << ciphertext << endl;

    // Scenario 1: Integrity Check
    uint32_t hash1 = fnv1a(ciphertext);
    uint32_t hash2 = fnv1a(ciphertext);

    cout << "\nScenario 1: Integrity Check" << endl;
    cout << "Original Hash: " << hash1 << endl;
    cout << "Recomputed Hash: " << hash2 << endl;

    if (hash1 == hash2)
    {
        cout << "Integrity Verified: Hashes match\n";

        // Allow decryption
        string decrypted = decryptRunningKey(ciphertext, key);
        cout << "Decrypted Text: " << decrypted << endl;
    }
    else
    {
        cout << "Integrity Failed. Decryption Denied.\n";
    }

    // Scenario 2: Tampering
    cout << "\nScenario 2: Tampering Simulation" << endl;

    string tampered = ciphertext;

    if (!tampered.empty())
    {
        tampered[0] = (tampered[0] == 'A') ? 'B' : 'A';
    }

    uint32_t tamperedHash = fnv1a(tampered);

    cout << "Tampered Ciphertext: " << tampered << endl;
    cout << "Original Hash: " << hash1 << endl;
    cout << "Tampered Hash: " << tamperedHash << endl;

    if (hash1 != tamperedHash)
    {
        cout << "Tampering Detected: Hash mismatch\n";
        cout << "Decryption Denied\n";
    }
    else
    {
        cout << "No Tampering Detected\n";

        // Only decrypt if safe
        string decrypted = decryptRunningKey(tampered, key);
        cout << "Decrypted Text: " << decrypted << endl;
    }

    return 0;
}