#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESOS 200   // por si quieren simular mas de 100

typedef struct {
    int id;   			// ID del proceso
    int arrival;                // Tiempo de llegada (t0, t1... tn)
    int burst;                  // Ráfaga de CPU original (tiempo cpu)
    int priority;               // Para algoritmos con prioridades
    int remaining;		// Tiempo restante (para RR, SRTN) 
    int start_time;		// Primer instante en que se ejecuta
    int finish_time;		// Momento en que termina
    int waiting_time;		// Tiempo total de espera,  turnaround - burst time
    int turnaround;		// finish_time - arrival
    int response_time;          // primer instante en que el proceso recibe CPU − arrival
} Process;

void simulate_srtn(Process *p, int n){
    int completed = 0;  // procesos que ya terminaron
    int current_time = 0;

    // reseteamos variables, por si hace el otro algoritmo aqui
    for (int i = 0; i < n; i++) {
        p[i].remaining    = p[i].burst;
        p[i].start_time   = -1;
        p[i].finish_time  = 0;
        p[i].waiting_time = 0;
        p[i].turnaround   = 0;
        p[i].response_time= -1;
    }

    while (completed < n) {
        // buscamos el proceso con menor tiempo restante de la lista de procesos
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= current_time && p[i].remaining > 0) {
                if (idx == -1 || p[i].remaining < p[idx].remaining)  // yo tengo menor tiempo
                    idx = i;   // se hace el cambio 

            }
        }

        // ningun proceso esta listo en este momento (current_time)
        // salta al proximo 
        if (idx == -1) {
            int next_arrival = -1;
            for (int i = 0; i < n; i++) {
                if (p[i].remaining > 0) {
                    if (next_arrival == -1 || p[i].arrival < next_arrival)
                        next_arrival = p[i].arrival;
                }
            }
            current_time = next_arrival;
            continue;
        }

        // guardamos el start_time de cada proceso
        if (p[idx].start_time == -1) {
            p[idx].start_time = current_time;
            p[idx].response_time = current_time - p[idx].arrival; // proceso reicbe cpu
        }

        // ejecuta por una unidad de tiempo
        p[idx].remaining--;   // se ejecuto 
        current_time++;  // aumentamos tiempo actual

        // revisamos status del proceso
        if (p[idx].remaining == 0) {
            p[idx].finish_time = current_time;
            p[idx].turnaround = p[idx].finish_time - p[idx].arrival;
            p[idx].waiting_time = p[idx].turnaround - p[idx].burst;
            completed++; // un proceso menos 
        }
    }

    // imprimimos resultados como tabla
    printf("\n=============== SRTF (Shortest Remaining Time First) ===============\n");
    printf("%-6s %-10s %-10s %-18s %-10s %-20s %-14s %-14s\n",
           "ID", "Arrival", "Burst", "Completion Time", "Start Time ", "Turnaround Time", "Waiting Time", "Response Time");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    double total_tat = 0, total_wt = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        printf("P%-5d %-10d %-10d %-18d %-10d %-20d %-14d %-14d\n",
               p[i].id,
               p[i].arrival,
               p[i].burst,
               p[i].finish_time,
               p[i].start_time,
               p[i].turnaround,
               p[i].waiting_time,
               p[i].response_time);
        total_tat += p[i].turnaround;
        total_wt  += p[i].waiting_time;
        total_rt  += p[i].response_time;
    }

    printf("-----------------------------------------------------------------------------------------------\n");
    printf("Average Turnaround Time : %.2f\n", total_tat / n);
    printf("Average Waiting Time    : %.2f\n", total_wt  / n);
    printf("Average Response Time   : %.2f\n", total_rt  / n);

}

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

    printf("Se leyeron %d procesos:\n", n);
    for (int i = 0; i < n; i++) {
        printf("P%3d: arrival=%3d burst=%2d priority=%d\n",
               procesos[i].id,
               procesos[i].arrival,
               procesos[i].burst,
               procesos[i].priority);
    }

    simulate_srtn(procesos, n);

    return 0;
}
