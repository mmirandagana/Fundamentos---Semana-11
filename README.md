ACIF101 - Fundamentos de Computación de Alto Desempeño (Semana 11)
Evaluación Sumativa 5: Optimización con MPI y Simulación Cuántica

Autor: Manuel Miranda
Fecha: 16 de Diciembre, 2025
Curso: ACIF101 - Universidad Andrés Bello Online

================================================================================

[ DESCRIPCIÓN DEL PROYECTO ]

Este repositorio contiene las implementaciones de código C desarrolladas para la Semana 11, enfocadas en dos paradigmas avanzados de computación:

1. Computación Paralela (MPI): Evaluación de rendimiento, escalabilidad y gestión de concurrencia (prevención de deadlocks) en sistemas distribuidos.

2. Simulación Cuántica: Emulación de lógica cuántica (Qubits, Superposición, Entrelazamiento) utilizando estructuras de datos clásicas para comprender el comportamiento probabilístico de circuitos cuánticos.

El objetivo es demostrar el uso eficiente de recursos de hardware y la aplicación de software de alto desempeño.

================================================================================

[ ENTORNO DE DESARROLLO Y REQUISITOS ]

Para compilar y ejecutar estos programas se requiere un entorno Linux (nativo o WSL).

- Sistema Operativo: Ubuntu 24.04 (WSL)
- Compilador: GCC y OpenMPI Wrapper (mpicc)
- Bibliotecas: mpi.h, math.h, time.h, stdlib.h

>> Instalación de Dependencias (Ubuntu/Debian)
Si no tienes configurado MPI, ejecuta los siguientes comandos:

    sudo apt update
    sudo apt install build-essential openmpi-bin libopenmpi-dev

================================================================================

[ COMPILACIÓN Y EJECUCIÓN ]

A continuación se detallan los comandos necesarios para compilar y ejecutar cada uno de los tres módulos del proyecto.

1. Evaluación de Rendimiento (MPI)
----------------------------------
Archivo: mpi_rendimiento.c
Descripción: Este programa mide la escalabilidad al sumar un arreglo masivo distribuido entre procesos.

-> Compilar:
   mpicc -o mpi_rendimiento mpi_rendimiento.c

-> Ejecutar:
   Puedes variar el número de procesos (-np) para ver cómo cambia el tiempo:
   mpirun -np 1 ./mpi_rendimiento
   mpirun -np 2 ./mpi_rendimiento
   mpirun -np 4 ./mpi_rendimiento


2. Prevención de Deadlocks (MPI)
----------------------------------
Archivo: mpi_deadlock_prevent.c
Descripción: Este programa demuestra el intercambio seguro de mensajes usando comunicación asíncrona.

-> Compilar:
   mpicc -o mpi_prevent mpi_deadlock_prevent.c

-> Ejecutar:
   mpirun -np 2 ./mpi_prevent


3. Simulación Cuántica
----------------------------------
Archivo: quantum_simulation.c
Descripción: Este programa simula un circuito cuántico con compuertas Hadamard y CNOT.

-> Compilar:
   (Nota: Es necesario agregar -lm al final para vincular la librería matemática)
   gcc -o quantum_sim quantum_simulation.c -lm

-> Ejecutar:
   ./quantum_sim
