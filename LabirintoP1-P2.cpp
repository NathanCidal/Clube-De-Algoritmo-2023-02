#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <windows.h>
#include <conio.h>

using namespace std;

struct Nodo{
	bool right;
	bool left;
	bool up;
	bool down;

	int x;
	int y;
	Nodo * next;

	Nodo(int x, int y){
		this->x = x;
		this->y = y;

		next = nullptr;
		right = false;
		left = false;
		up = false;
		down = false;
	}
};

class StackLab{
	private:
		Nodo * stack;
	
	public:
		StackLab(){
			stack = nullptr;
		}
		~StackLab(){
			while(stack != nullptr){
				Nodo * aux = stack;
				stack = stack->next;
				delete aux;
			}
		}

		void setRight(){
			stack->right = true;
		}
		void setLeft(){
			stack->left = true;
		}
		void setDown(){
			stack->down = true;
		}
		void setUp(){
			stack->up = true;
		}

		bool getRight()const{
			return stack->right;
		}

		bool getLeft()const{
			return stack->left;
		}

		bool getUp() const{
			return stack->up;
		}

		bool getDown() const{
			return stack->down;
		}

		
		
		bool isEmpty()const{
			if(stack == nullptr) return true;
			return false;
		}
		
		bool allOptions()const{
			if((stack->right == true) && (stack->left == true) && (stack->up == true) && (stack->down == true)) return true;
			return false;
 		}

		void push(Nodo * aux){
			if(stack == nullptr){
				stack = aux;
			}else{
				aux->next = stack;
				stack = aux;
			}
		}

		bool remove(){
			if(stack == nullptr) return false;
			
			Nodo * aux = stack;
			stack = stack->next;
			delete aux;

			return true;
		}

		bool getPos(int * a,int * b){
			if(stack == nullptr){
				*a = 0;
				*b = 0;
				return false;
			}

			*a = stack->x;
			*b = stack->y;
			return true;
		}

		bool jaPassou()const{
			int xA = stack->x;
			int yA = stack->y;

			if(stack->next == nullptr) return false;
			
			Nodo * passa = stack->next;

			while(passa != nullptr){
				if(passa->x == xA && passa->y == yA){
					delete passa;
					return true;
				}
				passa = passa->next;
			}

			delete passa;
			return false;

		}
};

int main(){

	int largura = 0;
	int altura = 0;

	ifstream arq;
	arq.open("input.txt", ios::in);

	if(arq.is_open() == false) return 1;

	char labirinto[1000][1000];
	string auxiliar;

	while(getline(arq,auxiliar)){
		//cout << auxiliar;

		for(int i = 0; i < auxiliar.length(); i++){
			largura = auxiliar.length();
			labirinto[altura][i] = auxiliar[i];
		}
		altura++;
	}

	arq.close();

	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hc, 0x07);		Bota na cor padrão
	//SetConsoleTextAttribute(hc, 0x02);

	for(int i = 0; i < altura; i++){
		for(int j = 0; j < largura; j++){
			cout << labirinto[i][j];
		}
		cout << endl;
	}

	int pontoXini = 0;
	int pontoYini = 0;
	
	StackLab * lab = new StackLab();
	bool achouFim = false;
	
	Nodo * auxInicial;
	auxInicial = new Nodo(pontoXini,pontoYini);
	
	lab->push(auxInicial);

	int xVerify;
	int yVerify;
	
	while(true){
		if(!lab->isEmpty()){
			
			lab->getPos(&xVerify, &yVerify);
			//cout << "[posY] :" << yVerify << " [posX]: " << xVerify << " Lab[" << yVerify << "][" << xVerify << "]: " << labirinto[yVerify][xVerify] << endl;

			//Mapa é tipo:	lab[altura][largura], ou lab[y][x];

			if(labirinto[yVerify][xVerify] == 'F'){
				achouFim = true;
				break;
			}			

			if(labirinto[yVerify][xVerify] == '#' || labirinto[yVerify][xVerify] != '.' && labirinto[yVerify][xVerify] != 'F' || lab->allOptions() == true || lab->jaPassou() == true){
				lab->remove();
				continue;
			}

			Nodo * aux = nullptr;
			if(lab->getRight() == false){
				aux = new Nodo(xVerify + 1, yVerify);
				aux->left = true;
				lab->setRight();
				lab->push(aux);
				continue;
			}

			if(lab->getUp() == false){
				aux = new Nodo(xVerify, yVerify + 1);
				aux->down = true;
				lab->setUp();
				lab->push(aux);
				continue;
			}

			if(lab->getLeft() == false){
				aux = new Nodo(xVerify - 1, yVerify);
				aux->right = true;
				lab->setLeft();
				lab->push(aux);
				continue;
			}

			if(lab->getDown() == false){
				aux = new Nodo(xVerify, yVerify - 1);
				aux->up = true;
				lab->setDown();
				lab->push(aux);
				continue;
			}
		}else{
			break;
		}
	}

	cout << endl << endl;

	int contador = 0;

	while(lab->isEmpty() == false){
		lab->getPos(&xVerify, &yVerify);
		contador++;
		labirinto[yVerify][xVerify] = 'X';
		lab->remove();
	}

	for(int i = 0; i < altura; i++){
		for(int j = 0; j < largura; j++){

			if(labirinto[i][j] == 'X'){
				SetConsoleTextAttribute(hc, 0x0B);
				cout << labirinto[i][j];
			}else{
				if(labirinto[i][j] == '.'){
					SetConsoleTextAttribute(hc, 0x00);
					cout << labirinto[i][j];
				}else{
					SetConsoleTextAttribute(hc, 0x08);
					cout << labirinto[i][j];
				}	
			}

			SetConsoleTextAttribute(hc, 0x07);

		}
		cout << endl;
	}

	SetConsoleTextAttribute(hc, 0x07);
	cout << "Passos: " << contador - 1 << endl;



	return 0;
}
