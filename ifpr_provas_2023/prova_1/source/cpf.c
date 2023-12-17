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

int contem_apenas_numeros(char cpf[CPF_LEN]);
int contem_os_mesmos_numeros(char cpf[CPF_LEN]);

// =============================================================================
//
// NÃO ALTERE ABSOLUTAMENTE NADA NOS CABEÇALHOS (ASSINATURAS) DAS FUNÇÕES
//
// =============================================================================

char calcular_verificador(char const* comeco, char const* fim)
{
    int verificador = 0;
    int distancia   = (int)(2 + fim - comeco);

    for (char const* position = comeco; position <= fim; ++position)
    {
        if (!isdigit(*position))
        {
            continue;
        }

        verificador += (distancia * TO_INT(*position));
        distancia -= 1;
    }

    if (verificador % 11 < 2)
    {
        return TO_CHR(0);
    }

    return (char)TO_CHR(11 - verificador % 11);
}

int validar_cpf(char cpf[CPF_LEN])
{
    if (strlen(cpf) != 11)                      return CPF_E_LEN;
    if (!contem_apenas_numeros(cpf))   return CPF_E_UNK;
    if (contem_os_mesmos_numeros(cpf)) return CPF_E_SAM;

    if (cpf[9] == calcular_verificador(&cpf[0], &cpf[8]) && cpf[10] == calcular_verificador(&cpf[0], &cpf[9]))
    {
        return CPF_E_OK;
    }
    else
    {
        if (cpf[9] != calcular_verificador(&cpf[0], &cpf[8]))
        {
            return CPF_E_DV1;
        }

        if (cpf[10] != calcular_verificador(&cpf[0], &cpf[9]))
        {
            return CPF_E_DV2;
        }
    }

    assert(false && "UNREACHABLE");

    return CPF_E_UNK;
}

void formatar_cpf(char cpf[CPF_LEN], char cpfFormatado_o[CPF_LEN + 3])
{
    char formato[] = "XXX.XXX.XXX-XX";

    memcpy(formato, cpf, 3);
    memcpy(formato + 4, cpf + 3, 3);
    memcpy(formato + 8, cpf + 6, 3);
    memcpy(formato + 12, cpf + 9, 2);

    memcpy(cpfFormatado_o, formato, sizeof(formato));
}

void estado_cpf(char cpf[CPF_LEN], char estados_o[ESTADOS_LEN])
{
    switch (TO_INT(cpf[8]))
    {
    case 0: memcpy(estados_o, FROM_STR("RS")); return;
    case 1: memcpy(estados_o, FROM_STR("DF, GO, MT, MS or TO")); return;
    case 2: memcpy(estados_o, FROM_STR("AM, PA, RO, AM, AC or RO")); return;
    case 3: memcpy(estados_o, FROM_STR("CE, MA ou PI")); return;
    case 4: memcpy(estados_o, FROM_STR("PA, PE, AL ou RN")); return;
    case 5: memcpy(estados_o, FROM_STR("BA ou SE")); return;
    case 6: memcpy(estados_o, FROM_STR("MG")); return;
    case 7: memcpy(estados_o, FROM_STR("RJ ou ES")); return;
    case 8: memcpy(estados_o, FROM_STR("SP")); return;
    case 9: memcpy(estados_o, FROM_STR("PR ou SC")); return;
    }

    memcpy(estados_o, FROM_STR("*-*-*"));
}

int contem_apenas_numeros(char cpf[CPF_LEN])
{
    for (int i = 0; i != CPF_LEN - 1; i += 1)
    {
        if (!isdigit(cpf[i])) return 0;
    }

    return 1;
}

int contem_os_mesmos_numeros(char cpf[CPF_LEN])
{
    for (int i = 0; i != CPF_LEN - 1; i += 1)
    {
        if (cpf[0] != cpf[i]) return 0;
    }

    return 1;
}
