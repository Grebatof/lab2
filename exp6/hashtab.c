#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHTAB_SIZE 75000

unsigned int hashtab_hash(char *key) {
    unsigned int h = 0, hash_mul = 31;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % HASHTAB_SIZE;
}

unsigned int FNV1Hash(char *buf)
{
  unsigned int hval = 2166136261; // FNV0 hval = 0
  unsigned int fnv_32_prime = 16777619;

  while (*buf)
    {
      hval *= fnv_32_prime;
      hval ^= (unsigned int)*buf++;
    }

  return hval % HASHTAB_SIZE;
}

void hashtab_init(struct listnode **hashtab) {
    int i;
    for (i = 0; i < HASHTAB_SIZE; i++)
        hashtab[i] = NULL;
}

void hashtab_add(struct listnode **hashtab, char *key, int value, int switcher, int *collision) {
    struct listnode *node;
    unsigned int index = 0;

    if (switcher == 0) {
      index = hashtab_hash(key);
    } else {
      index = FNV1Hash(key);
    }

    if (hashtab[index] != NULL) {
      (*collision)++;
    }

    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    } // добавить некое число K - коллизий, если hashtab[index] != NULL, то ++, иначе ничего не происходит
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key, int switcher) {
    struct listnode *node;
    int index;

    if (switcher == 0) {
      index = hashtab_hash(key);
    } else {
      index = FNV1Hash(key);
    }

    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key)) {
            return node;
        }
    }
    return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key) {
    struct listnode *node, *prev = NULL;
    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key)) {
            if (prev == NULL)
                hashtab[index] = node->next;
            else
                prev->next = node->next;
            free(node);
            return;
        }
        prev = node;
    }
}
