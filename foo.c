#include <stdlib.h>

typedef struct {
  int value;
  struct TNode *next;
} TNode;

TNode *insertStart(TNode *head, int value);
TNode *createNode(int value);

int main(int argc, char *argv[])
{
  TNode *head = NULL;

  head = insertStart(head, 3);

  return 0;
}

TNode *insertStart(TNode *head, int value)
{
  TNode *new = createNode(value);
  new->next = head;
  return new;
}

TNode *createNode(int value)
{
  TNode *new = (TNode *)malloc(sizeof(TNode));
  new->value = value;
  return new;
}
