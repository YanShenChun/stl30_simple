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

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_UNINITIALIZE_H */
