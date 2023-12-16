#ifndef __CPF_H
#define __CPF_H

// =============================================================================
//
// NÃO ALTERE ABSOLUTAMENTE NADA NESTE ARQUIVO
//
// =============================================================================
#define ESTADOS_LEN 256

#define CPF_OK 0   // CPF válido
#define CPF_DV1 -1 // Erro no DV1 (primeiro dígito verificador)
#define CPF_DV2 -2 // Erro no DV2
#define CPF_LEN -3 // CPF não contém 11 dígitos
#define CPF_SAM -4 // Todos os dígitos do CPF são iguais
#define CPF_ERR -5 // Qualquer outro erro

int validar_cpf(int item_len, char cpf[item_len]);
void formatar_cpf(int item_len, char cpf[item_len], char fcpf[item_len + 3]);
void estado_cpf(int item_len, char cpf[item_len], int estados_len, char estados[estados_len]);

#endif // __CPF_H
