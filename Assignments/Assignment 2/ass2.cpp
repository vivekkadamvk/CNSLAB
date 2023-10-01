#include <iostream>
#include <string>

using namespace std;

string polyalphabeticCipher(string text, string keyword, bool encrypt) {
    string result = "";
    int keywordLength = keyword.length();
    int offset = encrypt ? 1 : -1;

    for (int i = 0; i < text.length(); i++) {
        char inputChar = text[i];
        if (isalpha(inputChar)) {
            char base = isupper(inputChar) ? 'A' : 'a';
            char keywordChar = keyword[i % keywordLength];
            char shiftedChar = ((inputChar - base + offset * (keywordChar - 'A') + 26) % 26) + base;
            result += shiftedChar;
        } else {
            result += inputChar; // Non-alphabetic characters are unchanged
        }
    }

    return result;
}

int main() {
    string text, keyword;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the keyword: ";
    cin >> keyword;

    string encryptedText = polyalphabeticCipher(text, keyword, true);
    string decryptedText = polyalphabeticCipher(encryptedText, keyword, false);

    cout << "Encrypted Text: " << encryptedText << endl;
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
