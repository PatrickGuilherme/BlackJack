/*======================================================= 
Descrição: Contem dados dos usuários e manipula o arquivo
=======================================================*/

//Struct do jogador
typedef struct  {  
    char nome[50];  
    int idade;
	float dinheiro;  
}Jogador; 

//Variavel global do jogador
Jogador jogador;

//Cadastro de ususário
int cadastrarUsuario(){
	system("cls");
	printf("-------------------\n");
	printf(" C A D A S T R A R \n");
	printf("-------------------\n");
	printf("Insira seus dados para efetuar o cadastro\n");
	printf("|Nome: ");
	fflush(stdin);
	scanf("%[^\n]49s",jogador.nome);
	fflush(stdin);
	printf("|Idade: ");
	scanf("%d",&jogador.idade);
	fflush(stdin);		
	if(jogador.idade > 150){
		printf("\n[Idade invalida]\n");
		system("pause");
		return 0;
	}else if(jogador.idade < 18){
		printf("\n[Necessario ter mais de 18 anos]\n");
		system("pause");
		return 0;			
	}
	char confirm[4];
	printf("Criar conta? [SIM/NAO]\n");
	fflush(stdin);
	scanf("%[^\n]3s",confirm);
	if(strcmp(strupr(confirm),"SIM") == 0){
		jogador.dinheiro = 500;
		return 1;
	}
	return 0;
}

//Gravar os dados do usuario no arquivo
bool gravarDadosArquivo(){
	FILE *pontArq = fopen("dadosJogador.txt","a");
	if(pontArq == NULL){
		printf("\n[Erro ao abrir arquivo]\n");
		system("PAUSE");
		return 0;
	}
	fprintf(pontArq,"%s,%d,%.2f\n",jogador.nome,jogador.idade,jogador.dinheiro);
	fclose(pontArq);
	pontArq = NULL;
	free(pontArq);
	return true;
}

//Configurações de fullscream
void configuracoes(){
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

//Algoritmo de ordenação para o scoreboard
void Quick(Jogador *vetor, int inicio, int fim){
   float pivo;
   Jogador aux;
   int i, j, meio;
   i = inicio;
   j = fim;
   meio = (int) ((i + j) / 2);
   pivo = vetor[meio].dinheiro;
   
   do{
      while (vetor[i].dinheiro > pivo) i = i + 1;
      while (vetor[j].dinheiro < pivo) j = j - 1;
      if(i <= j){
         aux = vetor[i];
         vetor[i] = vetor[j];
         vetor[j] = aux;
         i = i + 1;
         j = j - 1;
      }
   }while(j > i);
   if(inicio < j) Quick(vetor, inicio, j);
   if(i < fim) Quick(vetor, i, fim);   
}

//Captura da quantidade de registros no arquivo
int qtdLinesFile(){
	FILE *pArq;//Ponteiro para aquivo
    pArq = fopen("dadosJogador.txt", "r");
    if(pArq == NULL){
    	printf("\n[Erro na abertura do arquivo]\n");
    	return 0;
    }
    char buf[1024];
	int qtdLine = 0;
    while(fgets(buf, sizeof buf, pArq) !=NULL){
    	qtdLine++;
    }
    fclose(pArq);
    pArq = NULL;
    free(pArq);
    return qtdLine;
}

//Rank de pontuação dos jogadores (maior -> menor)
void scoreboard(){
	FILE *pFile;
    int i=0, j=0, qtdPlayer; 
    qtdPlayer = qtdLinesFile();
    Jogador players[qtdPlayer];
    char buf[1024];

	//Verificação de registros no arquivo
	if(qtdPlayer <=0){
		printf("\n[Sem registros]\n");
		system("pause");
		return;	
	} 
    
	pFile = fopen("dadosJogador.txt", "r");

    //testando se o arquivo foi realmente criado
    if(pFile == NULL){
    	printf("\n[Erro na abertura do arquivo]\n");
        system("pause");
		return;
    }
	bool isString = true;
	bool isInt = true;
	bool isFloat = true;
	
	//lendo linhas do arquivo
    while(fgets(buf, sizeof buf, pFile) !=NULL){
    	
   		//token para seprar os dados vindos do arquivo por (,)
		char *token = strtok(buf,",");
		isString = true;
		isInt = true;
		isFloat = true;
		
		
		while(token != NULL){
			if(isString){//captura do nome
				strcpy(players[i].nome,token);
				isString = false;
			}else if(isInt){//captura da idade
				players[i].idade = atoi(token);
				isInt = false;
			}else if(isFloat){//captura do dinheiro
				players[i].dinheiro = atof(token);
				break;
			}
			//Captura o dado até encontrar virgula
			token = strtok(NULL,",");
		}i++;
    }
    //Ordenar por quick sort
    Quick(players,0,qtdPlayer - 1);
	
	//Printando dados dos jogadores ja ordenados
    printf("=====================\n");
    printf("        R A N K      \n");
    printf("=====================\n");
    for(j = 0; j < qtdPlayer; j++){
		printf("|Nome:%s\n|Idade:%d\n|Dinheiro:%.2f\n\n", players[j].nome, players[j].idade, players [j].dinheiro);
	}
    printf("=====================\n");
    printf("Total: %d\n",qtdPlayer);
}
