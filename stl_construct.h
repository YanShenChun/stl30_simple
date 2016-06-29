#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

#include <new>

__STL_BEGIN_NAMESPACE

template <class T>
inline void destory(T* pointer) {
  pointer->~T();
}

template <class T1, class T2>
inline void construct(T1* p, const T2& value) {
  new (p) T1(value);
}

__STL_END_NAMESPACE


#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */
