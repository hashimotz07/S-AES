#include <bits/stdc++.h>
using namespace std;

int addRoundKey(int estado_atual, int k0, int k1){
    int chave = (k0 << 8) | k1; //subchave
    return estado_atual ^ chave; 
}