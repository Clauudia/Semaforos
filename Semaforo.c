#include <omp.h>
#include <stdio.h>

//Definimos un tipo booleano 
typedef int bool;
#define true 1
#define false 0

//Creamos la cola 
 #define MAX nhilos;

struct Cola
{
	int arreglo[MAX];
	int inicio = 0;
	int final = -1;
	int contadorElementos = 0;	
};

bool estaVacia()
{
	return contadorElementos == 0;
}

bool estaLlena()
{
	return contadorElementos == MAX;
}

void insertar(int hilo)
{
	if(!estaLlena())
	{
		if(final == MAX-1)
		{
			final = -1;
		}

		arreglo[++final] = hilo;
		contadorElementos ++;
	}
}

void quitar()
{
	int hilo = arreglo[inicio++];
	if(inicio == MAX)
	{
		inicio = 0;
	}

	contadorElementos --;
}

//Termina la definición de la cola

struct Semaforo
{
	int n; //Variable en la cual se especifica el número de hilos que van a poder entrar a la sección crítica al mismo tiempo. 
	int contador;
	struct Cola Cola; 
};

int main(int argc, char *argv[])
{
	int nhilos,hilo_id;

	//Declaramos el semáforo1 de tipo Semáforo
	struct Semaforo Semaforo1;
	bool wait = false; //Variable con la que simulamos la condición de espera

	//Especificamos las características del semáforo1 
	Semaforo1.n = 2;
	Semaforo1.contador = 0;

	printf("Ingresa el número de hilos que deseas lanzar: \n",argv[1]); //Recibimos por línea de comandos el número de hilos que se van a lanzar
	scanf("%d", &nhilos);

	omp_set_num_threads(nhilos); //Establecemos el número de hilos que se van a lanzar

	//printf("Se lanzarán %d hilos \n",nhilos); 

	#pragma omp parallel private(hilo_id)
	{
		hilo_id = omp_get_thread_num(); //Obtenemos el id de los hilos

		for(int i=0; i>10; i++) //Los hilos van a iterar 10 veces
		{
			if(Semaforo1.contador < Semaforo1.n)
			{
				//Sección crítica
				Semaforo1.contador ++;
				printf("***El hilo %d acaba de entrar a la sección crítica***\n", hilo_id);
				
				int x = 0; //Variable auxiliar que usaremos para hacer la suma

				//Se hace la suma de los primeros 1000 números naturales
				for(int j=0; j<1000; j++)
				{
					x+=j;
				}
				Semaforo1.contador --;
				printf("---El hilo %d ha salido de la sección crítica---\n", hilo_id);
			}

		}

	}

	return 0;
}