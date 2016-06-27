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

template <class ForwardIterator>
inline void
__destory_aux(ForwardIterator first, ForwardIterator last, __false_type) {
  for (; first < last; ++first) {
    destory(&*first);
  }
}

template <class ForwardIterator>
inline void __destory_aux(ForwardIterator, ForwardIterator, __true_type) {}

template <class ForwardIterator, class T>
inline void __destory(ForwardIterator first, ForwardIterator last, T*) {
  typedef typename __type_traits<T>::has_trivial_destructor trival_destructor;
  __destory_aux(first, last, trival_destructor());
}

template <class ForwardIterator>
inline void destory(ForwardIterator first, ForwardIterator last) {
  __destory(first, last, value_type(first));
}

inline void destory(char*, char*) {}
inline void destory(wchar_t*, wchar_t*) {}

__STL_END_NAMESPACE


#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */
