#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_BOLD "\x1b[1m"

typedef struct Pagina {
    char url[100];
    char titulo[50];
    char dataHora[20];
    struct Pagina *prox;
} Pagina;

typedef struct {
    Pagina *topo;
} Pilha;

int total_paginas_visitadas = 0;
int total_paginas_historico = 0;
int total_paginas_futuro = 0;

void inicializar(Pilha *p) {
    p->topo = NULL;
}

int vazia(Pilha *p) {
    return p->topo == NULL;
}

Pagina* criar_pagina(const char *url, const char *titulo, const char *dataHora) {
    Pagina *nova = (Pagina*)malloc(sizeof(Pagina));
    if (nova == NULL) {
        printf(COLOR_RED "Erro de alocação de memória!\n" COLOR_RESET);
        return NULL;
    }
    strncpy(nova->url, url, 99);
    nova->url[99] = '\0';
    strncpy(nova->titulo, titulo, 49);
    nova->titulo[49] = '\0';
    strncpy(nova->dataHora, dataHora, 19);
    nova->dataHora[19] = '\0';
    nova->prox = NULL;
    return nova;
}

int push(Pilha *p, Pagina pag) {
    Pagina *nova = criar_pagina(pag.url, pag.titulo, pag.dataHora);
    if (nova == NULL) {
        return 0;
    }
    nova->prox = p->topo;
    p->topo = nova;
    return 1;
}

Pagina pop(Pilha *p, int *sucesso) {
    Pagina pag = {"", "", ""};
    if (vazia(p)) {
        *sucesso = 0;
        return pag;
    }
    Pagina *temp = p->topo;
    strncpy(pag.url, temp->url, 99);
    pag.url[99] = '\0';
    strncpy(pag.titulo, temp->titulo, 49);
    pag.titulo[49] = '\0';
    strncpy(pag.dataHora, temp->dataHora, 19);
    pag.dataHora[19] = '\0';
    p->topo = temp->prox;
    free(temp);
    *sucesso = 1;
    return pag;
}

Pagina peek(Pilha *p, int *sucesso) {
    Pagina pag = {"", "", ""};
    if (vazia(p)) {
        *sucesso = 0;
        return pag;
    }
    strncpy(pag.url, p->topo->url, 99);
    pag.url[99] = '\0';
    strncpy(pag.titulo, p->topo->titulo, 49);
    pag.titulo[49] = '\0';
    strncpy(pag.dataHora, p->topo->dataHora, 19);
    pag.dataHora[19] = '\0';
    *sucesso = 1;
    return pag;
}

void limpar(Pilha *p) {
    while (!vazia(p)) {
        int sucesso;
        pop(p, &sucesso);
    }
}

void limpar_pilha_interativo(Pilha *p, const char *nome) {
    if (vazia(p)) {
        printf(COLOR_RED "✗ %s já está vazio!\n" COLOR_RESET, nome);
        return;
    }
    char conf[10];
    printf(COLOR_YELLOW "Tem certeza que deseja limpar %s? (s/n): " COLOR_RESET, nome);
    fgets(conf, sizeof(conf), stdin);
    if (conf[0] == 's' || conf[0] == 'S') {
        limpar(p);
        printf(COLOR_GREEN "✓ %s limpo com sucesso!\n" COLOR_RESET, nome);
    } else {
        printf(COLOR_CYAN "Operação cancelada!\n" COLOR_RESET);
    }
}

int contar_paginas(Pilha *p) {
    int count = 0;
    Pagina *atual = p->topo;
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    return count;
}

void visitar_nova_pagina(Pilha *historico, Pilha *futuro) {
    Pagina nova;
    printf(COLOR_CYAN "\n🌐 Visitar Nova Página\n" COLOR_RESET);
    printf("Digite a URL: ");
    fgets(nova.url, sizeof(nova.url), stdin);
    nova.url[strcspn(nova.url, "\n")] = '\0';
    
    if (strlen(nova.url) == 0) {
        printf(COLOR_RED "✗ URL não pode estar vazia!\n" COLOR_RESET);
        return;
    }
    
    printf("Digite o Título: ");
    fgets(nova.titulo, sizeof(nova.titulo), stdin);
    nova.titulo[strcspn(nova.titulo, "\n")] = '\0';
    
    if (strlen(nova.titulo) == 0) {
        printf(COLOR_RED "✗ Título não pode estar vazio!\n" COLOR_RESET);
        return;
    }
    
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);
    sprintf(nova.dataHora, "%02d/%02d/%04d %02d:%02d", tm_info.tm_mday, tm_info.tm_mon + 1, tm_info.tm_year + 1900, tm_info.tm_hour, tm_info.tm_min);
    
    if (push(historico, nova)) {
        limpar(futuro);
        total_paginas_visitadas++;
        printf(COLOR_GREEN "✓ Página visitada com sucesso!\n" COLOR_RESET);
        printf("  📄 Título: %s\n", nova.titulo);
        printf("  🔗 URL: %s\n", nova.url);
    }
}

void voltar(Pilha *historico, Pilha *futuro) {
    int sucesso;
    if (vazia(historico) || historico->topo->prox == NULL) {
        printf(COLOR_RED "✗ Não há páginas anteriores para voltar!\n" COLOR_RESET);
        return;
    }
    
    Pagina atual = pop(historico, &sucesso);
    if (sucesso) {
        if (push(futuro, atual)) {
            printf(COLOR_GREEN "✓ Voltou para a página anterior!\n" COLOR_RESET);
            int peek_sucesso;
            Pagina pagina_atual = peek(historico, &peek_sucesso);
            if (peek_sucesso) {
                printf("  📄 Página atual: %s\n", pagina_atual.titulo);
                printf("  🔗 URL: %s\n", pagina_atual.url);
            }
        } else {
            push(historico, atual);
        }
    }
}

void avancar(Pilha *historico, Pilha *futuro) {
    int sucesso;
    if (vazia(futuro)) {
        printf(COLOR_RED "✗ Não há páginas à frente para avançar!\n" COLOR_RESET);
        return;
    }
    
    Pagina prox = pop(futuro, &sucesso);
    if (sucesso) {
        if (push(historico, prox)) {
            printf(COLOR_GREEN "✓ Avançou para a próxima página!\n" COLOR_RESET);
            printf("  📄 Página atual: %s\n", prox.titulo);
            printf("  🔗 URL: %s\n", prox.url);
        } else {
            push(futuro, prox);
        }
    }
}

void listar(Pilha *p, const char *nome) {
    if (vazia(p)) {
        printf("└─ Pilha %s vazia\n", nome);
        return;
    }
    printf("📚 Pilha %s (do topo até a base):\n", nome);
    Pagina *atual = p->topo;
    int cont = 1;
    while (atual != NULL) {
        printf("  %d. [%s] %s (%s)\n", cont++, atual->url, atual->titulo, atual->dataHora);
        atual = atual->prox;
    }
}

void salvar_csv(Pilha *historico, Pilha *futuro) {
    FILE *f_hist = fopen("historico.csv", "w");
    if (f_hist) {
        fprintf(f_hist, "url;titulo;dataHora\n");
        Pilha temp;
        inicializar(&temp);
        int sucesso;
        
        while (!vazia(historico)) {
            Pagina p = pop(historico, &sucesso);
            push(&temp, p);
        }
        
        while (!vazia(&temp)) {
            Pagina p = pop(&temp, &sucesso);
            fprintf(f_hist, "%s;%s;%s\n", p.url, p.titulo, p.dataHora);
            push(historico, p);
        }
        
        fclose(f_hist);
    }
    
    FILE *f_fut = fopen("futuro.csv", "w");
    if (f_fut) {
        fprintf(f_fut, "url;titulo;dataHora\n");
        Pilha temp;
        inicializar(&temp);
        int sucesso;
        
        while (!vazia(futuro)) {
            Pagina p = pop(futuro, &sucesso);
            push(&temp, p);
        }
        
        while (!vazia(&temp)) {
            Pagina p = pop(&temp, &sucesso);
            fprintf(f_fut, "%s;%s;%s\n", p.url, p.titulo, p.dataHora);
            push(futuro, p);
        }
        
        fclose(f_fut);
    }
    printf(COLOR_GREEN "✓ Navegação salva em CSV com sucesso!\n" COLOR_RESET);
}

void carregar_csv(Pilha *historico, Pilha *futuro) {
    limpar(historico);
    FILE *f_hist = fopen("historico.csv", "r");
    if (f_hist) {
        char linha[256];
        fgets(linha, sizeof(linha), f_hist);
        Pilha temp;
        inicializar(&temp);
        while (fgets(linha, sizeof(linha), f_hist)) {
            Pagina p = {"", "", ""};
            linha[strcspn(linha, "\n")] = 0;
            char *token = strtok(linha, ";");
            if (token)
                strcpy(p.url, token);
            token = strtok(NULL, ";");
            if (token)
                strcpy(p.titulo, token);
            token = strtok(NULL, ";");
            if (token)
                strcpy(p.dataHora, token);
            push(&temp, p);
        }
        
        int sucesso;
        while (!vazia(&temp)) {
            Pagina p = pop(&temp, &sucesso);
            push(historico, p);
        }
        
        fclose(f_hist);
    }
    
    limpar(futuro);
    FILE *f_fut = fopen("futuro.csv", "r");
    if (f_fut) {
        char linha[256];
        fgets(linha, sizeof(linha), f_fut);
        Pilha temp;
        inicializar(&temp);
        while (fgets(linha, sizeof(linha), f_fut)) {
            Pagina p = {"", "", ""};
            linha[strcspn(linha, "\n")] = 0;
            char *token = strtok(linha, ";");
            if (token)
                strcpy(p.url, token);
            token = strtok(NULL, ";");
            if (token)
                strcpy(p.titulo, token);
            token = strtok(NULL, ";");
            if (token)
                strcpy(p.dataHora, token);
            push(&temp, p);
        }
        
        int sucesso;
        while (!vazia(&temp)) {
            Pagina p = pop(&temp, &sucesso);
            push(futuro, p);
        }
        
        fclose(f_fut);
    }
    printf(COLOR_GREEN "✓ Navegação carregada do CSV com sucesso!\n" COLOR_RESET);
}

void exibir_estatisticas() {
    printf(COLOR_BOLD "\n📊 Estatísticas de Navegação\n" COLOR_RESET);
    printf("  📈 Total de páginas visitadas na sessão: %d\n", total_paginas_visitadas);
    printf("  📚 Páginas no histórico: %d\n", total_paginas_historico);
    printf("  ⏭️ Páginas no futuro: %d\n", total_paginas_futuro);
}

void exportar_relatorio(Pilha *historico, Pilha *futuro) {
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    char data_hora[50];
    strftime(data_hora, sizeof(data_hora), "%Y-%m-%d_%H-%M-%S", tm_info);
    
    char nome_arquivo[100];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "relatorio_navegacao_%s.txt", data_hora);
    
    FILE *f = fopen(nome_arquivo, "w");
    if (f) {
        fprintf(f, "=========================================\n");
        fprintf(f, "     RELATÓRIO DO SIMULADOR DE NAVEGADOR\n");
        fprintf(f, "=========================================\n");
        fprintf(f, "Gerado em: %s", ctime(&agora));
        fprintf(f, "\nTotal de páginas visitadas na sessão: %d\n", total_paginas_visitadas);
        fprintf(f, "Páginas no histórico: %d\n", total_paginas_historico);
        fprintf(f, "Páginas no futuro: %d\n", total_paginas_futuro);
        fprintf(f, "=========================================\n");
        
        fprintf(f, "\n📚 HISTÓRICO (do topo até a base):\n");
        fprintf(f, "-----------------------------------------\n");
        Pilha temp_hist;
        inicializar(&temp_hist);
        int sucesso;
        int cont = 1;
        while (!vazia(historico)) {
            Pagina p = pop(historico, &sucesso);
            fprintf(f, "%d. [%s] %s (%s)\n", cont++, p.url, p.titulo, p.dataHora);
            push(&temp_hist, p);
        }
        while (!vazia(&temp_hist)) {
            Pagina p = pop(&temp_hist, &sucesso);
            push(historico, p);
        }
        
        fprintf(f, "\n⏭️ FUTURO (do topo até a base):\n");
        fprintf(f, "-----------------------------------------\n");
        Pilha temp_fut;
        inicializar(&temp_fut);
        cont = 1;
        while (!vazia(futuro)) {
            Pagina p = pop(futuro, &sucesso);
            fprintf(f, "%d. [%s] %s (%s)\n", cont++, p.url, p.titulo, p.dataHora);
            push(&temp_fut, p);
        }
        while (!vazia(&temp_fut)) {
            Pagina p = pop(&temp_fut, &sucesso);
            push(futuro, p);
        }
        
        fclose(f);
        printf(COLOR_GREEN "✓ Relatório exportado para %s com sucesso!\n" COLOR_RESET, nome_arquivo);
    } else {
        printf(COLOR_RED "✗ Erro ao criar relatório!\n" COLOR_RESET);
    }
}

void menu() {
    Pilha historico, futuro;
    inicializar(&historico);
    inicializar(&futuro);
    
    int opcao = 0;
    char buffer[10];
    
    printf(COLOR_BOLD "\n=========================================\n" COLOR_RESET);
    printf(COLOR_BOLD "    🌐 BEM-VINDO AO SIMULADOR DE NAVEGADOR!\n" COLOR_RESET);
    printf(COLOR_BOLD "=========================================\n" COLOR_RESET);
    
    do {
        total_paginas_historico = contar_paginas(&historico);
        total_paginas_futuro = contar_paginas(&futuro);
        
        printf(COLOR_BOLD "\n--- SIMULADOR DE NAVEGADOR ---\n" COLOR_RESET);
        printf("1.  🌐 Visitar nova página\n");
        printf("2.  ↩️ Voltar (página anterior)\n");
        printf("3.  ↪️ Avançar (próxima página)\n");
        printf("4.  📄 Ver página atual (peek)\n");
        printf("5.  📚 Listar histórico\n");
        printf("6.  ⏭️ Listar futuro\n");
        printf("7.  💾 Salvar navegação em CSV\n");
        printf("8.  📂 Carregar navegação do CSV\n");
        printf("9.  🗑️ Limpar histórico\n");
        printf("10. 🗑️ Limpar futuro\n");
        printf("11. 📊 Relatório de páginas visitadas\n");
        printf("12. 📄 Exportar relatório completo\n");
        printf("13. 🚪 Sair\n");
        
        printf(COLOR_YELLOW "\nEscolha uma opção: " COLOR_RESET);
        
        if (!fgets(buffer, sizeof(buffer), stdin))
            break;
        opcao = atoi(buffer);
        
        switch (opcao) {
            case 1:
                visitar_nova_pagina(&historico, &futuro);
                break;
            case 2:
                voltar(&historico, &futuro);
                break;
            case 3:
                avancar(&historico, &futuro);
                break;
            case 4: {
                int sucesso;
                Pagina p = peek(&historico, &sucesso);
                if (sucesso) {
                    printf(COLOR_BLUE "\n📄 Página Atual:\n" COLOR_RESET);
                    printf("  Título: %s\n", p.titulo);
                    printf("  URL: %s\n", p.url);
                    printf("  Data/Hora: %s\n", p.dataHora);
                } else {
                    printf(COLOR_RED "✗ Nenhuma página no histórico!\n" COLOR_RESET);
                }
                break;
            }
            case 5:
                printf("\n");
                listar(&historico, "HISTÓRICO");
                break;
            case 6:
                printf("\n");
                listar(&futuro, "FUTURO");
                break;
            case 7:
                salvar_csv(&historico, &futuro);
                break;
            case 8:
                carregar_csv(&historico, &futuro);
                break;
            case 9:
                limpar_pilha_interativo(&historico, "Histórico");
                break;
            case 10:
                limpar_pilha_interativo(&futuro, "Futuro");
                break;
            case 11:
                exibir_estatisticas();
                break;
            case 12:
                exportar_relatorio(&historico, &futuro);
                break;
            case 13:
                limpar(&historico);
                limpar(&futuro);
                printf(COLOR_GREEN "👋 Obrigado por usar o Simulador de Navegador! Até a próxima!\n" COLOR_RESET);
                break;
            default:
                printf(COLOR_RED "✗ Opção inválida! Digite entre 1 e 13.\n" COLOR_RESET);
        }
    } while (opcao != 13);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    menu();
    return 0;
}
