#include <stdio.h>
#include <stdlib.h> //para a função exit(0);

void saida(int const dec1, int const dec2, int const *num1, int const *num2, int const *sum, int const *numc1, int const *numc2, int const *sub); //posso fazer uma lista encadeada de vetores e passar só um como argumento

void decToBin(int *num, const int dec);
void sumSub(int *operation, const int *num1, const int *num2);
void c1(int *vetc1, const int *vet);
void c2(int *vetc2, const int *vetc1);

int main(int argc, char **argv)
{
	int num1[8]; //Primeiro octeto binario
	int num2[8]; //Segundo octeto binario
	int numc1[8]; //Vetor C1 (Complemento a 1 do num2)
	int numc2[8]; //Vetor C2 (Complemento a 2 do num2)
	int sum[8]; //num1 + num2
	int sub[8]; //num1 + numc2 (Subtracao de num1 - num2)

	//Abre arquivo .txt
    FILE *file;
    file = fopen("decimais.txt", "r");

    if(file == NULL){
        printf("Arquivo nao existe!\n");
        getchar();
        exit(0);
    }

    int l = 1; //Contador de linha

	int dec1 = 0;
	int dec2 = 0;

	fscanf(file, "%i %i", &dec1, &dec2);
    while(!feof(file)){

        if(dec1 < -127 || dec1 > 127 || dec2 < -127 || dec2 > 127){ //verifica se os números são válidos
            printf("\nERRO: USE APENAS NUMEROS DECIMAIS DE -127 A 127\n"); //posso por isso em saida(); usando uma flag
            printf("Linha %i: %i %i\n", l, dec1, dec2);
            printf("\n-----------------------\n");
        }else{
            //Zera vetores
            for(int i=0; i<8; i++){
                num1[i] = 0; //Obrigatoriamente precisa ser zerado
                num2[i] = 0; //Obrigatoriamente precisa ser zerado
                numc1[i] = 0; //Não precisa ser zerado
                numc2[i] = 0; //Obrigatoriamente precisa ser zerado
                sum[i] = 0; //Não precisa ser zerado
                sub[i] = 0; //Não precisa ser zerado
            }

            decToBin(num1, dec1); //(o vetor do primeiro argumento precisa obrigatoriamente ser zerado antes)
            decToBin(num2, dec2);

            sumSub(sum, num1, num2);
            c1(numc1, num2); //O num2 será complementado a 1
            c2(numc2, numc1); //complemento a 2 (o vetor do primeiro argumento precisa obrigatoriamente ser zerado antes)
            sumSub(sub, num1, numc2); //A soma do num1+numc2 é o mesmo que a subtração de num1-num2

            //mostrar
            saida(dec1, dec2, num1, num2, sum, numc1, numc2, sub);
        }

        l++; //Conta mais uma linha
        fscanf(file, "%i %i", &dec1, &dec2); //lê os próximos valores

    }

    fclose(file); //Fecha arquivo .txt
    //obs: tentar adaptar o código pra funcionar com mais de dois inteiros decimais na msm linha

	return 0;
}

//dar a opção de saida em um arquivo binarios.txt
void saida(int const dec1, int const dec2, int const *num1, int const *num2, int const *sum, int const *numc1, int const *numc2, int const *sub){

        printf("\nnum1:%i num2:%i (Decimal)\n\n", dec1, dec2);

        printf("num1:         ");
        for(int i=0; i<8; i++){
            printf("%d ", num1[i]);
        }
        printf("\n");

        printf("num2:         ");
        for(int i=0; i<8; i++){
            printf("%d ", num2[i]);
        }
        printf("\n");

        printf("num1+num2:    "); //sum
        for(int i=0; i<8; i++){
            printf("%d ", sum[i]);
        }
        printf("\n");

        printf("C1 de num2:   "); //numc1
        for(int i=0; i<8; i++){
            printf("%d ", numc1[i]);
        }
        printf("\n");

        printf("C2 de num2:   "); //numc2
        for(int i=0; i<8; i++){
            printf("%d ", numc2[i]);
        }
        printf("\n");

        printf("num1+(-num2): "); //sub
        for(int i=0; i<8; i++){
            printf("%d ", sub[i]);
        }
        printf("\n");

        printf("\n-----------------------\n");

}

void decToBin(int *num, const int dec){ //tentar deixar o código mais bonito

    int q;
    int i=7;

	if(dec > 0){ //Para números positivos
		q = dec; //Quociente da divisao
		do{ //Converte o numero decimal para binario
			num[i] = q % 2; //Divide o decimal por 2 e atribui o resto (que pode ser 0 ou 1) em num[i]
			q /= 2; //Divide o decimal por 2 e atribui em q para ser usado no próximo loop
			i--;
		}while(q != 0); //Quando o quociente der 0 a operação acaba
	}else if(dec < 0){ //Para números negativos
        q = dec * (-1); //Multiplica por (-1) pro número ficar positivo
		do{
			num[i] = q % 2;
			q /= 2;
			i--;
		}while(q != 0);

		int numc1[8]; //Vetor usado na operação C1
		c1(numc1, num);

		for(int i=0; i<8; i++){ //zera o vetor num que servirá como numc2
            num[i] = 0;
		}
        c2(num, numc1);
	} //Se o numero for igual a 0 nao e feito nada (o vetor ja inicia com valor 0)
}

void sumSub(int operation[], const int num1[], const int num2[]){

	int soma;
	int k=0; //Equivalente ao vai 1 Ex.:(1+1 é 0 e vai 1)

	for(int i=7; i>=0; i--){
		soma = num1[i] + num2[i] + k;
		k = 0;

		if(soma == 0){ //0 + 0 = 0 (binario)
			operation[i] = 0;
		}else if(soma == 1){ //0 + 1 ou 1 + 0 = 1 (binario)
			operation[i] = 1;
		}else if(soma == 2){ //1 + 1 = 10 (binario)
			k = 1;
			operation[i] = 0;
		}else if(soma == 3){ //1 + 1 + 1 = 11 (binario)
			k = 1;
			operation[i] = 1;
		}else{
			printf("ERRO NO(S) VETOR(ES) num1 E/OU num2!\n");
            getchar();
			exit(0);
		}
	}

}

//Faz a operacao de complemento a 1
void c1(int vetc1[], const int vet[]){

    //Inverte os bits
	for(int i=0; i<8; i++){
		if(vet[i] == 0){
			vetc1[i] = 1;
		}else if(vet[i] == 1){
			vetc1[i] = 0;
		}else{
			printf("ERRO NO VETOR num2!\n");
			getchar();
			exit(0);
		}

	}

}

//Faz a operacao de complemento a 2
void c2(int vetc2[], const int vetc1[]){

	int i = 7; //contador
	do{
		if(vetc1[i] == 0){ //se o bit for 0 então inverte para 1
			vetc2[i] = 1;
			i--;
			while(i >= 0){ //Copia o restante dos bits
				vetc2[i] = vetc1[i];
				i--;
			}
		}else if(vetc1[i] != 1){
			printf("ERRO NA FUNCAO c2!\n");
			getchar();
			exit(0);
		} //Se o bit for 1 entao vetc2[i]=0 e volta uma posição do vetor (não precisa atribuir nada a vetc2[i] pois já está com valor 0 definido)
		i--;
	}while(i >= 0);

}
