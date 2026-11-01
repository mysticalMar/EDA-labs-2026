#include <stdio.h>
#include <stdlib.h>
#include "RS.h"
#include "RAC.h"
#include "RAL.h"

int lectura_operaciones(Padron RAL[], RAC *tablaRAC, RS *tablaRS) {
    Padron aux;
    PadronRAC auxRAC;
    PadronRS auxRS;
    RAL_inicializar(RAL);
    init_RAC(tablaRAC);
    init_RS(tablaRS);

    int opcion = 0, exito, pos;
    int costo = 0;
    int DNI;

    FILE *fp = fopen("Operaciones_Padron.txt", "r");
    if (fp == NULL) {
        printf("No se puede abrir el archivo\n");
        return 0;
    }

    while (!feof(fp)) {
       fscanf(fp, "%d", &opcion);
            fscanf(fp, "%d", &aux.DNI);
            if (opcion==1||opcion==2){
                fscanf(fp, " %[^\n]", aux.nombreyapellido);
                fscanf(fp, " %[^\n]", aux.domicilio);
                fscanf(fp, "%d", &aux.cp);
    fscanf(fp, "%d", &aux.mesa);
    fscanf(fp, "%d", &aux.circuito);

            // Copiar los datos de 'aux' a 'auxRAC' para RAC
            auxRAC.DNI = aux.DNI;
            strcpy(auxRAC.nombreyapellido, aux.nombreyapellido);
            strcpy(auxRAC.domicilio, aux.domicilio);
            auxRAC.cp=aux.cp;
            auxRAC.mesa=aux.mesa;
            auxRAC.circuito=aux.circuito;


            // Copiar también para RS
            auxRS.DNI = aux.DNI;
            strcpy(auxRS.nombreyapellido, aux.nombreyapellido);
            strcpy(auxRS.domicilio, aux.domicilio);
            auxRS.cp=aux.cp;
            auxRS.mesa=aux.mesa;
            auxRS.circuito=aux.circuito;

            if (opcion == 1) {  // Alta
                if (CantElemRAL < MRAL) {
                    Alta_RAL(RAL, aux, aux.DNI, &exito, opcion);
                }
                if (CantElem < MRAC) {
                    Alta_RAC(tablaRAC, auxRAC, &costo);
                }
                Alta_RS(tablaRS, auxRS);
            } else {  // Baja
                DNI = aux.DNI;
                Baja_RAL(RAL, DNI, &exito, aux, opcion);
                Baja_RAC(tablaRAC, auxRAC, &costo);
                Baja_RS(tablaRS, auxRS);
            }
        } else if (opcion == 3) {  // Evocar

            Evocar_RAL(RAL, &aux, aux.DNI, &exito, opcion);
            Evocar_RAC(tablaRAC, aux.DNI, &costo, &auxRAC);
             Evocar_RS(tablaRS, aux.DNI, &auxRS, &costo);
        }
    }

    fclose(fp);
    return 1;
}


int main()
{
    RS tablaRS;
    int opcion;
    Padron RAL[MRAL];
    RAC tablaRAC;

    do {
        printf("1: Comparar estructuras \n");
        printf("2: Mostrar: RAL \n");
        printf("3: Mostrar: RAC \n");
        printf("4: Mostrar: RS \n");
        printf("5: Salir \n");
        printf("-------------------------------------------------\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:  // Lectura y comparación de operaciones
                lectura_operaciones(RAL, &tablaRAC, &tablaRS);
                break;

            case 2:  // Mostrar RAL
                MostrarEstructura_RAL(RAL);
                break;

            case 3:  // Mostrar RAC
                MostrarEstructura_RAC(&tablaRAC);
                break;

            case 4:  // Mostrar RS
                MostrarEstructura_RS(&tablaRS);
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Error elija una opcion valida. \n");
                break;
        }
    } while (opcion != 5);
    //ANALISIS DE RESULTADOS: RAL
//Maximo de evocacion exitosa: 121
//Medio de evocacion exitosa: 4
//Maximo de evocacion no exitosa: 134
//Medio de evocacion no exitosa: 107
//Viendo los valores de la evocación exitosa, contrastan considerablemente con los de las evocaciones no exitosas,
//para las cuales el valor máximo es de 134 y el medio es de 107.
//Sin embargo, estos resultados son razonables, ya que, una vez que la estructura se encuentre más llena,
//cada evocación no exitosa analizará varias veces 134 celdas, es decir, toda la estructura.
//Entonces, como conclusión, se puede afirmar que los valores obtenidos son razonables respecto a la estructura, y su forma de localización.

//ANALISIS DE RESULTADOS: RAC
//Costo maximo de evocacion exitosa en RAC: 60
//Costo medio de evocacion exitosa en RAC: 2.15
//Costo maximo de evocacion no exitosa en RAC: 131
//Costo medio de evocacion no exitosa en RAC: 12.14
//En el RAC podemos observar una disminución considerable respecto al RAL, debido a la manera de localizar, mostrando que esta es mucho más eficiente que la anterior.

//ANALISIS DE RESULTADOS: RS
//Costo maximo de evocacion exitosa en RS: 7
//Costo medio de evocacion exitosa en RS: 1.58
//Costo maximo de evocacion no exitosa en RS: 4
//Costo medio de evocacion no exitosa en RS: 0.76
//El rebalse separado presenta el menor costo para ambos resultados, permitiendo llegar a la conclusión de que la estructura más eficiente
//respecto a celdas consultadas es el Rebalse Separado.
    return 0;
}
