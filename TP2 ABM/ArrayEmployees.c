#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <ArrayEmployees.h>

/** \brief  Muestra en pantalla el Menú de opciones
 * \param   No recibe parametros
 * \return  Retorna la opción ingresasa por teclado
 */

int menu()
{
    int opcion;

    system("cls");
    printf("  *** ABM Enterprise  ***\n\n");
    printf("1- Alta de empleados\n");
    printf("2- Baja de empleados\n");
    printf("3- Modificacion de empleados\n");
    printf("4- Listar empleados\n");
    printf("5- Salir\n\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opcion);

    return opcion;
}

/** \brief  Inicializa el array de empleados, poniendo todo el array en 1 (Vacío)
 *
 * \param   Recibe el vector de tipo employeeData
 * \param   Recibe el tamaño del vector
 * \return  No retorna nada
 *
 */

void initEmployees(employeeData vec[],int len){

    for (int i = 0; i < len; i++){

        vec[i].isEmpty = 1;
    }
}


/** \brief  Agrega un empleado nuevo (Alta)
 *
 * \param   Recibe el vector de tipo employeeData llamado vec
 * \param   Recibe el tamaño del vector
 * \param   Recibe el vector de tipo employeeSector llamado sectores
 * \param   Recibe el tamaño del vector
 * \return  No retorna nada
 *
 */

 void addEmployees(employeeData vec[], int len, employeeSector sectores[], int lensec){

    int indice;
    int id;
    int existe;

    //Buscar lugar disponible
    indice = findEmpty(vec, len);

    if (indice == -1){

        printf("No hay lugar disponible\n");

    }else
    {
        //Pido ID al usuario
        printf("Ingrese ID: ");
        scanf("%d", &id);

        //Me fijo si el empleado ya exite por ID
        existe = findEmployeeById(vec, len, id);

        if (existe == -1){

            //Pido el resto de los datos
            vec[indice].id = id;

            printf("Ingrese Nombre del Empleado: ");
            fflush(stdin);
            gets(vec[indice].name);

            printf("Ingrese Apellido del Empleado: ");
            fflush(stdin);
            gets(vec[indice].lastName);

            //Pongo en Mayus el primer caracter del nombre
        	for(int i=0; i <strlen(vec[indice].name); i++){

					vec[indice].name[0] = toupper(vec[indice].name[0]);
					if(vec[indice].name[i] == ' '){

						vec[indice].name[i+1] = toupper(vec[indice].name[i+1]);
					}
			}
			//Pongo en Mayus el primer caracter del apellido
			for(int i=0; i <strlen(vec[indice].lastName); i++){

					vec[indice].lastName[0] = toupper(vec[indice].lastName[0]);
					if(vec[indice].lastName[i] == ' '){

						vec[indice].lastName[i+1] = toupper(vec[indice].lastName[i+1]);
					}
			}

            printf("Ingrese Sueldo: ");
            scanf("%f", &vec[indice].salary);



            printSectores(sectores, lensec);

            printf("Ingrese ID Sector: ");
            scanf("%d", &vec[indice].sector);

            vec[indice].isEmpty = 0;

            printf("\nAlta Exitosa!!\n\n");

        }
        else{
            printf("Ya existe un empleado con ese ID\n");
            printEmployee(vec[existe], sectores, lensec);
        }


    }


 }

 /** \brief Busca en el array si hay un lugar libre
  *
  * \param  Recibe el vector de tipo employeeData
  * \param  Recibe el tamaño del vector
  * \return Retorna el indice donde hay un lugar libre. Si no hay lugar, retorna (-1)
  *
  */

int findEmpty(employeeData vec[], int len){

    int indice = -1;

    for (int i = 0; i < len; i++){

       if (vec[i].isEmpty == 1){
            indice = i;
            break;
       }
    }

    return indice;

}

/** \brief  Busca en el array si existe un empleado por ID
 *
 * \param   Recibe el vector de tipo employeeData
 * \param   Recibe el tamaño del vector
 * \param   Recibe el id
 * \return  Retorna el indice del array si ya existe un empleado con ese ID. Si no, retorna (-1)
 *
 */

int findEmployeeById (employeeData vec[], int len, int id){

    int indice = -1;

    for (int i = 0; i < len; i++){

       if (vec[i].isEmpty == 0 && vec[i].id == id){
            indice = i;
            break;
       }
    }

    return indice;
}

/** \brief  Obtiene el nombre del sector para luego mostrarlo en la lista de empleados
 *
 * \param   Recibe el array de tipo employeeSector
 * \param   Recibe el tamaño de dicho array
 * \param   Recibe el id del sectro
 * \param   Recibe la descripcion del sector
 * \return  si retorna 0, no se definió el sector. Si retorna 1, sector definido
 *
 */
int obtainSector(employeeSector sectores[], int lensec, int id, char desc[]){

    int fine = 0;

    for(int i=0; i < lensec; i++){

        if(id == sectores[i].idSector)
        {
            strcpy(desc, sectores[i].description);
            fine = 1;
            break;
        }
    }

    return fine;

}

/** \brief  Elimina a un empleado (Baja) pidiendo el ID del empleado
 *
 * \param   Recibe el vector de tipo employeeData llamado vec
 * \param   Recibe el tamaño del vector
 * \param   Recibe el vector de tipo employeeSector llamado sectores
 * \param   Recibe el tamaño del vector
 * \return  No retorna valor
 *
 */

void removeEmployees(employeeData vec[], int len, employeeSector sectores[], int lensec){

    int id;
    int existe;
    char confirma;
    //Pide ID
    printf("Ingrese el ID: ");
    scanf("%d", &id);
    //Lo busca si existe
    existe = findEmployeeById(vec, len, id);

    if (existe == -1){

        printf("No hay empleado registrado con ID: \'%d\'\n",id);
    }
    else
    {
        //Muestra al empleado existente
        printEmployee(vec[existe], sectores, lensec);

        printf("Desea confirmar eliminacion? s/n: ");
        fflush(stdin);
        confirma = getche();
        printf("\n");

        if (tolower(confirma)== 's'){
            vec[existe].isEmpty = 1;
        }
    }

}

/** \brief Lista a un empleado en particular o todos los empleados
 *
 * \param   Recibe una variable de tipo employeeData con nombre 'employee'
 * \param   Recibe el array de tipo employeeSector con nombre 'sectores'
 * \param   Recibe el tamaño de dicho vector
 * \return  No retorna valor
 *
 */

 void printEmployee(employeeData employee, employeeSector sectores[], int lensec){

    char nameSector[20];
    int obtainName;

    obtainName = obtainSector(sectores, lensec, employee.sector, nameSector);

    if(!obtainName){
         strcpy(nameSector, "Sin definir");
    }

    printf("%s     %s       %d       %.2f      %s\n", employee.lastName, employee.name, employee.id, employee.salary, nameSector);

}

/** \brief  Muestra el titulo de la lista y chequea si hay empleados dados de alta para mostrar
 *
 * \param   Recibe el vector de tipo employeeData llamado vec
 * \param   Recibe el tamaño del vector
 * \param   Recibe el vector de tipo employeeSector llamado sectores
 * \param   Recibe el tamaño del vector
 * \return  No retorna valor
 *
 */

void printEmployees(employeeData vec[], int len, employeeSector sectores[], int lensec){

    int contador = 0;

    system("cls");

    printf("APELLIDO      NOMBRE      ID         SUELDO    SECTOR\n");

    sortEmployees(vec, len);

    for (int i = 0; i < len; i++){

        if(vec[i].isEmpty == 0){

            printEmployee(vec[i], sectores, lensec);
            contador++;
        }

    }

    if (contador == 0){

        printf("No hay empleados para mostrar\n");
    }

}

/** \brief  Muestra el menú de Sectores
 *
 * \param   Recibe el array de tipo employeeSector con nombre "sectores"
 * \param   Recibe el  tamaño de dicho array
 * \return  No retorna valor
 *
 */

void printSectores(employeeSector sectores[], int lensec){

    printf("\n    Sectores\n");
    printf(" ID     Descripcion\n\n");

    for(int i=0; i < lensec; i++){
        printf("  %d      %s\n", sectores[i].idSector, sectores[i].description);
    }
    printf("\n\n");
}


/** \brief Función para confirma la salida de la consola y finalizar programa
 *
 * \param  No recibe parametros
 * \return Retorna el caracter ingresado por el usuario 's' o 'n'
 *
 */

 char confirmar(){

    char letra = 's';
    char confirma;
    printf("\nConfirmar salida s/n?: ");
    fflush(stdin);
    confirma = tolower(getche());

    while (confirma != 's' && confirma != 'n'){
        printf("\nDato erroneo..Vuelva a confirmar..");
        printf("\nConfirmar salida s/n?: ");
        fflush(stdin);
        confirma = tolower(getche());
    }
    if(tolower(confirma) == 's')
    {
       letra = 'n';
    }
    return letra;
}

/** \brief  Modifica cualquier dato del empleado pidiendo el ID
 *
 * \param   Recibe el vector de tipo employeeData llamado vec
 * \param   Recibe el tamaño del vector
 * \param   Recibe el vector de tipo employeeSector llamado sectores
 * \param   Recibe el tamaño del vector
 * \return  No retorna valor
 *
 */

 void modifyEmployees (employeeData vec[], int len, employeeSector sectores[], int lensec){

    int id;
    int existe;
    int newSector;
    float newSalary;
    char newName[51];
    char newLastName[51];
    char confirma;

    printf("Ingrese el ID: ");
    scanf("%d", &id);

    existe = findEmployeeById(vec, len, id);

    if (existe == -1){

        printf("No hay empleado registrado con ID \'%d\'\n",id);
    }
    else
    {
        printEmployee(vec[existe], sectores, lensec);

        printf("Desea modificar el sueldo? s/n: ");
        fflush(stdin);
        confirma = getche();
        printf("\n");

        if (tolower(confirma)== 's'){
            printf("Ingrese nuevo sueldo: ");
            scanf("%f", &newSalary);
            vec[existe].salary = newSalary;
            printf("Sueldo modificado\n\n");
        }
            printf("Desea modificar el nombre? s/n: ");
            fflush(stdin);
            confirma = getche();
            printf("\n");

        if (tolower(confirma)== 's'){
            printf("Ingrese nuevo nombre: ");
            fflush(stdin);
            gets(newName);
            strcpy(vec[existe].name,newName);
            printf("Nombre modificado\n\n");
        }

            printf("Desea modificar el apellido? s/n: ");
            fflush(stdin);
            confirma = getche();
            printf("\n");

        if (tolower(confirma)== 's'){
            printf("Ingrese nuevo Apellido: ");
            fflush(stdin);
            gets(newLastName);
            strcpy(vec[existe].lastName,newLastName);
            printf("Apellido modificado\n\n");

        }
        printf("Desea modificar el sector? s/n: ");
            fflush(stdin);
            confirma = getche();
            printf("\n");

        if (tolower(confirma)== 's'){
            printf("Ingrese ID Sector: ");
            scanf("%d", &newSector);
            vec[existe].sector=newSector;
            printf("Sector modificado\n\n");

        }
        else{

            printf("\nNo se ha modificado el empleado\n\n");

        }
        }
    }


/** \brief  Ordena la lista de empleados antes de mostrar en pantalla por apellido
 *
 * \param   Recibe el vector de tipo employeeData con nombre 'vec'
 * \param   Recibe el tamaño de dicho vector
 * \return  No retorna nada
 *
 */

 void sortEmployees(employeeData vec[], int len){

    employeeData auxEmployee;

    for (int  i = 0; i < len-1; i++){

            if(vec[i].isEmpty == 1){
                continue;
            }

        for (int j = i + 1; j < len; j++ ){

             if(vec[j].isEmpty == 1){
                continue;
            }

            if(strcmp(vec[i].lastName, vec[j].lastName)>0){

                auxEmployee = vec[j];
                vec[j]= vec[i];
                vec[i] = auxEmployee;
            }
        }
    }

}

