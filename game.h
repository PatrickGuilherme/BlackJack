/*======================================================= 
Descrição: Contem todas as funções relacionadas a execução do jogo
=======================================================*/

#include "pilhaDeCartas.h"
#include "infoJogador.h"

//Variaveis globais
float valorAposta = 0;
int chequeDeUm = 0;
int suportePrint = 0;
int suportePrintDiller = 0;
bool parar = false;
Pilha *cartasPlayer = createPilha();
Pilha *cartasMain = createPilha();
Pilha *cartasDiller = createPilha();

//Insert das cartas da pilha principal
Pilha* pilhaMainCartas(){
	Carta carta;
	srand(time(NULL));
	int cartas[52];
	for(int i = 0; i < 52; i++)
	{
		cartas[i]=0;
	}
	for(int i = 0; i < 52; i++)
	{
		cartas[i] = rand() %13;
		if(cartas[i] == 0) cartas[i]++;
		while(true)
		{
			int aux = 0;
			for(int j = 0; j < 52; j++)
			{
				if(cartas[i] == cartas[j]) aux++;
			}
			if(aux > 4 && cartas[i]!=10)
			{
				cartas[i]++;
				if(cartas[i] > 10)
				{
					cartas[i] = 1;
				}
			}
			else if(aux>16 && cartas[i]==10)
			{
				cartas[i]++;
				if(cartas[i] > 13)
				{
					cartas[i] = 1;
				}
			}
			else 
			{
				if(cartas[i]>10) cartas[i]=10;
				break;	
			}
		}
	}
	
	for(int i = 51; i >= 0; i--)
	{
		carta.valorCarta = cartas[i];
		empilhar(cartasMain, carta);
	}
	
	return cartasMain;
}

//Insert inicial das cartas da pilha do jogador
Pilha* pilhaJogador(){
    ObjetoP *op;
    Carta infoP;
    int index;
	for(int i = 0; i<2 ;i++ )
	{
		index = sizePilha(cartasMain);
		op = selectWherePilha(cartasMain, index);
		infoP = op->dados;
		if(chequeDeUm != 1) chequeDeUm = infoP.valorCarta;
		desempilhar(cartasMain, &infoP);
		idAi = i + 1;
		empilhar(cartasPlayer, infoP);
	}
	idAi=1;
	return cartasPlayer;
}

//Sacar cartas para o player
void sacarPilhaMainPlayer(){
	ObjetoP *op;
    Carta infoP;
    int o = sizePilha(cartasMain);
    op = selectWherePilha(cartasMain, o);
	infoP = op ->dados;
	desempilhar(cartasMain, &infoP);
	idAi = 3 + suportePrint;
    empilhar(cartasPlayer, infoP);
    suportePrint++;
}

//Sacar cartas para o diller
void sacarPilhaMainDiller(){
	ObjetoP *op;
    Carta infoP;
    int o = sizePilha(cartasMain);
    op = selectWherePilha(cartasMain, o);
	infoP = op ->dados;
	desempilhar(cartasMain, &infoP);
	idAi = 2 + suportePrintDiller;
    empilhar(cartasDiller, infoP);
    suportePrintDiller++;
}

//Insert inicial das cartas da pilha do diller
Pilha* pilhaDiller(){
    ObjetoP *op;
    Carta infoP;
    int index;
	index = sizePilha(cartasMain);
	op = selectWherePilha(cartasMain, index);
	infoP = op->dados;
	desempilhar(cartasMain, &infoP);
	idAi = 1;
	empilhar(cartasDiller, infoP);
	return cartasDiller;
}

//Inserção do valor de aposta do jogador
bool apostar(){
	system("cls");	
	char msgErro[2000];
	strcpy(msgErro,"");

	if(jogador.dinheiro >=50){
		int  opcAposta;
		while(valorAposta <= 0){
			system("cls");	
			printf("-------------------\n");
			printf("   A P O S T A R   \n");
			printf("-------------------\n");
			printf("[1] R$50,00\n");
			printf("[2] R$100,00\n");
			printf("[3] R$300,00\n");
			printf("[4] R$500,00\n");
			printf("[5] R$1000,00\n");
			printf("[6] Apostar tudo\n");
			printf("-------------------\n");
			printf("Carteira: R$%.2f\n",jogador.dinheiro);
			printf("-------------------\n");
			printf("\n\nSelecione o valor da aposta: ");
			scanf("%d",&opcAposta);
			
			switch(opcAposta){
				case 1:
					if(jogador.dinheiro >= 50){
						valorAposta = 50;
						jogador.dinheiro -= 50;
					}else{
						strcpy(msgErro,"\n[Saldo insuficiente para a aposta]\n");
					}
				break;
				case 2:
					if(jogador.dinheiro >= 100){
						valorAposta = 100;
						jogador.dinheiro -= 100;
					}else{
						strcpy(msgErro,"\n[Saldo insuficiente para a aposta]\n");
					}
				break;
				case 3:
					if(jogador.dinheiro >= 300){
						valorAposta = 300;
						jogador.dinheiro -= 300;
					}else{
						strcpy(msgErro,"\n[Saldo insuficiente para a aposta]\n");
					}
				break;				
				case 4:
					if(jogador.dinheiro >= 500){
						valorAposta = 500;
						jogador.dinheiro -= 500;
					}else{
						strcpy(msgErro,"\n[Saldo insuficiente para a aposta]\n");
					}
				break;
				case 5:
					if(jogador.dinheiro >= 1000){
						valorAposta = 1000;
						jogador.dinheiro -= 1000;
					}else{
						strcpy(msgErro,"\n[Saldo insuficiente para a aposta]\n");
					}
				break;
				case 6:
					valorAposta = jogador.dinheiro;
					jogador.dinheiro = 0;
				break;																				
				default:
					strcpy(msgErro,"\n[Opção selecionada é inválida]\n");
				break;				
			}
			//Veririca se ele apostou	
			if(valorAposta <= 0){
				printf("%s",msgErro);
				system("pause");
			}
		}
		return true;	
	}
	strcpy(msgErro,"\n[Saldo insuficiente para fazer apostas]\n");
	printf("%s",msgErro);
	return false;
}

//Definição do vencedor do jogo (diller ou jogador)
int vencedor(){
	if(sizePilha(cartasPlayer) > 0 && sizePilha(cartasDiller) > 0){
		//[1] - jogador
		//[2] - diller
		
		int vencedor = 0;
		int pPlayer = somaAllPilha(cartasPlayer);
		int pDiller = somaAllPilha(cartasDiller);
		
		//empate de 21
		if(pDiller == 21 && pPlayer == 21){
			printf("\n[Diller Wins!!]\n");			
			vencedor = 2;
		}
		//diller fez 21
		else if(pDiller == 21 && pPlayer != 21){
			printf("\n[Diller Wins!!]\n");
			vencedor = 2;
		}
		//jogador fez 21
		else if(pPlayer == 21 && pDiller != 21){
			printf("\n[%s Wins!!]\n",jogador.nome);
			vencedor = 1;
		}
		//jogador passou de 21
		else if(pPlayer > 21){
			printf("\n[Diller Wins!!]\n");
			vencedor = 2;
		}
		//diller passou de 21
		else if(pDiller > 21){
			printf("\n[%s Wins!!]\n",jogador.nome);
			vencedor = 1;
		}
		//jogador empatou com o diller sem ser com 21
		else if(pDiller == pPlayer){
			printf("\n[Diller Wins!!]\n");			
			vencedor = 2;
		}
		//jogador fez mais pontos
		else if(pPlayer > pDiller){
			printf("\n[%s Wins!!]\n",jogador.nome);
			vencedor = 1;
		}
		//Diller fez mais pontos
		else if(pDiller > pPlayer){
			printf("\n[Diller Wins!!]\n");
			vencedor = 2;
		}
		
		//Premiação em dinheiro
		if(vencedor == 1){
			jogador.dinheiro += valorAposta*2;//inicialmente ele aposta este valor descontando do dinheiro dele, se ele ganha ele recupera o que foi descontado inicialmente e ganha a mais o valor da aposta
		}
		return vencedor; 
	}
	return -1;
}

//Centralizar texto na tela
centerText(char *s){
	int tam = strlen(s);
	int loop = (505 - tam)/2;
	int i;
	for(i = 0; i < loop; i++){	
		printf(" ");
	}
	printf("%s",s);
}

//Arte digital da policia
polica(){
	system("cls");
	centerText("\x1b[1m" "                      ________________                           \n"  );
	centerText("\x1b[1m" "                      \\      __      /        __                \n" );
	centerText("\x1b[1m" "                       \\_____()_____/        /  )               \n"  );
	centerText("\x1b[1m" "                       '============`       /  /                 \n"  );
	centerText("\x1b[1m" "                        #---\\  /---#       /  /                 \n"  );
	centerText("\x1b[1m" "                       (# @\\| |/@  #)     /  /                  \n"  );
	centerText("\x1b[1m" "                        \\   (_)   /      /  /                   \n"  );
	centerText("\x1b[1m" "                        |\\ '---` /|     /  /                    \n"  );
	centerText("\x1b[1m" "                _______/ \\_____// \\____/ o_|                   \n"  );
	centerText("\x1b[1m" "               /       \\  /     \\  /  / o_|                    \n"  );
	centerText("\x1b[1m" "              / |           o|       / o_| \\                    \n"  );
	centerText("\x1b[1m" "             /  |  _____     |      / /   \\ \\                  \n"  );
	centerText("\x1b[1m" "            /   |  |===|    o|     / /\\    \\ \\                \n"  );
	centerText("\x1b[1m" "           |    |   \\@/      |    / /  \\    \\ \\              \n"  );
	centerText("\x1b[1m" "           |    |___________o|__/----)  \\    \\/\\              \n"  );
	centerText("\x1b[1m" "           |    '              ||  --)   \\     /                \n"  );
	centerText("\x1b[1m" "           |___________________||  --)  | \\   /                 \n"  );
	centerText("\x1b[1m" "                |           o|   ''''   |  \\_/                  \n"  );
	centerText("\x1b[1m" "                |            |          |                        \n"  );
	centerText("\x1b[1m" "                |            |          |                        \n"  );
	centerText("\x1b[1m" "                |            |          |                        \n"  );
	centerText("\x1b[1m" "                |            |          |                        \n" "\x1b[0m");
}

//Chamada da exibição da policia
void callPolicia(){
	int i = 0;
	while(i <=9){
		Beep(800,200);
		system("color 47");	
		polica();
		Sleep(90);
		system("color 17");
		polica();
		Sleep(90);		
		i++;
	}
	Beep(1000,500);
	centerText("\n\nVOCE FOI PRESO!!!");	
}

//Função de fugir do jogo e levar o dinheiro
void escape(){
	srand(time(NULL));
	int fuga = rand()%50;
	if(fuga == 25){
		jogador.dinheiro = 1000;
		printf("\n\n[VOCE ASSALTOU O CASSINO E ESCAPOU COM SUCESSO!]\n|Nome: %s\n|Dinheiro: %f",jogador.nome,jogador.dinheiro);
	}else{
		callPolicia();
	}
}
