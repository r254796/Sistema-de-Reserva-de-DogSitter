#ifndef ARQUIVOS_H
#define ARQUIVOS_H

void carregarUsuarios();
void carregarCuidadores();
void carregarReservas();
void inicializarDados(); 

[cite_start]// Funções de Salvamento (chamadas no FINAL do main.c, Opção 0 [cite: 36, 128-131, 261, 364-366])
void salvarUsuarios();
void salvarCuidadores();
void salvarReservas();
void liberarMemoria(); 

[cite_start]
void menuRelatorios();
void relatorioFaturamento(); [cite_start]
void relatorioReservas();    [cite_start]
void historicoReservas();    [cite_start]


#endif 
