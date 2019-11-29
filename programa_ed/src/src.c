#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "include.h"

//-----------------------IMPLEMENTAÇÃO DAS FUNÇÕES-----------------------------------------------

//Esta função imprime para o usuário o menu com todas as funcionalidades do programa
void menu(){
	int option,nInsc,shift;
	char name[100];
	char date[10], hour[8];

	system("clear");

	do{
		printf("\n+------------------------------------------------------------------+");
		printf("\n|                             Menu                                 |");
		printf("\n+------------------------------------------------------------------+");
		printf("\n|    1 - Listar todos os presentes                                 |");
		printf("\n|    2 - Listar participantes em ordem numerica                    |");
		printf("\n|    3 - Listar presenca do participante pelo numero de inscricao  |");
		printf("\n|    4 - Listar presenca do participante pelo seu nome             |");
		printf("\n|    5 - Listar participante(s) por data                           |");
		printf("\n|    6 - Listar participante(s) por data e turno                   |");
		printf("\n|    7 - Limpar tela                                               |");
		printf("\n|    0 - Sair                                                      |");
		printf("\n+------------------------------------------------------------------+");
		printf("\nDigite sua escolha >> ");
		scanf("%d",&option);

		//Sequência de "if" e "else if" que destinam a funcionalidade escolhida pelo usuário
		if(option==1)
			originalList();
		else if(option==2)
			listInOrder();
		else if(option==3){
			printf("Numero de inscricao >> ");
			scanf("%d",&nInsc);
			listParticipantByIns(nInsc);
		}
		else if(option==4){
			printf("Nome do participante >> ");
			scanf(" %[^\n]s",name);
			listParticipantByName(name);
		}
		else if(option==5){
			printf("Data (dd/mm/yyyy)>> ");
			scanf("%s",date);
			listByDate(date);
		}
		else if(option==6){
			printf("(1 - Manhã | 2 - Tarde | 3 - Noite) >> ");
			scanf("%d",&shift);
			printf("Data (dd/mm/yyyy)>> ");
			scanf("%s",date);
			listOrderByDate_Time(date,shift);
		}
		else if(option==7)
			system("clear");
		else if(option!=1 || option!=2 || option!=3 || option!=4 || option!=5 || option!=6 || option!=0 )
			option=0;

	}while(option!=0);
	system("clear");
}

//Esta função cria uma lista a partir do arquivo "iv_semana_si.txt"
int createList(){
	int i=0,j=0;
	char date[11], hour[11], nInsc[7], name[100], name2[100];

	char leitura[]="files/";
	char nome_arquivo[50];
	
	/*Leitura do nome do arquivo*/
	printf("Digite o nome do arquivo para ser lido\n->>");
	scanf("%s",nome_arquivo);

	/*Concatenação do nome do arquivo com seu caminho*/
	strcat(leitura, nome_arquivo);

	/*atribui o caminho a uma constante para que seja aceito no fopen*/
	const char* arquivo_lido = leitura;
	
	Info record;

	FILE *input;
	//Abre o arquivo e o seta em input
	input = fopen(arquivo_lido,"r");

	if(input==NULL)
		return 0;

	/**
	 * Este while captura através de cada "fgets" o "pedaço" da linha para cada variável
	 * Neste caso os 11 primeiros caracteres vão para date
	 * Os próximos 11 vão para hour, os próximos 7 para nInsc e os próximos 100 para name
	 * Até que ele sejam diferentes de NULL
	 *
	 * Cada vez que todas as condições são obedecidas e são setadas em cada variável através do fgets
	 * ela são copiadas, ou inseridas (no caso de nInsc), para a variável record do tipo Info
	 *
	 * Ao final de cada cópia e inserção de valor, a lista recebe record
	 * Após isso a lista é incrementada
	 */
	while ((fgets(date, 11, input)!=NULL) && (fgets(hour, 11, input)!= NULL) &&
	 	   (fgets(nInsc, 7, input) != NULL) && (fgets(name, 100, input)!= NULL)){

		strcpy(record.date, date);
	  	strcpy(record.hour, hour);
	  	record.nInsc=atoi(nInsc);

	  	for(i=0 ; name[i]!='\0' ; i++)
	  		if(name[i] == '\n')
	  			name[i] = name[i+1];

	  	strcpy(record.name, name);

	  	li.lista[li.qtd++] = record;
	}

	fclose(input);

	return 1;
}

//Esta função lista e imprime a lista original de presenças
void originalList(){
	int i,count=0;

	//Este laço for imprime as informações de cada ocorrência de acordo com a posição de "i"
	for(i=0 ; i<li.qtd ; i++){
		printf("\nIncrição: %d\n",li.lista[i].nInsc);
		printf("Aluno:    %s\n",li.lista[i].name);
		printf("Horário:  %s",li.lista[i].date);
		printf("%s\n",li.lista[i].hour);
		count++;
	}
	printf("\nQuantidade: %d\n",count);
}

//Esta função lista e imprimie todas as ocorrências de presenças em ordem e sem repetições
void listInOrder(){
	int i,j,k=0;
	Info aux;

	//Este laço é responsável por ordenar os números de inscrições com seus dados inclusos (nome, hora e data).
	for(i=0; i<li.qtd; i++)
		for(j=i+1;j<li.qtd;j++)
			if(li.lista[i].nInsc>li.lista[j].nInsc){
				aux = li.lista[i];
				li.lista[i] = li.lista[j];
				li.lista[j]=aux;
			}

	 //Ao entrar nesse for, são impressos os participantes sem repetições, graças ao laço while.
	for(i=0;i<li.qtd; i++){
		k++;
		printf("\nIncrição: %d\n",li.lista[i].nInsc);
		printf("Aluno:    %s\n",li.lista[i].name);
		printf("Horário:  %s",li.lista[i].date);
		printf("%s\n",li.lista[i].hour);

		/**
		 * Entramos nesse while para que o "i" seja iterado até que ele encontre um numero de inscrição diferente
		 * do atual utilizado no início do laço for.
		 */
		while(li.lista[i].nInsc == li.lista[i+1].nInsc)
			i++;
	}
	printf("\nTotal de participantes sem repetições: %d\n",k );
}

//Esta função lista e imprime todas as ocorrências de participantes de acordo com o número de inscrição solicitado
void listParticipantByIns(int nInsc){
	int i, count=0;

	for (i=0; i<li.qtd; i++){
		//Caso o numero de inscrição passado seja igual a algum que conste na lista ele imprime as informações
		//daquela inscrição
		if (nInsc == li.lista[i].nInsc){
			printf("\nIncrição: %d\n",li.lista[i].nInsc);
			printf("Aluno:    %s\n",li.lista[i].name);
			printf("Horário:  %s",li.lista[i].date);
			printf("%s\n",li.lista[i].hour);
			count++;
		}
	}
	printf("\nQuantidade de entradas e/ou saídas: %d\n", count);
}

//Esta função lista e imprime todas as ocorrências de participantes de acordo com o nome solicitado
void listParticipantByName(char *name){
	int i,test,count=0;

	/**
	 * Neste laço for a variável test recebe o resultado da comparação entre o nome passado e o nome na posição
	 * em que "i" ocupa.
	 * Caso o nome passado como parâmetro seja igual ao que consta na lista, test é setado com 0 e automaticamente
	 * a informação daquela ocorrência é impressa para o usuário
	 */
	for(i=0;i<li.qtd;i++){
		test = strcmp(li.lista[i].name, name);
		if(test == 0){
			printf("\nIncrição: %d\n",li.lista[i].nInsc);
			printf("Aluno:    %s\n",li.lista[i].name);
			printf("Horário:  %s",li.lista[i].date);
			printf("%s\n",li.lista[i].hour);
			count++;
		}
	}
	printf("\n%s tem %d entradas e/ou saídas.\n",name,count);
}

//Esta função lista e imprime todas as ocorrências de participantes de acordo com a data solicitada
void listByDate(char data[]){
	Info aux;
	int dat,i,j,date[li.qtd-1],count=0;

	//Sequência de "for" para ordenar a lista de presenças por ordem alfabética
	for(i=0;i<li.qtd;i++)
		for(j=i+1;j<li.qtd;j++){
			aux=li.lista[i];
			if(strcmp(aux.name,li.lista[j].name)>0){
				aux = li.lista[i];
				li.lista[i] = li.lista[j];
				li.lista[j]=aux;
			}
		}

	//dat recebe apenas os 2 primeiros dígitos da data passada pelo usuário
	dat=atoi(data);

	//"For" responsável por imprimir os casos em que a data passada pelo usuário for igual a data na lista
	for(i=0; i<li.qtd;i++){
		//date recebe os 2 primeiro dígitos da data na posição "i"
		date[i]= atoi(li.lista[i].date);
		if(date[i] == dat){
			printf("\nIncrição: %d\n",li.lista[i].nInsc);
			printf("Aluno:    %s\n",li.lista[i].name);
			printf("Horário:  %s",li.lista[i].date);
			printf("%s\n",li.lista[i].hour);
			count++;
		}
	}
	printf("\nqtd: %d\n",count);}

//Esta função lista e imprime todas as ocorrências de participantes de acordo com a data e turno solicitados
void listOrderByDate_Time(char data[], int turno){
	Info aux;
	int dat,k,i,j,date[li.qtd-1],time[li.qtd-1], count=0;
	char time2[9];

	//dat recebe os 2 primeiros dígitos correspondente ao dia, passados pelo usuários
	dat=atoi(data);

	//Sequência de "for" para ordenar a lista de presenças por ordem alfabética
	for(i=0;i<li.qtd;i++)
		for(j=i+1;j<li.qtd;j++){
			aux=li.lista[i];
			if(strcmp(aux.name,li.lista[j].name)>0){
				aux = li.lista[i];
				li.lista[i] = li.lista[j];
				li.lista[j]=aux;
			}
		}

	//Confirma ao usuário qual turno foi escolhido
	if(turno == 1)
		printf("\nManhã\n");
	else if(turno == 2)
		printf("\nTarde\n");
	else if(turno == 3)
		printf("\nNoite\n");
	else
		printf("\nTurno digitado inexistente\n");

	for(i=0; i<li.qtd;i++){
		//date recebe os 2 primeiros dígitos correspondentes ao dia, da lista, na posição "i"
		date[i]= atoi(li.lista[i].date);
		k=0;
		/**
		 * Este for é responsável por fazer com que a variável "time2" receba cada registro de hora, porém sem o espaço inicial
		 * que existe na variável "hour". Observe:
		 * hour - " 18:00:20", quando setado na variável time2 ele fica: "18:00:20"
		 */
		for(j=0; li.lista[i].hour[j]!='\0'; j++)
			if(li.lista[i].hour[j]!= ' '){
				time2[k] = li.lista[i].hour[j];
				k++;
			}

		time[i]=atoi(time2);

		/**
		 * Se a date na posição "i" for igual a dat (que corresponde a data que o usuário passou) forem iguais
		 * ele vai imprimir o turno passado pelo usuário dentro da data que o mesmo passou também
		 */
		if(date[i] == dat){

			if(turno==1 && (time[i] >= 06 && time[i] <= 12)){
				printf("\nIncrição: %d\n",li.lista[i].nInsc);
				printf("Aluno:    %s\n",li.lista[i].name);
				printf("Horário:  %s",li.lista[i].date);
				printf("%s\n",li.lista[i].hour);
				count++;
			}else if(turno == 2 && (time[i] > 12 && time[i] < 18)){
				printf("\nIncrição: %d\n",li.lista[i].nInsc);
				printf("Aluno:    %s\n",li.lista[i].name);
				printf("Horário:  %s",li.lista[i].date);
				printf("%s\n",li.lista[i].hour);
				count++;
			}else if(turno == 3 && (time[i] >= 18 && time[i] <= 22)){
				printf("\nIncrição: %d\n",li.lista[i].nInsc);
				printf("Aluno:    %s\n",li.lista[i].name);
				printf("Horário:  %s",li.lista[i].date);
				printf("%s\n",li.lista[i].hour);
				count++;
			}else if((turno != 1 && turno != 2 && turno != 3) && (time[i] < 6 && time[i] > 22)){
				printf("Frequencia(s) inexistente(s)!\n");
				break;
			}
		}
	}
	printf("\nQuantidade: %d\n",count);
}

