#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265358979323846

// --- ESTRUCTURAS ---

// Qubit simple para compuertas lógicas (Suma)
typedef struct {
    int state; // 0 o 1
} QubitLogic;

// Qubit complejo para QFT (Amplitudes)
typedef struct {
    double real;
    double imag;
} ComplexState;

// --- FUNCIONES PARA SUMA CUÁNTICA (Half Adder) ---

// Compuerta CNOT (XOR): Target cambia si Control es 1
void apply_cnot(QubitLogic *control, QubitLogic *target) {
    if (control->state == 1) {
        target->state = !target->state;
    }
}

// Compuerta Toffoli (CCNOT / AND): Target cambia si ambos Controles son 1
void apply_toffoli(QubitLogic *c1, QubitLogic *c2, QubitLogic *target) {
    if (c1->state == 1 && c2->state == 1) {
        target->state = !target->state;
    }
}

void quantum_sum_simulation() {
    printf("\n=== 1. SIMULACIÓN DE SUMA CUÁNTICA (Half Adder) ===\n");
    // Inicializar Qubits: A=1, B=1
    QubitLogic qA = {1};
    QubitLogic qB = {1};
    QubitLogic qSum = {0};   // Resultado Suma (XOR)
    QubitLogic qCarry = {0}; // Acarreo (AND)

    printf("Entrada: A=%d, B=%d\n", qA.state, qB.state);

    // Paso 1: Calcular Suma (CNOT)
    // Copiamos estado de A y B a Sum para simular el circuito
    QubitLogic tempA = qA; 
    QubitLogic tempB = qB;
    
    // En un Half Adder cuántico:
    // Sum = A XOR B (CNOT)
    // Carry = A AND B (Toffoli)
    
    // Simulación lógica:
    apply_cnot(&tempA, &qSum); // qSum = qSum XOR A
    apply_cnot(&tempB, &qSum); // qSum = qSum XOR B (Resultado final Suma)

    // Paso 2: Calcular Acarreo (Toffoli)
    apply_toffoli(&qA, &qB, &qCarry);

    printf("Resultado: Suma=%d, Carry=%d\n", qSum.state, qCarry.state);
    printf("(Nota: 1+1 binario es 10, es decir Suma 0 y Carry 1)\n");
}

// --- FUNCIONES PARA QFT (Transformada de Fourier) ---

void qft_simulation() {
    printf("\n=== 2. SIMULACIÓN DE FOURIER CUÁNTICA (QFT) ===\n");
    int num_qubits = 3;
    int num_states = 1 << num_qubits; // 2^3 = 8 estados
    
    // Inicializar vector de estado |000>
    ComplexState *states = (ComplexState*)malloc(sizeof(ComplexState) * num_states);
    for(int i=0; i<num_states; i++) { states[i].real = 0.0; states[i].imag = 0.0; }
    states[0].real = 1.0; // Estado inicial |0>

    printf("Estado Inicial: |000> (Amplitud 1.0)\n");

    // Aplicar QFT (Simulación matemática de la transformación)
    // La QFT transforma un estado base en una superposición uniforme con fases
    ComplexState *new_states = (ComplexState*)malloc(sizeof(ComplexState) * num_states);
    
    printf("Aplicando rotaciones de fase...\n");
    for (int k = 0; k < num_states; k++) {
        new_states[k].real = 0.0;
        new_states[k].imag = 0.0;
        for (int j = 0; j < num_states; j++) {
            // Fórmula QFT: y_k = (1/sqrt(N)) * sum(x_j * exp(2*pi*i*j*k/N))
            double angle = 2.0 * PI * j * k / num_states;
            double cos_val = cos(angle);
            double sin_val = sin(angle);
            
            // Multiplicación de complejos
            new_states[k].real += (states[j].real * cos_val - states[j].imag * sin_val);
            new_states[k].imag += (states[j].real * sin_val + states[j].imag * cos_val);
        }
        new_states[k].real /= sqrt(num_states);
        new_states[k].imag /= sqrt(num_states);
    }

    // Mostrar amplitudes resultantes
    printf("Amplitudes Finales (Superposición Uniforme):\n");
    for (int i = 0; i < num_states; i++) {
        // Calcular probabilidad (módulo cuadrado)
        double prob = new_states[i].real*new_states[i].real + new_states[i].imag*new_states[i].imag;
        printf("|%d>: Real=%.2f, Imag=%.2f, Prob=%.2f\n", i, new_states[i].real, new_states[i].imag, prob);
    }

    free(states);
    free(new_states);
}

int main() {
    quantum_sum_simulation();
    qft_simulation();
    return 0;
}