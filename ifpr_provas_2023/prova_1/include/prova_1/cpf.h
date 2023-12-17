#ifndef __CPF_H
#define __CPF_H

// =============================================================================
//
// NÃO ALTERE ABSOLUTAMENTE NADA NESTE ARQUIVO
//
// =============================================================================

#define CPF_LEN 12
#define ESTADOS_LEN 256

#define CPF_E_OK 0   // CPF válido
#define CPF_E_DV1 -1 // Erro no DV1 (primeiro dígito verificador)
#define CPF_E_DV2 -2 // Erro no DV2
#define CPF_E_LEN -3 // CPF não contém 11 dígitos
#define CPF_E_SAM -4 // Todos os dígitos do CPF são iguais
#define CPF_E_UNK -5 // Qualquer outro erro

int validar_cpf(char cpf[CPF_LEN]);
void formatar_cpf(char cpf[CPF_LEN], char cpfFormatado_o[CPF_LEN + 3]);
void estado_cpf(char cpf[CPF_LEN], char estados_o[ESTADOS_LEN]);

#endif // __CPF_H
