# Shift cipher
```c
#include <bits/stdc++.h>
using namespace std;

//Shift cipher
//Lowercase alphabets
//Modulo 26

string encrypt (string message , int key) {
    string  cipherText;
    for (int i = 0; i < message.size(); i++)
        cipherText += ((((((message[i] - 97) + key) % 26) + 26) % 26) + 97);

    return cipherText;
}

string decrypt (string cipherText , int key) {
    string  message;
    for (int i = 0; i < cipherText.size(); i++)
        message += ((((((cipherText[i] - 97) - key) % 26) + 26) % 26) + 97);

    return message;
}

int main() {

    string message = "wewillmeetatmidnight";
    string cipherText = "hphtwwxppelextoytrse";
    int key = 11;

    cout << encrypt (message , key) << endl;
    cout << decrypt (cipherText , key) << endl ;

    return 0;

}

```

# Affine cipher
```c
#include <bits/stdc++.h>
using namespace std;

//Affine cipher
//Lowercase alphabets
//Modulo 26

int getInverse (int key) {
       for (int i = 0; i < 26; i++) {
            if ( (key * i) % 26 == 1 )
                return i;
       }
    return -1;
}

string encrypt (string message , int key1 , int key2) {
    string  cipherText;
    for (int i = 0; i < message.size(); i++)
        cipherText += ((((((message[i] - 97) * key1) + key2) % 26) + 26) % 26 + 97);

    return cipherText;
}

string decrypt (string cipherText , int inverseOfKey1 , int key2) {
    string  message;
    for (int i = 0; i < cipherText.size(); i++)
        message += ((( inverseOfKey1 * ( (cipherText[i] - 97) - key2) % 26) + 26) % 26 + 97);

    return message;
}


int main() {

    string message = "hot";
    string cipherText = "axg";
    int key1 = 7;
    int key2 = 3;
    int inverseOfKey1 = getInverse(key1);

    cout << encrypt (message , key1 , key2) << endl;
    cout << ( inverseOfKey1 != -1 ? decrypt (cipherText , inverseOfKey1 , key2) : "There is no inverse for key1") << endl ;

}

```

# Substitution cipher
```c
#include <bits/stdc++.h>
using namespace std;

//Substitution  cipher
//Lowercase alphabets
//Modulo 26

string encrypt (string message , string key) {
    string  cipherText;
    for (int i = 0; i < message.size(); i++)
        cipherText += key[message[i] - 97] ;

    return cipherText;
}

string decrypt (string cipherText , string key) {
    string  message;
    for (int i = 0; i < cipherText.size(); i++)
        message += key[cipherText[i] - 97] ;

    return message;
}

int main() {

    string message = "right";
    string cipherText = "czogm";
    string encryptionKey = "xnyahpogzqwbtsflrcvmuekjdi";
    string decryptionKey = "diryvohezxqptbgfjqnmuskaci";

    cout << encrypt (message , encryptionKey) << endl;
    cout << decrypt (cipherText , decryptionKey) << endl ;

}

```
# Vigenere cipher
```c
#include <bits/stdc++.h>
using namespace std;

//Vigenere  cipher
//Lowercase alphabets
//Modulo 26

string encrypt (string message , string key) {
    string  cipherText;
    for (int i = 0; i < message.size(); i += key.size()) {
          for (int j = 0; j < key.size(); j++)
            cipherText += (((message[j + i] - 97) + (key[j] - 97)) % 26) + 97;
    }
    return cipherText;
}

string decrypt (string cipherText , string key) {
    string  message;
    for (int i = 0; i < cipherText.size(); i += key.size()) {
          for (int j = 0; j < key.size(); j++)
            message += (((((cipherText[j + i] - 97) - (key[j] - 97)) % 26) + 26 ) % 26) + 97;
    }
    return message;
}
int main() {

    string message = "tomorrowatthesunset";
    string cipherText = "vtnylttxknvmfcopxfd";
    string key = "cfbku";

    cout << "Encryption = " << encrypt (message , key) << endl;
    cout << "Decryption = " << decrypt (cipherText , key) << endl ;

}


```
# Hill cipher
```c
#include <bits/stdc++.h>
using namespace std;

//Hill  cipher
//Lowercase alphabets
//Modulo 26

int getInverse (int key) {
    for (int i = 0; i < 26; i++) {
        if ( (key * i) % 26 == 1 )
            return i;
    }
    return -1;
}

vector <vector<int>> getInverseMat (vector <vector <int> > key) {
    vector <vector<int>> inverseKey(2);
    int det = ((((key[0][0] * key[1][1]) - (key[0][1] * key[1][0])) % 26) + 26) % 26;
    int inverseDet = getInverse(det);

    inverseKey[0].push_back ((key[1][1]) * inverseDet);
    inverseKey[0].push_back ((((key[0][1] * -1 % 26) + 26) * inverseDet) % 26);
    inverseKey[1].push_back ((((key[1][0] * -1 % 26) + 26) * inverseDet) % 26);
    inverseKey[1].push_back ((key[0][0]) * inverseDet);

    return inverseKey;
}

string encrypt (string message, vector <vector <int> > key) {
    string  cipherText;
    for (int i = 0; i < message.size(); i += 2) {
        int col = 0;
        for (int j = 0; j < 2; j++) {
            cipherText += ((((message[i] - 97) * (key[0][col])) + ((message[i + 1] - 97) * (key[1][col]))) % 26) + 97;
            col++;
        }
    }
    return cipherText;
}

string decrypt (string cipherText, vector <vector <int>> key) {
    string  message;
    for (int i = 0; i < cipherText.size(); i += 2) {
        int col = 0;
        for (int j = 0; j < 2; j++) {
            message += ((((cipherText[i] - 97) * (key[0][col])) + ((cipherText[i + 1] - 97) * (key[1][col]))) % 26) + 97;
            col++;
        }
    }
    return message;
}

int main() {

    string message = "july";
    string cipherText = "delw";
    vector <vector<int>> encryptionKey =  {{ 11, 8 } , { 3, 7 }};
    vector <vector<int>> decryptionKey = getInverseMat(encryptionKey);

    cout << encrypt (message, encryptionKey) << endl;
    cout << decrypt (cipherText, decryptionKey) << endl ;

}


```

# Permutation cipher
```c
#include <bits/stdc++.h>
using namespace std;

//Permutation  cipher
//Lowercase alphabets
//Modulo 26

string encrypt (string message , vector<int> key) {
    string  cipherText;
    for (int i = 0; i < message.size(); i += key.size()) {
          for (int j = 0; j < key.size(); j++)
            cipherText += message[(key[j]) - 1 + i];
    }
    return cipherText;
}

string decrypt (string cipherText ,  vector<int> key) {
    string  message;
    for (int i = 0; i < cipherText.size(); i += key.size()) {
          for (int j = 0; j < key.size(); j++)
            message += cipherText[(key[j]) - 1 + i];
    }
    return message;
}
int main() {

    string message = "shesellsseashellsbytheseashore";
    string cipherText = "esaleshleshsselresetloebhsysah";
    vector<int> encryptionKey  = { 14 , 9 , 11 , 7 , 5 , 1 , 13 , 15 , 3 , 12 , 2 , 4 , 8 , 10 , 6};
    vector<int> decryptionKey  = { 6 , 11 , 9 , 12 , 5 , 15 , 4 , 13 , 2 , 14 , 3 , 10 , 7 , 1 , 8};


    cout << "Encryption  =  " << encrypt (message , encryptionKey) << endl;
    cout << "Decryption  =  " << decrypt (cipherText , decryptionKey) << endl ;

}

```
