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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Kernel_d/Ray_d.h
// package       : Kernel_d (0.9.68)
// revision      : $Revision: 1.10 $
// revision_date : $Date: 2002/03/18 20:34:00 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_RAY_D_H
#define CGAL_RAY_D_H

#include <CGAL/Kernel_d/Pair_d.h>
#include <CGAL/Kernel_d/Segment_d.h> 
#include <CGAL/Kernel_d/Line_d.h>

CGAL_BEGIN_NAMESPACE

template <class R>
std::istream& operator>>(std::istream&, Ray_d<R>&);
template <class R>
std::ostream& operator<<(std::ostream&, const Ray_d<R>&);


/*{\Manpage {Ray_d}{R}{Rays in d-space}{r}}*/

template <class p_R>
class Ray_d : public Handle_for< Pair_d<p_R> > { 
  typedef Pair_d<p_R>       Pair;
  typedef Handle_for<Pair>  Base;
  typedef Ray_d<p_R>        Self;

/*{\Mdefinition
An instance of data type |Ray_d| is a ray in $d$-dimensional
Euclidian space. It starts in a point called the source of |\Mvar| and
it goes to infinity.}*/

public: 
/*{\Mtypes 4}*/
typedef p_R R;
/*{\Mtypemember the representation type.}*/
typedef typename p_R::RT RT;
/*{\Mtypemember the ring type.}*/
typedef typename p_R::FT FT;
/*{\Mtypemember the field type.}*/
typedef typename p_R::LA LA;
/*{\Mtypemember the linear algebra layer.}*/

typedef typename Vector_d<R>::Base_vector Base_vector;

friend class Line_d<R>; 
friend class Segment_d<R>; 

private:
Ray_d(const Base& b) : Base(b) {}
public: 
/*{\Mcreation 3}*/

Ray_d() : Base( Pair() ) {}
/*{\Mcreate introduces some ray in $d$-dimensional space }*/
 
Ray_d(const Point_d<R>& p, const Point_d<R>& q)
/*{\Mcreate introduces a ray through |p| and |q| and starting at |p|.
\precond $p$ and $q$ are distinct and have the same dimension. }*/
 : Base( Pair(p,q) )
{ CGAL_assertion_msg(!ptr()->is_degenerate(), 
    "Ray_d::constructor: the two points must be different." );
  CGAL_assertion_msg((p.dimension()==q.dimension()), 
    "Ray_d::constructor: the two points must have the same dimension." );
}

Ray_d(const Point_d<R>& p, const Direction_d<R>& dir)
/*{\Mcreate introduces a ray starting in |p| with direction |dir|.
\precond |p| and |dir| have the same dimension and |dir| is not
trivial.}*/
  : Base( Pair(p,p+dir.vector()) )
{ CGAL_assertion_msg((p.dimension()==dir.dimension()), 
    "Ray_d::constructor: the p and dir must have the same dimension." );
  CGAL_assertion_msg(!dir.is_degenerate(), 
    "Ray_d::constructor: dir must be non-degenerate." );
}

Ray_d(const Segment_d<R>& s) 
/*{\Mcreate introduces a ray through |s.source()| and |s.target()| and 
starting at |s.source()|. \precond $s$ is not trivial. }*/
  : Base( s ) 
{ CGAL_assertion_msg(!s.is_degenerate(), 
    "Ray_d::constructor: segment is trivial.");
}

Ray_d(const Ray_d<R>& r) : Base(r) {}

/*{\Moperations 3 3}*/

int dimension() const { return (ptr()->_p[0].dimension()); }
/*{\Mop returns the dimension of the underlying space.}*/

Point_d<R> source() const { return (ptr()->_p[0]); }
/*{\Mop returns the source point of |\Mvar|. }*/

Point_d<R> point(int i) const 
/*{\Mop returns a point on |\Mvar|. |point(0)| is the source.
|point(i)|, with $i>0$, is different from the source. \precond $i
\geq 0$.}*/ 
{ return (ptr()->_p[i%2]); }

Direction_d<R> direction() const 
/*{\Mop returns the direction of |\Mvar|. }*/
{ return ptr()->direction(); }

inline Line_d<R> supporting_line() const; 
/*{\Mop returns the supporting line of |\Mvar|.}*/

Ray_d<R> opposite() const
/*{\Mop returns the ray with direction opposite to |\Mvar|
and starting in |source|.}*/
{ return Ray_d<R>(source(),-direction()); }

Ray_d<R> transform(const Aff_transformation_d<R>& t) const
/*{\Mop returns $t(l)$. }*/
{ return Ray_d<R>(point(0).transform(t),point(1).transform(t)); }

Ray_d<R> operator+(const Vector_d<R>& v) const
/*{\Mbinop returns |\Mvar+v|, i.e., |\Mvar| translated by vector $v$.}*/ 
{ return Ray_d<R>(point(0)+v, point(1)+v); }

bool has_on(const Point_d<R>& p) const 
/*{\Mop A point is on |r|, iff it is equal to the source of |r|, or if it is
in the interior of |r|.}*/
{ typename R::Position_on_line_d pos; FT l;
  if (pos(p,point(0),point(1),l)) return (FT(0)<=l);
  return false;
}

/*{\Mtext \headerline{Non-Member Functions}}*/

bool operator==(const Ray_d<R>& r1) const
{ if ( identical(r1) ) return true;
  if ( dimension() != r1.dimension() ) return false;
  return source() == r1.source() && 
         direction() == r1.direction(); 
}

bool operator!=(const Ray_d<R>& r1)
{ return !operator==(r1); }

friend std::istream& operator>> CGAL_NULL_TMPL_ARGS 
(std::istream&, Ray_d<R>&);
friend std::ostream& operator<< CGAL_NULL_TMPL_ARGS 
(std::ostream&, const Ray_d<R>&); 

}; // end of class

template <class R>
bool parallel(const Ray_d<R>& r1, const Ray_d<R>& r2)
/*{\Mfunc returns true if the unoriented supporting lines of |r1| and |r2|
are parallel and false otherwise. }*/
{ return (r1.direction() == r2.direction()) || 
         (r1.direction() == -(r2.direction())); 
} 

template <class R>
std::istream& operator>>(std::istream& I, Ray_d<R>& r) 
{ r.copy_on_write(); r.ptr()->read(I); 
  CGAL_assertion_msg(r.point(0)!=r.point(1),
    "Line_d::operator>>: trivial ray.");
  CGAL_assertion_msg(r.point(0).dimension()==r.point(1).dimension(),
  "Ray_d::operator>>: dimensions disagree.");
  return I; 
}

template <class R>
std::ostream& operator<<(std::ostream& O, const Ray_d<R>& r)
{ r.ptr()->print(O,"Ray_d"); return O; }

template <class R>
inline CGAL::io_Operator io_tag(const Ray_d<R>&) 
{ return CGAL::io_Operator(); }


/*{\Mimplementation 
Rays are implemented by a pair of points as an item type.  All
operations like creation, initialization, tests, direction
calculation, input and output on a ray $r$ take time
$O(|r.dimension()|)$. |dimension()|, coordinate and point access, and
identity test take constant time. The space requirement is
$O(|r.dimension()|)$.}*/


CGAL_END_NAMESPACE
#endif // CGAL_RAYHD_H
//----------------------- end of file ----------------------------------

