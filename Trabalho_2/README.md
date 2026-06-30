# 🌐 Simulador de Navegador (Melhorado!) - Pilhas Encadeadas Dinâmicas em C

Programa que simula os botões **Voltar** e **Avançar** de um navegador web usando **duas pilhas encadeadas dinâmicas** (histórico e futuro), com mensagens amigáveis, estatísticas e relatórios completos!

---

## ✨ Novidades e Melhorias

- 🎉 Mensagens mais amigáveis e intuitivas com emojis
- 📊 Estatísticas de navegação (total de páginas visitadas, páginas no histórico, páginas no futuro)
- 📄 Geração de relatórios completos em arquivo .txt com data/hora
- 🔍 Melhor feedback nas operações de voltar e avançar (mostra a página atual)
- 📝 Melhor contagem de páginas visitadas (apenas novas visitas contam)
- 👋 Tela de boas-vindas
- 🚪 Mensagem de despedida
- 📚 Melhor exibição de pilhas

---

## 📋 Funcionalidades

- ✅ **Pilhas Encadeadas Dinâmicas**: Implementação com nós contendo ponteiros para o próximo elemento
- ✅ **Alocação Dinâmica**: Uso de `malloc()` e `free()` para gerenciar memória das pilhas
- ✅ **Duas pilhas independentes**: Histórico e futuro
- ✅ **Operações completas**: Push, Pop, Peek, Listar, Limpar
- ✅ **Menu interativo** com opções numéricas e emojis
- ✅ **Persistência**: Salva e carrega dados em arquivos CSV
- ✅ **Controle de memória**: Libera todos os nós ao sair
- ✅ **Estatísticas**: Total de páginas visitadas, páginas no histórico, páginas no futuro
- ✅ **Relatórios**: Geração de relatórios detalhados em arquivo .txt

---

## 🔍 Estrutura de Dados

### Campos do Registro (Página)

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `url` | `char[100]` | Endereço da página |
| `titulo` | `char[50]` | Título da página |
| `dataHora` | `char[20]` | Data e hora da visita |
| `prox` | `struct Pagina*` | Ponteiro para a próxima página na pilha |

---

## 📁 Estrutura do Projeto

```
.
├── main.c                      # Código-fonte completo (melhorado)
├── Makefile                    # Script de compilação via make
├── compile.bat                 # Compilação automática (Windows)
├── historico.csv               # Arquivo de dados do histórico
├── futuro.csv                  # Arquivo de dados do futuro
├── relatorio_navegacao_*.txt   # Relatórios gerados pelo programa
└── README.md                   # Este arquivo (atualizado)
└── QUICKSTART.md               # Guia rápido (atualizado)
└── TESTES.md                   # Plano de testes (atualizado)
```

---

## 🛠️ Compilação e Execução Direta no Terminal

### Windows (MinGW/GCC)

```bash
# Compile
gcc -Wall -Wextra -std=c99 -o navegador main.c

# Execute diretamente
./navegador

# Ou use o script
compile.bat
```

### Linux/macOS

```bash
# Compile
gcc -Wall -Wextra -std=c99 -o navegador main.c

# Execute
./navegador

# Ou use make
make run
```

---

## 📖 Menu Principal

```
--- SIMULADOR DE NAVEGADOR ---
1.  🌐 Visitar nova página
2.  ↩️ Voltar (página anterior)
3.  ↪️ Avançar (próxima página)
4.  📄 Ver página atual (peek)
5.  📚 Listar histórico
6.  ⏭️ Listar futuro
7.  💾 Salvar navegação em CSV
8.  📂 Carregar navegação do CSV
9.  🗑️ Limpar histórico
10. 🗑️ Limpar futuro
11. 📊 Estatísticas de páginas visitadas
12. 📄 Exportar relatório completo
13. 🚪 Sair
```

---

## 🎯 Exemplo de Fluxo

1. 🌐 Visitar: `google.com` → Título: `Google`
2. 🌐 Visitar: `github.com` → Título: `GitHub`
3. 🌐 Visitar: `stackoverflow.com` → Título: `Stack Overflow`
4. ↩️ Voltar → Página atual: GitHub
5. ↩️ Voltar → Página atual: Google
6. ↪️ Avançar → Página atual: GitHub
7. 🌐 Visitar: `youtube.com` → Título: YouTube (futuro é limpo!)
8. 📚 Listar histórico → [YouTube, GitHub, Google]

---

## 💾 Formato CSV

`historico.csv` e `futuro.csv` seguem o formato:

```csv
url;titulo;dataHora
google.com;Google;14/06/2026 10:00
github.com;GitHub;14/06/2026 10:01
stackoverflow.com;Stack Overflow;14/06/2026 10:02
```

Os arquivos são gravados da base para o topo para preservar a ordem no carregamento.

---

## 📊 Estatísticas

```
📊 Estatísticas de Navegação
  📈 Total de páginas visitadas na sessão: 5
  📚 Páginas no histórico: 3
  ⏭️ Páginas no futuro: 2
```

---

## 📄 Relatórios

Gera um arquivo `relatorio_navegacao_YYYY-MM-DD_HH-MM-SS.txt` com:
- Data e hora de geração
- Resumo das estatísticas
- Histórico completo (do topo à base)
- Futuro completo (do topo à base)

---

## ✅ Validações Implementadas

- ✅ Pilha vazia verificada antes de pop e peek com mensagens amigáveis
- ✅ Memória alocada com verificação de erro
- ✅ Campos URL e Título não podem ser vazios
- ✅ Data/hora preenchida automaticamente
- ✅ Confirmação antes de limpar pilha
- ✅ Tratamento de erro ao abrir arquivos CSV
- ✅ Liberação de memória ao sair
- ✅ Feedback claro em todas as operações

---

## 🧠 Conceitos Aplicados

| Conceito | Onde é usado |
|----------|-------------|
| LIFO (Last In, First Out) | Pilhas de histórico e futuro |
| Lista Encadeada Dinâmica | Implementação das pilhas |
| Alocação Dinâmica | `malloc()` para criar nós, `free()` para liberar |
| Ponteiros | Manipulação da pilha encadeada |
| Persistência | Leitura e escrita de arquivos CSV |
| Estatísticas e Relatórios | Novas funcionalidades |

---

## 📊 Complexidade

| Operação | Complexidade |
|----------|-------------|
| Push | O(1) |
| Pop | O(1) |
| Peek | O(1) |
| Listar | O(n) |
| Salvar/Carregar | O(n) |
| Limpar Pilha | O(n) |

---

## 👋 Autor

Implementação de pilhas encadeadas dinâmicas em C, melhorada com mensagens amigáveis, estatísticas e relatórios!  
Tema: Simulador de Navegador.

---

## 📄 Licença

Este projeto foi desenvolvido como atividade educacional.
