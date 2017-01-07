/*
 * File:   main.cpp
 * Author: Josef
 *
 * Created on 16. brezna 2016, 9:19
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>

using namespace std;

const char lookup[32] =
     {0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0};

string HEX2STR(string str)
{
  string out;
  out.reserve(str.size()/2);

  const char* tmp = str.c_str();
  unsigned char ch, last = 1;
  while(*tmp)
  {
    ch <<= 4;
    ch |= lookup[*tmp&0x1f];
    if(last ^= 1)
      out += ch;
    tmp++;
  }
  return out;
}

void STRING2HEX (const string &text){
    for(int i = 0 ; i < text.length() ; i++) cout<<hex<<(int)text[i];
    cout << endl;
}


int main(void) {

    cout << "Zadejte > priklad 1 :           1" << endl
         << "        > priklad 2 :           2" << endl
         << "        > prevod hex na ascii : 3" << endl
         << "        > prevod ascii na hex : 4" << endl;

    int m_prob;
    cin >> m_prob;


//priklad1
    if (m_prob == 1){
           char m_dec[100];
           string m_hex1 = "fc57c9cfdac7202694e8c2712d1f0e8e21b8c6f6d612d6c96847e42e6257b3f9ea98466cfc8761ed5e0308311deb15";
           string m_hex2 = "a83fa0bcfaae5306f5c8b1144e6d6bfa01cca38ea23cf68707258b4a1b77c09185ed2a08dcf5048c3a237c5974983b";
           string m_dec1 = HEX2STR(m_hex1);
           string m_dec2 = HEX2STR(m_hex2);

           for (int i = 0; i<m_dec1.length(); i++) m_dec[i] = (m_dec1[i] xor m_dec2[i]);
           for (int i = 0; i<m_dec1.length(); i++) cout << m_dec[i];
           cout << endl;
    }

//priklad2
    else if (m_prob == 2) STRING2HEX ("Test string");

// 3 - prevod hex cisla na ASCII
    else if (m_prob == 3){
        string m_hex;
        cout << "Zadejte hexadecimalni cislo.";
        cin >> m_hex;
        cout << "ASCII: " << HEX2STR(m_hex) << endl;
    }

// 4 - prevod ASCII na HEX
    else if (m_prob == 4){
        string tmp;
        string m_ascii;
        cout << "Zadejte retezec v ASCII kodovani." << endl;
        getline(cin,tmp, '\n');
        getline(cin, m_ascii, '\n');
        STRING2HEX(m_ascii);
    }

    else{
        cout << "Segmentation fault" << endl;
        return -10756238;
    }
    return 0;
}
