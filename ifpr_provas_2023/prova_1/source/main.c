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

void validar_cpfs(int quantidadeCpfs, int tamanhoString, char cpfs[quantidadeCpfs][tamanhoString], char cpfsValidos[quantidadeCpfs][tamanhoString],
                  char cpfsInvalidos[quantidadeCpfs][tamanhoString], int* quantidadeValidos, int* quantidadeInvalidos)
{
    char cpfFormatado[tamanhoString + 3];

    memset(cpfFormatado, 0, tamanhoString + 3);

    *quantidadeValidos = 0;
    *quantidadeInvalidos = 0;

    for (int i = 0; i != quantidadeCpfs; i += 1)
    {
        int resultado = validar_cpf(tamanhoString, cpfs[i]);

        char estados[ESTADOS_LEN] = {0};

        switch (resultado)
        {
        case CPF_OK:
            formatar_cpf(tamanhoString, cpfs[i], cpfFormatado);
            estado_cpf(tamanhoString, cpfs[i], ESTADOS_LEN, estados);
            printf("CPF %s\tvalido, Estado(s): %s\n", cpfFormatado, estados);
            strcpy_s(cpfsValidos[(*quantidadeValidos)++], tamanhoString, cpfs[i]);
            break;
        case CPF_DV1: printf("CPF %s\t\tErro no DV1\n", cpfs[i]); break;
        case CPF_DV2: printf("CPF %s\t\tErro no DV2\n", cpfs[i]); break;
        case CPF_LEN: printf("CPF %s\t\tNão tem 11 digitos\n", cpfs[i]); break;
        case CPF_SAM: printf("CPF %s\t\tCom todos os digitos iguais\n", cpfs[i]); break;
        case CPF_ERR: printf("CPF %s\t\tErro desconhecido\n", cpfs[i]); break;
        }

        if (resultado != CPF_OK)
        {
            strcpy_s(cpfsInvalidos[(*quantidadeInvalidos)++], tamanhoString, cpfs[i]);
        }
    }
}

// =============================================================================
// percorre a matriz "arr" exibindo seu valor e a posição na qual ele se
// encontra
// =============================================================================

void mostrar(int quantidadeCpfs, int tamanhoString, char cpfs[quantidadeCpfs][tamanhoString])
{
    for (int i = 0; i != quantidadeCpfs; i += 1)
    {
        printf("[%2d]: %s\n", i + 1, cpfs[i]);
    }
}

int main()
{
    // CPFs obtidos em https://www.4devs.com.br/gerador_de_cpf

#if 0
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

    char cpfsValidos[MAX_ITEMS][ITEM_LEN] = {0};
    char cpfsInvalidos[MAX_ITEMS][ITEM_LEN] = {0};
    int quantidadeValidos = 0;
    int quantidadeInvalidos = 0;

    // seção para validar CPFs
    printf("===> VALIDAR CPFs <===\n");
    validar_cpfs(MAX_ITEMS, ITEM_LEN, cpfs, cpfsValidos, cpfsInvalidos, &quantidadeValidos, &quantidadeInvalidos);
    printf("\nCPFs válidos..: %2d\n", quantidadeValidos);
    printf("CPFs inválidos: %2d\n\n", quantidadeInvalidos);

    // seção para mostrar somente os CPFs válidos antes da ordenação
    printf("\n===> SOMENTE CPFs VÁLIDOS <===\n");
    printf("===> ANTES DE ORDENAR <===\n");
    mostrar(quantidadeValidos, ITEM_LEN, cpfsValidos);

    // seção para mostrar somente os CPFs válidos depis da ordenação
    printf("\n===> DEPOIS DE ORDENAR <===\n");
    ordenar(quantidadeValidos, ITEM_LEN, cpfsValidos, 0, quantidadeValidos - 1);
    mostrar(quantidadeValidos, ITEM_LEN, cpfsValidos);
}

