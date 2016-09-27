#ifndef __SGI_STL_INTERNAL_RELOPS
#define __SGI_STL_INTERNAL_RELOPS

__STL_BEGIN_RELOPS_NAMESPACE

template <class T>
inline bool operator!=(const T& x, const T& y) {
  return !(x == y);
}

template <class T>
inline bool operator>(const T& x, const T& y) {
  return y < x;
}

template <class T>
inline bool operator<=(const T& x, const T& y) {
  return !(y < x);
}

template <class T>
inline bool operator>=(const T& x, const T& y) {
  return !(x < y);
}

__STL_END_RELOPS_NAMESPACE

#endif /* __SGI_STL_INTERNAL_RELOPS */
