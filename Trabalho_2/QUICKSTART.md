# ⚡ Guia Rápido - Simulador de Navegador (Melhorado!)

---

## 📥 Instalação e Compilação

### Windows

```bash
# 1. Abra o terminal na pasta do projeto
# 2. Compile o programa
gcc -Wall -Wextra -std=c99 -o navegador main.c

# 3. Execute diretamente
./navegador

# Ou use o script de compilação automática
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

## 🚀 Primeiro Uso

### Visitar uma Página

```
Menu → Opção 1
Digite a URL: google.com
Digite o Título: Google
✅ Página visitada com sucesso!
  📄 Título: Google
  🔗 URL: google.com
```

---

## 📋 Operações Rápidas

| Ação | Opção | Resumo |
|------|-------|--------|
| Visitar nova página | 1 | Adiciona página no topo do histórico, limpa o futuro |
| Voltar | 2 | Move página do histórico para o futuro e mostra página atual |
| Avançar | 3 | Move página do futuro para o histórico e mostra página atual |
| Ver página atual | 4 | Mostra topo do histórico sem remover |
| Listar histórico | 5 | Lista do topo até a base |
| Listar futuro | 6 | Lista do topo até a base |
| Salvar navegação | 7 | Salva histórico e futuro em CSV |
| Carregar navegação | 8 | Carrega histórico e futuro de CSV |
| Limpar histórico | 9 | Limpa todo o histórico (com confirmação) |
| Limpar futuro | 10 | Limpa todo o futuro (com confirmação) |
| Estatísticas | 11 | Mostra estatísticas de navegação |
| Exportar relatório | 12 | Exporta relatório completo para arquivo .txt |
| Sair | 13 | Libera memória e encerra o programa |

---

## 🔄 Fluxo Completo de Teste

1. Abra o programa
2. Visite 3 páginas (Google, GitHub, Stack Overflow)
3. Volte 1 vez (mostrará GitHub como página atual)
4. Avance 1 vez (mostrará Stack Overflow como página atual)
5. Visite uma página nova (limpa o futuro!)
6. Liste o histórico
7. Salve tudo (opção 7)
8. Feche o programa
9. Abra novamente
10. Carregue a navegação (opção 8)
11. Veja as estatísticas (opção 11)
12. Exporte o relatório (opção 12)

---

## 🐛 Troubleshooting

### Erro de Compilação
- Verifique se o GCC está instalado e no PATH
- No Windows, instale MinGW ou TDM-GCC

---

## 💡 Dicas Importantes

1. 📅 **Data/Hora Automática**: Não precisa digitar, é preenchida automaticamente com o horário do sistema!
2. 🧹 **Nova Visita Limpa o Futuro**: Sempre que você visita uma página nova, o futuro é completamente limpo!
3. 💾 **Salve Frequentemente**: Use a opção 7 para salvar seu progresso em CSV!
4. 📊 **Veja as Estatísticas**: Opção 11 para ver quantas páginas visitou!
5. 📄 **Exporte Relatórios**: Opção 12 para gerar um arquivo com todo o histórico!
6. 🧹 **Liberação de Memória**: Ao sair (opção 13), toda a memória alocada é liberada!

---

## 🎯 Exemplo Prático

```
🌐 SIMULADOR DE NAVEGADOR INICIADO!

Menu → Opção 1
Digite a URL: google.com
Digite o Título: Google
✅ Página visitada com sucesso!

Menu → Opção 1
Digite a URL: github.com
Digite o Título: GitHub

Menu → Opção 1
Digite a URL: stackoverflow.com
Digite o Título: Stack Overflow

Menu → Opção 5 (Listar histórico)
📚 Pilha HISTÓRICO (do topo até a base):
  1. [stackoverflow.com] Stack Overflow (...)
  2. [github.com] GitHub (...)
  3. [google.com] Google (...)

Menu → Opção 2 (Voltar)
✅ Voltou para a página anterior!
  📄 Página atual: GitHub
  🔗 URL: github.com

Menu → Opção 4 (Ver atual)
📄 Página Atual:
  Título: GitHub
  URL: github.com
```

---

## 📞 Suporte

- Leia o README.md para documentação completa
- Veja TESTES.md para validar tudo funciona
- Revise o código em main.c para entender a implementação

---

**Pronto para começar? 🚀
