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
        
    }
}

int addRoundKey(int estado_atual, int k0, int k1){
    int chave = (k0 << 8) | k1; //subchave
    return estado_atual ^ chave; 
}