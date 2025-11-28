# Cronograma Geral do Projeto

Com base no [cronograma sugerido pelo professor](https://github.com/sergioaafreitas/COMP1/blob/main/semana%2001/docs/Guia%20-%20Projeto%20de%20um%20interpretador.md), a equipe estruturou o desenvolvimento do interpretador em **6 sprints**, cada uma com objetivos, entregas e tarefas definidas.

De maneira geral, o planejamento está estruturado da seguinte forma:

## Cronograma Geral do Projeto

| Sprint     | Período       | Objetivo Resumido                     |
|------------|---------------|--------------------------------------|
| Sprint 1   | 10/09 – 18/09 | Configuração do projeto e protótipos iniciais |
| Sprint 2   | 19/09 – 02/10 | Conclusão da análise léxica e início da sintática |
| Sprint 3   | 03/10 – 16/10 | Construção da AST e análise semântica inicial |
| Sprint 4   | 17/10 – 30/10 | Execução sobre AST e análise semântica aprimorada |
| Sprint 5   | 31/10 – 20/11 | Otimizações, recursos adicionais e testes integrados |
| Sprint 6   | 21/11 – 04/12 | Entrevista final, ajustes e conclusão da documentação |

---

## Detalhamento por Sprint

### Sprint 1 – 10/09 a 18/09

**Objetivo:** Configuração do projeto, definição da linguagem e criação dos protótipos iniciais (`lex.l` e `parser.y`).

**Entregáveis:**

- Documento inicial da linguagem
- Protótipo de gramática
- Ambiente configurado

**Tarefas:**

- Criar repositório e configurar ambiente de desenvolvimento
- Definir especificação inicial da linguagem
- Criar protótipo `lex.l` básico
- Criar protótipo `parser.y` inicial

---

### Sprint 2 – 19/09 a 02/10

**Objetivo:** Conclusão da análise léxica e início da análise sintática. Preparação do Ponto de Controle P1.

**Entregáveis:**

- Arquivo `.l` completo
- Primeiras regras sintáticas no `.y`
- Testes básicos realizados
- Formulário P1 e apresentação preparados

**Tarefas:**

- Completar arquivo `.l` com todos os tokens necessários
- Desenvolver primeiras regras sintáticas no `.y`
- Realizar testes básicos de análise léxica e sintática
- Preparar formulário P1 e apresentação

---

### Sprint 3 – 03/10 a 16/10

**Objetivo:** Construção da AST e início da análise semântica (variáveis e tipos).

**Entregáveis:**

- Estruturas da AST implementadas
- Parser gerando AST
- Tabela de símbolos inicial criada
- Testes semânticos básicos realizados

**Tarefas:**

- Implementar estrutura da AST
- Modificar parser para gerar AST
- Criar tabela de símbolos inicial
- Realizar testes semânticos básicos

---

### Sprint 4 – 17/10 a 30/10

**Objetivo:** Implementação da execução sobre a AST e aprimoramento da análise semântica. Preparação do Ponto de Controle P2.

**Entregáveis:**

- Interpretador funcional implementado
- Análise semântica aprimorada
- Apresentação P2 preparada

**Tarefas:**

- Implementar execução sobre a AST
- Aprimorar análise semântica
- Realizar testes com códigos reais e extensos
- Preparar apresentação P2

---

### Sprint 5 – 31/10 a 20/11

**Objetivo:** Otimizações, inclusão de recursos adicionais e testes integrados. Preparação para entrega final.

**Entregáveis:**

- Interpretador ampliado
- Testes integrados realizados
- Versão final consolidada

**Tarefas:**

- Realizar otimizações no código
- Incluir recursos adicionais
- Realizar testes integrados cobrindo todo o escopo
- Preparar versão final consolidada

---

### Sprint 6 – 21/11 a 04/12

**Objetivo:** Entrevista final com professor, ajustes finais e conclusão da documentação.

**Entregáveis:**

- Entrevista final realizada
- Ajustes finais realizados
- Documentação completa concluída

**Tarefas:**

- Realizar entrevista final com o professor
- Realizar ajustes finais no código e documentação
- Concluir documentação completa

# Histórico de versões

| Versão | Data       | Autor           | Descrição da Alteração                  | Revisor   |
|--------|-----------|----------------|----------------------------------------|--------------|
| 1.0    | 13/09/2025 | Ana Catarina    | Adição planejamento das sprints | |
