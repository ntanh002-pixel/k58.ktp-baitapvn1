// classical_ciphers.cpp
#include <bits/stdc++.h>
using namespace std;

// ----- Utility -----
string normalize(const string &s) {
    string t;
    for (char ch : s) if (isalpha((unsigned char)ch)) t += toupper(ch);
    return t;
}

// ================== 1. Caesar ==================
string caesar_encrypt(const string &plain, int k) {
    string p = normalize(plain), out;
    k = (k % 26 + 26) % 26;
    for (char c : p) out += char('A' + (c - 'A' + k) % 26);
    return out;
}
string caesar_decrypt(const string &cipher, int k) {
    return caesar_encrypt(cipher, -k);
}

// ================== 2. Affine ==================
int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return -1;
}
string affine_encrypt(const string &plain, int a, int b) {
    string p = normalize(plain), out;
    for (char c : p) {
        int x = c - 'A';
        out += char('A' + (a * x + b) % 26);
    }
    return out;
}
string affine_decrypt(const string &cipher, int a, int b) {
    string out;
    int a_inv = modInverse(a, 26);
    for (char c : cipher) {
        int y = c - 'A';
        out += char('A' + (a_inv * (y - b + 26)) % 26);
    }
    return out;
}

// ================== 3. Columnar Transposition ==================
string transposition_encrypt(const string &plain, const string &key) {
    string p = normalize(plain);
    int n = key.size();
    int rows = (p.size() + n - 1) / n;
    vector<string> matrix(rows, string(n, 'X'));
    for (int i = 0; i < (int)p.size(); i++) matrix[i/n][i%n] = p[i];

    vector<pair<char,int>> order;
    for (int i = 0; i < n; i++) order.push_back({toupper(key[i]), i});
    sort(order.begin(), order.end());

    string out;
    for (auto [ch, col] : order) {
        for (int r = 0; r < rows; r++) out += matrix[r][col];
    }
    return out;
}
string transposition_decrypt(const string &cipher, const string &key) {
    int n = key.size();
    int rows = (cipher.size() + n - 1) / n;
    int total = cipher.size();

    vector<pair<char,int>> order;
    for (int i = 0; i < n; i++) order.push_back({toupper(key[i]), i});
    sort(order.begin(), order.end());

    vector<string> matrix(rows, string(n, ' '));
    vector<int> colLen(n, rows);
    int extra = n*rows - total;
    for (int i = n-extra; i < n; i++) colLen[order[i].second]--;

    int idx = 0;
    for (auto [ch, col] : order) {
        for (int r = 0; r < colLen[col]; r++)
            matrix[r][col] = cipher[idx++];
    }
    string out;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < n; c++)
            if (matrix[r][c] != ' ') out += matrix[r][c];
    return out;
}

// ================== 4. Vigenere ==================
string vigenere_encrypt(const string &plain, const string &key) {
    string p = normalize(plain), k = normalize(key), out;
    for (int i = 0; i < (int)p.size(); i++) {
        int shift = k[i % k.size()] - 'A';
        out += char('A' + (p[i] - 'A' + shift) % 26);
    }
    return out;
}
string vigenere_decrypt(const string &cipher, const string &key) {
    string k = normalize(key), out;
    for (int i = 0; i < (int)cipher.size(); i++) {
        int shift = k[i % k.size()] - 'A';
        out += char('A' + (cipher[i] - 'A' - shift + 26) % 26);
    }
    return out;
}

// ================== 5. Playfair ==================
struct Playfair {
    char table[5][5];
    map<char,pair<int,int>> pos;

    Playfair(string key) {
        string k = normalize(key) + "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // J=I
        string seen;
        for (char c : k) {
            if (c == 'J') c = 'I';
            if (seen.find(c) == string::npos) seen += c;
        }
        int idx = 0;
        for (int r=0; r<5; r++) for (int c=0; c<5; c++) {
            table[r][c] = seen[idx];
            pos[seen[idx]] = {r,c};
            idx++;
        }
    }

    vector<pair<char,char>> makePairs(string text) {
        string p = normalize(text);
        vector<pair<char,char>> res;
        for (int i=0; i<(int)p.size();) {
            char a = p[i];
            char b = (i+1 < (int)p.size()) ? p[i+1] : 'X';
            if (a == b) { res.push_back({a,'X'}); i++; }
            else { res.push_back({a,b}); i+=2; }
        }
        if (res.back().second == 0) res.back().second = 'X';
        return res;
    }

    string encrypt(string text) {
        auto pairs = makePairs(text);
        string out;
        for (auto [a,b]: pairs) {
            if (a=='J') a='I'; if (b=='J') b='I';
            auto [r1,c1] = pos[a];
            auto [r2,c2] = pos[b];
            if (r1==r2) { out += table[r1][(c1+1)%5]; out += table[r2][(c2+1)%5]; }
            else if (c1==c2) { out += table[(r1+1)%5][c1]; out += table[(r2+1)%5][c2]; }
            else { out += table[r1][c2]; out += table[r2][c1]; }
        }
        return out;
    }
    string decrypt(string text) {
        string p = normalize(text);
        string out;
        for (int i=0; i<(int)p.size(); i+=2) {
            char a = p[i], b = p[i+1];
            auto [r1,c1] = pos[a];
            auto [r2,c2] = pos[b];
            if (r1==r2) { out += table[r1][(c1+4)%5]; out += table[r2][(c2+4)%5]; }
            else if (c1==c2) { out += table[(r1+4)%5][c1]; out += table[(r2+4)%5][c2]; }
            else { out += table[r1][c2]; out += table[r2][c1]; }
        }
        return out;
    }
};

// ================== MAIN DEMO ==================
int main() {
    cout << "=== Classical Ciphers Demo ===\n";
    string text = "HELLO WORLD";

    cout << "\nCaesar:\n";
    string c1 = caesar_encrypt(text,3);
    cout << "Encrypt: " << c1 << " Decrypt: " << caesar_decrypt(c1,3) << "\n";

    cout << "\nAffine:\n";
    string c2 = affine_encrypt(text,5,8);
    cout << "Encrypt: " << c2 << " Decrypt: " << affine_decrypt(c2,5,8) << "\n";

    cout << "\nTransposition (KEY=ZEBRA):\n";
    string c3 = transposition_encrypt(text,"ZEBRA");
    cout << "Encrypt: " << c3 << " Decrypt: " << transposition_decrypt(c3,"ZEBRA") << "\n";

    cout << "\nVigenere (KEY=KEY):\n";
    string c4 = vigenere_encrypt(text,"KEY");
    cout << "Encrypt: " << c4 << " Decrypt: " << vigenere_decrypt(c4,"KEY") << "\n";

    cout << "\nPlayfair (KEY=MONARCHY):\n";
    Playfair pf("MONARCHY");
    string c5 = pf.encrypt(text);
    cout << "Encrypt: " << c5 << " Decrypt: " << pf.decrypt(c5) << "\n";
}
