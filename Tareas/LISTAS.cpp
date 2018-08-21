#include <iostream>
#include <cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::malloc;
using std::free;

typedef struct node {
	int n;
	struct node *ptr;
} LISTA;

LISTA *init_list, *aux, *e;
int Elems = 0;

void agregaOrdenado(int data){
	e = (LISTA*) malloc(sizeof(LISTA));
	e -> n = data;
	e -> ptr = NULL;

	if(init_list == NULL || init_list -> n >= data){
		e -> ptr = init_list;
		init_list = e;
	} else {
		aux = init_list;
		while(aux -> ptr != NULL && (aux -> ptr) -> n < data){
			aux = aux -> ptr;
		}
		e -> ptr = aux -> ptr;
		aux -> ptr = e;
	}
	Elems++;
}

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
	for (int i = 0; i < 5; i++){
		cout << "Elemento " << (Elems + 1) << "  ";
		cin >> num;
		agregaFinal(num);
	}

	cout << "Los valores son: \n";
	print();

	for (int i = 0; i < 5; i++){
		cout << "Elemento " << (Elems + 1) << "  ";
		cin >> num;
		agregaOrdenado(num);
		cout << "Los valores son: \n";
		print();
	}

	cin.get();
	return 0;
}


