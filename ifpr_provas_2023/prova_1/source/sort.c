#include <string.h>

#include "sort.h"

// =============================================================================
//
// NÃO ALTERE ABSOLUTAMENTE NADA NOS CABEÇALHOS (ASSINATURAS) DAS FUNÇÕES
//
// =============================================================================

static void trocar(int tamanhoString, char stringA[tamanhoString], char stringB[tamanhoString])
{
    char temporario[tamanhoString];

    memset(temporario, 0, (size_t)tamanhoString);

    memcpy(&temporario, stringA, (size_t)tamanhoString);
    memcpy(stringA, stringB, (size_t)tamanhoString);
    memcpy(stringB, temporario, (size_t)tamanhoString);
}

static int particionar(int quantidadeStrings, int tamanhoString, char strings[quantidadeStrings][tamanhoString], int inicio, int fim)
{
    int pivo = strings[fim][0];
    int i = inicio - 1;

    for (int j = inicio; j != quantidadeStrings - 1; j += 1)
    {
        if (strings[j][0] < pivo)
        {
            i += 1;
            trocar(tamanhoString, strings[i], strings[j]);
        }
    }

    if (pivo < strings[i + 1][0])
    {
        trocar(tamanhoString, strings[i + 1], strings[fim]);
    }

    return i + 1;
}

void ordenar(int quantidadeStrings, int tamanhoStrings, char strings[quantidadeStrings][tamanhoStrings], int inicio, int fim)
{
    if (inicio < fim)
    {
        int i = particionar(quantidadeStrings, tamanhoStrings, strings, inicio, fim);
        ordenar(quantidadeStrings, tamanhoStrings, strings, inicio, i - 1);
        ordenar(quantidadeStrings, tamanhoStrings, strings, i + 1, fim);
    }
}

