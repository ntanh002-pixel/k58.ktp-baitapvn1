#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ================== CAESAR ==================
string caesarEncrypt(const string &text, int k) {
    string res="";
    for(char c:text){
        if(isalpha(c)){
            char base=isupper(c)?'A':'a';
            res+=char((c-base+k)%26+base);
        } else res+=c;
    }
    return res;
}
string caesarDecrypt(const string &text,int k){
    return caesarEncrypt(text,26-(k%26));
}

// ================== AFFINE ==================
int modInverse(int a,int m){
    a=(a%m+m)%m;
    for(int x=1;x<m;x++)
        if((a*x)%m==1) return x;
    return -1;
}
string affineEncrypt(const string &text,int a,int b){
    string res="";
    for(char c:text){
        if(isalpha(c)){
            char base=isupper(c)?'A':'a';
            res+=char((a*(c-base)+b)%26+base);
        } else res+=c;
    }
    return res;
}
string affineDecrypt(const string &text,int a,int b){
    string res="";
    int inv=modInverse(a,26);
    for(char c:text){
        if(isalpha(c)){
            char base=isupper(c)?'A':'a';
            int val=(inv*((c-base)-b+26))%26;
            res+=char(val+base);
        } else res+=c;
    }
    return res;
}

// ================== HOÁN VỊ ==================
string hoanviEncrypt(const string &text,const vector<int> &key){
    string res="";
    int block=key.size();
    for(int i=0;i<text.size();i+=block){
        string b=text.substr(i,block);
        if(b.size()<block) b.append(block-b.size(),'X');
        string newb(block,' ');
        for(int j=0;j<block;j++) newb[j]=b[key[j]-1];
        res+=newb;
    }
    return res;
}
string hoanviDecrypt(const string &text,const vector<int> &key){
    string res="";
    int block=key.size();
    vector<int> inv(block);
    for(int i=0;i<block;i++) inv[key[i]-1]=i;
    for(int i=0;i<text.size();i+=block){
        string b=text.substr(i,block);
        string newb(block,' ');
        for(int j=0;j<block;j++) newb[j]=b[inv[j]];
        res+=newb;
    }
    return res;
}

// ================== VIGENERE ==================
string vigenereEncrypt(const string &text,const string &key){
    string res=""; int klen=key.size(),ki=0;
    for(char c:text){
        if(isalpha(c)){
            char base=isupper(c)?'A':'a';
            char kbase=isupper(key[ki%klen])?'A':'a';
            int shift=key[ki%klen]-kbase;
            res+=char((c-base+shift)%26+base);
            ki++;
        } else res+=c;
    }
    return res;
}
string vigenereDecrypt(const string &text,const string &key){
    string res=""; int klen=key.size(),ki=0;
    for(char c:text){
        if(isalpha(c)){
            char base=isupper(c)?'A':'a';
            char kbase=isupper(key[ki%klen])?'A':'a';
            int shift=key[ki%klen]-kbase;
            res+=char((c-base-shift+26)%26+base);
            ki++;
        } else res+=c;
    }
    return res;
}

// ================== PLAYFAIR ==================
void generateMatrix(const string &key,char mat[5][5]){
    string used="";
    for(char c:key){
        c=tolower(c); if(c=='j') c='i';
        if(isalpha(c) && used.find(c)==string::npos) used+=c;
    }
    for(char c='a';c<='z';c++){
        if(c=='j') continue;
        if(used.find(c)==string::npos) used+=c;
    }
    int idx=0;
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) mat[i][j]=used[idx++];
}
void findPos(char mat[5][5],char c,int &r,int &col){
    if(c=='j') c='i';
    for(int i=0;i<5;i++) for(int j=0;j<5;j++)
        if(mat[i][j]==c){r=i;col=j;return;}
}
string playfairEncrypt(string text,const string &key){
    char mat[5][5]; generateMatrix(key,mat);
    string clean="";
    for(char c:text){
        if(isalpha(c)){c=tolower(c); if(c=='j') c='i'; clean+=c;}
    }
    string prep="";
    for(int i=0;i<clean.size();i++){
        prep+=clean[i];
        if(i+1<clean.size() && clean[i]==clean[i+1]) prep+='x';
    }
    if(prep.size()%2) prep+='x';
    string res="";
    for(int i=0;i<prep.size();i+=2){
        char a=prep[i],b=prep[i+1]; int r1,c1,r2,c2;
        findPos(mat,a,r1,c1); findPos(mat,b,r2,c2);
        if(r1==r2){res+=mat[r1][(c1+1)%5]; res+=mat[r2][(c2+1)%5];}
        else if(c1==c2){res+=mat[(r1+1)%5][c1]; res+=mat[(r2+1)%5][c2];}
        else {res+=mat[r1][c2]; res+=mat[r2][c1];}
    }
    return res;
}
string playfairDecrypt(string text,const string &key){
    char mat[5][5]; generateMatrix(key,mat);
    string res="";
    for(int i=0;i<text.size();i+=2){
        char a=text[i],b=text[i+1]; int r1,c1,r2,c2;
        findPos(mat,a,r1,c1); findPos(mat,b,r2,c2);
        if(r1==r2){res+=mat[r1][(c1+4)%5]; res+=mat[r2][(c2+4)%5];}
        else if(c1==c2){res+=mat[(r1+4)%5][c1]; res+=mat[(r2+4)%5][c2];}
        else {res+=mat[r1][c2]; res+=mat[r2][c1];}
    }
    return res;
}

// ================== MAIN ==================
int main(){
    int count=0;
    cout<<"=============================\n";
    cout<<"   🔐 CLASSICAL CIPHERS 🔐\n";
    cout<<"=============================\n";
    while(true){
        cout<<"\n--- MENU ---\n";
        cout<<"1. Caesar\n2. Affine\n3. Hoan vi\n4. Vigenere\n5. Playfair\n0. Thoat\n";
        cout<<"Chon phuong phap: ";
        int method; cin>>method; cin.ignore();
        if(method==0) break;

        cout<<"1. Ma hoa\n2. Giai ma\nChon thao tac: ";
        int act; cin>>act; cin.ignore();

        string text,key; int k,a,b;

        switch(method){
        case 1:
            cout<<"Nhap chuoi: "; getline(cin,text);
            cout<<"Nhap k: "; cin>>k; cin.ignore();
            cout<<(act==1? "Ma hoa: ":"Giai ma: ");
            cout<<(act==1? caesarEncrypt(text,k):caesarDecrypt(text,k))<<"\n";
            break;
        case 2:
            cout<<"Nhap chuoi: "; getline(cin,text);
            cout<<"Nhap a: "; cin>>a; cout<<"Nhap b: "; cin>>b; cin.ignore();
            cout<<(act==1? "Ma hoa: ":"Giai ma: ");
            cout<<(act==1? affineEncrypt(text,a,b):affineDecrypt(text,a,b))<<"\n";
            break;
        case 3:{
            cout<<"Nhap chuoi: "; getline(cin,text);
            int n; cout<<"Nhap so phan tu khoa: "; cin>>n;
            vector<int> hv(n); cout<<"Nhap khoa (vd 3 1 2): ";
            for(int i=0;i<n;i++) cin>>hv[i]; cin.ignore();
            cout<<(act==1? "Ma hoa: ":"Giai ma: ");
            cout<<(act==1? hoanviEncrypt(text,hv):hoanviDecrypt(text,hv))<<"\n";
            break;}
        case 4:
            cout<<"Nhap chuoi: "; getline(cin,text);
            cout<<"Nhap khoa: "; getline(cin,key);
            cout<<(act==1? "Ma hoa: ":"Giai ma: ");
            cout<<(act==1? vigenereEncrypt(text,key):vigenereDecrypt(text,key))<<"\n";
            break;
        case 5:
            cout<<"Nhap chuoi: "; getline(cin,text);
            cout<<"Nhap khoa: "; getline(cin,key);
            cout<<(act==1? "Ma hoa: ":"Giai ma: ");
            cout<<(act==1? playfairEncrypt(text,key):playfairDecrypt(text,key))<<"\n";
            break;
        default:
            cout<<"Lua chon khong hop le!\n";
        }
        count++;
        cout<<"[Thao tac da thuc hien: "<<count<<"]\n";
        system("pause");
    }
    cout<<"\nCam on da su dung! Hen gap lai 👋\n";
    return 0;
}
