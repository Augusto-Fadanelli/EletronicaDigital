#include <stdio.h>
#include <stdlib.h> //para a funcao exit

void decToBin(int *num, const int dec);
void sumSub(int *operation, const int *num1, const int *num2);
void c1(int *vetc1, const int *vet);
void c2(int *vetc2, const int *vetc1);

int main(int argc, char **argv)
{
	//*NAO ALTERAR OS VALORES DOS VETORES*
	int num1[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //Primeiro octeto binario
	int num2[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //Segundo octeto binario
	int numc1[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //Vetor C1 (Complemento a 1 do num2)
	int numc2[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //Vetor C2 (Complemento a 2 do num2)
	int sum[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //num1 + num2
	int sub[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //num1 + numc2 (Subtracao de num1 - num2)

	//Manipular arquivo .txt
    FILE *file;
    file = fopen("decimais.txt", "r");

    if(file == NULL){
        printf("Arquivo nao existe!\n");
        getchar();
        //Getchar(); + scanf("c\n");
        exit(0);
    }

	int dec1 = 0;
	int dec2 = 0;

    fscanf(file, "%i %i", &dec1, &dec2);
    printf("%i %i\n", dec1, dec2);

    fclose(file); //Fim da manipulação de arquivo .txt
    /*obs: verificar se o numero é maior q 127 ou "menor q -127"
    * tentar adaptar o código pra funcionaro com mais de dois inteiros na msm linha
    * Executar novamente a cada linha com os valores atualizados
    */

	decToBin(num1, dec1);
	decToBin(num2, dec2);

	sumSub(sum, num1, num2);
	c1(numc1, num2); //O num2 sera complementado a 1
	c2(numc2, numc1); //complemento a 2
	sumSub(sub, num1, numc2); //A soma do num1+numc2 e o msm que a subtracao de num1-num2

	//mostrar
	printf("num1:\n");
	for(int i=0; i<8; i++){
		printf("%d ", num1[i]);
	}
	printf("\n");

	printf("num2:\n");
	for(int i=0; i<8; i++){
		printf("%d ", num2[i]);
	}
	printf("\n");

	printf("sum:\n");
	for(int i=0; i<8; i++){
		printf("%d ", sum[i]);
	}
	printf("\n");

	printf("numc1:\n");
	for(int i=0; i<8; i++){
		printf("%d ", numc1[i]);
	}
	printf("\n");

	printf("numc2:\n");
	for(int i=0; i<8; i++){
		printf("%d ", numc2[i]);
	}
	printf("\n");

	printf("sub:\n");
	for(int i=0; i<8; i++){
		printf("%d ", sub[i]);
	}
	printf("\n");

	return 0;
}

void decToBin(int *num, const int dec){

	if(dec > 0){
		int q = dec; //quociente da divisao
		int i=7;
		do{
			num[i] = q % 2;
			q /= 2;
			i--;
		}while(q != 0);
	}else if(dec < 0){
		printf("ERRO: NUMERO DECIMAL NEGATIVO!\n");
		exit(0);
	} //Se o numero for igual a 0 nao e feito nada (o vetor ja inicia com valor 0)
}

void sumSub(int operation[], const int num1[], const int num2[]){

	int soma;
	int k=0;

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
			exit(0);
		}
	}

}

//Faz a operacao de complemento a 1
void c1(int vetc1[], const int vet[]){

	//int i = 7; //contador
	for(int i=0; i<8; i++){
		if(vet[i] == 0){
			vetc1[i] = 1;
		}else if(vet[i] == 1){
			vetc1[i] = 0;
		}else{
			printf("ERRO NO VETOR num2!\n");
			exit(0);
		}

	}

}

//Faz a operacao de complemento a 2
void c2(int vetc2[], const int vetc1[]){

	int vet[8];
	for(int i=0; i<8; i++){
		vet[i] = vetc1[i];
	}

	//Complemento a 2
	int i = 7; //contador
	do{
		vet[i] += 1;
		if(vet[i] == 1){
			vetc2[i] = 1;
			while(i >= 0){
				vetc2[i] = vet[i];
				i--;
			}
			i++; // i=0 (no fim da operacao acima i=-1)
		}else if(vet[i] != 2){
			printf("ERRO NA FUNCAO c2!\n");
			exit(0);
		}
		i--;
	}while(i != -1);

}
