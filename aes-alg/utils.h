#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Enumeração para o tipo de operação (criptografar ou descriptografar)
enum OperationType
{
    Encrypt = 1,
    Decrypt = -1
};

// Tabela de substituição (S-Box) usada na criptografia AES
const unsigned char sBox[16][16] = {
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
    {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
    {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
    {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
    {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
    {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
    {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
    {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
    {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
    {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}};

// Tabela de substituição inversa (S-Box inversa) usada na descriptografia AES
const unsigned char invSBox[16][16] = {
    {0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB},
    {0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB},
    {0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E},
    {0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25},
    {0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92},
    {0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84},
    {0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06},
    {0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B},
    {0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73},
    {0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E},
    {0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B},
    {0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4},
    {0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F},
    {0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF},
    {0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D}};
;

// Matriz de multiplicação usada na etapa de MixColumns para criptografia
const unsigned char multiplicationMatrixEncrypt[4][4] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}};

// Matriz de multiplicação usada na etapa de MixColumns para descriptografia
const unsigned char multiplicationMatrixDecrypt[4][4] = {
    {0x0E, 0x0B, 0x0D, 0x09},
    {0x09, 0x0E, 0x0B, 0x0D},
    {0x0D, 0x09, 0x0E, 0x0B},
    {0x0B, 0x0D, 0x09, 0x0E}};

// Tabela de substituição usada na etapa de MixColumns para criptografia
const unsigned char eTable[16][16] = {
    {0x01, 0x03, 0x05, 0x0F, 0x11, 0x33, 0x55, 0xFF, 0x1A, 0x2E, 0x72, 0x96, 0xA1, 0xF8, 0x13, 0x35},
    {0x5F, 0xE1, 0x38, 0x48, 0xD8, 0x73, 0x95, 0xA4, 0xF7, 0x02, 0x06, 0x0A, 0x1E, 0x22, 0x66, 0xAA},
    {0xE5, 0x34, 0x5C, 0xE4, 0x37, 0x59, 0xEB, 0x26, 0x6A, 0xBE, 0xD9, 0x70, 0x90, 0xAB, 0xE6, 0x31},
    {0x53, 0xF5, 0x04, 0x0C, 0x14, 0x3C, 0x44, 0xCC, 0x4F, 0xD1, 0x68, 0xB8, 0xD3, 0x6E, 0xB2, 0xCD},
    {0x4C, 0xD4, 0x67, 0xA9, 0xE0, 0x3B, 0x4D, 0xD7, 0x62, 0xA6, 0xF1, 0x08, 0x18, 0x28, 0x78, 0x88},
    {0x83, 0x9E, 0xB9, 0xD0, 0x6B, 0xBD, 0xDC, 0x7F, 0x81, 0x98, 0xB3, 0xCE, 0x49, 0xDB, 0x76, 0x9A},
    {0xB5, 0xC4, 0x57, 0xF9, 0x10, 0x30, 0x50, 0xF0, 0x0B, 0x1D, 0x27, 0x69, 0xBB, 0xD6, 0x61, 0xA3},
    {0xFE, 0x19, 0x2B, 0x7D, 0x87, 0x92, 0xAD, 0xEC, 0x2F, 0x71, 0x93, 0xAE, 0xE9, 0x20, 0x60, 0xA0},
    {0xFB, 0x16, 0x3A, 0x4E, 0xD2, 0x6D, 0xB7, 0xC2, 0x5D, 0xE7, 0x32, 0x56, 0xFA, 0x15, 0x3F, 0x41},
    {0xC3, 0x5E, 0xE2, 0x3D, 0x47, 0xC9, 0x40, 0xC0, 0x5B, 0xED, 0x2C, 0x74, 0x9C, 0xBF, 0xDA, 0x75},
    {0x9F, 0xBA, 0xD5, 0x64, 0xAC, 0xEF, 0x2A, 0x7E, 0x82, 0x9D, 0xBC, 0xDF, 0x7A, 0x8E, 0x89, 0x80},
    {0x9B, 0xB6, 0xC1, 0x58, 0xE8, 0x23, 0x65, 0xAF, 0xEA, 0x25, 0x6F, 0xB1, 0xC8, 0x43, 0xC5, 0x54},
    {0xFC, 0x1F, 0x21, 0x63, 0xA5, 0xF4, 0x07, 0x09, 0x1B, 0x2D, 0x77, 0x99, 0xB0, 0xCB, 0x46, 0xCA},
    {0x45, 0xCF, 0x4A, 0xDE, 0x79, 0x8B, 0x86, 0x91, 0xA8, 0xE3, 0x3E, 0x42, 0xC6, 0x51, 0xF3, 0x0E},
    {0x12, 0x36, 0x5A, 0xEE, 0x29, 0x7B, 0x8D, 0x8C, 0x8F, 0x8A, 0x85, 0x94, 0xA7, 0xF2, 0x0D, 0x17},
    {0x39, 0x4B, 0xDD, 0x7C, 0x84, 0x97, 0xA2, 0xFD, 0x1C, 0x24, 0x6C, 0xB4, 0xC7, 0x52, 0xF6, 0x01}};

// Tabela de substituição usada na etapa de MixColumns para descriptografia
const unsigned char lTable[16][16] = {
    {0x00, 0x00, 0x19, 0x01, 0x32, 0x02, 0x1A, 0xC6, 0x4B, 0xC7, 0x1B, 0x68, 0x33, 0xEE, 0xDF, 0x03},
    {0x64, 0x04, 0xE0, 0x0E, 0x34, 0x8D, 0x81, 0xEF, 0x4C, 0x71, 0x08, 0xC8, 0xF8, 0x69, 0x1C, 0xC1},
    {0x7D, 0xC2, 0x1D, 0xB5, 0xF9, 0xB9, 0x27, 0x6A, 0x4D, 0xE4, 0xA6, 0x72, 0x9A, 0xC9, 0x09, 0x78},
    {0x65, 0x2F, 0x8A, 0x05, 0x21, 0x0F, 0xE1, 0x24, 0x12, 0xF0, 0x82, 0x45, 0x35, 0x93, 0xDA, 0x8E},
    {0x96, 0x8F, 0xDB, 0xBD, 0x36, 0xD0, 0xCE, 0x94, 0x13, 0x5C, 0xD2, 0xF1, 0x40, 0x46, 0x83, 0x38},
    {0x66, 0xDD, 0xFD, 0x30, 0xBF, 0x06, 0x8B, 0x62, 0xB3, 0x25, 0xE2, 0x98, 0x22, 0x88, 0x91, 0x10},
    {0x7E, 0x6E, 0x48, 0xC3, 0xA3, 0xB6, 0x1E, 0x42, 0x3A, 0x6B, 0x28, 0x54, 0xFA, 0x85, 0x3D, 0xBA},
    {0x2B, 0x79, 0x0A, 0x15, 0x9B, 0x9F, 0x5E, 0xCA, 0x4E, 0xD4, 0xAC, 0xE5, 0xF3, 0x73, 0xA7, 0x57},
    {0xAF, 0x58, 0xA8, 0x50, 0xF4, 0xEA, 0xD6, 0x74, 0x4F, 0xAE, 0xE9, 0xD5, 0xE7, 0xE6, 0xAD, 0xE8},
    {0x2C, 0xD7, 0x75, 0x7A, 0xEB, 0x16, 0x0B, 0xF5, 0x59, 0xCB, 0x5F, 0xB0, 0x9C, 0xA9, 0x51, 0xA0},
    {0x7F, 0x0C, 0xF6, 0x6F, 0x17, 0xC4, 0x49, 0xEC, 0xD8, 0x43, 0x1F, 0x2D, 0xA4, 0x76, 0x7B, 0xB7},
    {0xCC, 0xBB, 0x3E, 0x5A, 0xFB, 0x60, 0xB1, 0x86, 0x3B, 0x52, 0xA1, 0x6C, 0xAA, 0x55, 0x29, 0x9D},
    {0x97, 0xB2, 0x87, 0x90, 0x61, 0xBE, 0xDC, 0xFC, 0xBC, 0x95, 0xCF, 0xCD, 0x37, 0x3F, 0x5B, 0xD1},
    {0x53, 0x39, 0x84, 0x3C, 0x41, 0xA2, 0x6D, 0x47, 0x14, 0x2A, 0x9E, 0x5D, 0x56, 0xF2, 0xD3, 0xAB},
    {0x44, 0x11, 0x92, 0xD9, 0x23, 0x20, 0x2E, 0x89, 0xB4, 0x7C, 0xB8, 0x26, 0x77, 0x99, 0xE3, 0xA5},
    {0x67, 0x4A, 0xED, 0xDE, 0xC5, 0x31, 0xFE, 0x18, 0x0D, 0x63, 0x8C, 0x80, 0xC0, 0xF7, 0x70, 0x07}};

/**
 * @brief Função que extrai os valores de x (primeiros 4 bits a esquerda) e y (ultimos 4 bits) de um número hexadecimal.
 * @param hex O número hexadecimal a ser extraído.
 * @param x O valor de x a ser retornado.
 * @param y O valor de y a ser retornado.
 * @return void - Os valores de x e y são retornados por referência.
 */
void extractXY(unsigned char hex, int *x, int *y)
{
    // Extrai o primeiro dígito (4 bits mais significativos) como x
    *x = (hex >> 4) & 0xF;

    // Extrai o segundo dígito (4 bits menos significativos) como y
    *y = hex & 0xF;
}

/**
 * @brief Realoca a memória de um vetor com um ponteiro para ponteiro.
 *
 * Esta função realoca a memória do vetor representado por um ponteiro para ponteiro
 * para o novo tamanho especificado. Se a realocação for bem-sucedida, o ponteiro
 * original é atualizado para apontar para a nova memória alocada. Caso contrário,
 * uma mensagem de erro é exibida.
 *
 * @param[in,out] vector O ponteiro para ponteiro que representa o vetor a ser realocado.
 * @param[in] newVectorSize O novo tamanho desejado para o vetor.
 */
int reallocMemory(unsigned char **vector, uint32_t newVectorSize)
{
    unsigned char *newVector = (unsigned char *)realloc(*vector, newVectorSize * sizeof(unsigned char));
    if (newVector != NULL)
    {
        *vector = newVector; // Atualiza o ponteiro original
    }
    else
    {
        printf("Algo deu errado ao realocar a memória.\n");
        return 1;
    }
    return 0;
}

/**
 * @brief Obtém um valor da tabela E ou L com base no valor fornecido.
 *
 * Esta função obtém um valor da tabela E ou L com base em um valor de entrada `n`.
 * A tabela usada é especificada pelo parâmetro `table`.
 *
 * @param[in] n O valor de entrada.
 * @param[in] table A tabela a ser usada (E ou L).
 * @return O valor correspondente da tabela.
 */
unsigned char getEorLValue(unsigned char n, const unsigned char (*table)[16])
{
    int x, y;
    extractXY(n, &x, &y);

    return table[x][y];
}

/**
 * @brief Remove bytes de um vetor de dados.
 *
 * Esta função remove um número especificado de bytes de um vetor de dados.
 * Os bytes a serem removidos são especificados pelo parâmetro `bytesToRemove`.
 *
 * @param[in,out] data O ponteiro para o vetor de dados.
 * @param[in] dataSize O tamanho atual do vetor de dados.
 * @param[in] bytesToRemove O número de bytes a serem removidos.
 */
void removeBytes(unsigned char **data, uint32_t dataSize, short bytesToRemove)
{
    uint32_t vectorSize = dataSize + bytesToRemove;
    // Inicie a partir da posição onde os bytes devem ser removidos
    size_t copySize = vectorSize - bytesToRemove; // Tamanho do trecho a ser copiado

    // Usando memcpy para copiar o trecho de data
    memcpy(*data, *data + bytesToRemove, copySize);
    // realloc
    reallocMemory(data, copySize);
}

/**
 * @brief Obtém o tamanho da chave a partir de uma string de chave.
 *
 * Esta função calcula o tamanho da chave com base na string de chave fornecida.
 *
 * @param[in] key A string de chave.
 * @return O tamanho da chave.
 */
short getKeyLength(const char *key)
{
    if (key == NULL)
    {
        printf("Erro ao obter o tamanho da chave.\n");
        return -1;
    }

    return (short)strlen(key);
}

/**
 * @brief Obtém o tamanho mais próximo para a chave com base em um valor x.
 *
 * Esta função retorna o tamanho de chave mais próximo com base em um valor x fornecido.
 *
 * @param[in] x O valor usado para determinar o tamanho da chave.
 * @return O tamanho de chave mais próximo.
 */
unsigned char getNearestKeySize(unsigned char x)
{
    if (x <= 16)
    {
        return 16;
    }
    else if (x <= 24)
    {
        return 24;
    }
    else
    {
        return 32;
    }
}

/**
 * @brief Converte um array de bytes em um valor uint32_t.
 *
 * Esta função converte um array de 4 bytes em um valor uint32_t.
 *
 * @param[in] byteArray O array de bytes a ser convertido.
 * @return O valor uint32_t resultante.
 */
uint32_t bytesToUInt(const unsigned char byteArray[4])
{
    uint32_t value = 0;
    value |= ((uint32_t)byteArray[0] << 24);
    value |= ((uint32_t)byteArray[1] << 16);
    value |= ((uint32_t)byteArray[2] << 8);
    value |= byteArray[3];
    return value;
}

/**
 * @brief Converte um valor uint32_t em um array de bytes.
 *
 * Esta função converte um valor uint32_t em um array de 4 bytes.
 *
 * @param[in] value O valor uint32_t a ser convertido.
 * @param[out] byteArray O array de bytes resultante.
 */
void uintToBytes(uint32_t value, unsigned char byteArray[4])
{
    byteArray[0] = (value >> 24) & 0xFF;
    byteArray[1] = (value >> 16) & 0xFF;
    byteArray[2] = (value >> 8) & 0xFF;
    byteArray[3] = value & 0xFF;
}

/**
 * @brief Obtém o número de rodadas com base no tamanho da chave.
 *
 * Esta função determina o número de rodadas com base no tamanho da chave.
 *
 * @param[in] keyLength O tamanho da chave.
 * @return O número de rodadas.
 */
short getRoundsCount(short keyLength)
{
    switch (keyLength)
    {
    case 16:
        return 10;
    case 24:
        return 12;
    case 32:
        return 14;
    default:
        return -1;
    }
}

/**
 * @brief Converte uma string em um vetor de bytes e armazena-o em um vetor de dados.
 *
 * Esta função converte uma string em um vetor de bytes e armazena-o no vetor de dados fornecido. Ela também redimensiona o vetor de dados, se necessário, para acomodar os bytes da string.
 *
 * @param text A string a ser convertida em bytes.
 * @param vectorSize O tamanho atual do vetor de dados.
 * @param data Um ponteiro para o vetor de dados onde os bytes da string serão armazenados.
 * @param start A posição inicial no vetor de dados para armazenar os bytes da string.
 */
void stringToBytes(const char *text, size_t vectorSize, unsigned char **data, uint32_t start)
{
    if (reallocMemory(data, vectorSize) == 0)
    {
        for (size_t i = start; i < vectorSize; i++)
        {
            (*data)[i] = (unsigned char)text[i - start];
        }
    }
}

/**
 * @brief Converte um vetor de bytes em uma string.
 *
 * Esta função aloca memória para uma string e copia os bytes do vetor para a string, incluindo o caractere nulo '\0' no final.
 *
 * @param bytes Um ponteiro para o vetor de bytes a ser convertido em uma string.
 * @param size O tamanho do vetor de bytes.
 * @return Um ponteiro para a string recém-criada. O chamador é responsável por liberar a memória alocada quando não precisar mais da string.
 *
 * @note Certifique-se de liberar a memória alocada para a string usando a função `free` quando não precisar mais dela.
 */
char *bytesToString(const unsigned char *bytes, size_t size)
{
    // Aloca memória para a string, incluindo espaço para o caractere nulo '\0'
    char *str = (char *)malloc(size + 1);

    if (str == NULL)
    {
        return NULL; // Erro de alocação de memória
    }

    // Copia os bytes para a string
    memcpy(str, bytes, size);

    // Adiciona o caractere nulo ao final da string
    str[size] = '\0';

    return str;
}

/**
 * @brief Adiciona um prefixo de tamanho a um vetor de bytes.
 *
 * Esta função aloca memória para um novo vetor de bytes que contém um prefixo
 * de 4 bytes representando a quantidade de bytes em data
 *
 * @param data O ponteiro para o vetor de bytes.
 * @param dataSize o tamanho dos dados
 *
 * @return 1 se a operação for bem-sucedida, 0 caso contrário.
 */
int addSizePrefix(unsigned char **data, size_t dataSize)
{
    unsigned char bytes[4];
    if (reallocMemory(data, dataSize + 4) == 0)
    {
        // Adiciona a contagem de bytes no início
        uintToBytes((uint32_t)dataSize, bytes);

        // Copia os bytes de contagem no início
        memcpy(*data, bytes, 4);
        return 1;
    }
    return 0;
}

void removeSizePrefix(unsigned char **data)
{
    if (*data == NULL)
    {
        return;
    }

    // Obtém o tamanho a partir dos primeiros 4 bytes
    uint32_t size = bytesToUInt(*data);

    if (size >= 4)
    {
        // Remove os primeiros 4 bytes
        removeBytes(data, size, 4);
    }
}

#endif