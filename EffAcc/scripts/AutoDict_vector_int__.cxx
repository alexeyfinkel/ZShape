#include "vector"
#ifdef __CINT__ 
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;
#pragma link C++ class vector<int*>+;
#pragma link C++ class vector<int*>::*;
#ifdef G__VECTOR_HAS_CLASS_ITERATOR
#pragma link C++ operators vector<int*>::iterator;
#pragma link C++ operators vector<int*>::const_iterator;
#pragma link C++ operators vector<int*>::reverse_iterator;
#endif
#endif
