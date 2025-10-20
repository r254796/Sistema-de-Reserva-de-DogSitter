#ifndef ARQUIVOS_H
#define ARQUIVOS_H

void limparTela();
int retornarMenu();

int fazerLogin(); //não implementada
void exibirMenuPrincipal();
void listarCuidadores();

void carregarUsuarios(); //não implementada
void carregarCuidadores();
void carregarReservas();
void inicializarDados(); 


void salvarUsuarios(); //não implementada
void salvarCuidadores(); //não implementada
void salvarReservas();
void liberarMemoria(); 


void exibirMenuRelatorios();
void relatorioFaturamento(); //não implementada
void relatorioReservas();    
void historicoReservas(); //não implementada


#endif 

