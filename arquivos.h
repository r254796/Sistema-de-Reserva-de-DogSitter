#ifndef ARQUIVOS_H
#define ARQUIVOS_H

int verificaIndiceCuidador(int idCuidadorBuscado);
int buscarCuidadorPorData(int idCuidadorBuscado, char dataBuscada[], char horaBuscada[], int duracaoBuscada);
void exibirMenuBuscarCuidadorPorData();
void receberInformacoesDeBusca(char dataBuscada[], char horaBuscada[], int *duracaoBuscada);
void exibirMenuDetalhesCuidador();

int horaParaMinutos(char horario[]);
int validarData(char data[]);
int validarHorario(char horario[]);
void limparTela();
void retornarMenu();

int fazerLogin(); //não implementada
void exibirMenuPrincipal();
void listarCuidadores();

void carregarUsuarios(); //não implementada
void carregarCuidadores();
void carregarReservas();
void inicializarDados(); 


void salvarUsuarios(); 
void salvarCuidadores();
void salvarReservas();
void liberarMemoria(); 


void exibirMenuRelatorios();
void relatorioFaturamento(); //não implementada
void relatorioReservas();    
void historicoReservas(); //não implementada


void novaReserva(int idUsuario);
void listarReservasUsuario(int idUsuario);
void cancelarReserva();

#endif 



