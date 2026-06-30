#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define ARQUIVO_CSV_NORMAL "fila_normal.csv"
#define ARQUIVO_CSV_PRIORITARIA "fila_prioritaria.csv"
#define ARQUIVO_CSV_UNICO "filas_completo.csv"
#define ARQUIVO_RELATORIO "relatorio_atendimentos.txt"

typedef struct Trabalho {
    int id;
    char arquivo[50];
    int paginas;
    char tipo;
    time_t tempo_entrada;
    struct Trabalho *prox;
} Trabalho;

typedef struct {
    Trabalho *inicio;
    Trabalho *fim;
    int quantidade;
} Fila;

typedef struct Atendimento {
    int id;
    char arquivo[50];
    int paginas;
    char tipo;
    long espera_seg;
    time_t tempo_atendido;
    struct Atendimento *prox;
} Atendimento;

typedef struct {
    int total_atendidos;
    int total_prioritarios;
    int total_normais;
    int paginas_totais;
    long espera_total_seg;
    Atendimento *historico;
} Estatisticas;

Estatisticas stats = {0};

int prop_prioritarios = 1;
int prop_normais = 1;
int prio_processados = 0;
int norm_processados = 0;

int id_contador = 1;

Fila fila_normal, fila_prioritaria;

Trabalho* criar_trabalho(int id, const char *arquivo, int paginas, char tipo, time_t tempo_entrada) {
    Trabalho *novo = (Trabalho*)malloc(sizeof(Trabalho));
    if (novo == NULL) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    novo->id = id;
    strncpy(novo->arquivo, arquivo, 49);
    novo->arquivo[49] = '\0';
    novo->paginas = paginas;
    novo->tipo = tipo;
    novo->tempo_entrada = tempo_entrada;
    novo->prox = NULL;
    return novo;
}

Atendimento* criar_atendimento(Trabalho t, time_t tempo_atendido, long espera_seg) {
    Atendimento *novo = (Atendimento*)malloc(sizeof(Atendimento));
    if (novo == NULL) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    novo->id = t.id;
    strncpy(novo->arquivo, t.arquivo, 49);
    novo->arquivo[49] = '\0';
    novo->paginas = t.paginas;
    novo->tipo = t.tipo;
    novo->espera_seg = espera_seg;
    novo->tempo_atendido = tempo_atendido;
    novo->prox = NULL;
    return novo;
}

void inicializar_fila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->quantidade = 0;
}

int fila_vazia(Fila *f) {
    return f->inicio == NULL;
}

void enfileirar(Fila *f, Trabalho t) {
    Trabalho *novo = criar_trabalho(t.id, t.arquivo, t.paginas, t.tipo, t.tempo_entrada);
    if (novo == NULL) {
        return;
    }
    if (fila_vazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
    f->quantidade++;
}

int desenfileirar(Fila *f, Trabalho *dest) {
    if (fila_vazia(f)) {
        return 0;
    }
    Trabalho *temp = f->inicio;
    dest->id = temp->id;
    strncpy(dest->arquivo, temp->arquivo, 49);
    dest->arquivo[49] = '\0';
    dest->paginas = temp->paginas;
    dest->tipo = temp->tipo;
    dest->tempo_entrada = temp->tempo_entrada;
    dest->prox = NULL;
    f->inicio = temp->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    free(temp);
    f->quantidade--;
    return 1;
}

int consultar_proximo(Fila *f, Trabalho *dest) {
    if (fila_vazia(f)) {
        return 0;
    }
    dest->id = f->inicio->id;
    strncpy(dest->arquivo, f->inicio->arquivo, 49);
    dest->arquivo[49] = '\0';
    dest->paginas = f->inicio->paginas;
    dest->tipo = f->inicio->tipo;
    dest->tempo_entrada = f->inicio->tempo_entrada;
    dest->prox = NULL;
    return 1;
}

int buscar_na_fila(Fila *f, int id) {
    Trabalho *atual = f->inicio;
    int pos = 0;
    while (atual != NULL) {
        if (atual->id == id) {
            return pos;
        }
        atual = atual->prox;
        pos++;
    }
    return -1;
}

void cancelar_na_fila(Fila *f, int id) {
    Trabalho *atual = f->inicio;
    Trabalho *anterior = NULL;
    while (atual != NULL) {
        if (atual->id == id) {
            if (anterior == NULL) {
                f->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            if (atual == f->fim) {
                f->fim = anterior;
            }
            free(atual);
            f->quantidade--;
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void limpar_fila(Fila *f) {
    Trabalho *temp;
    while (f->inicio != NULL) {
        temp = f->inicio;
        f->inicio = f->inicio->prox;
        free(temp);
    }
    f->fim = NULL;
    f->quantidade = 0;
}

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void remover_quebra_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[--len] = '\0';
    if (len > 0 && str[len - 1] == '\r')
        str[len - 1] = '\0';
}

void habilitar_utf8(void) {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    setlocale(LC_ALL, "");
}

void exibir_trabalho(Trabalho t, int posicao) {
    if (posicao > 0)
        printf("  [%d] ", posicao);
    else
        printf("  ");
    printf("🆔 ID: %d | 📄 Arquivo: %s | 📄 Páginas: %d | 🏷️ Tipo: %s\n", t.id, t.arquivo, t.paginas, (t.tipo == 'P') ? "Prioritário" : "Normal");
}

void listar_fila(Fila *f, const char *nome) {
    if (fila_vazia(f)) {
        printf("  📭 Fila %s: VAZIA\n", nome);
        return;
    }
    printf("  📋 Fila %s (%d trabalho(s)):\n", nome, f->quantidade);
    Trabalho *atual = f->inicio;
    int cont = 1;
    while (atual != NULL) {
        exibir_trabalho(*atual, cont++);
        atual = atual->prox;
    }
}

void buscar_por_id(int id) {
    int pos_n = buscar_na_fila(&fila_normal, id);
    int pos_p = buscar_na_fila(&fila_prioritaria, id);
    if (pos_n != -1) {
        Trabalho *atual = fila_normal.inicio;
        for (int i = 0; i < pos_n; i++) {
            atual = atual->prox;
        }
        printf("✅ Trabalho encontrado na FILA NORMAL (posição %d):\n", pos_n + 1);
        exibir_trabalho(*atual, pos_n + 1);
    } else if (pos_p != -1) {
        Trabalho *atual = fila_prioritaria.inicio;
        for (int i = 0; i < pos_p; i++) {
            atual = atual->prox;
        }
        printf("✅ Trabalho encontrado na FILA PRIORITÁRIA (posição %d):\n", pos_p + 1);
        exibir_trabalho(*atual, pos_p + 1);
    } else {
        printf("❌ Trabalho com ID %d não encontrado!\n", id);
    }
}

void cancelar_por_id(int id) {
    if (buscar_na_fila(&fila_normal, id) == -1 && buscar_na_fila(&fila_prioritaria, id) == -1) {
        printf("❌ Trabalho com ID %d não encontrado!\n", id);
        return;
    }
    
    char conf[4];
    printf("⚠️ Tem certeza que deseja cancelar o trabalho ID %d? (S/N): ", id);
    fgets(conf, sizeof(conf), stdin);
    if (toupper((unsigned char)conf[0]) == 'S') {
        if (buscar_na_fila(&fila_normal, id) != -1) {
            cancelar_na_fila(&fila_normal, id);
            printf("✅ Trabalho ID %d cancelado da fila normal com sucesso!\n", id);
        } else if (buscar_na_fila(&fila_prioritaria, id) != -1) {
            cancelar_na_fila(&fila_prioritaria, id);
            printf("✅ Trabalho ID %d cancelado da fila prioritária com sucesso!\n", id);
        }
    } else {
        printf("ℹ️ Cancelamento abortado!\n");
    }
}

void registrar_atendimento(Trabalho t) {
    time_t agora = time(NULL);
    long espera = (t.tempo_entrada > 0) ? (long)(agora - t.tempo_entrada) : 0;
    
    Atendimento *novo = criar_atendimento(t, agora, espera);
    if (novo != NULL) {
        novo->prox = stats.historico;
        stats.historico = novo;
    }
    
    stats.total_atendidos++;
    stats.paginas_totais += t.paginas;
    stats.espera_total_seg += espera;
    if (t.tipo == 'P')
        stats.total_prioritarios++;
    else
        stats.total_normais++;
}

void exibir_estatisticas(void) {
    printf("\n+--------------------------------------------+\n");
    printf("|        📊 ESTATÍSTICAS DE ATENDIMENTO       |\n");
    printf("+--------------------------------------------+\n");
    printf("| Total atendidos           : %-19d |\n", stats.total_atendidos);
    printf("|   Prioritários            : %-19d |\n", stats.total_prioritarios);
    printf("|   Normais                 : %-19d |\n", stats.total_normais);
    printf("| Páginas impressas         : %-19d |\n", stats.paginas_totais);
    if (stats.total_atendidos > 0) {
        long media = stats.espera_total_seg / stats.total_atendidos;
        printf("| Tempo total de espera     : %-14ld seg |\n", stats.espera_total_seg);
        printf("| Tempo médio de espera     : %-14ld seg |\n", media);
    } else {
        printf("| Nenhum trabalho atendido ainda.             |\n");
    }
    printf("+--------------------------------------------+\n");
}

void processar_proximo(void) {
    Trabalho t;
    int removeu = 0;
    int usar_prior = 0;
    
    if (!fila_vazia(&fila_prioritaria) && !fila_vazia(&fila_normal)) {
        if (prio_processados < prop_prioritarios) {
            usar_prior = 1;
        } else if (norm_processados < prop_normais) {
            usar_prior = 0;
        } else {
            prio_processados = 0;
            norm_processados = 0;
            usar_prior = 1;
        }
    } else if (!fila_vazia(&fila_prioritaria)) {
        usar_prior = 1;
    } else if (!fila_vazia(&fila_normal)) {
        usar_prior = 0;
    } else {
        printf("📭 Nenhum trabalho na fila para processar!\n");
        return;
    }
    
    if (usar_prior) {
        removeu = desenfileirar(&fila_prioritaria, &t);
        if (removeu) {
            printf("\n🚀 Processando trabalho PRIORITÁRIO:\n");
            prio_processados++;
        }
    } else {
        removeu = desenfileirar(&fila_normal, &t);
        if (removeu) {
            printf("\n📋 Processando trabalho NORMAL:\n");
            norm_processados++;
        }
    }
    
    if (!removeu) {
        printf("📭 Nenhum trabalho na fila!\n");
        return;
    }
    
    exibir_trabalho(t, 0);
    registrar_atendimento(t);
    printf("✅ Trabalho processado com sucesso!\n");
}

void consultar_proximo_geral(void) {
    Trabalho t;
    int encontrou = 0;
    
    if (!fila_vazia(&fila_prioritaria)) {
        encontrou = consultar_proximo(&fila_prioritaria, &t);
        if (encontrou)
            printf("\n🔍 Próximo a ser processado (PRIORITÁRIO):\n");
    } else if (!fila_vazia(&fila_normal)) {
        encontrou = consultar_proximo(&fila_normal, &t);
        if (encontrou)
            printf("\n🔍 Próximo a ser processado (NORMAL):\n");
    }
    
    if (!encontrou) {
        printf("📭 Nenhum trabalho na fila!\n");
        return;
    }
    exibir_trabalho(t, 0);
}

static void escrever_cabecalho_csv(FILE *arq) {
    fprintf(arq, "id;arquivo;paginas;tipo;tempo_entrada\n");
}

static void escrever_trabalho_csv(FILE *arq, Trabalho t) {
    fprintf(arq, "%d;%s;%d;%c;%ld\n", t.id, t.arquivo, t.paginas, t.tipo, (long)t.tempo_entrada);
}

void salvar_csv(void) {
    FILE *arq;
    
    arq = fopen(ARQUIVO_CSV_NORMAL, "w");
    if (!arq) {
        printf("❌ Erro ao abrir '%s'!\n", ARQUIVO_CSV_NORMAL);
        return;
    }
    escrever_cabecalho_csv(arq);
    Trabalho *atual = fila_normal.inicio;
    while (atual != NULL) {
        escrever_trabalho_csv(arq, *atual);
        atual = atual->prox;
    }
    fclose(arq);
    
    arq = fopen(ARQUIVO_CSV_PRIORITARIA, "w");
    if (!arq) {
        printf("❌ Erro ao abrir '%s'!\n", ARQUIVO_CSV_PRIORITARIA);
        return;
    }
    escrever_cabecalho_csv(arq);
    atual = fila_prioritaria.inicio;
    while (atual != NULL) {
        escrever_trabalho_csv(arq, *atual);
        atual = atual->prox;
    }
    fclose(arq);
    
    printf("✅ Filas salvas em '%s' e '%s' com sucesso!\n", ARQUIVO_CSV_NORMAL, ARQUIVO_CSV_PRIORITARIA);
}

void salvar_csv_unico(void) {
    FILE *arq = fopen(ARQUIVO_CSV_UNICO, "w");
    if (!arq) {
        printf("❌ Erro ao abrir '%s'!\n", ARQUIVO_CSV_UNICO);
        return;
    }
    
    time_t agora = time(NULL);
    fprintf(arq, "# FILAS DE IMPRESSÃO - ESTADO COMPLETO\n");
    fprintf(arq, "# Gerado em: %s", ctime(&agora));
    fprintf(arq, "#\n");
    
    fprintf(arq, "[SECAO:FILA_NORMAL]\n");
    escrever_cabecalho_csv(arq);
    Trabalho *atual = fila_normal.inicio;
    while (atual != NULL) {
        escrever_trabalho_csv(arq, *atual);
        atual = atual->prox;
    }
    
    fprintf(arq, "[SECAO:FILA_PRIORITARIA]\n");
    escrever_cabecalho_csv(arq);
    atual = fila_prioritaria.inicio;
    while (atual != NULL) {
        escrever_trabalho_csv(arq, *atual);
        atual = atual->prox;
    }
    
    fclose(arq);
    printf("✅ Filas salvas em arquivo único '%s' com sucesso!\n", ARQUIVO_CSV_UNICO);
}

static int ler_linha_csv(char *linha, Trabalho *t) {
    char tipo_str[4];
    long ts = 0;
    int campos = sscanf(linha, "%d;%49[^;];%d;%3[^;];%ld", &t->id, t->arquivo, &t->paginas, tipo_str, &ts);
    if (campos < 4)
        return 0;
    t->tipo = toupper((unsigned char)tipo_str[0]);
    t->tempo_entrada = (time_t)ts;
    t->prox = NULL;
    return 1;
}

void carregar_csv(void) {
    limpar_fila(&fila_normal);
    FILE *arq = fopen(ARQUIVO_CSV_NORMAL, "r");
    if (arq) {
        char linha[256];
        fgets(linha, sizeof(linha), arq);
        while (fgets(linha, sizeof(linha), arq)) {
            remover_quebra_linha(linha);
            if (strlen(linha) == 0 || linha[0] == '#')
                continue;
            Trabalho t = {0};
            if (ler_linha_csv(linha, &t)) {
                enfileirar(&fila_normal, t);
                if (t.id >= id_contador)
                    id_contador = t.id + 1;
            }
        }
        fclose(arq);
    }
    
    limpar_fila(&fila_prioritaria);
    arq = fopen(ARQUIVO_CSV_PRIORITARIA, "r");
    if (arq) {
        char linha[256];
        fgets(linha, sizeof(linha), arq);
        while (fgets(linha, sizeof(linha), arq)) {
            remover_quebra_linha(linha);
            if (strlen(linha) == 0 || linha[0] == '#')
                continue;
            Trabalho t = {0};
            if (ler_linha_csv(linha, &t)) {
                enfileirar(&fila_prioritaria, t);
                if (t.id >= id_contador)
                    id_contador = t.id + 1;
            }
        }
        fclose(arq);
    }
    
    printf("✅ Filas carregadas de '%s' e '%s' com sucesso!\n", ARQUIVO_CSV_NORMAL, ARQUIVO_CSV_PRIORITARIA);
}

void salvar_relatorio(void) {
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    char data_hora[50];
    strftime(data_hora, sizeof(data_hora), "%Y-%m-%d_%H-%M-%S", tm_info);
    
    char nome_arquivo[100];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "relatorio_atendimentos_%s.txt", data_hora);
    
    FILE *arq = fopen(nome_arquivo, "w");
    if (!arq) {
        printf("❌ Erro ao abrir '%s'!\n", ARQUIVO_RELATORIO);
        return;
    }
    
    fprintf(arq, "=============================================\n");
    fprintf(arq, "     RELATÓRIO DE ATENDIMENTOS - FILA IMPRESSÃO\n");
    fprintf(arq, "=============================================\n");
    fprintf(arq, "Gerado em: %s", ctime(&agora));
    
    fprintf(arq, "\n--- RESUMO ---\n");
    fprintf(arq, "Total atendidos   : %d\n", stats.total_atendidos);
    fprintf(arq, "  Prioritários    : %d\n", stats.total_prioritarios);
    fprintf(arq, "  Normais         : %d\n", stats.total_normais);
    fprintf(arq, "Páginas impressas : %d\n", stats.paginas_totais);
    if (stats.total_atendidos > 0) {
        long media = stats.espera_total_seg / stats.total_atendidos;
        fprintf(arq, "Espera total (s)  : %ld\n", stats.espera_total_seg);
        fprintf(arq, "Espera média (s)  : %ld\n", media);
    }
    
    fprintf(arq, "\n--- HISTÓRICO DETALHADO ---\n");
    fprintf(arq, "%-6s %-30s %-8s %-12s %-12s %s\n", "ID", "Arquivo", "Páginas", "Tipo", "Espera(s)", "Atendido em");
    
    Atendimento *atual = stats.historico;
    Atendimento *temp_historico = NULL;
    while (atual != NULL) {
        Atendimento *novo = (Atendimento*)malloc(sizeof(Atendimento));
        memcpy(novo, atual, sizeof(Atendimento));
        novo->prox = temp_historico;
        temp_historico = novo;
        atual = atual->prox;
    }
    
    atual = temp_historico;
    while (atual != NULL) {
        char buf[32];
        struct tm *tm_info_atend = localtime(&atual->tempo_atendido);
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info_atend);
        fprintf(arq, "%-6d %-30s %-8d %-12s %-12ld %s\n", atual->id, atual->arquivo, atual->paginas, (atual->tipo == 'P') ? "Prioritário" : "Normal", atual->espera_seg, buf);
        
        Atendimento *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    
    fclose(arq);
    printf("✅ Relatório salvo em '%s' com sucesso!\n", nome_arquivo);
}

void configurar_proporcao(void) {
    printf("\n+--------------------------------------------+\n");
    printf("|      ⚙️ CONFIGURAÇÃO DE PROPORÇÃO            |\n");
    printf("+--------------------------------------------+\n");
    printf("Configuração atual: %d prioritário(s) por cada %d normal(is)\n", prop_prioritarios, prop_normais);
    printf("Novo número de prioritários por ciclo (1-100): ");
    
    int p;
    if (scanf("%d", &p) != 1 || p < 1 || p > 100) {
        limpar_buffer();
        printf("❌ Valor inválido! Configuração não alterada.\n");
        return;
    }
    limpar_buffer();
    
    printf("Novo número de normais por ciclo (1-100): ");
    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
        limpar_buffer();
        printf("❌ Valor inválido! Configuração não alterada.\n");
        return;
    }
    limpar_buffer();
    
    prop_prioritarios = p;
    prop_normais = n;
    prio_processados = 0;
    norm_processados = 0;
    printf("✅ Proporção atualizada: %d prioritário(s) por %d normal(is)!\n", p, n);
}

void exibir_menu(void) {
    printf("\n+--------------------------------------------+\n");
    printf("|   🖨️ GERENCIADOR DE FILA DE IMPRESSÃO       |\n");
    printf("+--------------------------------------------+\n");
    printf("| 1.  ➕ Enfileirar trabalho                  |\n");
    printf("| 2.  🚀 Processar próximo trabalho           |\n");
    printf("| 3.  🔍 Consultar próximo (sem remover)      |\n");
    printf("| 4.  📋 Listar fila normal                  |\n");
    printf("| 5.  📋 Listar fila prioritária             |\n");
    printf("| 6.  📋 Listar ambas as filas               |\n");
    printf("| 7.  🔍 Buscar trabalho por ID              |\n");
    printf("| 8.  ❌ Cancelar trabalho por ID            |\n");
    printf("| 9.  📊 Estatísticas de atendimento         |\n");
    printf("| 10. ⚙️ Configurar proporção de prioridade  |\n");
    printf("| 11. 💾 Salvar filas em arquivos separados  |\n");
    printf("| 12. 💾 Salvar filas em arquivo único       |\n");
    printf("| 13. 📂 Carregar filas de CSV               |\n");
    printf("| 14. 📄 Salvar relatório de atendimentos    |\n");
    printf("| 0.  🚪 Sair                                |\n");
    printf("+--------------------------------------------+\n");
    printf("Proporção ativa: %dP / %dN  | Opção: ", prop_prioritarios, prop_normais);
}

void liberar_memoria(void) {
    limpar_fila(&fila_normal);
    limpar_fila(&fila_prioritaria);
    
    Atendimento *temp;
    while (stats.historico != NULL) {
        temp = stats.historico;
        stats.historico = stats.historico->prox;
        free(temp);
    }
}

int main(void) {
    habilitar_utf8();
    inicializar_fila(&fila_normal);
    inicializar_fila(&fila_prioritaria);
    stats.historico = NULL;
    
    int opcao;
    
    printf("\n=============================================\n");
    printf("   👋 BEM-VINDO AO GERENCIADOR DE FILA DE IMPRESSÃO!\n");
    printf("=============================================\n");
    
    while (1) {
        exibir_menu();
        
        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            printf("❌ Entrada inválida! Digite um número.\n");
            continue;
        }
        limpar_buffer();
        
        switch (opcao) {
                
            case 1: {
                Trabalho t = {0};
                char tipo_input[10];
                
                t.id = id_contador;
                t.tempo_entrada = time(NULL);
                
                printf("\n📄 Nome do arquivo: ");
                fgets(t.arquivo, sizeof(t.arquivo), stdin);
                remover_quebra_linha(t.arquivo);
                if (strlen(t.arquivo) == 0) {
                    printf("❌ Nome do arquivo não pode ser vazio!\n");
                    break;
                }
                
                printf("📄 Número de páginas: ");
                if (scanf("%d", &t.paginas) != 1 || t.paginas <= 0) {
                    limpar_buffer();
                    printf("❌ Número de páginas inválido! Deve ser maior que zero.\n");
                    break;
                }
                limpar_buffer();
                
                printf("🏷️ Tipo (N=Normal, P=Prioritário): ");
                fgets(tipo_input, sizeof(tipo_input), stdin);
                t.tipo = toupper((unsigned char)tipo_input[0]);
                
                if (t.tipo != 'N' && t.tipo != 'P') {
                    printf("❌ Tipo inválido! Use N ou P.\n");
                    break;
                }
                
                if (t.tipo == 'P') {
                    enfileirar(&fila_prioritaria, t);
                    printf("✅ Trabalho enfileirado como PRIORITÁRIO (ID: %d)!\n", t.id);
                } else {
                    enfileirar(&fila_normal, t);
                    printf("✅ Trabalho enfileirado como NORMAL (ID: %d)!\n", t.id);
                }
                id_contador++;
                break;
            }
                
            case 2:
                processar_proximo();
                break;
                
            case 3:
                consultar_proximo_geral();
                break;
                
            case 4:
                printf("\n");
                listar_fila(&fila_normal, "NORMAL");
                break;
                
            case 5:
                printf("\n");
                listar_fila(&fila_prioritaria, "PRIORITÁRIA");
                break;
                
            case 6:
                printf("\n");
                listar_fila(&fila_normal, "NORMAL");
                printf("\n");
                listar_fila(&fila_prioritaria, "PRIORITÁRIA");
                break;
                
            case 7: {
                int id;
                printf("\n🔍 ID a buscar: ");
                if (scanf("%d", &id) != 1) {
                    limpar_buffer();
                    printf("❌ ID inválido!\n");
                    break;
                }
                limpar_buffer();
                buscar_por_id(id);
                break;
            }
                
            case 8: {
                int id;
                printf("\n❌ ID a cancelar: ");
                if (scanf("%d", &id) != 1) {
                    limpar_buffer();
                    printf("❌ ID inválido!\n");
                    break;
                }
                limpar_buffer();
                cancelar_por_id(id);
                break;
            }
                
            case 9:
                exibir_estatisticas();
                break;
                
            case 10:
                configurar_proporcao();
                break;
                
            case 11:
                salvar_csv();
                break;
                
            case 12:
                salvar_csv_unico();
                break;
                
            case 13:
                carregar_csv();
                break;
                
            case 14:
                salvar_relatorio();
                break;
                
            case 0:
                liberar_memoria();
                printf("\n👋 Obrigado por usar o Gerenciador de Fila de Impressão! Até a próxima!\n");
                return 0;
                
            default:
                printf("❌ Opção inválida! Tente novamente.\n");
        }
    }
    
    return 0;
}
