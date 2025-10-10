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

[cite_start]// Funções de Relatórios (Opção 7 do Menu Principal [cite: 100, 271, 329])
void menuRelatorios();
void relatorioFaturamento(); [cite_start]// Faturamento total por cuidador [cite: 105, 117, 266, 348]
void relatorioReservas();    [cite_start]// Total de reservas ativas e canceladas [cite: 106, 122, 261, 354]
void historicoReservas();    [cite_start]// Histórico de todas as reservas [cite: 107, 125, 357, 358]

#endif // ARQUIVOS_H