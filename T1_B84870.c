

#include <stdio.h>

#define MAX_TAM 100

int leer_matriz(const char* nombre_archivo, int matriz[MAX_TAM][MAX_TAM], int* tam) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo.\n");
        return 0;
    }

    int fila = 0, columna = 0;
    int valor;
    int columnas_esperadas = -1;

    while (!feof(archivo)) {
        columna = 0;
        for (int i = 0; i < MAX_TAM; i++) {
            if (fscanf(archivo, "%d", &valor) != 1)
                break;

            if (valor != 0 && valor != 1) {
                printf("Error: La matriz contiene un valor no binario: %d\n", valor);
                fclose(archivo);
                return 0;
            }

            matriz[fila][columna] = valor;
            columna++;
            if (fgetc(archivo) == '\n') {
                break;
            }
        }

        if (columnas_esperadas == -1) {
            columnas_esperadas = columna;
        } else if (columna != columnas_esperadas) {
            printf("Error: La matriz no es cuadrada (longitudes de filas distintas).\n");
            fclose(archivo);
            return 0;
        }

        fila++;
    }

    if (fila != columnas_esperadas) {
        printf("Error: La matriz no es cuadrada (filas != columnas).\n");
        fclose(archivo);
        return 0;
    }

    *tam = fila;
    fclose(archivo);
    return 1;
}

int encontrar_diagonal_mas_larga(int matriz[MAX_TAM][MAX_TAM], int tam) {
    int max_longitud = 0;

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            if (matriz[i][j] == 1) {
                int longitud = 1;
                int fila = i - 1;
                int col = j - 1;

                while (fila >= 0 && col >= 0 && matriz[fila][col] == 1) {
                    longitud++;
                    fila--;
                    col--;
                }

                if (longitud > max_longitud) {
                    max_longitud = longitud;
                }
            }
        }
    }

    return max_longitud;
}

void imprimir_matriz(int matriz[MAX_TAM][MAX_TAM], int tam) {
    printf("La matriz utilizada corresponde a:\n");
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matriz[MAX_TAM][MAX_TAM];
    int tam;

    if (!leer_matriz("matriz.txt", matriz, &tam)) {
        return 1;
    }

    imprimir_matriz(matriz, tam);
    int resultado = encontrar_diagonal_mas_larga(matriz, tam);
    printf("La secuencia de 1s más grande es: %d\n", resultado);

    return 0;
}
