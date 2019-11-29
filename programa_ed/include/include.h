typedef  struct {
	char date[11];
	char hour[11];
	int nInsc;
	char name[100];
}Info;

typedef struct {
	int qtd;
	Info lista[685];
}Lista;

Lista li; 



//-----------------------PROTOTIPOS DAS FUNÇÕES-----------------------------------------------
void menu();

int createList();

void originalList();

void listByDate(char []);

void listParticipantByIns(int);

void listParticipantByName(char*);

void listInOrder();

void listOrderByDate_Time(char [], int);