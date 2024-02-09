/******************************************************************************
 ** ISCTE-IUL: Trabalho prático 2 de Sistemas Operativos
 **
 ** Aluno: Nº: XXXXXX  Nome: Este Módulo não precisa ser entregue
 ** Nome do Módulo: common.h
 ** Descrição/Explicação do Módulo:
 **     Definição das estruturas de dados comuns aos módulos servidor e cliente
 **
 ******************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

#include <signal.h>
#include <unistd.h>

#define MIN_PROCESSAMENTO   1   // Tempo mínimo de processamento do Cliente
#define MAX_PROCESSAMENTO   7   // Tempo máximo de processamento do Cliente
#define MAX_ESPERA          5   // Tempo máximo de espera por parte do Cliente
#define NUM_PASSAGENS      20   // Tamanho máximo do buffer de Passagens

typedef struct {
    int nif;                    // Número de contribuinte do utilizador
    char senha[20];             // Senha do utilizador
    char nome[52];              // Nome do utilizador
    int saldo;                  // Saldo do utilizador
    int pid_cliente;            // PID do processo Cliente
    int pid_servidor_dedicado;  // PID do processo Servidor Dedicado
} Login;

#define FILE_SUFFIX_FIFO  ".fifo"                   // Sufixo (extensão) para os nomes dos FIFOs (Named Pipes)
#define FILE_REQUESTS  "servidor" FILE_SUFFIX_FIFO  // Nome do FIFO (Named Pipe) que serve para o Cliente fazer os pedidos ao Servidor
#define FILE_PREFIX_CLIENT  "cli-"                  // Prefixo para o nome do FIFO do cliente
#define FILE_PREFIX_SRVDED  "sd-"                   // Prefixo para o nome do FIFO do servidor dedicado
#define FILE_DATABASE  "bd_utilizadores.dat"        // Ficheiro de acesso direto que armazena a lista de utilizadores
#define SIZE_FILENAME 50

#endif
