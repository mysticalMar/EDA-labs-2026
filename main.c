#include <stdio.h>
#include <stdlib.h>
#include "LSOBB.h"
#include "LVO.h"
int lectura_operaciones(Padron LSOBB[]) {
    //init_ABB(arbol);  // Inicializa el árbol
    //inicializarLSO(LSO);  // Inicializa las listas secuenciales
    int opcion = 0, exitoLVO = 0, exitoLSOBB = 0, exito = 0;
    int DNI, prestadorescargadosLSO = 0, padronescargadosLSOBB = 0;
    LVO lvo;
    Padron aux, aux2;
   // PrestadorABB a;  // Variable para almacenar datos en ABB
    if (CantElem==0){
    FILE *fp = fopen("Operaciones-Padrón.txt", "r");

    if (fp == NULL) {
        printf("No se puede abrir el archivo\n");
        return 0;
    }
    else {
      while (!feof(fp)){
            fscanf(fp, "%d", &opcion);
            fscanf(fp, "%d", &aux.DNI);
            if (opcion==1||opcion==2){
                fscanf(fp, " %[^\n]", aux.nombreyapellido);
                fscanf(fp, " %[^\n]", aux.domicilio);
                fscanf(fp, " %[^\n]", &aux.cp);
                fscanf(fp, " %[^\n]", &aux.mesa);
                fscanf(fp, " %[^\n]", &aux.circuito);
                if (opcion==1){

                    //if (DNI<INFINITO){
                      // Inserta en LSO
                    //LVO_Alta(LSO, aux, &exitoLSO, opcion);
                    //}
                // Inserta en LSOBB
                LSOBB_Alta(LSOBB, aux, &exitoLSOBB, opcion);
                LVO_Alta(&lvo, aux, &exitoLVO);
                // Convierte los datos de Prestador a PrestadorABB antes de insertarlo en el ABB
                //a.DNI = aux.DNI;
                //strcpy(a.nombreyapellido, aux.nombreyapellido);
                //strcpy(a.servicios, aux.servicios);
                //strcpy(a.domicilio, aux.domicilio);
                //strcpy(a.correo, aux.correo);
                //strcpy(a.telefono, aux.telefono);

                // Inserta en el ABB
                //Alta_ABB(arbol, a, &exito);
            }
                else{
                    DNI=aux.DNI;
                    //if (DNI<INFINITO){
                    //LVO_Baja(LSO, DNI, &exitoLSO, aux, opcion);
                    //}
                    LSOBB_Baja(LSOBB, DNI, &exitoLSOBB, aux, opcion);
                    //Baja_ABB(arbol, a);
                }
            } else if (opcion==3){
                 DNI=aux.DNI;
                //if (DNI<INFINITO){
                //LVO_Evocar(LSO, &aux2, DNI, &exitoLSO, opcion);
                //}
                LSOBB_Evocar(LSOBB, &aux2, DNI, &exitoLSOBB, opcion);
                //Evocar_ABB(arbol, DNI, &exito, &a);
            }
            opcion=0;

        }
        fclose(fp);
        return 1;
    }

    }
     else {printf("Las estructuras deben estar vacias. \n");
        return 0;
    }

}

int main()
{
 int i, c=1, exito, pos;
 Padron p[5];
 for (i=0; i<5; i++){
    p[i].DNI=c;
    c=c+2;
    CantElem++;
     printf("Arreglo: %d \n", p[i].DNI);
     printf("CantElem: %d \n", CantElem);
 }

 LSOBB_Localizar(p,0, &exito, &pos, 0);
 printf("Exito: %d \n", exito);
 printf("Posicion: %d \n", pos);


}
