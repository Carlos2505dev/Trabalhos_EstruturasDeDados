# 🧪 Plano de Testes - Gerenciador de Fila de Impressão (Melhorado!)

---

## ✨ Novidades nos Testes

- Testes para as novas funcionalidades (Estatísticas, Relatórios, Limpeza de Filas)
- Testes para as validações adicionais (ID positivo, nome de arquivo não vazio, páginas > 0)
- Testes para as mensagens amigáveis e feedback ao usuário

---

## Casos de Teste

---

### 1. 📄 Teste: Adicionar Documento Normal
**Objetivo**: Verificar se um documento normal é adicionado corretamente à fila.
**Pré-condição**: Fila vazia.
**Passos**:
1. Opção 1 (Adicionar documento)
2. ID: 1
3. Nome: relatorio.pdf
4. Prioridade: 0
5. Páginas: 20
6. Listar filas (opção 3)
**Resultado Esperado**:
- Mensagem: `✅ Documento 'relatorio.pdf' adicionado à fila NORMAL!`
- Listagem exibe o documento na fila normal.

---

### 2. 📄 Teste: Adicionar Documento Prioritário
**Objetivo**: Verificar se um documento prioritário é adicionado corretamente.
**Pré-condição**: Fila vazia.
**Passos**:
1. Opção 1 (Adicionar documento)
2. ID: 2
3. Nome: urgente.docx
4. Prioridade: 1
5. Páginas: 10
6. Listar filas (opção 3)
**Resultado Esperado**:
- Mensagem: `✅ Documento 'urgente.docx' adicionado à fila PRIORITÁRIA!`
- Listagem exibe o documento na fila prioritária.

---

### 3. ❌ Teste: ID Duplicado
**Objetivo**: Verificar se IDs duplicados são rejeitados.
**Pré-condição**: Documento com ID 1 já existe.
**Passos**:
1. Opção 1 (Adicionar documento)
2. ID: 1
**Resultado Esperado**:
- Mensagem: `❌ Erro: Já existe um documento com esse ID!`
- Documento não é adicionado.

---

### 4. ❌ Teste: ID Zero/Negativo
**Objetivo**: Verificar se IDs não positivos são rejeitados.
**Passos**:
1. Opção 1
2. ID: 0 ou -5
**Resultado Esperado**:
- Mensagem: `❌ Erro: ID deve ser positivo!`
- Documento não é adicionado.

---

### 5. ❌ Teste: Nome de Arquivo Vazio
**Objetivo**: Verificar se nome de arquivo vazio é rejeitado.
**Passos**:
1. Opção 1
2. ID: 3
3. Nome: (deixar vazio, só Enter)
**Resultado Esperado**:
- Mensagem: `❌ Erro: Nome do arquivo não pode ficar vazio!`
- Documento não é adicionado.

---

### 6. ❌ Teste: Número de Páginas ≤ 0
**Objetivo**: Verificar se número de páginas inválido é rejeitado.
**Passos**:
1. Opção 1
2. Preencher ID, nome, prioridade
3. Páginas: 0 ou -10
**Resultado Esperado**:
- Mensagem: `❌ Erro: Número de páginas deve ser positivo!`
- Documento não é adicionado.

---

### 7. ❌ Teste: Prioridade Inválida
**Objetivo**: Verificar se prioridade diferente de 0 ou 1 é rejeitada.
**Passos**:
1. Opção 1
2. Prioridade: 2
**Resultado Esperado**:
- Mensagem: `❌ Erro: Prioridade deve ser 0 (Normal) ou 1 (Prioritária)!`
- Documento não é adicionado.

---

### 8. 🖨️ Teste: Atender Documento Normal
**Objetivo**: Verificar atendimento de documento normal quando a fila prioritária está vazia.
**Pré-condição**: Fila com um documento normal (ID 1).
**Passos**:
1. Opção 2 (Atender impressão)
2. Verificar resultado
**Resultado Esperado**:
- Mensagem com detalhes do documento
- Documento movido para atendidos
- Fila normal fica vazia

---

### 9. 🖨️ Teste: Atender Documento Prioritário
**Objetivo**: Verificar atendimento de documento prioritário quando a fila normal está vazia.
**Pré-condição**: Fila com um documento prioritário (ID 2).
**Passos**:
1. Opção 2
**Resultado Esperado**:
- Documento prioritário é atendido
- Mensagem exibe os detalhes

---

### 10. 🖨️ Teste: Atendimento com Proporcionalidade 1:2
**Objetivo**: Verificar a regra de atendimento: 1 prioritário para cada 2 normais.
**Pré-condição**:
- Filas:
  - Normal: N1, N2, N3, N4
  - Prioritária: P1
**Passos**:
1. Atender 3 vezes
**Resultado Esperado**:
- Ordem de atendimento: P1 → N1 → N2
- Após atendimento, restam: Normal com N3, N4; Prioritária vazia.

---

### 11. 🖨️ Teste: Atender Filas Vazias
**Objetivo**: Verificar tratamento de filas vazias ao tentar atender.
**Pré-condição**: Ambas as filas estão vazias.
**Passos**:
1. Opção 2
**Resultado Esperado**:
- Mensagem: `❌ Nenhuma impressão pendente!`
- Nada é alterado.

---

### 12. 📋 Teste: Listar Filas Vazias
**Objetivo**: Verificar listagem de filas vazias.
**Pré-condição**: Ambas as filas estão vazias.
**Passos**:
1. Opção 3
**Resultado Esperado**:
- Mensagem: `📭 Fila NORMAL está vazia!`
- Mensagem: `📭 Fila PRIORITÁRIA está vazia!`

---

### 13. 🧹 Teste: Limpar Filas (Confirmado)
**Objetivo**: Verificar limpeza de filas com confirmação do usuário.
**Pré-condição**: Ambas as filas têm documentos.
**Passos**:
1. Opção 6
2. Confirmar com `S` ou `s`
3. Listar filas (opção 3)
**Resultado Esperado**:
- Mensagem: `✅ Todas as filas foram limpas com sucesso!`
- Ambas as filas estão vazias
- Memória liberada corretamente

---

### 14. 🧹 Teste: Limpar Filas (Cancelado)
**Objetivo**: Verificar se cancelar a limpeza mantém as filas intactas.
**Pré-condição**: Filas com documentos.
**Passos**:
1. Opção 6
2. Responder `N` ou `n`
3. Listar filas
**Resultado Esperado**:
- Mensagem: `❌ Operação cancelada!`
- Filas permanecem com os documentos originais

---

### 15. 💾 Teste: Salvar e Carregar Filas em CSV
**Objetivo**: Verificar persistência das filas em arquivo CSV.
**Passos**:
1. Adicionar alguns documentos
2. Salvar (opção 4)
3. Limpar filas (opção 6, confirmar)
4. Carregar (opção 5)
5. Listar filas
**Resultado Esperado**:
- Mensagens de sucesso em salvar e carregar
- Após carregar, as filas contêm os mesmos documentos que antes de limpar

---

### 16. 📊 Teste: Estatísticas das Filas
**Objetivo**: Verificar se as estatísticas são exibidas corretamente.
**Pré-condição**:
- Fila normal: 3 documentos
- Fila prioritária: 2 documentos
- Atendidos: 1 documento
**Passos**:
1. Opção 7 (Estatísticas)
**Resultado Esperado**:
- Exibe total de documentos, por fila, atendidos e total de páginas.

---

### 17. 📄 Teste: Gerar Relatório Completo
**Objetivo**: Verificar se o relatório é gerado corretamente com timestamp.
**Passos**:
1. Adicionar alguns documentos e atender alguns
2. Opção 8 (Gerar relatório)
3. Verificar se o arquivo `relatorio_impressao_*.txt` foi criado
**Resultado Esperado**:
- Mensagem: `✅ Relatório gerado com sucesso!`
- Arquivo existe com data/hora no nome
- Arquivo contém:
  - Data e hora de geração
  - Estatísticas
  - Lista das filas (normal e prioritária)
  - Lista dos atendidos

---

### 18. 👋 Teste: Tela de Boas-Vindas e Despedida
**Objetivo**: Verificar se as mensagens de boas-vindas e despedida são exibidas.
**Passos**:
1. Abra o programa
2. Saia usando a opção 0
**Resultado Esperado**:
- Mensagem de boas-vindas exibida no início
- Mensagem de despedida exibida ao sair
- Memória liberada corretamente

---

### 19. ❌ Teste: Opção Inválida no Menu
**Objetivo**: Verificar tratamento de opções inválidas no menu.
**Passos**:
1. Digitar opção 99
2. Digitar letra
**Resultado Esperado**:
- Mensagem: `❌ Opção inválida! Por favor, escolha uma opção entre 0 e 8.`
- Programa continua funcionando normalmente

---

### 20. 🧹 Teste: Liberação de Memória ao Sair
**Objetivo**: Verificar se toda a memória alocada é liberada ao sair.
**Pré-condição**: Filas com vários documentos.
**Passos**:
1. Usar o programa normalmente
2. Sair (opção 0)
**Resultado Esperado**:
- Memória liberada sem vazamentos (confira via valgrind no Linux).
- Mensagem de despedida exibida.

---

## 📊 Sumário de Testes

| Categoria | Total |
|-----------|-------|
| Adição de documento (incluindo validações) | 7 |
| Atendimento (incluindo proporcionalidade) | 4 |
| Listagem | 1 |
| Limpeza | 2 |
| Persistência (CSV) | 1 |
| Estatísticas | 1 |
| Relatórios | 1 |
| Interface | 2 |
| Memória | 1 |
| **Total** | **20** |

---

## ✅ Checklist Final

- [ ] Tela de boas-vindas exibida
- [ ] Todas as opções do menu funcionam corretamente
- [ ] Adição de documento normal funciona
- [ ] Adição de documento prioritário funciona
- [ ] ID duplicado é rejeitado
- [ ] ID positivo é validado
- [ ] Nome de arquivo vazio é rejeitado
- [ ] Número de páginas > 0 é validado
- [ ] Prioridade 0/1 é validada
- [ ] Atendimento com proporcionalidade 1:2 funciona
- [ ] Atendimento de filas vazias é tratado
- [ ] Listagem de filas funciona (incluindo filas vazias)
- [ ] Limpar filas com confirmação funciona
- [ ] Cancelar limpeza mantém as filas intactas
- [ ] Salvar em CSV funciona
- [ ] Carregar de CSV funciona
- [ ] Estatísticas são exibidas corretamente
- [ ] Relatório é gerado com timestamp
- [ ] Mensagens amigáveis são exibidas em todas as operações
- [ ] Memória liberada sem vazamentos ao sair
- [ ] Tratamento de opções inválidas no menu
- [ ] Mensagem de despedida exibida
