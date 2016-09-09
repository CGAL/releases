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
// file          : include/CGAL/Kernel_d/Segment_d.h
// package       : Kernel_d (0.9.68)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2002/03/18 20:34:01 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_SEGMENT_D_H
#define CGAL_SEGMENT_D_H 

#include <CGAL/Kernel_d/Pair_d.h> 
#include <CGAL/Kernel_d/Line_d.h> 
#include <CGAL/Kernel_d/Ray_d.h>

CGAL_BEGIN_NAMESPACE

template <class R> std::istream& operator>>
  (std::istream&, Segment_d<R>&);
template <class R> std::ostream& operator<<
  (std::ostream&, const Segment_d<R>&);


/*{\Manpage {Segment_d}{R}{Segments in d-space}{s}}*/

template <class p_R>
class Segment_d : public Handle_for< Pair_d<p_R> > { 
  typedef Pair_d<p_R>      Pair;
  typedef Handle_for<Pair> Base;
  typedef Segment_d<p_R>   Self;

/*{\Mdefinition 
An instance $s$ of the data type |Segment_d| is a directed straight
line segment in $d$-dimensional Euclidian space connecting two points
$p$ and $q$. $p$ is called the source point and $q$ is called
the target point of $s$, both points are called endpoints of $s$. A
segment whose endpoints are equal is called \emph{degenerate}.}*/
public: 
/*{\Mtypes 5}*/
typedef p_R R;
/*{\Mtypemember the representation type.}*/
typedef typename p_R::RT RT;
/*{\Mtypemember the ring type.}*/
typedef typename p_R::FT FT;
/*{\Mtypemember the field type.}*/
typedef typename p_R::LA LA;
/*{\Mtypemember the linear algebra layer.}*/

friend class Line_d<R>; 
friend class Ray_d<R>; 

private:
Segment_d(const Base& b) : Base(b) {}
public: 
/*{\Mcreation 3}*/

Segment_d() : Base( Pair() ) {}
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname|.}*/

Segment_d(const Point_d<R>& p, const Point_d<R>& q) 
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| which
is initialized to the segment $(p,q)$. }*/
 : Base( Pair(p,q) ) {}

Segment_d(const Point_d<R>& p, const Vector_d<R>& v)
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| which 
is initialized to the segment |(p,p+v)|. }*/
 : Base( Pair(p,p+v) ) {}

Segment_d(const Segment_d<R>& s) : Base(s) {}     

/*{\Moperations 3 3}*/

int dimension() const { return (ptr()->_p[0].dimension()); }
/*{\Mop returns the dimension of the underlying space. }*/

Point_d<R>  source() const { return ptr()->_p[0]; }
/*{\Mop    returns the source point of segment |\Mvar|. }*/ 

Point_d<R>  target() const { return ptr()->_p[1]; } 
/*{\Mop    returns the target point of segment |\Mvar|. }*/ 

// defined for historical reasons
Point_d<R>  vertex(int i) const 
/*{\Mop returns source or target of |\Mvar|: |vertex(0)| returns the
source, |vertex(1)| returns the target. The parameter $i$ is taken
modulo $2$, which gives easy access to the other vertex.
\precond $i \geq 0$.}*/
{ CGAL_assertion(i>=0); return ptr()->_p[i%2]; }

Point_d<R>  point(int i) const { return vertex(i); }
/*{\Mop returns |vertex(i)|.}*/ 

Point_d<R>  operator[](int i) const { return vertex(i); }
/*{\Marrop returns |vertex(i)|.}*/

Point_d<R> min() const 
/*{\Mop returns the lexicographically smaller vertex.}*/
{ typename R::Compare_lexicographically_d cmp; 
  if (cmp(source(),target()) == CGAL::SMALLER) return source();
  else return target();
}

Point_d<R> max() const 
/*{\Mop returns the lexicographically larger vertex.}*/
{ typename R::Compare_lexicographically_d cmp; 
  if (cmp(source(),target()) == SMALLER) return target();
  else return source();
}

Segment_d<R> opposite() const 
/*{\Mop returns the segment |(target(),source())|.}*/
{ return Segment_d<R>(target(),source()); }


Direction_d<R> direction() const
/*{\Mop returns the direction from source to target.\\
\precond |\Mvar| is non-degenerate. }*/
{ CGAL_assertion_msg((!is_degenerate()), 
  "Segment_d::direction(): degenerate segment cannot be converted.");
  return ptr()->direction(); 
}

Vector_d<R> vector() const
/*{\Mop returns the vector from source to target.}*/
{ return ptr()->vector(); }

FT squared_length() const
/*{\Mop returns the square of the length of |\Mvar|.}*/
{ return (target()-source()).squared_length(); } 

bool has_on(const Point_d<R>& p) const 
/*{\Mop returns true if $p$ lies on |\Mvar| and false otherwise. }*/
{ if (is_degenerate()) return (source() == p);
  typename R::Position_on_line_d pos; FT l;
  if ( pos(p,source(),target(),l) ) return (FT(0)<=l && l<=FT(1));
  return false;
}

inline Line_d<R> supporting_line() const;
/*{\Mop returns the supporting line of |\Mvar|.
\precond |\Mvar| is non-degenerate. }*/ 

Segment_d<R>   
transform(const Aff_transformation_d<R>& t) const
/*{\Mop returns $t(s)$.}*/ 
{ return Segment_d<R>(source().transform(t),
                      target().transform(t)); }

Segment_d<R> operator+(const Vector_d<R>& v) const
/*{\Mbinop returns $s+v$, i.e., |\Mvar| translated by vector $v$.}*/ 
{ return Segment_d<R>(source()+v,target()+v); }

bool is_degenerate() const 
/*{\Mop returns true if |\Mvar| is degenerate i.e. 
|\Mvar.source()=\Mvar.target()|. }*/
{ return ptr()->is_degenerate(); } 

bool operator==(const Segment_d<R>& t) const
{ if (identical(t)) return true;
  return ((source() == t.source() && 
           target() == t.target())); } 

bool operator!=(const Segment_d<R>& t) const 
{ return !operator==(t); }

friend std::istream& operator>> CGAL_NULL_TMPL_ARGS 
(std::istream&, Segment_d<R>&);
friend std::ostream& operator<< CGAL_NULL_TMPL_ARGS 
(std::ostream&, const Segment_d<R>&);

};  // end of class

/*{\Mtext \headerline{Non-Member Functions} }*/

template <class R>
bool weak_equality(const Segment_d<R>& s, const Segment_d<R>& t)
/*{\Mfunc Test for equality as unoriented segments.}*/
{ return (s==t || s==t.opposite()); } 

template <class R>
bool parallel(const Segment_d<R>& s1, const Segment_d<R>& s2)
/*{\Mfunc return true if one of the segments is trivial or
if the unoriented supporting lines are parallel. }*/
{ return s1.is_degenerate() || s2.is_degenerate() ||
         s1.direction() == s2.direction() || 
         s1.direction() == -s2.direction(); } 

template <class R>
bool common_endpoint(const Segment_d<R>& s1, const Segment_d<R>& s2,
  Point_d<R>& common) 
/*{\Mfunc if |s1| and |s2| touch in a common end point, this point
is assigned to |common| and the result is |true|, otherwise the 
result is |false|. }*/
{ if (s1.source() == s2.source()) { common = s1.source(); return true; }
  if (s1.source() == s2.target()) { common = s1.source(); return true; }
  if (s1.target() == s2.source()) { common = s1.target(); return true; }
  if (s1.target() == s2.target()) { common = s1.target(); return true; }
  return false; 
}

template <class R> 
std::istream& operator>>(std::istream& I, Segment_d<R>& s)
{ s.copy_on_write(); s.ptr()->read(I); 
  CGAL_assertion_msg(s.source().dimension()==s.target().dimension(),
  "Segment_d::operator>>: dimensions disagree.");
  return I; 
}

template <class R> 
std::ostream& operator<<(std::ostream& O, const Segment_d<R>& s)
{ s.ptr()->print(O,"Segment_d"); return O; }

template <class R>
inline CGAL::io_Operator io_tag(const Segment_d<R>&) 
{ return CGAL::io_Operator(); }


/*{\Mimplementation 
Segments are implemented by a pair of points as an item type.  All
operations like creation, initialization, tests, the calculation of
the direction and source - target vector, input and output on a
segment $s$ take time $O(|s.dimension()|)$. |dimension()|, coordinate
and end point access, and identity test take constant time.  The
operations for intersection calculation also take time
$O(|s.dimension()|)$. The space requirement is $O(|s.dimension()|)$.
}*/


CGAL_END_NAMESPACE
#endif // CGAL_SEGMENT_D_H
//----------------------- end of file ----------------------------------

