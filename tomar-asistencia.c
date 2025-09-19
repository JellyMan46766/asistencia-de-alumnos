#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OFFSET 1
#define WEEK_DAYS 5

typedef struct {
  int *attendance; // 1 - present, 0 - not present
  int id;
  char *name;
} TStudent;

typedef struct {
  TStudent student;
  struct TNode *next;
} TNode;

void welcome();
int readNStudents();
void readStudentsData(int n_students);
TNode *insertStart(TNode *head, TStudent student);
TNode *createNode(TStudent student);
void printMenu();

void takeAttendance(TNode *head);
void printDayAttendance(TNode *head);
void printWeekAttendance(TNode *head);
void advanceDay();

int main()
{
  int n_students;
  welcome();
  n_students = readNStudents();
  readStudentsData(n_students);
  printMenu();

  return 0;
}

void welcome()
{
  printf("X-------------------------------X\n");
  printf("Bienvenido al programa de\ntoma de asistencia de alumnos.\n");
  char buffer;
  printf("Presiona N.\n> ");
  scanf(" %c", &buffer);
  printf("X-------------------------------X\n");
  system("clear");
}

int readNStudents()
{
  int n_students;
  printf("X-------------------------------X\n");
  printf("Ingresa la cantidad de alumnos de la clase:\n");
  printf("X-------------------------------X\n> ");
  scanf("%d", &n_students);
  system("clear");
  return n_students;
}

void readStudentsData(int n_students)
{
  TNode *head = NULL;
  TStudent current_student;
  printf("X-------------------------------X\n");
  for (int i = 0; i < n_students; i++) {
    printf("Ingresa el id del estudiante #%d: ", i + OFFSET);
    scanf("%d", &current_student.id);
    printf("Ingresa el nombre del estudiante #%d", i + OFFSET);
    scanf("%[^\n]", current_student.name);
    head = insertStart(head, current_student);
  }
}

TNode *insertStart(TNode *head, TStudent current_student)
{
  TNode *new = createNode(current_student);
  new->next = head;
  return new;
}

TNode *createNode(TStudent current_student)
{
  TNode *new = (TNode *)malloc(sizeof(TNode));
  if (new == NULL) {
    printf("Error al asignar memoria\n");
    return NULL;
  }
  new->student.id = current_student.id;
  new->student.name =
      (char *)malloc(strlen(current_student.name) * sizeof(char));
  if (new->student.name == NULL) {
    printf("Error al asignar memoria\n");
    return NULL;
  }
  new->student.attendance = (int *)malloc(WEEK_DAYS * sizeof(int));
  if (new->student.attendance == NULL) {
    printf("Error al asignar memoria\n");
    return NULL;
  }
  return new;
}
