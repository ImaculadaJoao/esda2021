#include <stdio.h>
#include <stdbool.h>
// #include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>


struct players{
    char nome[40], apelido[20], equipe[50];
    int idade,nrGolos;
}player;

struct teams{
    char nome[25];
    int titulos, desde;
}team;

bool ano(int entrada);
bool vnome(char entrada[60]);
bool vidade(int entrada);
bool v_golos_jogos(int entrada);

char* validacaoEliminarJogador(char nome[50]);
bool validacaoCadastroJogador(char nome[50], char apelido[50], char equipe[50]);
bool validacaoCadastroEquipe(char nome[50]);
int numero_de_Equipes();
int numero_de_Jogadores();
void carregar_jogador(void);
void carregar_equipe(void);
void pesquisarJogador(void);
void pesquisarEquipe(void);
void adicionar_jogador(void);
void adicionar_equipe(void);
void apagarJogador(void);
void menu_principal(void);

void menu_principal(void){
    bool aberto = true;
    int opcao;
    printf("<><><><><><><><><><><><><><><><> MENU PRINCIPAL <><><><><><><><><><><><><><><><>\n");

    Menu:
    while(aberto){
        printf("1. Adicionar Equipe\n2. Imprimir Equipes\n3. Adicionar Jogador\n4. Imprimir Jogadores\n5. Apagar Jogador\n");
        scanf("%i", &opcao);

        if(opcao > 0 && opcao < 6){
            aberto = !aberto;
        }else{
            system("cls");
            printf("Entrada Invalida! Por favor, Digite uma Valida!\n");
            goto Menu;
        }

        system("cls");
        switch(opcao){
            case 1:{
                adicionar_equipe();
                break;
            }

            case 2:{
                carregar_equipe();
                break;
            }

            case 3:{
                adicionar_jogador();
                break;
            }

            case 4:{
                carregar_jogador();
                break;
            }

            case 5:{
                apagarJogador();
                break;
            }
    }
}
}


int main(){
    system("title Primeira Tarefa");
    int numero = numero_de_Jogadores();
    //adicionar_jogador();
    //adicionar_equipe();
    //apagarJogador();
    menu_principal();
    //carregar_jogador();
    //printf("O numero total de Jogadores e: %i ", numero);
    //carregar_equipe();

    return 0;
}

/**Validacao do ano*/
bool ano(int entrada){
        if(entrada>1800 && entrada<2022){return true;}
        else return false;
}

/**Validacao do nome*/
bool vnome(char entrada[60]){
    bool retorno=true;

    for(int i=0; i<strlen(entrada); i++){
        if(entrada[i]==' '){
            continue;
        }
        if(isalpha(entrada[i])==0){
            retorno=false;
        }
    }
    return retorno;
}

/**Validacao da Idade*/
bool vidade(int entrada){
    if(entrada>15 && entrada<45){
        return true;
    }else{
        return false;
    }
}

/**Validacao do numero de golos*/
bool v_golos_jogos(int entrada){
    if(entrada>=0){return true;}
        else return false;
}

/**Achar numero de elementos que existem no ficheiro de Equipes*/
int numero_de_Equipes(){
    FILE *ficheiro;
    int quantidade=0;

    ficheiro=fopen("Equipes.txt","rb");

    if(ficheiro == NULL){
        printf("ERROR 404 ao abrir o ficheiro para contagem de Equipes!!!");
        exit(1);
    }

    while(fread(&team, sizeof(team),1, ficheiro)){
        quantidade++;
    }
    return quantidade;

     fclose(ficheiro);
}

/**Achar numero de elementos que existem no ficheiro de Jogadores*/
int numero_de_Jogadores(){
    FILE *ficheiro;
    int quantidade=0;

    ficheiro=fopen("Jogadores.txt", "rb");

    if(ficheiro == NULL){
        printf("ERROR 404 ao abrir o ficheiro para contagem de Jogadores!!!");
        exit(1);
    }

    while(fread(&player, sizeof(player),1, ficheiro)){
        quantidade++;
    }
    return quantidade;

     fclose(ficheiro);
}

/**Adicionar Jogador*/
void adicionar_jogador(void){
     bool aberto = true;

        FILE *ficheiro;
        ficheiro=fopen("Jogadores.txt","ab");

        if(ficheiro == NULL){
            printf("ERROR 404 ao tentar abrir o ficheiro para Cadastro do Jogador!!!");
            exit(1);
        }

        int idade, i=0, equipe,golos=0;
        char nome[50], apelido[50];
        struct players player;

        //Entrada do nome
        do{
            printf("Nome do Jogador: ");
            scanf("%s", &nome);
            setbuf(stdin, NULL);
            system("cls");
            if(vnome(nome) == false){
                printf("Nome Invalido! Por favor, Digite um nome Valido!\n");
            }
        }while(vnome(nome) == false);

        //Entrada de Apelido
        do{
            printf("Apelido do Jogador: ");
            scanf("%s", &apelido);
            setbuf(stdin, NULL);
            system("cls");
            if(vnome(apelido) == false){
                printf("Apelido Invalido! Por favor, Digite um Apelido Valido!\n");
            }
        }while(vnome(apelido) == false);

        //Entrada do ano de Inicio
        do{
            printf("Idade do Jogador: ");
            scanf("%i", &idade);
            setbuf(stdin, NULL);
            system("cls");
            if(vidade(idade) == false){
                printf("Entrada Invalida! Certifique-se e Volte a tentar\n");
            }
        }while(vidade(idade) == false);

        do{
            printf("Numero de Golos do Jogador: ");
            scanf("%i", &golos);
            setbuf(stdin, NULL);
            system("cls");
            if(v_golos_jogos(golos) == false){
                printf("Entrada Invalida! Certifique-se e Volte a tentar\n");
            }
        }while(v_golos_jogos(golos) == false);

        FILE *ficheiroE;
        ficheiroE=fopen("Equipes.txt","rb");

        if(ficheiroE == NULL){
            printf("ERROR 404 ao tentar abrir o ficheiro de equipes para seleccao automatica no cadastro do Jogador!!!");
            exit(1);
        }

        int tamanho = numero_de_Equipes();
        struct teams equipes[tamanho]; //Vector para armazenar dados buscados no ficheiro

        //Preenchendo o vector de Equipes
        while(fread(&team, sizeof(team),1, ficheiroE)){
            strcpy(equipes[i].nome, team.nome);
            i++;
        }

        do{
            i=0;
            //Imprimindo Equipes
            while(i < (tamanho)){
                printf("%i. %s\n", (i+1), equipes[i].nome);
                i++;
            }
            scanf("%i", &equipe);

            setbuf(stdin, NULL);
            system("cls");
            if(equipe < 1 || equipe > tamanho){
                printf("Entrada Invalida! Certifique-se e Volte a tentar\n");
            }
        }
        while(equipe < 1 || equipe > tamanho);

            strcpy(player.nome, nome);
            strcpy(player.apelido, apelido);
            player.idade = idade;
            strcpy(player.equipe, equipes[equipe-1].nome);
            player.nrGolos=golos;

        if(validacaoCadastroJogador(nome, apelido, equipes[equipe-1].nome) == true){
            fwrite(&player, sizeof(player), 1, ficheiro);
            printf("\n\t\t\t\t\t\tJogador Cadastrado com Sucesso....\n");
        }else{
            printf("Os dados digitados, constam no ficheiro!!!\n");
            exit(1);
        }

        setbuf(stdin,NULL);
        fclose(ficheiroE);
        fclose(ficheiro);
}

/**Adicionar Equipe*/
void adicionar_equipe(void){
    FILE *ficheiro;
    ficheiro=fopen("Equipes.txt","ab");

    if(ficheiro == NULL){
        printf("ERROR 404 ao abrir o ficheiro para Cadastro da Equipe!!!");
        exit(1);
    }

    int desde, titulos;
    char nome[50];
    struct teams team;

        //Entrada do nome
        do{
            printf("Nome da Equipe: ");
            scanf("%s", &nome);
            setbuf(stdin, NULL);
            system("cls");
            if(vnome(nome) == false){
                printf("Nome Invalido! Por favor, Digite um nome Valido!\n");
            }
        }while(vnome(nome) == false);

        //Entrada do ano de Inicio
        do{
            printf("Primordios da Equipe: ");
            scanf("%i", &desde);
            system("cls");
            if(desde < 1800 || desde > 2020){
                printf("Entrada Invalida! Certifique-se e Volte a tentar\n");
            }
        }while(desde < 1800 || desde > 2020);

        //Entrada do ano de Inicio
        do{
            printf("Titulos da Equipe: ");
            scanf("%i", &titulos);
            system("cls");
            if(titulos < 0){
                printf("Entrada Invalida! Certifique-se e Volte a tentar\n");
            }
        }while(titulos < 0);

        strcpy(team.nome, nome);
        team.desde = desde;
        team.titulos = titulos;

        if(validacaoCadastroEquipe(nome) == true){
            fwrite(&team, sizeof(team), 1, ficheiro);
            printf("\n\t\t\t\t\t\Equipe Cadastrada com Sucesso....\n");
        }else{
            printf("O nome da Equipe introduzido, Constam no Ficheiro!!!");
            exit(1);
        }

        fclose(ficheiro);
}

/**Imprimir Jogadores*/
void carregar_jogador(void){
    FILE *ficheiro;
    ficheiro=fopen("Jogadores.txt","rb");

    if(ficheiro == NULL){
        printf("ERROR 404 ao tentar abrir o ficheiro para carregar os Jogadores!!!\n");
        exit(1);
    }

    while(fread(&player, sizeof(player),1, ficheiro)){
        printf("\nNome: %s \n", player.nome);
        printf("Apelido: %s \n", player.apelido);
        printf("Idade: %d \n", player.idade);
        printf("Numero de Golos: %d \n", player.nrGolos);
        printf("Equipa: %s \n", player.equipe);
    };
    fclose(ficheiro);
}

/**Imprimir Equipes*/
void carregar_equipe(void){
    FILE *ficheiro;
    ficheiro=fopen("Equipes.txt","rb");

    if(ficheiro == NULL){
        printf("ERROR 404 ao abrir o ficheiro para impressao de Equipes!!!");
        exit(1);
    }

    while(fread(&team, sizeof(team),1, ficheiro)){
        printf("\nNome: %s \n", team.nome);
        printf("Fundado em: %d \n", team.desde);
        printf("Titulos Ganhos: %d \n", team.titulos);
    }
    fclose(ficheiro);
}

void apagarJogador(void){
    FILE *ficheiro;
    FILE *ficheiroE;

    ficheiro=fopen("Jogadores.txt","rb");
    ficheiroE=fopen("Auxiliar.txt","w+b");
    char nome[50], auxiliar[40], apelido[50], auxiliar1[30];
    int aux = 0, controlador = 0, i = 0;

    if(ficheiro == NULL){
        printf("ERROR 404 ao abrir o ficheiro de Jogadores para a remocao do Jogador!!!");
        exit(1);
    }else
        if(ficheiroE == NULL){
            printf("ERROR 404 ao abrir o ficheiro Auxiliar para a copia de jogadores para a Remocao!!!");
            exit(1);
        }

        //Entrada do nome
        do{
            printf("Entre com o nome do Jogador a ser Eliminado: ");
            scanf("%s", &nome);
            setbuf(stdin, NULL);
            system("cls");
            if(vnome(nome) == false){
                printf("Nome Invalido! Por favor, Digite um nome Valido!\n");
            }
        }while(vnome(nome) == false);
        strcpy(auxiliar1, nome);
        //strcpy(nome, nome);

    strcpy(auxiliar, validacaoEliminarJogador(nome));
    //printf("RESPOSTA: %s\n\n", auxiliar);

    if(strcmp(auxiliar, "ERROR 404") == 0){
        printf("NOME INVALIDO!!!\n");
        exit(1);
    }

    if(strcmp(validacaoEliminarJogador(nome), nome) == 0){
        //Percorrer o nome em casos de ser composto
        for(int i=0; i<(strlen(auxiliar)); i++){
            nome[i] = auxiliar[i];
            if(auxiliar[i] == ' '){
                aux = i;
                break;
            }
        }


    int tamanho = numero_de_Jogadores();
    struct players jogador[tamanho];
    i=0;
        if(aux != 0){
            while(aux <= strlen(auxiliar)){
                apelido[controlador] = auxiliar[aux+1]; //Devolvendo o Apelido
                controlador++;
                aux++;
            }

            while(fread(&player, sizeof(player),1, ficheiro)){
                if(strcmp(player.nome, auxiliar1) == 0){
                    if(strcmp(player.apelido, apelido) != 0){
                        fwrite(&player, sizeof(player), 1, ficheiroE);
                    }
                }else{
                    fwrite(&player, sizeof(player), 1, ficheiroE);
                }
            }
        }else{
            while(fread(&player, sizeof(player),1, ficheiro)){
                if(strcmp(player.nome, auxiliar1) != 0){
                    fwrite(&player, sizeof(player), 1, ficheiroE);
                }
            }
        }
    }
    fclose(ficheiro);
    fclose(ficheiroE);

    remove("Jogadores.txt");
    rename("Auxiliar.txt", "Jogadores.txt");

    printf("\n\n\t\t\t\t\t\tJogador Eliminado com Sucesso!!!");
}

char* validacaoEliminarJogador(char nome[50]){
    FILE *ficheiro;
    ficheiro=fopen("Jogadores.txt","rb");

    if(ficheiro == NULL){
        printf("ERROR 404 ao abrir o ficheiro de Jogadores para a remocao do Jogador!!!");
        exit(1);
    }

/**Variaveis Locais para Manipulacao dos dados nessa funcao...*/
bool aberto = true;
int contador = 0;
char resultado[50], apelidoT[40];
strcpy(resultado, "");

    while(fread(&player, sizeof(player),1,ficheiro)){
        if(strcmp(player.nome, nome) == 0){
            contador++;
        }
    };

    if(contador == 0){
        strcpy(nome, "ERROR 404");
    }

    if(contador == 1){
        strcpy(resultado, nome);
    }

    if(contador > 1){
        printf("FORAM ENCONTRADOS MAIS DE 1 JOGADOR COM O NOME INTRODUZIDO!!!\n");
        //Entrada de Apelido
        do{
            printf("Entre com o Apelido do Jogador para confirmar a Pesquisa: ");
            scanf("%s", &apelidoT);
            setbuf(stdin, NULL);
            system("cls");
            if(vnome(apelidoT) == false){
                printf("Apelido Invalido! Por favor, ");
            }
        }while(vnome(apelidoT) == false);

        rewind(ficheiro);

        while(fread(&player, sizeof(player),1,ficheiro)){
            if(strcmp(player.nome, nome) == 0 && strcmp(player.apelido, apelidoT) == 0){
                aberto = true;
                break;
            }else{
                aberto = false;
            }
        };

        if(aberto == true){
            //printf("NOME LOCALIZADO A PARTIR DO APELIDO!!!\n");
            strcat(nome, " ");
            strcat(nome, apelidoT);
        }else{
            //printf("O APELIDO INTRODUZIDO, NAO PERTENCE AO NOME DIGITADO!!!\n");
            strcpy(nome, "ERROR 404");
        }

    }
    fclose(ficheiro);
    return nome;
}

bool validacaoCadastroEquipe(char nome[50]){
    bool aberto = true;

    FILE *ficheiro;
    ficheiro=fopen("Equipes.txt","rb");

    if(ficheiro == NULL){
        printf("ERROR 404 ao abrir o ficheiro para validacao de Equipes para Cadastro!!!");
        exit(1);
    }

    while(fread(&team, sizeof(team),1, ficheiro)){
        if(strcmp(team.nome, nome) == 0){
            aberto = !aberto;
        }
    };
    fclose(ficheiro);

    return aberto;
}

bool validacaoCadastroJogador(char nome[50], char apelido[50], char equipe[50]){
    bool aberto = true;

    FILE *ficheiro;
    ficheiro=fopen("Jogadores.txt","rb");

    if(ficheiro == NULL){
        printf("ERROR 404 ao abrir o ficheiro para validar a existencia do jogador para o cadastro!!!\n");
        exit(1);
    }

    while(fread(&player, sizeof(player),1,ficheiro)){
        if(strcmp(player.nome, nome) == 0 && strcmp(player.apelido, apelido) == 0 && strcmp(player.equipe, equipe) == 0){
            aberto = !aberto;
        }
    };
    fclose(ficheiro);
    return aberto;
}
