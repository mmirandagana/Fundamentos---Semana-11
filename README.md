# ACIF101 - Fundamentos de Computación de Alto Desempeño (Semana 11)

**Evaluación Sumativa 5: Optimización con MPI y Simulación Cuántica**

* **Autor:** Manuel Miranda
* **Fecha:** 14 de Diciembre, 2025
* **Curso:** ACIF101 - Universidad Andrés Bello Online

---

## 📋 Descripción del Proyecto

Este repositorio contiene las implementaciones de código C desarrolladas para la Semana 11, enfocadas en dos paradigmas avanzados de computación:

1.  **Computación Paralela (MPI):** Evaluación de rendimiento, escalabilidad y gestión de concurrencia (prevención de deadlocks) en sistemas distribuidos.
2.  **Simulación Cuántica:** Emulación de lógica cuántica (Qubits, Superposición, Entrelazamiento) utilizando estructuras de datos clásicas para comprender el comportamiento probabilístico de circuitos cuánticos.

El objetivo es demostrar el uso eficiente de recursos de hardware y la aplicación de software de alto desempeño.

---

## 🛠️ Entorno de Desarrollo y Requisitos

Para compilar y ejecutar estos programas se requiere un entorno Linux (nativo o WSL).

* **Sistema Operativo:** Ubuntu 24.04 (WSL)
* **Compilador:** GCC y OpenMPI Wrapper (`mpicc`) 
* **Bibliotecas:** `mpi.h`, `math.h`, `time.h`, `stdlib.h`

### Instalación de Dependencias (Ubuntu/Debian)
Si no tienes configurado MPI, ejecuta:
```bash
sudo apt update
sudo apt install build-essential openmpi-bin libopenmpi-dev
