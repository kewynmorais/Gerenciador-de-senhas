#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Login_Usuario.h"
#include "Senhas.h"

int main()
{
    int opcao = 0;
    int opcaoUsuario = 0;

    while (opcao != 3)
    {
        printf("\n==========================================\n");
        printf("          GERENCIADOR DE SENHAS\n");
        printf("==========================================\n\n");

        printf("1 - Cadastrar usuario\n");
        printf("2 - Utilizar usuario existente\n");
        printf("3 - Sair\n\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1)
        {
            cadastrarUsuario();
        }
        else if (opcao == 2)
        {
            if (UsuarioExistente())
            {
                opcaoUsuario = 0;

                while (opcaoUsuario != 3)
                {
                    printf("\n==========================================\n");
                    printf("          GERENCIADOR DE SENHAS\n");
                    printf("==========================================\n\n");

                    printf("Usuario: %s\n\n", usuario.nome);

                    printf("1 - Adicionar senha\n");
                    printf("2 - Visualizar senhas\n");
                    printf("3 - Sair do usuario\n\n");

                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaoUsuario);
                    getchar();

                    if (opcaoUsuario == 1)
                    {
                        adicionarSenha();
                    }
                    else if (opcaoUsuario == 2)
                    {
                        visualizarSenhas();
                    }
                    else if (opcaoUsuario == 3)
                    {
                        printf("\nSaindo do usuario...\n");
                    }
                    else
                    {
                        printf("\nOpcao invalida.\n");
                    }
                }
            }
        }
        else if (opcao == 3)
        {
            printf("\nSaindo...\n");
        }
        else
        {
            printf("\nOpcao invalida.\n");
        }
    }

    return 0;
}