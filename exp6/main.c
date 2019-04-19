#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define NUMBER_OF_WORDS 75000
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
  fp = fopen("txt1.txt", "r");
  int i;
  for (i = 0; i < NUMBER_OF_WORDS; i++) {
    fscanf(fp, "%s", words[i]);
  }

  shuffle(words);

  struct listnode *hashtab1[NUMBER_OF_WORDS];
  struct listnode *hashtab2[NUMBER_OF_WORDS];
  double lookupTimer = 0, lookupTemp = 0;
  int collision = 0;
  int switcher = 0;
  hashtab_init(hashtab1);
  hashtab_init(hashtab2);

  FILE *hashtab1Lookup = fopen("hashtab1Lookup.dat", "w");
  FILE *hashtab2Lookup = fopen("hashtab2Lookup.dat", "w");
  FILE *hashtab1Kol = fopen("hashtab1Kol.dat", "w");
  FILE *hashtab2Kol = fopen("hashtab2Kol.dat", "w");

  for (i = 1; i <= NUMBER_OF_WORDS; ++i) {
    hashtab_add(hashtab1, words[i], i, switcher, &collision);
    if (i % 300 == 0) {
      char *searchKey = words[getrand(0, i)];
      lookupTimer = wtime();
      struct listnode *hashNode = hashtab_lookup(hashtab1, searchKey, switcher);
      lookupTemp += wtime() - lookupTimer;
    }
    if (i % 6000 == 0) {
      fprintf(hashtab1Lookup, "%d %f\n", i / 1000, lookupTemp * 50);
      fprintf(hashtab1Kol, "%d %d\n", i / 1000, collision);
      lookupTemp = 0;
    }
  }

  lookupTemp = 0;
  collision = 0;
  switcher = 1;

  for (i = 1; i <= NUMBER_OF_WORDS; ++i) {
    hashtab_add(hashtab2, words[i], i, switcher, &collision);
    if (i % 300 == 0) {
      char *searchKey = words[getrand(0, i)];
      lookupTimer = wtime();
      struct listnode *hashNode = hashtab_lookup(hashtab2, searchKey, switcher);
      lookupTemp += wtime() - lookupTimer;
    }
    if (i % 6000 == 0) {
      fprintf(hashtab2Lookup, "%d %f\n", i / 1000, lookupTemp * 50);
      fprintf(hashtab2Kol, "%d %d\n", i / 1000, collision);
      lookupTemp = 0;
    }
  }

  fclose(hashtab1Lookup);
  fclose(hashtab2Lookup);
  fclose(hashtab1Kol);
  fclose(hashtab2Kol);
  fclose(fp);

  return 0;
}
