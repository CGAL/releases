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
// file          : include/CGAL/Partition.h
// package       : Union_find (0.9.5)
// chapter       : Nef Polyhedra
//
// source        : nef_2d/Partition.lw
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2001/06/21 09:18:09 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: Paritions implemented by union-find with path compression
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_PARTITION_H
#define CGAL_PARTITION_H

#include <CGAL/basic.h>
#include <memory>
#include <cassert>
#define ALLOC(t) std::allocator<t>

#ifdef _MSC_VER
#define CGAL_PARTITION_NO_ALLOCATOR
#endif

CGAL_BEGIN_NAMESPACE

template <typename T, typename A = ALLOC(int) > 
class Partition;

/*{\Manpage {Partition}{T,A}{Parameterized Partitions}{P}}*/

template <typename T, typename A>
class Partition {

/*{\Mdefinition An instance |\Mvar| of the data type |\Mname|
consists of a finite set of items (|partition_item|) and a partition
of this set into blocks. Each item has an associated information of
type |T|.  The type |A| has to be a model of the allocator concept 
as defined in the C++ standard.}*/

class Partition_struct {
  typedef Partition_struct* partition_item;
  friend class Partition<T,A>;
protected:
  T              _inf;
  size_t         _size;
  partition_item _next, _up;
  Partition_struct(partition_item n, const T& x) : 
    _inf(x), _size(1), _next(n), _up(0) {}
};

public:
/*{\Mtypes 5}*/ 
  typedef Partition_struct* partition_item;

  typedef Partition_struct* item;
  /*{\Mtypemember the item type.}*/

#ifndef CGAL_PARTITION_NO_ALLOCATOR
  typedef typename A::template rebind<Partition_struct>::other  
          allocator;
  /*{\Mtypemember the allocator.}*/
#endif

/*{\Mcreation 4}*/

  Partition() : _first(0), _blocks(0) {}
  /*{\Mcreate creates an instance |\Mvar| of type |\Mname| and initializes 
     it to the empty partition.}*/

  ~Partition() { clear(); }

/*{\Moperations 3 2}*/

  void clear();
  /*{\Mopl makes |\Mvar| the empty partition.}*/


  partition_item make_block(const T& x);
  /*{\Mop returns a new |partition_item| |it|, adds
     the block |{it}| to partition |\Mvar|, and associates |x| with |it|.}*/


  partition_item find(partition_item p) const;
  /*{\Mop returns a canonical item of the block that
     contains item $p$, i.e., iff |P.same_block(p,q)| 
     then |P.find(p)| and |P.find(q)| return the same item.\\
     \precond $p$ is an item in |\Mvar|. }*/

  size_t size(partition_item p) const
  { return find(p)->_size; }
  /*{\Mop returns the size of the block containing $p$.}*/

  size_t number_of_blocks() const
  { return _blocks; }
  /*{\Mop returns the number of blocks of |\Mvar|.}*/

  bool same_block(partition_item p, partition_item q) const
  { return find(p)==find(q); }
  /*{\Mop returns true if $p$ and $q$ belong to the same
     block of partition |\Mvar|.\\
     \precond $p$ and $q$ are items in |\Mvar|.}*/

  void union_blocks(partition_item p, partition_item q);
  /*{\Mop unites the blocks of partition |\Mvar| containing
  items $p$ and $q$.\\
  \precond $p$ and $q$ are items in |\Mvar|.}*/

  const T& inf(partition_item p) const
  { return p->_inf; }
  /*{\Mop returns the information associated with |it|.}*/

  void change_inf(partition_item p, const T& x)
  { p->_inf = x; }
  /*{\Mop changes the information associates with |it| to |x|.}*/
  
protected:
  partition_item _first;
  size_t         _blocks;
#ifndef CGAL_PARTITION_NO_ALLOCATOR
  static allocator _a;
#endif
};

#ifndef CGAL_PARTITION_NO_ALLOCATOR
template <typename T, typename A>
typename Partition<T,A>::allocator Partition<T,A>::_a;
#endif

template <typename T, typename A>
typename Partition<T,A>::partition_item 
Partition<T,A>::make_block(const T& x) 
{ partition_item tmp = _first;
#ifndef CGAL_PARTITION_NO_ALLOCATOR
  _first = _a.allocate(1);
  new ((void*)_first) Partition_struct(tmp,x);
#else
  _first = new Partition_struct(tmp,x);
#endif
  _blocks++;
  return _first;
}

template <typename T, typename A>
void Partition<T,A>::clear()
{ while (_first) { 
     partition_item n = _first->_next;
#ifndef CGAL_PARTITION_NO_ALLOCATOR
     _a.destroy(_first);
     _a.deallocate(_first,1);
#else
     delete _first;
#endif
     _first = n;
  }
  _blocks = 0;
}


template <typename T, typename A>
typename Partition<T,A>::partition_item 
Partition<T,A>::find(partition_item p) const
{ assert(p);
  partition_item r(p);
  while (r->_up) { r = r->_up; }
  // now root is r;
  while (p->_up) 
  { partition_item u = p->_up; p->_up=r; p=u; }
  return r;
}

template <typename T, typename A>
void
Partition<T,A>::union_blocks(partition_item p, partition_item q)
{ assert(p&&q);
  partition_item pit = find(p);
  partition_item qit = find(q);
  if (pit == qit) return;
  size_t sp = pit->_size, sq = qit->_size;
  if (sp > sq) std::swap(p,q);
  // now sp <= sq
  pit->_up = qit;  // linking roots
  qit->_size += pit->_size; // updating size
  _blocks++;
}

CGAL_END_NAMESPACE

#endif // CGAL_PARTITION_H

