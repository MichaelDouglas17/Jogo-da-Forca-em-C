#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

//variáveis globais
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura(){

printf("   |/|    \n");
printf("   | |    \n");
printf("   |/|    \n");
printf("   | |    \n");
printf("   |/|    \n");
printf("   | |    \n");
printf("   |/|    \n");
printf("  (___)   \n");
printf("  (___)         JOGO DA MONARQUIA FRANCESA\n");
printf("  (___)             === remastered ===\n");
printf("  (___)   \n");
printf("  (___)   \n");
printf("  // \\               heads will roll \n");
printf(" // \\    \n");
printf("|| ||     \n");
printf("|| ||     \n");
printf("|| ||     \n");
printf(" \\___//            \n");
printf("   ---                    \n");
}

void chuta(){

        char chute;
        scanf(" %c", &chute);

        chutes[chutesdados] = chute;
        chutesdados++;
}

int jachutou(char letra) {
    int achou = 0;
    for(int j= 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca() {

    int erros = chuteserrados(); 
     
printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");

    printf("\n\n");

        printf("Voce ja deu %d chutes\n", chutesdados);
        
        for(int i = 0; i < strlen(palavrasecreta); i++) {   

            if( jachutou(palavrasecreta[i]) ) {
                printf("%c ", palavrasecreta[i]);
            } else {
                printf("_ ");
            }
        }
        printf("\n");
}

void adicionapalavra() {

    char resp;
    printf("Voce deseja adicionar uma nova palavra no jogo? [S/N]");
    scanf(" %c", &resp);
    
    if(resp =='S') {
        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra que voce quer adicionar?");
        scanf("%s", &novapalavra);

        FILE* f; 
        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Desculpe, banco de dados não disponível.\n");
            exit(1);
        }

        int qtd; 
        fscanf(f, "%d", &qtd);
        qtd++;

        //posicionar na primeira linha do arquivo e adcionar a nova palavra
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        //posicionar na ultima linha e adicionar nova palavra
        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }

}

void escolhepalavra() {
    //abrir e ler arquivo txt
    FILE* f;
    f = fopen("palavras.txt", "r");

    if( f == 0) {
        printf("Desculpe, banco de dados não disponivel");
        exit(1);
    }

    int quantpalavras;
    fscanf(f, "%d", &quantpalavras); 

    //puxar palavra aleatória
    srand(time(0));
    int randomico = rand() % quantpalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }
 
    fclose(f);
}

int acertou(){

    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }
    return 1;
}

int chuteserrados(){

    int erros = 0; 

    for(int i = 0; i < chutesdados; i++) {

        int existe = 0;
        for(int j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]) {
                existe = 1;
                break; 
            }
        }
            if(!existe) erros++;
    }

    return erros;
}

int enforcou() {
    //tava aqui
    return chuteserrados() >= 5;
}

int main() {

    escolhepalavra();
    abertura();

    do {
        desenhaforca();
        chuta();

    } while (!acertou() && !enforcou());

    if(acertou()) {
            
        printf("PARABENS VOCE GANHOU⠀");

    } else {
        
        printf("      VOCE PERDEU HIHIHI HA \n");
        printf("\n");
        printf(" BEM VINDO AO GIGANTE DA COLINA \n");
        printf("\n A PALAVRA SECRETA ERA == %s ==\n", palavrasecreta);
   

    adicionapalavra();
}
