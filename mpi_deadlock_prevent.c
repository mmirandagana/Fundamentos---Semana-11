#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("Se necesitan al menos 2 procesos para esta prueba.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Datos para la comunicación
    int send_data = rank + 100;
    int recv_data;
    
    // Solicitudes (Requests) para manejar la comunicación no bloqueante
    MPI_Request request_send, request_recv;

    // Lógica de intercambio en anillo (Ring Topology)
    int dest = (rank + 1) % size;           // Enviar al siguiente
    int source = (rank - 1 + size) % size;  // Recibir del anterior

    printf("Proceso %d iniciando intercambio no bloqueante con Dest: %d, Source: %d\n", rank, dest, source);

    // 1. Iniciar Envío NO Bloqueante (Isend)
    // El proceso no se detiene aquí, sigue ejecutando.
    MPI_Isend(&send_data, 1, MPI_INT, dest, 0, MPI_COMM_WORLD, &request_send);

    // 2. Iniciar Recepción NO Bloqueante (Irecv)
    MPI_Irecv(&recv_data, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &request_recv);

    // Aquí se podrían hacer cálculos útiles mientras los datos viajan...
    
    // 3. Esperar a que la comunicación termine (Wait)
    // Esto asegura que los datos se enviaron y recibieron correctamente antes de usarlos
    MPI_Wait(&request_send, MPI_STATUS_IGNORE);
    MPI_Wait(&request_recv, MPI_STATUS_IGNORE);

    printf("--> ÉXITO: Proceso %d envió %d y recibió %d sin Deadlock.\n", rank, send_data, recv_data);

    MPI_Finalize();
    return 0;
}