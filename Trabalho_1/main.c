#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define COR_RESET   "\033[0m"
#define COR_NEGRITO "\033[1m"
#define COR_TITULO  "\033[1;36m"
#define COR_MENU    "\033[1;33m"
#define COR_OK      "\033[1;32m"
#define COR_ERRO    "\033[1;31m"
#define COR_INFO    "\033[0;37m"
#define COR_AVISO   "\033[1;35m"

static void limpar_tela(void) {
    system("cls");
}

static void pausar(void) {
    printf(COR_AVISO "\nPressione Enter para continuar..." COR_RESET);
    getchar();
}

static void habilitar_cores_windows(void) {
#ifdef _WIN32
    system("");
#endif
}

typedef struct Musica {
    int id;
    char titulo[50];
    char artista[50];
    int duracao;
    char genero[30];
    struct Musica *prox;
} Musica;

Musica *lista = NULL;

Musica* criar_musica(int id, const char *titulo, const char *artista, int duracao, const char *genero) {
    Musica *nova = (Musica*)malloc(sizeof(Musica));
    if (nova == NULL) {
        printf(COR_ERRO "Erro de alocação de memória!" COR_RESET);
        return NULL;
    }
    nova->id = id;
    strncpy(nova->titulo, titulo, 49);
    nova->titulo[49] = '\0';
    strncpy(nova->artista, artista, 49);
    nova->artista[49] = '\0';
    nova->duracao = duracao;
    strncpy(nova->genero, genero, 29);
    nova->genero[29] = '\0';
    nova->prox = NULL;
    return nova;
}

int id_existe(int id) {
    Musica *atual = lista;
    while (atual != NULL) {
        if (atual->id == id) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void formatar_duracao(int segundos, char *buffer, size_t tamanho) {
    int horas = segundos / 3600;
    int minutos = (segundos % 3600) / 60;
    int segs = segundos % 60;
    if (horas > 0) {
        snprintf(buffer, tamanho, "%dh %02dm %02ds", horas, minutos, segs);
    } else {
        snprintf(buffer, tamanho, "%dm %02ds", minutos, segs);
    }
}

void inserir_musica() {
    limpar_tela();
    int id;
    printf(COR_TITULO "\n🎵 Inserir Nova Música 🎵\n" COR_RESET);
    printf("ID: ");
    if (scanf("%d", &id) != 1) {
        getchar();
        printf(COR_ERRO "Erro: ID inválido!" COR_RESET);
        pausar();
        return;
    }
    getchar();
    
    if (id <= 0) {
        printf(COR_ERRO "Erro: ID deve ser positivo!\n" COR_RESET);
        pausar();
        return;
    }
    
    if (id_existe(id)) {
        printf(COR_ERRO "Ops! Já existe uma música com o ID %d. Escolha outro!\n" COR_RESET, id);
        pausar();
        return;
    }
    
    char titulo[50], artista[50], genero[30];
    int duracao;
    
    printf("Título: ");
    fgets(titulo, 50, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';
    if (strlen(titulo) == 0) {
        printf(COR_ERRO "Erro: Título não pode ficar vazio!\n" COR_RESET);
        pausar();
        return;
    }
    
    printf("Artista: ");
    fgets(artista, 50, stdin);
    artista[strcspn(artista, "\n")] = '\0';
    if (strlen(artista) == 0) {
        printf(COR_ERRO "Erro: Artista não pode ficar vazio!\n" COR_RESET);
        pausar();
        return;
    }
    
    printf("Duração (segundos): ");
    if (scanf("%d", &duracao) != 1 || duracao <= 0) {
        getchar();
        printf(COR_ERRO "Erro: Duração deve ser um número positivo!\n" COR_RESET);
        pausar();
        return;
    }
    getchar();
    
    printf("Gênero: ");
    fgets(genero, 30, stdin);
    genero[strcspn(genero, "\n")] = '\0';
    if (strlen(genero) == 0) {
        printf(COR_ERRO "Erro: Gênero não pode ficar vazio!\n" COR_RESET);
        pausar();
        return;
    }
    
    Musica *nova = criar_musica(id, titulo, artista, duracao, genero);
    if (nova == NULL) {
        pausar();
        return;
    }
    
    if (lista == NULL) {
        lista = nova;
    } else {
        Musica *atual = lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = nova;
    }
    
    char duracao_formatada[50];
    formatar_duracao(duracao, duracao_formatada, sizeof(duracao_formatada));
    printf(COR_OK "\n🎉 Música adicionada com sucesso!\n" COR_RESET);
    printf("📋 %s - %s (%s)\n", titulo, artista, duracao_formatada);
    pausar();
}

void buscar_musica() {
    limpar_tela();
    if (lista == NULL) {
        printf(COR_ERRO "\nAinda não há músicas na playlist!\n" COR_RESET);
        pausar();
        return;
    }
    
    int id;
    printf(COR_TITULO "\n🔍 Buscar Música 🔍\n" COR_RESET);
    printf("Digite o ID da música: ");
    if (scanf("%d", &id) != 1) {
        getchar();
        printf(COR_ERRO "Erro: ID inválido!" COR_RESET);
        pausar();
        return;
    }
    getchar();
    
    Musica *atual = lista;
    while (atual != NULL) {
        if (atual->id == id) {
            char duracao_formatada[50];
            formatar_duracao(atual->duracao, duracao_formatada, sizeof(duracao_formatada));
            printf(COR_OK "\n✨ Música Encontrada ✨\n" COR_RESET);
            printf(COR_INFO "🆔 ID: %d\n", atual->id);
            printf("🎵 Título: %s\n", atual->titulo);
            printf("🎤 Artista: %s\n", atual->artista);
            printf("⏱️ Duração: %s\n", duracao_formatada);
            printf("🎶 Gênero: %s\n" COR_RESET, atual->genero);
            pausar();
            return;
        }
        atual = atual->prox;
    }
    
    printf(COR_ERRO "Desculpe, não encontrei nenhuma música com o ID %d.\n" COR_RESET, id);
    pausar();
}

void editar_musica() {
    limpar_tela();
    if (lista == NULL) {
        printf(COR_ERRO "\nAinda não há músicas para editar!\n" COR_RESET);
        pausar();
        return;
    }
    
    int id;
    printf(COR_TITULO "\n✏️ Editar Música ✏️\n" COR_RESET);
    printf("Digite o ID da música que deseja editar: ");
    if (scanf("%d", &id) != 1) {
        getchar();
        printf(COR_ERRO "Erro: ID inválido!" COR_RESET);
        pausar();
        return;
    }
    getchar();
    
    Musica *atual = lista;
    while (atual != NULL) {
        if (atual->id == id) {
            char temp[50];
            printf("\n🎵 Música atual: %s - %s\n", atual->titulo, atual->artista);
            printf("(Deixe em branco para manter o valor atual)\n\n");
            
            printf("Novo título: ");
            fgets(temp, 50, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            if (strlen(temp) > 0) {
                strncpy(atual->titulo, temp, 49);
                atual->titulo[49] = '\0';
            }
            
            printf("Novo artista: ");
            fgets(temp, 50, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            if (strlen(temp) > 0) {
                strncpy(atual->artista, temp, 49);
                atual->artista[49] = '\0';
            }
            
            printf("Nova duração (segundos): ");
            fgets(temp, 50, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            if (strlen(temp) > 0) {
                int nova_duracao = atoi(temp);
                if (nova_duracao > 0) {
                    atual->duracao = nova_duracao;
                } else {
                    printf(COR_AVISO "Aviso: Duração inválida, mantendo o valor atual.\n" COR_RESET);
                }
            }
            
            printf("Novo gênero: ");
            fgets(temp, 30, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            if (strlen(temp) > 0) {
                strncpy(atual->genero, temp, 29);
                atual->genero[29] = '\0';
            }
            
            printf(COR_OK "\n✅ Música editada com sucesso!\n" COR_RESET);
            pausar();
            return;
        }
        atual = atual->prox;
    }
    
    printf(COR_ERRO "Desculpe, não encontrei nenhuma música com o ID %d.\n" COR_RESET, id);
    pausar();
}

void excluir_musica() {
    limpar_tela();
    if (lista == NULL) {
        printf(COR_ERRO "\nAinda não há músicas para excluir!\n" COR_RESET);
        pausar();
        return;
    }
    
    int id;
    printf(COR_TITULO "\n🗑️ Excluir Música 🗑️\n" COR_RESET);
    printf("Digite o ID da música que deseja excluir: ");
    if (scanf("%d", &id) != 1) {
        getchar();
        printf(COR_ERRO "Erro: ID inválido!" COR_RESET);
        pausar();
        return;
    }
    getchar();
    
    Musica *atual = lista;
    Musica *anterior = NULL;
    
    while (atual != NULL) {
        if (atual->id == id) {
            char duracao_formatada[50];
            formatar_duracao(atual->duracao, duracao_formatada, sizeof(duracao_formatada));
            
            printf(COR_INFO "\n📋 Música selecionada para exclusão:\n");
            printf("  🆔 ID:     %d\n", atual->id);
            printf("  🎵 Título: %s\n", atual->titulo);
            printf("  🎤 Artista: %s\n", atual->artista);
            printf("  ⏱️ Duração: %s\n", duracao_formatada);
            printf("  🎶 Gênero: %s\n" COR_RESET, atual->genero);
            
            char resposta[4];
            printf(COR_AVISO "\n⚠️ Tem certeza que deseja EXCLUIR esta música? (S/N): " COR_RESET);
            fgets(resposta, sizeof(resposta), stdin);
            
            if (resposta[0] != 'S' && resposta[0] != 's') {
                printf(COR_AVISO "\nExclusão cancelada! A música permanece na playlist.\n" COR_RESET);
                pausar();
                return;
            }
            
            if (anterior == NULL) {
                lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            
            printf(COR_OK "\n✅ Música com ID %d foi removida da playlist!\n" COR_RESET, id);
            pausar();
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    
    printf(COR_ERRO "Desculpe, não encontrei nenhuma música com o ID %d.\n" COR_RESET, id);
    pausar();
}

void listar_musicas() {
    limpar_tela();
    if (lista == NULL) {
        printf(COR_AVISO "\n📭 A playlist está vazia!\nAdicione algumas músicas para começar.\n" COR_RESET);
        pausar();
        return;
    }
    
    printf(COR_TITULO "\n🎶 Sua Playlist 🎶\n" COR_RESET);
    Musica *atual = lista;
    int cont = 1;
    while (atual != NULL) {
        char duracao_formatada[50];
        formatar_duracao(atual->duracao, duracao_formatada, sizeof(duracao_formatada));
        printf("\n%d. 🆔 %d\n", cont++, atual->id);
        printf("   🎵 %s\n", atual->titulo);
        printf("   🎤 %s\n", atual->artista);
        printf("   ⏱️ %s\n", duracao_formatada);
        printf("   🎶 %s\n", atual->genero);
        atual = atual->prox;
    }
    printf("\n");
    pausar();
}

void exibir_estatisticas() {
    limpar_tela();
    if (lista == NULL) {
        printf(COR_AVISO "\n📭 A playlist está vazia!\n" COR_RESET);
        pausar();
        return;
    }
    
    int total_musicas = 0;
    int total_duracao = 0;
    Musica *atual = lista;
    
    while (atual != NULL) {
        total_musicas++;
        total_duracao += atual->duracao;
        atual = atual->prox;
    }
    
    char total_formatado[50];
    formatar_duracao(total_duracao, total_formatado, sizeof(total_formatado));
    
    printf(COR_TITULO "\n📊 Estatísticas da Playlist 📊\n" COR_RESET);
    printf("\n");
    printf(COR_INFO "🎵 Total de músicas: %d\n", total_musicas);
    printf("⏱️ Duração total: %s\n", total_formatado);
    printf("📈 Média por música: ", total_musicas);
    if (total_musicas > 0) {
        char media_formatada[50];
        formatar_duracao(total_duracao / total_musicas, media_formatada, sizeof(media_formatada));
        printf("%s\n" COR_RESET, media_formatada);
    } else {
        printf("--\n" COR_RESET);
    }
    pausar();
}

void salvar_csv() {
    limpar_tela();
    FILE *arquivo = fopen("playlist.csv", "w");
    
    if (arquivo == NULL) {
        printf(COR_ERRO "\n❌ Erro ao abrir o arquivo para escrita!\n" COR_RESET);
        pausar();
        return;
    }
    
    fprintf(arquivo, "id;titulo;artista;duracao;genero\n");
    
    Musica *atual = lista;
    int count = 0;
    while (atual != NULL) {
        fprintf(arquivo, "%d;%s;%s;%d;%s\n",
                atual->id,
                atual->titulo,
                atual->artista,
                atual->duracao,
                atual->genero);
        atual = atual->prox;
        count++;
    }
    
    fclose(arquivo);
    printf(COR_OK "\n✅ Playlist salva com sucesso!\n" COR_RESET);
    printf("📝 %d músicas salvas em playlist.csv\n", count);
    pausar();
}

void carregar_csv() {
    limpar_tela();
    while (lista != NULL) {
        Musica *temp = lista;
        lista = lista->prox;
        free(temp);
    }
    
    FILE *arquivo = fopen("playlist.csv", "r");
    
    if (arquivo == NULL) {
        printf(COR_AVISO "\n📭 Arquivo playlist.csv não encontrado.\nIniciando com playlist vazia.\n" COR_RESET);
        pausar();
        return;
    }
    
    char linha[200];
    
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);
        printf(COR_AVISO "\nArquivo playlist.csv está vazio.\n" COR_RESET);
        pausar();
        return;
    }
    
    Musica *ultima = NULL;
    int count = 0;
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        
        int id, duracao;
        char titulo[50], artista[50], genero[30];
        
        if (sscanf(linha, "%d;%49[^;];%49[^;];%d;%29[^\n]",
                   &id, titulo, artista, &duracao, genero) == 5) {
            Musica *nova = criar_musica(id, titulo, artista, duracao, genero);
            if (nova != NULL) {
                if (lista == NULL) {
                    lista = nova;
                } else {
                    ultima->prox = nova;
                }
                ultima = nova;
                count++;
            }
        }
    }
    
    fclose(arquivo);
    printf(COR_OK "\n✅ Playlist carregada com sucesso!\n" COR_RESET);
    printf("📝 %d músicas carregadas\n", count);
    pausar();
}

void gerar_relatorio() {
    limpar_tela();
    if (lista == NULL) {
        printf(COR_AVISO "\n📭 A playlist está vazia!\n" COR_RESET);
        pausar();
        return;
    }
    
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    char data_hora[50];
    strftime(data_hora, sizeof(data_hora), "%Y-%m-%d_%H-%M-%S", tm_info);
    
    char nome_arquivo[100];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "relatorio_playlist_%s.txt", data_hora);
    
    FILE *arquivo = fopen(nome_arquivo, "w");
    
    if (arquivo == NULL) {
        printf(COR_ERRO "\n❌ Erro ao criar relatório!\n" COR_RESET);
        pausar();
        return;
    }
    
    int total_musicas = 0;
    int total_duracao = 0;
    Musica *atual = lista;
    
    while (atual != NULL) {
        total_musicas++;
        total_duracao += atual->duracao;
        atual = atual->prox;
    }
    
    char total_formatado[50];
    formatar_duracao(total_duracao, total_formatado, sizeof(total_formatado));
    
    fprintf(arquivo, "=========================================\n");
    fprintf(arquivo, "       RELATÓRIO DA PLAYLIST\n");
    fprintf(arquivo, "=========================================\n");
    fprintf(arquivo, "Gerado em: %s", ctime(&agora));
    fprintf(arquivo, "Total de músicas: %d\n", total_musicas);
    fprintf(arquivo, "Duração total: %s\n", total_formatado);
    if (total_musicas > 0) {
        char media_formatada[50];
        formatar_duracao(total_duracao / total_musicas, media_formatada, sizeof(media_formatada));
        fprintf(arquivo, "Média por música: %s\n", media_formatada);
    }
    fprintf(arquivo, "=========================================\n");
    fprintf(arquivo, "\nDETALHES DAS MÚSICAS:\n");
    fprintf(arquivo, "-----------------------------------------\n");
    
    atual = lista;
    int cont = 1;
    while (atual != NULL) {
        char duracao_formatada[50];
        formatar_duracao(atual->duracao, duracao_formatada, sizeof(duracao_formatada));
        fprintf(arquivo, "%d. ID: %d\n", cont++, atual->id);
        fprintf(arquivo, "   Título: %s\n", atual->titulo);
        fprintf(arquivo, "   Artista: %s\n", atual->artista);
        fprintf(arquivo, "   Duração: %s\n", duracao_formatada);
        fprintf(arquivo, "   Gênero: %s\n", atual->genero);
        fprintf(arquivo, "-----------------------------------------\n");
        atual = atual->prox;
    }
    
    fclose(arquivo);
    
    printf(COR_OK "\n✅ Relatório gerado com sucesso!\n" COR_RESET);
    printf("📄 Arquivo: %s\n", nome_arquivo);
    pausar();
}

void liberar_lista() {
    while (lista != NULL) {
        Musica *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

void exibir_menu() {
    printf(COR_TITULO "\n🎵 GERENCIADOR DE PLAYLIST 🎵\n" COR_RESET);
    printf(COR_MENU "1. 🎵 Inserir música\n");
    printf("2. 🔍 Buscar música por ID\n");
    printf("3. ✏️ Editar música\n");
    printf("4. 🗑️ Excluir música\n");
    printf("5. 📋 Listar todas as músicas\n");
    printf("6. 📊 Estatísticas da playlist\n");
    printf("7. 📄 Gerar relatório\n");
    printf("8. 💾 Salvar em CSV\n");
    printf("9. 📂 Carregar do CSV\n");
    printf("0. 🚪 Sair\n" COR_RESET);
    printf("Escolha uma opção: ");
}

int main() {
    int opcao;
    
    habilitar_cores_windows();
    setlocale(LC_ALL, "Portuguese");
    
    printf(COR_TITULO "\n=========================================\n" COR_RESET);
    printf(COR_NEGRITO "        BEM-VINDO AO GERENCIADOR DE PLAYLIST!\n" COR_RESET);
    printf(COR_TITULO "=========================================\n" COR_RESET);
    
    limpar_tela();
    while (lista != NULL) {
        Musica *temp = lista;
        lista = lista->prox;
        free(temp);
    }
    
    FILE *arquivo = fopen("playlist.csv", "r");
    
    if (arquivo != NULL) {
        char linha[200];
        
        if (fgets(linha, sizeof(linha), arquivo) != NULL) {
            Musica *ultima = NULL;
            int count = 0;
            
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                linha[strcspn(linha, "\n")] = '\0';
                
                int id, duracao;
                char titulo[50], artista[50], genero[30];
                
                if (sscanf(linha, "%d;%49[^;];%49[^;];%d;%29[^\n]",
                           &id, titulo, artista, &duracao, genero) == 5) {
                    Musica *nova = criar_musica(id, titulo, artista, duracao, genero);
                    if (nova != NULL) {
                        if (lista == NULL) {
                            lista = nova;
                        } else {
                            ultima->prox = nova;
                        }
                        ultima = nova;
                        count++;
                    }
                }
            }
            
            if (count > 0) {
                printf(COR_OK "✅ %d músicas carregadas automaticamente!\n" COR_RESET, count);
            }
        }
        
        fclose(arquivo);
    }
    
    pausar();
    
    while (1) {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            getchar();
            printf(COR_ERRO "\n❌ Opção inválida! Por favor, digite um número.\n" COR_RESET);
            pausar();
            continue;
        }
        getchar();
        
        switch (opcao) {
            case 1:
                inserir_musica();
                break;
            case 2:
                buscar_musica();
                break;
            case 3:
                editar_musica();
                break;
            case 4:
                excluir_musica();
                break;
            case 5:
                listar_musicas();
                break;
            case 6:
                exibir_estatisticas();
                break;
            case 7:
                gerar_relatorio();
                break;
            case 8:
                salvar_csv();
                break;
            case 9:
                carregar_csv();
                break;
            case 0:
                printf("\n💾 Salvando playlist...\n");
                salvar_csv();
                liberar_lista();
                printf(COR_OK "\n👋 Obrigado por usar o Gerenciador de Playlist!\nAté a próxima!\n" COR_RESET);
                return 0;
            default:
                printf(COR_ERRO "\n❌ Opção inválida! Escolha um número entre 0 e 9.\n" COR_RESET);
                pausar();
        }
    }
    
    return 0;
}