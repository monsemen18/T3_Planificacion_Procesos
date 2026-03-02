# Simulación de técnicas de planificación de procesos (CPU scheduling)

## Equipo 3
1. Ledesma Cuevas Eduardo
2. Mendez Camacho Monserrat

Simulación de una tecnica de planificación de procesos (CPU scheduling) en C. Los algoritmos seleccionados son: **Shortest Remaining Time Next (SRTN)** y **Lottery Scheduling**.


## Descripción

El simulador permite evaluar métricas clave como:
- **Orden de ejecución**
- **Tiempo de Espera (Waiting Time)**: Tiempo total que un proceso espera en la cola. Turn around time - burst time
- **Tiempo de Retorno (Turnaround Time)**: Desde que llega hasta que termina. Completion time - arrival time
- **Tiempo de Respuesta (Response Time)**: Desde que llega hasta que recibe CPU por primera vez.
- **Promedios de las métricas anteriores**

Para simular las pruebas se utiliza un archivo `Procesos.txt` que contiene datos para simular la ejecución de 100 procesos que contienen ID, tiempo de llegada, tiempo de ráfaga (CPU burst) y prioridad.

##  **SRTN - Shortest Remaining Time Next** 
Es la version apropiativa de Shortest Job First. En SRTJ, el proceso con el menor tiempo restante por terminar es seleccionado para ejecutarse. 
La ejecución continúa hasta que termina o un nuevo proceso con menor tiempo restante llega. 

- Preemptive/ apropiativa (puede interrumpir procesos en ejecución) 
- Favorece procesos cortos
- Puede causar que procesos largos no se ejecuten

##  **Lottery Scheduling** 
Es un algoritmo de planificación en el que se dan "tickets de lotería" a cada proceso y un número de lotería es elegido al azar para determinar el siguiente proceso a ejecutarse. El proceso se ejecuta durante un tiempo asignado y se vuelve a elegir un número para seleccionar el siguiente proceso.

- El número de tickets que un proceso recibe determina la probabilidad de que sea elegido
- Si un nuevo proceso se añade, su probabilidad de ser elegido es proporcional al número de tickets que recibe, por lo que es un algoritmo muy responsivo
- Algunos procesos que cooperan puede intercambiar tickets entre sí, para que si alguno se bloquea, se transfieran todos los tickets al que sigue activo

## Como ejecutar
### Compilar
```
mkdir -p build
```
```
gcc srtn/simuladorPlanProcesos.c -o build/srtn
```
```
gcc srtn/simuladorPlanProcesos.c -o build/lottery
```

### Correr el programa 
#### SRTN
```
./build/srtn < Procesos.txt
```
#### Lottery Scheduling
```
./build/lottery < Procesos.txt
```

## Resultados

### Comparativa: SRTN vs Lottery Scheduling
Basado en el promedio de 10 ejecuciones.

| Métrica                     | SRTN | Lottery     |
|-----------------------------|------|-------------|
| Waiting Time Promedio       |129.66|318.4        |
| Turnaround Time Promedio    |135.66|324.41       |
| Response Time Promedio      |129.54|75.86        |
| Starvation                  |Si    |Poco probable|

### ¿Qué algoritmo favorece a procesos cortos?
SRTN es claramente el algoritmo que más favorece a procesos cortos, pues siempre ejecuta el proceso con menor tiempo restante, incluso pudiendo interrumpir el proceso actual si llega un proceso nuevo más corto.

### ¿Cuál es más “justo”?
El más justo entre los dos sería Lottery Scheduling, ya que todos los procesos tienen oportunidad de ser ejecutados y a diferencia de SRTN, no hay problema de "starvation" con procesos largos si se asigna al menos un ticket a todos los procesos.