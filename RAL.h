

#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "RS.h"
#define MRAL 2532 /// M : N / ρ --> 2000 / 0.79 --> M = 2532

typedef struct {
    int DNI;
    char nombreyapellido[50];
    char domicilio[80];
    int cp;
    int mesa;
    int circuito;
} Padron;
int CantElemRAL=0, RAL_c=0, RAL_t_E=0, RAL_t_F=0, RAL_max_E=0, RAL_max_F=0, RAL_evocar_E=0, RAL_evocar_F=0;
float RAL_medio=0;

 void RAL_inicializar(Padron r[]){
 int i;
     for(i=0; i<MRAL; i++){
        r[i].DNI=-1;//marca de celda virgen
     }
 }
 int confirma(Padron l[], int pos, Padron elemento) {
    return l[pos].DNI == elemento.DNI &&
           strcasecmp(l[pos].nombreyapellido, elemento.nombreyapellido) == 0 &&
           strcasecmp(l[pos].domicilio, elemento.domicilio) == 0 &&
           l[pos].cp == elemento.cp &&
           l[pos].mesa == elemento.mesa &&
           l[pos].circuito == elemento.circuito;
}
void Localizar_RAL(Padron l[], int dni, int *exito, int *pos, int opcion) {
    int i = hashing(dni, MRAL), c=0, posf, flag=0;
    if (opcion==3){
        RAL_c++;
    }
    while (c<MRAL&&l[i].DNI!=-1&&l[i].DNI!=dni){//controlar no recorrer los M baldes
            if (l[i].DNI==-2&&flag==0){
             flag=1;
             posf=i;
            }
        i=(i+1)%MRAL;
        c++;
        if (opcion==3){
        RAL_c++;
        }
    }
    if (l[i].DNI==dni){
        *pos=i;
        *exito=1;
    }
        else {
            *exito=0;
          if (flag) *pos = posf; else *pos = i;
    }

}
void Alta_RAL(Padron r[], Padron nuevo,  int dni, int *exito, int opcion){
int exitoLocalizar, pos;
        Localizar_RAL(r, dni, &exitoLocalizar, &pos, opcion);
        if (!exitoLocalizar){
            r[pos]=nuevo;
            *exito=1;
            CantElemRAL++;

        } else *exito=2;

}

void Baja_RAL(Padron r[], int dni, int *exito, Padron e, int opcion){
    int exitoLocalizar, pos;
    Localizar_RAL(r, dni, &exitoLocalizar, &pos, opcion);
    if (exitoLocalizar&&confirma(r, pos, e)){
        r[pos].DNI=-2; //-2: marca de celda libre
        *exito=1;
        CantElemRAL--;
    }
    else *exito=0;
}
void Evocar_RAL(Padron r[], Padron *e, int dni, int *exito, int opcion){ //agregar parámetro de costo
    int exitoLocalizar, pos;
     Localizar_RAL(r, dni, &exitoLocalizar, &pos, opcion);
     if(exitoLocalizar){
        *e=r[pos];
        *exito=1;
        RAL_evocar_E++;
           if (RAL_c>RAL_max_E){
            RAL_max_E=RAL_c;
        }
        RAL_t_E+=RAL_c;
        RAL_c=0;
     }
     else {
        *exito=0;
        RAL_evocar_F++;
           if (RAL_c>RAL_max_F){
            RAL_max_F=RAL_c;
        }
        RAL_t_F+=RAL_c;
        RAL_c=0;
     }
}


void MostrarEstructura_RAL(Padron l[]) {
    int i, c = 0;
    if (CantElemRAL == 0) {
        printf("La lista de electores esta vacia.\n");
        getchar();
        return;
    }
    for (i = 0; i < MRAL; i++) {
        printf("Celda %d: ", i);
        if (l[i].DNI == -1) printf("Virgen\n");
        else if (l[i].DNI == -2) printf("Libre\n");
        else {
            printf("Ocupada\n");
            printf("DNI: %d\n", l[i].DNI);
            printf("Nombre y Apellido: %s\n", l[i].nombreyapellido);
            printf("Domicilio: %s\n", l[i].domicilio);
            printf("Codigo Postal: %d\n", l[i].cp);
            printf("Mesa: %d\n", l[i].mesa);
            printf("Circuito: %d\n", l[i].circuito);
            printf("------------------------------------------\n");
        }
        if (++c % 5 == 0) { printf("Presione ENTER para continuar...\n"); getchar(); }
    }
}
#endif // RAL_H_INCLUDED
