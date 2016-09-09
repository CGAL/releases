// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Hash_map.h
// package       : Hash_map (0.9.7)
// chapter       : Nef Polyhedra
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/06/21 08:56:46 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: Hashing Map by chained hashing
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_HASH_MAP_H
#define CGAL_HASH_MAP_H

#include <CGAL/basic.h>
#include <CGAL/Tools/chained_map.h>

CGAL_BEGIN_NAMESPACE

struct Handle_index {
  template <class H> 
  size_t operator() (const H& h) const
  { return size_t(&*h); } 
};

struct VoidPtr_index {
  size_t operator() (void* p) const
  { return size_t(p); } 
};


/*{\Manpage {Hash_map} {D,E,I} 
{Data Association for uniquely indexed objects}{M}}*/

template <class D, class E, class I=Handle_index>
class Hash_map : private CGALi::chained_map<E> {

/*{\Mdefinition An instance |\Mvar| of the parameterized data type
|\Mname| is an injective mapping from the set of indexed objects of
type |D|, called the domain type of |\Mvar|, to the set of variables
of data type |E|, called the element type of |\Mvar|.

An object |i| of the index data type |I| delivers a unique integer
index |i(d)| for objects $d \in D$.

We use |M(d)| to denote the variable associated to |d|. All variables
are initialized to |default_element|, an element of |E| that is
specified in the definition of |M|. A subset of |D| is designated as
the domain of |M|. Elements are added to |dom(M)| by the array
operator; however, the domain may also contain indices for which the
access operator was never executed.

There's one default index schemes already defined: |Handle_index|.  It
allows to index all handles, iterators and circulators.  Thus
|\Mtype<D,E>| can be used for any handle or iterator type |D| (handles
are static iterators).}*/

  typedef Hash_map<D,E,I>       Self;
  typedef CGALi::chained_map<E> Base;
  I _index;

public:
  /*{\Mtypes 5}*/ 

  typedef typename Base::item item;
  /*{\Mtypemember the item type.}*/

  typedef D domain_type;
  /*{\Mtypemember the domain type.}*/  

  typedef E element_type;
  /*{\Mtypemember the element type.}*/ 

  typedef I index_type;
  /*{\Mtypemember the index type.}*/

  class element_iterator {  
  /*{\Mtypemember a forward iterator over all element entries.}*/
    item it; Self* pM;
  public:
    typedef E             value_type;
    typedef ptrdiff_t     difference_type;
    typedef E*            pointer;
    typedef E&            reference; 
    typedef std::forward_iterator_tag iterator_category;

    element_iterator(item p, Self* pMi) : it(p), pM(pMi) {}
    element_iterator() : it(0), pM(0) {}
    bool  operator==( const element_iterator& i) const 
    { return ( it == i.it); }
    bool  operator!=( const element_iterator& i) const 
    { return !(*this == i); }
    const E& operator*() const { return pM->inf(it); }
    const E* operator->() const { return &(pM->inf(it)); }
    element_iterator& operator++() 
    { it=pM->next_item(it); return *this; }
    element_iterator operator++(int) 
    { element_iterator tmp=*this; ++*this; return tmp; }

    operator item() const { return it; }
  };

protected:
  friend class element_iterator;
 
  item next_item(item it) const
  { return Base::next_item(it); }
  const E& inf(item it) const
  { return Base::inf(it); }
public:

/*{\Mcreation 4}*/

Hash_map() { Base::xdef() = E(); }
/*{\Mcreate creates an injective function $m$ from $D$ to the set of unused
variables of type $E$, sets |default_value| to the default value of type |E|
(if |E| has no default value then |default_value| is set to an unspecified
element of |E|), and initializes $M$ with $m$.}*/

Hash_map(const E& def) { Base::xdef() = def; }
/*{\Mcreate creates an injective function $m$ from $D$ to the set of unused
variables of type $E$, sets |default_value| to |def|, and initializes $M$ with
$m$.}*/

Hash_map(const E& def, int table_sz) : Base(table_sz)
{ Base::xdef() = def; }

Hash_map<D,E,I>& operator=(const Hash_map<D,E,I>& M) 
{ Base::operator=((Base&)M);
  return *this;
}
Hash_map(const Hash_map<D,E,I>& M) : Base((Base&)M) {}
~Hash_map() { clear_entries(); }

/*{\Moperations 2 4.5 }*/

void clear() { Base::clear(); }
/*{\Mop makes |\Mvar| empty.}*/
void clear(const E& def) { Base::clear(); Base::xdef() = def; }
/*{\Mop makes |\Mvar| empty and sets |default_value| to |x|. }*/

bool is_defined(const D& d) const { return Base::lookup(_index(d)) != 0; }
/*{\Mop returns true if $d \in |dom(M)|$.}*/

const E& operator[](const D& d) const
{ item p = Base::lookup(_index(d));
  if ( p != 0 ) return Base::inf(p);
  else return Base::cxdef();
}

E& operator[](const D& d)
/*{\Marrop returns the variable $M(d)$ and adds $d$ to |dom(M)|. If |M|
is a const-object then |M(d)| is read-only and $d$ is not added to 
|dom(M)|.}*/
{ return Base::access(_index(d)); }

element_iterator begin() 
/*{\Mop returns the element iterator pointing to the first element 
stored.}*/
{ return element_iterator(Base::first_item(),this); }

element_iterator end() 
/*{\Mop returns the element iterator pointing beyond the last element 
stored.}*/
{ return element_iterator();}

void statistics() const { Base::statistics(); }

};

/*{\Mimplementation |Hash_maps| are implemented via chained hashing
scheme. Access operations |M[i]| take expected time $O(1)$. 
The design was derived from the LEDA type map. }*/

CGAL_END_NAMESPACE

#endif // CGAL_HASH_MAP_H

