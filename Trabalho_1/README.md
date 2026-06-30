# 🎵 Gerenciador de Playlist - Lista Encadeada Dinâmica em C

Um programa de gerenciamento de playlist usando **lista encadeada dinâmica** implementado em C, com menu interativo, persistência em CSV, estatísticas detalhadas, relatórios e mensagens amigáveis!

## ✨ Novidades e Melhorias
- 🎉 Mensagens mais amigáveis e intuitivas
- 📊 Estatísticas da playlist (total de músicas, duração total, média por música)
- 📄 Geração de relatórios detalhados em arquivo .txt com data/hora
- 🔍 Validações adicionais (ID positivo, campos não vazios, duração > 0)
- � Formatação melhorada da duração (horas, minutos, segundos)
- 🔄 Carregamento automático da playlist ao iniciar com feedback
- 🎨 Interface com emojis para melhor experiência do usuário

## 📋 Funcionalidades
- ✅ **Lista Encadeada Dinâmica**: Implementação com `struct Musica` contendo ponteiro para próximo elemento
- ✅ **Alocação Dinâmica**: Uso de `malloc()` e `free()` para gerenciar memória
- ✅ **Menu Interativo**: Interface com opções numéricas e emojis
- ✅ **Persistência**: Salva e carrega dados em arquivo CSV automaticamente
- ✅ **ID Único**: Validação para evitar IDs duplicados e ID positivo
- ✅ **Operações Completas**: Inserir, Buscar, Editar, Excluir, Listar
- ✅ **Estatísticas**: Total de músicas, duração total, média por música
- ✅ **Relatórios**: Geração de relatórios detalhados em arquivo .txt

## 🎼 Campos da Música
| Campo | Tipo | Descrição |
|-------|------|-----------|
| id | int | Identificador único (positivo) |
| titulo | char[50] | Título da música |
| artista | char[50] | Nome do artista |
| duracao | int | Duração em segundos |
| genero | char[30] | Gênero musical |
| prox | struct Musica* | Ponteiro para próxima música na lista |

## 📁 Estrutura do Projeto
```
.
├── main.c                       # Código-fonte completo (melhorado)
├── Makefile                     # Script de compilação (Linux/macOS/Windows com MinGW)
├── compile.bat                  # Compilação automática (Windows)
├── playlist.csv                 # Arquivo de dados de exemplo
├── relatorio_playlist_*.txt     # Relatórios gerados pelo programa
├── README.md                    # Este arquivo (atualizado)
├── QUICKSTART.md                # Guia rápido (atualizado)
└── TESTES.md                    # Plano de testes (atualizado)
```

## 🛠️ Compilação e Execução (Direto no Terminal)

### No Windows (Com MinGW/GCC)
```bash
# Compilar
gcc -Wall -Wextra -std=c99 -o playlist main.c

# Executar diretamente
./playlist

# Ou usando o script
compile.bat
```

### No Linux/macOS
```bash
# Compile
gcc -Wall -Wextra -std=c99 -o playlist main.c

# Execute
./playlist

# Ou usando make
make run
```

## 📖 Menu Principal
```
🎵 GERENCIADOR DE PLAYLIST 🎵
1.  🎵 Inserir música
2.  🔍 Buscar música por ID
3.  ✏️ Editar música
4.  🗑️ Excluir música
5.  📋 Listar todas as músicas
6.  📊 Estatísticas da playlist
7.  📄 Gerar relatório
8.  💾 Salvar em CSV
9.  📂 Carregar do CSV
0.  🚪 Sair
```

## 🎯 Exemplos de Uso

### Inserir Música
```
🎵 Inserir Nova Música
ID: 100
Título: Minha Música Favorita
Artista: Meu Artista Preferido
Duração (segundos): 240
Gênero: Pop

🎉 Música adicionada com sucesso!
📋 Minha Música Favorita - Meu Artista Preferido (4m 00s)
```

### Buscar Música
```
🔍 Buscar Música
Digite o ID da música: 1

✨ Música Encontrada!
🆔 ID: 1
🎵 Título: Bohemian Rhapsody
🎤 Artista: Queen
⏱️ Duração: 5m 54s
🎶 Gênero: Rock
```

## 🔒 Validações Implementadas
- ✅ **Lista Vazia**: Informa quando não há músicas cadastradas
- ✅ **ID Único**: Impede cadastro de músicas com ID duplicado
- ✅ **ID Positivo**: Valida que o ID deve ser maior que zero
- ✅ **Campos Não Vazios**: Título, artista e gênero não podem ser vazios
- ✅ **Duração Válida**: Duração deve ser maior que zero
- ✅ **Busca Segura**: Valida se ID existe antes de operar
- ✅ **Arquivo**: Verifica e trata erros de I/O
- ✅ **Liberação de Memória**: Libera todos os nós ao sair

## 📊 Estatísticas da Playlist
```
📊 ESTATÍSTICAS DA PLAYLIST
🎵 Total de músicas: 8
⏱️ Duração total: 35m 20s
📈 Média por música: 4m 25s
```

## 📝 Arquivo CSV
O arquivo `playlist.csv` segue o formato:
```
id;titulo;artista;duracao;genero
1;Bohemian Rhapsody;Queen;354;Rock
2;Blinding Lights;The Weeknd;200;Pop
```

**Ao iniciar**: O programa carrega automaticamente `playlist.csv` se existir, com feedback!  
**Ao sair (opção 0)**: A playlist é salva automaticamente em `playlist.csv`.

## 📄 Relatórios
Gera um arquivo `relatorio_playlist_YYYY-MM-DD_HH-MM-SS.txt` com:
- Data e hora de geração
- Resumo da playlist
- Detalhes de todas as músicas

## 🧠 Conceitos Implementados
1. **Struct**: Definição do registro `Musica` com ponteiro para próximo
2. **Lista Encadeada Dinâmica**: Inserção no final, busca linear, exclusão com ajuste de ponteiros
3. **Alocação Dinâmica**: Uso de `malloc()` para criar novos nós e `free()` para liberar memória
4. **Busca Linear**: Percorre a lista seguindo os ponteiros
5. **I/O de Arquivo**: Leitura e escrita em CSV
6. **Validação de Dados**: Verificações robustas de entrada do usuário
7. **Estatísticas e Relatórios**: Cálculos e geração de arquivos de relatório

## 🧪 Testes Recomendados
Consulte o arquivo `TESTES.md` para o plano completo de testes!

## 📌 Notas Importantes
- **Alocação Dinâmica**: Memória é alocada conforme necessário, sem limite fixo
- **Liberação de Memória**: Ao sair, todos os nós são liberados com `free()`
- **Ordem de Inserção**: Músicas mantidas na ordem de cadastro (FIFO)

## � Autor
Implementação de lista encadeada dinâmica em C, melhorada com mensagens amigáveis, estatísticas e relatórios!  
Tema: Gerenciador de Playlist

## 📄 Licença
Este projeto foi desenvolvido como atividade educacional.
