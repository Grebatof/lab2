#include "bstree.h"
#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define NUMBER_OF_WORDS 90001
#define SIZE_OF_WORD 50

void swap(char* cur, char* rep)
{
  char temp[SIZE_OF_WORD];
  strcpy(temp, cur);
  strcpy(cur, rep);
  strcpy(rep, temp);
}

int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void shuffle(char words[NUMBER_OF_WORDS][SIZE_OF_WORD]) {
  for (size_t i = 0; i < NUMBER_OF_WORDS; i++) {
    swap(words[i], words[getrand(0, NUMBER_OF_WORDS)]);
  }
}

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main() {

  char words[NUMBER_OF_WORDS][SIZE_OF_WORD];
  srand(time(NULL));
  FILE *fp;
  fp = fopen("txt.txt", "r");
  int i;
  for (i = 0; i < NUMBER_OF_WORDS; i++) {
    fscanf(fp, "%s ", words[i]);
  }

  shuffle(words);

  struct bstree *tree = bstree_create(words[0], 0);
  struct listnode *hashtab[NUMBER_OF_WORDS];
  double lookupTimer1 = 0, lookupTemp1 = 0, lookupTimer2 = 0, lookupTemp2 = 0;
  hashtab_init(hashtab);

  FILE *bstreeLookup = fopen("bstreeLookup.dat", "w");
  FILE *hashtabLookup = fopen("hashtabLookup.dat", "w");


  for (i = 1; i <= NUMBER_OF_WORDS; ++i) {
    bstree_add(tree, words[i], i);
    hashtab_add(hashtab, words[i], i);
    if (i % 300 == 0) {
      char *searchKey = words[getrand(0, i)];
      lookupTimer1 = wtime();
      struct bstree *treeNode = bstree_lookup(tree, searchKey);
      lookupTemp1 += wtime() - lookupTimer1;
      lookupTimer2 = wtime();
      struct listnode *hashNode = hashtab_lookup(hashtab, searchKey);
      lookupTemp2 += wtime() - lookupTimer2;
    }
    if (i % 6000 == 0) {
      fprintf(bstreeLookup, "%d %f\n", i / 1000, lookupTemp1 * 50);
      lookupTemp1 = 0;
      fprintf(hashtabLookup, "%d %f\n", i / 1000, lookupTemp2 * 50);
      lookupTemp2 = 0;
    }
  }

  fclose(bstreeLookup);
  fclose(hashtabLookup);
  fclose(fp);

  return 0;
}
