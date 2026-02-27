# CPU scheduling - Algoritmo Shortest Remaining Time Next (SRTN)

## Equipo 3
1. Ledesma Cuevas Eduardo
2. Mendez Camacho Monserrat

Simulacion de una tecnica de planificacion de procesos (CPU scheduling) en C. El algoritmo seleccionado es el de **Shortest Remaining Time Next (SRTN)**.


## Descripción

El simulador permite evaluar métricas clave como:
- **Orden de ejecucion**
- **Tiempo de Espera (Waiting Time)**: Tiempo total que un proceso espera en la cola. Turn around time - burst time
- **Tiempo de Retorno (Turnaround Time)**: Desde que llega hasta que termina. Completion time - arrival time
- **Tiempo de Respuesta (Response Time)**: Desde que llega hasta que recibe CPU por primera vez.
- **Promedios de las métricas anteriores**

##  **SRTN - Shortest Remaining Time Next** 
Es la version apropiativa de Shortest Job First. En SRTJ, el procesos con el menor tiempo restante por terminar es seleccionado para ejecutares. 
La ejecucion continua hasta que termina o un nuevo proceso con menor tiempo restante llega. 

- Preemptive/ apropiativa (puede interrumpir procesos en ejecución) 
- Favorece procesos cortos
- Puede causar que procesos largos no se ejecuten

## Como ejecutar 
### Compilar 
```
gcc simuladorPlanProcesos.c -o simuladorPlanProcesos
```

### Correr el programa 
```
./simulador < Procesos.txt
```
