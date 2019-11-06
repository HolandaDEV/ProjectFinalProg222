#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addAluno(){
    aluno* p = (aluno*)malloc(sizeof(aluno));
    printf("digite o RA do aluno\n");
    int RA;
    scanf("%d",&RA);
    getchar();

//digita o name do aluno
    printf("digite o nome do aluno\n");
    char name [TAMNAME];
    scanf("%[^\n]",name);
    getchar();

//digita o login do aluno
    printf("digite o login\n");
    char login[TAMLOGIN];
    scanf("%[^\n]",login);
    getchar();

//difgita a senha do aluno 
    printf("digite a senha\n");
    char password[TAMSENHA];
    scanf("%[^\n]",password);
    getchar();

  //cria ou abre o arquvo que cadastra os alunos
    FILE* alun;
    alun=fopen("Aluno.txt","a+");
    if(alun==NULL){
      printf ("erro ao abrir arquivo");
      exit(0);
    }


  // escreve o os dados do aluno no arquivo 
  //Aluno.txt RA,Nome,login,senha
    fprintf(alun,"%d,%s,%s,%s\n",RA,name,login,password);
    fclose(alun);

}

int lerString(char login[TAMLOGIN],char senha[TAMSENHA]){
    
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