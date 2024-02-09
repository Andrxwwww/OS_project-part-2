/******************************************************************************
 ** ISCTE-IUL: Trabalho prático de Sistemas Operativos
 **
 ** Nome do Módulo: so_utils.h
 ** Descrição/Explicação do Módulo:
 **     Definição de funções utilitárias genéricas
 **
 ******************************************************************************/
#ifndef __SO_UTILS_H__
#define __SO_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#define TRUE  1
#define FALSE 0

/******************************************************************************
 *  Macros para tratamento de erros
 ******************************************************************************/

/**
 *  Valida se uma operação teve sucesso ou não. Se não teve, escreve uma mensagem de erro e sai com erro -1, e mostrando a mensagem de erro,
 *  @param status   resultado da operação anterior. Se < 0 é porque houve erro, e nesse caso afixa a mensagem de erro e sai com status -1
 *  @param errorMsg mensagem de erro a apresentar em caso de erro
 */
#define so_exit_on_error(status, errorMsg) do { if (status < 0) { if (errno) perror(errorMsg); else fprintf(stderr, "%s\n", errorMsg); exit(-1); } } while (0)

/**
 *  Valida se uma operação teve sucesso ou não. Se não teve, escreve uma mensagem de erro e sai com erro -1, e mostrando a mensagem de erro,
 *  @param status   resultado da operação anterior. Se == NULL é porque houve erro, e nesse caso afixa a mensagem de erro e sai com status -1
 *  @param errorMsg mensagem de erro a apresentar em caso de erro
 */
#define so_exit_on_null(status, errorMsg) do { if (NULL == status) { if (errno) perror(errorMsg); else fprintf(stderr, "%s\n", errorMsg); exit(-1); } } while (0)

/******************************************************************************
 *  Macros para leitura de Strings de um ficheiro ou do STDIN
 ******************************************************************************/

/**
 *  Macro para leitura de uma string de um ficheiro já aberto
 *  Esta macro basicamente efetua a leitura de uma string de um ficheiro aberto, definido um buffer_size. Semelhante a fgets(), mas removendo o '\n' e os caracteres extra.
 *  @param buffer       (char*) buffer onde vai ser depositada a informação
 *  @param buffer_size  (int) tamanho do buffer acima (em bytes)
 *  @param file         (FILE*) handler do ficheiro já previamente aberto, de onde deve ler
 *  @return             Um apontador (char *) para o buffer passado (a string lida), ou NULL em caso de erro
 */
#define so_fgets(buffer, buffer_size, file) ({          \
    char *_result = fgets(buffer, buffer_size, file);   \
    if (NULL != _result) {                              \
        if ('\n' == buffer[strlen(buffer) - 1])         \
            buffer[strlen(buffer) - 1] = '\0';          \
        else {                                          \
            int c;                                      \
            do                                          \
                c = getc(file);                         \
            while ('\n' != c && EOF != c);              \
        }                                               \
    }                                                   \
    _result;                                            \
})

/**
 *  Macro para leitura de uma string do STDIN
 *  Esta macro basicamente efetua a leitura de uma string do STDIN, definido um buffer_size. Semelhante a fgets(), mas removendo o '\n' e os caracteres extra.
 *  @param buffer        (char*) buffer onde vai ser depositada a informação
 *  @param buffer_size   (int) tamanho do buffer acima (em bytes)
 *  @return             Um apontador (char *) para o buffer passado (a string lida), ou NULL em caso de erro
 */
#define so_gets(buffer, buffer_size) so_fgets(buffer, buffer_size, stdin)

/**
 *  Macro para leitura de um inteiro de um ficheiro já aberto
 *  Esta macro basicamente efetua a leitura de uma string de um ficheiro já aberto, e depois converte a string num inteiro, retornando-o.
 *  O comportamento dessa conversão é o descrito em https://www.ibm.com/docs/en/i/7.4?topic=functions-atoi-convert-character-string-integer
 *  @param file (FILE*) handler do ficheiro já previamente aberto, de onde deve ler
 *  @return int O inteiro lido
 */
#define __SO_UTILS_TEMPORARY_BUFFER_SIZE__ 11
char __so_utils_temporary_buffer__[__SO_UTILS_TEMPORARY_BUFFER_SIZE__];
#define so_fgeti(file) ({                                                                           \
    int _result = 0;                                                                                \
    if ( NULL != so_fgets(__so_utils_temporary_buffer__, __SO_UTILS_TEMPORARY_BUFFER_SIZE__, file)) \
        _result = atoi(__so_utils_temporary_buffer__);                                               \
    _result;                                                                                        \
})

/**
 *  Macro para leitura de um inteiro do STDIN
 *  Esta macro basicamente efetua a leitura de uma string do STDIN, e depois converte a string num inteiro, retornando-o.
 *  @return int O inteiro lido
 */
#define so_geti() so_fgeti(stdin)

/**
 *  Macro para leitura de um float de um ficheiro já aberto
 *  Esta macro basicamente efetua a leitura de uma string de um ficheiro já aberto, e depois converte a string num float, retornando-o.
 *  O comportamento dessa conversão é o descrito em https://www.ibm.com/docs/en/i/7.4?topic=functions-atof-convert-character-string-float
 *  @param file (FILE*) handler do ficheiro já previamente aberto, de onde deve ler
 *  @return float O float lido
 */
#define so_fgetf(file) ({                                                                           \
    float _result = 0;                                                                                \
    if ( NULL != so_fgets(__so_utils_temporary_buffer__, __SO_UTILS_TEMPORARY_BUFFER_SIZE__, file)) \
        _result = atof(__so_utils_temporary_buffer__);                                               \
    _result;                                                                                        \
})

/**
 *  Macro para leitura de um float do STDIN
 *  Esta macro basicamente efetua a leitura de uma string do STDIN, e depois converte a string num float, retornando-o.
 *  @return float O float lido
 */
#define so_getf() so_fgetf(stdin)

/******************************************************************************
 *  Macros utilitárias
 ******************************************************************************/

#define so_rand() ({         \
    struct timeval tv;       \
    gettimeofday(&tv, NULL); \
    srand(tv.tv_usec);       \
    rand();                  \
})

#define so_rand_between_values(value_min, value_max) (so_rand() % (value_max - value_min + 1) + value_min)

/******************************************************************************
 *  Macros para impressão de mensagens de debug, sucesso e erro
 ******************************************************************************/

//#define SO_HIDE_COLOURS    // Uncomment this line to hide all colours
#include "/home/so/reference/so_define-colours.h"

/**
 *  Impressão de mensagens de DEBUG incluindo o módulo e a linha de código.
 */
// #define SO_HIDE_DEBUG   // Uncomment this line to hide all @DEBUG statements

/**
 *  Escreve uma mensagem de debug (parâmetros iguais ao printf) se SO_HIDE_DEBUG não estiver definida
 */
#ifndef SO_HIDE_DEBUG
#define so_debug(fmt, ...) do { printf( BACK_FAINT_GRAY "@DEBUG:%s:%d:%s():" GRAY " [" fmt "]" NO_COLOUR "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__); } while (0)
#else   // SO_HIDE_DEBUG
#define so_debug(fmt, ...) do { } while (0)
#endif  // SO_HIDE_DEBUG

/**
 *  Escreve uma mensagem de sucesso (parâmetros iguais ao printf), deve ser usado em todas as mensagens "positivas" que a aplicação mostra
 *  @param passo (o passo do enunciado) ... os argumentos são os mesmos que os do printf(), logo recebe uma string de formatação e depois um número variável de argumentos
 */
#define so_success(passo, fmt, ...) do { printf( BACK_GREEN "@SUCCESS {" passo "}" GREEN " [" fmt "]" NO_COLOUR "\n", ## __VA_ARGS__); } while (0)

/**
 *  Escreve uma mensagem de erro (parâmetros iguais ao printf), deve ser usado em todas as mensagens "de erro" que a aplicação mostra.
 *  Estas mensagens de erro são as "de negócio", e não as de erros referentes a problemas técnicos como abertura de ficheiros, etc. (onde se deve usar perror)
 *  @param passo (o passo do enunciado) ... os argumentos são os mesmos que os do printf(), logo recebe uma string de formatação e depois um número variável de argumentos
 */
#define so_error(passo, fmt, ...) do { printf( BACK_BOLD_RED "@ERROR {" passo "}" RED " [" fmt "]" NO_COLOUR "\n", ## __VA_ARGS__); if (errno) perror(""); } while (0)

#endif // __SO_UTILS_H__