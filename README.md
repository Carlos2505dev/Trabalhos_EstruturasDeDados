# Trabalhos de Estruturas de Dados

![C](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Estruturas de Dados](https://img.shields.io/badge/Disciplina-Estruturas%20de%20Dados-brightgreen.svg)
![Professor](https://img.shields.io/badge/Professor-Nirton%20Afonso-orange.svg)

**Autores:** Carlos Bezerra, Caio Ricardo e Marcos Antônio

Repositório contendo os trabalhos desenvolvidos para a disciplina de **Estruturas de Dados**, ministrada pelo professor **Nirton Afonso**. Todos os projetos foram implementados na linguagem C, abordando diferentes estruturas de dados **dinâmicas**!

---

## ✨ Novidades e Melhorias Recentes

Todos os trabalhos foram aprimorados com:
- 🎉 **Mensagens mais amigáveis** com emojis em todas as interações
- 📊 **Estatísticas detalhadas** sobre o uso do programa
- 📄 **Relatórios completos** em arquivo .txt com data/hora no nome
- 🔍 **Validações adicionais** para entrada de dados mais segura
- 🎨 **Interface melhorada** com feedback claro ao usuário
- 💾 **Persistência automática** em arquivo CSV

---

## 📚 Resumo dos Trabalhos

### [Trabalho 1: Gerenciador de Playlist](./Trabalho_1)

**Estrutura de Dados:** Lista Encadeada Dinâmica

Um programa em C para gerenciamento de uma playlist de músicas.

- **Funcionalidades:** Inserção, busca por ID, edição (com campo em branco para manter valor), exclusão, listagem completa, estatísticas e relatórios.
- **Características:** Persistência automática em arquivo CSV, validação de IDs duplicados e positivos, campos não vazios, duração > 0, formatação da duração em horas/minutos/segundos, e carregamento automático com feedback.

### [Trabalho 2: Simulador de Navegador Web](./Trabalho_2)

**Estrutura de Dados:** Pilhas Encadeadas Dinâmicas (Histórico e Futuro)

Simula o funcionamento dos botões "Voltar" e "Avançar" de um navegador web.

- **Funcionalidades:** Controle de navegação utilizando duas pilhas independentes (Histórico e Futuro). Operações de Push, Pop, Peek, listagem, limpeza com confirmação, estatísticas e relatórios.
- **Características:** Gravação e leitura do histórico/futuro a partir de arquivos CSV, navegação fluida baseada no conceito LIFO (*Last In, First Out*), data/hora automática nas visitas, e feedback claro nas operações de voltar/avançar.

### [Trabalho 3: Gerenciador de Fila de Impressão](./Trabalho_3)

**Estrutura de Dados:** Filas Encadeadas Dinâmicas (Fila Normal e Fila Prioritária)

Simula o gerenciamento de uma fila de impressão de documentos com dois níveis de prioridade.

- **Funcionalidades:** Enfileiramento, processamento intercalado de trabalhos (1 prioritário para cada 2 normais), consultas, limpeza de filas com confirmação, estatísticas e relatórios.
- **Características:** Persistência em arquivo CSV, validação de IDs únicos e positivos, nome de arquivo não vazio, páginas > 0, prioridade 0/1, e timestamp automático nas impressões.

---

## 🛠️ Como Executar

Cada trabalho está contido em sua respectiva pasta (`Trabalho_1`, `Trabalho_2`, `Trabalho_3`). Dentro de cada diretório, existem arquivos `Makefile` (para ambientes Unix) e scripts `.bat` (para Windows) que facilitam a compilação e execução. Consulte o arquivo `README.md` individual de cada trabalho para obter instruções detalhadas.

---

## 📁 Estrutura do Repositório

```
.
├── Trabalho_1/              # Gerenciador de Playlist (Lista Encadeada Dinâmica)
│   ├── main.c               # Código-fonte (melhorado!)
│   ├── Makefile             # Compilação Unix
│   ├── compile.bat          # Compilação Windows
│   ├── playlist.csv         # Arquivo de dados
│   ├── README.md            # Documentação completa
│   ├── QUICKSTART.md        # Guia rápido
│   └── TESTES.md            # Plano de testes
├── Trabalho_2/              # Simulador de Navegador (Pilhas Encadeadas Dinâmicas)
│   ├── main.c               # Código-fonte (melhorado!)
│   ├── Makefile             # Compilação Unix
│   ├── compile.bat          # Compilação Windows
│   ├── historico.csv        # Arquivo de dados
│   ├── futuro.csv           # Arquivo de dados
│   ├── README.md            # Documentação completa
│   ├── QUICKSTART.md        # Guia rápido
│   └── TESTES.md            # Plano de testes
├── Trabalho_3/              # Gerenciador de Fila de Impressão (Filas Encadeadas Dinâmicas)
│   ├── main.c               # Código-fonte (melhorado!)
│   ├── Makefile             # Compilação Unix
│   ├── compile.bat          # Compilação Windows
│   ├── fila_impressao.csv   # Arquivo de dados
│   ├── README.md            # Documentação completa
│   ├── QUICKSTART.md        # Guia rápido
│   └── TESTES.md            # Plano de testes
└── README.md                # Este arquivo (atualizado!)
```
