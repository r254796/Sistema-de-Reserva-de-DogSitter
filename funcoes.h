#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "arquivos.h"

void limparTela(){
    printf("\033[2J\033[H");
}

/*Possibilita o usuário de retornar ao menu anterior ou sair do programa*/
void retornarMenu(){
    int opcao;
    
    do{
    printf("[1] VOLTAR\t[0] SAIR\n");
    printf("Escolha uma opção: ");

    scanf("%d", &opcao);
    while(getchar() != '\n'); //limpa o buffer

    switch(opcao){
        case 0: printf("Saindo...\n"); exit(0);
        case 1: limparTela(); break;
        default: printf("OPÇÃO INVÁLIDA.\n\n");
    }

    } while(opcao != 1 && opcao != 0);
}


void exibirMenuPrincipal(){
    int opcao;
    
    do{
        printf("=============================================\n");
        printf("          MENU PRINCIPAL DO USUÁRIO\n");
        printf("=============================================\n");
        printf("1 - Ver cuidadores disponíveis\n");
        printf("2 - Buscar cuidador por data\n");
        printf("3 - Ver detalhes de um cuidador\n");
        printf("4 - Fazer uma reserva\n");
        printf("5 - Consultar minhas reservas\n");
        printf("6 - Cancelar uma reserva\n");
        printf("7 - Relatórios \n");
        printf("0 - Sair\n");
        printf("=============================================\n");
        printf("Escolha uma opção: ");

        scanf("%d", &opcao);
        while(getchar() != '\n'); //limpa o buffer

        switch (opcao) {
            case 1: limparTela(); listarCuidadores(); retornarMenu(); break; //exibe a lista de cuidadores
            case 7: limparTela(); exibirMenuRelatorios(); break;
            case 0: printf("Saindo...\n"); exit(0);
            default: limparTela(); printf("OPÇÃO INVÁLIDA.\n");
        }

    } while(opcao != 0);
}

void listarCuidadores() {
    printf("=========================================================\n");
    printf("                CUIDADORES DISPONÍVEIS\n");
    printf("=========================================================\n\n");
    printf("%-4s|%-20s|%-12s|%-20s\n", "ID", "NOME", "VALOR/HORA", "PORTE ACEITO");

    for(int i = 0; i < totalCuidadores; i++){
        printf("%-4d|%-20s|%-12.2f|%-20s\n", 
                cuidadores[i].id, 
                cuidadores[i].nome, 
                cuidadores[i].valor_hora, 
                cuidadores[i].porte_aceito);
    }
    printf("\n");
}

void carregarCuidadores(){
    FILE *arq = fopen("cuidadores.txt", "r");
    if (arq == NULL) {
        printf("Arquivo cuidadores.txt nao encontrado.\n");
        exit(1);
    }
    
    Cuidador temp;

    while (fscanf(arq, "%d;%[^;];%f;%[^;];%[^;];%d;%d;%[^\n]\n",
                  &temp.id,
                  temp.nome,
                  &temp.valor_hora,
                  temp.porte_aceito,
                  temp.dias_expediente,
                  &temp.hora_inicio_expediente,
                  &temp.hora_fim_expediente,
                  temp.experiencia) == 8) {

        cuidadores = (Cuidador*) realloc(cuidadores, (totalCuidadores + 1) * sizeof(Cuidador));
        if (cuidadores == NULL) {
            perror("Falha na alocação de memória ao carregar cuidadores.\n");
            exit(1);
        }

        cuidadores[totalCuidadores] = temp;
        totalCuidadores++;
    }

    fclose(arq);
}


void carregarReservas() {
    FILE *arq = fopen("reservas.txt", "r");
    if (arq == NULL) {
        printf("Arquivo reservas.txt nao encontrado. Iniciando com 0 reservas.\n");
        return;
    }

    Reserva temp;
    int maxId = 0;
    
    while (fscanf(arq, "%d;%d;%d;%[^;];%[^;];%d;%[^;];%f;%[^\n]\n", 
                  &temp.id, 
                  &temp.id_usuario, 
                  &temp.id_cuidador,
                  temp.data,
                  temp.hora,
                  &temp.duracao_horas,
                  temp.nome_cachorro,
                  &temp.valor_total,
                  temp.status) == 9) {
        
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
}


void salvarReservas() {
    FILE *arq = fopen("reservas.txt", "w"); 
    if (arq == NULL) {
        perror("Erro ao abrir reservas.txt para salvar");
        return;
    }
    
    for (int i = 0; i < totalReservas; i++) {
        fprintf(arq, "%d;%d;%d;%s;%s;%d;%s;%.2f;%s\n", 
                reservas[i].id, 
                reservas[i].id_usuario, 
                reservas[i].id_cuidador,
                reservas[i].data,
                reservas[i].hora,
                reservas[i].duracao_horas,
                reservas[i].nome_cachorro,
                reservas[i].valor_total,
                reservas[i].status);
    }
    
    fclose(arq);
}



void inicializarDados() {
    //carregarUsuarios(); //não implementada
    carregarCuidadores();
    carregarReservas();
}

void liberarMemoria() {
    if (usuarios != NULL) free(usuarios);
    if (cuidadores != NULL) free(cuidadores);
    if (reservas != NULL) free(reservas);
}


void exibirMenuRelatorios() {
    int opcao;
    do {
        printf("=============================================\n");
        printf("                  RELATÓRIOS\n");
        printf("=============================================\n");
        printf("1 - Faturamento total por cuidador\n");
        printf("2 - Total de reservas ativas e canceladas\n");
        printf("3 - Histórico de todas as reservas\n");
        printf("0 - Voltar\n");
        printf("=============================================\n");
        printf("Escolha uma opção: ");

        scanf("%d", &opcao);
        while(getchar() != '\n'); //limpa o buffer

        switch (opcao) {
            //case 1: relatorioFaturamento(); break; //não implementada
            case 2: limparTela(); relatorioReservas(); retornarMenu(); limparTela(); break; //exibe o relatório de reservas
            //case 3: historicoReservas(); break; //não implementada
            case 0: limparTela(); break;
            default: limparTela(); printf("OPÇÃO INVÁLIDA.\n");
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
    
    printf("----------------------------\n");
    printf("     TOTAL DE RESERVAS\n");
    printf("----------------------------\n");
    printf("Reservas ativas: %d\n", ativas);
    printf("Reservas canceladas: %d\n\n", canceladas);
}
