#include <stdio.h>
#include <stdlib.h>
#include "dados.h" 
#include "arquivos.h" 

Usuario* usuarios = NULL;
int totalUsuarios = 0;

Cuidador* cuidadores = NULL;
int totalCuidadores = 0;

Reserva* reservas = NULL;
int totalReservas = 0;

int usuarioLogadoID = -1; 

int fazerLogin(); 
void menuPrincipalUsuario(); 

int main() {
    int opcao;

    inicializarDados(); 

    do {
        [cite_start]
        printf("\n=============================================\n");
        printf("BEM-VINDO AO SISTEMA DE DOGSITTER\n");
        printf("=============================================\n");
        printf("1 - Cadastrar-se\n");
        printf("2 - Fazer login\n");
        printf("0 - Sair\n");
        printf("=============================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                printf("Modulo de Cadastro (Pessoa 1) nao implementado.\n");
                break;
            case 2: 
                usuarioLogadoID = 1; 
                if (usuarioLogadoID != -1) {
                    menuPrincipalUsuario(); 
                }
                break;
            case 0:
                printf("\nSaindo do sistema... Ate logo!\n"); [cite_start]
                salvarUsuarios();
                salvarCuidadores();
                salvarReservas();
                liberarMemoria();
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}