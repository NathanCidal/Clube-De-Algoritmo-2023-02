#include <iostream>
#include <string>

using namespace std;

int main(){
	int * p1Baralho = new int[51];
	int * p2Baralho = new int[51];

	for(int i = 0; i < 50; i++){
		p1Baralho[i] = 0;
		p2Baralho[i] = 0;
	}

	p1Baralho[0] = 9;
	p1Baralho[1] = 2;
	p1Baralho[2] = 6;
	p1Baralho[3] = 3;
	p1Baralho[4] = 1;

	p2Baralho[0] = 5;
	p2Baralho[1] = 8;
	p2Baralho[2] = 4;
	p2Baralho[3] = 7;
	p2Baralho[4] = 10;
	
    int p1Tam = 5;
	int p2Tam = 5;
	
	int conta = 0;
	while(conta < 20){
	    conta++;
	    cout << p1Baralho[0] << " " << p2Baralho[0] << endl;
	    cout << endl;
	    
		if(p1Baralho[0] > p2Baralho[0]){	
			int auxiliar1 = p1Baralho[0];
			int auxiliar2 = p2Baralho[0];

			for(int i = 0; i < p1Tam - 1; i++){
				p1Baralho[i] = p1Baralho[i+1];
				cout << p1Baralho[i] << " ";
			}
			cout << endl;

            
			for(int i = 0; i < p2Tam - 1; i++){
				p2Baralho[i] = p2Baralho[i+1];
				cout << p2Baralho[i] << " ";
			}
			cout << endl;

				p1Baralho[p1Tam] = auxiliar1;
				p1Tam++;
				p1Baralho[p1Tam] = auxiliar2;
				p1Tam++;
				p2Tam--;

				if(p2Tam == 0){
					cout << "P1 Ganhou" << endl;
				}
			
		}else{
		    cout << endl;
		    cout << endl;
			if(p1Baralho[0] < p2Baralho[0]){
	
				int auxiliar1 = p1Baralho[0];
				int auxiliar2 = p2Baralho[0];

				for(int i = 0; i < p1Tam - 1; i++){
				p1Baralho[i] = p1Baralho[i+1];
				cout << p1Baralho[i] << " ";
			}
			cout << endl;

			for(int i = 0; i < p2Tam - 1; i++){
				p2Baralho[i] = p2Baralho[i+1];
				cout << p2Baralho[i] << " ";
			}
			cout << endl;

				p2Baralho[p2Tam] = auxiliar2;
				p2Tam++;
				p2Baralho[p2Tam] = auxiliar1;
				p2Tam++;
				p1Tam--;


				if(p1Tam == 0){
					cout << "P2 Ganhou" << endl;
				}
			}
		}
	}
	
    return 0;
}  
