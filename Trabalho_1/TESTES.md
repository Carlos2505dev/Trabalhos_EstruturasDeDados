# 🧪 Plano de Testes - Gerenciador de Playlist (Melhorado!)

---

## ✨ Novidades nos Testes
- Testes para as novas funcionalidades (Estatísticas, Relatórios)
- Testes para as validações adicionais (ID positivo, campos não vazios, duração > 0)
- Testes para a edição com campo em branco

---

## Casos de Teste

### 1. ✅ Teste: Inserir Música Válida
**Objetivo**: Verificar se uma música é inserida corretamente na lista encadeada.

**Pré-condição**: Programa iniciado.
**Passos**:
1. Escolher opção 1 (Inserir música).
2. ID: 100 (positivo).
3. Título: Test Song (não vazio).
4. Artista: Test Artist (não vazio).
5. Duração: 240 (> 0).
6. Gênero: Pop (não vazio).

**Resultado Esperado**:
```
🎉 Música adicionada com sucesso!
📋 Test Song - Test Artist (4m 00s)
```

---

### 2. ❌ Teste: Inserir Música com ID Duplicado
**Objetivo**: Validar se o sistema impede IDs duplicados.

**Pré-condição**: Música com ID 1 já existe.
**Passos**:
1. Escolher opção 1 (Inserir música).
2. ID: 1.
3. Preencher outros campos.

**Resultado Esperado**: `Ops! Já existe uma música com o ID 1. Escolha outro!`

---

### 3. ❌ Teste: Inserir Música com ID Zero ou Negativo
**Objetivo**: Validar que o ID deve ser positivo.

**Pré-condição**: Programa iniciado.
**Passos**:
1. Escolher opção 1 (Inserir música).
2. ID: 0 (ou -5).

**Resultado Esperado**: `Erro: ID deve ser positivo!`

---

### 4. ❌ Teste: Inserir Música com Campo Vazio
**Objetivo**: Validar campos obrigatórios não vazios.

**Pré-condição**: Programa iniciado.
**Passos**:
1. Escolher opção 1 (Inserir música).
2. ID: 101.
3. Título: (deixar vazio, só pressionar Enter).

**Resultado Esperado**: `Erro: Título não pode ficar vazio!` (ou similar para artista/gênero).

---

### 5. ❌ Teste: Inserir Música com Duração Inválida
**Objetivo**: Validar que a duração deve ser maior que zero.

**Pré-condição**: Programa iniciado.
**Passos**:
1. Escolher opção 1 (Inserir música).
2. Preencher ID, título, artista.
3. Duração: 0 (ou -10).

**Resultado Esperado**: `Erro: Duração deve ser um número positivo!`

---

### 6. 🔍 Teste: Buscar Música Existente
**Objetivo**: Verificar se a busca encontra a música corretamente.

**Pré-condição**: Música com ID 1 existe.
**Passos**:
1. Escolher opção 2 (Buscar música por ID).
2. ID: 1.

**Resultado Esperado**:
```
✨ Música Encontrada!
🆔 ID: 1
🎵 Título: Bohemian Rhapsody
🎤 Artista: Queen
⏱️ Duração: 5m 54s
🎶 Gênero: Rock
```

---

### 7. 🔍 Teste: Buscar Música Inexistente
**Objetivo**: Validar mensagem correta para ID não encontrado.

**Pré-condição**: Nenhuma música com ID 999.
**Passos**:
1. Escolher opção 2 (Buscar música por ID).
2. ID: 999.

**Resultado Esperado**: `Desculpe, não encontrei nenhuma música com o ID 999.`

---

### 8. 🔍 Teste: Buscar com Lista Vazia
**Objetivo**: Validar mensagem ao buscar em lista vazia.

**Pré-condição**: Lista completamente vazia.
**Passos**:
1. Escolher opção 2 (Buscar música por ID).

**Resultado Esperado**: `Ainda não há músicas na playlist!`

---

### 9. ✏️ Teste: Editar Música Existente (Campos Alterados)
**Objetivo**: Verificar se a edição atualiza todos os campos corretamente.

**Pré-condição**: Música com ID 1 existe.
**Passos**:
1. Escolher opção 3 (Editar música).
2. ID: 1.
3. Novo título: Novo Título.
4. Novo artista: Novo Artista.
5. Nova duração (segundos): 500.
6. Novo gênero: Rock.

**Resultado Esperado**: `✅ Música editada com sucesso!`

---

### 10. ✏️ Teste: Editar Música (Deixar Campo em Branco)
**Objetivo**: Verificar se campos em branco mantêm o valor atual.

**Pré-condição**: Música com ID 1 existe.
**Passos**:
1. Escolher opção 3 (Editar música).
2. ID: 1.
3. Novo título: (deixar em branco).
4. Novo artista: Artista Alterado.
5. Nova duração (segundos): (deixar em branco).
6. Novo gênero: (deixar em branco).

**Resultado Esperado**: `✅ Música editada com sucesso!` (apenas o artista é alterado).

---

### 11. ✏️ Teste: Editar Música Inexistente
**Objetivo**: Validar mensagem correta para ID não encontrado.

**Pré-condição**: Nenhuma música com ID 999.
**Passos**:
1. Escolher opção 3 (Editar música).
2. ID: 999.

**Resultado Esperado**: `Desculpe, não encontrei nenhuma música com o ID 999.`

---

### 12. ✏️ Teste: Editar com Lista Vazia
**Objetivo**: Validar mensagem ao editar em lista vazia.

**Pré-condição**: Lista completamente vazia.
**Passos**:
1. Escolher opção 3 (Editar música).

**Resultado Esperado**: `Ainda não há músicas para editar!`

---

### 13. 🗑️ Teste: Excluir Primeira Música
**Objetivo**: Verificar se exclusão do primeiro elemento funciona.

**Pré-condição**: Lista tem músicas [1, 2, 3].
**Passos**:
1. Escolher opção 4 (Excluir música).
2. ID: 1.
3. Confirmar exclusão com 'S' ou 's'.

**Resultado Esperado**:
```
✅ Música com ID 1 foi removida da playlist!
```
Lista fica [2, 3].

---

### 14. 🗑️ Teste: Excluir Música (Cancelar)
**Objetivo**: Verificar se a exclusão pode ser cancelada.

**Pré-condição**: Música com ID 1 existe.
**Passos**:
1. Escolher opção 4 (Excluir música).
2. ID: 1.
3. Responder 'N' ou 'n' para confirmação.

**Resultado Esperado**: `Exclusão cancelada! A música permanece na playlist.`

---

### 15. 📋 Teste: Listar com Lista Vazia
**Objetivo**: Verificar comportamento com lista vazia.

**Pré-condição**: Lista completamente vazia.
**Passos**:
1. Escolher opção 5 (Listar todas as músicas).

**Resultado Esperado**: `📭 A playlist está vazia! Adicione algumas músicas para começar.`

---

### 16. 📊 Teste: Exibir Estatísticas
**Objetivo**: Verificar se as estatísticas são calculadas corretamente.

**Pré-condição**: Lista com 8 músicas, total de duração 2120 segundos.
**Passos**:
1. Escolher opção 6 (Estatísticas da playlist).

**Resultado Esperado**:
```
📊 ESTATÍSTICAS DA PLAYLIST
🎵 Total de músicas: 8
⏱️ Duração total: 35m 20s
📈 Média por música: 4m 25s
```

---

### 17. 📄 Teste: Gerar Relatório
**Objetivo**: Verificar se o arquivo de relatório é gerado corretamente.

**Pré-condição**: Lista com algumas músicas.
**Passos**:
1. Escolher opção 7 (Gerar relatório).
2. Verificar se o arquivo `relatorio_playlist_*.txt` foi criado.
3. Abrir o arquivo e verificar se contém todas as informações.

**Resultado Esperado**:
- Mensagem: `✅ Relatório gerado com sucesso! 📄 Arquivo: relatorio_playlist_*.txt`
- Arquivo existe com data e hora no nome.
- Arquivo contém resumo e detalhes das músicas.

---

### 18. 💾 Teste: Salvar em CSV
**Objetivo**: Verificar se o arquivo é criado corretamente.

**Pré-condição**: Algumas músicas na lista.
**Passos**:
1. Escolher opção 8 (Salvar em CSV).

**Resultado Esperado**: `✅ Playlist salva com sucesso! 📋 X músicas salvas em playlist.csv`

---

### 19. 📂 Teste: Carregar do CSV
**Objetivo**: Verificar se os dados são recuperados corretamente.

**Pré-condição**: Arquivo `playlist.csv` existe com dados.
**Passos**:
1. Escolher opção 9 (Carregar do CSV).

**Resultado Esperado**: `✅ Playlist carregada com sucesso! 📋 X músicas carregadas`

---

### 20. 🚪 Teste: Sair (Salva Automaticamente)
**Objetivo**: Verificar se a opção 0 salva e libera memória.

**Pré-condição**: Lista com músicas.
**Passos**:
1. Escolher opção 0 (Sair).

**Resultado Esperado**:
```
💾 Salvando playlist...
✅ Playlist salva com sucesso!
👋 Obrigado por usar o Gerenciador de Playlist! Até a próxima!
```

---

## 📊 Sumário de Testes

| Categoria | Total |
|-----------|-------|
| Inserção (incluindo validações) | 5 |
| Busca | 3 |
| Edição | 3 |
| Exclusão | 2 |
| Listagem | 1 |
| Estatísticas | 1 |
| Relatórios | 1 |
| CSV | 2 |
| Saída | 1 |
| **TOTAL** | **20** |

---

## 📝 Instruções de Execução

1. Compile o programa diretamente no terminal: `gcc -Wall -Wextra -std=c99 -o playlist main.c`
2. Execute diretamente: `./playlist`
3. Realize os testes na ordem especificada
4. Marque ✅ ou ❌ em cada teste
5. Relate qualquer comportamento inesperado

---

## ✅ Checklist Final

- [ ] Todas as opções do menu funcionam corretamente
- [ ] IDs duplicados são rejeitados
- [ ] ID positivo é validado
- [ ] Campos vazios são rejeitados
- [ ] Duração > 0 é validada
- [ ] Busca exibe todos os campos corretamente com emojis
- [ ] Edição funciona com campos em branco (mantém valor atual)
- [ ] Exclusão com confirmação funciona
- [ ] Listagem exibe duração formatada (h m s)
- [ ] Estatísticas são calculadas corretamente
- [ ] Relatório é gerado com data/hora no nome
- [ ] CSV salva e carrega dados com separador `;`
- [ ] Sair (opção 0) salva automaticamente
- [ ] Dados persistem entre execuções
- [ ] Mensagens amigáveis são exibidas em todas as operações
- [ ] Sem crashes ou travamentos
- [ ] Nenhum vazamento de memória
