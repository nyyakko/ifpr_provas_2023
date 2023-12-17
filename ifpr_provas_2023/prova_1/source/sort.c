#include <string.h>

#include "sort.h"

// =============================================================================
//
// NÃO ALTERE ABSOLUTAMENTE NADA NOS CABEÇALHOS (ASSINATURAS) DAS FUNÇÕES
//
// =============================================================================

static void trocar(char stringA_o[CPF_LEN], char stringB_o[CPF_LEN])
{
    char temporario[CPF_LEN];

    memset(temporario, 0, (size_t)CPF_LEN);

    memcpy(&temporario, stringA_o, (size_t)CPF_LEN);
    memcpy(stringA_o, stringB_o, (size_t)CPF_LEN);
    memcpy(stringB_o, temporario, (size_t)CPF_LEN);
}

static int particionar(int quantidadeStrings, char strings_o[quantidadeStrings][CPF_LEN], int inicio, int fim)
{
    int pivo = strings_o[fim][0];
    int i = inicio - 1;

    for (int j = inicio; j != quantidadeStrings - 1; j += 1)
    {
        if (strings_o[j][0] < pivo)
        {
            i += 1;
            trocar(strings_o[i], strings_o[j]);
        }
    }

    if (pivo < strings_o[i + 1][0])
    {
        trocar(strings_o[i + 1], strings_o[fim]);
    }

    return i + 1;
}

void ordenar(int quantidadeStrings, char strings_o[quantidadeStrings][CPF_LEN], int inicio, int fim)
{
    if (inicio < fim)
    {
        int i = particionar(quantidadeStrings, strings_o, inicio, fim);
        ordenar(quantidadeStrings, strings_o, inicio, i - 1);
        ordenar(quantidadeStrings, strings_o, i + 1, fim);
    }
}

