// =============================================================================
// Nome(s) completo(s) do(s) aluno(a)(s)
// Se há somente um aluno, apague a linha "Aluno(a) 2:"
//
// Aluno 1:
// Aluno 2:
//
// =============================================================================

#include <stdio.h>
#include <string.h>

#include "cpf.h"
#include "main.h"
#include "sort.h"

// =============================================================================
//
// NÃO ALTERE ABSOLUTAMENTE NADA NESTE ARQUIVO
//
// =============================================================================

// =============================================================================
// Esta função recebe vários parâmetros, a saber:
// max_items      : quantidade de elementos na matriz de strings "cpfs"
// item_len       : comprimento de cada string em "cpfs"
// cpfs           : matriz com os CPFs a validar
// cpfs_validos   : matriz na qual a função armazenará os CPFs válidos
// cpfs_invalidos : matriz na qual a função armazenará os CPFs inválidos
// total_alidos   : quantidade de CPFs válidos
// total_invalidos: quantidade de CPFs inválidos
// =============================================================================

void validar_cpfs(int max_items, int item_len, char cpfs[max_items][item_len], char cpfs_validos[max_items][item_len],
                  char cpfs_invalidos[max_items][item_len], int *total_validos, int *total_invalidos)
{
    char fcpf[item_len + 3];

    memset(fcpf, 0, item_len + 3);

    *total_validos = 0;

    for (int i = 0; i != max_items; i += 1)
    {
        int result = validar_cpf(item_len, cpfs[i]);

        char estados[ESTADOS_LEN] = {0};

        switch (result)
        {
        case CPF_OK:
            formatar_cpf(item_len, cpfs[i], fcpf);
            estado_cpf(item_len, cpfs[i], ESTADOS_LEN, estados);
            printf("CPF %s\tvalido, Estado(s): %s\n", fcpf, estados);
            strcpy_s(cpfs_validos[(*total_validos)++], item_len, cpfs[i]);
            break;
        case CPF_DV1: printf("CPF %s\t\tErro no DV1\n", cpfs[i]); break;
        case CPF_DV2: printf("CPF %s\t\tErro no DV2\n", cpfs[i]); break;
        case CPF_LEN: printf("CPF %s\t\tNão tem 11 digitos\n", cpfs[i]); break;
        case CPF_SAM: printf("CPF %s\t\tCom todos os digitos iguais\n", cpfs[i]); break;
        case CPF_ERR: printf("CPF %s\t\tErro desconhecido\n", cpfs[i]); break;
        }

        if (result != CPF_OK)
        {
            strcpy_s(cpfs_invalidos[(*total_invalidos)++], item_len, cpfs[i]);
        }
    }
}

// =============================================================================
// percorre a matriz "arr" exibindo seu valor e a posição na qual ele se
// encontra
// =============================================================================

void mostrar(int max_items, int item_len, char arr[max_items][item_len])
{
    for (int i = 0; i != max_items; i += 1)
    {
        printf("[%2d]: %s\n", i + 1, arr[i]);
    }
}

int main()
{
    // CPFs obtidos em https://www.4devs.com.br/gerador_de_cpf

#if 1
    // matriz de CPFs válidos
    char cpfs[MAX_ITEMS][ITEM_LEN] =
    {
        "40207576238", // 0
        "41964254027", // 1
        "21525127586", // 2
        "59514776119", // 3
        "52638407488", // 4
        "04312239207", // 5
        "61716975166", // 6
        "52399494920", // 7
        "93123217655", // 8
        "28739553922", // 9
    };
#else
    // matriz de CPFs contendo 5 válidos e 5 inválidos
    char cpfs[MAX_ITEMS][ITEM_LEN] =
    {
        "40207576238", // 0
        "41964254007", // 1
        "21525127586", // 2
        "59514776110", // 3
        "52638407488", // 4
        "043122392",   // 5
        "61716975166", // 6
        "55555555555", // 7
        "93123217655", // 8
        "287395539a2"  // 9
    };
#endif

    char cpfs_validos[MAX_ITEMS][ITEM_LEN] = {0};
    char cpfs_invalidos[MAX_ITEMS][ITEM_LEN] = {0};
    int total_validos = 0;
    int total_invalidos = 0;

    // seção para validar CPFs
    printf("===> VALIDAR CPFs <===\n");
    validar_cpfs(MAX_ITEMS, ITEM_LEN, cpfs, cpfs_validos, cpfs_invalidos, &total_validos, &total_invalidos);
    printf("\nCPFs válidos..: %2d\n", total_validos);
    printf("CPFs inválidos: %2d\n\n", total_invalidos);

    // seção para mostrar somente os CPFs válidos antes da ordenação
    printf("\n===> SOMENTE CPFs VÁLIDOS <===\n");
    printf("===> ANTES DE ORDENAR <===\n");
    mostrar(total_validos, ITEM_LEN, cpfs_validos);

    // seção para mostrar somente os CPFs válidos depis da ordenação
    printf("\n===> DEPOIS DE ORDENAR <===\n");
    ordenar(total_validos, ITEM_LEN, cpfs_validos, 0, total_validos - 1);
    mostrar(total_validos, ITEM_LEN, cpfs_validos);
}
