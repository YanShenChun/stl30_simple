#ifndef __SGI_STL_INTERNAL_UNINITIALIZE_H
#define __SGI_STL_INTERNAL_UNINITIALIZE_H

__STL_BEGIN_NAMESPACE

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
__uninitialize_copy_aux(InputIterator first, InputIterator last,
                        ForwardIterator result,
                        __true_type) {
  return copy(first, last, result);
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
__uninitialize_copy_aux(InputIterator first, InputIterator last,
                        ForwardIterator result,
                        __false_type) {
  ForwardIterator cur = result;
  __STL_TRY {
    for (; first != last; ++first, ++cur)
      construct(&*cur, *first);
    return cur;
  }
  __STL_UNWIND(destory(result, cur));
}

template <class InputIterator, class ForwardIterator, class T>
inline ForwardIterator
__uninitialize_copy(InputIterator first, InputIterator last,
                    ForwardIterator result, T*) {
  typedef typename __type_traits<T>::is_POD_type is_POD;
  return __uninitialize_copy_aux(first, last, result, is_POD());
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
uninitialized_copy(InputIterator first, InputIterator last,
                   ForwardIterator result) {
  return __uninitialize_copy(first, last, result, value_type(result));
}

inline char* uninitialized_copy(const char* first, const char* last,
                                char* result) {
  memmove(result, first, last - first);
  return result + (last - first);
}

inline wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last,
                                   wchar_t* result) {
  memmove(result, first, sizeof(wchar_t) * (last - first));
  return result + (last - first);
}


template <class ForwardIterator, class Size, class T>
ForwardIterator
__uninitialized_fill_n_aux(ForwardIterator first, Size n,
                           const T& x, __true_type) {
  return fill_n(first, n, x);
}

template <class ForwardIterator, class Size, class T>
ForwardIterator
__uninitialized_fill_n_aux(ForwardIterator first, Size n,
                           const T& x, __false_type) {
  ForwardIterator cur = first;
  __STL_TRY {
    for (; n > 0; --n, ++cur)
      construct(&*cur, x);
    return cur;
  }
  __STL_UNWIND();
}

template <class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n,
                                              const T& x, T1*) {
  typedef typename __type_traits<T1>::is_POD_type is_POD;
  return __uninitialized_fill_n_aux(first, n, x, is_POD());
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n,
                                              const T& x) {
  return __uninitialized_fill_n(first, n, x, value_type(first));
}


__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_UNINITIALIZE_H */
