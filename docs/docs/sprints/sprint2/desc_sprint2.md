## Sprint 2

Na segunda sprint, houve um avanço significativo no detalhamento do compilador, com foco na interpretação das instruções fornecidas pelo usuário. Os principais pontos desta sprint foram:

- **Análise léxica:**  
  Garantiu a identificação e classificação correta de todos os tokens, permitindo o funcionamento consistente dos demais módulos.

- **Análise sintática:**  
  Evoluiu para regras mais completas, incluindo:
  - **Variáveis:** Suporte à declaração e atualização de valores
  - **Operações aritméticas:** Sistema de precedência respeitando a ordem natural de execução
  - **Escopos:** Gerenciamento robusto de blocos de código, evitando conflitos de variáveis

- **Evolução da AST:**  
  Novos tipos de nós foram incorporados, possibilitando a futura interpretação de estruturas mais complexas e transformando o projeto em uma linguagem funcional, ainda que limitada.

Durante essa sprint, houve desafios relacionados à consistência da gramática, exigindo ajustes frequentes para evitar conflitos. Esta etapa foi fundamental para amadurecer a linguagem e preparar o caminho para funcionalidades mais avançadas.

## Issues atreladas a Sprint 2

- **[Atribuição e declaração de variáveis](https://github.com/an4catarina/Interpretador-Compiladores/issues/5)**  
  Implementação da declaração e atribuição de valores a variáveis, permitindo a manipulação de dados na linguagem.

- **[Operações Aritméticas](https://github.com/an4catarina/Interpretador-Compiladores/issues/6)**  
  Desenvolvimento de operações aritméticas básicas, como soma, subtração, multiplicação e divisão.

- **[Implementar estrutura de escopos no interpretador](https://github.com/an4catarina/Interpretador-Compiladores/issues/10)**  
  Criação de um sistema de escopos para gerenciar o escopo de variáveis e funções, garantindo o isolamento e a organização do código.

# Histórico de versões

| Versão | Data       | Autor           | Descrição da Alteração                                        | Revisor       |
|--------|-----------|----------------|---------------------------------------------------------------|---------------|
| 1.0    | 29/09/2025 | Pedro Henrique | Adição da descrição da sprint 2 | Ana Catarina  |
