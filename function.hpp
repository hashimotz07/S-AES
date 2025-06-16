#ifndef S_AES_HPP
#define S_AES_HPP

#include <bits/stdc++.h>
using namespace std;
// S-Box constante
extern const vector<int> sbox;

/**
 * @brief Multiplicação no corpo GF(2^4) com polinômio irredutível x^4 + x + 1
 * @param a Primeiro operando (4 bits)
 * @param b Segundo operando (4 bits)
 * @return Resultado da multiplicação (4 bits)
 */
int GF(int a, int b);

/**
 * @brief Operação MixColumns
 * @param estado Estado atual de 16 bits
 * @return Novo estado após MixColumns
 */
int mixColumns(int estado);

/**
 * @brief Substitui 2 nibbles usando a S-Box
 * @param chave Byte de entrada (8 bits)
 * @return Byte com nibbles substituídos
 */
int subNibble(int chave);

/**
 * @brief Inverte a ordem dos nibbles em um byte
 * @param nibble Byte de entrada (8 bits)
 * @return Byte com nibbles invertidos
 */
int giraNibble(int nibble);

/**
 * @brief Expansão de chave para gerar subchaves
 * @param chave Chave principal de 16 bits
 * @return Vetor com 6 subchaves geradas
 */
vector<int> expansaoChave(int chave);

/**
 * @brief Operação ShiftRows
 * @param input Estado atual de 16 bits
 * @return Novo estado após ShiftRows
 */
int shiftRows(int input);

/**
 * @brief Adiciona a chave de rodada ao estado (XOR)
 * @param estado_atual Estado atual de 16 bits
 * @param k0 Primeiro byte da subchave
 * @param k1 Segundo byte da subchave
 * @return Novo estado após AddRoundKey
 */
int addRoundKey(int estado_atual, int k0, int k1);

/**
 * @brief Função principal de encriptação S-AES
 * @param plaintext Texto claro de 16 bits
 * @param chaves Vetor de subchaves expandidas
 * @return Texto cifrado de 16 bits
 */
int encripta(int plaintext, vector<int>& chaves);

#endif // S_AES_HPP