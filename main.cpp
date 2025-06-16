#include "functions.cpp"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>

string toBin(int n, int sz){
    string bits = "";
    for(int i=sz-1; i >= 0; i--){
        bits += (char)(((n >> i) & 1) + '0');
    } 
    return bits;
}

int toInt(string bits, int sz){
    int num=0;
    for(int i=sz-1, j=0; i >= 0; i--, j++){
        if(bits[i] == '1') num |= (1 << j);
    } 
    return num;
}

vector<int> ECB(vector<int> box, int chave) {
    vector<int> cifrados;
    vector<int> chaves = expansaoChave(chave); // Gera as subchaves
    
    for (int bloco : box ) {
        // Cifra cada bloco independentemente
        int blocoCifrado = encripta(bloco, chaves);
        cifrados.push_back(blocoCifrado);
    }
    
    return cifrados;
}

int main(){
    
}