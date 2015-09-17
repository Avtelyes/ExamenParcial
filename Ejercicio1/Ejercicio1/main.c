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

void adicionNomina(Trabajador *, int * );
void edicionNomina(Trabajador * , int * );
void borrarNomina(Trabajador * , int * );
void adicionEstructura(Modelo * , int * );
void adicionEdificio(Edificio * , int * );

void reporteTrabajadores(Trabajador *, int * );

void liberarMemoria(Trabajador *, int * );

typedef struct {
    Modelo * modelo;
} Trabajo;

int main(int argc, const char * argv[]) {
    
    int numTrabajadores = 0;
    
    printf("Dame el numero de trabajadores a adicionar: ");
    scanf("%d", &numTrabajadores);
    
    
    Trabajador * nomina = (Trabajador *) malloc(numTrabajadores * sizeof(Trabajador));
    
    adicionNomina(nomina, &numTrabajadores);
    reporteTrabajadores(nomina, &numTrabajadores);
    
    
    liberarMemoria(nomina, &numTrabajadores);
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
            free(inicio);
        }
    }
}

void adicionEstructura(Modelo * modelos, int * tam, Trabajador * persona)
{
    int opcion = 0;
    
    printf("Dame el tipo de estructura:\n1.- Edificio\n2.-Torre\n3.-Nave\n");
    scanf("%d", &opcion);
    
    if(opcion == 1)
    {
        adicionEdificio(modelos->edificio, &modelos->tamEdificio, persona);
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
            
            strcpy("Edificio", inicio->tipo);
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
        }
    }
}

void reporteTrabajadores(Trabajador * nomina, int * tam)
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

void liberarMemoria(Trabajador * trabajadores, int * tam)
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


