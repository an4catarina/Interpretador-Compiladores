# Como rodar o projeto

Para executar o interpretador, siga os passos abaixo. O projeto utiliza `flex` e `bison` para a análise léxica e sintática, e `cmake` para a compilação.

## Pré-requisitos

Certifique-se de ter as seguintes ferramentas instaladas em seu sistema:

- **GCC** (GNU Compiler Collection)
- **CMake** (versão 3.10 ou superior)
- **Flex** (Fast Lexical Analyzer)
- **Bison** (GNU Parser Generator)

## Compilação

1.  **Navegue até o diretório do projeto:**
    ```bash
    cd Interpretador-Compiladores-main/interpretador
    ```

2.  **Crie um diretório de build e navegue até ele:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Execute o CMake para configurar o projeto:**
    ```bash
    cmake ..
    ```

4.  **Compile o projeto:**
    ```bash
    make
    ```
    O executável do interpretador será gerado no diretório `build` com o nome `interpretador`.

## Execução

Para executar o interpretador, você deve fornecer o caminho para o arquivo de código-fonte C que deseja interpretar:

```bash
./interpretador <caminho_para_o_arquivo.c>
```

**Exemplo:**

```bash
./interpretador ../test/cases/var/var_decl.c
```

## Histórico de versões

| Versão | Data       | Autor           | Descrição da Alteração                                        | Revisor       |
|--------|-----------|----------------|---------------------------------------------------------------|---------------|
| 1.0    | 27/11/2025 | Pedro Henrique | Adição das instruções de compilação e execução | Ana Catarina  |
