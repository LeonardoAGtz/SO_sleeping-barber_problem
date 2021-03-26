#include <stdio.h>
#include <pthread.h>
#include <unistd.h>//para la función sleep
#include <windows.h>//para los colores

#define SILLAS 5 //cantidad de sillas
#define CLIENTES 10 //numero de clientes

typedef int semaforo;
semaforo sem_barbero(0), sem_cliente(0), sem_mutex(1);
int espera(0), clientes_del_dia = CLIENTES, clientes_atendidos(0);

void *cliente(void*);
void *barbero(void*);
void up(semaforo*);
void down(semaforo*);

using namespace std;

int main()
{
    printf("Leonardo Aranda Gutierrez 217761528\n");
    printf("CENTRO UNIVERSITARIO DE CIENCIAS EXACTAS E INGENIERIAS\n");
    printf("INGENIERIA INFORMATICA\n");
    printf("SISTEMAS OPERATIVOS\n");
    printf("ESTE PROGRAMA REPRESENTA EL PROBLEMA DEL BARBERO DORMILON CON 1 BARBERO, 10 CLIENTES Y 5 SILLAS\n");

    system("pause");


    pthread_t t_barbero;//Se crea un hilo para el barbero
    pthread_t t_cliente[CLIENTES]; //Se crea un array de hilos para los clientes
    int i;
    pthread_create(&t_barbero,NULL,barbero,NULL);
    for(i=0; i<CLIENTES;++i){
        sleep(1);
        pthread_create(&t_cliente[i],NULL, cliente,NULL);//Se crea cada hilo indv y se asigna a un espacio del arreglo
    }

    pthread_join(t_barbero,NULL);//Entra en función el barbero
    return 0;
}

void *cliente(void*n){
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),1);
    printf("Cliente: Entrando, hay %d esperando\n", espera);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
    down(&sem_mutex);
    if (espera < SILLAS) {
        espera++;
        up(&sem_cliente);
        up(&sem_mutex);
        down(&sem_barbero);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),6);
        printf("Cliente: Recibiendo corte de pelo\n");
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
    }else {
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
        up(&sem_mutex);
        printf("Cliente: No hay lugar para esperar, me voy\n");
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
    }
}

void *barbero(void*i){
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),2);
    printf("Barbero: Comienza el trabajo\n");
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
    while (true) {
        down (&sem_cliente);
        down (&sem_mutex);
        espera--;
        up (&sem_barbero);
        up (&sem_mutex);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),2);
        printf("Barbero: Comienzo un corte de pelo, quedan %d\n", espera);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
        sleep(3);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),2);
        printf("Barbero. Termine un corte, quedan %d\n", espera);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
    }
}

void up (semaforo *sem) {
    *sem+=1;
}

void down (semaforo *sem) {
    while (*sem<=0){};
    *sem-=1;
}
