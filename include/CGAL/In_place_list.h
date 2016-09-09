// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/In_place_list.h
// package       : STL_Extension (1.17)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.12 $
// revision_date : $Date: 1998/10/08 14:35:33 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// A doubly linked list managing items in place.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IN_PLACE_LIST_H
#define CGAL_IN_PLACE_LIST_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#ifndef CGAL_PROTECT_STDDEF_H
#include <stddef.h>
#define CGAL_PROTECT_STDDEF_H
#endif // CGAL_PROTECT_STDDEF_H

#ifndef CGAL_PROTECT_ITERATOR_H
#include <iterator.h>
#define CGAL_PROTECT_ITERATOR_H
#endif // CGAL_PROTECT_ITERATOR_H

#ifndef CGAL_PROTECT_FUNCTION_H
#include <function.h>
#define CGAL_PROTECT_FUNCTION_H
#endif // CGAL_PROTECT_FUNCTION_H

#ifndef CGAL_PROTECT_ALGOBASE_H
#include <algobase.h>
#define CGAL_PROTECT_ALGOBASE_H
#endif // CGAL_PROTECT_ALGOBASE_H

#ifndef CGAL_CIRCULATOR_IMPL_H
#include <CGAL/circulator_impl.h>
#endif

#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

// Define shorter names to please linker (g++/egcs)
#define CGAL__In_place_list_iterator             CGAL__Ipli
#define CGAL__In_place_list_const_iterator       CGAL__Iplci

// Forward declarations
template <class T> class CGAL__In_place_list_iterator;
template <class T> class CGAL__In_place_list_const_iterator;
template <class T, bool managed> class CGAL_In_place_list;

template < class T >
class CGAL_In_place_sl_list_base {
public:
    T* next_link;        // forward pointer
};

template < class T >
class CGAL_In_place_list_base {
public:
    T* next_link;        // forward pointer
    T* prev_link;        // backwards pointer
    friend  class CGAL__In_place_list_iterator<T>;
    friend  class CGAL__In_place_list_const_iterator<T>;
    friend  class CGAL_In_place_list<T,false>;
    friend  class CGAL_In_place_list<T,true>;
};
template <class T>
class CGAL__In_place_list_iterator {
// protected:  // Made public for g++ 2.8 and egcs 2.90. They don't
               // accept the friend declarations below.
public:
    T* node;
public:
    // friend  class CGAL_In_place_list<T,false>;
    // friend  class CGAL_In_place_list<T,true>;

    typedef CGAL__In_place_list_iterator<T> Self;
    typedef CGAL_In_place_list_base<T>      Base;

    typedef T          value_type;
    typedef T*         pointer;
    typedef const T*   const_pointer;
    typedef T&         reference;
    typedef const T&   const_reference;
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
    typedef bidirectional_iterator_tag   iterator_category;

    CGAL__In_place_list_iterator() : node(0) {}
    CGAL__In_place_list_iterator(T* x) : node(x) {}

    bool  operator==( const Self& x) const { return node == x.node; }
    bool  operator!=( const Self& x) const { return node != x.node; }
    T&    operator*()  const { return *node; }
    T*    operator->() const { return  node; }
    Self& operator++() {
        node = ((Base*)(node))->next_link;
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        node = ((Base*)(node))->prev_link;
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
};

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class T>
inline  bidirectional_iterator_tag
iterator_category( const  CGAL__In_place_list_iterator<T>&) {
    return bidirectional_iterator_tag();
}
template < class T>
inline  T*
value_type( const  CGAL__In_place_list_iterator<T>&) {
    return (T*)(0);
}
template < class T>
inline  ptrdiff_t*
distance_type( const  CGAL__In_place_list_iterator<T>&) {
    return (ptrdiff_t*)(0);
}
template < class T>
inline  CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
    const CGAL__In_place_list_iterator<T>&) {
    return CGAL_Iterator_tag();
}
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //


template <class T>
class CGAL__In_place_list_const_iterator {
// protected:  // Made public for g++ 2.8 and egcs 2.90. They don't
               // accept the friend declarations below.
public:
    const T* node;  // It's not Ptr. Otherwise traversal won't work.
public:
    // friend  class CGAL_In_place_list<T,false>;
    // friend  class CGAL_In_place_list<T,true>;

    typedef CGAL__In_place_list_const_iterator<T> Self;
    typedef CGAL__In_place_list_iterator<T>       Iterator;
    typedef CGAL_In_place_list_base<T>            Base;

    typedef T          value_type;
    typedef T*         pointer;
    typedef const T*   const_pointer;
    typedef T&         reference;
    typedef const T&   const_reference;
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
    typedef bidirectional_iterator_tag   iterator_category;

    CGAL__In_place_list_const_iterator() : node(0) {}
    CGAL__In_place_list_const_iterator( Iterator i) : node(&*i) {}
    CGAL__In_place_list_const_iterator(const T* x) : node(x) {}

    bool     operator==( const Self& x) const { return node == x.node; }
    bool     operator!=( const Self& x) const { return node != x.node; }
    const T& operator*()  const { return *node; }
    const T* operator->() const { return  node; }
    Self& operator++() {
        node = ((const Base*)(node))->next_link;
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        node = ((const Base*)(node))->prev_link;
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
};

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class T>
inline  bidirectional_iterator_tag
iterator_category( const  CGAL__In_place_list_const_iterator<T>&) {
    return bidirectional_iterator_tag();
}
template < class T>
inline  T*
value_type( const  CGAL__In_place_list_const_iterator<T>&) {
    return (T*)(0);
}
template < class T>
inline  ptrdiff_t*
distance_type( const  CGAL__In_place_list_const_iterator<T>&) {
    return (ptrdiff_t*)(0);
}
template < class T>
inline  CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
    const  CGAL__In_place_list_const_iterator<T>&) {
    return CGAL_Iterator_tag();
}
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //



template <class T, bool managed>
class CGAL_In_place_list {
protected:
    T*      node;
    size_t  length;

    T*   get_node()           { return new T;}
    T*   get_node(const T& t) { return new T(t);}
    void put_node(T* p)       { delete p;}

//
// Bidirectional List Managing Objects in Place
// --------------------------------------------
//
// DEFINITION An object of the class CGAL_In_place_list<T,bool> is a
// sequence that supports bidirectional iterators and allows constant time
// insert and erase operations anywhere within the sequence. The
// functionality is similar to the `list<T>' in the STL.
//
// The CGAL_In_place_list<T,bool> manages element items in place. Two
// pointers `T*' are expected in the class. For example the base class
// `CGAL_In_place_list_base<T>' can be used.
//
// The CGAL_In_place_list<T,bool> does not copy element items during
// insertion (unless otherwise stated for a function). On removal or
// destruction of the list the element items are not deleted by default.
// The second template parameter `bool' has to be set to `false' in this
// case. If the CGAL_In_place_list<T,bool> should take the responsibility
// for the stored objects the `bool' parameter could be set to `true', in
// which case the list will delete removed items and will delete all
// remaining items on destruction. In any case, the `destroy()' member
// function deletes all elements.
//
// On purpose, these two possible versions of CGAL_In_place_list<T,bool>
// are not assignment compatible to avoid confusions between the different
// storage responsibilities.
//
// PARAMETERS
//
// The full classname is `CGAL_In_place_list<T,bool managed = false, T*
// T::*next = &T::next_link, T* T::*prev = &T::prev_link>'. As long as no
// default template arguments are supported, only
// CGAL_In_place_list<T,bool> is provided.
//
// TYPES

public:
    typedef T          value_type;
    typedef T*         pointer;
    typedef const T*   const_pointer;
    typedef T&         reference;
    typedef const T&   const_reference;
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;

    typedef CGAL__In_place_list_iterator<T>        iterator;
    typedef CGAL__In_place_list_const_iterator<T>  const_iterator;

    typedef reverse_bidirectional_iterator<
        iterator,
        value_type,
        reference,
        difference_type
    > reverse_iterator;
    typedef reverse_bidirectional_iterator<
        const_iterator,
        value_type,
        const_reference,
        difference_type
    > const_reverse_iterator;

    typedef CGAL_In_place_list<T,managed>  Self;

// CREATION
//
// New creation variable is: `l'

    CGAL_In_place_list() : length(0) {
        // introduces an empty list.
        node = get_node();
        (*node).next_link = node;
        (*node).prev_link = node;
    }
    void swap(Self& x) {
        ::swap(node, x.node);
        ::swap(length, x.length);
    }

// ACCESS MEMBER FUNCTIONS

    iterator       begin() { return (*node).next_link; }
    const_iterator begin() const { return (*node).next_link; }
    iterator       end() { return node; }
    const_iterator end() const { return node; }

    reverse_iterator       rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }
    reverse_iterator       rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    bool            empty() const    { return length == 0; }
    size_type       size() const     { return length; }
    size_type       max_size() const { return size_type(-1); }

    reference       front()          { return *begin(); }
    const_reference front() const    { return *begin(); }
    reference       back()           { return *(--end()); }
    const_reference back() const     { return *(--end()); }

// INSERTION

    iterator insert(iterator position, T& x) {
        // inserts `t' in front of iterator `pos'. The return value points
        // to the inserted item.
        x.next_link = position.node;
        x.prev_link = (*position.node).prev_link;
        (*((*position.node).prev_link)).next_link = &x;
        (*position.node).prev_link = &x;
        ++length;
        return &x;
    }
    iterator insert(T* pos, T& x) {
        return insert( iterator(pos), x);
    }
    void push_front(T& x) { insert(begin(), x); }
        // inserts an item in front of list `l'.

    void push_back(T& x)  { insert(end(), x); }
        // inserts an item at the back of list `l'.

    void insert(iterator position, size_type n, const T& x = T());
        // inserts n copies of `t' in front of iterator `pos'.
    void insert( T* pos, size_type n, const T& x = T()) {
        insert( iterator(pos), n, x);
    }

    void insert(iterator pos, const_iterator first, const_iterator last);

    // template <class InputIterator>
    // void insert(iterator pos, InputIterator first, InputIterator last);
        // inserts the range [`first, last') in front of iterator `pos'.

    // non-member-template version.
    void insert(iterator position, const T* first, const T* last);

    // template <class InputIterator>
    // void insert(T* pos, InputIterator first, InputIterator last);
        // inserts the range [`first, last') in front of iterator `pos'.

    // non-member-template version.
    void insert(T* position, const T* first, const T* last);

// REMOVAL

    void erase(iterator i) {
        // removes the item from list `l', where `pos' refers to.
        CGAL_assertion( length > 0);
        (*((*i.node).prev_link)).next_link = (*i.node).next_link;
        (*((*i.node).next_link)).prev_link = (*i.node).prev_link;
        if (managed)
            put_node(i.node);
        --length;
    }
    void erase(T* pos)  { erase( iterator( pos)); }

    void pop_front() { erase(begin()); }
        // removes the first item from list `l'.

    void pop_back() {
        // removes the last item from list `l'.
        iterator tmp = end();
        erase(--tmp);
    }

    void erase(iterator first, iterator last);
        // removes the items in the range [`first, last') from list `l'.

    void erase(T* first, T* last) {
        erase( iterator(first), iterator(last));
    }

// CREATION (Continued)

    CGAL_In_place_list(size_type n, const T& value = T()) : length(0) {
        // introduces a list with n items, all initialized with copies of
        // value.
        node = get_node();
        (*node).next_link = node;
        (*node).prev_link = node;
        insert(begin(), n, value);
    }
    CGAL_In_place_list(const T* first, const T* last) : length(0) {
        // a list with copies from the range [`first,last').
        node = get_node();
        (*node).next_link = node;
        (*node).prev_link = node;
        insert(begin(), first, last);
    }
    CGAL_In_place_list(const Self& x) : length(0) {
        // copy constructor. Each item in `l1' is copied.
        node = get_node();
        (*node).next_link = node;
        (*node).prev_link = node;
        insert(begin(), x.begin(), x.end());
    }
    ~CGAL_In_place_list() {
        erase(begin(), end());
        put_node(node);
    }

    Self&
    operator=(const Self& x);

    void destroy();

// COMPARISON OPERATIONS

#ifndef CGAL_CFG_NO_LAZY_INSTANTIATION
// Not supported for Polyhedrons --> not supported with Gnu g++.
    bool operator==( const Self& y) const {
        return size() == y.size() && equal(begin(), end(), y.begin());
    }

    bool operator!=( const Self& y) const {
        return size() != y.size() || ! equal(begin(), end(), y.begin());
    }

    bool operator<(const Self& y) const {
        return lexicographical_compare(begin(),end(),y.begin(),y.end());
    }
    bool operator>( const Self& i) const {
        return i < *this;
    }
    bool operator<=( const Self& i) const {
        return !(i < *this);
    }
    bool operator>=( const Self& i) const {
        return !(*this < i);
    }
#endif // CGAL_CFG_NO_LAZY_INSTANTIATION //

// SPECIAL LIST OPERATIONS

protected:
    void transfer(iterator position, iterator first, iterator last) {
        // move the range [`first, last') before the position.
        (*((*last.node).prev_link)).next_link = position.node;
        (*((*first.node).prev_link)).next_link = last.node;
        (*((*position.node).prev_link)).next_link = first.node;
        T* tmp = (*position.node).prev_link;
        (*position.node).prev_link = (*last.node).prev_link;
        (*last.node).prev_link = (*first.node).prev_link;
        (*first.node).prev_link = tmp;
    }

public:
    void splice(iterator position, Self& x) {
        // inserts the list x before position `pos' and x becomes empty.
        // It takes constant time. Precondition: `&l != &x'.
        if (!x.empty()) {
            transfer(position, x.begin(), x.end());
            length += x.length;
            x.length = 0;
        }
    }
    void splice(T* position, Self& x) {
        splice( iterator(position), x);
    }
    void splice(iterator position,
                Self& x,
                iterator i) {
        // inserts an element pointed to by i from list x before position
        // `pos' and removes the element from x. It takes constant time. i
        // is a valid dereferenceable iterator of x. The result is
        // unchanged if `pos == i' or `pos == ++i'.
        iterator j = i;
        if (position == i || position == ++j) return;
        transfer(position, i, j);
        ++length;
        --x.length;
    }
    void splice(T* position, Self& x, T* i) {
        splice( iterator(position), x, iterator(i));
    }
    void splice(iterator position,
                Self& x,
                iterator first,
                iterator last) {
        // inserts elements in the range [`first, last') before position
        // `pos' and removes the elements from x. It takes constant time
        // if `&x == $l'; otherwise, it takes linear time. [`first,
        // last') is a valid range in x. Precondition: `pos' is not in the
        // range [`first, last').
        if (first != last) {
            if (&x != this) {
                difference_type n = 0;
                distance(first, last, n);
                x.length -= n;
                length += n;
            }
            transfer(position, first, last);
        }
    }
    void splice(T* p, Self& x, T* first, T* last) {
        splice( iterator(p), x, iterator(first), iterator(last));
    }

    void remove(const T& value);
        // erases all elements e in the list l for which `e == value'.
        // It is stable. Precondition: a suitable `operator==' for the
        // type T.

    void reverse();
        // reverses the order of the elements in `l' in linear time.

#ifndef CGAL_CFG_NO_LAZY_INSTANTIATION
// Not supported for Polyhedrons --> not supported with Gnu g++.
    void unique();
        // erases all but the first element from every consecutive group
        // of equal elements in the list `l'. Precondition: a suitable
        // `operator==' for the type T.

    void merge(Self& x);
        // merges the list x into the list `l' and x becomes empty. It is
        // stable. Precondition: Both lists are increasingly sorted. A
        // suitable `operator<' for the type T.

    void sort();
        // sorts the list `l' according to the `operator<' in time O(n
        // log n) where `n = size()'. It is stable. Precondition: a
        // suitable `operator<' for the type T.
#endif // CGAL_CFG_NO_LAZY_INSTANTIATION //
};

template <class T, bool managed>
void CGAL_In_place_list<T,managed>::
insert(CGAL__In_place_list_iterator<T> position,
       const T* first, const T* last) {
    while (first != last)
        insert(position, *get_node(*first++));
}

template <class T, bool managed>
void CGAL_In_place_list<T,managed>::
insert(CGAL__In_place_list_iterator<T> position,
       CGAL__In_place_list_const_iterator<T> first,
       CGAL__In_place_list_const_iterator<T> last) {
    while (first != last)
        insert(position, *get_node(*first++));
}

template <class T, bool managed>
void CGAL_In_place_list<T,managed>::
insert(CGAL__In_place_list_iterator<T> position,
       size_t n, const T& x) {
    while (n--)
        insert(position, *get_node(x));
}

template <class T, bool managed>
void CGAL_In_place_list<T,managed>::
erase( CGAL__In_place_list_iterator<T> first,
       CGAL__In_place_list_iterator<T> last) {
    while (first != last)
        erase(first++);
}

template <class T, bool managed>
CGAL_In_place_list<T,managed>&
CGAL_In_place_list<T,managed>::
operator=(const CGAL_In_place_list<T,managed>& x) {
    if (this != &x) {
        iterator first1 = begin();
        iterator last1  = end();
        const_iterator first2 = x.begin();
        const_iterator last2  = x.end();
        while (first1 != last1 && first2 != last2) {
            // Save the pointer values before assignment.
            // Assignment avoids unneccassary delete's and new's.
            T* tmp1 = (*first1).next_link;
            T* tmp2 = (*first1).prev_link;
            *first1 = *first2++;
            (*first1).next_link = tmp1;
            (*first1).prev_link = tmp2;
            ++first1;
        }
        if (first2 == last2)
            erase(first1, last1);
        else
            insert(last1, first2, last2);
    }
    return *this;
}

template <class T, bool managed>
void CGAL_In_place_list<T,managed>::
destroy() {
    iterator first = begin();
    iterator last  = end();
    while( first != last) {
        iterator i = first++;
        put_node(i.node);
    }
    length = 0;
    (*node).next_link = node;
    (*node).prev_link = node;
}

template <class T, bool managed>
void CGAL_In_place_list<T,managed>::remove(const T& value) {
    iterator first = begin();
    iterator last = end();
    while (first != last) {
        iterator next = first;
        ++next;
        if (*first == value) erase(first);
        first = next;
    }
}

template <class T, bool managed>
void CGAL_In_place_list<T,managed>::reverse() {
    if (size() < 2) return;
    for (iterator first = ++begin(); first != end();) {
        iterator old = first++;
        transfer(begin(), old, first);
    }
}

#ifndef CGAL_CFG_NO_LAZY_INSTANTIATION
// Not supported for Polyhedrons --> not supported with Gnu g++.

template <class T, bool managed>
void CGAL_In_place_list<T,managed>::unique() {
    iterator first = begin();
    iterator last = end();
    if (first == last) return;
    iterator next = first;
    while (++next != last) {
        if (*first == *next)
            erase(next);
        else
            first = next;
        next = first;
    }
}

template <class T, bool managed>
void CGAL_In_place_list<T,managed>::merge(CGAL_In_place_list<T,managed>& x) {
    iterator first1 = begin();
    iterator last1 = end();
    iterator first2 = x.begin();
    iterator last2 = x.end();
    while (first1 != last1 && first2 != last2)
        if (*first2 < *first1) {
            iterator next = first2;
            transfer(first1, first2, ++next);
            first2 = next;
        } else
            ++first1;
    if (first2 != last2) transfer(last1, first2, last2);
    length += x.length;
    x.length= 0;
}

template <class T, bool managed>
void CGAL_In_place_list<T,managed>::sort() {
    if (size() < 2) return;
    CGAL_In_place_list<T,managed> carry;
    CGAL_In_place_list<T,managed> counter[64];
    int fill = 0;
    while (!empty()) {
        carry.splice(carry.begin(), *this, begin());
        int i = 0;
        while(i < fill && !counter[i].empty()) {
            counter[i].merge(carry);
            carry.swap(counter[i++]);
        }
        carry.swap(counter[i]);
        if (i == fill) ++fill;
    }

    for (int i = 1; i < fill; ++i) counter[i].merge(counter[i-1]);
    swap(counter[fill-1]);
}
#endif // CGAL_CFG_NO_LAZY_INSTANTIATION //


// Undef shorter names (g++/egcs)
#undef CGAL__In_place_list_iterator
#undef CGAL__In_place_list_const_iterator
#endif // CGAL_IN_PLACE_LIST_H //
// EOF //
