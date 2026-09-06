#ifndef LVO_H_INCLUDED
#define LVO_H_INCLUDED
#include <string.h>
int LVO_Altas = 0, LVO_total_Alta = 0, LVO_corr_Alta = 0, LVO_max_Alta = 0,
    LVO_Bajas = 0, LVO_total_Baja = 0, LVO_corr_Baja = 0, LVO_max_Baja = 0;
float LVO_medio_Alta = 0, LVO_medio_Baja = 0;

typedef struct
{
    int DNI;
    char nombreyapellido[50];
    char domicilio[80];
    int cp;
    int mesa;
    int circuito;
} Padron;

int LVO_cant=0;
    typedef struct nodo{
    Padron dato;
    struct nodo *next; //puntero al siguiente nodo
    } Nodo;
    typedef struct{
    Nodo *acc;
    Nodo *cur;
    Nodo *aux;
    } LVO;
    void inicio_LVO(LVO *l){
    l->acc=NULL;
    l->cur=NULL;
    l->aux=NULL;
    }
    void reset(LVO *l){
    l->cur=l->acc;
    l->aux=l->cur;
    }
    void forwards(LVO *l){
    l->acc=l->cur;
    l->cur=l->cur->next;
    }

    int LVO_confirma(LVO *l, Padron elemento){
    int c;
   if (strcasecmp(l->cur->dato.nombreyapellido, elemento.nombreyapellido) == 0 &&
    strcasecmp(l->cur->dato.domicilio, elemento.domicilio) == 0)
    //strcasecmp(l->cur->dato.cp, elemento.cp) == 0 &&
    //strcasecmp(l->cur->dato.mesa, elemento.mesa) == 0) &&
    //strcasecmp(l->cur->dato.circuito, elemento.circuito) == 0)
    {
    c = 1;
} else {
    c = 0;
}
return c;
}

    void LVO_Localizar(LVO *l, int dni, int *exito){
    l->cur=l->acc;
    l->aux=l->acc;
    if (LVO_cant==0){
        *exito=0;
    }
    else{
        while (l->cur!=NULL&&l->cur->dato.DNI<dni){
            l->aux=l->cur;
            l->cur=l->cur->next;
        }
        if (l->cur!=NULL&&l->cur->dato.DNI==dni){
            *exito=1;
        }
        else *exito=0;
        }
    }
    void LVO_Alta(LVO *l, Padron n, int *exito){
    int exito_l;
    LVO_Localizar(l, n.DNI, &exito_l);
    if (!exito_l){
    Nodo *aux=(Nodo*)malloc(sizeof(Nodo));
    if (l->cur==l->acc){ //inserto al principio
        l->acc=aux;
        aux->next=l->cur;
        l->cur=l->acc;
        l->aux=l->acc;
         LVO_corr_Alta++;
    }
    else {//inserto en otro lado
        l->aux->next=aux;
        aux->next=l->cur;
        l->cur=aux;
          LVO_corr_Alta++;
    }
    l->cur->dato=n;
    LVO_cant++;
    *exito=1; //alta exitosa
    LVO_Altas++;
    }else *exito=0;//alta no exitosa: el dni ya estaba en la lista
       //Calculos de costos
     if (LVO_corr_Alta>LVO_max_Alta){
        LVO_max_Alta=LVO_corr_Alta;
    }
       LVO_total_Alta+=LVO_corr_Alta;
    }
    void LVO_Baja(LVO *l, Padron e, int *exito){
        int exito_l;
        LVO_Localizar(l, e.DNI, &exito_l);

        if (exito_l){
            if (LVO_confirma(l, e)){
                if(l->cur==l->acc){
                    l->acc=l->cur->next;
                    free(l->cur);
                    l->cur=l->acc;
                    l->aux=l->acc;
                   LVO_corr_Baja++;
                }
                else {
                    l->cur->next=l->cur->next;
                    free(l->cur);
                    l->cur=l->aux->next;
                    LVO_corr_Baja++;
                }
                *exito=1; //baja exitosa
                LVO_cant--;
                LVO_Bajas++;
        }
            else exito=0;//baja no exitosa, los campos no coinciden
             //Calculos de costos
     if (LVO_corr_Baja>LVO_max_Baja){
        LVO_max_Baja=LVO_corr_Baja;
    }
     LVO_total_Baja+=LVO_corr_Baja;
    LVO_corr_Baja=0;
}
    else exito=0;//baja no exitosa, el elemento no estaba en la lista
    }


    int LVO_Evocar(LVO l, int dni, Padron *a){
    int exito;
    LVO_Localizar(&l, dni, &exito);
    if (exito){
        *a=l.cur->dato;
        return 1;
    }
        else return 0;
    }

    void LVO_MostrarEstructura(LVO l){
        int i=0, c=0;
        l.cur=l.acc;
        if (LVO_cant==0){
            printf("La lista de prestadores esta vacia. \n");
        }
        else{
            while (l.cur!=NULL&&i<LVO_cant){
               printf("--------- Listado de Prestadores ---------\n");
                printf("Prestador %d:\n", i);
                printf("DNI: %d\n", l.cur->dato.DNI);
                printf("Nombre y Apellido: %s\n", l.cur->dato.nombreyapellido);
                printf("Domicilio: %s\n", l.cur->dato.domicilio);
                printf("Codigo Postal: %d\n", l.cur->dato.cp);
                printf("Mesa: %d\n", l.cur->dato.mesa);
                printf("Circuito: %d\n", l.cur->dato.circuito);
                printf("------------------------------------------\n");
                c++;
                if (c==5){
                    getchar();
                    c=0;
                }
                i++;
                l.cur=l.cur->next;
            }
        }
    }




#endif // LVO_H_INCLUDED
