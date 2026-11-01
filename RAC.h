

#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "RS.h"
/// M : N / ρ --> 2000 / 0,83 --> M = 2409,6 , primo mas cercano 2411.
#define MRAC 2411

///Variables Globales Costos
int maxEvocExitosa_RAC = 0, maxEvocNoExitosa_RAC = 0;
int totalEvocExitosa_RAC = 0, totalEvocNoExitosa_RAC = 0;
int cantEvocExitosa_RAC = 0, cantEvocNoExitosa_RAC = 0;



  typedef struct {
    int DNI;
    char nombreyapellido[50];
    char domicilio[80];
    int cp;
    int mesa;
    int circuito;
} PadronRAC;
typedef struct {
   char estado;
   PadronRAC padron;
  } CeldaRAC;
  typedef struct{
   CeldaRAC celda[MRAC];
   int cant;
  } RAC;

     int CantElem=0;
    void init_RAC(RAC *tabla){
     int i;
    for(i=0; i<MRAC; i++){
    tabla->celda[i].estado = '*';///Inicializamos todas las celdas como virgenes
  }
   tabla->cant = 0;
 }

int confirmaRAC(CeldaRAC l[], int pos, PadronRAC elemento) {
    return l[pos].estado == 'O' &&
           l[pos].padron.DNI == elemento.DNI &&
           strcasecmp(l[pos].padron.nombreyapellido, elemento.nombreyapellido) == 0 &&
           strcasecmp(l[pos].padron.domicilio, elemento.domicilio) == 0 &&
           l[pos].padron.cp == elemento.cp &&
           l[pos].padron.mesa == elemento.mesa &&
           l[pos].padron.circuito == elemento.circuito;
}


  int Localizar_RAC(RAC *tabla, int dni, int *pos, int *costo) {
    *pos = hashing(dni, MRAC);
    int i = *pos;
    int aux = -1;
    int contador = 0;
    int k = 1;
    int flag=0;

    *costo = 0;

    while (contador < MRAC && tabla->celda[i].estado != '*'&&
           tabla->celda[i].padron.DNI != dni) {


        if (tabla->celda[i].estado == '+'&&flag==0) {
            aux = i;
            flag=1;
        }
        // Calculamos la siguiente posición usando exploración cuadrática
        i = (i + k) % MRAC;
        k++;
        contador++;
        (*costo)++;
    }

    // Caso 1: Prestador encontrado
    if (tabla->celda[i].padron.DNI == dni&&tabla->celda[i].estado=='O') {
        *pos = i;
        return 1;  // Encontrado
    }
    else {
    // Caso 2: No encontrado, pero se puede dar de alta
    if (tabla->celda[i].estado == '+' && aux != -1) {
       *pos = aux;
       } else {
       *pos = i;
           }

    return 0;
    }

}
int Alta_RAC(RAC *tabla, PadronRAC padron, int *costo) {
    int pos = 0;
    int resultado = Localizar_RAC(tabla, padron.DNI, &pos, costo);

    if (tabla->cant >= MRAC) {
        return -1;  // No hay espacio disponible
    }

    if (resultado == 1) {
        return 0;  // Fallo en el alta: el prestador ya existe
    } else {
        // Insertamos el prestador en la posición encontrada
        tabla->celda[pos].padron = padron;
        tabla->celda[pos].estado = 'O';  // Marcamos la celda como ocupada
        tabla->cant++;
        return 1;  // Alta exitosa
    }
}


int Baja_RAC(RAC *tabla, PadronRAC padron, int *costo){
    int pos = 0;
    if (tabla->cant==0) return -1;
    if (!Localizar_RAC(tabla, padron.DNI, &pos, costo)) return 0;
    if (confirmaRAC(tabla->celda, pos, padron)) {
        tabla->celda[pos].estado = '+';
        tabla->cant--;
        return 1;
    }
    return 0;
}
int Evocar_RAC(RAC *tabla, int dni, int *costo, PadronRAC *c) {
    int pos = 0;
     if (tabla->cant == 0) {
        return -1;  // Estructura vacía
    }
    int encontrado = Localizar_RAC(tabla, dni, &pos, costo);


    if (encontrado == 1) {
        *c=tabla->celda[pos].padron;
        // Evocación exitosa
        totalEvocExitosa_RAC += *costo;
        cantEvocExitosa_RAC++;
        if (*costo > maxEvocExitosa_RAC) {
            maxEvocExitosa_RAC = *costo;
        }
        return 1;  // Evocación exitosa
    } else {
        // Evocación no exitosa
        totalEvocNoExitosa_RAC += *costo;
        cantEvocNoExitosa_RAC++;
        if (*costo > maxEvocNoExitosa_RAC) {
            maxEvocNoExitosa_RAC = *costo;
        }
        return 0;  // Evocación no exitosa
    }
}

void MostrarEstructura_RAC(RAC *tabla) {
    int counta = 0;  // Contador para la paginación
    int i;
    int lista_vacia = 1;  // Bandera para verificar si la lista está vacía
    int totalElectoresMostrados = 0;
    // Verificar si la lista está vacía
    for (i = 0; i < MRAC; i++) {
        if (tabla->celda[i].estado == 'O') {
            lista_vacia = 0;
            break;
        }
    }

    if (lista_vacia) {
        printf("La lista de electores esta vacia.\n");
        getchar();  // Esperar a que el usuario presione ENTER
        return;  // Salir de la función
    }

    // Mostrar las celdas si no está vacía
    for (i = 0; i < MRAC && totalElectoresMostrados < MRAL ; i++) {
        // Mostrar estado de la celda

        if (tabla->celda[i].estado == '*') {
            printf("Celda %d: Virgen (nunca usada)\n", i);
        } else if (tabla->celda[i].estado == '+') {
            printf("Celda %d: Libre (usada previamente)\n", i);
        } else if (tabla->celda[i].estado == 'O') {
            // Mostrar datos del prestador en celdas ocupadas
            PadronRAC p = tabla->celda[i].padron;
            printf("Celda %d: Ocupada\n", i);
              printf("Elector %d:\n", i);
                printf("DNI: %d\n", p.DNI);
                printf("Nombre y Apellido: %s\n", p.nombreyapellido);
                printf("Domicilio: %s\n", p.domicilio);
                printf("Codigo Postal: %d\n", p.cp);
                printf("Mesa: %d\n", p.mesa);
                printf("Circuito: %d\n", p.circuito);
                printf("------------------------------------------\n");

            totalElectoresMostrados++;  // Incrementar el contador
        }




        // Paginación: detener cada 5 celdas
        counta++;
        if (counta % 5 == 0) {
            printf("\nPresione ENTER para continuar o cualquier otra tecla para salir...\n");
            char cont = getchar();  // Captura la tecla presionada

            // Si no es ENTER, terminar la visualización
            if (cont != '\n') {
                break;
            }
        }


}
    // Pausa final si quedaron elementos sin mostrar
    if (counta % 5 != 0) {
        printf("Presione ENTER para volver al menu principal...\n");
        getchar();
    }


}







#endif // RAC_H_INCLUDED
