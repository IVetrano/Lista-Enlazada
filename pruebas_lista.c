#include "lista.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>


static void prueba_lista_vacia(){
    lista_t* lista = lista_crear();
    print_test("Se pudo crear la lista", lista != NULL);
    print_test("La lista esta vacia al crearla", lista_esta_vacia(lista));
    print_test("La lista no tiene primer elemento al crearla", lista_ver_primero(lista) == NULL);
    print_test("La lista no tiene ultimo elemento al crearla", lista_ver_ultimo(lista) == NULL);
    print_test("El largo de la lista es 0 al crearla", lista_largo(lista) == 0);
    print_test("Al intentar borrar primero vacia devuelve NULL", lista_borrar_primero(lista) == NULL);
    lista_destruir(lista, NULL);
}

static void prueba_insertar_primero(){
	lista_t* lista = lista_crear();
	int a;
	print_test("Se pudo insertar un elemento al principio", lista_insertar_primero(lista, &a));
	print_test("Ahora la lista ya no esta vacia", !lista_esta_vacia(lista));
	print_test("Ahora el largo de la lista es 1", lista_largo(lista) == 1);
	print_test("Al ver primero recibo el elemento que inserte", lista_ver_primero(lista) == &a);
	print_test("Al ver ultimo recibo el mismo elemento", lista_ver_ultimo(lista) == &a);
	print_test("Al borrar primero recibo el mismo elemento", lista_borrar_primero(lista) == &a);
	print_test("Ahora la lista esta vacia", lista_esta_vacia(lista));
	print_test("Ahora el largo de la lista es 0", lista_largo(lista) == 0);
	lista_destruir(lista, NULL);
}

static void prueba_insertar_ultimo(){
	lista_t* lista = lista_crear();
	int a;
	print_test("Se pudo insertar un elemento al final", lista_insertar_ultimo(lista, &a));
	print_test("Ahora el largo de la lista es 1", lista_largo(lista) == 1);
	print_test("Al ver primero recibo el elemento que inserte", lista_ver_primero(lista) == &a);
	print_test("Al ver ultimo recibo el mismo elemento", lista_ver_ultimo(lista) == &a);
	print_test("Al borrar primero recibo el mismo elemento", lista_borrar_primero(lista) == &a);
	print_test("Ahora la lista esta vacia", lista_esta_vacia(lista));
	print_test("Ahora el largo de la lista es 0", lista_largo(lista) == 0);
	lista_destruir(lista, NULL);
}

static void prueba_volumen_invariante_al_principio(){
	//Pruebo insertando los elementos al principio
	lista_t* lista = lista_crear();
	int arr[1000];

	bool insertado = true;
	bool primero = true;
	bool ultimo = true;
	bool borrar = true;
	bool largo = true;

	for (int i = 0; i < 1000; i++){
		insertado &= lista_insertar_primero(lista, &arr[i]);
		primero &= lista_ver_primero(lista) == &arr[i];
		ultimo &= lista_ver_ultimo(lista) == &arr[0];
		largo &= lista_largo(lista) == i + 1;
	}

	print_test("Se pudieron insertar 1000 elementos al principio", insertado);
	print_test("Al ver primero las 1000 veces coincidio con el nuevo insertado", primero);
	print_test("Al ver ultimo las 1000 veces coincidio con el primer insertado", ultimo);
	print_test("El largo de la lista era correcto todas las veces", largo);

	primero = true;
	largo = true;

	for (int i = 999; i >= 0; i--){
		largo &= lista_largo(lista) == i + 1;
		primero &= lista_ver_primero(lista) == &arr[i];
		borrar &= lista_borrar_primero(lista) == &arr[i];
	}

	print_test("Al borrar los elementos se recibian en el orden correcto", borrar);
	print_test("Al ver primero mientras se borraban se recibien en el orden correcto", primero);
	print_test("Ahora la lista esta vacia", lista_esta_vacia(lista));
	print_test("El largo de la lista era correcto todas las veces", largo);

	
	lista_destruir(lista, NULL);

}

static void prueba_volumen_invariante_al_final(){
	//Pruebo insertando los elementos al final
	lista_t* lista = lista_crear();
	int arr[1000];

	bool insertado = true;
	bool primero = true;
	bool ultimo = true;
	bool borrar = true;
	bool largo = true;

	for (int i = 0; i < 1000; i++){
		insertado &= lista_insertar_ultimo(lista, &arr[i]);
		primero &= lista_ver_primero(lista) == &arr[0];
		ultimo &= lista_ver_ultimo(lista) == &arr[i];
		largo &= lista_largo(lista) == i + 1;
	}

	print_test("Se pudieron insertar 1000 elementos al final", insertado);
	print_test("Al ver ultimo las 1000 veces coincidio con el nuevo insertado", ultimo);
	print_test("Al ver primero las 1000 veces coincidio con el primer insertado", primero);
	print_test("El largo de la lista era correcto todas las veces", largo);

	primero = true;
	largo = true;

	for (int i = 0; i < 1000; i++){
		largo &= lista_largo(lista) == 1000 - i;
		primero &= lista_ver_primero(lista) == &arr[i];
		borrar &= lista_borrar_primero(lista) == &arr[i];
	}

	print_test("Al borrar los elementos se recibian en el orden correcto", borrar);
	print_test("Al ver primero mientras se borraban se recibien en el orden correcto", primero);
	print_test("Ahora la lista esta vacia", lista_esta_vacia(lista));
	print_test("El largo de la lista era correcto todas las veces", largo);

	lista_destruir(lista, NULL);
}

static void prueba_invariante(){
	lista_t* lista = lista_crear();
	int arr[3];

	print_test("Se pudo insertar el elemento A al principio", lista_insertar_primero(lista, &arr[0]));
	print_test("Ahora el primer elemento es A", lista_ver_primero(lista) == &arr[0]);
	print_test("Ahora el ultimo elemento es A", lista_ver_ultimo(lista) == &arr[0]);
	print_test("Ahora el largo de la lista es 1", lista_largo(lista) == 1);
	print_test("Se pudo insertar el elemento C al final", lista_insertar_ultimo(lista, &arr[2]));
	print_test("Ahora el ultimo elemento es C", lista_ver_ultimo(lista) == &arr[2]);
	print_test("El primer elemento sigue siendo A", lista_ver_primero(lista) == &arr[0]);
	print_test("Ahora el largo de la lista es 2", lista_largo(lista) == 2);
	print_test("Borrando el primer elemento recibo A", lista_borrar_primero(lista) == &arr[0]);
	print_test("Ahora el primer elemento es C", lista_ver_primero(lista) == &arr[2]);
	print_test("El ultimo elemento sigude siendo C", lista_ver_ultimo(lista) == &arr[2]);
	print_test("Ahora el largo de la lista es 1", lista_largo(lista) == 1);
	print_test("Se pudo insertar B al principio", lista_insertar_primero(lista, &arr[1]));
	print_test("Se pudo insertar A al principio", lista_insertar_primero(lista, &arr[0]));
	print_test("Ahora el primer elemento es A", lista_ver_primero(lista) == &arr[0]);
	print_test("El ultimo elemento sigue siendo C", lista_ver_ultimo(lista) == &arr[2]);
	print_test("Ahora el largo de la lista es 3", lista_largo(lista) == 3);
	print_test("Al borrar primero recibo A", lista_borrar_primero(lista) == &arr[0]);
	print_test("Al borrar primero recibo B", lista_borrar_primero(lista) == &arr[1]);
	print_test("Al borrar primero recibo C", lista_borrar_primero(lista) == &arr[2]);
	print_test("Ahora la lista esta vacia", lista_esta_vacia(lista));
	print_test("Ahora el largo de la lista es 0", lista_largo(lista) == 0);

	lista_destruir(lista, NULL);
}

static void insertar_NULL(){
	void* a = NULL;

	lista_t* lista = lista_crear();

	print_test("Se pudo insertar NULL al principio", lista_insertar_primero(lista, &a));
	print_test("Ahora el largo de la lista es 1", lista_largo(lista) == 1);
	print_test("La lista no esta vacia", !lista_esta_vacia(lista));
	print_test("Al ver primero recibo el puntero a NULL que inserte", lista_ver_primero(lista) == &a);
	print_test("Al borrar primero recibo el puntero a NULL que inserte", lista_borrar_primero(lista) == &a);

	lista_destruir(lista, NULL);
}

static void prueba_destruir_vacia_sin_funcion(){
	//Destruyo una vacia sin funcion para destruir elementos
	lista_t* lista = lista_crear();
	lista_destruir(lista, NULL);
	print_test("Se destruyo una lista vacia", true);
}

static void prueba_destruir_no_vacia_sin_funcion(){
	//Destruyo una con elementos pero sin funcion para destruir elementos
	bool insertar = true;
	int arreglo_1[3];
	lista_t* lista = lista_crear();

	for (int i = 0; i < 3; i++){
		insertar &= lista_insertar_ultimo(lista, &arreglo_1[i]);
	}
	print_test("Se pudieron insertar 3 elementos", insertar);
	lista_destruir(lista, NULL);
	print_test("Se destruyo una lista con elementos pero sin funcion para destruirlos", true);
}

static void prueba_destruir_vacia_con_funcion(){
	//Destruyo una sin elementos pero con funcion para destruir los elementos
	lista_t* lista = lista_crear();
	lista_destruir(lista, free);
	print_test("Se destruyo una lista sin elementos pero con funcion para destruirlos", true);
}

static void prueba_destruir_no_vacia_con_funcion(){
	//Destruyo una con elementos y con funcion para destruirlos.
	//Uso memoria dinamica => le paso a lista_destruir() "free()" como funcion
	//de destruccion de datos.

	bool insertar = true;

	int* arreglo_2[10];

	for (int i = 0; i < 10; i++){
		arreglo_2[i] = malloc(sizeof(int));
	}

	lista_t* lista = lista_crear();

	for(int i = 0; i < 10; i++){
		insertar &= lista_insertar_ultimo(lista, arreglo_2[i]);
	}
	print_test("Se pudieron insertar 10 elementos al final", insertar);
	lista_destruir(lista, free);
	print_test("Se destruyo una lista con elementos y con funcion para destruirlos", true);
}

bool suma_total(void* dato, void* extra){
	*(int*) extra += *(int*) dato;
	return true;
}

bool false_en_3(void* dato, void* extra){
	*(int*) extra = *(int*) dato;
	if (*(int*) dato == 3) return false;
	return true;
}

static void prueba_iterador_interno(){
	lista_t* lista = lista_crear();

	int arreglo[] = {1, 2, 3, 4, 5};
	bool insertar = true;

	for (int i = 0; i < 5; i++){
		insertar &= lista_insertar_ultimo(lista, &arreglo[i]);
	}
	print_test("Se pudieron insertar 5 elementos", insertar);


	//Pruebo con funcion que recorre todos los elementos
	int sumatoria = 0;
	lista_iterar(lista, suma_total, &sumatoria);
	//La sumatoria deberia dar 15
	print_test("Al sumar todos los elementos con el iterador interno el resultado es correcto", sumatoria == 15);

	//Pruebo con funcion que recorre hasta que el dato es 3
	int x;
	lista_iterar(lista, false_en_3, &x);
	print_test("El iterador deja de iterar cuando la funcion devuelve false", x == 3);
	lista_destruir(lista, NULL);
}

static void prueba_iterador_externo(){
	lista_t* lista = lista_crear();

	int arreglo[] = {1, 2, 3, 4, 5};
	bool insertar = true;

	for (int i = 0; i < 5; i++){
		insertar &= lista_insertar_ultimo(lista, &arreglo[i]);
	}
	print_test("Se pudieron insertar elementos del 1 al 5", insertar);

	lista_iter_t* iter = lista_iter_crear(lista);

	print_test("Se pudo crear un iterador", iter != NULL);
	print_test("El iterador esta al principio al ser creado", lista_iter_ver_actual(iter) == &arreglo[0]);
	print_test("Al ser creado (si la lista tiene elementos) el iterador no esta al final", !lista_iter_al_final(iter));

	int nuevo = 45;

	print_test("Se pudo insertar un nuevo elemento al principio", lista_iter_insertar(iter, &nuevo));
	print_test("El iterador se encuentra posicionado en el elemento agregado", lista_iter_ver_actual(iter) == &nuevo);
	print_test("El primer elemento de la lista cambio correctamente", lista_ver_primero(lista) == &nuevo);
	print_test("Al borrar elemento recibo el elemento insertado", lista_iter_borrar(iter) == &nuevo);
	print_test("Ahora el primer elemento volvio a ser el antiguo", lista_ver_primero(lista) == &arreglo[0]);
	print_test("El iterador esta ahora posicionado en ese elemento", lista_iter_ver_actual(iter) == &arreglo[0]);

	//Itero hasta que el dato sea 3
	int i = 0;
	bool invariante = true;
	bool avanzo = true;
	while (lista_iter_ver_actual(iter) != &arreglo[2]){
		invariante &= lista_iter_ver_actual(iter) == &arreglo[i];
		avanzo &= lista_iter_avanzar(iter);
		i++;
	}

	print_test("Se avanzo correctamente hasta el 3", lista_iter_ver_actual(iter) == &arreglo[2]);
	print_test("El actual fue siempre correspondiente", invariante);
	print_test("Avanzo dio true siempre", avanzo);
	print_test("Se pudo insertar un elemento entre el 2 y el 3", lista_iter_insertar(iter, &nuevo));
	print_test("El iterador esta posicionado en el nuevo elemento", lista_iter_ver_actual(iter) == &nuevo);
	print_test("Se pudo avanzar", lista_iter_avanzar(iter));
	print_test("Ahora el iterador esta psicionado en el 3", lista_iter_ver_actual(iter) == &arreglo[2]);

	//Itero hasta el final
	invariante = true;
	avanzo = true;
	while (!lista_iter_al_final(iter)){
		invariante &= lista_iter_ver_actual(iter) == &arreglo[i];
		avanzo &= lista_iter_avanzar(iter);
		i++;
	}

	print_test("El actual fue siempre correspondiente", invariante);
	print_test("Avanzo dio true siempre", avanzo);
	print_test("iter_al_final devuelve true cuando estoy al final", lista_iter_al_final(iter));
	print_test("iter_avanzar invalida cuando se esta al final", !lista_iter_avanzar(iter));
	print_test("Se pudo agregar un elemento al final", lista_iter_insertar(iter, &nuevo));
	print_test("Ahora el ultimo elemento de la lista es el nuevo elemento", lista_ver_ultimo(lista) == &nuevo);
	print_test("El iterador se encuentra posicionado en el elemento agregado", lista_iter_ver_actual(iter) == &nuevo);
	print_test("Al borrar elemento recibo el elemento agregado", lista_iter_borrar(iter) == &nuevo);
	print_test("Ahora el ultimo elemento volvio a ser el antiguo", lista_ver_ultimo(lista) == &arreglo[4]);

	lista_iter_destruir(iter);

	iter = lista_iter_crear(lista);

	print_test("Se pudo crear un nuevo iterador", iter != NULL);
	print_test("El nuevo iterador esta al principio al ser creado", lista_iter_ver_actual(iter) == &arreglo[0]);


	//Avanzo hasta el 2 para ver si el siguiente elemento es el nuevo elemento que agregue antes
	i = 0;
	invariante = true;
	avanzo = true;
	while (lista_iter_ver_actual(iter) != &arreglo[1]){
		invariante &= lista_iter_ver_actual(iter) == &arreglo[i];
		avanzo &= lista_iter_avanzar(iter);
		i++;
	}

	print_test("Se pudo avanzar despues del 2", lista_iter_avanzar(iter));
	print_test("El actual fue siempre correspondiente", invariante);
	print_test("Avanzo dio true siempre", avanzo);
	print_test("Despues del 2 esta el nuevo elemento agregado antes", lista_iter_ver_actual(iter) == &nuevo);
	print_test("Al borrar recibo el nuevo elemento", lista_iter_borrar(iter) == &nuevo);

	lista_iter_destruir(iter);
	lista_destruir(lista, NULL);

}



void pruebas_lista_estudiante(void){
	prueba_lista_vacia();
	prueba_insertar_primero();
	prueba_insertar_ultimo();
	prueba_volumen_invariante_al_principio();
	prueba_volumen_invariante_al_final();
	prueba_invariante();
	insertar_NULL();
	prueba_destruir_vacia_con_funcion();
	prueba_destruir_vacia_sin_funcion();
	prueba_destruir_no_vacia_con_funcion();
	prueba_destruir_no_vacia_sin_funcion();
	prueba_iterador_interno();
	prueba_iterador_externo();
}


#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
