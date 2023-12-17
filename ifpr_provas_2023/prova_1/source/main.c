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

struct pair_t
{
    int first;
    int second;
};

struct pair_t validar_cpfs(char cpfs[MAX_ITEMS][CPF_LEN], char cpfsValidos_o[MAX_ITEMS][CPF_LEN], char cpfsInvalidos_o[MAX_ITEMS][CPF_LEN])
{
    struct pair_t resultado = {0};

    for (int i = 0; i != MAX_ITEMS; i += 1)
    {
        int resultadoValidacao = validar_cpf(cpfs[i]);

        switch (resultadoValidacao)
        {
        case CPF_E_OK:
        {
            char cpfFormatado[CPF_LEN + 3] = {0};
            formatar_cpf(cpfs[i], cpfFormatado);

            char estados[ESTADOS_LEN] = {0};
            estado_cpf(cpfs[i], estados);
            printf("CPF %s\tvalido, Estado(s): %s\n", cpfFormatado, estados);

            strcpy_s(cpfsValidos_o[(resultado.first)++], CPF_LEN, cpfs[i]);

            break;
        }
        case CPF_E_DV1: printf("CPF %s\t\tErro no DV1\n", cpfs[i]); break;
        case CPF_E_DV2: printf("CPF %s\t\tErro no DV2\n", cpfs[i]); break;
        case CPF_E_LEN: printf("CPF %s\t\tNão tem 11 digitos\n", cpfs[i]); break;
        case CPF_E_SAM: printf("CPF %s\t\tCom todos os digitos iguais\n", cpfs[i]); break;
        case CPF_E_UNK: printf("CPF %s\t\tErro desconhecido\n", cpfs[i]); break;
        }

        if (resultadoValidacao != CPF_E_OK)
        {
            strcpy_s(cpfsInvalidos_o[(resultado.second)++], CPF_LEN, cpfs[i]);
        }
    }

    return resultado;
}

// =============================================================================
// percorre a matriz "arr" exibindo seu valor e a posição na qual ele se
// encontra
// =============================================================================

void mostrar(int quantidadeStrings, char cpfs[quantidadeStrings][CPF_LEN])
{
    for (int i = 0; i != quantidadeStrings; i += 1)
    {
        printf("[%2d]: %s\n", i + 1, cpfs[i]);
    }
}

int main()
{
    // CPFs obtidos em https://www.4devs.com.br/gerador_de_cpf

#if 0
    // matriz de CPFs válidos
    char cpfs[MAX_ITEMS][CPF_LEN] =
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
    char cpfs[MAX_ITEMS][CPF_LEN] =
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

    printf("===> VALIDAR CPFs <===\n\n");

    char cpfsValidos[MAX_ITEMS][CPF_LEN] = {0};
    char cpfsInvalidos[MAX_ITEMS][CPF_LEN] = {0};

    struct pair_t resultado = validar_cpfs(cpfs, cpfsValidos, cpfsInvalidos);

    printf("\nCPFs válidos..: %2d\n", resultado.first);
    printf("CPFs inválidos: %2d\n\n", resultado.second);

    printf("\n===> SOMENTE CPFs VÁLIDOS <===\n\n");

    printf("===> ANTES DE ORDENAR <===\n");
    mostrar(resultado.first, cpfsValidos);

    printf("\n===> DEPOIS DE ORDENAR <===\n");
    ordenar(resultado.first, cpfsValidos, 0, resultado.first - 1);
    mostrar(resultado.first, cpfsValidos);
}

