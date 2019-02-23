#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TCar
{
  struct TCar              * m_Next;
  char                     * m_Model;
} TCAR;

typedef struct TEmployee
{
  struct TEmployee         * m_Next;
  struct TCar              * m_Car;
  char                     * m_Name;
} TEMPLOYEE;

typedef struct TOffice
{
  TEMPLOYEE                * m_Emp;
  TCAR                     * m_Car;
} TOFFICE;

char* makeCopyOf(const char *src)
{
  size_t result_size = strlen(src) + 1;
  char *result = (char *) malloc(result_size);
  if(result == NULL)
  {
    return NULL;
  }
  strcpy(result, src);
  *(result + result_size -1) = '\0';
  return result;
}

void freeCar(TCAR *head)
{
  while(head)
  {
    TCAR *temp_car = head->m_Next;
    free(head->m_Model);
    free(head);
    head = temp_car;
  }
}

void freeEmployee(TEMPLOYEE *head)
{
  while(head)
  {
    TEMPLOYEE* temp_empl = head->m_Next;
    free(head->m_Name);
    free(head);
    head = temp_empl;
  }
}

TOFFICE * initOffice ()
{
  TOFFICE *new_office = (TOFFICE *)malloc(sizeof(*new_office));
  if(new_office == NULL)
  {
    return NULL;
  }
  new_office->m_Emp = NULL;
  new_office->m_Car = NULL;
  return new_office;
}

TEMPLOYEE* initEmployee(const char *name, TCAR *car)
{
  TEMPLOYEE *new_employee = (TEMPLOYEE *) malloc(sizeof(*new_employee));
  if(new_employee == NULL)
  {
    return NULL;
  }
  new_employee->m_Car = car;
  new_employee->m_Name = makeCopyOf(name);
  return new_employee;
}

void addEmployee ( TOFFICE * office,
                                  const char * name )
{
  TEMPLOYEE *new_employee = initEmployee(name, NULL);
  if(new_employee == NULL)
  {
    return;
  }
  new_employee->m_Next = office->m_Emp;
  office->m_Emp = new_employee;
}

TCAR* initCar(const char *model)
{
  TCAR *new_car = (TCAR *) malloc(sizeof(*new_car));
  if(new_car == NULL)
  {
    return NULL;
  }
  new_car->m_Model = makeCopyOf(model);
  return new_car;
}

void addCar ( TOFFICE * office,
              const char * model )
{
  TCAR *new_car = initCar(model);
  if(new_car == NULL)
  {
    return;
  }
  new_car->m_Next = office->m_Car;
  office->m_Car = new_car;
}

void duplicateCars(TCAR *head)
{
  TCAR *next;
  while(head)
  {
    next = head->m_Next;
    head->m_Next = initCar(head->m_Model);
    if(head->m_Next == NULL)
    {
      return;
    }
    head->m_Next->m_Next = next;
    head = next;
  }
}

TCAR* splitCars(TCAR *original)
{
  TCAR *copy_head = NULL;
  if(original)
  {
    TCAR *copy = original->m_Next;
    copy_head = copy;
    while (original && copy)
    {
        original->m_Next = original->m_Next ? original -> m_Next->m_Next : NULL;
        copy->m_Next = copy->m_Next ? copy -> m_Next->m_Next : NULL;
        original = original->m_Next;
        copy = copy->m_Next;
    }
  }
  return copy_head;
}

void duplicateEmployees(TEMPLOYEE *head)
{
  TEMPLOYEE *next;
  while(head)
  {
    next = head->m_Next;
    TCAR *dummy = NULL;
    if(head->m_Car)
    {
      dummy = head->m_Car->m_Next;
    }
    head->m_Next = initEmployee(head->m_Name, dummy);
    if(head->m_Next == NULL)
    {
      return;
    }
    head->m_Next->m_Next = next;
    head = next;
  }
}

TEMPLOYEE* splitEmployees(TEMPLOYEE *original)
{
  TEMPLOYEE *copy_head = NULL;
  if(original)
  {
    TEMPLOYEE *copy = original->m_Next;
    copy_head = copy;
    while (original && copy)
    {
        original->m_Next = original->m_Next? original->m_Next->m_Next : NULL;
        copy->m_Next = copy->m_Next? copy->m_Next->m_Next: NULL;
        original = original->m_Next;
        copy = copy->m_Next;
    }
  }
  return copy_head;
}

TOFFICE * cloneOffice ( TOFFICE * office )
{
  if(office == NULL)
  {
    return NULL;
  }
  TOFFICE *new_office = initOffice();
  duplicateCars(office->m_Car);
  duplicateEmployees(office->m_Emp);
  new_office->m_Car = splitCars(office->m_Car);
  new_office->m_Emp = splitEmployees(office->m_Emp);
  return new_office;
}
void freeOffice ( TOFFICE * office )
{
  if(office == NULL)
  {
    return;
  }
  freeCar(office->m_Car);
  freeEmployee(office->m_Emp);
  free(office);
}
