#ifndef PROJECT_H
#define PROJECT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_NOME 30
#define TAM_SENHA 20
#define TAM_LOGIN 20
#define MAX_CRED 32

typedef struct Aluno
{
    int RA;
    char name[TAM_NOME];
    char login[TAM_LOGIN];
    char passaword[TAM_SENHA];
} Aluno;
typedef struct Disciplina Disciplina;

typedef struct Prerequisito
{
    int qtd;
    Disciplina *disciplina[3];
} Prerequisito;

typedef struct Disciplina
{
    char codigo[10];
    char nome[1000];
    int creditos;
    int qtdPrerequisito;
    Prerequisito prerequisto[3];
} Disciplina;

typedef struct Matricula
{
    int ra;
    int semestre;
    char codigo[10];
    float nota;
    float falta;
} Matricula;

void addAluno();
Aluno *loginAluno(char *login, char *senha);
void atribuiPrerequisito(Disciplina *disciplina);
Disciplina *consultaDisciplina(char *cod);
void imprimeDisciplina(Disciplina *disc);
void cadastrarDisciplina(Aluno *aluno);
void atualizarNotaFalta(Aluno *aluno);

#endif