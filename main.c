#include <stdio.h>
#include <stdlib.h>
#include "dados.h" 
#include "arquivos.h" 
#include "funcoes.h"

Usuario* usuarios = NULL;
int totalUsuarios = 0;

Cuidador* cuidadores = NULL;
int totalCuidadores = 0;

Reserva* reservas = NULL;
int totalReservas = 0;

int usuarioLogadoID = -1; 


int main() {
    int opcao;

    inicializarDados();

    do{
        printf("=============================================\n");
        printf("      BEM-VINDO AO SISTEMA DE DOGSITTER\n");
        printf("=============================================\n");
        printf("1 - Cadastrar-se\n");
        printf("2 - Fazer login\n");
        printf("0 - Sair\n");
        printf("=============================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

            switch (opcao) {
                case 1: 
                    printf("Modulo de Cadastro (Pessoa 1) nao implementado.\n");
                    break;
                case 2: 
                    usuarioLogadoID = 1; 
                    if (usuarioLogadoID != -1) {
                        limparTela();
                        exibirMenuPrincipal(); 
                    }
                    opcao = 0;
                    break;
                case 0:
                    printf("\nSaindo do sistema... Ate logo!\n");
                    //salvarUsuarios(); //não implementado
                    //salvarCuidadores(); //não implementado
                    salvarReservas();
                    liberarMemoria();
                    break;
                default:
                    printf("OPÇÃO INVÁLIDA. TENTE NOVAMENTE.\n");
            }
    } while(opcao != 0);

    return 0;
}
