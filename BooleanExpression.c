#include <stdio.h>

enum Bit {F, V};

int main(){	
	int tam = 32;
	enum Bit tabelaVerdade[tam];

	for(int i=0; tam>i; i++){
		if(i%2 == 0){
			tabelaVerdade[i] = F;
		}else{
			tabelaVerdade[i] = V;
		}
	}
	
	//Mostra o vetor tabelaVerdade
	for(int i=0; tam>i; i++){
		printf("%c", tabelaVerdade[i]);
	}
}
