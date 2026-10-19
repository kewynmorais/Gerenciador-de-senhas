#ifndef LOGIN_USUARIO_H
#define LOGIN_USUARIO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tabela.h"

typedef struct
{
    char nome[50];
    char senha[50];
} Usuario;

Usuario usuario;

void removerEnter(char texto[])
{
    for (int i = 0; texto[i] != '\0'; i++)
    {
        if (texto[i] == '\n')
        {
            texto[i] = '\0';
        }
    }
}

int obterFator(char caractere)
{
    for (int i = 0; i < (int)(sizeof(tabela) / sizeof(tabela[0])); i++)
    {
        if (tabela[i].caractere == caractere)
        {
            return tabela[i].fator;
        }
    }

    return -1;
}

int codificar_mensagem(char mensagem[], int *codigos)
{
    int tamanho = 0;

    for (int i = 0; mensagem[i] != '\0'; i++)
    {
        int fator = obterFator(mensagem[i]);

        if (fator == -1)
        {
            return 0;
        }

        int ascii = mensagem[i];

        codigos[tamanho] = ascii * 128 + fator;
        tamanho++;
    }

    return tamanho;
}

void cadastrarUsuario()
{
    FILE *arquivoUsuario;
    FILE *arquivoSenhas;

    int codigos[100];
    int tamanho;

    char nomeArquivo[100];

    arquivoUsuario = fopen("arquivoUsuarios.txt", "a");

    if (arquivoUsuario == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return;
    }

    printf("\nDigite o nome do usuario: ");
    fgets(usuario.nome, sizeof(usuario.nome), stdin);
    removerEnter(usuario.nome);

    printf("Crie a senha mestra: ");
    fgets(usuario.senha, sizeof(usuario.senha), stdin);
    removerEnter(usuario.senha);

    tamanho = codificar_mensagem(usuario.senha, codigos);

    if (tamanho == 0)
    {
        printf("Erro: a senha possui caracteres nao suportados.\n");
        fclose(arquivoUsuario);
        return;
    }

    fprintf(arquivoUsuario, "Nome: %s\n", usuario.nome);
    fprintf(arquivoUsuario, "Senha Mestra: ");

    for (int i = 0; i < tamanho; i++)
    {
        fprintf(arquivoUsuario, "%d ", codigos[i]);
    }

    fprintf(arquivoUsuario, "\n");

    fclose(arquivoUsuario);

    sprintf(nomeArquivo, "%s.txt", usuario.nome);

    arquivoSenhas = fopen(nomeArquivo, "a");

    if (arquivoSenhas != NULL)
    {
        fclose(arquivoSenhas);
    }

    printf("\nUsuario cadastrado com sucesso!\n");
}

int UsuarioExistente()
{
    FILE *arquivoUsuario;

    char nomeDigitado[50];
    char linha[1000];

    arquivoUsuario = fopen("arquivoUsuarios.txt", "r");

    if (arquivoUsuario == NULL)
    {
        printf("Nenhum usuario cadastrado.\n");
        return 0;
    }

    printf("\nDigite o nome do usuario: ");
    fgets(nomeDigitado, sizeof(nomeDigitado), stdin);
    removerEnter(nomeDigitado);

    while (fgets(linha, sizeof(linha), arquivoUsuario) != NULL)
    {
        if (strncmp(linha, "Nome: ", 6) == 0)
        {
            removerEnter(linha);

            if (strcmp(linha + 6, nomeDigitado) == 0)
            {
                strcpy(usuario.nome, nomeDigitado);

                fclose(arquivoUsuario);

                printf("\nUsuario encontrado.\n");

                return 1;
            }
        }
    }

    fclose(arquivoUsuario);

    printf("\nUsuario nao encontrado.\n");

    return 0;
}

int verificarSenhaMestra()
{
    FILE *arquivoUsuario;

    char linha[1000];
    char senhaDigitada[50];

    int codigosDigitados[100];
    int codigosArquivo[100];

    int tamanhoDigitado;
    int tamanhoArquivo = 0;

    arquivoUsuario = fopen("arquivoUsuarios.txt", "r");

    if (arquivoUsuario == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivoUsuario) != NULL)
    {
        if (strncmp(linha, "Nome: ", 6) == 0) //strncmp compara os primeiros n caracteres de duas strings
        {
            removerEnter(linha);

            if (strcmp(linha + 6, usuario.nome) == 0) //strcmp compara duas strings
            {
                if (fgets(linha, sizeof(linha), arquivoUsuario) == NULL)
                {
                    fclose(arquivoUsuario);
                    return 0;
                }

                if (strncmp(linha, "Senha Mestra: ", 14) == 0)
                {
                    char *numero = strtok(linha + 14, " \n");

                    while (numero != NULL && tamanhoArquivo < 100)
                    {
                        codigosArquivo[tamanhoArquivo] = atoi(numero);
                        tamanhoArquivo++;

                        numero = strtok(NULL, " \n"); //strtok divide uma string com base em delimitadores
                    }

                    break;
                }
            }
        }
    }

    fclose(arquivoUsuario);

    printf("\nDigite a senha mestra: ");
    fgets(senhaDigitada, sizeof(senhaDigitada), stdin);
    removerEnter(senhaDigitada);

    tamanhoDigitado = codificar_mensagem(
        senhaDigitada,
        codigosDigitados
    );

    if (tamanhoDigitado == 0)
    {
        printf("Senha possui caracteres nao suportados.\n");
        return 0;
    }

    if (tamanhoDigitado != tamanhoArquivo)
    {
        printf("Senha mestra incorreta.\n");
        return 0;
    }

    for (int i = 0; i < tamanhoDigitado; i++)
    {
        if (codigosDigitados[i] != codigosArquivo[i])
        {
            printf("Senha mestra incorreta.\n");
            return 0;
        }
    }

    printf("Senha mestra correta!\n");

    return 1;
}

#endif