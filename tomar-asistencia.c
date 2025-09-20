#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OFFSET 1
#define WEEK_DAYS 5
#define TAKE_ATTENDANCE 1
#define SHOW_DAY_ATTENDANCE 2
#define SHOW_WEEK_ATTENDANCE 3
#define ADVANCE_DAY 4
#define QUIT 5

typedef struct {
  int *attendance; // 1 - present, 0 - not present
  int id;
  char *name;
} TStudent;

typedef struct TNode {
  TStudent student;
  struct TNode *next;
} TNode;

void welcome();
int readNStudents();
void readStudentsData(int n_students);
TNode *insertStart(TNode *head, TStudent student, char current_student_name[]);
TNode *createNode(TStudent student, char current_student_name[]);
void printMenu(TNode *head);
void callFunctions(int option, int *current_day, TNode *head,
                   int *attendance_taken);

void takeAttendance(TNode *head, int current_day);
void printDayAttendance(TNode *head, int current_day);
void printWeekAttendance(TNode *head, int *attendance_taken, int current_day);
void advanceDay();

int main()
{
  int n_students;
  welcome();
  n_students = readNStudents();
  readStudentsData(n_students);

  return 0;
}

void welcome()
{
  system("clear");
  printf("X------------------------------------------------X\n");
  printf("Bienvenido al programa de\ntoma de asistencia de alumnos.\n");
  char buffer;
  printf("Presiona N.\n> ");
  scanf(" %c", &buffer);
  printf("X------------------------------------------------X\n");
  system("clear");
}

int readNStudents()
{
  int n_students;
  printf("X------------------------------------------------X\n");
  printf("Ingresa la cantidad de alumnos de la clase:\n");
  printf("X------------------------------------------------X\n> ");
  scanf("%d", &n_students);
  system("clear");
  return n_students;
}

void readStudentsData(int n_students)
{
  TNode *head = NULL;
  TStudent current_student;
  char current_student_name[50];
  printf("X------------------------------------------------X\n");
  for (int i = 0; i < n_students; i++) {
    printf("Ingresa el id del estudiante #%d: ", i + OFFSET);
    scanf("%d", &current_student.id);
    printf("Ingresa el nombre del estudiante #%d: ", i + OFFSET);
    scanf(" %[^\n]", current_student_name);
    head = insertStart(head, current_student, current_student_name);
  }
  printMenu(head);
}

TNode *insertStart(TNode *head, TStudent current_student,
                   char current_student_name[])
{
  TNode *new = createNode(current_student, current_student_name);
  new->next = head;
  return new;
}

TNode *createNode(TStudent current_student, char current_student_name[])
{
  TNode *new = (TNode *)malloc(sizeof(TNode));
  if (new == NULL) {
    printf("Error al asignar memoria\n");
    return NULL;
  }
  new->student.id = current_student.id;
  new->student.name =
      (char *)malloc(strlen(current_student_name) * sizeof(char));
  if (new->student.name == NULL) {
    printf("Error al asignar memoria\n");
    return NULL;
  }
  strcpy(new->student.name, current_student_name);
  new->student.attendance = (int *)malloc(WEEK_DAYS * sizeof(int));
  if (new->student.attendance == NULL) {
    printf("Error al asignar memoria\n");
    return NULL;
  }
  return new;
}

void printMenu(TNode *head)
{
  int option, current_day = 1;
  int *attendance_taken;
  attendance_taken = (int *)malloc(WEEK_DAYS * sizeof(int));
  if (attendance_taken == NULL) {
    printf("Error al asignar memoria\n");
    return;
  }
  do {
    printf("X------------------------------------------------X\n");
    printf("Dia: %d\n\n", current_day);
    printf("Elige una opcion:\n");
    printf("1. Tomar lista\n");
    printf("2. Mostrar asistencia del dia\n");
    printf("3. Mostrar asistencia de la semana\n");
    printf("4. Avanzar dia\n");
    printf("5. Salir\n");
    printf("X------------------------------------------------X\n> ");
    scanf("%d", &option);
    callFunctions(option, &current_day, head, attendance_taken);
    if (current_day == 6) {
      printf("Nueva semana\n");
      current_day = 1;
      for (int i = 1; i <= WEEK_DAYS; i++) {
        *(attendance_taken + i) = 0;
      }
    }
  } while (option != 5);
}

void callFunctions(int option, int *current_day, TNode *head,
                   int *attendance_taken)
{
  switch (option) {
  case TAKE_ATTENDANCE:
    if (*(attendance_taken + *current_day) == 1) {
      printf("Ya se tomo asistencia hoy\n");
    }
    else {
      *(attendance_taken + *current_day) = 1;
      takeAttendance(head, *current_day);
    }
    break;
  case SHOW_DAY_ATTENDANCE:
    if (*(attendance_taken + *current_day) == 1) {
      printDayAttendance(head, *current_day);
    }
    else {
      printf("No se ha tomado asistencia hoy\n");
    }
    break;
  case SHOW_WEEK_ATTENDANCE:
    printWeekAttendance(head, attendance_taken, *current_day);
    break;
  case ADVANCE_DAY:
    (*current_day)++;
    break;
  case QUIT:
    return;
  default:
    printf("Opcion no valida\n");
    break;
  }
}

void takeAttendance(TNode *head, int current_day)
{
  TNode *current_student = head;
  int student_attended;
  printf("X------------------------------------------------X\n");
  printf("Tomar asistencia de hoy:\n");
  printf("Asistio: 1, No asistio: 0\n");
  while (current_student != NULL) {
    printf("%s, %d: ", current_student->student.name,
           current_student->student.id);
    scanf("%d", &student_attended);
    *(current_student->student.attendance + current_day) = student_attended;
    current_student = current_student->next;
  }
}

void printDayAttendance(TNode *head, int current_day)
{
  TNode *current_student = head;
  printf("X------------------------------------------------X\n");
  printf("Asistencia de hoy:\n\n");
  while (current_student != NULL) {
    printf("%s, %d: ", current_student->student.name,
           current_student->student.id);
    if (*(current_student->student.attendance + current_day) == 1) {
      printf("Asistio\n");
    }
    else {
      printf("No asistio\n");
    }
    current_student = current_student->next;
  }
}

void printWeekAttendance(TNode *head, int *attendance_taken, int current_day)
{
  printf("X------------------------------------------------X\n");
  printf("Asistencia de la semana:\n\n");
  for (int i = 1; i <= current_day; i++) {
    printf("Dia %d:\n", i);
    if (*(attendance_taken + i) == 1) {
      TNode *current_student = head;
      while (current_student != NULL) {
        printf("%s, %d: ", current_student->student.name,
               current_student->student.id);
        int *current_attendance = current_student->student.attendance + i;
        if (*current_attendance == 1) {
          printf("Asistio\n");
        }
        else {
          printf("No asistio\n");
        }
        current_student = current_student->next;
      }
    }
    else {
      printf("No se tomo asistencia ese dia\n\n");
      continue;
    }
    printf("\n");
  }
}
