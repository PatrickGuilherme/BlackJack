/*======================================================= 
Descrição: Arquivo execultavel do jogo
=======================================================*/

#include "mainimport.h"
#include "mesa.h"

using namespace std;

//Função de reiniciar o jogo
void resetGame(){
	valorAposta = 0;
	suportePrint = 0;
	suportePrintDiller = 0;
	chequeDeUm = 0;
	parar = false;
	idAi = 1;
	deleteAllPilha(cartasPlayer);
	deleteAllPilha(cartasPlayer);
	deleteAllPilha(cartasMain);
	deleteAllPilha(cartasDiller);	
	printarCartas = 0;
	printarCartasDiller = 0;
}


int main(){		
	//Configurações de display
	configuracoes();
	int opcMenu;
	
	//Cadastro do jogador no inicio
	if(cadastrarUsuario()){
		while(1){
			
			//Menu iniciar
			system("cls");
			printf("================\n");
			printf("     M E N U    \n");
			printf("================\n");
			printf("[1] Iniciar game\n");
			printf("[2] Rank\n");
			printf("[3] Carteira\n");
			printf("[4] Sair\n");
			printf("================\n");		
			printf("Selecione uma acao: ");
			scanf("%d",&opcMenu);
			if(opcMenu < 1 || opcMenu > 4){
				continue;
			}else if(opcMenu == 4){
				break;
			}else if(opcMenu == 2){
				system("cls");
				scoreboard();
				system("\npause");
				continue;
			}else if(opcMenu == 3){
				system("cls");
				printf("Dinheiro: %f\n",jogador.dinheiro);
				system("pause");
				continue;
			}
			system("cls");
			
			
			//hora da aposta
			apostar();
			
			//crição da pilha de cartas principal
			cartasMain = pilhaMainCartas();
			
			//criação da pilha de cartas do jogador
			pilhaJogador();	
			
			//criação da pilha de cartas do diller
			pilhaDiller();
			
			//exibição da mesa
			apresentarMesa();

			//Acesso as ações do player durante o jogo
			while(somaAllPilha(cartasPlayer) < 21)
			{
				char comando = getch();
				switch(comando)
				{
					case('1'):
						system("cls");
						sacarPilhaMainPlayer();
						printarCartas++;
						apresentarMesa();
						break;
					case('2'):
						parar = true;
						break;
					case('3'):
						system("cls");			
						sacarPilhaMainPlayer();
						printarCartas++;
						jogador.dinheiro -= valorAposta;
						valorAposta = valorAposta*2;
						apresentarMesa();
						parar = true;
						break;
					case('4'):
						escape();
						return 0;
						break;
				}
				if(parar == true) break;
			}
			
			//Função da jogada do diller
			if(somaAllPilha(cartasPlayer) < 21){
				while(somaAllPilha(cartasDiller) <= 16 && somaAllPilha(cartasDiller) < 21)
				{
					system("cls");
					sacarPilhaMainDiller();
					printarCartasDiller++;
					apresentarMesa();
					system("pause");
				}				
			}
			
			//Definição do vencedor e reinicio do jogo
			vencedor();
			system("pause");
			system("cls");
			resetGame();

			//Verificação de saldo para continuar o jogo
			if(jogador.dinheiro < 50){
				printf("\n[Saldo insuficiente para jogar]\n");
				system("pause");
				break;
			}
		}
		//gravar dados do jogador
		gravarDadosArquivo();	
	}
	return 0;
}
