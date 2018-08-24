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
int numElems = 0;

struct node *creaNodo(int data){
	struct node *nuevo = (LISTA*) malloc(sizeof(LISTA));

	nuevo -> n = data;
	nuevo -> ptr = NULL;
	return nuevo;
}

bool estaVacia(){
	return init_list == NULL;
}

void agregaOrdenado(struct node *nuevo){
	if(estaVacia() || init_list -> n >= nuevo -> n){
		nuevo -> ptr = init_list;
		init_list = nuevo;
	} else {
		aux = init_list;
		while(aux -> ptr != NULL && (aux -> ptr) -> n < nuevo -> n){
			aux = aux -> ptr;
		}
		nuevo -> ptr = aux -> ptr;
		aux -> ptr = nuevo;
	}
	numElems++;
}

void elimina(int data){
	if(estaVacia()) {
		cout << "Lista vacía." << endl;
	} else {
		aux = init_list;

		if(aux -> n == data){
			init_list = init_list -> ptr;
			free(aux);
			numElems--;
		} else {
			while(aux != NULL && aux -> n != data){
				aux2 = aux;
				aux = aux -> ptr;
			}
			if(aux != NULL){
				aux2 -> ptr = aux -> ptr;
				free(aux);
				numElems--;
			} else {
				cout << data << " no está en la lista." << endl;
			}
		}
	}
}

void agregaFinal(struct node *nuevo){
	if(estaVacia()){
		init_list = nuevo;
	} else {
		aux = init_list;

		while(aux -> ptr != NULL){
			aux = aux -> ptr;
		}
		aux -> ptr = nuevo;
	}
	numElems++;
}

void print(struct node *inicio){
	if(estaVacia()){
		cout << "Lista vacía." << endl;
	} else {
		cout << numElems << " elementos en la lista. Los valores son:" << endl;

		aux = inicio;
		while(aux != NULL){
			cout << aux -> n << endl;
			aux = aux -> ptr;
		}
	}
}


int main() {
	int num;
	cout << "============Inicio del programa.=============" << endl;
	print(init_list);

	cout << "=========Se agregan 5 elementos ordenados a la lista.==========" << endl;
	for (int i = 0; i < 5; ++i){
		e = creaNodo(i * 5);
		agregaFinal(e);
	}
	print(init_list);

	cout << "==========El usuario puede añadir números.==========\n" << endl;
	for (int i = 0; i < 5; i++){
		cout << "Agrega " << i + 1 << "  ";
		cin >> num;
		e = creaNodo(num);
		agregaOrdenado(e);
	}

	print(init_list);

	cout << "===========El usuario puede eliminar números.==========\n" << endl;
	for (int i = 0; i < 5; i++){
		cout << "Elimina " << i + 1 << "  ";
		cin >> num;
		elimina(num);
	}

	print(init_list);

	cin.get();
	return 0;
}