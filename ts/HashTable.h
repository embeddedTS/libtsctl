#ifndef __HASHTABLE_H
#define __HASHTABLE_H
#include "Array.h"

struct HashTable;
typedef struct HashTable HashTable;

int HashTableEqual(HashTable *a,HashTable *b);
HashTable *HashTableNew(unsigned int minsize,
                 unsigned int (*hashfunction) (void*),
                 int (*key_eq_fn) (void*,void*));

int HashTableInsert(HashTable *h, void *k, void *v);
void *HashTableLookup(HashTable *h, void *k);
void *HashTableReplace(HashTable *h, void *k, void *v);
void *HashTableRemove(HashTable *h, void *k);
unsigned int HashTableCount(HashTable *h);
void HashTableDestroy(HashTable *h, int free_values);

typedef unsigned int  (*hFcn)(void *);
typedef int (*eFcn)(void *,void *);

int ASCIIZEqual(char *str1,char *str2);
unsigned int ASCIIZHash(unsigned char *str);

unsigned int ArrayHash(void *arr1);
int ArrayEqualQ(void *a,void *b);

unsigned int IntegerHash(void *i);
int IntegerEqualQ(void *a,void *b);

__attribute__((always_inline)) 
static inline HashTable *HashTableNewASCIIZ() {
  return HashTableNew(16,(hFcn)ASCIIZHash,(eFcn)ASCIIZEqual);
}

__attribute__((always_inline)) 
static inline HashTable *HashTableNewArrKey() {
  return HashTableNew(16,(hFcn)ArrayHash,(eFcn)ArrayEqualQ);
}

__attribute__((always_inline)) 
static inline HashTable *HashTableNewInteger() {
  return HashTableNew(16,(hFcn)IntegerHash,(eFcn)IntegerEqualQ);
}
#endif 
/*
 * Copyright (c) 2002, Christopher Clark
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * * Neither the name of the original author; nor the names of any contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
