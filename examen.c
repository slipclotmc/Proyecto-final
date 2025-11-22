/*Velázquez Domínguez Ricardo
Fundamentos de programación - Proyecto final */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_OYENTES 100
#define NUM_CANCIONES 10

// Prototipos de funciones
int leerVotoOyente(int numeroOyente, int votos[3]);
void leerVotos(int votos[MAX_OYENTES][3], int *numOyentes);
void calcularResultados(int votos[MAX_OYENTES][3], int numOyentes, int puntuaciones[NUM_CANCIONES], int *primera, int *segunda);
void calcularPremios(int votos[MAX_OYENTES][3], int numOyentes, int primera, int segunda, int puntosOyentes[MAX_OYENTES]);
void encontrarGanadores(int puntosOyentes[], int numOyentes);
void mostrarResultados(int puntuaciones[NUM_CANCIONES], int primera, int segunda, int puntosOyentes[MAX_OYENTES], int numOyentes);

int main() {
    int votos[MAX_OYENTES][3];
    int puntuaciones[NUM_CANCIONES] = {0};
    int puntosOyentes[MAX_OYENTES] = {0};
    int numOyentes, primera, segunda;
    
    // inciso 1)
    leerVotos(votos, &numOyentes);
    
    if (numOyentes == 0) {
        printf("No se ingresaron votos. Programa terminado.\n");
        return 0;
    }
    
    // inciso 2)
    calcularResultados(votos, numOyentes, puntuaciones, &primera, &segunda);
    
    // inciso 3)
    calcularPremios(votos, numOyentes, primera, segunda, puntosOyentes);
    
    // Mostrar todos los resultados
    mostrarResultados(puntuaciones, primera, segunda, puntosOyentes, numOyentes);
    
    // Encontrar y mostrar ganador(es)
    encontrarGanadores(puntosOyentes, numOyentes);
    
    return 0;
}

// Función para leer el voto de un oyente con validación
int leerVotoOyente(int numeroOyente, int votos[3]) {
    int v1, v2, v3;
    
    while (1) {  // Se repite hasta que ingrese votos válidos
        printf("Oyente %d: ", numeroOyente);
        
        // Leer los tres votos
        if (scanf("%d %d %d", &v1, &v2, &v3) != 3) {
            printf("Error: Debe ingresar exactamente 3 números. Intente nuevamente.\n");
            while (getchar() != '\n');
            continue;
        }
        
        // Verificar condición de terminación
        if (v1 == -1) {
            return -1; 
        }
        
        // Verificar rangos (0-9)
        if (v1 < 0 || v1 > 9 || v2 < 0 || v2 > 9 || v3 < 0 || v3 > 9) {
            printf("Error: Las canciones deben ser números entre 0 y 9. Intente nuevamente.\n");
            continue;
        }
        
        // Verificar que las tres canciones sean diferentes
        if (v1 == v2 || v1 == v3 || v2 == v3) {
            printf("Error: Debe elegir 3 canciones DIFERENTES. Intente nuevamente.\n");
            continue;
        }
        
        // Votos válidos
        votos[0] = v1;
        votos[1] = v2;
        votos[2] = v3;
        return 1;  // Éxito
    }
}

// inciso 1)
void leerVotos(int votos[MAX_OYENTES][3], int *numOyentes) {
    int oyente = 0;
    int resultado;
    
    printf("INGRESO DE VOTOS\n");
    printf("Formato: primer_lugar segundo_lugar tercer_lugar\n");
    printf("Las canciones van del 0 al 9. Ingrese -1 para terminar.\n");
    printf("Debe elegir 3 canciones DIFERENTES.\n\n");
    
    while (oyente < MAX_OYENTES) {
        resultado = leerVotoOyente(oyente, votos[oyente]);
        
        if (resultado == -1) {
            break;  // Terminar entrada
        } else if (resultado == 1) {
            oyente++;  // Voto válido, siguiente oyente
        }
    }
    
    *numOyentes = oyente;
    printf("\nTotal de oyentes registrados: %d\n\n", *numOyentes);
}

// inciso 2)  Calcular votos por canción y encontrar las más votadas
void calcularResultados(int votos[MAX_OYENTES][3], int numOyentes, int puntuaciones[NUM_CANCIONES], int *primera, int *segunda) {
    int i;
    
    // Inicializar puntuaciones
    for (i = 0; i < NUM_CANCIONES; i++) {
        puntuaciones[i] = 0;
    }
    
    // Calcular puntuaciones de cada canción
    for (i = 0; i < numOyentes; i++) {
        // Primer lugar: 3 puntos
        puntuaciones[votos[i][0]] += 3;
        // Segundo lugar: 2 puntos
        puntuaciones[votos[i][1]] += 2;
        // Tercer lugar: 1 punto
        puntuaciones[votos[i][2]] += 1;
    }
    
    // Encontrar las dos canciones más votadas
    *primera = 0;
    *segunda = 1;
    
    // Asegurar que primera sea la mayor
    if (puntuaciones[*segunda] > puntuaciones[*primera]) {
        int temp = *primera;
        *primera = *segunda;
        *segunda = temp;
    }
    
    // Buscar en todas las canciones
    for (i = 2; i < NUM_CANCIONES; i++) {
        if (puntuaciones[i] > puntuaciones[*primera]) {
            *segunda = *primera;
            *primera = i;
        } else if (puntuaciones[i] > puntuaciones[*segunda]) {
            *segunda = i;
        }
    }
}

// Inciso 3: Calcular puntos de cada oyente
void calcularPremios(int votos[MAX_OYENTES][3], int numOyentes, int primera, int segunda, int puntosOyentes[MAX_OYENTES]) {
    int i, j;
    int tienePrimera, tieneSegunda;
    
    // Inicializar puntos de oyentes
    for (i = 0; i < numOyentes; i++) {
        puntosOyentes[i] = 0;
    }
    
    for (i = 0; i < numOyentes; i++) {
        tienePrimera = 0;
        tieneSegunda = 0;
        
        // Verificar si el oyente votó por las canciones ganadoras
        for (j = 0; j < 3; j++) {
            if (votos[i][j] == primera) {
                tienePrimera = 1;
            }
            if (votos[i][j] == segunda) {
                tieneSegunda = 1;
            }
        }
        
        // Calcular puntos según las reglas
        if (tienePrimera) {
            puntosOyentes[i] += 30;
        }
        if (tieneSegunda) {
            puntosOyentes[i] += 20;
        }
        if (tienePrimera && tieneSegunda) {
            puntosOyentes[i] += 10;
        }
    }
}

// Encontrar y mostrar todos los ganadores (maneja empates)
void encontrarGanadores(int puntosOyentes[], int numOyentes) {
    int maxPuntos = 0;
    int i;
    int ganadores[MAX_OYENTES];
    int numGanadores = 0;
    
    // Encontrar puntuación máxima
    for (i = 0; i < numOyentes; i++) {
        if (puntosOyentes[i] > maxPuntos) {
            maxPuntos = puntosOyentes[i];
        }
    }
    
    // Encontrar todos los oyentes con puntuación máxima
    for (i = 0; i < numOyentes; i++) {
        if (puntosOyentes[i] == maxPuntos) {
            ganadores[numGanadores] = i;
            numGanadores++;
        }
    }
    
    // Mostrar resultados
    printf("\n-- RESULTADO FINAL --\n");
    
    if (numGanadores == 1) {
        printf("GANADOR ÚNICO\n");
        printf("Oyente número: %d\n", ganadores[0]);
        printf("Puntos obtenidos: %d\n", maxPuntos);
    } else {
        printf("EMPATE - %d GANADORES\n", numGanadores);
        for (i = 0; i < numGanadores; i++) {
            printf("Oyente número: %d\n", ganadores[i]);
            printf("Puntos obtenidos: %d\n", maxPuntos);
        }
        
        // Sorteo para premio único
        srand(time(NULL));
        int premioUnico = ganadores[rand() % numGanadores];
        printf("\nGANADOR DEL SORTEO PARA PREMIO ÚNICO: Oyente %d\n", premioUnico);
    }
}

// Mostrar todos los resultados
void mostrarResultados(int puntuaciones[NUM_CANCIONES], int primera, int segunda, int puntosOyentes[MAX_OYENTES], int numOyentes) {
    int i;
    
    printf("-- RESULTADOS DEL CONCURSO --\n\n");
    
    // Mostrar puntuaciones de canciones
    printf("PUNTUACIONES POR CANCIÓN:\n");
    for (i = 0; i < NUM_CANCIONES; i++) {
        printf("Canción %d: %d votos\n", i, puntuaciones[i]);
    }
    
    printf("\nCANCIONES MÁS VOTADAS:\n");
    printf("1a canción: %d (%d votos)\n", primera, puntuaciones[primera]);
    printf("2a canción: %d (%d votos)\n\n", segunda, puntuaciones[segunda]);
    
    // Mostrar puntos de oyentes
    printf("PUNTOS DE OYENTES:\n");
    for (i = 0; i < numOyentes; i++) {
        printf("Oyente %d: %d puntos\n", i, puntosOyentes[i]);
    }
}
        }
    }
}

// Inciso 3: Calcular puntos de cada oyente
void calcularPremios(int votos[MAX_OYENTES][3], int oyentes, int primera, int segunda, int puntosOyentes[MAX_OYENTES]) {
    int i, j;
    int tienePrimera, tieneSegunda;
    
    // Inicializar puntos de oyentes
    for (i = 0; i < oyentes; i++) {
        puntosOyentes[i] = 0;
    }
    
    for (i = 0; i < oyentes; i++) {
        tienePrimera = 0;
        tieneSegunda = 0;
        
        // Verificar si el oyente votó por las canciones ganadoras
        for (j = 0; j < 3; j++) {
            if (votos[i][j] == primera) {
                tienePrimera = 1;
            }
            if (votos[i][j] == segunda) {
                tieneSegunda = 1;
            }
        }
        
        // Calcular puntos según las reglas
        if (tienePrimera) {
            puntosOyentes[i] += 30;
        }
        if (tieneSegunda) {
            puntosOyentes[i] += 20;
        }
        if (tienePrimera && tieneSegunda) {
            puntosOyentes[i] += 10;
        }
    }
}

// Encontrar y mostrar todos los ganadores (maneja empates)
void encontrarGanadores(int puntosOyentes[], int oyentes) {
    int maxPuntos = 0;
    int i;
    int ganadores[MAX_OYENTES];
    int numGanadores = 0;
    
    // Encontrar puntuación máxima
    for (i = 0; i < oyentes; i++) {
        if (puntosOyentes[i] > maxPuntos) {
            maxPuntos = puntosOyentes[i];
        }
    }
    
    // Encontrar todos los oyentes con puntuación máxima
    for (i = 0; i < oyentes; i++) {
        if (puntosOyentes[i] == maxPuntos) {
            ganadores[numGanadores] = i;
            numGanadores++;
        }
    }
    
    // Mostrar resultados
    printf("\n-- RESULTADO FINAL --\n");
    
    if (numGanadores == 1) {
        printf("GANADOR ÚNICO\n");
        printf("Oyente número: %d\n", ganadores[0]);
        printf("Puntos obtenidos: %d\n", maxPuntos);
    } else {
        printf("EMPATE - %d GANADORES\n", numGanadores);
        for (i = 0; i < numGanadores; i++) {
            printf("Oyente número: %d\n", ganadores[i]);
            printf("Puntos obtenidos: %d\n", maxPuntos);
        }
        
        // Sorteo para premio único
        srand(time(NULL));
        int premioUnico = ganadores[rand() % numGanadores];
        printf("\nGANADOR DEL SORTEO PARA PREMIO ÚNICO: Oyente %d\n", premioUnico);
    }
}

// Mostrar todos los resultados
void mostrarResultados(int puntuaciones[NUM_CANCIONES], int primera, int segunda, int puntosOyentes[MAX_OYENTES], int oyentes) {
    int i;
    
    printf("-- RESULTADOS DEL CONCURSO --\n\n");
    
    // Mostrar puntuaciones de canciones
    printf("PUNTUACIONES POR CANCIÓN:\n");
    for (i = 0; i < NUM_CANCIONES; i++) {
        printf("Canción %d: %d votos\n", i, puntuaciones[i]);
    }
    
    printf("\nCANCIONES MÁS VOTADAS:\n");
    printf("1a canción: %d (%d votos)\n", primera, puntuaciones[primera]);
    printf("2a canción: %d (%d votos)\n\n", segunda, puntuaciones[segunda]);
    
    // Mostrar puntos de oyentes
    printf("PUNTOS DE OYENTES:\n");
    for (i = 0; i < oyentes; i++) {
        printf("Oyente %d: %d puntos\n", i, puntosOyentes[i]);
    }
}
