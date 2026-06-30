# ⚡ Guia Rápido - Gerenciador de Playlist (Melhorado!)

## 📥 Instalação e Compilação
### Windows
```bash
# 1. Abra o terminal na pasta do projeto
# 2. Compile o programa
gcc -Wall -Wextra -std=c99 -o playlist main.c

# 3. Execute diretamente
./playlist

# Ou usando o script de compilação automática
compile.bat
```

### Linux/macOS
```bash
# Compile
gcc -Wall -Wextra -std=c99 -o playlist main.c

# Execute
./playlist

# Ou usando make
make run
```

## 🚀 Primeiro Uso

O programa já vem com uma **playlist de exemplo** em `playlist.csv`!  
Ao iniciar, o programa carrega automaticamente e mostra quantas músicas foram carregadas!

## 🎯 Teste Rápido (5 minutos)

### Passo 1: Listar Músicas
- Opção **5** → Ver todas as músicas da playlist!

### Passo 2: Inserir Música
- Opção **1**
- ID: **100** (deve ser único e positivo)
- Título: **Minha Música Favorita** (não pode ser vazio)
- Artista: **Meu Artista Preferido** (não pode ser vazio)
- Duração: **240** (deve ser > 0)
- Gênero: **Pop** (não pode ser vazio)
- Resultado: Música adicionada com sucesso!

### Passo 3: Ver Estatísticas
- Opção **6** → Mostra total de músicas, duração total e média!

### Passo 4: Gerar Relatório
- Opção **7** → Cria um arquivo .txt com todas as informações!

### Passo 5: Buscar Música
- Opção **2** → ID: **1** → Vê os detalhes da música!

### Passo 6: Editar Música
- Opção **3** → ID: **100** → Altere campos (deixe em branco para manter o valor atual!)

### Passo 7: Excluir Música
- Opção **4** → ID: **100** → Confirme a exclusão!

### Passo 8: Salvar
- Opção **8** → Salva em playlist.csv!

### Passo 9: Sair
- Opção **0** → Salva automaticamente e sai!

## 🐛 Troubleshooting

### Erro: "gcc não encontrado"
- Instale [MinGW](https://www.mingw-w64.org/) no Windows
- Ou instale [Code::Blocks](https://www.codeblocks.org/) com MinGW
- Ou use [TDM-GCC](https://jmeubank.github.io/tdm-gcc/)

### Erro ao compilar
1. Verifique se `main.c` está na pasta
2. Certifique-se que gcc está no PATH
3. Tente: `compile.bat` novamente

### Arquivo CSV não encontrado
- Normal na primeira vez! O programa cria um ao salvar
- Uma cópia exemplo já existe: `playlist.csv`

### Mensagem "ID já existe!"
- Escolha outro ID, pois IDs devem ser únicos!

### Mensagem "Campo não pode ser vazio!"
- Preencha todos os campos obrigatórios (título, artista, gênero)!

## 📖 Menu Completo
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

## 💡 Exemplos Rápidos

### Inserir (ID deve ser único e positivo!)
```
🎵 Inserir Nova Música
ID: 100
Título: Amazing Song
Artista: Super Artista
Duração (segundos): 240
Gênero: Rock

🎉 Música adicionada com sucesso!
```

### Editar (deixe em branco para manter o valor!)
```
✏️ Editar Música
Digite o ID da música que deseja editar: 100

🎵 Música atual: Amazing Song - Super Artista
(Deixe em branco para manter o valor atual)

Novo título: Amazing Song 2.0
Novo artista: Super Artista
Nova duração (segundos): 
Novo gênero: Rock

✅ Música editada com sucesso!
```

## 📊 Estrutura dos Dados

Cada música tem:
- **ID**: Número único e positivo
- **Título**: Até 50 caracteres (não vazio)
- **Artista**: Até 50 caracteres (não vazio)
- **Duração**: Segundos (> 0)
- **Gênero**: Até 30 caracteres (não vazio)

## 🔧 Arquivos Importantes

| Arquivo | Função |
|---------|--------|
| `main.c` | Código-fonte completo (melhorado) |
| `playlist.csv` | Arquivo de dados |
| `relatorio_playlist_*.txt` | Relatórios gerados |
| `compile.bat` | Compilação automática (Windows) |
| `Makefile` | Compilação via make |
| `README.md` | Documentação completa |
| `TESTES.md` | Plano de testes |

## 🎓 O Que Você Aprenderá

✅ Listas encadeadas dinâmicas
✅ Ponteiros em C
✅ Alocação/Liberação de memória (malloc/free)
✅ Busca e manipulação de dados em listas
✅ Leitura/Escrita de arquivos CSV
✅ Menu interativo com emojis
✅ Validações robustas de entrada
✅ Cálculo de estatísticas
✅ Geração de relatórios em arquivo

## ❓ FAQ

**P: Posso ter várias playlists?**
R: Não neste projeto. Mas você pode renomear `playlist.csv` para backup e criar novas!

**P: Qual é o máximo de músicas?**
R: Ilimitado, dependendo da memória disponível. Usa alocação dinâmica!

**P: O ID pode ser qualquer número?**
R: Sim, desde que seja único e positivo! Recomenda-se: 1, 2, 3...

**P: Posso usar caracteres especiais no título?**
R: Sim, mas o CSV usa `;` como separador. Evite `;` nos dados!

**P: Os dados são salvos automaticamente?**
R: Sim! Ao sair (opção 0), a playlist é salva automaticamente!

## 🚀 Próximos Passos Após Criar Tudo

1. ✅ Compile o programa
2. ✅ Execute diretamente no terminal
3. ✅ Teste com os exemplos acima
4. ✅ Consulte `TESTES.md` para testes completos
5. ✅ Estude o código em `main.c`
6. ✅ Faça modificações conforme necessário!

## 📞 Suporte

- Leia o `README.md` para documentação completa
- Veja `TESTES.md` para validar tudo funciona
- Revise o código em `main.c` para entender a implementação
- Dúvidas? Consulte os comentários no código!

---

**Aproveite o Gerenciador de Playlist melhorado! 🎵**
