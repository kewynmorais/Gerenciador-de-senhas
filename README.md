# Gerenciador de Senhas em C

Gerenciador de senhas desenvolvido em linguagem C, executado diretamente no terminal. Cada usuário possui uma **senha mestra** e pode armazenar credenciais de sites e serviços, escolhendo entre **três métodos de criptografia** para proteger cada senha.

> **Aviso importante:** este é um projeto **educacional**. Os algoritmos utilizados foram criados para fins de estudo e **não são seguros** para proteger senhas reais. Consulte a seção [Limitações e segurança](#limitações-e-segurança).

## Funcionalidades

- Cadastro de usuários com senha mestra
- Acesso a usuários existentes
- Adição de senhas (serviço/site, usuário/login e senha)
- Visualização das senhas salvas, protegida pela senha mestra
- Três métodos de criptografia à escolha:

| Opção | Método | Funcionamento |
|-------|--------|---------------|
| 1 | **Simples** | Cifra de César com chave variável (`1, 2, 3, 4` repetida ao longo da senha) |
| 2 | **Intermediário** | Operação XOR de cada caractere com uma chave fixa |
| 3 | **Complexa** | Codificação por tabela: `ASCII × 128 + fator`, em que o fator é definido para cada caractere em `Tabela.h` |

## Estrutura do projeto

```
.
├── Gerenciador_de_senhas.c   # Programa principal e menus
├── Login_Usuario.h           # Cadastro, busca de usuário e verificação da senha mestra
├── Senhas.h                  # Criptografia, descriptografia e gerenciamento das senhas
└── Tabela.h                  # Tabela de fatores usada no método "Complexa"
```

## Como funciona

O programa é dividido em dois níveis de menu. No primeiro, é possível cadastrar um novo usuário ou acessar um já existente. No segundo, o usuário autenticado pode adicionar novas senhas ou visualizar as já salvas, sendo que a visualização exige a confirmação da senha mestra.

Os dados são persistidos em arquivos de texto:

- `arquivoUsuarios.txt`: nomes e senhas mestras (codificadas) de todos os usuários
- `<nome_do_usuario>.txt`: senhas salvas de cada usuário, com o método de criptografia utilizado em cada registro

## Limitações e segurança

Por se tratar de um projeto de aprendizado, há limitações conhecidas:

- Os métodos de criptografia são **reversíveis** e utilizam chaves fixas no código, não substituindo algoritmos modernos como o AES.
- A senha mestra é armazenada de forma codificada, e não como *hash* (por exemplo, bcrypt ou Argon2).
- Os arquivos de texto ficam no mesmo diretório do programa, sem proteção adicional.
- A tabela de caracteres suporta letras (sem acento), números, espaço e símbolos comuns. Demais caracteres são recusados.

Portanto, o projeto é adequado para estudo, mas **não deve ser usado para armazenar senhas reais**.

## Conceitos praticados

- Modularização com arquivos de cabeçalho (`.h`)
- Manipulação de arquivos em C (`fopen`, `fgets`, `fprintf`)
- Manipulação de strings (`strtok`, `strcmp`, `strncmp`)
- Structs e vetores de structs
- Noções de criptografia clássica (César, XOR e substituição por tabela)

## Autor

Desenvolvido por **Kewyn Morais**.
Feedbacks e sugestões são bem-vindos.

- GitHub: (https://github.com/kewynmorais)
- LinkedIn: (https://www.linkedin.com/in/kewyn.morais)
