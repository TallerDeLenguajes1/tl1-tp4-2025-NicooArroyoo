#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea
{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo* Siguiente;
}Nodo;

 
Nodo * CrearListaVacia();
Nodo * CrearNodo(int id);
void PedirDescripcion(Nodo *NNodo);    
void PedirDuracion(Nodo * NNodo);
void InsertarNodo(Nodo ** Start , Nodo *Nodo);

int main(){

    Nodo * TareasPendientes;
    TareasPendientes = CrearListaVacia();
    Nodo * TareasRealizadas;
    TareasRealizadas = CrearListaVacia();
    int seleccion, id = 1000;
    do{
         printf("\nCrear nueva tarea? 0:NO, 1:SI ");
         scanf("%d",&seleccion);
         if(seleccion == 1){
            InsertarNodo(&TareasPendientes , CrearNodo(id));
            id++;
         }
         printf("\n");
    }while(seleccion != 0);

    return 0;
}

void InsertarNodo(Nodo ** Start , Nodo *Nodo)
{
Nodo->Siguiente= *Start;
*Start = Nodo ;
}

Nodo * CrearListaVacia()
{
    return NULL;
}

Nodo * CrearNodo(int id)
{
    Nodo * NNodo = (Nodo *) malloc (sizeof(Nodo));
    NNodo->T.TareaID = id;
    NNodo->Siguiente = NULL;
    PedirDescripcion(NNodo);
    PedirDuracion(NNodo);
    return NNodo;
}


void PedirDescripcion(Nodo * NNodo)
{
    char cadenaAux[500];
    printf("\n\n------ TAREA %d ------",NNodo->T.TareaID);
    printf("\nDescripcion: ");
    getchar();
    scanf("%s",cadenaAux);
    NNodo->T.Descripcion = (char *)malloc(strlen(cadenaAux) + 1);
    strcpy(NNodo->T.Descripcion, cadenaAux);
}

void PedirDuracion(Nodo * NNodo)
{
    do{
        printf("\nDuracion: ");
        fflush(stdin);
        scanf("%d",&(NNodo->T.Duracion));
    }while(NNodo->T.Duracion<10 || NNodo->T.Duracion>100);
}