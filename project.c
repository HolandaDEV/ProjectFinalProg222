#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addAluno(){
    aluno* p = (aluno*)malloc(sizeof(aluno));
    printf("digite o RA do aluno\n");
    scanf("%d",&p->RA);
    getchar();

    printf("digite o nome do aluno\n");
    scanf("%[^\n]",p->name);
    getchar();

    printf("digite o login\n");
    scanf("%[^\n]",&p->login);
    getchar();

    printf("digite a senha\n");
    scanf("%[^\n]",&p->password);
    getchar();

    FILE* alun;
    alun=fopen("Aluno.txt","a+");
    if(alun==NULL){
      printf ("erro ao abrir arquivo");
      exit(0);
    }

    //Aluno.txt RA,Nome,login,senha
    fprintf(alun,"%d,%s,%s,%s\n",p->RA,p->name,p->login,p->password);
    fclose(alun);

}

int loginAluno(char login[TAMLOGIN],char senha[TAMSENHA]){
    
    FILE* arquivo;
    arquivo = fopen("Aluno.txt","r");
    if(arquivo == NULL){
        puts("erro ao abrir arquivo");
        exit(1);
    }
    int RA;//RA
    char name[TAMNAME];//nome
    char user[TAMLOGIN];//login
    char pass[TAMSENHA];//senha
    
    // le o arquivo e ve se usuario esta cadastrado
    int x =0;
    while(!feof(arquivo)){
        fscanf(arquivo,"%d",&RA);
        fscanf(arquivo,",%[^,]s",name);
        
        fscanf(arquivo,",%[^,]s",user);

        fscanf(arquivo,",%[^\n]s",pass);

        if(!strcmp(user,login)){
            if(!strcmp(pass,senha)){
                return 1;
            }
        }
        
    }
    //printf("%d\n%s\n%s\n%s\n",RA,name,user,pass);
    return 0;
}
Disciplina * consultaDisciplina(char * cod){
    char aux;
    int i = 0;
    Disciplina * disc =(Disciplina*) malloc(sizeof(Disciplina));
    strcpy(disc->codigo, "");
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
    int i = 0;
    char aux;
    FILE * fl = fopen("Prerequisitos.txt", "r");

    char pre[10];
    while (!feof(fl)){
        fscanf(fl,"%c", &aux);
        //printf("%c", aux);
        if (aux == disc->codigo[i++])
        {
            if(disc->codigo[i] == '\0'){//Encontrou a linha de prerequisitos
                fscanf(fl,"%c", &aux);//primeira ","
                fscanf(fl,"%c", &aux);//primeiro caractere
                i = 0;
                while (aux != '\n')
                {
                    if(aux == 32 || aux == '*' || aux == '/'){
                        pre[i] = '\0';
                        if(pre[0] != '\0'){
                            Disciplina * d = consultaDisciplina(pre);
                            printf("(%s)",pre);
                            if(d->nome[0] != '\0'){
                                printf(" - %s",d->nome);
                            }
                        }
                        i = 0;
                        printf("%c", aux);
                    }else
                    {
                        pre[i++]=aux;
                    }
                    fscanf(fl,"%c", &aux);
                    
                }
                pre[i] = '\0';
                Disciplina * d = consultaDisciplina(pre);
                printf("(%s)",pre);
                if(d->nome[0] != '\0'){
                    printf(" - %s",d->nome);
                }
               
            }
        }else
        {
            i = 0;
        }
    }
    
    fclose(fl);
}
void realizarMatricular(int status){
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
    char codDisc[5];
    char codExit[5] = "XX000";
    int qtdeCred = 0;
    FILE * fl = fopen("AlunosDisciplinas.txt", "w");
    //code:

    if (status == 1)
    {
        while (qtdeCred <= MAX_CRED)
        {
            while (strcmp(codExit, codDisc) == 1)
            {
                scanf("%s", codDisc);
            }
            
        }
        puts("ERROR 0001 - Quantidade de créditos maximos excedida");
        exit(1);
    }
    
}