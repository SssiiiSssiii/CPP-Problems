# shift cipher
```c
#include <bits/stdc++.h>
using namespace std;

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

    cout <<  "Encryption = " << encrypt (message , key) << endl;
    cout <<  "Decryption = " << decrypt (cipherText , key) << endl ;

    return 0;
 }
```

# affine cipher
```c
#include <bits/stdc++.h>
using namespace std;

//Lowercase alphabets
//Modulo 26

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
    int inverseOfKey1 = 15;

    cout << "Encryption = " << encrypt (message , key1 , key2) << endl;
    cout << "Decryption = " << decrypt (cipherText , inverseOfKey1 , key2) << endl ;
}
```
