#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000 // Número de elementos en el arreglo masivo

int main(int argc, char **argv) {
  // 1. Inicializar el entorno MPI
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // ID del proceso
  MPI_Comm_size(MPI_COMM_WORLD, &size); // Total de procesos

  double *array = NULL;
  double local_sum = 0.0;
  double total_sum = 0.0;

  // 2. El proceso Maestro (0) inicializa los datos
  if (rank == 0) {
    array = (double *)malloc(N * sizeof(double));
    if (array == NULL) {
      fprintf(stderr, "Error de memoria en proceso raíz.\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
    // Llenar el arreglo con valores (1, 2, ..., N)
    for (int i = 0; i < N; i++) {
      array[i] = i + 1;
    }
    printf("Proceso Maestro: Datos inicializados. Iniciando distribución...\n");
  }

  // 3. Distribución de datos (Scatter)
  // Calculamos cuántos elementos le tocan a cada proceso
  int elements_per_proc = N / size;
  double *sub_array = (double *)malloc(elements_per_proc * sizeof(double));

  // Medición de tiempo (Start)
  double start_time;
  if (rank == 0)
    start_time = MPI_Wtime();

  // Enviamos partes del arreglo a todos los procesos
  MPI_Scatter(array, elements_per_proc, MPI_DOUBLE, sub_array,
              elements_per_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // 4. Cómputo Paralelo (Suma Local)
  for (int i = 0; i < elements_per_proc; i++) {
    local_sum += sub_array[i];
  }

  // 5. Recolección y Reducción (Reduce)
  // Sumamos todas las sumas locales en la variable total_sum del maestro
  MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  // Medición de tiempo (End)
  if (rank == 0) {
    double end_time = MPI_Wtime();
    double time_taken = end_time - start_time;

    printf("--- Resultados ---\n");
    printf("Suma total calculada: %.2f\n", total_sum);
    printf("Tiempo total de ejecución con %d procesos: %f segundos\n", size,
           time_taken);

    free(array);
  }

  free(sub_array);
  MPI_Finalize(); // Finalizar MPI
  return 0;
}