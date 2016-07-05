#ifndef __SGI_STL_INTERNAL_ALGOBASE_H
#define __SGI_STL_INTERNAL_ALGOBASE_H

#ifndef __STL_CONFIG_H
#include <stl_config.h>
#endif

#ifndef __SGI_STL_INTERNAL_RELOPS
#include <stl_relops.h>
#endif

#ifndef __SGI_STL_INTERNAL_PAIR_H
#include <stl_pair.h>
#endif

#ifndef __TYPE_TRAITS_H
#include <type_traits.h>
#endif

#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stddef.h>
#include <new>
#include <iostream>

#ifndef __SGI_STL_INTERNAL_ITERATOR_H
#include <stl_iterator.h>
#endif

__STL_BEGIN_NAMESPACE

template <class ForwardIterator1, class ForwardIterator2, class T>
inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*) {
  T tmp = *a;
  *a = *b;
  *b = tmp;
}

template <class ForwardIterator1, class ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
  __iter_swap(a, b, value_type(a));
}

template <class T>
inline void swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

#undef min
#undef max

template <class T>
inline const T& min(const T& a, const T& b) {
  return b < a ? b : a;
}

template <class T>
inline const T& max(const T& a, const T& b) {
  return a < b? b : a;
}

template <class T, class Compare>
inline const T& min(const T& a, const T& b, Compare comp) {
  return comp(b, a) ? b : a;
}

template <class T, class Compare>
inline const T& max(const T& a, const T& b, Compare comp) {
  return comp(a, b) ? b : a;
}

template <class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last,
                             OutputIterator result, input_iterator_tag) {
  for (; first != last; ++result, ++ first)
    *result = *first;

  return result;
}

template <class RandomAccessIterator, class OutputIterator, class Distance>
inline OutputIterator
__copy_d(RandomAccessIterator first, RandomAccessIterator last,
         OutputIterator result, Distance*) {
  for (Distance n = last - first; n > 0; --n, ++result, ++first)
    *result = *first;

  return result;
}

template <class RandomAccessIterator, class OutputIterator>
inline OutputIterator
__copy(RandomAccessIterator first, RandomAccessIterator last,
       OutputIterator result, random_access_iterator_tag) {
  return __copy_d(first, last, result, distance_type(first));
}

template <class InputIterator, class OutputIterator>
struct __copy_dispatch {
  OutputIterator operator()(InputIterator first, InputIterator last,
                            OutputIterator result) {
    return __copy(first, last, result, iterator_category(first));
  }
};

template <class T>
inline T* __copy_t(const T* first, const T* last, T* result, __true_type) {
  memmove(result, first, sizeof(T) * (last - first));
  return result + (last - first);
}

template <class T>
inline T* __copy_t(const T* first, const T* last, T* result, __false_type) {
  return __copy_d(first, last, result, (ptrdiff_t*)0);
}

template <class T>
struct __copy_dispatch<T*, T*> {
  T* operator()(T* first, T* last, T* result) {
    typedef typename __type_traits<T>::has_trival_assignment_operator t;
    return __copy_t(first, last, result, t());
  }
};

template <class T>
struct __copy_dispatch<const T*, T*> {
  T* operator()(const T* first, const T* last, T* result) {
    typedef typename __type_traits<T>::has_trival_assignment_operator t;
    return __copy_t(first, last, result, t());
  }
};


template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last,
                           OutputIterator result) {
  return __copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
}

template <class BidirectionalIterator1, class BidirectionalIterator2>
inline BidirectionalIterator2 __copy_backward(BidirectionalIterator1 first,
                                              BidirectionalIterator1 last,
                                              BidirectionalIterator2 result) {
  while (first != last) *--result = *--last;
  return result;
}

template <class BidirectionalIterator1, class BidirectionalIterator2>
struct __copy_backward_dispatch {
  BidirectionalIterator2 operator()(BidirectionalIterator1 first,
                                    BidirectionalIterator1 last,
                                    BidirectionalIterator2 result) {
    return __copy_backward(first, last, result);
  }
};

template <class T>
inline T* __copy_backward_t(const T* first, const T* last, T* result,
                            __true_type) {
  const ptrdiff_t N = last - first;
  memmove(result - N, first, sizeof(T) * N);
  return result - N;
}

template <class T>
inline T* __copy_backward_t(const T* first, const T* last, T* result,
                            __false_type) {
  return __copy_backward(first, last, result);
}

template <class T>
struct __copy_backward_dispatch<T*, T*> {
  T* operator()(T* first, T* last, T* result) {
    typedef typename __type_traits<T>::has_trival_assignment_operator t;
    return __copy_backward_t(first, last, result, t());
  }
};

template <class T>
struct __copy_backward_dispatch<const T*, T*> {
  T* operator()(const T* first, const T* last, T* result) {
    typedef typename __type_traits<T>::has_trival_assignment_operator t;
    return __copy_backward_t(first, last, result, t());
  }
};

template <class BidirectionalIterator1, class BidirectionalIterator2>
inline BidirectionalIterator2 copy_backward(BidirectionalIterator1 first,
                                            BidirectionalIterator1 last,
                                            BidirectionalIterator2 result) {
  return __copy_backward_dispatch<BidirectionalIterator1,
                                  BidirectionalIterator2>()(first, last, result);
}

template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
  for (; n > 0; --n, ++first)
    *first = value;

  return first;
}


__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_ALGOBASE_H */
