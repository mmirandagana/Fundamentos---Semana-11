#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_QUBITS 2 

// Estructura para representar un Qubit con amplitudes de probabilidad
typedef struct {
    double alpha; // Amplitud del estado |0>
    double beta;  // Amplitud del estado |1>
} Qubit;

// Inicializar Qubit en estado base |0>
void initialize_qubit(Qubit *q) {
    q->alpha = 1.0;
    q->beta = 0.0;
}

// Compuerta Hadamard (Crea Superposición)
void apply_hadamard(Qubit *q) {
    // Transformación: |0> -> (|0> + |1>) / sqrt(2)
    double new_alpha = (q->alpha + q->beta) / sqrt(2);
    double new_beta = (q->alpha - q->beta) / sqrt(2);
    q->alpha = new_alpha;
    q->beta = new_beta;
}

// Compuerta CNOT (Crea Entrelazamiento si el control está en superposición)
void apply_cnot(Qubit *control, Qubit *target) {
    // Si el control tiene componente en |1>, invertimos la componente del target
    // Nota: Esta es una simplificación funcional para demostrar la lógica CNOT
    if (control->beta != 0.0) { 
        double temp = target->alpha;
        target->alpha = target->beta;
        target->beta = temp;
    }
}

// Función de Medición (Colapso de la función de onda)
int measure_qubit(Qubit q) {
    double random_value = (double)rand() / RAND_MAX;
    // La probabilidad de medir 0 es alpha^2
    if (random_value < (q.alpha * q.alpha)) {
        return 0;
    } else {
        return 1;
    }
}

void display_state(Qubit qubits[], int n) {
    printf("\n--- Estado Cuántico Actual ---\n");
    for (int i = 0; i < n; i++) {
        printf("Qubit %d: Amplitud(|0>)=%.2f, Amplitud(|1>)=%.2f\n", i, qubits[i].alpha, qubits[i].beta);
    }
}

int main() {
    srand(time(NULL));
    Qubit qubits[NUM_QUBITS];

    printf("1. Inicializando Qubits en |0>...\n");
    initialize_qubit(&qubits[0]);
    initialize_qubit(&qubits[1]);
    display_state(qubits, NUM_QUBITS);

    printf("\n2. Aplicando Hadamard a Qubit 0 (Superposición)...\n");
    apply_hadamard(&qubits[0]);
    display_state(qubits, NUM_QUBITS);

    printf("\n3. Aplicando CNOT (Qubit 0 Control -> Qubit 1 Target) (Entrelazamiento)...\n");
    apply_cnot(&qubits[0], &qubits[1]);
    display_state(qubits, NUM_QUBITS);

    printf("\n4. Realizando Mediciones (Colapso)...\n");
    for (int i = 0; i < NUM_QUBITS; i++) {
        int res = measure_qubit(qubits[i]);
        printf("Resultado medición Qubit %d: |%d>\n", i, res);
    }

    return 0;
}