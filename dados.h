#ifndef DADOS_H
#define DADOS_H

#define MAX_NOME 100
#define MAX_EMAIL 100
#define MAX_SENHA 50
#define MAX_TEL 20
#define MAX_PORTE 50
#define MAX_DATA 20
#define MAX_STATUS 20 

typedef struct Usuario {
    int id;
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char senha[MAX_SENHA];
    char telefone[MAX_TEL];
} Usuario;

typedef struct Cuidador {
    int id;
    char nome[MAX_NOME];
    float valor_hora;
    char porte_aceito[MAX_PORTE]; 
} Cuidador;

typedef struct Reserva {
    int id;
    int id_usuario;
    int id_cuidador;
    char data_hora_inicio[MAX_DATA]; 
    int duracao_horas;
    char nome_cachorro[MAX_NOME];
    float valor_total; 
    char status[MAX_STATUS]; [cite_start]// "Ativa" ou "Cancelada" [cite: 92, 93, 319, 320]
} Reserva;

extern Usuario* usuarios;
extern int totalUsuarios;

extern Cuidador* cuidadores;
extern int totalCuidadores;

extern Reserva* reservas;
extern int totalReservas;

#endif 