#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "cpf.h"

#define TO_INT(x) ((x) - '0')
#define TO_CHR(x) ((x) + '0')
#define FROM_STR(x) x, sizeof(x)

// protótipos de funções de suporte (usadas somente neste código fonte)
// =============================================================================
//
// NÃO ALTERE ABSOLUTAMENTE NADA NOS CABEÇALHOS (ASSINATURAS) DAS FUNÇÕES
//
// =============================================================================
int contem_apenas_numeros(int item_len, char s[item_len]);
int contem_os_mesmos_numeros(int item_len, char s[item_len]);

// =============================================================================
//
// NÃO ALTERE ABSOLUTAMENTE NADA NOS CABEÇALHOS (ASSINATURAS) DAS FUNÇÕES
//
// =============================================================================

char calcular_verificador(char const* begin, char const* end)
{
    int verifier = 0;
    int distance = (int)(2 + end - begin);

    for (char const* position = begin; position <= end; ++position)
    {
        if (!isdigit(*position))
        {
            continue;
        }

        verifier += (distance * TO_INT(*position));
        distance -= 1;
    }

    if (verifier % 11 < 2)
    {
        return TO_CHR(0);
    }

    return (char)TO_CHR(11 - verifier % 11);
}

int validar_cpf(int item_len, char cpf[item_len])
{
    if (strlen(cpf) != 11)                       return CPF_LEN;
    if (!contem_apenas_numeros(item_len, cpf))   return CPF_ERR;
    if (contem_os_mesmos_numeros(item_len, cpf)) return CPF_SAM;

    if (cpf[9] == calcular_verificador(&cpf[0], &cpf[8]) && cpf[10] == calcular_verificador(&cpf[0], &cpf[9]))
    {
        return CPF_OK;
    }
    else
    {
        if (cpf[9] != calcular_verificador(&cpf[0], &cpf[8]))
        {
            return CPF_DV1;
        }

        if (cpf[10] != calcular_verificador(&cpf[0], &cpf[9]))
        {
            return CPF_DV2;
        }
    }

    assert(false && "UNREACHABLE");

    return CPF_ERR;
}

void formatar_cpf(int item_len, char cpf[item_len], char fcpf[item_len + 3])
{
    char wildcard[] = "XXX.XXX.XXX-XX";

    memcpy(wildcard, cpf, 3);
    memcpy(wildcard + 4, cpf + 3, 3);
    memcpy(wildcard + 8, cpf + 6, 3);
    memcpy(wildcard + 12, cpf + 9, 2);

    memcpy(fcpf, wildcard, sizeof(wildcard));
}

void estado_cpf(int item_len, char cpf[item_len], int estados_len, char estados[estados_len])
{
    switch (TO_INT(cpf[8]))
    {
    case 0: memcpy(estados, FROM_STR("RS")); return;
    case 1: memcpy(estados, FROM_STR("DF, GO, MT, MS or TO")); return;
    case 2: memcpy(estados, FROM_STR("AM, PA, RO, AM, AC or RO")); return;
    case 3: memcpy(estados, FROM_STR("CE, MA ou PI")); return;
    case 4: memcpy(estados, FROM_STR("PA, PE, AL ou RN")); return;
    case 5: memcpy(estados, FROM_STR("BA ou SE")); return;
    case 6: memcpy(estados, FROM_STR("MG")); return;
    case 7: memcpy(estados, FROM_STR("RJ ou ES")); return;
    case 8: memcpy(estados, FROM_STR("SP")); return;
    case 9: memcpy(estados, FROM_STR("PR ou SC")); return;
    }

    memcpy(estados, FROM_STR("*-*-*"));
}

int contem_apenas_numeros(int item_len, char s[item_len])
{
    for (int i = 0; i != item_len - 1; i += 1)
    {
        if (!isdigit(s[i])) return 0;
    }

    return 1;
}

int contem_os_mesmos_numeros(int item_len, char s[item_len])
{
    int count = 0;
    int lastSeen = 0;

    for (int i = 0; i != item_len - 1; i += 1)
    {
        if (!lastSeen) lastSeen = s[i];

        if (lastSeen == s[i])
        {
            lastSeen = s[i];
            count += 1;
        }
        else
        {
            return 0;
        }
    }

    return count == item_len - 1;
}
