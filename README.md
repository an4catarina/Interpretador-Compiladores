# **Trabalho de Compiladores 1 - Interpretador de C**

Repositório dedicado ao desenvolvimento do trabalho final da disciplina Compiladores 1 ministrada pelo professor Sergio Antonio Andrade de Freitas no semestre 2025/2. Neste repositório está a implementação de um interpretador de C feito com o flex e o bison.

---

## **Requisitos Mínimos**

Para compilar o projeto é necessário ter instalado as seguintes ferramentas:

- cmake
- ninja
- flex
- bison
- just

Para executar os testes localmente também é necessário ter instalado:

- python
- pytest

---

## **Compilação**

O projeto utiliza o *runner* de comandos just para padronizar a invocação dos comandos utilizados para compilar o interpretador, caso tenha o just instalado basta executar o seguinte comando:

```bash
just build
```

Depois de compilado, o binário do interpretador estará na pasta `interpretador/build`.

Caso não tenha o just o projeto pode ser compilado copiando a receita *build* definida no `justfile` presente na raiz do repositório.

---

## **Testes**

Assim como a compilação, os testes podem ser executados utilizando a receita do just utilizando o seguinte comando:

```bash
just test
```

Caso queira rodar apenas uma suíte de testes específicas, coloque o nome da mesma ao final do comando mostrado acima, exemplo:

```bash
just test var
```

Atualmente foram implementadas as seguintes suítes de testes:

|  Nome   | Casos de Teste | Funcionalidade testada                                     |
| :-----: | :------------: | :--------------------------------------------------------- |
|   var   |       8        | Declaração, inicialização e uso de variáveis               |
|  expr   |       8        | Expressões aritméticas                                     |
| scopes  |       3        | Criação de escopos, uso de variáveis de escopos diferentes |
| if_else |       7        | Estruturas `if`, `else` e `else if`                        |

---

## **Utilização**

O interpretador pode ser utilizado apenas invocando o binário sem passar um arquivo fonte utilizando o comando abaixo, neste caso o interpretador irá aceitar comandos escritos no terminal até que um erro seja detectado ou seja enviando um sinal de EOF.

```bash
./interpretador/build/interpretador
```

Também é possível passar um arquivo para o interpretador da seguinte forma

```bash
./interpretador/build/interpretador < "arquivo.c"
```

A receita *run* definida no arquivo `justfile` pode ser usada com o mesmo resultado:

```bash
just run # Modo interativo

just run "arquivo.c" # Execução de código fonte
```