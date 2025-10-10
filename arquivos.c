#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "arquivos.h"

void carregarReservas() {
    FILE *arq = fopen("reservas.txt", "r");
    if (arq == NULL) {
        printf("Arquivo reservas.txt nao encontrado. Iniciando com 0 reservas.\n");
        return;
    }

    Reserva temp;
    int maxId = 0;
    
    while (fscanf(arq, "%d;%d;%d;%[^;];%d;%[^;];%f;%[^\n]\n", 
                  &temp.id, 
                  &temp.id_usuario, 
                  &temp.id_cuidador,
                  temp.data_hora_inicio,
                  &temp.duracao_horas,
                  temp.nome_cachorro,
                  &temp.valor_total,
                  temp.status) == 8) {
        
        reservas = (Reserva*) realloc(reservas, (totalReservas + 1) * sizeof(Reserva));
        if (reservas == NULL) {
            perror("Falha na alocacao de memoria ao carregar reservas");
            exit(1);
        }

        reservas[totalReservas] = temp;
        totalReservas++;

        if (temp.id > maxId) {
            maxId = temp.id;
        }
    }
    
    
    fclose(arq);
    printf("%d reservas carregadas com sucesso.\n", totalReservas);
}
void salvarReservas() {
    FILE *arq = fopen("reservas.txt", "w"); 
    if (arq == NULL) {
        perror("Erro ao abrir reservas.txt para salvar");
        return;
    }
    
    for (int i = 0; i < totalReservas; i++) {
        fprintf(arq, "%d;%d;%d;%s;%d;%s;%.2f;%s\n", 
                reservas[i].id, 
                reservas[i].id_usuario, 
                reservas[i].id_cuidador,
                reservas[i].data_hora_inicio,
                reservas[i].duracao_horas,
                reservas[i].nome_cachorro,
                reservas[i].valor_total,
                reservas[i].status);
    }
    
    fclose(arq);
    printf("Dados de reservas salvos em reservas.txt.\n");
}



void inicializarDados() {
    carregarUsuarios();
    carregarCuidadores();
    carregarReservas();
    printf("\nSistema pronto para uso.\n");
}

void liberarMemoria() {
    if (usuarios != NULL) free(usuarios);
    if (cuidadores != NULL) free(cuidadores);
    if (reservas != NULL) free(reservas);
}


void menuRelatorios() {
    int opcao;
    do {
        printf("\n=============================================\n");
        printf("RELATORIOS\n"); [cite_start]
        printf("=============================================\n");
        printf("1 - Faturamento total por cuidador\n"); [cite_start]
        printf("2 - Total de reservas ativas e canceladas\n"); [cite_start]
        printf("3 - Historico de todas as reservas\n"); [cite_start]
        printf("0 - Voltar\n"); [cite_start]
        printf("=============================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: relatorioFaturamento(); break;
            case 2: relatorioReservas(); break;
            case 3: historicoReservas(); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void relatorioReservas() {
    int ativas = 0;
    int canceladas = 0;
    
    for (int i = 0; i < totalReservas; i++) {
        if (strcmp(reservas[i].status, "Ativa") == 0) {
            ativas++;
        } else if (strcmp(reservas[i].status, "Cancelada") == 0) {
            canceladas++;
        }
    }
    
    printf("\n--- TOTAL DE RESERVAS ---\n");
    printf("Reservas ativas: %d\n", ativas); [cite_start]
    printf("Reservas canceladas: %d\n", canceladas); [cite_start]
}
