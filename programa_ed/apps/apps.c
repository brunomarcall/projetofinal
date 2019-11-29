#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "include.h"

//-----------------------FUNÇÃO PRINCIPAL-----------------------------------------------
int main(){
	/**
	 * Caso o retorno da função creatList seja a 0 (o que significa que o arquivo "iv_semana_si.txt"), ele
	 * executará os seguintes passos.
	 * Precedido de 5 segundos o programa será finalizado.
	 */
	if(!createList()){
		printf("Desculpe, o arquivo não possui dados ou o nome do arquivo digitado é inexistente!");
		printf("\n");
		sleep(5);
		exit(1);
	}
	//chama a função com as opções de navegação para o usuário
	menu();
	return 1;
}
