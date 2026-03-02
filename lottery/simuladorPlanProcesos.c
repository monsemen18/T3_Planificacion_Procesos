#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESOS 200   // por si quieren simular mas de 100

/**
 * Estructura para representar los procesos del CPU.
 * 
 */
typedef struct {
    int id;   			        // ID del proceso
    int arrival;                // Tiempo de llegada (t0, t1... tn)
    int burst;                  // Ráfaga de CPU original (tiempo cpu)
    int priority;               // Para algoritmos con prioridades
    int remaining;		        // Tiempo restante (para RR, SRTN)
    int start_time;		        // Primer instante en que se ejecuta
    int finish_time;		    // Momento en que termina
    int waiting_time;		    // Tiempo total de espera
    int turnaround;		        // finish_time - arrival
    int response_time;          // primer instante en que el proceso recibe CPU − arrival
} Process;

/**
 * Archivo main que maneja el flujo del programa.
 * 
 * Carga los procesos desde un archivo de texto
 * y hace las llamadas a las funciones correspondientes
 * para las simulaciones.
 * 
 */
int main(void) {
    Process procesos[MAX_PROCESOS];
    int n = 0;

    // Lee desde stdin hasta EOF: cada línea debe tener id arrival burst priority
    while (scanf("%d %d %d %d",
                 &procesos[n].id,
                 &procesos[n].arrival,
                 &procesos[n].burst,
                 &procesos[n].priority) == 4) {

        procesos[n].remaining    = procesos[n].burst;
        procesos[n].start_time   = -1;
        procesos[n].finish_time  = 0;
        procesos[n].waiting_time = 0;
        procesos[n].turnaround   = 0;
        procesos[n].response_time= -1;
        n++;

        if (n >= MAX_PROCESOS) {
            fprintf(stderr, "Se alcanzó el límite MAX_PROCESOS=%d\n", MAX_PROCESOS);
            break;
        }
    }

    void simulate_lottery(Process *p, int n);
    
    simulate_lottery(procesos, n);

    return 0;
}

/**
 * Función que implementa una simulación de Lottery Scheduling.
 * Asigna tickets a los procesos y realiza un sorteo
 * para elegir el siguiente proceso.
 * 
 */
void simulate_lottery(Process *p, int n) {

    printf("\nResultado Lottery Scheduling: \n");

    printf("\nOrden de ejecución: \n");

    int current_time = 0;
    int completed = 0;

    srand(time(NULL)); // Iniciar random con current time como semilla.

    while(completed < n) {

        int total_tickets = 0;
        
        // Suma los tickets de los procesos listos.
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= current_time && p[i].remaining > 0) {
                total_tickets += p[i].priority;
            }
        }

        // Si no hay procesos listos, avanza un tiempo.
        if(total_tickets == 0) {
            current_time++;
            continue;
        }
        
        // Generar un ticket ganador.
        int ganador = rand() % total_tickets;


        // Encontrar el ganador
        int acumulado = 0;
        int elegido = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= current_time && p[i].remaining > 0) {
                acumulado += p[i].priority;

                if (ganador < acumulado) {
                    elegido = i;
                    break;
                }
            }
        }

        // Ejecutar una unidad de tiempo
        if (elegido != -1) {

            printf("\nPID: %d", elegido);

            if (p[elegido].start_time == -1) {
                p[elegido].start_time = current_time;
                p[elegido].response_time = current_time - p[elegido].arrival;
            }

            p[elegido].remaining--;
            current_time++;

            // Si el proceso ya terminó
            if (p[elegido].remaining == 0) {
                p[elegido].finish_time = current_time;
                p[elegido].turnaround = p[elegido].finish_time - p[elegido].arrival;
                p[elegido].waiting_time = p[elegido].turnaround - p[elegido].burst;

                completed++;
                printf(" Terminó");
            }

            
        }
    }


    double total_waiting_time = 0   ;
    double total_turnaround = 0;
    double total_response_time = 0;

    printf("\n\nInformación procesos: \n");
    printf("PID\tWT\tTA\tRT\n");    

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n",
            p[i].id,
            p[i].waiting_time,
            p[i].turnaround,
            p[i].response_time);

        total_waiting_time  += p[i].waiting_time;
        total_turnaround += p[i].turnaround;
        total_response_time  += p[i].response_time;
    }

    printf("\nPromedios:\n");
    printf("WT promedio  = %.2f\n", total_waiting_time / n);
    printf("TAT promedio = %.2f\n", total_turnaround / n);
    printf("RT promedio  = %.2f\n", total_response_time / n);

}