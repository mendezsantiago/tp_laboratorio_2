#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <ArrayEmployees.h>

#define LEN 1000
#define LENSEC 5


/*
    *   Falta agregar el total de salarios + promedio + salarios por encima del promedio
    **  Modificar el ingreso del ID por automatico
    *** Corregir error de compilación. No detecta el archivo.h en el directorio. Si se pone todo en el main (Estructuras, prototipos
        y funciones), el programa funciona.

*/


//Inicio del main
int main()
{
    //Declaro arrays
    employeeData arrayEmployees[LEN];
    initEmployees(arrayEmployees, LEN);

    employeeSector sectores[] =
    {
        {1, "Area Tecnica"},
        {2, "Area Produccion"},
        {3, "Area Comercial"},
        {4, "Area Logistica"},
        {5, "Area I+D"},

    };

    char seguir = 's';

    do{
            switch(menu()){
            case 1:
                addEmployees (arrayEmployees, LEN, sectores, LENSEC);
                system("pause");
            break;
            case 2:
                removeEmployees(arrayEmployees, LEN, sectores, LENSEC);
                system("pause");
            break;
            case 3:
                modifyEmployees(arrayEmployees, LEN, sectores, LENSEC);
                system("pause");
            break;
            case 4:
                printEmployees(arrayEmployees, LEN, sectores, LENSEC);
                system("pause");
            break;
            case 5:
                seguir = confirmar();
                printf("\n");
                system("pause");
            break;
            default:
                printf("\n Opcion invalida\n\n");
                system("break");
            }//Fin switch

    }while(seguir == 's');

    return 0;
}







