#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
int row[26];
int col[26];
char text[26];
char x;
void buildMatrix(string key) {
    int curindex = 0;
    for (int i=0; i<key.length(); i++) {
        if (!isalpha(key[i])) continue;
        int no = tolower(key[i]) - 'a';
        if (key[i] == 'j') no -= 1;
        if (row[no] != -1) continue;
        row[no] = curindex / 5;
        col[no] = curindex % 5;
        text[curindex] = 'a' + no;
        curindex ++;
    }
    for (int i=0; i<26; i++) {
        if (i == 9) continue;
        if (row[i] == -1) {
            row[i] = curindex / 5;
            col[i] = curindex % 5;
            text[curindex] = 'a' + i;
            curindex ++;
        }
    }
    if (curindex != 25) cout << "Something wrong!" << endl;    
    for (int r=0; r <5; r ++) {
        for (int c = 0; c < 5; c ++) {
            for (int i=0; i<26; i++) {
                if (row[i] == r && col[i] == c)
                    cout << char('a'+ i) << ' ';
            }
        }
        cout << endl;
    }
    row[9] = row[8]; col[9] = col[8];
}
void encrypt(string p) {
    x = tolower(x);
    int ptr = 0;
    int first, second;
    string res = "";
    while (true) {
        first = -1;
        second = -1;
        if (ptr < p.length()) {
            first = tolower(p[ptr]) - 'a';
            ptr ++;
        }
        if (ptr < p.length()) {
            second = tolower(p[ptr]) - 'a';
            ptr ++;
        }
        if (first == -1) break;
        if (second == -1) {
            second = x - 'a';
        } else {
            if (first == second) {
                second = x - 'a';
                ptr --;
            }
        }
        cout << char('a'+first) << char('a'+second);
        cout << "--->";
        char c1, c2;
        if (row[first] == row[second]) {
            c1 = text[row[first] * 5 + (col[first]+1)%5];
            c2 = text[row[second] * 5 + (col[second]+1)%5];
        } else if (col[first] == col[second]) {
            c1 = text[((row[first]+1)%5)*5+col[first]];
            c2 = text[((row[second]+1)%5)*5+col[first]];
        } else {
            c1 = text[(row[first])*5 + col[second]];
            c2 = text[(row[second])*5 + col[first]];
        }
        cout << c1 << c2 << endl;
        res += c1;
        res += c2;
    }
    cout << "cipher text:" << res << endl;
}
void decrypt(string ciphertext) {
    int ptr = 0;
    int first, second;
    string raw= "";
    string res = "";
    while (ptr < ciphertext.length()) {
        first = tolower(ciphertext[ptr]) - 'a';
        if (first == 9) first --;
        ptr ++;
        second = tolower(ciphertext[ptr]) - 'a';
        if (second == 9) second --;
        ptr ++;
        cout << char('a'+first) << char('a'+second);
        cout << "--->";
        char c1, c2;
        if (row[first] == row[second]) {
            c1 = text[row[first] * 5 + (col[first]+4)%5];
            c2 = text[row[second] * 5 + (col[second]+4)%5];
        } else if (col[first] == col[second]) {
            c1 = text[((row[first]+4)%5)*5+col[first]];
            c2 = text[((row[second]+4)%5)*5+col[first]];
        } else {
            c1 = text[(row[first])*5 + col[second]];
            c2 = text[(row[second])*5 + col[first]];
        }
        cout << c1 << c2 << endl;
        raw += c1;
        raw += c2;
        res += c1;
        if (c2 != x) res += c2;
    }
    cout << "raw plain:" << raw << endl;
    cout << "plain:" << res << endl;
}
int main() {
    for (int i=0; i<26; i++) {
        row[i] = -1;
        col[i] = -1;
    }
    cout << "input x:";
    cin >> x;
    string key;
    cout << "input key:";
    cin >> key;
    buildMatrix(key);
    string plaintext;
    cout << "input plaintext:";
    cin >> plaintext;
    encrypt(plaintext);
    string ciphertext;
    cout << "input ciphertext:";
    cin >> ciphertext;
    decrypt(ciphertext);
}