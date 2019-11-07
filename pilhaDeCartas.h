/*======================================================= 
Descrição: Contem funções de manipulação de pilha simplismente encadeada
=======================================================*/

//Informação da pilha
typedef struct{
	int  valorCarta;
}Carta;

//Objeto da pilha
typedef struct objeto{
	int id;
	Carta dados;	
	struct objeto *proxObj;
}ObjetoP;

//Pilha de objetos
typedef struct{
	ObjetoP *topo;
}Pilha;

//Gerador de ID, e variaveis globais
int idAi = 1;
//Soma do valorDasCartas
int totValorCartas = 0;

//Criar pilha
Pilha* createPilha();

//Empilhar
bool empilhar(Pilha *pilha, Carta carta);

//Desempilha
bool desempilhar(Pilha *pilha,Carta carta);

//Verifica se a pilha esta vazia
bool emptyPilha(Pilha *pilha);

//Verificar o tamanho da pilha
int sizePilha(Pilha *pilha);

//Consultar todos os dados da pilha (não retorna objetos)
void selectAllPilha(Pilha *pilha);

//Soma o valor das cartas de uma pilha (diller ou jogador)
int somaAllPilha(Pilha *pilha);

//Consulta objeto especifico da pilha por ID (retorna objeto)
ObjetoP* selectWherePilha(Pilha *pilha, int searchId); 

//Deletar/destruir todos os objetos da pilha
bool deleteAllPilha(Pilha *pilha, bool destruir);

//Deletar objeto especifico por id
bool deleteWherePilha(Pilha *pilha, int id);

//Destruir pilha
void destroi_pilha(Pilha *p);

Pilha* createPilha(){
	Pilha *pilha = (Pilha*)malloc(sizeof(Pilha));
	if(pilha == NULL) return NULL;
	pilha->topo = NULL;
	return pilha;
}

bool empilhar(Pilha *pilha, Carta carta){
	if(pilha == NULL) return false;
	ObjetoP *newObjetoP=(ObjetoP*)malloc(sizeof(ObjetoP));
	if(newObjetoP == NULL) return false;
	newObjetoP->dados = carta;
	newObjetoP->id = idAi++;
	newObjetoP->proxObj = pilha->topo;
	pilha->topo = newObjetoP;
	return true;
}

bool desempilhar(Pilha *pilha,Carta *carta){
	if(emptyPilha(pilha)) return false;
	
	ObjetoP *aux = pilha->topo;
	carta->valorCarta = aux->dados.valorCarta;
	pilha->topo = aux->proxObj;
	free(aux);
	return true;
}

bool emptyPilha(Pilha *pilha){
	if(pilha->topo == NULL || pilha == NULL) return true;
	return false;
}

int sizePilha(Pilha *pilha){
	int sizePilha = 0;
	if(!emptyPilha(pilha)){
		ObjetoP *aux = pilha->topo;
		while(aux != NULL){
			sizePilha++;
			aux = aux->proxObj;
		}
	}
	return sizePilha;
}

void selectAllPilha(Pilha *pilha){
	if(emptyPilha(pilha)){
		printf("\n[Sem registros]\n");	
	}else{
		ObjetoP *aux = pilha->topo;
		printf("\n========================\n");
		printf("       C A R T A S       \n");
		printf("========================\n");
		int qtdObjetosP = 0;
		while( aux != NULL){
			qtdObjetosP++;
			printf("|ID: %d\n", aux->id);
			printf("|valor:%d\n\n",aux->dados.valorCarta);		
			aux = aux->proxObj;
		}
		printf("========================\n");
		printf("Total de cartas: %d\n",qtdObjetosP);
	}	
}

int somaAllPilha(Pilha *pilha){
	totValorCartas = 0;
	int qtdCartas = sizePilha(pilha);
	
	if(!emptyPilha(pilha)){
		ObjetoP *aux = pilha->topo;
		while(aux != NULL){
			if(qtdCartas == 2 && aux->dados.valorCarta == 1){
				totValorCartas += 11;
				qtdCartas = 3;//permite definir que somente 1 carta tenha valor 11
			}else{
				totValorCartas += aux->dados.valorCarta;
			}
			aux = aux->proxObj;
		}
	}
	return totValorCartas;
}

ObjetoP* selectWherePilha(Pilha *pilha, int searchId){
	if(emptyPilha(pilha)){
		printf("\n[Sem registros]\n");	
		return NULL;
	}else{
		ObjetoP *aux = pilha->topo;
		while(aux != NULL){
			if(aux->id == searchId) break;
			aux = aux->proxObj;
		}
		if(aux != NULL){
			return aux;
		}else{
			printf("\n[Registro não encontrado]\n");	
		}		
	}
}

bool deleteAllPilha(Pilha *pilha){
	if(!emptyPilha(pilha)){
		ObjetoP *aux = pilha->topo;
		while (aux!=NULL){
			pilha->topo = aux->proxObj;
			free(aux);
			aux = pilha->topo;
		}
	}
	pilha = NULL;
	return true;
}
