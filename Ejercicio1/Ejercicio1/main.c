//
//  main.c
//  Ejercicio1
//
//  Created by Josué Carlos García Puig on 17/09/15.
//  Copyright (c) 2015 Avtelyes. All rights reserved.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

typedef struct {
    int nomina;
    char * nombre;
    char * apellidos;
    char * fecha_nacimiento;
    char * fecha_empresa;
    int salario;
    char * puesto;
} Trabajador;

typedef struct {
    int dia;
    int mes;
    int anio;
    Trabajador * trabajador;
} Fecha;

typedef struct {
    char * tipo;
    int * modales;
    int periodo;
    char * simetria;
    Fecha * fecha;
    int niveles;
} Edificio;

typedef struct {
    char * tipo;
    int * modales;
    int periodo;
    char ** diametros;
    Fecha * fecha;
    int niveles;
} Torre;

typedef struct {
    char * tipo;
    int * modales;
    int periodo;
    char * techo;
    Fecha * fecha;
    int niveles;
} Nave;

typedef struct {
    Edificio * edificio;
    int tamEdificio;
    Torre * torre;
    int tamTorre;
    Nave * nave;
    int tamNave;
} Modelo;

typedef struct {
    Modelo * modelo;
} Trabajo;

typedef struct {
    int dia;
    int mes;
    int anio;
    Trabajador * trabajador;
    Modelo * modelo;
    int tam;
    int tamTrabajador;
} FechaDia;

void adicionNomina(Trabajador *, int * );
void edicionNomina(Trabajador * , int * );
void borrarNomina(Trabajador * , int * );
void adicionEstructura(Modelo *, int, Trabajador *, int *);
void adicionEdificio(Edificio * , int *, Trabajador * );
void adicionTorre(Torre * , int * , Trabajador * );
void adicionNave(Nave * , int * , Trabajador * );
void consultaModelos(Modelo * , Trabajador * , int * );

void reporteTrabajadores(Trabajador *, int * , Modelo *);
void impresionTrabajadores(Trabajador * , int * );
void impresionModelosDia(FechaDia * , Modelo * );
Trabajador * obtienePersona(Trabajador *, int *, int);

void LiberaMemoriaTrabajo(Trabajo * );
void liberarMemoriaNomina(Trabajador *, int * );

int main(int argc, const char * argv[]) {
    
    int numTrabajadores = 0, numNomina = 0;
    
    printf("Dame el numero de trabajadores a adicionar: ");
    scanf("%d", &numTrabajadores);
    
    Trabajo * work = (Trabajo *) malloc(sizeof(Trabajo));
    Modelo * modelo = (Modelo *) malloc(sizeof(Modelo));
    work->modelo = modelo;
    Trabajador * nomina = (Trabajador *) malloc(numTrabajadores * sizeof(Trabajador));
    
    adicionNomina(nomina, &numTrabajadores);
    printf("\nDame el numero de nomina para agregar edificacion: ");
    scanf("%d", &numNomina);
    adicionEstructura(modelo, numNomina, nomina, &numTrabajadores);
    consultaModelos(modelo, nomina, &numTrabajadores);
    reporteTrabajadores(nomina, &numTrabajadores, modelo);
    
    edicionNomina(nomina, &numTrabajadores);
    impresionTrabajadores(nomina, &numTrabajadores);
    
    /*borrarNomina(nomina, &numTrabajadores);
    impresionTrabajadores(nomina, &numTrabajadores);*/
    
    
    LiberaMemoriaTrabajo(work);
    liberarMemoriaNomina(nomina, &numTrabajadores);
    free(nomina);
    
    return 0;
}

void adicionNomina(Trabajador * nomina, int * tam)
{
    Trabajador * inicio = nomina;
    Trabajador * fin = (inicio+*tam);
    
    for(; inicio<fin; ++inicio)
    {
        if(inicio->nomina == 0)
        {
            inicio->nombre = (char *) malloc(70 * sizeof(char));
            inicio->apellidos = (char *) malloc(70 * sizeof(char));
            inicio->fecha_nacimiento = (char *) malloc(100 * sizeof(char));
            inicio->fecha_empresa = (char *) malloc(100 * sizeof(char));
            inicio->puesto = (char *) malloc(70 * sizeof(char));
            
            printf("\nDame el numero de nomina: ");
            scanf("%d", &inicio->nomina);
            printf("Dame el nombre: ");
            scanf(" %[^\n]s", inicio->nombre);
            printf("Dame el apellido: ");
            scanf(" %[^\n]s", inicio->apellidos);
            printf("Dame la fecha de nacimiento: ");
            scanf(" %[^\n]s", inicio->fecha_nacimiento);
            printf("Dame la fecha de ingreso a la empresa: ");
            scanf(" %[^\n]s", inicio->fecha_empresa);
            printf("Dame el salario: ");
            scanf("%d", &inicio->salario);
            printf("Dame el puesto: ");
            scanf(" %[^\n]s", inicio->puesto);
        }
    }
}

void edicionNomina(Trabajador * nomina, int * tam)
{
    int numero = 0;
    
    printf("Dame el numero de nomina que quieras editar: ");
    scanf("%d", &numero);
    
    Trabajador * inicio = nomina;
    Trabajador * final = (inicio + *tam);
    
    for(; inicio<final; ++inicio)
    {
        if(inicio->nomina == numero)
        {
            printf("Dame el numero de nomina: ");
            scanf("%d", &inicio->nomina);
            printf("Dame el nombre: ");
            scanf(" %[^\n]s", inicio->nombre);
            printf("Dame el apellido: ");
            scanf(" %[^\n]s", inicio->apellidos);
            printf("Dame la fecha de nacimiento: ");
            scanf(" %[^\n]s", inicio->fecha_nacimiento);
            printf("Dame la fecha de ingreso a la empresa: ");
            scanf(" %[^\n]s", inicio->fecha_empresa);
            printf("Dame el salario: ");
            scanf("%d", &inicio->salario);
            printf("Dame el puesto: ");
            scanf(" %[^\n]s", inicio->puesto);
        }
    }
}

void borrarNomina(Trabajador * nomina, int * tam)
{
    int numero = 0;
    
    printf("Dame el numero de nomina que quieras borrar: ");
    scanf("%d", &numero);
    
    Trabajador * inicio = nomina;
    Trabajador * final = (inicio + *tam);
    
    for(; inicio<final; ++inicio)
    {
        if(inicio->nomina == numero)
        {
            free(inicio->puesto);
            free(inicio->fecha_empresa);
            free(inicio->fecha_nacimiento);
            free(inicio->apellidos);
            free(inicio->nombre);
            inicio->salario = 0;
        }
    }
}

void adicionEstructura(Modelo * modelos, int nomina, Trabajador * trabajadores, int * tamTrabajadores)
{
    int opcion = 0;
    
    printf("Dame el tipo de estructura:\n1.-Edificio\n2.-Torre\n3.-Nave\n");
    scanf("%d", &opcion);
    
    Trabajador * persona = obtienePersona(trabajadores, tamTrabajadores, nomina);
    
    if(opcion == 1)
    {
        if(modelos->tamEdificio == 1)
        {
            modelos->edificio = (Edificio *) realloc(modelos->edificio, sizeof(Edificio) * (modelos->tamEdificio + 1));
            modelos->tamEdificio += 1;
        }
        else
        {
            modelos->edificio = (Edificio *) malloc(sizeof(Edificio));
            modelos->tamEdificio = 1;
        }
        adicionEdificio(modelos->edificio, &modelos->tamEdificio, persona);
    }
    else if (opcion == 2)
    {
        if(modelos->tamTorre == 1)
        {
            modelos->torre = (Torre *) realloc(modelos->torre, sizeof(Torre) * (modelos->tamTorre + 1));
            modelos->tamTorre += 1;
        }
        else
        {
            modelos->torre = (Torre *) malloc(sizeof(Torre));
            modelos->tamTorre = 1;
        }
        adicionTorre(modelos->torre, &modelos->tamTorre, persona);
    }
    else if (opcion == 3)
    {
        if(modelos->tamNave == 1)
        {
            modelos->nave = (Nave *) realloc(modelos->nave, sizeof(Nave) * (modelos->tamNave + 1));
            modelos->tamNave += 1;
        }
        else
        {
            modelos->nave = (Nave *) malloc(sizeof(Nave));
            modelos->tamNave = 1;
        }
        adicionNave(modelos->nave, &modelos->tamNave, persona);
    }
}

void adicionEdificio(Edificio * edificios, int * tam, Trabajador * persona)
{
    Edificio * inicio = edificios;
    Edificio * fin = (inicio+*tam);
    
    int niveles = 0;
    
    for(; inicio<fin; ++inicio)
    {
        if(inicio->periodo == 0)
        {
            inicio->tipo = (char *) malloc(70 * sizeof(char));
            printf("Dame el numero de niveles: ");
            scanf("%d", &niveles);
            inicio->modales = (int *) malloc(niveles * sizeof(int));
            inicio->simetria = (char *) malloc(70 * sizeof(char));
            inicio->fecha = (Fecha *) malloc(sizeof(Fecha));
            inicio->fecha->trabajador = persona;
            
            strcpy(inicio->tipo, "Edificio");
            printf("Dame el periodo: ");
            scanf("%d", &inicio->periodo);
            printf("Dame la simetria: ");
            scanf(" %[^\n]s", inicio->simetria);
            printf("Dame el dia: ");
            scanf("%d", &inicio->fecha->dia);
            printf("Dame el mes: ");
            scanf("%d", &inicio->fecha->mes);
            printf("Dame el año: ");
            scanf("%d", &inicio->fecha->anio);
            inicio->niveles = niveles;
            printf("Modelando Edificio...\n");
        }
    }
}

void adicionTorre(Torre * torres, int * tam, Trabajador * persona)
{
    Torre * inicio = torres;
    Torre * fin = (inicio+*tam);
    
    int niveles = 0;
    
    for(; inicio<fin; ++inicio)
    {
        if(inicio->periodo == 0)
        {
            inicio->tipo = (char *) malloc(70 * sizeof(char));
            printf("Dame el numero de niveles: ");
            scanf("%d", &niveles);
            inicio->modales = (int *) malloc(niveles * sizeof(int));
            inicio->diametros = (char **) malloc(2 * sizeof(char *));
            int i;
            for(i = 0; i<niveles; ++i)
                *(inicio->diametros+i) = (char *) malloc(2 * sizeof(char));
            inicio->fecha = (Fecha *) malloc(sizeof(Fecha));
            inicio->fecha->trabajador = persona;
            
            strcpy(inicio->tipo, "Torre");
            printf("Dame el periodo: ");
            scanf("%d", &inicio->periodo);
            for(i = 0; i<niveles; ++i)
            {
                printf("Nivel %d\n", i);
                printf("Dame el diametro inferior: ");
                scanf("%s", *(inicio->diametros+i));
                printf("Dame el diametro superior: ");
                scanf("%s", *(inicio->diametros+i)+1);
            }
            printf("Dame el dia: ");
            scanf("%d", &inicio->fecha->dia);
            printf("Dame el mes: ");
            scanf("%d", &inicio->fecha->mes);
            printf("Dame el año: ");
            scanf("%d", &inicio->fecha->anio);
            inicio->niveles = niveles;
            printf("Modelando Torre...\n");
        }
    }
}

void adicionNave(Nave * naves, int * tam, Trabajador * persona)
{
    Nave * inicio = naves;
    Nave * fin = (inicio+*tam);
    
    int niveles = 0;
    
    for(; inicio<fin; ++inicio)
    {
        if(inicio->periodo == 0)
        {
            inicio->tipo = (char *) malloc(70 * sizeof(char));
            printf("Dame el numero de niveles: ");
            scanf("%d", &niveles);
            inicio->modales = (int *) malloc(niveles * sizeof(int));
            inicio->techo = (char *) malloc(70 * sizeof(char));
            inicio->fecha = (Fecha *) malloc(sizeof(Fecha));
            inicio->fecha->trabajador = persona;
            
            strcpy(inicio->tipo, "Nave");
            printf("Dame el periodo: ");
            scanf("%d", &inicio->periodo);
            printf("Dame la simetria: ");
            scanf(" %[^\n]s", inicio->techo);
            printf("Dame el dia: ");
            scanf("%d", &inicio->fecha->dia);
            printf("Dame el mes: ");
            scanf("%d", &inicio->fecha->mes);
            printf("Dame el año: ");
            scanf("%d", &inicio->fecha->anio);
            inicio->niveles = niveles;
            printf("Modelando Nave...\n");
        }
    }
}

void reporteTrabajadores(Trabajador * nomina, int * tamNomina, Modelo * modelo)
{
    FechaDia * fechadia = (FechaDia *) malloc(10 * sizeof(FechaDia));
    fechadia->tam = 0;
    
    int dia1 = 0, mes1 = 0, anio1 = 0;
    int dia2 = 0, mes2 = 0, anio2 = 0;
    
    printf("Dame el dia de inicio: ");
    scanf("%d", &dia1);
    printf("Dame el mes de inicio: ");
    scanf("%d", &mes1);
    printf("Dame el año de inicio: ");
    scanf("%d", &anio1);
    
    printf("Dame el dia de finalizacion: ");
    scanf("%d", &dia2);
    printf("Dame el mes de finalizacion: ");
    scanf("%d", &mes2);
    printf("Dame el año de finalizacion: ");
    scanf("%d", &anio2);
    
    Edificio * inicioE = modelo->edificio;
    Edificio * finE = (inicioE+modelo->tamEdificio);
    //Edificio * auxE;
    
    Torre * inicioT = modelo->torre;
    Torre * finT = (inicioT+modelo->tamTorre);
    //Torre * auxT;
    
    Nave * inicioN = modelo->nave;
    Nave * finN = (inicioN+modelo->tamNave);
    //Nave * auxN;
    
    for(; inicioE<finE; ++inicioE)
    {
        if(inicioE->fecha->anio >= anio1 && inicioE->fecha->anio <= anio2)
        {
            if(inicioE->fecha->mes >= mes1 && inicioE->fecha->mes <= mes2)
            {
                if(inicioE->fecha->dia >= dia1 && inicioE->fecha->dia <= dia2)
                {
                    FechaDia * iniFec = fechadia;
                    FechaDia * finFec = (iniFec+10);
                    
                    for(; iniFec<finFec; ++iniFec)
                    {
                        if(iniFec->dia == inicioE->fecha->dia && iniFec->mes == inicioE->fecha->mes && iniFec->anio == inicioE->fecha->anio)
                        {
                        }
                        else
                        {
                            fechadia->tam += 1;
                            iniFec->dia = inicioE->fecha->dia;
                            iniFec->mes = inicioE->fecha->mes;
                            iniFec->anio = inicioE->fecha->anio;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    for(; inicioT<finT; ++inicioT)
    {
        if(inicioT->fecha->anio >= anio1 && inicioT->fecha->anio <= anio2)
        {
            if(inicioT->fecha->mes >= mes1 && inicioT->fecha->mes <= mes2)
            {
                if(inicioT->fecha->dia >= dia1 && inicioT->fecha->dia <= dia2)
                {
                    FechaDia * iniFec = fechadia;
                    FechaDia * finFec = (iniFec+10);
                    
                    for(; iniFec<finFec; ++iniFec)
                    {
                        if(iniFec->dia == inicioT->fecha->dia && iniFec->mes == inicioT->fecha->mes && iniFec->anio == inicioT->fecha->anio)
                        {
                        }
                        else
                        {
                            fechadia->tam += 1;
                            iniFec->dia = inicioT->fecha->dia;
                            iniFec->mes = inicioT->fecha->mes;
                            iniFec->anio = inicioT->fecha->anio;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    for(; inicioN<finN; ++inicioN)
    {
        if(inicioN->fecha->anio >= anio1 && inicioN->fecha->anio <= anio2)
        {
            if(inicioN->fecha->mes >= mes1 && inicioN->fecha->mes <= mes2)
            {
                if(inicioN->fecha->dia >= dia1 && inicioN->fecha->dia <= dia2)
                {
                    FechaDia * iniFec = fechadia;
                    FechaDia * finFec = (iniFec+10);
                    
                    for(; iniFec<finFec; ++iniFec)
                    {
                        if(iniFec->dia == inicioN->fecha->dia && iniFec->mes == inicioN->fecha->mes && iniFec->anio == inicioN->fecha->anio)
                        {
                        }
                        else
                        {
                            fechadia->tam += 1;
                            iniFec->dia = inicioN->fecha->dia;
                            iniFec->mes = inicioN->fecha->mes;
                            iniFec->anio = inicioN->fecha->anio;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    impresionTrabajadores(nomina, tamNomina);
    impresionModelosDia(fechadia, modelo);
    
    free(fechadia);
    
}

void impresionModelosDia(FechaDia * fechadia, Modelo * modelos)
{
    //Trabajador * auxTra;
    
    int numModelaciones = 0;
    
    FechaDia * inicioFec = fechadia;
    FechaDia *finFec = (inicioFec+fechadia->tam);
    
    int dia = 0, mes = 0, anio = 0;
    
    Edificio * inicioE = modelos->edificio;
    Edificio * finE = (inicioE+modelos->tamEdificio);
    
    Torre * inicioT = modelos->torre;
    Torre * finT = (inicioT+modelos->tamTorre);
    
    Nave * inicioN = modelos->nave;
    Nave * finN = (inicioN+modelos->tamNave);
    
    for(; inicioFec<finFec; ++inicioFec)
    {
        dia = inicioFec->dia;
        mes = inicioFec->mes;
        anio = inicioFec->anio;
        
        printf("\n\nFecha-> Dia: %d, Mes: %d, Año: %d", dia, mes, anio);
        
        for(; inicioE<finE; ++inicioE)
        {
            if(inicioE->fecha->dia == dia && inicioE->fecha->mes == mes && inicioE->fecha->anio)
            {
                printf("\nNiveles: %d\nPeriodo: %d\nSimetria: %s\n\n", inicioE->niveles, inicioE->periodo, inicioE->simetria);
                numModelaciones++;
            }
        }
        
        for(; inicioT<finT; ++inicioT)
        {
            if(inicioT->fecha->dia == dia && inicioT->fecha->mes == mes && inicioT->fecha->anio)
            {
                printf("\nTipo: %s\nPeriodo: %d\n\n", inicioT->tipo, inicioT->periodo);
                numModelaciones++;
            }
        }
        
        for(; inicioN<finN; ++inicioN)
        {
            if(inicioN->fecha->dia == dia && inicioN->fecha->mes == mes && inicioN->fecha->anio)
            {
                printf("\nNiveles: %d\nPeriodo: %d\nTecho: %s\n\n", inicioN->niveles, inicioN->periodo, inicioN->techo);
                numModelaciones++;
            }
        }
        printf("Modelaciones del dia: %d\n", numModelaciones);
    }
}

void impresionTrabajadores(Trabajador * nomina, int * tam)
{
    Trabajador * inicio = nomina;
    Trabajador * fin = (inicio+*tam);
    
    for(; inicio<fin; ++inicio)
    {
        if(inicio->nomina != 0)
        {
            printf("\n\nNomina: %d\nNombre: %s\nApellido: %s\nFecha Nacimiento: %s\nFecha Ingreso: %s\nSalario: %d\nPuesto: %s", inicio->nomina, inicio->nombre, inicio->apellidos, inicio->fecha_nacimiento, inicio->fecha_empresa, inicio->salario, inicio->puesto);
        }
    }
}

void consultaModelos(Modelo * modelos, Trabajador * trabajadores, int * tamTrab)
{
    int nomina = 0;
    printf("Dame el numero de nomina: ");
    scanf("%d", &nomina);
    
    Trabajador * auxTra = obtienePersona(trabajadores, tamTrab, nomina);
    
    int dia = 0, mes = 0, anio = 0;
    
    int numE = 0, numT = 0, numN = 0;
    
    printf("Dame el dia: ");
    scanf("%d", &dia);
    printf("Dame el mes: ");
    scanf("%d", &mes);
    printf("Dame el año: ");
    scanf("%d", &anio);
    
    Edificio * inicioE = modelos->edificio;
    Edificio * finE = (inicioE+modelos->tamEdificio);
    Edificio * auxE;
    
    Torre * inicioT = modelos->torre;
    Torre * finT = (inicioT+modelos->tamTorre);
    Torre * auxT;
    
    Nave * inicioN = modelos->nave;
    Nave * finN = (inicioN+modelos->tamNave);
    Nave * auxN;
    
    for(; inicioE<finE; ++inicioE)
    {
        if(inicioE->fecha->dia == dia && inicioE->fecha->mes == mes && inicioE->fecha->anio && inicioE->fecha->trabajador->nomina == auxTra->nomina)
        {
            *(auxE+numE) = *inicioE;
            numE++;
        }
    }
    
    for(; inicioT<finT; ++inicioT)
    {
        if(inicioT->fecha->dia == dia && inicioT->fecha->mes == mes && inicioT->fecha->anio && inicioT->fecha->trabajador->nomina == auxTra->nomina)
        {
            *(auxT+numT) = *inicioT;
            numT++;
        }
    }
    
    for(; inicioN<finN; ++inicioN)
    {
        if(inicioN->fecha->dia == dia && inicioN->fecha->mes == mes && inicioN->fecha->anio && inicioN->fecha->trabajador->nomina == auxTra->nomina)
        {
            *(auxN+numN) = *inicioN;
            numN++;
        }
    }
    
    Edificio * inicioE2 = auxE;
    Edificio * finE2 = (inicioE2+numE);
    
    Torre * inicioT2 = auxT;
    Torre * finT2 = (inicioT2+numT);
    
    Nave * inicioN2 = auxN;
    Nave * finN2 = (inicioN2+numN);
    
    for(; inicioE2<finE2; ++inicioE2)
    {
        printf("\nNiveles: %d\nPeriodo: %d\nSimetria: %s\n\n", inicioE2->niveles, inicioE2->periodo, inicioE2->simetria);
    }
    
    for(; inicioT2<finT2; ++inicioT2)
    {
        printf("\nTipo: %s\nPeriodo: %d\n\n", inicioT2->tipo, inicioT2->periodo);
    }
    
    for(; inicioN2<finN2; ++inicioN2)
    {
        printf("\nNiveles: %d\nPeriodo: %d\nTecho: %s\n\n", inicioN2->niveles, inicioN2->periodo, inicioN2->techo);
    }
}

Trabajador * obtienePersona(Trabajador * trabajadores, int * tam, int nomina)
{
    Trabajador * inicio = trabajadores;
    Trabajador * fin = (inicio+*tam);
    
    Trabajador * aux;
    
    for(; inicio<fin; ++inicio)
    {
        if(inicio->nomina == nomina)
        {
            aux = inicio;
            break;
        }
    }
    
    return aux;
}

void LiberaMemoriaTrabajo(Trabajo * trabajo)
{
    int tE = 0, tT = 0, tN = 0;
    int nivelesT = 0;
    
    Modelo * auxMol = trabajo->modelo;
    tE = auxMol->tamEdificio;
    tT = auxMol->tamTorre;
    tN = auxMol->tamNave;
    
    Edificio * inicioE = auxMol->edificio;
    Edificio * finE = (inicioE+tE);
    
    Torre * inicioT = auxMol->torre;
    Torre * finT = (inicioT+tT);
    
    Nave * inicioN = auxMol->nave;
    Nave * finN = (inicioN+tN);
    
    for(; inicioE<finE; ++inicioE)
    {
        free(inicioE->fecha);
        free(inicioE->simetria);
        free(inicioE->modales);
        free(inicioE->tipo);
    }
    
    free(auxMol->edificio);
    
    for(; inicioT<finT; ++inicioT)
    {
        free(inicioT->fecha);
        nivelesT = inicioT->niveles;
        int i;
        for(i=0; i<nivelesT; ++i)
            free(*(inicioT->diametros+i));
        free(inicioT->diametros);
        free(inicioT->modales);
        free(inicioT->tipo);
        free(inicioT);
    }
    
    free(auxMol->torre);
    
    for(; inicioN<finN; ++inicioN)
    {
        free(inicioN->fecha);
        free(inicioN->techo);
        free(inicioN->modales);
        free(inicioN->tipo);
        free(inicioN);
    }
    
    free(auxMol->nave);
    
    free(auxMol);
    free(trabajo);
    
}

void liberarMemoriaNomina(Trabajador * trabajadores, int * tam)
{
    Trabajador * inicio = trabajadores;
    Trabajador * fin = (inicio + *tam);
    
    for(; inicio<fin; ++inicio)
    {
        free(inicio->puesto);
        free(inicio->fecha_empresa);
        free(inicio->fecha_nacimiento);
        free(inicio->apellidos);
        free(inicio->nombre);
    }
}


