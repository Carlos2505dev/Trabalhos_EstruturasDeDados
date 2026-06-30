# 📄 Gerenciador de Fila de Impressão (Melhorado!)

Um programa completo para gerenciar filas de impressão em C usando filas encadeadas dinâmicas com prioridade, mensagens amigáveis, estatísticas detalhadas e relatórios com timestamp!

---

## ✨ Novidades e Melhorias

- 🎉 **Mensagens Amigáveis**: Todas as interações do usuário agora usam emojis e mensagens claras e amigáveis!
- 📊 **Estatísticas Detalhadas**: Opção para ver estatísticas das filas e impressões!
- 📄 **Relatórios com Timestamp**: Gerar relatórios completos em arquivo .txt com a data e hora no nome!
- 🧹 **Limpeza de Filas**: Limpar todas as filas com confirmação do usuário!
- 📅 **Data/Hora Automática**: Timestamp de impressão gerado automaticamente!
- 🔍 **Melhor Feedback**: Todas as operações (adicionar, atender, etc.) dão feedback claro ao usuário!
- 👋 **Tela de Boas-Vindas**: Mensagem de boas-vindas ao abrir o programa!
- 🚪 **Mensagem de Despedida**: Mensagem de despedida ao sair do programa!

---

## 📋 Funcionalidades Principais

### Operações de Fila
- 📄 **Adicionar à Fila**: Adiciona documentos à fila de espera normal ou prioritária
- 🖨️ **Atender Impressão**: Atende o próximo documento da fila, respeitando prioridade
- 📋 **Listar Filas**: Mostra o estado das filas normal e prioritária
- 🧹 **Limpar Filas**: Limpa todas as filas com confirmação
- 💾 **Salvar/Carregar**: Persiste os dados em arquivo CSV
- 📊 **Estatísticas**: Mostra estatísticas das filas e impressões
- 📄 **Relatórios**: Gera relatórios completos com timestamp
- 🧹 **Liberar Memória**: Libera toda a memória alocada

---

## 🔍 Regras de Atendimento

A fila segue a regra de atendimento com **proporcionalidade**:
- **1 documento prioritário**: atendido a cada **2 documentos normais**
- Se só houver documentos prioritários → atendidos imediatamente
- Se só houver documentos normais → atendidos normalmente

---

## 📁 Estrutura de Arquivos

```
Trabalho_3/
├── main.c                      # Código-fonte completo (melhorado!)
├── Makefile                    # Makefile para compilação no Linux/macOS
├── compile.bat                 # Script de compilação no Windows
├── fila_impressao.csv          # Arquivo de dados CSV (gerado automaticamente)
├── relatorio_impressao_*.txt   # Relatórios gerados (com timestamp!)
├── README.md                   # Este arquivo
├── QUICKSTART.md               # Guia rápido
└── TESTES.md                   # Plano de testes
```

---

## 🛠️ Compilação e Execução

### No Windows (MinGW)
1. Abra o terminal na pasta do projeto
2. Compile o programa: `gcc -Wall -Wextra -std=c99 -o fila_impressao main.c`
3. Execute o programa: `./fila_impressao`
4. Ou use o script: `compile.bat`

### No Linux/macOS
1. Compile usando make: `make`
2. Execute: `./fila_impressao`

---

## 📖 Menu Principal

```
📄 GERENCIADOR DE FILA DE IMPRESSÃO 🖨️
1.  📄 Adicionar Documento à Fila
2.  🖨️ Atender Próxima Impressão
3.  📋 Listar Filas de Impressão
4.  💾 Salvar Filas em Arquivo
5.  📂 Carregar Filas de Arquivo
6.  🧹 Limpar Todas as Filas
7.  📊 Estatísticas das Filas
8.  📄 Gerar Relatório Completo
0.  🚪 Sair do Programa
```

---

## 📊 Campo de Dados

### Struct Documento
| Campo | Tipo | Descrição |
|-------|------|-----------|
| `id` | `int` | ID único do documento |
| `nomeArquivo` | `char[100]` | Nome do arquivo |
| `prioridade` | `int` | 0 = Normal, 1 = Prioritária |
| `numPaginas` | `int` | Número de páginas do documento |
| `timestamp` | `char[20]` | Data/hora da impressão (dd/mm/aaaa hh:mm) |

---

## 💾 Formato CSV

O arquivo `fila_impressao.csv` segue o formato:
```csv
tipo_fila;id;nomeArquivo;prioridade;numPaginas;timestamp
normal;1;relatorio.pdf;0;25;14/06/2026 10:30
prioritaria;2;urgente.docx;1;10;14/06/2026 10:31
```

Onde `tipo_fila` pode ser `normal` ou `prioritaria`.

---

## 📄 Exemplo de Relatório Gerado

O arquivo `relatorio_impressao_*.txt` conterá:
1. Data e hora de geração
2. Estatísticas das filas
3. Lista completa das filas (normal e prioritária)
4. Lista dos documentos já atendidos

---

## 🧠 Conceitos Aplicados

- **Fila Encadeada Dinâmica**: Implementação com struct e ponteiros para próximo elemento
- **FIFO (First-In, First-Out)**: Política padrão para filas de impressão
- **Prioridade**: Atendimento com proporcionalidade (1 prioritário a cada 2 normais)
- **Alocação Dinâmica**: Uso de malloc() e free()
- **Persistência**: Leitura e escrita de arquivos CSV
- **Validação**: Validação de entrada do usuário (ID único, páginas > 0, etc.)

---

## 🔒 Validações Implementadas

- ✅ **ID Único**: Valida que o documento não tem ID duplicado
- ✅ **ID Positivo**: Valida que o ID é um número positivo
- ✅ **Nome de Arquivo Não Vazio**: Valida que o nome do arquivo não é vazio
- ✅ **Número de Páginas > 0**: Valida que o número de páginas é maior que zero
- ✅ **Prioridade Válida**: Valida que a prioridade é 0 ou 1
- ✅ **Fila Vazia**: Verifica se a fila está vazia antes de atender
- ✅ **Confirmação**: Confirmação do usuário antes de limpar as filas
- ✅ **Arquivo CSV**: Trata erros de leitura e escrita em arquivo

---

## 👋 Autor

Implementação de fila encadeada dinâmica em C, com atendimento por prioridade, mensagens amigáveis, estatísticas e relatórios!  
Tema: Gerenciador de Fila de Impressão!

---

## 📄 Licença

Desenvolvido para fins educacionais!
