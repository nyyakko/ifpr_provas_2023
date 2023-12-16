#include <string.h>

#include "sort.h"

// protótipos de funções de suporte (usadas somente neste código fonte)
// =============================================================================
//
// NÃO ALTERE ABSOLUTAMENTE NADA NOS CABEÇALHOS (ASSINATURAS) DAS FUNÇÕES
//
// =============================================================================
int particionar(int max_items, int item_len, char arr[max_items][item_len], int inicio, int fim);

void trocar(int item_len, char s1[item_len], char s2[item_len]);

// =============================================================================
//
// NÃO ALTERE ABSOLUTAMENTE NADA NOS CABEÇALHOS (ASSINATURAS) DAS FUNÇÕES
//
// =============================================================================
void ordenar(int max_items, int item_len, char arr[max_items][item_len], int inicio, int fim)
{
    if (inicio < fim)
    {
        int p = particionar(max_items, item_len, arr, inicio, fim);
        ordenar(max_items, item_len, arr, inicio, p - 1);
        ordenar(max_items, item_len, arr, p + 1, fim);
    }
}

int particionar(int max_items, int item_len, char arr[max_items][item_len], int inicio, int fim)
{
    int pivot = arr[fim][0];
    int i = inicio - 1;

    for (int j = inicio; j != max_items - 1; j += 1)
    {
        if (arr[j][0] < pivot)
        {
            i += 1;
            trocar(item_len, arr[i], arr[j]);
        }
    }

    if (pivot < arr[i + 1][0])
    {
        trocar(item_len, arr[i + 1], arr[fim]);
    }

    return i + 1;
}

void trocar(int item_len, char s1[item_len], char s2[item_len])
{
    char temp[item_len];

    memset(temp, 0, (size_t)item_len);

    memcpy(&temp, s1, (size_t)item_len);
    memcpy(s1, s2, (size_t)item_len);
    memcpy(s2, temp, (size_t)item_len);
}
