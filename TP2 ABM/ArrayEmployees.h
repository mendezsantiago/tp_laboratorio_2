typedef struct{

   int idSector;
   char description[20];

}employeeSector;

typedef struct{

    int id;
    int isEmpty;
    int sector;
    float salary;
    char name[51];
    char lastName[51];

}employeeData;


//Prototipos
int menu();
char confirmar();
void initEmployees(employeeData vec[],int len);
void addEmployees(employeeData vec[], int len, employeeSector sectores[], int lensec);
void removeEmployees(employeeData vec[], int len, employeeSector sectores[], int lensec);
void modifyEmployees (employeeData vec[], int len, employeeSector sectores[], int lensec);
void printEmployee(employeeData employee, employeeSector sectores[], int lensec);
void printEmployees(employeeData vec[], int len, employeeSector sectores[], int lensec);
void printSectores(employeeSector sectores[], int lensec);
void sortEmployees(employeeData vec[], int len);
int findEmpty(employeeData vec[], int len);
int findEmployeeById(employeeData vec[], int len, int id);
int obtainSector(employeeSector sectores[], int lensec, int idSector, char desc[]);

