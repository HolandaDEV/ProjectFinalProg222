#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addAluno(){
    Aluno* p = (Aluno*)malloc(sizeof(Aluno));
    printf("digite o RA do aluno\n");
    int RA;
    scanf("%d",&RA);
    getchar();

    printf("digite o nome do aluno\n");
    char name [TAM_NOME];
    scanf("%[^\n]",name);
    getchar();

    printf("digite o login\n");
    char login[TAM_LOGIN];
    scanf("%[^\n]",login);
    getchar();

    printf("digite a senha\n");
    char password[TAM_SENHA];
    scanf("%[^\n]",password);
    getchar();


    FILE* alun;
    alun=fopen("Aluno.txt","a+");
    if(alun==NULL){
      printf ("erro ao abrir arquivo");
      exit(0);
    }


  //Aluno.txt RA,Nome,login,senha
    fprintf(alun,"%d,%s,%s,%s\n",RA,name,login,password);
    fclose(alun);

}

Aluno* loginAluno(char* login,char* senha){
    Aluno* aluno= (Aluno*) malloc(sizeof(Aluno));
      aluno->RA=0;


    FILE* arquivo;
    arquivo = fopen("Aluno.txt","r");
    if(arquivo == NULL){
        puts("erro ao abrir arquivo");
        exit(1);
    }
    int RA;//RA
    char name[TAM_NOME];//nome
    char user[TAM_LOGIN];//login
    char pass[TAM_SENHA];//senha
    
    // le o arquivo e ve se usuario esta cadastrado
    int x =0;
    while(!feof(arquivo)){
        fscanf(arquivo,"%d",&RA);
        fscanf(arquivo,",%[^,]s",name);
        
        fscanf(arquivo,",%[^,]s",user);

        fscanf(arquivo,",%[^\n]s",pass);

        if(!strcmp(user,login)){
            if(!strcmp(pass,senha)){
                aluno->RA=RA;
                strcpy(aluno->name,name);
                strcpy(aluno->login,user);
                strcpy(aluno->passaword,pass);
                return aluno;
            }
        }
        
    }
    //printf("%d\n%s\n%s\n%s\n",RA,name,user,pass);
    return aluno;
}
void atribuiPrerequisito(Disciplina* disciplina){
    disciplina->qtdPrerequisito = 0;
    for(int i = 0; i < 3; i++){
        disciplina->prerequisto[i].qtd=0;
    }
    int i = 0;
    char aux;
    FILE * fl = fopen("Prerequisitos.txt", "r");

    char pre[10];
    while (!feof(fl)){
        fscanf(fl,"%c", &aux);
        //printf("%c", aux);
        if (aux == disciplina->codigo[i++])
        {
            if(disciplina->codigo[i] == '\0'){//Encontrou a linha de prerequisitos
                fscanf(fl,"%c", &aux);//primeira ","
                fscanf(fl,"%c", &aux);//primeiro caractere
                if(aux == 'n'){
                    break;
                }
                i = 0;
                while (aux != '\n')
                {
                    if(aux == 32 || aux == '/'){//aqui encontrou o pre requisto que vem antes de espaço ou /
                    //atribui a disciplina ao pre requisito
                        pre[i] = '\0';
                        Disciplina * d = consultaDisciplina(pre);
                        Prerequisito* p = &(disciplina->prerequisto[disciplina->qtdPrerequisito]);
                        p->disciplina[p->qtd++] = d;
                        i = 0;
                    }else
                    {
                        pre[i++]=aux;
                    }
                    if(aux == '/'){
                        //incrementa o numero de pre requisito se encontrar / ou \n
                        disciplina->qtdPrerequisito++;
                    }
                    fscanf(fl,"%c", &aux);
                }
                pre[i] = '\0';
                Disciplina * d = consultaDisciplina(pre);
                Prerequisito* p = &(disciplina->prerequisto[disciplina->qtdPrerequisito]);
                p->disciplina[p->qtd++] = d;
                disciplina->qtdPrerequisito++;
            }
        }else
        {
            i = 0;
        }
    }
    
    fclose(fl);
    
    
}
Disciplina * consultaDisciplina(char * cod){
    char aux;
    int i = 0;
    Disciplina * disc =(Disciplina*) malloc(sizeof(Disciplina));
    strcpy(disc->codigo, cod);
    strcpy(disc->nome, "");
    disc->creditos = 0;
    
    FILE * sub = fopen("Disciplinas.txt", "r");

    while (!feof(sub)){
        fscanf(sub,"%c", &aux);
        if (aux == cod[i++])
        {
            if(cod[i] == '\0'){
                strcpy(disc->codigo, cod);
                fscanf(sub,",%[^,]s",disc->nome);
                fscanf(sub,",%d",&disc->creditos);
                fclose(sub);
                return disc;
            }
        }else
        {
            i = 0;
        }
    }
    
    fclose(sub);
    return disc;
}
void imprimeDisciplina(Disciplina * disc){
    printf("Nome: %s\n", disc->nome);
    printf("Quantidade de Créditos: %d\n", disc->creditos);
    printf("Pré-requisitos:");
    for(int i=0; i<disc->qtdPrerequisito;i++){
        if(i>0){
            printf("/");
        }
        for(int j=0;j<disc->prerequisto[i].qtd;j++){
            if(j>0){
                printf(" ");
            }
            printf("(%s)",disc->prerequisto[i].disciplina[j]->codigo);
            if(disc->prerequisto[i].disciplina[j]->nome[0]!='\0'){
                printf("->[%s]",disc->prerequisto[i].disciplina[j]->nome);
            }
        }
    }
}
// int validarDisciplina(Disciplina* disciplina,Aluno* aluno){
//     FILE* 
// }


void cadastrarDisciplina(Aluno* aluno){

    // printf("Tela de Realizar Matrícula \n");
    // printf("Para sair, digite XX000\n");
    // printf("Digite o semestre: ");
    // printf("Digite a disciplina: ");
        /* Anotações:
     * <> Fazer a busca da Disciplina pelo arquivo (consultaDisciplina). 
     * <> Somente será possível cadastrar uma disciplina se, e somente se, o aluno já tiver cursado os pré-requisitos e
     *    tiver obtido, no mínimo, conceito igual a 5 e faltas menor que 25%.
     * <> Caso não exista a disciplina no momento do cadastro, o sistema deve informar de imediato que a disciplina não
     *    existe, mas não apagar as outras que já foram digitadas.
     * <> Não é permitido inserir um semestre que seja anterior ao semestre mais atual do aluno, caso isso ocorra,
     *    o sistema deverá informar de imediato o erro e pedir um novo semestre.
     */
    
    //variaveis
    int semestreAtual = 1;
    int semestre = 0;
    int qtdeCred = 0;
    Disciplina * disc =(Disciplina*) malloc(sizeof(Disciplina));
    FILE * fl = fopen("AlunosDisciplinas.txt", "wXX))");
    //code:

    if (aluno->RA != 0)
    {   
        while (1)
        {         
            puts("Digite o semestre:");
            scanf("%d", &semestre);
            getchar();
            
            if (!(semestre < semestreAtual))
            {
                while (qtdeCred <= MAX_CRED)
                {
                        puts("Digite o a disciplina:");
                        scanf("%s", disc->codigo);
                        getchar();
                        //printf("%d\n", strcmp(disc->codigo, "XX000"));
                        if (strcmp(disc->codigo, "XX000") != 0)
                        {   int creditoDisciplina ;
                            creditoDisciplina = consultaDisciplina(disc->codigo)->creditos;

                            if(creditoDisciplina !=0 )
                            {   if((qtdeCred+creditoDisciplina) == MAX_CRED){
                                qtdeCred += creditoDisciplina;
                                    printf("%d\n",qtdeCred);
                                    break;
                                }else if((qtdeCred + creditoDisciplina) < MAX_CRED){
                                    qtdeCred += creditoDisciplina;
                                    printf("%d\n",qtdeCred);
                                }
                            }else
                            {
                                printf("Materia nao existe\n");
                            }
                            fprintf(fl, "%s,", disc->codigo);
                            *(disc->codigo) = 0;
                        }else
                        {
                            break;
                        }
                }
                if (qtdeCred > MAX_CRED)
                {
                    puts("ERROR 0001 - Quantidade de créditos maximos excedida");
                }
                break;
            }else
            {
                puts("Semestre Inválido, insira novamente!");
            }
        }
    }

}
