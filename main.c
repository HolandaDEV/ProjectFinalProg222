#include <stdio.h>
#include <stdlib.h>
#include "project.h"
//Grupo:
//Edy Mauro Enumo RA: 233772
//Lucas Samuel Lopes RA: 240147
//Renan Douglas Sousa Holanda RA: 243782

int main(){
    int m = 0;
    //addAluno();
    // char nome[]="edy";
    // char senha[]="123";
    // printf("%d",lerString(nome,senha));
    //imprimeDisciplina(consultaDisciplina("ST765"));]]

    char usuario[100];
    char senha[100];
    char codigo[100];
    do{
        puts("Digite o usuario:");
        scanf("%s",usuario);
        puts("Digite a senha:");
        scanf("%s",senha);
        if(!lerString(usuario,senha)){
            puts("Usuario ou senha incorreto, tente novamente!");
        }
    }while(!lerString(usuario,senha));
    int n;
    while(1){
        puts("\n----Escolha a opção---");
        puts("1 - Cadastro de aluno");
        puts("2 - Consulta de disciplina");
        puts("3 - Sair!");
        scanf("%d",&n);
        switch (n)
        {
        case 1:addAluno();
            /* code */
            break;
        case 2:
            puts("Digite o código da disciplina");
            scanf("%s",codigo);
            imprimeDisciplina(consultaDisciplina(codigo));
            /* code */
            break;
        case 3:
            puts("Tchau");
            return 0;
        default:
            puts("Código inválido!");
            break;
        }
    }

    return 0;
}