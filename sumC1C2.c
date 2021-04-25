#include <stdio.h>
#include <stdlib.h> //para a funcao exit

void c1(int *vetc1, int *vet);

int main(int argc, char **argv)
{
	int num1[8] = {0, 1, 0, 0, 0, 0, 0, 0}; //Primeiro octeto binario
	int num2[8] = {0, 1, 1, 1, 1, 1, 1, 0}; //Segundo octeto binario
	int numc1[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //Vetor C1 (NAO ALTERAR OS VALORES)

	//sum();
	c1(numc1, num2); //O num2 sera complementado a 1 - numc1 copiado
	
	//mostrar
	for(int i=0; i<8; i++){
		printf("%d, ", numc1[i]);
	}
	printf("\n");

	return 0;
}

//Faz a operacao de complemento a 1
void c1(int vetc1[], int vet[]){
	
	//Complemento a 1
	int i = 7; //contador
	do{
		vet[i] += 1;
		if(vet[i] == 1){
			vetc1[i] = 1;
			while(i >= 0){
				vetc1[i] = vet[i];
				i--;
			}
			i++; // i=0 (no fim da operacao acima i=-1)
		}else if(vet[i] != 2){
			printf("ERRO NA FUNCAO c1!\n");
			exit(0);
		}
		i--;
	}while(i != -1);
	
}
