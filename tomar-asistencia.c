typedef struct {
  int *present; // 1 - present, 0 - no present
  int id;
  char *name;
} TStudent;

typedef struct {
  TStudent student;
  struct TNode *next;
} TNode;
