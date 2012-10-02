#ifndef __Iterator_HashTable_
#define __Iterator_HashTable_
#include "HashTable.h"
#include "HashTable_private.h" /* needed to enable inlining */

typedef struct IteratorHashTable IteratorHashTable;
struct IteratorHashTable
{
    HashTable *h;
    struct entry *e;
    struct entry *parent;
    unsigned int index;
};


/*****************************************************************************/
/* IteratorHashTable
 */

IteratorHashTable *IteratorHashTableNew(HashTable *h);

/*****************************************************************************/
/* IteratorHashTableKey
 * - return the key of the (key,value) pair at the current position */

extern inline void *IteratorHashTableKey(IteratorHashTable *i) { return i->e->k; }

/*****************************************************************************/
/* Value - return the value of the (key,value) pair at the current position */

extern inline void * IteratorHashTableValue(IteratorHashTable *i) {
    return i->e->v;
}

/*****************************************************************************/
/* Next - advance the iterator to the next element
 *           returns zero if advanced to end of table */

int IteratorHashTableNext(IteratorHashTable *itr);

/*****************************************************************************/
/* Delete - remove current element and advance the iterator to the next element
 *          NB: if you need the value to free it, read it before
 *          removing. ie: beware memory leaks!
 *          returns zero if advanced to end of table */

int IteratorHashTableDelete(IteratorHashTable *itr);

/*****************************************************************************/
/* Lookup - overwrite the supplied iterator, to point to the entry
 *          matching the supplied key.
            h points to the hashtable to be searched.
 *          returns zero if not found. */
int IteratorHashTableLookup(IteratorHashTable *itr,HashTable *h, void *k);
void IteratorHashTableFini(IteratorHashTable *itr);

#endif
/*
 * Copyright (c) 2002, 2004, Christopher Clark
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
