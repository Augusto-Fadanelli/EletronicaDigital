#include <stdio.h>
#include <stdlib.h> //para calloc(), realloc() e exit()
#include <stdbool.h> //para tipos bool
#include <math.h> //para pow() e log()

#define TMAX 5

void errorMessage();
char alphabet(int n);
void dynamicAlloc(bool *output);

int main()
{


    FILE *file;
    file = fopen("saida.txt", "r");

    if(file == NULL){
        printf("Arquivo nao existe!\n");
        getchar();
        exit(0);
    }

    bool *output = NULL; //Declaração do ponteiro
    output = (bool*) calloc(2, sizeof(bool)); //Alocação de memória para output

    if(output == NULL){
        printf("O array output nao pode ser alocado!\n");
        getchar();
        exit(0);
    }

    unsigned long int cont = 0;
    int contAlloc = 1;
    fscanf(file, "%d", &output[cont]);
    while(!feof(file)){
        //Sempre que o array output[] encher, a funcao dynamicAlloc é chamada e o output[] dobra de tamanho
        if(pow(2, contAlloc) == cont+1){
            if(contAlloc > TMAX){ //verifica se há mais do que 2^26 bits
                printf("\n\nQuantidade maxima de bits alocada!\n");
                errorMessage();
                break; //Forca a saída do laco
            }else{
                dynamicAlloc(output);
                contAlloc++;
            }
        }

        cont++;
        fscanf(file, "%d", &output[cont]);
    }

    //Talvez seja desnecessario
    if(cont > pow(2, TMAX)){
        cont = pow(2, TMAX);
    }
    //logaritmo na base 2 da quantidade de bits em saida.txt
    double log2 = 0;
    log2 = log(cont)/log(2);

    //BUG: Mensagem de erro aparece duas vezes
    if(log2 != (int)log2 || cont == 1){ //casting da variável para inteiro || se houver apenas 1 bit a mensagem e exibida
        printf("\n\n");
        errorMessage();
        log2 = floor(log2);//Arredonda log2 para baixo - log2 agora é a quantidade de variaveis/colunas
    }

    cont = pow(2, log2); //ignora os bits a mais

    //cont: linhas | log2: colunas
    bool truthTable[cont][(int)log2];

    //Atribui os valores dos bits da tabela verdade
    int teste = 0;
    int loop = -1;
    for(int j=(int)log2-1; 0<=j; j--, teste++){
        for(int i=0; cont>i; i++){
                loop++;
                if(0 <= loop && pow(2, teste) > loop){
                    truthTable[i][j] = 0;
                }else{
                    truthTable[i][j] = 1;
                    if(2*pow(2,teste)-1 == loop){
                        loop = -1;
                    }
                }
            }
            loop = -1;
    }

    //Mostra a tabela verdade completa
    char op;
    printf("Mostrar a tabela verdade?[s][n] ");
    scanf("%c", &op);
    printf("\n\n");
    if('s' == op || 'S' == op){
        for(int j = 0; (int)log2 > j; j++){
            printf("%c ", alphabet(j));
        }
        printf("S0\n");
        for (int i=0; cont > i; i++){
            for (int j=0; (int)log2 > j; j++){
                printf("%d ", truthTable[i][j]);
            }
            printf("%d", output[i]);
            printf("\n");
        }
        printf("\n\n");
    }

    //Mostra Expressão Booleana
    bool flag = false;
    for (int i=0; cont > i; i++){
            if(1 == output[i]){
                if(flag){
                    printf("+");
                }else{
                    flag = true;
                }
                for (int j=0; log2 > j; j++){
                    if(1 == truthTable[i][j]){
                        printf("%c",alphabet(j));
                    }else{
                        printf("%c'",alphabet(j));
                    }
                }

            }
        }
        printf("\n");

    return 0;
}

void errorMessage(){
    static bool flag = false;
    if(false == flag){
        printf("Aviso: A quantidade de bits no arquivo saida.txt nao e de ordem (2^n | 1<=n<=%d)\n", TMAX);
        printf("Para que nao haja erros e recomendado que se utilize uma quantidade de bits de acordo com os parametros acima.\n\n");
        flag = true;
    }
}

char alphabet(int n){
    //Array do alfabeto
    char a[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    return a[n];
}

//Aumenta o array output em ordem pow(2, exponent)
void dynamicAlloc(bool *output){
    static int exponent = 2;
    exponent++;
    output = (bool*) realloc(output, pow(2, exponent) * sizeof(bool));

    if(output == NULL){
        printf("O array output nao pode ser alocado[2]!\nExponent: %d", exponent);
        getchar();
        exit(0);
    }
}
