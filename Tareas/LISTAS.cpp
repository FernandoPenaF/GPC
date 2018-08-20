#include <iostream>
#include <cstdlib>
using std::cout;
using std::cin;
using std::malloc;
using std::free;

typedef struct list_int {
	int n;
	struct list_int *ptr;
} LISTA;

LISTA *init_list, *aux, *e;
int Elems = 1;


int main() {


	cout << "Dar 5 elementos ordenados a la lista\n";
	e = (LISTA*) malloc(sizeof(LISTA));
	cout << "Elemento " << Elems << "  ";
	cin >> e->n;
	e->ptr = NULL;
	aux = e;
	init_list = e;
	Elems++;
	while (Elems <= 5) {
		e = (LISTA*) malloc(sizeof(LISTA));
		cout << "Elemento " << Elems << "  ";
		cin >> e->n;
		aux->ptr = e;
		e->ptr = NULL;
		aux = e;
		Elems++;
	}
	cout << "Los valores son: \n";
	aux = init_list;
	while (aux != NULL) {
		cout << aux->n << "\n";
		aux = aux->ptr;
	}
	cin.get();
	cin.get();
	return 0;
}


