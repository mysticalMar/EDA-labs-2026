#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include <string.h>
#define MAXELECTORES 110
#define PAUSA_ELECTORES 5
#define cant_RS 1242 // MRS ρ=1.61.
///Variables globales de costo
int maxEvocExitosa_RS = 0, maxEvocNoExitosa_RS = 0;
int totalEvocExitosa_RS = 0, totalEvocNoExitosa_RS = 0;
int cantEvocExitosa_RS = 0, cantEvocNoExitosa_RS = 0;


typedef struct {
    int DNI;
    char nombreyapellido[50];
    char domicilio[80];
    int cp;
    int mesa;
    int circuito;
} PadronRS;

typedef struct celdaRS {
    PadronRS datos;
    struct celdaRS *psig;
} CeldaRS;

typedef struct {
    CeldaRS *a[cant_RS];
    int cant;
} RS;

// Función hashing para calcular la posición
int hashing (int dni , int M) {
char x[10] ;
int longitud , i ;
int contador=0;
sprintf(x, "%d" , dni );
longitud=strlen(x);
for (i=0; i< longitud; i++)
contador+=((int)x[i ]) * (i+1);
return (contador %M );
}

void init_RS(RS *tabla) {
int i;
tabla->cant = 0;
for (i=0;i<cant_RS; i++)
        tabla->a[i] = NULL;
}

// Crear una nueva celda para la lista enlazada
CeldaRS* nuevacelda(PadronRS padron) {
    CeldaRS *nuevo = (CeldaRS*)malloc(sizeof(CeldaRS));
    if (nuevo == NULL) return NULL;
    nuevo->datos = padron;
    nuevo->psig = NULL;
    return nuevo;
}
int confirmaRS(PadronRS a, PadronRS b) {
    return a.DNI == b.DNI &&
           strcmp(a.nombreyapellido, b.nombreyapellido) == 0 &&
           strcmp(a.domicilio, b.domicilio) == 0 &&
           a.cp == b.cp && a.mesa == b.mesa && a.circuito == b.circuito;
}


int Localizar_RS(RS *tabla, int DNI, CeldaRS **resultado, int *costo, int *pos){
    *pos=hashing(DNI, cant_RS);
    int c=0;
    CeldaRS *actual = tabla->a[*pos];
    while (actual!=NULL) {
        c++;
        if (actual->datos.DNI==DNI) {
            *resultado=actual;
            *costo=c;
            return 1;
        }
        actual=actual->psig;
    }
    *costo = c;
    return 0;
}


int Alta_RS(RS *tabla, PadronRS padron){
    CeldaRS *existe=NULL;
    int c=0, pos;
    if (Localizar_RS(tabla, padron.DNI, &existe, &c, &pos))
        return 0;                       // duplicado
    CeldaRS *nuevo=nuevacelda(padron);
    if (nuevo==NULL) return -1;       // sin memoria
    nuevo->psig=tabla->a[pos];
    tabla->a[pos]=nuevo;
    tabla->cant++;
    return 1;
}


int Baja_RS(RS *tabla, PadronRS padron){
    int pos=hashing(padron.DNI, cant_RS);
    CeldaRS *actual=tabla->a[pos], *anterior=NULL;
    while (actual!=NULL) {
        if (actual->datos.DNI==padron.DNI) {
            if (!confirmaRS(actual->datos, padron))
                return 0;  // el DNI está pero la nupla no coincide
            if (anterior==NULL) tabla->a[pos]=actual->psig;
            else anterior->psig=actual->psig;
            free(actual);
            tabla->cant--;
            return 1;
        }
        anterior=actual;
        actual=actual->psig;
    }
    return 0;
}

   int Evocar_RS(RS *tabla, int DNI, PadronRS *resultado, int *costo){
    CeldaRS *padron=NULL;
    int c;
    int pos;
    int e=Localizar_RS(tabla, DNI, &padron, &c, &pos);
    *costo=c;

    if (e==1) {  // Evocación exitosa
        totalEvocExitosa_RS += c;
        cantEvocExitosa_RS++;
        if (c > maxEvocExitosa_RS) {
            maxEvocExitosa_RS = c;
        }
        // Devolver los datos del prestador encontrado
        *resultado = padron->datos;
    } else {  // Evocación no exitosa
        totalEvocNoExitosa_RS += c;
        cantEvocNoExitosa_RS++;
        if (c > maxEvocNoExitosa_RS) {
            maxEvocNoExitosa_RS = c;
        }
    }

    return e;  // Retorna 1 si se encontró, 0 si no
}


void MostrarPadron(PadronRS p) {
                printf("DNI: %d\n", p.DNI);
                printf("Nombre y Apellido: %s\n", p.nombreyapellido);
                printf("Domicilio: %s\n", p.domicilio);
                printf("Codigo Postal: %d\n", p.cp);
                printf("Mesa: %d\n", p.mesa);
                printf("Circuito: %d\n", p.circuito);
                printf("------------------------------------------\n");
}

void MostrarEstructura_RS(RS *rs) {
    int i, contador=0, hayElectores=0;

    for (i=0; i<cant_RS;i++){
        if (rs->a[i]!=NULL){
            hayElectores=1; break;
        }
    }
    if (!hayElectores){
        printf("La lista de electores esta vacia.\n");
        getchar();
        return;
    }

    for (i=0; i<cant_RS; i++){
        CeldaRS *actual=rs->a[i];
        printf("Posicion %d: ", i);
        if (actual==NULL) printf("Vacia \n");
        else printf("\n");

        while (actual!=NULL){
            MostrarPadron(actual->datos);
            actual=actual->psig;
            contador++;
            if (contador % PAUSA_ELECTORES==0){
                printf("Presione Enter para continuar...\n");
                getchar();
            }
        }
    }
    printf("Presione Enter para volver al menu...\n");
    getchar();
}

#endif // RS_H_INCLUDED
