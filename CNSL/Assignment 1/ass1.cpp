#include <iostream>
#include <string>

using namespace std;

string encrypt(const string &plaintext, int shift) {
    string result = plaintext;

    for (char &ch : result) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = ((ch - base + shift) % 26) + base;
        }
    }

    return result;
}

string decrypt(const string &ciphertext, int shift) {
    return encrypt(ciphertext, 26 - shift);
}

int main() {
    string plaintext, ciphertext;
    int shift;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter the shift value (an integer): ";
    cin >> shift;

    ciphertext = encrypt(plaintext, shift);
    cout << "Encrypted Text: " << ciphertext << endl;

    string decryptedText = decrypt(ciphertext, shift);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
//Code by VK