#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quicksort(void *lineptr[], int left, int right, int reveresed,
               int (*comp)(void *, void *));

int numcmp(const char *, const char *);

int main(int argc, char *argv[])
{
  int nlines;
  int numeric = 0, reversed = 0, casefold = 0;
  char c;
  int (*compfunc)(void*, void*);

  while (--argc > 0 && (*++argv)[0] == '-') {
    while ((c = *++argv[0])) {
      switch (c) {
        case 'n':
          numeric = 1;
          break;
        case 'r':
          reversed = 1;
          break;
        case 'f':
          casefold = 1;
          break;
        default:
          printf("Unrecognised option %c\n", c);
          break;
      }
    }
  }

  // Below - casts function to a pointer to a  function that takes two void pointers
  if (numeric) {
    compfunc = (int (*)(void*, void*))numcmp;
  } else if (casefold) {
    compfunc = (int (*)(void*, void*))strcasecmp;
  } else {
    compfunc = (int (*)(void*, void*))strcmp;
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    quicksort((void **) lineptr, 0, nlines-1, reversed, compfunc);
              // lineptr cast as pointer to void pointer
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("Input too big to sort\n");
    return 1;
  }
}


int numcmp(const char *s1, const char *s2)
{
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}
