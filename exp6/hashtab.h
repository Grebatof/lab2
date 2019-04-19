#pragma once

typedef struct listnode {
    char *key;
    int value;
    struct listnode *next;
} listnode;

unsigned int hashtab_hash(char *key);
void hashtab_init(struct listnode **hashtab);
void hashtab_add(struct listnode **hashtab, char *key, int value, int switcher, int *collision);
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key, int switcher);
unsigned int FNV1Hash(char *buf);

void hashtab_delete(struct listnode **hashtab, char *key);
