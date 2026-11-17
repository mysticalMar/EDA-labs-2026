//Grupo 33 Romano Mariana, Masucci Fiona
#include <stdio.h>
#include <stdlib.h>
#include "RS.h"
#include "RAC.h"
#include "RAL.h"


//ANALISIS DE RESULTADOS: RAL
//Maximo de evocacion exitosa: 1964
//Medio de evocacion exitosa: 559.779785
//Maximo de evocacion no exitosa: 1998
//Medio de evocacion no exitosa: 1580.086670
//viendo los valores, el costo es muy alto en las evocaciones,revisa casi toda la estructura en el peor caso.
//Sin embargo, estos resultados son razonables, ya que una vez que se llena, cada evoacion no exitosa analiza
//bloques contiguos de celdas ocupadas y libres hasta llegar a una celda virgen.
//Como comclusión, los valores son esperables para un RAL de tal densidad, demostrando poca eficiencia para el volumen de datos.

//ANALISIS DE RESULTADOS: RAC
//Maximo de evocacion exitosa: 64
//Medio de evocacion exitosa: 29.463908
//Maximo de evocacion no exitosa: 68
//Medio de evocacion no exitosa:  56.088737
//En el RAC podemos observar una disminución drástica respecto al RAL.
//Esto se debe a la manera de localizar, mostrando que esta es mucho más eficiente que la anterior

//ANALISIS DE RESULTADOS: RS
//Maximo de evocacion exitosa:  19
//Medio de evocacion exitosa: 5.208736
//Maximo de evocacion no exitosa:  19
//Medio de evocacion no exitosa:  7.238675
//El rebalse separado presenta el menor costo para ambos resultados, permitiendo llegar a la conclusión de que la estructura más eficiente
//respecto a celdas consultadas es el Rebalse Separado.

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
                //RAL
                printf("\n--- REBALSE ABIERTO LINEAL (RAL) ---\n");
                printf("Maximo de evocacion exitosa: %d \n",RAL_max_E);
                printf("Medio de evocacion exitosa: %f \n",(float)RAL_t_E/RAL_evocar_E);
                printf("Maximo de evocacion no exitosa: %d \n",RAL_max_F);
                printf("Medio de evocacion no exitosa: %f \n", (float)RAL_t_F/RAL_evocar_F);
                //RAC
                printf("\n--- REBALSE ABIERTO CUADRATICO (RAC) ---\n");
                printf("Maximo de evocacion exitosa: %d \n", maxEvocExitosa_RAC);
                printf("Medio de evocacion exitosa: %f \n", (float)totalEvocExitosa_RAC/cantEvocExitosa_RAC);
                printf("Maximo de evocacion no exitosa: %d \n", maxEvocNoExitosa_RAC);
                printf("Medio de evocacion no exitosa: %f \n", (float)totalEvocNoExitosa_RAC/cantEvocNoExitosa_RAC);
                //RS
                printf("\n--- REBALSE SEPARADO (RS) ---\n");
                printf("Maximo de evocacion exitosa: %d \n", maxEvocExitosa_RS);
                printf("Medio de evocacion exitosa: %f \n", (float)totalEvocExitosa_RS/cantEvocExitosa_RS);
                printf("Maximo de evocacion no exitosa: %d \n", maxEvocNoExitosa_RS);
                printf("Medio de evocacion no exitosa: %f \n", (float)totalEvocNoExitosa_RS/cantEvocNoExitosa_RS);

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
    return 0;
}
