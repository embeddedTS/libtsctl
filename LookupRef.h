#ifndef __LookupRef_h
#define __LookupRef_h
// A lookup reference table contains an array of names sorted by name.
// Each name is associated with an array of offsets

typedef struct LookupRef LookupRef;
struct LookupRef {
  char* name;
  int* offset;
};

// return a new lookup reference table
// this table always remains in order sorted by name
LookupRef* LookupRefNew();

// destroy old lookupref
void LookupRefOld(LookupRef* lu);

// if the lookupref array doesn't already have an entry containing
// the specified name, then add it
// return a pointer to the entry
LookupRef *LookupRefName(LookupRef* *lu,char* name);
#endif
