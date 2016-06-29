#ifndef __SGI_STL_INTERNAL_LIST_H
#define __SGI_STL_INTERNAL_LIST_H

__STL_BEGIN_NAMESPACE

template <class T>
struct __list_node {
  typedef void* void_pointer;
  void_pointer next;
  void_pointer prev;
  T data;
};

template <class T, class Ref, class Ptr>
struct __list_iterator {
  typedef __list_iterator<T, T&, T*>             iterator;
  typedef __list_iterator<T, Ref, Ptr>           self;

  typedef bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef Ptr pointer;
  typedef Ref reference;
  typedef __list_node<T>* link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  link_type node;

  __list_iterator(link_type x) : node(x) {}
  __list_iterator() {}
  __list_iterator(const iterator& x) : node(x.node) {}

  bool operator==(const self& x) const { return node == x.node; }
  bool operator!=(const self& x) const { return node != x.node; }
  reference operator*() const { return (*node).data;}
  pointer operator->() const { return &(operator*()); }

  self& operator++() {
    node = (link_type)((*node).next);
    return *this;
  }

  self operator++(int) {
    self tmp = *this;
    ++*this;
    return tmp;
  }

  self& operator--() {
    node = (link_type)((*node).prev);
    return *this;
  }

  self& operator--(int) {
    self tmp = *this;
    --*this;
    return tmp;
  }
};

template <class T, class Alloc = alloc>
class list {
protected:
  typedef void* void_pointer;
  typedef __list_node<T> list_node;
  typedef simple_alloc<list_node, Alloc> list_node_allocator;

public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef list_node* link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef __list_iterator<T, T&, T*>             iterator;
  typedef __list_iterator<T, const T&, const T*> const_iterator;

protected:
  link_type get_node() { return list_node_allocator::allocate(); }
  void put_node(link_type p) { list_node_allocator::deallocate(p); }

  link_type create_node(const T& x) {
    link_type p = get_node();
    __STL_TRY {
      construct(&p->data, x);
    }
    __STL_UNWIND(put_node(p));
    return p;
  }

  void destory_node(link_type p) {
    destory(&p->data);
    put_node(p);
  }

protected:
  void empty_initialize() {
    node = get_node();
    node->next = node;
    node->prev = node;
  }

  void fill_initialize(size_type n, const T& value) {
    empty_initialize();
    __STL_TRY {
      insert(begin(), n, value);
    }
    __STL_UNWIND(clear(); put_node(node));
  }

protected:
  link_type node;

public:
  list() { empty_initialize(); }

  iterator begin() { return (link_type)((*node).next); }
  iterator end() { return node; }

  bool empty() const { return node->next == node; }

  iterator insert(iterator position, const T& x) {
    link_type tmp = create_node(x);
    tmp->next = position.node;
    tmp->prev = position.node->prev;
    (link_type(position.node->prev))->next = tmp;
    position.node->prev = tmp;
    return tmp;
  }

  void push_front(const T& x) { insert(begin(), x); }
  void push_back(const T& x) { insert(end(), x); }

  iterator erase(iterator position) {
    link_type next_node = link_type(position.node->next);
    link_type prev_node = link_type(position.node->prev);
    prev_node->next = next_node;
    next_node->prev = prev_node;
    destory_node(position.node);
    return iterator(next_node);
  }

  void pop_front() { erase(begin()); }
  void pop_back() {
    iterator tmp = end();
    erase(--tmp);
  }

  void clear();
};

template <class T, class Alloc>
void list<T, Alloc>::clear() {
  link_type cur = (link_type)node->next;
  while (cur != node) {
    link_type tmp = cur;
    cur = (link_type)cur->next;
    destory_node(tmp);
  }

  node->next = node;
  node->prev = node;
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_LIST_H  */
