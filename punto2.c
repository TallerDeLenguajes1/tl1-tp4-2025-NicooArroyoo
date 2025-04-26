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
Nodo * QuitarNodo(Nodo **Start, int dato);
void MostrarLista(Nodo **Start);
Nodo* ConsultarTareaID(Nodo **Start, int dato);
Nodo* ConsultarTareaPalabraClave(Nodo **Start, char* dato);
void MostrarTarea(Nodo *Nodo);


int main(){

    Nodo * TareasPendientes;
    TareasPendientes = CrearListaVacia();
    Nodo * TareasRealizadas;
    TareasRealizadas = CrearListaVacia();
    int id = 1000, opcion=0, seleccion = 1; ;
    do{
        printf("\n\n[1] Ingresar tareas");
        printf("\n[2] Trasferir tareas pendientes a realizadas");
        printf("\n[3] Listar tareas");
        printf("\n[4] Consultar tarea por id o palabra clave");
        printf("\n[5] Salir");
        printf("\n\nIngrese una opcion:");
        scanf("%d",&opcion);
        switch (opcion)
        {
            case 1:      
                                      
                do{              
                   InsertarNodo(&TareasPendientes , CrearNodo(id));
                   id++;
                   printf("\nTarea ingresada correctamente...");            
                   printf("\nCrear nueva tarea? 0:NO, 1:SI ");
                   fflush(stdin);
                   scanf("%d",&seleccion);                  
                   printf("\n");
                }while(seleccion == 1); 

                break;
                
            case 2:
                int idBuscado;
                do{
                    printf("Ingrese ID de la tarea pendiente que completo: ");
                    scanf("%d", &idBuscado);
                    Nodo* Buscado = QuitarNodo(&TareasPendientes, idBuscado);              
                    if(Buscado)
                    {
                        InsertarNodo(&TareasRealizadas , Buscado); 
                        printf("\nTarea %d transferida a la lista de realizadas", idBuscado);
                    }else{
                        printf("\nTarea %d no encontrada en pendiente");
                    }
                    printf("\nTrasferir otra tarea? 0:NO, 1:SI ");
                    scanf("%d",&seleccion);
                }while(seleccion == 1); 

                break;


            case 3:
                printf("\n...........TAREAS PENDIENTES..........");
                MostrarLista(&TareasPendientes);
                printf("\n...........TAREAS REALIZADAS..........");
                MostrarLista(&TareasRealizadas);
                break;
            
            case 4:
                
                do{
                    printf("\n[1]Buscar tarea por ID");
                    printf("\n[2]Buscar tarea por PALABRA CLAVE");
                    printf("\n\nIngrese una opcion: ");
                    scanf("%d", &seleccion);
                }while(seleccion<1 || seleccion>2);
                
                if(seleccion == 1){
                    int idBuscado;
                    printf("Ingrese el ID:");
                    scanf("%d", &idBuscado);
                    Nodo * Buscado1; //Elemento buscado en la lista de tareas pendientes
                    Nodo * Buscado2; //Elemento buscado en la lista de tareas realizadas
                    if((Buscado1 = ConsultarTareaID(&TareasPendientes, idBuscado)) || (Buscado2 = ConsultarTareaID(&TareasRealizadas, idBuscado)) ){
                        if(Buscado1){
                            printf("--- TAREA PENDIENTE ---");
                            MostrarTarea(Buscado1);
                        }else{
                            printf("--- TAREA REALIZADA ---");
                            MostrarTarea(Buscado2);
                        }                  
                    }
                    else{
                        printf("\nTarea NO existente");
                    }
                    
                }else{
                    char clave[50];
                    printf("Ingrese la PALABRE CLAVE:");
                    fflush(stdin);
                    scanf("%s", clave);
                    Nodo * Buscado1; //Elemento buscado en la lista de tareas pendientes
                    Nodo * Buscado2; //Elemento buscado en la lista de tareas realizadas
                    if((Buscado1 = ConsultarTareaPalabraClave(&TareasPendientes, clave)) || (Buscado2 = ConsultarTareaPalabraClave(&TareasRealizadas, clave)) ){
                        if(Buscado1){
                            printf("--- TAREA PENDIENTE ---");
                            MostrarTarea(Buscado1);
                        }else{
                            printf("--- TAREA REALIZADA ---");
                            MostrarTarea(Buscado2);
                        }                  
                    }else{
                        printf("\nTarea NO existente");
                    }
                }
                
                break;
           
            default:
                printf("\nOpcion incorrecta, vuelva a intentar");
                break;
        }
    }while(opcion !=5);
    

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
    fflush(stdin);
    printf("\nDescripcion: ");
    gets(cadenaAux);
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

Nodo * QuitarNodo(Nodo **Start, int dato) {
    Nodo ** aux = Start;  // Usamos un puntero doble para apuntar al puntero actual.
    
    // Iteramos sobre la lista hasta encontrar el dato o alcanzar el final de la lista.
    while (*aux != NULL && (*aux)->T.TareaID != dato) {
        aux = &(*aux)->Siguiente;
    }

    // Si encontramos el nodo con el dato especificado, lo quitamos de la lista y retornamos al programa para su posterior eliminación.
    if (*aux) {
        Nodo *temp = *aux;  // Guardamos el nodo a eliminar en una variable temporal.
        *aux = (*aux)->Siguiente;  // Desvinculamos el nodo de la lista.
        temp->Siguiente =NULL; // Ponemos en NULL el puntero siguiente para asegura no llevar vinculos por fuera de la lista
        return temp;
    }
    return NULL;
}

void MostrarLista(Nodo **Start){
    Nodo * Aux = *Start;
     while (Aux)
    {
      printf("\n\n_ TAREA %d _",Aux->T.TareaID);
      printf("\nDescripcion: %s", Aux->T.Descripcion);
      printf("\nDuracion: %d\n", Aux->T.Duracion);
      Aux = Aux->Siguiente;
    }
}

void MostrarTarea(Nodo *Nodo){
    printf("\n_ Tarea %d _", Nodo->T.TareaID);
    printf("\nDescripcion: %s", Nodo->T.Descripcion);
    printf("\nDuracion: %d\n", Nodo->T.Duracion);
}

Nodo* ConsultarTareaID(Nodo **Start, int dato){
    Nodo * Aux = *Start;
    while (Aux && Aux->T.TareaID != dato)
    {
      Aux = Aux->Siguiente;
    }
    return Aux;
}

Nodo* ConsultarTareaPalabraClave(Nodo **Start, char* dato){
    Nodo * Aux = *Start;
    while(Aux){
        if (strstr(Aux->T.Descripcion, dato) != NULL){
            return Aux;
        }
        Aux = Aux->Siguiente;
    }
    return NULL;
}

