#include <bits/stdc++.h>
#include <bitset>
using namespace std;

//s-box
vector<int> sbox{9, 4, 10, 11, 13, 1, 8, 5, 6, 2, 0, 3, 12, 14, 15, 7};

int GF(int a, int b){
    int resultado = 0;
    while(b){
        int formula = 19; //x**4 + x + 1

        if(b & 1)
            resultado ^= a;
        a <<= 1;
        if(a & 16)
            a ^= 19;
        b >>=1;
    }
    return resultado & 15;
}

int mixColumns(int estado){
    int s0 = (estado >> 12) & 15;
    int s1 = (estado >> 8) & 15;
    int s2 = (estado >> 4) & 15;
    int s3 = (estado & 15);

    int t0 = GF(1, s0) ^ GF(4, s2);
    int t1 = GF(1, s1) ^ GF(4, s3);
    int t2 = GF(4, s0) ^ GF(1, s2);
    int t3 = GF(4, s1) ^ GF(1, s3);

    return (t0 << 12) | (t1 << 8) | (t2 << 4) | t3;
}

//substitui 2 nibbles
int subNibble(int chave){
    return (sbox[chave >> 4] << 4) | (sbox[chave & 15]);
}

//inverte os nibbles
int giraNibble(int nibble){
    return (nibble << 4) | (nibble >> 4);
}

int subNibble16(int chave){
    int resultado = 0;
    for(int i = 0; i < 4; i++){
        resultado |= (sbox[(chave >> (i * 4)) & 15] << (i * 4));
    }
    return resultado;
}

vector<int> expansaoChave(int chave){
    vector<int> v(6, 0);
    v[0] = (chave >> 8) & 255; //byte mais significativo
    v[1] = chave & 255; //byte menos significativo
    //
    v[2] = v[0] ^ 128 ^ subNibble(giraNibble(v[1]));
    v[3] = v[2] ^ v[1];
    //
    v[4] = v[2] ^ 48 ^ subNibble(giraNibble(v[3]));
    v[5] = v[4] ^ v[3];

    return v;
}

int shiftRows(int input){
    int s0 = (input >> 12) & 15;
    int s1 = (input >> 8) & 15;
    int s2 = (input >> 4) & 15;
    int s3 = (input & 15);

    return (s0 << 12) | (s3 << 8) | (s2 << 4) | s1; 
}

int addRoundKey(int estado_atual, int k0, int k1){
    int chave = (k0 << 8) | k1; //subchave
    return estado_atual ^ chave; 
}

int encripta(int plaintext,  vector<int>& chaves) {
    int estado = plaintext;
    
    //rodada inicial
    estado ^= chaves[0];
    
    //rodada 1
    estado = subNibble(estado);
    estado = shiftRows(estado);
    estado = mixColumns(estado);
    estado ^= chaves[1];
    
    //rodada 2
    estado = subNibble(estado);
    estado = shiftRows(estado);
    estado ^= chaves[2];
    
    return estado;
}
