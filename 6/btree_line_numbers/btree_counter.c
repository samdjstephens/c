#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define MAXLINE 10000

typedef struct tnode {
  char *word;
  int* line_numbers;
  int total_linenumbers;
  struct tnode *left;
  struct tnode *right;
} Treenode;


Treenode *addtree(Treenode *, char *, int, int);
void treeprint(Treenode *);
int sget_word(char* s, char* word, int lim);
int get_line(char *s, int lim);
Treenode* balance_tree(Treenode*);


int main()
{
  Treenode *root;
  char line[MAXLINE];
  char word[MAXWORD];
  char* line_pos;
  int len, linenumber = 0, advanced;
  root = NULL;

  while ((len = get_line(line, MAXLINE)) > 0) {
    advanced = 0;
    line_pos = line;
    linenumber++;
    while ((advanced = sget_word(line_pos = line_pos + advanced, word, 100)) > 0) {
      if (isalpha(word[0])) {
        root = addtree(root, word, linenumber, 0);
      }
    }
  }
  treeprint(root);
  printf("\n\n##### BALANCED #####\n\n");
  root = balance_tree(root);
  treeprint(root);
  return 0;
}
