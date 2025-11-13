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
    limparTela();
    fazerLogin();
    exibirMenuPrincipal();

    return 0;
}
