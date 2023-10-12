#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Queue{
	private:
		int elementos;
		int maxElementos;
		int * queue;
	public:
		Queue(int mxzSize){
			elementos = 0;
			maxElementos = mxzSize;
			queue = new int[maxElementos];

			for(int i = 0; i < maxElementos; i++){
				queue[i] = 0;
			}
		}

		~Queue(){
			delete[] queue;
			elementos = 0;
			maxElementos = 0;
		}

		bool isEmpty() const{
			if(elementos == 0) return true;
			return false;		
		}

		bool isFull() const{
			if(elementos >= maxElementos) return true;
			return false;
		}

		int peekInicio() const{
			if(isEmpty()) return 0;
			return queue[0];
		}

		bool adiciona(int e){
			if(isFull() == false){
				queue[elementos] = e;
				elementos++;
				return true;
			}

			return false;
		}

		int removeInicio(){
			//Remove e coloca no e;
			if(isEmpty() == false){
				int e = queue[0];
				
				elementos--;

				for(int i = 0; i < elementos; i++){
					queue[i] = queue[i+1];
				}

				return e;
			}

			return 0;
		}
	
		int getSize() const {
			return elementos;
		}

		int getMaxSize() const{
			return maxElementos;
		}

		string str() const{
			stringstream ss;
			ss << "| ";
			for(int i = 0; i < elementos; i++){
				ss << queue[i] << " | ";
			}			

			for(int i = elementos; i < maxElementos; i++){
				ss << " | ";
			}

			ss << endl;
			return ss.str();
		}
};

int main(){

	ifstream arq;
	arq.open("input.txt", ios::in);
	if(!arq.is_open()){
		cerr << "> ERRO AO ABRIR ARQUIVO" << endl;
		return 1;
	}


	Queue * lista;
	Queue * lista2;

	lista = new Queue(300);
	lista2 = new Queue(300);

	string cabecalho;
	string auxiliar;

	int contador = 1;

	getline(arq, cabecalho);

	while(getline(arq, auxiliar) || !arq.eof()){
		cout << auxiliar << endl;

		if(auxiliar.empty()){
			contador++;
			getline(arq, cabecalho);
		}else{
			if(contador == 1){
				lista->adiciona(stoi(auxiliar));
			}

			if(contador == 2){
				lista2->adiciona(stoi(auxiliar));
			}
		}
	}

	arq.close();

	bool p1G = false;

	while(1){
		if(lista->peekInicio() > lista2->peekInicio()){
			lista->adiciona(lista->removeInicio());
			lista->adiciona(lista2->removeInicio());

			if(lista2->isEmpty()){
				cout << "Player 1 ganhou" << endl;
				p1G = true;
				break;
			}
		}else{
			if(lista->peekInicio() < lista2->peekInicio()){
				lista2->adiciona(lista2->removeInicio());
				lista2->adiciona(lista->removeInicio());
				
				if(lista->isEmpty()){
					cout << "Player 2 ganhou" << endl;
					break;
				}	
			}
		}
	}
	
	cout << lista->str() << endl;
	cout << lista2->str() << endl;

	cout << "Hora da pontuacao: " << endl;
	int somador = 0;
	
	if(!p1G){
		for(int i = 0; i < lista2->getMaxSize(); i++){
			somador += (lista2->peekInicio() * lista2->getSize());
			lista2->removeInicio();
		}
	}else{
		for(int i = 0; i < lista->getMaxSize(); i++){
			somador += (lista->peekInicio() * lista->getSize());
			lista->removeInicio();
		}
	}

	if(p1G) cout << "Pontuacao do P1 que ganhou: ";
	else cout << "Pontuacao do P2 que ganhou: ";

	cout << somador << endl;

	return 0;
}
