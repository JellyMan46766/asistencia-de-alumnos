#include <stdio.h>
#include <stdlib.h>

#define OFFSET 1

typedef struct {
  int *present; // 1 - present, 0 - not present
  int id;
  char *name;
} TStudent;

typedef struct {
  TStudent student;
  struct TNode *next;
} TNode;

void menu();
void welcome();
int readNStudents();
void readStudentsData(int n_students);
TNode *createNode(TStudent student);
TNode *insertStart(TNode *head, TStudent student);

void takeAttendance(TNode *head);
void printDayAttendance(TNode *head);
void printWeekAttendance(TNode *head);
void advanceDay();

int main()
{
  menu();

  return 0;
}

void menu()
{
  int n_students;
  welcome();
  n_students = readNStudents();
  readStudentsData(n_students);
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
  TNode *head;
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
