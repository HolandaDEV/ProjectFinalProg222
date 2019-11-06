#ifndef PROJECT_H
#define PROJECT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMNAME 30
#define TAMSENHA 20
#define TAMLOGIN 20
#define MAX_CRED 32

typedef struct aluno
{
    int RA;
    char name[20];
    char login[10];
    char password[10];
}aluno;

typedef struct alunos
{
    aluno *lista[100];
    int top;

}alunos;

typedef struct Disciplinas
{
    char codigo[10];
    char nome[1000];
    int creditos;

}Disciplina;


void addAluno();
int loginAluno(char Login[TAMLOGIN],char Senha[TAMSENHA]);
Disciplina * consultaDisciplina(char* cod);
void imprimeDisciplina(Disciplina * disc);
void realizarMatricular(int status);

#endif 