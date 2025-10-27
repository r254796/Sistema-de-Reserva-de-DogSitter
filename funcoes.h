#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
        case 0: liberarMemoria(); printf("Saindo...\n"); exit(0);
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
        printf("1 - Ver lista de cuidadores\n");
        printf("2 - Buscar cuidadores disponíveis por data\n");
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
            case 2: limparTela(); exibirMenuBuscarCuidadorPorData(); retornarMenu(); break;
            case 3: limparTela(); exibirMenuDetalhesCuidador(); retornarMenu(); break;
            case 7: limparTela(); exibirMenuRelatorios(); break;
            case 0: liberarMemoria(); printf("Saindo...\n"); exit(0);
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


int validarData(char data[]) {
    int dia, mes, ano, diasNoMes;

    // Verifica tamanho exato e a posição das barras
    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        printf("DATA EM FORMATO INVÁLIDO. TENTE NOVAMENTE.\n\n");
        return 0;
    }

    // Verifica se todos os outros caracteres são dígitos
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(data[i])) {
            printf("DATA EM FORMATO INVÁLIDO. TENTE NOVAMENTE.\n\n");
            return 0;
        }
    }

    sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano);

    // Verifica validade dos valores
    if (ano < 1 || mes < 1 || mes > 12 || dia < 1) {
        printf("DATA INVÁLIDA. TENTE NOVAMENTE.\n\n");
        return 0;
    }

    // Dias no mês
    switch (mes) {
        case 2:
            // Ano bissexto
            if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
                diasNoMes = 29;
            else
                diasNoMes = 28;
            break;
        case 4: case 6: case 9: case 11:
            diasNoMes = 30;
            break;
        default:
            diasNoMes = 31;
    }

    if (dia > diasNoMes) {
        printf("DATA INVÁLIDA. TENTE NOVAMENTE.\n\n");
        return 0;
    }

    return 1;
}


int validarHorario(char horario[]){
    int horas, minutos;

    /*verifica se o horário está no formato correto*/
    if(strlen(horario) != 5 || horario[2] != ':'){
        printf("HORÁRIO EM FORMATO INVÁLIDO. TENTE NOVAMENTE.\n\n");
        return 0;
    }
    for(int i = 0; i < 5; i++){
        if(i == 2)
            continue;
        if(!isdigit(horario[i])){
            printf("HORÁRIO EM FORMATO INVÁLIDO. TENTE NOVAMENTE.\n\n");
            return 0;
        }
    }
    
    /*verifica se o horário existe*/
    sscanf(horario, "%d:%d", &horas, &minutos);
    if(horas > 23 || minutos > 59 || minutos < 0 || horas < 0){
        printf("HORÁRIO INVÁLIDO. TENTE NOVAMENTE.\n\n");
        return 0;
    }
    else return 1;
}


int horaParaMinutos(char horario[]) {
    int horas, minutos;
    sscanf(horario, "%d:%d", &horas, &minutos);
    return horas * 60 + minutos;
}


/*recebe o id do cuidador e retorna o índice dele no vetor*/
int verificaIndiceCuidador(int idCuidadorBuscado){
    for(int i = 0; i < totalCuidadores; i++){
        if(cuidadores[i].id == idCuidadorBuscado){
            return i;
        }
    }
    return -1;
}


/*verifica se o cuidador possui uma reserva ativa na data e hora recebida*/
int buscarCuidadorPorData(int idCuidadorBuscado, char dataBuscada[], char horaBuscada[], int duracaoBuscada){
    int horaReservaMinutos, horaBuscadaMinutos, duracaoBuscadaMinutos, horaInicioExpedMinutos, horaFimExpedMinutos, iCuidadorBuscado;

    iCuidadorBuscado = verificaIndiceCuidador(idCuidadorBuscado); //verifica se o cuidador buscado existe
    if(iCuidadorBuscado == -1){
        return 0;
    } 

    /*verifica se o cuidador está disponível na hora e data passadas analisando as reservas já feitas*/
    for(int i = 0; i < totalReservas; i++){
        horaReservaMinutos = horaParaMinutos(reservas[i].hora);
        horaBuscadaMinutos = horaParaMinutos(horaBuscada);
        horaInicioExpedMinutos = horaParaMinutos(cuidadores[iCuidadorBuscado].hora_inicio_expediente);
        horaFimExpedMinutos = horaParaMinutos(cuidadores[iCuidadorBuscado].hora_fim_expediente);
        duracaoBuscadaMinutos = duracaoBuscada * 60;

        if(horaInicioExpedMinutos > horaBuscadaMinutos || horaFimExpedMinutos - 60 < horaBuscadaMinutos || horaBuscadaMinutos + duracaoBuscadaMinutos > horaFimExpedMinutos) //verifica se a hora buscada está dentro do expediente do cuidador
            return 0;

        if(reservas[i].id_cuidador != idCuidadorBuscado) // verifica se o cuidador buscado não é o mesmo do cuidador da reserva
            continue;

        if(strcmp(reservas[i].status, "Cancelada") == 0) // verifica se a reserva foi cancelada, podendo ser considerada como horário disponível caso sim
            continue;
        
        if(strcmp(reservas[i].data, dataBuscada) != 0) //verifica se a data buscada não é a mesma da data da reserva
            continue;


        /*verifica se a hora buscada não se encontra entre o período da reserva*/
        if((horaReservaMinutos > horaBuscadaMinutos) || horaBuscadaMinutos >= horaReservaMinutos + (reservas[i].duracao_horas * 60)){
            if(horaBuscadaMinutos + duracaoBuscadaMinutos <= horaReservaMinutos)
                continue;
            else
                return 0;
        }
        else
            return 0;
    }
    return 1;
}

//modifica o valor das variáveis passadas nos parâmetros para as informações de busca inseridas pelo usuário
void receberInformacoesDeBusca(char dataBuscada[], char horaBuscada[], int *duracaoBuscada){
    int i;

    do{
        printf("Insira a data (dd/mm/aaaa): ");
        scanf("%11s", dataBuscada);
        while(getchar() != '\n'); //limpa o buffer
    } while(!(validarData(dataBuscada)));

    do{
        printf("Insira o horário (hh:mm): ");
        scanf("%6s", horaBuscada);
        while(getchar() != '\n'); //limpa o buffer
    } while(!(validarHorario(horaBuscada)));

    do{
        printf("---------------------------------------------\n");
        printf("             DURAÇÃO DA SESSÃO\n");
        printf("---------------------------------------------\n");
        for(i = 1; i <= 8; i+=2){
            printf("[%d] - %d hora(s) \t[%d] - %d hora(s)\n", i, i, i+1, i+1);
        }
        printf("\nEscolha a duração da sessão: ");
        scanf("%d", duracaoBuscada);
        while(getchar() != '\n'); //limpa o buffer

        if(*duracaoBuscada > 8 || *duracaoBuscada < 1){
            limparTela();
            printf("DURAÇÃO DE SESSÃO INVÁLIDA.\n");
        }

    } while(*duracaoBuscada < 1 || *duracaoBuscada > 8);
}


void exibirMenuBuscarCuidadorPorData(){
    char dataBuscada[MAX_DATA];
    char horaBuscada[MAX_HORA];
    int duracaoBuscada;
    int cuidadorDisponivel;
    int totalCuidadoresDisponiveis = 0;
    int i;
    
    printf("=============================================\n");
    printf("          BUSCAR CUIDADORES POR DATA\n");
    printf("=============================================\n");

    receberInformacoesDeBusca(dataBuscada, horaBuscada, &duracaoBuscada);
    limparTela();

    printf("=======================================================\n");
    printf("                CUIDADORES ENCONTRADOS\n");
    printf("=======================================================\n");
    printf("DATA: %s   HORÁRIO: %s   DURAÇÃO: %d horas(s)\n", dataBuscada, horaBuscada, duracaoBuscada);
    printf("-------------------------------------------------------\n");

    /*para cada cuidador, verifica se ele está disponível no horário e data e exibe as informações dele*/
    for(i = 0; i < totalCuidadores; i++){
        if(cuidadorDisponivel = buscarCuidadorPorData(cuidadores[i].id, dataBuscada, horaBuscada, duracaoBuscada)){
            printf("%d - %s - (%.2f/h)\n", cuidadores[i].id, cuidadores[i].nome, cuidadores[i].valor_hora);
            totalCuidadoresDisponiveis += 1;
        }
    }
    if(totalCuidadoresDisponiveis == 0){
        printf("NENHUM CUIDADOR ENCONTRADO NESSA DATA E HORÁRIO.\n\n");
    }
    else
        printf("\nTOTAL DE CUIDADORES ENCONTRADOS: %d\n\n", totalCuidadoresDisponiveis);

}


void exibirMenuDetalhesCuidador(){
    int idCuidadorBuscado;
    int iCuidadorBuscado;

    do{
        printf("===============================================================\n");
        printf("                      DETALHES DO CUIDADOR\n");
        printf("===============================================================\n");
        printf("Insira o id do cuidador para saber mais detalhes sobre ele: ");
        scanf("%d", &idCuidadorBuscado);
        while(getchar() != '\n'); //limpa o buffer
        
        /*verifica se o cuidador existe e imprime na tela as informações dele*/
        iCuidadorBuscado = verificaIndiceCuidador(idCuidadorBuscado);
        if(iCuidadorBuscado != -1){
            printf("\nNome: %s\n", cuidadores[iCuidadorBuscado].nome);
            printf("Valor/hora: R$%.2f\n", cuidadores[iCuidadorBuscado].valor_hora);
            printf("Porte aceito: %s\n", cuidadores[iCuidadorBuscado].porte_aceito);
            printf("Disponibilidade: %s, %s às %s\n", cuidadores[iCuidadorBuscado].dias_expediente, cuidadores[iCuidadorBuscado].hora_inicio_expediente, cuidadores[iCuidadorBuscado].hora_fim_expediente);
            printf("Experiência: %s\n\n", cuidadores[iCuidadorBuscado].experiencia);
        }
        else{
            limparTela();
            printf("ID DE CUIDADOR INVÁLIDO. TENTE NOVAMENTE.\n");
        }
    } while(iCuidadorBuscado == -1);

}


void carregarCuidadores(){
    FILE *arq = fopen("cuidadores.txt", "r");
    if (arq == NULL) {
        printf("Arquivo cuidadores.txt nao encontrado.\n");
        exit(1);
    }
    
    Cuidador temp;

    while (fscanf(arq, "%d;%[^;];%f;%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                  &temp.id,
                  temp.nome,
                  &temp.valor_hora,
                  temp.porte_aceito,
                  temp.dias_expediente,
                  temp.hora_inicio_expediente,
                  temp.hora_fim_expediente,
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
        exit(1);
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


//FEITO POR GABRIEL
/* --- Início: implementações das funções de Reservas (Pessoa 3) --- */

/* cria uma nova reserva para o usuário idUsuario */
void novaReserva(int idUsuario) {
    int idCuidador;
    char data[MAX_DATA];
    char hora[MAX_HORA];
    int duracao;
    char nomeCachorro[MAX_NOME];
    int idxCuidador;

    printf("Digite o ID do cuidador: ");
    if (scanf("%d%*c", &idCuidador) != 1) {
        printf("Entrada inválida.\n");
        return;
    }

    idxCuidador = verificaIndiceCuidador(idCuidador);
    if (idxCuidador == -1) {
        printf("Cuidador com ID %d não encontrado.\n", idCuidador);
        return;
    }

    printf("Digite a data (dd/mm/aaaa): ");
    if (fgets(data, MAX_DATA, stdin) == NULL) return;
    data[strcspn(data, "\n")] = '\0';

    printf("Digite a hora (hh:mm): ");
    if (fgets(hora, MAX_HORA, stdin) == NULL) return;
    hora[strcspn(hora, "\n")] = '\0';

    printf("Digite a duração em horas (ex: 2): ");
    if (scanf("%d%*c", &duracao) != 1) {
        printf("Entrada inválida.\n");
        return;
    }

    /* verificar disponibilidade usando a função já existente */
    int disponivel = buscarCuidadorPorData(idCuidador, data, hora, duracao);
    if (!disponivel) {
        printf("Cuidador indisponível nesse horário/data.\n");
        return;
    }

    printf("Nome do cachorro: ");
    if (fgets(nomeCachorro, MAX_NOME, stdin) == NULL) return;
    nomeCachorro[strcspn(nomeCachorro, "\n")] = '\0';

    /* calcular valor total */
    float valor_hora = cuidadores[idxCuidador].valor_hora;
    float valor_total = valor_hora * (float)duracao;

    printf("Valor total: R$ %.2f\n", valor_total);
    printf("Deseja confirmar a reserva? (S/N): ");
    char opc;
    if (scanf(" %c%*c", &opc) != 1) return;
    if (opc != 'S' && opc != 's') {
        printf("Reserva cancelada pelo usuário.\n");
        return;
    }

    /* cria a Reserva */
    Reserva nova;
    /* gera id: pega maior id existente + 1 (evita duplicar caso tenha cancelamentos) */
    int maxId = 0;
    for (int i = 0; i < totalReservas; i++) if (reservas[i].id > maxId) maxId = reservas[i].id;
    nova.id = maxId + 1;

    nova.id_usuario = idUsuario;
    nova.id_cuidador = idCuidador;
    strncpy(nova.data, data, MAX_DATA-1); nova.data[MAX_DATA-1] = '\0';
    strncpy(nova.hora, hora, MAX_HORA-1); nova.hora[MAX_HORA-1] = '\0';
    nova.duracao_horas = duracao;
    strncpy(nova.nome_cachorro, nomeCachorro, MAX_NOME-1); nova.nome_cachorro[MAX_NOME-1] = '\0';
    nova.valor_total = valor_total;
    strncpy(nova.status, "Ativa", MAX_STATUS-1); nova.status[MAX_STATUS-1] = '\0';

    /* realoca vetor de reservas e adiciona */
    Reserva *tmp = realloc(reservas, sizeof(Reserva) * (totalReservas + 1));
    if (tmp == NULL) {
        printf("Erro ao alocar memória para reserva.\n");
        return;
    }
    reservas = tmp;
    reservas[totalReservas] = nova;
    totalReservas++;

    /* persistir (se existir função salvarReservas) */
    #ifdef SALVAR_RESERVAS_EXISTS
    salvarReservas(); /* se implementada em outro módulo */
    #else
    /* tente chamar salvarReservas se estiver implementada no projeto */
    #endif

    printf("Reserva criada com sucesso! ID da reserva: %d\n", nova.id);
}

/* lista todas as reservas do usuário idUsuario */
void listarReservasUsuario(int idUsuario) {
    int encontrou = 0;
    printf("Reservas do usuário (ID %d):\n", idUsuario);
    printf("ID | CuidadorID | Data       | Hora   | Duracao | Nome do cachorro     | Valor    | Status\n");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].id_usuario == idUsuario) {
            encontrou = 1;
            printf("%-3d| %-10d| %-11s| %-6s | %-7d | %-20s | R$%7.2f | %-8s\n",
                   reservas[i].id,
                   reservas[i].id_cuidador,
                   reservas[i].data,
                   reservas[i].hora,
                   reservas[i].duracao_horas,
                   reservas[i].nome_cachorro,
                   reservas[i].valor_total,
                   reservas[i].status);
        }
    }
    if (!encontrou) {
        printf("Nenhuma reserva encontrada para este usuário.\n");
    }
}

/* cancela reserva com id igual a idReserva */
void cancelarReserva(int idReserva) {
    int idx = -1;
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].id == idReserva) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("Reserva com ID %d não encontrada.\n", idReserva);
        return;
    }

    if (strcmp(reservas[idx].status, "Cancelada") == 0) {
        printf("Reserva já está cancelada.\n");
        return;
    }

    /* altera status e zera valor, se desejado */
    strncpy(reservas[idx].status, "Cancelada", MAX_STATUS-1);
    reservas[idx].status[MAX_STATUS-1] = '\0';
    /* opcional: definir valor_total = 0.0; (se o requisito exigir) */
    /* reservas[idx].valor_total = 0.0f; */

    /* persistir se houver função */
    #ifdef SALVAR_RESERVAS_EXISTS
    salvarReservas();
    #endif

    printf("Reserva %d cancelada com sucesso.\n", idReserva);
}

/* --- Fim: implementações das funções de Reservas (Pessoa 3) --- */
