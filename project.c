#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addAluno()
{
    Aluno *p = (Aluno *)malloc(sizeof(Aluno));
    printf("digite o RA do aluno\n");
    int RA;
    scanf("%d", &RA);
    getchar();

    printf("digite o nome do aluno\n");
    char name[TAM_NOME];
    scanf("%[^\n]", name);
    getchar();

    printf("digite o login\n");
    char login[TAM_LOGIN];
    scanf("%[^\n]", login);
    getchar();

    printf("digite a senha\n");
    char password[TAM_SENHA];
    scanf("%[^\n]", password);
    getchar();

    FILE *alun;
    alun = fopen("Aluno.txt", "a+");
    if (alun == NULL)
    {
        printf("erro ao abrir arquivo");
        exit(0);
    }

    //Aluno.txt RA,Nome,login,senha
    fprintf(alun, "%d,%s,%s,%s\n", RA, name, login, password);
    fclose(alun);
}

Aluno *loginAluno(char *login, char *senha)
{
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));
    aluno->RA = 0;

    FILE *arquivo;
    arquivo = fopen("Aluno.txt", "r");
    if (arquivo == NULL)
    {
        puts("erro ao abrir arquivo");
        exit(1);
    }
    int RA;               //RA
    char name[TAM_NOME];  //nome
    char user[TAM_LOGIN]; //login
    char pass[TAM_SENHA]; //senha

    // le o arquivo e ve se usuario esta cadastrado
    int x = 0;
    while (!feof(arquivo))
    {
        fscanf(arquivo, "%d", &RA);
        fscanf(arquivo, ",%[^,]s", name);

        fscanf(arquivo, ",%[^,]s", user);

        fscanf(arquivo, ",%[^\n]s", pass);

        if (!strcmp(user, login))
        {
            if (!strcmp(pass, senha))
            {
                aluno->RA = RA;
                strcpy(aluno->name, name);
                strcpy(aluno->login, user);
                strcpy(aluno->passaword, pass);
                return aluno;
            }
        }
    }
    //printf("%d\n%s\n%s\n%s\n",RA,name,user,pass);
    return aluno;
}
void atribuiPrerequisito(Disciplina *disciplina)
{
    disciplina->qtdPrerequisito = 0;
    for (int i = 0; i < 3; i++)
    {
        disciplina->prerequisto[i].qtd = 0;
    }
    int i = 0;
    char aux;
    FILE *fl = fopen("Prerequisitos.txt", "r");

    char pre[10];
    while (!feof(fl))
    {
        fscanf(fl, "%c", &aux);
        //printf("%c", aux);
        if (aux == disciplina->codigo[i++])
        {
            if (disciplina->codigo[i] == '\0')
            {                           //Encontrou a linha de prerequisitos
                fscanf(fl, "%c", &aux); //primeira ","
                fscanf(fl, "%c", &aux); //primeiro caractere
                if (aux == 'n')
                {
                    break;
                }
                i = 0;
                while (aux != '\n')
                {
                    if (aux == 32 || aux == '/')
                    { //aqui encontrou o pre requisto que vem antes de espaço ou /
                        //atribui a disciplina ao pre requisito
                        pre[i] = '\0';
                        Disciplina *d = consultaDisciplina(pre);
                        Prerequisito *p = &(disciplina->prerequisto[disciplina->qtdPrerequisito]);
                        p->disciplina[p->qtd++] = d;
                        i = 0;
                    }
                    else
                    {
                        pre[i++] = aux;
                    }
                    if (aux == '/')
                    {
                        //incrementa o numero de pre requisito se encontrar / ou \n
                        disciplina->qtdPrerequisito++;
                    }
                    fscanf(fl, "%c", &aux);
                }
                pre[i] = '\0';
                Disciplina *d = consultaDisciplina(pre);
                Prerequisito *p = &(disciplina->prerequisto[disciplina->qtdPrerequisito]);
                p->disciplina[p->qtd++] = d;
                disciplina->qtdPrerequisito++;
            }
        }
        else
        {
            i = 0;
        }
    }

    fclose(fl);
}
Disciplina *consultaDisciplina(char *cod)
{
    char aux;
    int i = 0;
    Disciplina *disc = (Disciplina *)malloc(sizeof(Disciplina));
    strcpy(disc->codigo, cod);
    strcpy(disc->nome, "");
    disc->creditos = 0;

    FILE *sub = fopen("Disciplinas.txt", "r");

    while (!feof(sub))
    {
        fscanf(sub, "%c", &aux);
        if (aux == cod[i++])
        {
            if (cod[i] == '\0')
            {
                strcpy(disc->codigo, cod);
                fscanf(sub, ",%[^,]s", disc->nome);
                fscanf(sub, ",%d", &disc->creditos);
                fclose(sub);
                return disc;
            }
        }
        else
        {
            i = 0;
        }
    }

    fclose(sub);
    return disc;
}
void imprimeDisciplina(Disciplina *disc)
{
    printf("Nome: %s\n", disc->nome);
    printf("Quantidade de Créditos: %d\n", disc->creditos);
    printf("Pré-requisitos:");
    for (int i = 0; i < disc->qtdPrerequisito; i++)
    {
        if (i > 0)
        {
            printf("/");
        }
        for (int j = 0; j < disc->prerequisto[i].qtd; j++)
        {
            if (j > 0)
            {
                printf(" ");
            }
            printf("(%s)", disc->prerequisto[i].disciplina[j]->codigo);
            if (disc->prerequisto[i].disciplina[j]->nome[0] != '\0')
            {
                printf("->[%s]", disc->prerequisto[i].disciplina[j]->nome);
            }
        }
    }
}
// int validarDisciplina(Disciplina* disciplina,Aluno* aluno){
//     FILE*
// }

int verificaSemestre(Aluno *a, int s)
{
    FILE *fl = fopen("AlunosDisciplinas.txt", "r");
    int ra, semestre;
    char codigo[10];
    float nota, faltas;
    int aux = 0;
    while (!feof(fl))
    {
        fscanf(fl, "%d", &ra);
        fscanf(fl, ",%[^,]s", codigo);
        fscanf(fl, ",%d", &semestre);
        fscanf(fl, ",%f", &nota);
        fscanf(fl, ",%f\n", &faltas);
        if (ra == a->RA)
        {
            if (semestre > aux)
            {
                aux = semestre;
            }
        }
    }
    fclose(fl);
    return s >= semestre;
}

int getSemestre(Aluno *aluno)
{
    int semestre;
    int aux;
    do
    {
        puts("Digite o semestre:");
        scanf("%d", &semestre);
        getchar();
        aux = verificaSemestre(aluno, semestre);
        if (!aux)
        {
            puts("Semestre invalido! Tente novamente");
        }
    } while (!aux);
    return semestre;
}

int verificaDisciplinaAprovacao(Disciplina *d, Aluno *a)
{
    FILE *fl = fopen("AlunosDisciplinas.txt", "r");
    int ra, semestre;
    char codigo[10];
    float nota, faltas;
    while (!feof(fl))
    {
        fscanf(fl, "%d", &ra);
        fscanf(fl, ",%[^,]s", codigo);
        fscanf(fl, ",%d", &semestre);
        fscanf(fl, ",%f", &nota);
        fscanf(fl, ",%f\n", &faltas);
        if (ra == a->RA && !strcmp(codigo, d->codigo) && nota >= 5 && faltas <= 25)
        {
            fclose(fl);
            return 0;
        }
    }
    fclose(fl);
    return 1;
}
int verificaPreRequisito(Disciplina *d, Aluno *a)
{
    if (d->qtdPrerequisito == 0)
    {
        return 1;
    }
    int continua;
    for (int i = 0; i < d->qtdPrerequisito; i++)
    {
        continua = 0;
        for (int j = 0; j < d->prerequisto[i].qtd; j++)
        {
            continua += verificaDisciplinaAprovacao(d->prerequisto[i].disciplina[j], a);
        }
        if (continua == 0)
        {
            return 1;
        }
    }
    return 0;
}
void salvarDisciplinas(Disciplina **listaDisciplina, int qtdDisc, Aluno *a, int semestre)
{
    FILE *fl = fopen("AlunosDisciplinas.txt", "a");
    for (int i = 0; i < qtdDisc; i++)
    {
        fprintf(fl, "%d,%s,%d,0,0\n", a->RA, listaDisciplina[i]->codigo, semestre);
    }
    fclose(fl);
}

Disciplina *getDisciplina()
{
    while (1)
    {
        Disciplina *disc;
        char codigo[10];
        printf("Digite o a disciplina:");
        scanf("%s", codigo);
        getchar();
        if (!strcmp(codigo, "XX000"))
        {
            disc = (Disciplina *)malloc(sizeof(Disciplina));
            strcpy(disc->codigo, codigo);
            return disc;
        }
        disc = consultaDisciplina(codigo);
        if (disc->creditos == 0)
        {
            puts("Disciplina inválida");
        }
        else
        {
            return disc;
        }
    }
}

void cadastrarDisciplina(Aluno *aluno)
{
    //variaveis
    int semestreAtual = 1;
    int semestre = 0;
    int qtdeCred = 0;
    int qtdDisc = 0;
    Disciplina *disc;
    Disciplina **listaDisciplina = (Disciplina **)malloc(20 * sizeof(Disciplina *));
    //code:
    if (aluno->RA != 0)
    {
        puts("Tela de Realizar Matrícula");
        puts("Para sair, digite XX000");
        semestre = getSemestre(aluno);
        while (qtdeCred <= MAX_CRED)
        { //cadastrar as disciplinas

            disc = getDisciplina();
            if (!strcmp(disc->codigo, "XX000"))
            {
                break;
            }

            atribuiPrerequisito(disc);
            if (verificaPreRequisito(disc, aluno))
            {
                listaDisciplina[qtdDisc++] = disc;
                qtdeCred += disc->creditos;
            }
            else
            {
                puts("O Aluno nao possui os pre-requisitos necessarios para cursar esta disciplina");
            }
        }

        if (qtdeCred <= MAX_CRED)
        { //salvar as disciplinas
            salvarDisciplinas(listaDisciplina, qtdDisc, aluno, semestre);
        }
        else
        {
            puts("ERROR 0001 - Quantidade de créditos maximos excedida");
        }
    }
}

void imprimeDisciplinasSemestre(int s, Aluno *a)
{
    FILE *fl = fopen("AlunosDisciplinas.txt", "r");
    int ra, semestre;
    char codigo[10];
    float nota, faltas;
    while (!feof(fl))
    {
        fscanf(fl, "%d", &ra);
        fscanf(fl, ",%[^,]s", codigo);
        fscanf(fl, ",%d", &semestre);
        fscanf(fl, ",%f", &nota);
        fscanf(fl, ",%f\n", &faltas);
        if (semestre == s)
        {
            printf("%s - %s - Nota: %.1f , Falta: %.1f (%%)\n", codigo, consultaDisciplina(codigo)->nome, nota, faltas);
        }
    }
    fclose(fl);
}

void editarDisciplina(int s, Aluno *a)
{
    while (1)
    {
        printf("Digite o código da disciplina que deseja fazer a alteração:");
        Disciplina *disc = getDisciplina();
        if (!strcmp(disc->codigo, "XX000"))
        {
            return;
        }
    }
}
Matricula **carregaMatriculas()
{
    Matricula **m = (Matricula **)malloc(sizeof(Matricula *) * 10000);
    FILE *fl = fopen("AlunosDisciplinas.txt", "r");
    int top = 0;
    int ra, semestre;
    char codigo[10];
    float nota, faltas;
    while (!feof(fl))
    {
        m[top] = (Matricula*)malloc(sizeof(Matricula));
        fscanf(fl, "%d", &m[top]->ra);
        fscanf(fl, ",%[^,]s", m[top]->codigo);
        fscanf(fl, ",%d", &m[top]->semestre);
        fscanf(fl, ",%f", &m[top]->nota);
        fscanf(fl, ",%f\n", &m[top]->falta);
        top++;
    }
    fclose(fl);
    return m;
}



void atualizarNotaFalta(Aluno *aluno)
{
    int semestre;
    printf("Digite o semestre: ");
    scanf("%d", &semestre);
    getchar();
    Matricula **matriculas = carregaMatriculas();
    for(int i=0;i<10000;i++){
        printf("%s - %s - Nota: %.1f , Falta: %.1f (%%)\n", matriculas[i]->codigo, consultaDisciplina(matriculas[i]->codigo)->nome, matriculas[i]->nota, matriculas[i]->falta);
    }

    ////imprimeDisciplinasSemestre(semestre, aluno);
    //editarDisciplina(semestre, aluno);
}
