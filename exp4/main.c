#include "bstree.h"
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
  for (i = NUMBER_OF_WORDS - 1; i >= 0; i--) {
    fscanf(fp, "%s ", words[i]);
  }

  struct bstree *treeGood = bstree_create(words[0], 0);
  double lookupTimer = 0, lookupTemp = 0;

  FILE *bstreeLookupGood = fopen("bstreeLookupG.dat", "w");


  for (i = 1; i <= NUMBER_OF_WORDS; ++i) {
    bstree_add(treeGood, words[i], i);
    if (i % 300 == 0) {
      lookupTimer = wtime();
      bstree_min(treeGood);
      lookupTemp += wtime() - lookupTimer;
    }
    if (i % 6000 == 0) {
      fprintf(bstreeLookupGood, "%d %f\n", i / 1000, lookupTemp * 50);
      lookupTemp = 0;
    }
  }





  shuffle(words);

  struct bstree *treeBad = bstree_create(words[0], 0);
  lookupTimer = 0, lookupTemp = 0;

  FILE *bstreeLookupBad = fopen("bstreeLookupB.dat", "w");

  //struct bstree *treeNode;
  for (i = 1; i <= NUMBER_OF_WORDS; ++i) {
    bstree_add(treeBad, words[i], i);
    if (i % 300 == 0) {
      lookupTimer = wtime();
      //treeNode = bstree_min(treeBad);
      bstree_min(treeBad);
      lookupTemp += wtime() - lookupTimer;
    }
    if (i % 6000 == 0) {
      //printf("%s\n", treeNode->key);
      fprintf(bstreeLookupBad, "%d %f\n", i / 1000, lookupTemp * 50);
      lookupTemp = 0;
    }
  }

  fclose(bstreeLookupBad);
  fclose(bstreeLookupGood);
  fclose(fp);

  return 0;
}
