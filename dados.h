#ifndef DADOS_H
#define DADOS_H

#define MAX_NOME 25
#define MAX_EMAIL 100
#define MAX_SENHA 50
#define MAX_TEL 20
#define MAX_PORTE 20
#define MAX_EXPEDIENTE 50
#define MAX_DATA 12
#define MAX_HORA 12
#define MAX_EXPERIENCIA 50
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
    char dias_expediente[MAX_EXPEDIENTE];
    char hora_inicio_expediente[MAX_HORA];
    char hora_fim_expediente[MAX_HORA];
    char experiencia[MAX_EXPERIENCIA];
} Cuidador;

typedef struct Reserva {
    int id;
    int id_usuario;
    int id_cuidador;
    char data[MAX_DATA];
    char hora[MAX_HORA];
    int duracao_horas;
    char nome_cachorro[MAX_NOME];
    float valor_total; 
    char status[MAX_STATUS];
} Reserva;

extern Usuario* usuarios;
extern int totalUsuarios;

extern Cuidador* cuidadores;
extern int totalCuidadores;

extern Reserva* reservas;
extern int totalReservas;


#endif 
