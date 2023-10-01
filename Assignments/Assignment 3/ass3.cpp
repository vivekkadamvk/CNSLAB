#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;
// Function to remove spaces and convert to uppercase
string prepare_plaintext(string plaintext) {
 string result = "";
 for (int i = 0; i < plaintext.length(); i++) {
 if (isalpha(plaintext[i])) {
 result += toupper(plaintext[i]);
 }
 }
 return result;
}
// Function to construct the Playfair matrix
void construct_matrix(string keyword, char matrix[][6]) {
 bool used[26] = { false };
 int k = 0;
 // Add the keyword to the matrix
 for (int i = 0; i < keyword.length(); i++) {
 if (!used[keyword[i] - 'A']) {
 matrix[k / 6][k % 6] = keyword[i];
 used[keyword[i] - 'A'] = true;
 k++;
 }
 }
 // Add the remaining letters of the alphabet to the matrix
 for (int i = 0; i < 26; i++) {
 if (!used[i] && i != ('J' - 'A')) {
 matrix[k / 6][k % 6] = i + 'A';
 used[i] = true;
 k++;
 }
 }
}
// Function to encrypt using the Playfair cipher algorithm
string encrypt(string plaintext, char matrix[][6]) {
 string ciphertext = "";
 // Divide the plaintext into pairs of letters
 for (int i = 0; i < plaintext.length(); i += 2) {
 char letter1 = plaintext[i];
 char letter2 = plaintext[i + 1];
 // If the two letters are the same, add a padding 'X' after the first letter
 if (letter1 == letter2) {
 letter2 = 'X';
 i--;
 }
 int row1, col1, row2, col2;
 // Find the row and column of the first letter
 for (int j = 0; j < 5; j++) {
 for (int k = 0; k < 6; k++) {
 if (matrix[j][k] == letter1) {
 row1 = j;
 col1 = k;
 }
 }
 }
 // Find the row and column of the second letter
 for (int j = 0; j < 5; j++) {
 for (int k = 0; k < 6; k++) {
 if (matrix[j][k] == letter2) {
 row2 = j;
 col2 = k;
 }
 }
 }
 // If the two letters are in the same row, use the letters to their right
 if (row1 == row2) {
 ciphertext += matrix[row1][(col1 + 1) % 6];
 ciphertext += matrix[row2][(col2 + 1) % 6];
 }
 // If the two letters are in the same column, use the letters below them
 else if (col1 == col2) {
 ciphertext += matrix[(row1 + 1) % 5][col1];
 ciphertext += matrix[(row2 + 1) % 5][col2];
 }
 // Otherwise, form a rectangle with the two letters and use the letters at the opposite corners
 else {
 ciphertext += matrix[row1][col2];
 ciphertext += matrix[row2][col1];
 }
}
return ciphertext;
}
// Function to decrypt using the Playfair cipher algorithm
string decrypt(string ciphertext, char matrix[][6]) {
string plaintext = "";
// Divide the ciphertext into pairs of letters
for (int i = 0; i < ciphertext.length(); i += 2) {
char letter1 = ciphertext[i];
char letter2 = ciphertext[i + 1];
int row1, col1, row2, col2;
// Find the row and column of the first letter
for (int j = 0; j < 5; j++) {
for (int k = 0; k < 6; k++) {
if (matrix[j][k] == letter1) {
row1 = j;
col1 = k;
}
}
}
// Find the row and column of the second letter
for (int j = 0; j < 5; j++) {
for (int k = 0; k < 6; k++) {
if (matrix[j][k] == letter2) {
row2 = j;
col2 = k;
}
}
}
// If the two letters are in the same row, use the letters to their left
if (row1 == row2) {
plaintext += matrix[row1][(col1 + 5) % 6];
plaintext += matrix[row2][(col2 + 5) % 6];
}
// If the two letters are in the same column, use the letters above them
else if (col1 == col2) {
plaintext += matrix[(row1 + 5) % 5][col1];
plaintext += matrix[(row2 + 5) % 5][col2];
}
// Otherwise, form a rectangle with the two letters and use the letters at the opposite corners
else {
plaintext += matrix[row1][col2];
plaintext += matrix[row2][col1];
}
}
// Remove any padding 'X' characters
if (plaintext[plaintext.length() - 1] == 'X') {
plaintext = plaintext.substr(0, plaintext.length() - 1);
}
return plaintext;
}
int main() {
string plaintext, keyword;
char matrix[5][6];
cout << "Enter the plaintext: ";
getline(cin, plaintext);
cout << "Enter the keyword: ";
getline(cin, keyword);
// Prepare the plaintext and construct the matrix
plaintext = prepare_plaintext(plaintext);
construct_matrix(keyword, matrix);
// Encrypt and decrypt the plaintext using the matrix
string ciphertext = encrypt(plaintext, matrix);
string decrypted_plaintext = decrypt(ciphertext, matrix);
// Print the results
cout << "Plaintext: " << plaintext << endl;
cout << "Ciphertext: " << ciphertext << endl;
cout << "Decrypted plaintext: " << decrypted_plaintext << endl;
return 0;
}