// ======================================================================
//
// Copyright (c) 2000,2001 The CGAL Consortium

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
// file          : include/CGAL/Kernel_d/DirectionHd.h
// package       : Kernel_d (0.9.47)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/06/28 09:32:17 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_DIRECTIONHD_H
#define CGAL_DIRECTIONHD_H

#ifndef NOCGALINCL
#include <CGAL/basic.h>
#include <CGAL/Quotient.h>
#endif
#include <CGAL/Kernel_d/Tuple_d.h> 
#include <CGAL/Kernel_d/PointHd.h>
#include <CGAL/Kernel_d/VectorHd.h>
#include <CGAL/Kernel_d/Aff_transformationHd.h>

CGAL_BEGIN_NAMESPACE

template <class RT, class LA> class DirectionHd;
template <class RT, class LA>
std::istream& operator>>(std::istream&, DirectionHd<RT,LA>&);
template <class RT, class LA>
std::ostream& operator<<(std::ostream&, const DirectionHd<RT,LA>&);

/*{\Manpage{Direction_d}{R}{Directions in d-space}{dir}}*/
/*{\Msubst 
Hd<RT,LA>#_d<R>
VectorHd#Vector_d
DirectionHd#Direction_d
Quotient<RT>#FT
}*/

template <class _RT, class _LA>
class DirectionHd : public Handle_for< Tuple_d<_RT,_LA> > { 
  typedef Tuple_d<_RT,_LA> Tuple;
  typedef Handle_for<Tuple> Base;
  typedef DirectionHd<_RT,_LA> Self;

/*{\Mdefinition 
A |DirectionHd| is a vector in the $d$-dimensional vector space
where we forget about its length. We represent directions in
$d$-dimensional space as a tuple $(h_0,\ldots,h_d)$ of variables of
type |RT| which we call the homogeneous coordinates of the
direction. The coordinate $h_d$ must be positive.  The Cartesian
coordinates of a direction are $c_i = h_i/h_d$ for $0 \le i < d$,
which are of type |Quotient<RT>|.  Two directions are equal if their
Cartesian coordinates are positive multiples of each other. Directions
are in one-to-one correspondence to points on the unit sphere.}*/

const typename _LA::Vector& vector_rep() const { return ptr->v; }
_RT& entry(int i) const { return ptr->v[i]; }
void invert_rep() { ptr->invert(); }

public: 
/*{\Mtypes 4}*/

typedef _RT RT;
/*{\Mtypemember the ring type.}*/
typedef Quotient<_RT> FT;
/*{\Mtypemember the field type.}*/
typedef _LA LA;
/*{\Mtypemember the linear algebra layer.}*/
typedef typename Tuple::const_iterator Delta_const_iterator;
/*{\Mtypemember a read-only iterator for the deltas of |\Mvar|.}*/

class Base_direction {};
/*{\Mtypemember construction tag.}*/

friend class VectorHd<RT,LA>; 

/*{\Mcreation 4}*/

DirectionHd(int d = 0) : Base( Tuple(d+1) )  
/*{\Mcreate introduces a variable |\Mvar| of type |DirectionHd<RT,LA>| 
initialized to some direction in $d$-dimensional space.}*/
{ if (d>0) entry(d) = 1; }

DirectionHd(const VectorHd<RT,LA>& v);
/*{\Mcreate introduces a variable |\Mvar| of type |DirectionHd<RT,LA>| 
initialized to the direction of |v|.}*/

#ifndef CGAL_SIMPLE_INTERFACE

template <class InputIterator>
DirectionHd(int d, InputIterator first, InputIterator last) : 
  Base( Tuple(d+1,first,last,1) ) {}
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| in dimension |d|
with representation tuple |set [first,last)|. \precond |d| is
nonnegative, |[first,last)| has |d| elements and the value type of 
|InputIterator| is |RT|.}*/

#else
#define FIXDIRHD(I) \
DirectionHd(int d, I first, I last) : Base( Tuple(d+1,first,last,1) ) {}
FIXDIRHD(int*)
FIXDIRHD(const int*)
FIXDIRHD(RT*)
FIXDIRHD(const RT*)
#undef FIXDIRHD
#endif

DirectionHd(int d, Base_direction, int i) : Base( Tuple(d+1) )
/*{\Mcreate returns a variable |\Mvar| of type |\Mname| initialized  
to the direction of the $i$-th base vector of dimension $d$.
\precond $0 \leq i < d$.}*/
{ entry(d) = 1; 
  if ( d==0 ) return;
  CGAL_assertion_msg((0<=i&&i<d), "DirectionHd::base: index out of range.");
  entry(i) = 1;
}

DirectionHd(const RT& x, const RT& y) : Base( Tuple(x,y,1) ) {}
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| in 
$2$-dimensional space. }*/

DirectionHd(int a, int b) : 
  Base( Tuple(RT(a),RT(b),RT(1)) ) {}

DirectionHd(const RT& x, const RT& y, const RT& z) : 
  Base( Tuple(x,y,z,1) ) {}
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| in 
$3$-dimensional space. }*/

DirectionHd(int a, int b, int c) : 
  Base( Tuple(RT(a),RT(b),RT(c),RT(1)) ) {}

DirectionHd(const DirectionHd<RT,LA>& p) : Base(p)  {}
~DirectionHd() {}     

/*{\Moperations 5 3}*/

int dimension() const { return ptr->size()-1; }
/*{\Mop returns the dimension of |\Mvar|. }*/ 

RT delta(int i) const  

/*{\Mop returns the $i$-th component of |\Mvar|. 
   \precond $0 \leq i < d$.}*/
{ CGAL_assertion_msg((0<=i && i<(dimension())), "DirectionHd::delta():\
  index out of range.");
  return entry(i);
}

RT D() { return entry(dimension()); }

RT operator[](int i) const  
/*{\Marrop returns the $i$-th delta of |\Mvar|. 
\precond $0 \leq i < d$.}*/
{ return delta(i); }

Delta_const_iterator deltas_begin() const { return ptr->begin(); }
/*{\Mop  returns an iterator pointing to the first delta of |\Mvar|. }*/
Delta_const_iterator deltas_end() const { return ptr->last(); }
/*{\Mop  returns an iterator pointing beyond the last delta of |\Mvar|. }*/

VectorHd<RT,LA> vector() const; 
/*{\Mop returns a vector pointing in direction |\Mvar|. }*/

bool  is_degenerate() const 
/*{\Mop returns true iff |\Mvar.vector()| is the zero vector.}*/
{ for (int i=0; i<dimension(); ++i) 
   if ( delta(i) != RT(0) ) return false;
  return true; }

DirectionHd<RT,LA> transform(const Aff_transformationHd<RT,LA>& t) const; 
/*{\Mop returns $t(p)$. }*/
DirectionHd<RT,LA>  opposite() const
/*{\Mop returns the direction opposite to |\Mvar|. }*/
{ DirectionHd<RT,LA> result(*this); // creates a copied object!
  result.copy_on_write(); // creates a copied object!
  result.ptr->invert(dimension()); 
  return result; 
}

DirectionHd<RT,LA>  operator- () const
/*{\Munop returns the direction opposite to |\Mvar|.}*/
{ return opposite(); }

static Comparison_result cmp(
  const DirectionHd<RT,LA>& h1, const DirectionHd<RT,LA>& h2); 
bool operator==(const DirectionHd<RT,LA>& w) const
{ if ( identical(w) ) return true;
  if ( dimension()!=w.dimension() ) return false;
  return (DirectionHd<RT,LA>::cmp(*this,w) == EQUAL); 
}

bool operator!=(const DirectionHd<RT,LA>& w) const
{ return !operator==(w); }

/*{\Mtext \headerline{Downward compatibility}
We provide all operations of the lower dimensional interface |dx()|,
|dy()|, |dz()|.}*/
RT dx() const { return delta(0); }
RT dy() const { return delta(1); }
RT dz() const { return delta(2); }

friend std::istream& operator>> CGAL_NULL_TMPL_ARGS
  (std::istream& I, DirectionHd<RT,LA>& d);
friend std::ostream& operator<< CGAL_NULL_TMPL_ARGS
  (std::ostream& O, const DirectionHd<RT,LA>& d);

}; // end of class DirectionHd


/*{\Mimplementation 
Directions are implemented by arrays of integers as an item type.  All
operations like creation, initialization, tests, inversion, input and
output on a direction $d$ take time $O(|d.dimension()|)$. |dimension()|,
coordinate access and conversion take constant time.  The space
requirement is $O(|d.dimension()|)$.  }*/



CGAL_END_NAMESPACE
#endif // CGAL_DIRECTIONHD_H
//----------------------- end of file ----------------------------------

