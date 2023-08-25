#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct elemento{
    char *nombreCompleto;
    int n_semestre;
    int n_creditos;
}alumno;

typedef struct elemento2{
    alumno* alum;
    struct elemento2 *sig;
}nodo;

//Firmas
alumno* crearAlumno(char *nombreCompleto, int semestre, int creditos);
nodo* crearLista();
nodo* crearNodo(alumno *a);
nodo *encontrarAnterior(nodo *cabeza, nodo *nuevo);
void insertarNodoOrdenadoCreditos(nodo **cabeza, alumno *a);
void imprimirLista(nodo *cabeza);
void imprimirAlumno(alumno *a);

int main(){

    nodo *cabeza = crearLista();

    alumno *a1 = crearAlumno("Rodrigo Adran Canto Paredes", 1, 50);
    alumno *a2 = crearAlumno("Alex Enrique Dzul Lopez", 3, 47);
    alumno *a3 = crearAlumno("Ricardo Cordova Martinez", 4, 78);
    alumno *a4 = crearAlumno("Pablo Ernesto Baeza Lara", 3, 67);
    alumno *a5 = crearAlumno("Eduardo Alexander Canto Paredes", 4, 68);

    insertarNodoOrdenadoCreditos(&cabeza, a1);
    insertarNodoOrdenadoCreditos(&cabeza, a2);
    insertarNodoOrdenadoCreditos(&cabeza, a3);
    insertarNodoOrdenadoCreditos(&cabeza, a4);
    insertarNodoOrdenadoCreditos(&cabeza, a5);

    imprimirLista(cabeza);

    return 0;
}

alumno* crearAlumno(char *nombre, int semestre, int creditos){
    alumno *a = malloc(sizeof(alumno));
    a -> nombreCompleto = nombre;
    a -> n_creditos = creditos;
    a -> n_semestre = semestre;
    return a;
}

nodo* crearLista(){
    nodo *cabeza = NULL;
    return cabeza;
}

nodo* crearNodo(alumno *a){
    nodo *nuevo = malloc(sizeof(nodo));
    nuevo -> alum = a;
    nuevo -> sig = NULL;
    return nuevo;
}

nodo *encontrarAnterior(nodo *cabeza, nodo *nuevo){
    nodo *actual = cabeza;
    nodo *anterior = NULL;

    while((actual != NULL) && (nuevo -> alum -> n_creditos < actual -> alum -> n_creditos)){
        anterior = actual;
        actual = actual -> sig;
    }

    return anterior;
}

void insertarNodoOrdenadoCreditos(nodo **cabeza, alumno *a){

    nodo *nuevo = crearNodo(a);
    nodo *anterior;
    nodo *actual;

    if(*cabeza == NULL){
        *cabeza = nuevo;
        nuevo -> sig = NULL;
    }
    else{
        anterior = encontrarAnterior(*cabeza, nuevo);

        if(anterior == NULL){
            nuevo -> sig = *cabeza;
            *cabeza = nuevo;
        }
        else{
            actual = anterior -> sig;
            anterior -> sig = nuevo;
            nuevo -> sig = actual;
        }
    }
}

void imprimirAlumno(alumno *a){
    printf("-> %s, Semestre %d, %d creditos aprobados", a -> nombreCompleto, a -> n_semestre, a -> n_creditos);
    printf("\n");
}

void imprimirLista(nodo *cabeza){
    nodo *actual;

    for(actual = cabeza; actual != NULL; actual = actual -> sig){
        imprimirAlumno(actual -> alum);
    }
}