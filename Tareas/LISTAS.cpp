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

LISTA *init_list, *aux, *aux2, *e;
int Elems = 0;

bool estaVacia(){
	return init_list == NULL;
}

void agregaOrdenado(int data){
	e = (LISTA*) malloc(sizeof(LISTA));
	e -> n = data;
	e -> ptr = NULL;

	if(estaVacia() || init_list -> n >= data){
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

void elimina(int data){
	if(estaVacia()) {
		cout << "Lista vacía" << endl;
	} else {
		aux = init_list;

		if(aux -> n == data){
			init_list = init_list -> ptr;
			free(aux);
			Elems--;
		} else {
			while(aux != NULL && aux -> n != data){
				aux2 = aux;
				aux = aux -> ptr;
			}
			if(aux != NULL){
				aux2 -> ptr = aux -> ptr;
				free(aux);
				Elems--;
			} else {
				cout << "El elemento no está en la lista." << endl;
			}
		}
	}
}

void agregaFinal(int data){
	e = (LISTA*) malloc(sizeof(LISTA));
	e -> n = data;
	e -> ptr = NULL;

	if(estaVacia()){
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

void print(struct node *inicio){
	aux = inicio;

	while(aux != NULL){
		cout << aux -> n << endl;
		aux = aux -> ptr;
	}
}


int main() {
	int num;
	elimina(10);
	for (int i = 0; i < 5; i++){
		cout << "Agrega " << i + 1 << "  ";
		cin >> num;
		agregaOrdenado(num);
	}

	cout << Elems << " elementos en la lista. Los valores son:" << endl;
	print(init_list);

	for (int i = 0; i < 5; i++){
		cout << "Elimina " << i + 1 << "  ";
		cin >> num;
		elimina(num);
		cout << Elems << " elementos en la lista. Los valores son:" << endl;
		print(init_list);
	}

	cin.get();
	return 0;
}


