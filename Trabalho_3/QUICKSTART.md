# ⚡ Guia Rápido - Gerenciador de Fila de Impressão (Melhorado!)

---

## 🚀 Primeiro Uso Rápido

1. **Compile e execute** o programa
2. **Adicione alguns documentos** usando a opção 1
3. **Listar as filas** usando a opção 3 para ver o estado
4. **Atender impressões** usando a opção 2 para ver o atendimento em ação!
5. **Veja as estatísticas** (opção 7) e **gere um relatório** (opção 8)!

---

## 🛠️ Compilação e Execução Direta

### Windows
```bash
gcc -Wall -Wextra -std=c99 -o fila_impressao main.c
./fila_impressao
```

### Linux/macOS
```bash
make
./fila_impressao
```

---

## 📋 Operações Principais (Com Exemplos!)

### 1. Adicionar Documento à Fila
Escolha a opção 1 e preencha os dados do documento!
Exemplo:
```
📄 Adicionar Documento à Fila
ID do documento: 1
Nome do arquivo: relatorio_final.pdf
Prioridade (0=Normal, 1=Prioritária): 0
Número de páginas: 35

✅ Documento 'relatorio_final.pdf' adicionado à fila NORMAL!
```

### 2. Atender Próxima Impressão
Escolha a opção 2 para atender o próximo documento!
Exemplo:
```
🖨️ Atendendo impressão...
✅ Documento impresso com sucesso!
📄 Arquivo: relatorio_final.pdf
📊 Páginas: 35
📅 Data/Hora: 14/06/2026 10:30
```

---

## 📊 Regras de Atendimento com Prioridade

O programa usa uma regra **1:2** (1 prioritário a cada 2 normais):
- Se houver documentos prioritários: atende 1 prioritário para cada 2 normais
- Se só houver prioritários: atende todos normalmente
- Se só houver normais: atende todos normalmente

---

## 🔍 Exemplos de Fluxo de Uso

### Fluxo Básico
1. Adicione documento normal (ID 1)
2. Adicione documento prioritário (ID 2)
3. Adicione documento normal (ID 3)
4. Adicione documento normal (ID 4)
5. Atenda 3 vezes → Ordem esperada: 2 (prioritário), 1 (normal), 3 (normal)

---

## 💡 Dicas Importantes

1. **ID único**: Não use o mesmo ID para dois documentos!
2. **Prioridade**: 0 = Normal, 1 = Prioritária
3. **Salvar frequentemente**: Use a opção 4 para salvar em arquivo CSV!
4. **Limpar filas**: Opção 6 limpa todas as filas (com confirmação!)
5. **Estatísticas**: Opção 7 mostra o estado completo das filas!
6. **Relatórios**: Opção 8 gera um arquivo .txt com timestamp!
7. **Persistência**: Salve antes de sair para não perder dados!

---

## 📄 Formato do Arquivo CSV

O arquivo `fila_impressao.csv` é automaticamente gerado e segue o padrão:
```csv
tipo_fila;id;nomeArquivo;prioridade;numPaginas;timestamp
normal;1;relatorio.pdf;0;25;14/06/2026 10:30
prioritaria;2;urgente.docx;1;10;14/06/2026 10:31
```

---

## 🐛 Troubleshooting Comum

### Erro na compilação
- Verifique se o compilador GCC está instalado e no PATH
- No Windows, use MinGW ou MSYS2

### Erro no arquivo CSV
- Certifique-se de ter permissão de escrita na pasta
- Verifique se o arquivo não está aberto em outro programa

### Documento não é atendido
- Verifique se a fila não está vazia!

---

## 📞 Suporte

- Consulte o arquivo `README.md` para detalhes completos
- Verifique `TESTES.md` para verificar se tudo funciona
- Leia os comentários no código `main.c` para entender a implementação

---

## 🎯 Pronto para começar!

Aproveite o Gerenciador de Fila de Impressão melhorado! 🎉
