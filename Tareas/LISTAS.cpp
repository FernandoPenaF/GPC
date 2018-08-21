#include <iostream>
#include <cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::malloc;
using std::free;

typedef struct list_int {
	int n;
	struct list_int *ptr;
} LISTA;

LISTA *init_list, *aux, *e;
int Elems = 0;

void agregaFinal(int data){
	e = (LISTA*) malloc(sizeof(LISTA));
	e -> n = data;
	e -> ptr = NULL;

	if(init_list == NULL){
		init_list = e;
	} else {
		aux = init_list;

		while(aux -> ptr != NULL){
			aux = aux -> ptr;
		}
		aux -> ptr = e;
	}
	Elems++;
}

void print(){
	aux = init_list;

	while(aux != NULL){
		cout << aux -> n << endl;
		aux = aux -> ptr;
	}
}


int main() {
	int num;

	cout << "Dar 5 elementos ordenados a la lista\n";
	cout << "Elemento " << (Elems + 1) << "  ";
	cin >> num;
	agregaFinal(num);

	while (Elems < 5) {
		cout << "Elemento " << (Elems + 1) << "  ";
		cin >> num;
		agregaFinal(num);
	}
	cout << "Los valores son: \n";
	print();
	cin.get();
	cin.get();
	return 0;
}


