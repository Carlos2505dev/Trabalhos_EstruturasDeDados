# ✅ Casos de Teste - Simulador de Navegador (Melhorado!)

---

## ✨ Novidades nos Testes

- Testes para as novas funcionalidades (Estatísticas, Relatórios)
- Testes para o novo feedback nas operações de voltar e avançar
- Testes para a tela de boas-vindas e mensagem de despedida

---

## Casos de Teste

### 1. 🌐 Teste: Visitar Páginas Sequenciais (Push)
**Objetivo**: Verificar se o push empilha corretamente na pilha encadeada dinâmica, com feedback amigável.

**Passos**:
1. Inicie o programa (verifique a tela de boas-vindas!)
2. Opção 1 → URL: `google.com` / Título: `Google`
3. Opção 1 → URL: `github.com` / Título: `GitHub`
4. Opção 1 → URL: `stackoverflow.com` / Título: `Stack Overflow`
5. Opção 5 (Listar histórico)

**Resultado Esperado**:
- Cada visita exibe: `✅ Página visitada com sucesso!`
- Histórico exibe as 3 páginas na ordem correta (Stack Overflow no topo)

---

### 2. 👁️ Teste: Peek - Ver Página Atual Sem Remover
**Objetivo**: Verificar que o peek não altera a pilha encadeada e exibe a página com emojis.

**Passos**:
1. Com 3 páginas no histórico (Teste 1)
2. Opção 4 (Ver página atual) → 3 vezes consecutivas
3. Opção 5 (Listar histórico)

**Resultado Esperado**:
- Cada peek exibe a página com emojis: `📄 Página Atual:`
- Histórico continua com 3 elementos na mesma ordem

---

### 3. ↩️ Teste: Voltar Simples (Pop Histórico + Push Futuro)
**Objetivo**: Verificar a operação de voltar com pilhas encadeadas e o novo feedback.

**Passos**:
1. Histórico: [Stack Overflow, GitHub, Google] (topo → base)
2. Opção 2 (Voltar)

**Resultado Esperado**:
```
✅ Voltou para a página anterior!
  📄 Página atual: GitHub
  🔗 URL: github.com
```

---

### 4. ↪️ Teste: Avançar (Pop Futuro + Push Histórico)
**Objetivo**: Verificar a operação de avançar com pilhas encadeadas e o novo feedback.

**Passos**:
1. Após Teste 3 (futuro tem `stackoverflow.com`)
2. Opção 3 (Avançar)

**Resultado Esperado**:
```
✅ Avançou para a próxima página!
  📄 Página atual: Stack Overflow
  🔗 URL: stackoverflow.com
```

---

### 5. 🔄 Teste: Múltiplas Voltas
**Objetivo**: Verificar LIFO com várias voltas consecutivas em pilhas encadeadas.

**Passos**:
1. Visite 5 páginas: A, B, C, D, E
2. Volte 3 vezes (opção 2)
3. Opção 5 (Listar histórico)
4. Opção 6 (Listar futuro)

**Resultado Esperado**:
- Histórico (topo → base): B, A
- Futuro (topo → base): C, D, E

---

### 6. ❌ Teste: Voltar com Histórico Vazio ou com Apenas Uma Página
**Objetivo**: Verificar tratamento de erro em pop com pilha vazia.

**Passos**:
1. Inicie o programa (sem visitar nada) → Opção 2
2. Ou visite apenas uma página → Opção 2

**Resultado Esperado**:
```
❌ Não há páginas anteriores para voltar!
```

---

### 7. ❌ Teste: Avançar com Futuro Vazio
**Objetivo**: Verificar tratamento de erro em pop com pilha vazia.

**Passos**:
1. Visite 1 página
2. Opção 3 (Avançar) logo em seguida

**Resultado Esperado**:
```
❌ Não há páginas à frente para avançar!
```

---

### 8. 🧹 Teste: Nova Visita Limpa o Futuro
**Objetivo**: Garantir que visitar nova página zera o futuro na pilha encadeada.

**Passos**:
1. Visite A, B, C
2. Volte 2 vezes → futuro tem [C, B]
3. Opção 1 → Visite D
4. Opção 6 (Listar futuro)

**Resultado Esperado**:
```
└─ Pilha FUTURO vazia
```
- Histórico: [D, A]

---

### 9. 💾 Teste: Salvar em CSV
**Objetivo**: Verificar gravação correta dos arquivos a partir de pilhas encadeadas com mensagem amigável.

**Passos**:
1. Visite 3 páginas
2. Volte 1 vez
3. Opção 7 (Salvar)

**Resultado Esperado**:
```
✅ Navegação salva em CSV com sucesso!
```
- Arquivos historico.csv e futuro.csv criados

---

### 10. 📂 Teste: Carregar do CSV
**Objetivo**: Verificar que o carregamento reconstrói as pilhas encadeadas na ordem correta.

**Passos**:
1. Execute os passos do Teste 9 e salve
2. Reinicie o programa
3. Opção 8 (Carregar)
4. Opção 5 (Listar histórico)

**Resultado Esperado**:
```
✅ Navegação carregada do CSV com sucesso!
```
- Pilhas carregadas com mesmos elementos e mesma ordem

---

### 11. 📅 Teste: Data e Hora Automática
**Objetivo**: Verificar preenchimento automático de `dataHora`.

**Passos**:
1. Opção 1 → preencha URL e Título
2. Opção 4 (Ver atual)

**Resultado Esperado**:
- Campo Data/Hora exibido no formato: `DD/MM/YYYY HH:MM`

---

### 12. ❌ Teste: Validação de Campos Vazios
**Objetivo**: Verificar que URL e Título em branco são rejeitados com mensagens claras.

**Passos**:
1. Opção 1
2. Pressione Enter sem digitar URL

**Resultado Esperado**:
```
❌ URL não pode estar vazia!
```
- Mesmo comportamento para Título vazio

---

### 13. 📚 Teste: Listar Pilha Vazia
**Objetivo**: Verificar mensagem adequada para pilha vazia na lista encadeada.

**Passos**:
1. Inicie o programa (sem visitar nada)
2. Opção 5 (Listar histórico)
3. Opção 6 (Listar futuro)

**Resultado Esperado**:
```
└─ Pilha HISTÓRICO vazia
└─ Pilha FUTURO vazia
```

---

### 14. 🗑️ Teste: Limpar Histórico com Confirmação
**Objetivo**: Verificar a limpeza com confirmação do usuário na pilha encadeada.

**Passos**:
1. Visite 3 páginas
2. Opção 9 (Limpar histórico)
3. Confirme com `s`
4. Opção 5 (Listar histórico)

**Resultado Esperado**:
```
✅ Histórico limpo com sucesso!
└─ Pilha HISTÓRICO vazia
```

**Variação — Cancelar**:
- Na etapa 3, responda `n`
- Histórico deve permanecer intacto!

---

### 15. 🗑️ Teste: Limpar Pilha Já Vazia
**Objetivo**: Verificar mensagem ao tentar limpar pilha vazia.

**Passos**:
1. Inicie sem visitar nada
2. Opção 9 (Limpar histórico)

**Resultado Esperado**:
```
❌ Histórico já está vazio!
```

---

### 16. 🔄 Teste: Persistência Completa (Salvar → Fechar → Carregar)
**Objetivo**: Verificar que o estado é totalmente preservado entre execuções.

**Passos**:
1. Visite A, B, C
2. Volte 1 vez → histórico: [B, A], futuro: [C]
3. Opção 7 (Salvar)
4. Opção 13 (Sair) → verifique mensagem de despedida!
5. Reinicie o programa
6. Opção 8 (Carregar)
7. Opção 3 (Avançar)

**Resultado Esperado**:
- Página atual: C
- Histórico: [C, B, A]
- Futuro: vazio
- Memória liberada corretamente ao sair

---

### 17. ❌ Teste: Opção Inválida no Menu
**Objetivo**: Verificar robustez contra entradas fora do intervalo.

**Passos**:
1. Digite 0 no menu
2. Digite 99 no menu
3. Digite letras no menu

**Resultado Esperado**:
```
❌ Opção inválida! Digite entre 1 e 13.
```

---

### 18. 🔄 Teste: Navegação Complexa
**Objetivo**: Simular um fluxo real de navegação com pilhas encadeadas.

**Sequência**:
1. Visite GitHub
2. Visite Google
3. Visite Stack Overflow
4. Voltar → atual: Google
5. Visite YouTube → futuro limpo
6. Voltar → atual: Google
7. Voltar → atual: GitHub
8. Avançar → atual: Google
9. Visite Wikipedia
10. Listar histórico

**Resultado Esperado**:
Histórico (topo → base):
1. Wikipedia
2. Google
3. GitHub

---

### 19. 📊 Teste: Estatísticas de Páginas Visitadas
**Objetivo**: Verificar que as estatísticas são exibidas corretamente.

**Passos**:
1. Visite 2 páginas
2. Opção 11 (Estatísticas)

**Resultado Esperado**:
```
📊 Estatísticas de Navegação
  📈 Total de páginas visitadas na sessão: 2
  📚 Páginas no histórico: 2
  ⏭️ Páginas no futuro: 0
```

---

### 20. 📄 Teste: Exportar Relatório Completo
**Objetivo**: Verificar a geração correta do relatório em arquivo de texto.

**Passos**:
1. Visite páginas e modifique histórico/futuro
2. Opção 12 (Exportar relatório completo)
3. Verifique se o arquivo `relatorio_navegacao_*.txt` foi criado

**Resultado Esperado**:
- Mensagem: `✅ Relatório exportado para relatorio_navegacao_*.txt com sucesso!`
- Arquivo existe com data e hora no nome
- Arquivo contém: resumo, histórico completo, futuro completo

---

### 21. 🚪 Teste: Sair com Mensagem de Despedida
**Objetivo**: Verificar que a opção 13 libera memória e exibe mensagem de despedida.

**Passos**:
1. Use o programa normalmente
2. Opção 13 (Sair)

**Resultado Esperado**:
```
👋 Obrigado por usar o Simulador de Navegador! Até a próxima!
```
- Nenhum vazamento de memória

---

## 📊 Resumo dos Testes

| # | Teste | Operação |
|---|-------|----------|
| 1 | Visitar páginas sequenciais | Push |
| 2 | Peek sem remover | Peek |
| 3 | Voltar simples | Pop Histórico, Push Futuro |
| 4 | Avançar | Pop Futuro, Push Histórico |
| 5 | Múltiplas voltas | LIFO |
| 6 | Voltar com histórico vazio | Validação |
| 7 | Avançar com futuro vazio | Validação |
| 8 | Nova visita limpa futuro | Regra de Negócio |
| 9 | Salvar em CSV | Arquivo |
| 10 | Carregar do CSV | Arquivo |
| 11 | Data/hora automática | Utilitário |
| 12 | Campos vazios rejeitados | Validação |
| 13 | Listar pilha vazia | Listar |
| 14 | Limpar com confirmação | Limpeza |
| 15 | Limpar pilha já vazia | Validação |
| 16 | Persistência entre execuções | CSV + Estado |
| 17 | Opção inválida no menu | Robustez |
| 18 | Navegação complexa | Fluxo Completo |
| 19 | Estatísticas | Novidade |
| 20 | Exportar relatório completo | Novidade |
| 21 | Sair com mensagem | Novidade |

---

## Instruções de Execução

1. Compile o programa diretamente no terminal: `gcc -Wall -Wextra -std=c99 -o navegador main.c`
2. Execute diretamente: `./navegador`
3. Realize os testes na ordem especificada
4. Marque ✅ ou ❌ em cada teste
5. Relate qualquer comportamento inesperado

---

## ✅ Checklist Final

- [ ] Tela de boas-vindas exibida
- [ ] Todas as opções do menu funcionam corretamente
- [ ] Push insere no topo da pilha encadeada com mensagem de sucesso
- [ ] Pop remove do topo e libera memória
- [ ] Peek não altera a pilha e exibe com emojis
- [ ] LIFO é mantido em todas as operações
- [ ] Nova visita limpa o futuro
- [ ] Voltar e avançar exibem a página atual com feedback
- [ ] Salvar e carregar CSV preserva a ordem das pilhas com mensagem de sucesso
- [ ] Validações de campos vazios funcionam
- [ ] Confirmação antes de limpar pilhas
- [ ] Tratamento de pilhas vazias
- [ ] Data/hora automática correta
- [ ] Estatísticas são exibidas corretamente
- [ ] Relatório é gerado com data/hora no nome
- [ ] Mensagem de despedida exibida
- [ ] Memória liberada corretamente ao sair
- [ ] Sem crashes ou travamentos
- [ ] Nenhum vazamento de memória (Valgrind)
