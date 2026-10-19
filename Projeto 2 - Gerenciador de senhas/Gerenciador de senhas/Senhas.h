#ifndef SENHAS_H
#define SENHAS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Login_Usuario.h"

#define CHAVE_XOR 1234

int criptografarCesar(char texto[], int resultado[])
{
    int tamanho = 0;
    int chave[4] = {1, 2, 3, 4};

    for (int i = 0; texto[i] != '\0'; i++)
    {
        resultado[tamanho] =
            (unsigned char)texto[i] + chave[i % 4];

        tamanho++;
    }

    return tamanho;
}

int descriptografarCesar(int codigo[], int tamanho, char resultado[])
{
    int chave[4] = {1, 2, 3, 4};

    for (int i = 0; i < tamanho; i++)
    {
        resultado[i] =
            codigo[i] - chave[i % 4];
    }

    resultado[tamanho] = '\0';

    return tamanho;
}

int criptografarXOR(char texto[], int resultado[])
{
    int tamanho = 0;

    for (int i = 0; texto[i] != '\0'; i++)
    {
        resultado[tamanho] =
            ((unsigned char)texto[i]) ^ CHAVE_XOR;

        tamanho++;
    }

    return tamanho;
}

int descriptografarXOR(int codigo[], int tamanho, char resultado[])
{
    for (int i = 0; i < tamanho; i++)
    {
        resultado[i] =
            codigo[i] ^ CHAVE_XOR;
    }

    resultado[tamanho] = '\0';

    return tamanho;
}

int criptografarTabela(char texto[], int resultado[])
{
    return codificar_mensagem(texto, resultado);
}

int descriptografarTabela(int codigo[], int tamanho, char resultado[])
{
    for (int i = 0; i < tamanho; i++)
    {
        int ascii = codigo[i] / 128;

        resultado[i] = (char)ascii;
    }

    resultado[tamanho] = '\0';

    return tamanho;
}

void adicionarSenha()
{
    FILE *arquivo;

    char nomeArquivo[100];

    char site[100];
    char usuarioSenha[100];
    char senha[100];

    int metodo;
    int codigo[100];
    int tamanho;

    printf("\n==========================================\n");
    printf("             ADICIONAR SENHA\n");
    printf("==========================================\n");

    printf("\nDigite o servico/site: ");
    fgets(site, sizeof(site), stdin);
    removerEnter(site);

    printf("Digite o usuario/login: ");
    fgets(usuarioSenha, sizeof(usuarioSenha), stdin);
    removerEnter(usuarioSenha);

    printf("Digite a senha: ");
    fgets(senha, sizeof(senha), stdin);
    removerEnter(senha);
    while (1)
    {
    printf("\nEscolha o metodo de criptografia:\n");
    printf("1 - Simples\n");
    printf("2 - Intermediario\n");
    printf("3 - Complexa\n");
    printf("\nOpcao: ");

    scanf("%d", &metodo);
    getchar();

    if (metodo < 1 || metodo > 3)
    {
        printf("\nMetodo invalido.\n");
        continue;
    }

    if (metodo == 1)
    {
        tamanho = criptografarCesar(senha, codigo);
    }
    else if (metodo == 2)
    {
        tamanho = criptografarXOR(senha, codigo);
    }
    else
    {
        tamanho = criptografarTabela(senha, codigo);
    }

    if (tamanho == 0)
    {
        printf("\nA senha possui um caractere nao suportado pelo metodo escolhido.\n");

        printf("Digite a senha novamente: ");
        fgets(senha, sizeof(senha), stdin);
        removerEnter(senha);

        continue;
    }

    break;
}
    sprintf(nomeArquivo, "%s.txt", usuario.nome);

    arquivo = fopen(nomeArquivo, "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de senhas.\n");
        return;
    }

    fprintf(arquivo, "Site: %s\n", site);
    fprintf(arquivo, "Usuario: %s\n", usuarioSenha);
    fprintf(arquivo, "Metodo: %d\n", metodo);
    fprintf(arquivo, "Senha: ");

    for (int i = 0; i < tamanho; i++)
    {
        fprintf(arquivo, "%d ", codigo[i]);
    }

    fprintf(arquivo, "\n");
    fprintf(arquivo, "------------------------------\n");

    fclose(arquivo);

    printf("\nSenha adicionada com sucesso!\n");
}

void visualizarSenhas()
{
    FILE *arquivo;

    char nomeArquivo[100];
    char linha[1000];

    char site[100];
    char usuarioSenha[100];
    char senhaDescriptografada[100];

    int metodo;
    int codigo[100];
    int tamanho;

    if (!verificarSenhaMestra())
    {
        return;
    }

    sprintf(nomeArquivo, "%s.txt", usuario.nome);

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("\nNenhuma senha foi cadastrada.\n");
        return;
    }

    printf("\n==========================================\n");
    printf("             SENHAS SALVAS\n");
    printf("==========================================\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strncmp(linha, "Site: ", 6) == 0)
        {
            strcpy(site, linha + 6);
            removerEnter(site);

            if (fgets(linha, sizeof(linha), arquivo) == NULL)
                break;

            strcpy(usuarioSenha, linha + 9); //strcpy copia uma string para outra
            removerEnter(usuarioSenha);

            if (fgets(linha, sizeof(linha), arquivo) == NULL)
                break;

            metodo = atoi(linha + 8);

            if (fgets(linha, sizeof(linha), arquivo) == NULL)
                break;

            tamanho = 0;

            char *numero = strtok(linha + 7, " \n");

            while (numero != NULL && tamanho < 100)
            {
                codigo[tamanho] = atoi(numero);
                tamanho++;

                numero = strtok(NULL, " \n");
            }

            if (metodo == 1)
            {
                descriptografarCesar(
                    codigo,
                    tamanho,
                    senhaDescriptografada
                );
            }
            else if (metodo == 2)
            {
                descriptografarXOR(
                    codigo,
                    tamanho,
                    senhaDescriptografada
                );
            }
            else if (metodo == 3)
            {
                descriptografarTabela(
                    codigo,
                    tamanho,
                    senhaDescriptografada
                );
            }

            printf("\nSite: %s\n", site);
            printf("Usuario: %s\n", usuarioSenha);
            printf("Metodo: %d\n", metodo);
            printf("Senha: %s\n", senhaDescriptografada);

            fgets(linha, sizeof(linha), arquivo);
        }
    }

    fclose(arquivo);
}

#endif