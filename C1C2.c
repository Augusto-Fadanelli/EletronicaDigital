#include <stdio.h>
#include <stdlib.h> //para a funcao exit

void c1(int *vetc1, int *vet);
void c2(int *vetc2, const int *vetc1);

int main(int argc, char **argv)
{
	int num1[8] = {0, 1, 0, 0, 0, 0, 0, 0}; //Primeiro octeto binario
	int num2[8] = {0, 1, 1, 1, 1, 1, 1, 0}; //Segundo octeto binario
	int numc1[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //Vetor C1 (NAO ALTERAR OS VALORES)
	int numc2[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	//sum();
	c1(numc1, num2); //O num2 sera complementado a 1
	c2(numc2, numc1); //complemento a 2
	
	//mostrar
	printf("num1:\n");
	for(int i=0; i<8; i++){
		printf("%d, ", num1[i]);
	}
	printf("\n");
	
	printf("num2:\n");
	for(int i=0; i<8; i++){
		printf("%d, ", num2[i]);
	}
	printf("\n");
	
	printf("numc1:\n");
	for(int i=0; i<8; i++){
		printf("%d, ", numc1[i]);
	}
	printf("\n");
	
	printf("numc2:\n");
	for(int i=0; i<8; i++){
		printf("%d, ", numc2[i]);
	}
	printf("\n");

	return 0;
}

//Faz a operacao de complemento a 1
void c1(int vetc1[], int vet[]){
	
	//int i = 7; //contador
	for(int i=0; i<8; i++){
		if(vet[i] == 0){
			vetc1[i] = 1;
		}else if(vet[i] == 1){
			vetc1[i] = 0;
		}else{
			printf("ERRO NO VETOR num2\n");
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
