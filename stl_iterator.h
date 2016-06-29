#ifndef __SGI_STL_INTERNAL_ITERATOR_H
#define __SGI_STL_INTERNAL_ITERATOR_H

__STL_BEGIN_NAMESPACE

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_ITERATOR_H */
