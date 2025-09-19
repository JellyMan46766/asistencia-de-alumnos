typedef struct {
  int *present; // 1 - present, 0 - not present
  int id;
  char *name;
} TStudent;

typedef struct {
  TStudent student;
  struct TNode *next;
} TNode;

void printMenu();
int readNStudents();
void readStudentsData();
TNode *createNode(TStudent student);
TNode *insertStart(TNode *head, TStudent student);

void takeAttendance(TNode *head);
void printDayAttendance(TNode *head);
void printWeekAttendance(TNode *head);
void advanceDay();
