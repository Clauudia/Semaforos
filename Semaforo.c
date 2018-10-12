#include <omp.h>
#include <stdio.h>
#include <stdlib.h> 

//Definimos un tipo booleano 
typedef int bool;
#define true 1
#define false 0

// ------ Creación de la cola basada en: https://www.geeksforgeeks.org/queue-set-2-linked-list-implementation/

//Definimos un nodo, el cuál almacenara a los elementos de la cola
struct Nodo
{
	int llave;
	struct Nodo *siguiente;
};
 
//Definimos la cola, inicio almacena el elemento al inicio de la cola y final almacena el elemento final
struct Cola
{
	struct Nodo *inicio, *final;
};

//Función auxiliar para crear una nueva lista de nodos
struct Nodo* nuevoNodo(int k)
{
	struct Nodo *temp = (struct Nodo*)malloc(sizeof(struct Nodo));
	temp->llave = k;
	temp->siguiente = NULL;
	return temp;
};

//Función auxiliar para crear una cola vacía 
struct Cola *creaCola()
{
	struct Cola *q = (struct Cola*)malloc(sizeof(struct Cola));
	q->inicio = q->final = NULL;
	return q;
};

//Método para encolar los hilos
void encolar(struct Cola *q, int k)
{
	struct Nodo *temp = nuevoNodo(k);

	if(q->final == NULL)
	{
		q->inicio = q->final = temp;
		return;
	} 

	q->final->siguiente = temp;
	q->final = temp;
}

//Método para desencolar los hilos
struct Nodo *desencola(struct Cola *q)
{
	if(q->inicio == NULL)
		return NULL;
	struct Nodo *temp = q->inicio;
	q->inicio = q->inicio->siguiente;

	if(q->inicio == NULL)
		q->final = NULL;
	return temp;
};

//Método con el cual verificamos sí la cola está vacía
bool estaVacia(struct Cola *cola)
{
	return cola->inicio == NULL;
};

//Creamos la esctructura semáforo
struct Semaforo
{
	int n; //Variable en la cual se especifica el número de hilos que van a poder entrar a la sección crítica al mismo tiempo. 
	struct Cola *cola; //Estructura de datos mediante la que controlaremos el acceso de los procesos.
};

//Implementación de la función wait, la cual bloquea al hilo
void wait(struct Semaforo *semaforo, bool b[], int hilo_id)
{	
	if(semaforo->n==0)//Verificamos si el contador es cero
	{
		b[hilo_id] = true; //Cambiamos la condición de  espera a true
		encolar(semaforo->cola, hilo_id); //Añadimos al hilo que quiere entrar a la cola
		while(b[hilo_id]); //Dormimos al hilo
	}else
	{
		semaforo->n--; //Si el contador no es cero entonces disminuimos en uno al contador
	}
}

//Implementación de la función signal, la cuál desbloquea al hilo
void signal(struct Semaforo *semaforo, bool b[])
{
	if(estaVacia(semaforo->cola)!=true)//Verificamos si la cola está vacía
	{
		struct Nodo *nodo = desencola(semaforo->cola);//Sacamos al hilo de la cola
		b[nodo->llave] = false; //Cambiamos la condición de espera
	} else {
		semaforo->n++; //En otro caso aumentamos el contador en uno
	}
}

int main(int argc, char *argv[])
{
	int nhilos,hilo_id;

	//Declaramos el semáforo1 de tipo Semáforo
	struct Semaforo Semaforo1;
	//bool wait = false; //Variable con la que simulamos la condición de espera

	//Especificamos las características del semáforo1 
	Semaforo1.n = 1;

	printf("Ingresa el número de hilos que deseas lanzar: \n",argv[1]); //Recibimos por línea de comandos el número de hilos que se van a lanzar
	scanf("%d", &nhilos);

	omp_set_num_threads(nhilos); //Establecemos el número de hilos que se van a lanzar

	//printf("Se lanzarán %d hilos \n",nhilos); 
	bool arreglo_bool[nhilos];

	#pragma omp parallel private(hilo_id)
	{
		hilo_id = omp_get_thread_num(); //Obtenemos el id de los hilos

		for(int i=0; i>10; i++) //Los hilos van a iterar 10 veces
		{
			int x = 0; //Variable de la cuál se hará uso para calcular la suma 
			//Sección crítica
			printf("***El hilo %d acaba de entrar a la sección crítica***\n", hilo_id);
			
			//Se hace la suma de los primeros 1000 números naturales
			for(int j=0; j<1000; j++)
			{
				x+=j;
			}
		printf("---El hilo %d ha salido de la sección crítica---\n", hilo_id);
		}

	}
	return 0;
}