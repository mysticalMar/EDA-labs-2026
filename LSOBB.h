#ifndef LSOBB_H_INCLUDED
#define LSOBB_H_INCLUDED
#define MAXELECTORES 2000
#include <string.h>

typedef struct {
    int DNI;
    char nombreyapellido[50];
    char domicilio[80];
    int cp;
    int mesa;
    int circuito;
} Padron;

int CantElem=0;
int confirma(Padron l[], int pos, Padron elemento){ //solo comparo caracteres?
    int c;
   if (strcasecmp(l[pos].nombreyapellido, elemento.nombreyapellido) == 0 &&
    strcasecmp(l[pos].domicilio, elemento.domicilio) == 0) {
    c = 1;
} else {
    c = 0;
}
return c;
}
//variables de costos
int LSOBB_Altas=0, LSOBB_total_Alta, LSOBB_corr_Alta=0, LSOBB_max_Alta=0,
LSOBB_Bajas=0, LSOBB_total_Baja=0, LSOBB_corr_Baja=0, LSOBB_max_Baja=0,
LSOBB_local=0, LSOBB_total_local=0, LSOBB_cant_local=0, LSOBB_max_local=0,
LSOBB_evocacion_NE=0, LSOBB_max_evocacion_NE=0,  LSOBB_max_local_EE=0;
float LSOBB_medio_Alta=0, LSOBB_medio_Baja=0, LSOBB_medio_local=0;
//Explicacion de variables:
//LSOBB_Altas: total de altas exitosas en la lista
//LSOBB_total_Alta: son todos los corrimientos en la lista
//LSOBB_corr_Alta: son los corrimientos en cada ejecucion. Auxiliar para el máximo.
//LSOBB_max_Alta: cantidad de corrimientos más alto en el alta.
//LSOBB_medio_Alta: coste medio del alta.

//en la lista secuencial la funci´ on de costo ser´ a la cantidad de
//corrimientos y cada corrimiento de elemento tiene costo 1 (uno).
//limite inferior inclusivo, lımite superior inclusivo, testigo a izquierda y segmento mas grande a la izquierda.

void LSOBB_Localizar(Padron l[], int dni, int *exito, int *pos, int opcion) {
     int li,ls, t;
     float m;
     li=0;
     ls=CantElem-1;
	 while ((li<ls)){
      t=((li+ls)/2);
 printf("Limite inferior: %d \n", li);
       printf("Limite superior: %d \n", ls);

      printf("Testigo: %d \n", t);
      printf("Elemento: %d \n", l[t].DNI);




     if (l[t].DNI<dni) {
            li = t+1;
     }
		 else {
         ls=t;
		 }
    }

    if (ls==li) {
                *exito= 0; //localización no exitosa
                *pos=li;
            }
            else {
            *exito=1; //localizacion exitosa
            *pos=t;
            }
}
void LSOBB_Alta(Padron l[], Padron ElementoAlta, int *exito, int opcion) {
    int pos, exitoLocalizar = 0, i;

    LSOBB_Localizar(l, ElementoAlta.DNI, &exitoLocalizar, &pos, opcion);


    if (!exitoLocalizar) {
        if (CantElem < MAXELECTORES) {
            // Realizamos el corrimiento para insertar en la posición correcta
            for (i = CantElem; i > pos; i--) {
                l[i] = l[i - 1];
                LSOBB_corr_Alta++;
            }
            // Insertamos el elemento en la posición encontrada
            l[pos] = ElementoAlta;
            CantElem++;
            *exito = 1;  // Alta exitosa
            LSOBB_Altas++;

        } else {
            *exito = -1;  // Alta no exitosa, lista llena o DNI inválido

        }
    } else {
        *exito = 2;  // Alta no exitosa, DNI repetido

    }
    //Calculos de costos
     if (LSOBB_corr_Alta>LSOBB_max_Alta){
        LSOBB_max_Alta=LSOBB_corr_Alta;
    }
       LSOBB_total_Alta+=LSOBB_corr_Alta;
    LSOBB_corr_Alta=0;
}
void LSOBB_Baja(Padron l[], int DNI, int *exito, Padron e, int opcion){
int pos, exitoLocalizar=0, i;

LSOBB_Localizar(l, DNI,  &exitoLocalizar, &pos, opcion);

if(exitoLocalizar){

   if(confirma(l, pos, e)==1){
    for(i=pos; i<CantElem-1; i++){
        l[i] = l[i+1];
        LSOBB_corr_Baja++;
    }
    CantElem--;//Reducimos el numero de elementos

    *exito=1; //Se dio de baja correctamente
    LSOBB_Bajas++;

        } else {
            *exito = 0;

        }
    } else {
        *exito = 0; // No se encontró el prestador

    }
       //Calculos de costos
     if (LSOBB_corr_Baja>LSOBB_max_Baja){
        LSOBB_max_Baja=LSOBB_corr_Baja;
    }
     LSOBB_total_Baja+=LSOBB_corr_Baja;
    LSOBB_corr_Baja=0;
}

    void LSOBB_MostrarEstructura(Padron l[]){
        int i=0, c=0;
        if (CantElem==0){
            printf("La lista esta vacia. \n");
        }
        else{
            while (i<CantElem){
               printf("--------- Listado de Prestadores ---------\n");
                printf("Prestador %d:\n", i);
                printf("DNI: %d\n", l[i].DNI);
                printf("Nombre y Apellido: %s\n", l[i].nombreyapellido);
                printf("Domicilio: %s\n", l[i].domicilio);
                printf("Codigo Postal: %d\n", l[i].cp);
                printf("Mesa: %d\n", l[i].mesa);
                printf("Circuito: %d\n", l[i].circuito);
                printf("------------------------------------------\n");
                c++;
                if (c==5){
                    getchar();
                    c=0;
                }
                i++;
            }
        }
    }

void LSOBB_Evocar(Padron LSOBB[], Padron *Elem, int DNI, int *exito, int opcion){
    int pos, exitoLocalizar;
    LSOBB_Localizar(LSOBB, DNI, &exitoLocalizar, &pos, opcion);

    if(exitoLocalizar){
        *Elem = LSOBB[pos]; //Copiamos la informacion del prestador encontrado
        *exito = 1;//Evocacion exitosa
        LSOBB_local++;
         if (LSOBB_cant_local>LSOBB_max_local_EE){
            LSOBB_max_local_EE=LSOBB_cant_local;
        }
          LSOBB_total_local+=LSOBB_cant_local;
    }else{
        *exito=0;
        LSOBB_evocacion_NE++;
         if (LSOBB_cant_local>LSOBB_max_evocacion_NE){
            LSOBB_max_evocacion_NE=LSOBB_cant_local;
        }
          LSOBB_total_local+=LSOBB_cant_local;
    }



     LSOBB_cant_local=0;

}


#endif // LSOBB_H_INCLUDED
