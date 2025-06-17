#include "modes.cpp"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/cryptlib.h>

using namespace CryptoPP;

// Função para imprimir texto em hexadecimal
void imprimirHex(const string& titulo, const string& texto) {
    string codificado;
    StringSource(texto, true, new HexEncoder(new StringSink(codificado)));
    cout << titulo << ": " << codificado << endl;
}

// ECB
void modoECB(const string& mensagem, const SecByteBlock& chave) {
    string cifrado;

    ECB_Mode<AES>::Encryption enc;
    enc.SetKey(chave, chave.size());
    StringSource(mensagem, true, new StreamTransformationFilter(enc, new StringSink(cifrado)));

    cout << "\n== ECB ==" << endl;
    imprimirHex("Cifrado", cifrado);
}

// CBC
void modoCBC(const string& mensagem, const SecByteBlock& chave, const CryptoPP::byte* iv) {
    string cifrado;

    CBC_Mode<AES>::Encryption enc;
    enc.SetKeyWithIV(chave, chave.size(), iv);
    StringSource(mensagem, true, new StreamTransformationFilter(enc, new StringSink(cifrado)));

    cout << "\n== CBC ==" << endl;
    imprimirHex("Cifrado", cifrado);
}

// CFB
void modoCFB(const string& mensagem, const SecByteBlock& chave, CryptoPP::byte* iv) {
    string cifrado;

    CFB_Mode<AES>::Encryption enc;
    enc.SetKeyWithIV(chave, chave.size(), iv);
    StringSource(mensagem, true, new StreamTransformationFilter(enc, new StringSink(cifrado)));

    cout << "\n== CFB ==" << endl;
    imprimirHex("Cifrado", cifrado);
}

// OFB
void modoOFB(const string& mensagem, const SecByteBlock& chave, CryptoPP::byte* iv) {
    string cifrado;

    OFB_Mode<AES>::Encryption enc;
    enc.SetKeyWithIV(chave, chave.size(), iv);
    StringSource(mensagem, true, new StreamTransformationFilter(enc, new StringSink(cifrado)));

    cout << "\n== OFB ==" << endl;
    imprimirHex("Cifrado", cifrado);
}

// CTR
void modoCTR(const string& mensagem, const SecByteBlock& chave, CryptoPP::byte* iv) {
    string cifrado;

    CTR_Mode<AES>::Encryption enc;
    enc.SetKeyWithIV(chave, chave.size(), iv);
    StringSource(mensagem, true, new StreamTransformationFilter(enc, new StringSink(cifrado)));

    cout << "\n== CTR ==" << endl;
    imprimirHex("Cifrado", cifrado);
}

string blocosParaString(const vector<int>& blocos) {
    string resultado;
    for (int bloco : blocos) {
        // Supondo blocos de 16 bits -> 2 bytes por bloco, big endian
        char byte1 = (bloco >> 8) & 0xFF;
        char byte2 = bloco & 0xFF;
        resultado.push_back(byte1);
        resultado.push_back(byte2);
    }
    return resultado;
}

int main(){
    cout << "modo ecb sem uso de biblioteca\n\n";
    vector<int> box = {0b1100101011110001, 0b0110111001001100};
    int chave = 0b0100101011110101; 
    

    vector<int> ecb = ECB(box, chave);
    for (int i = 0; i < ecb.size(); i++) {
        cout << "Bloco " << i + 1 << ": " << toBin(ecb[i], 16) << endl;
    }

    string texto = blocosParaString(box);
    SecByteBlock chaveCrypto(16);
    for (int i = 0; i < 8; i++) {   
        chaveCrypto[i*2] = (chave >> 8) & 0xFF;
        chaveCrypto[i*2+1] = chave & 0xFF;
    }

    CryptoPP::byte iv[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                   0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    cout << "\nmodos de operação com biblioteca Crypto++\n";

    modoECB(texto, chaveCrypto);
    modoCBC(texto, chaveCrypto, iv);
    modoCFB(texto, chaveCrypto, iv);
    modoOFB(texto, chaveCrypto, iv);
    modoCTR(texto, chaveCrypto, iv);

    return 0;
}