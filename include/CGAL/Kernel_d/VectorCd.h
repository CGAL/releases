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
// file          : include/CGAL/Kernel_d/VectorCd.h
// package       : Kernel_d (0.9.68)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2002/03/18 20:34:02 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_VECTORCD_H
#define CGAL_VECTORCD_H 

#ifndef NOCGALINCL
#include <CGAL/basic.h>
#endif
#include <CGAL/Kernel_d/Tuple_d.h> 

CGAL_BEGIN_NAMESPACE
#define PointCd PointCd2

template <class FT, class LA> class VectorCd;
template <class FT, class LA>
std::istream& operator>>(std::istream&, VectorCd<FT,LA>&);
template <class FT, class LA>
std::ostream& operator<<(std::ostream&, const VectorCd<FT,LA>&);

template <class _FT, class _LA>
class VectorCd : public Handle_for< Tuple_d<_FT,_LA> > { 
  typedef Tuple_d<_FT,_LA>  Tuple;
  typedef Handle_for<Tuple> Base;
  typedef VectorCd<_FT,_LA> Self;

typename _LA::Vector& vector_rep() { return ptr()->v; }
const typename _LA::Vector& vector_rep() const { return ptr()->v; }
_FT& entry(int i) { return ptr()->v[i]; }
const _FT& entry(int i) const { return ptr()->v[i]; }
void invert_rep() { ptr()->invert(); }
VectorCd(const Base& b) : Base(b) {}

public: 

typedef _FT RT;
typedef _FT FT;
typedef _LA LA;
typedef typename Tuple::const_iterator Cartesian_const_iterator;
typedef typename Tuple::Homogeneous_const_iterator Homogeneous_const_iterator;

class Base_vector {};

friend class PointCd<FT,LA>;
friend class DirectionCd<FT,LA>;
friend class HyperplaneCd<FT,LA>; 

VectorCd(int d = 0) : Base( Tuple(d) ) {}
VectorCd(int d, Null_vector) : Base( Tuple(d) ) {}

#ifndef CGAL_SIMPLE_INTERFACE

template <class InputIterator>
VectorCd(int d, InputIterator first, InputIterator last) 
  : Base( Tuple(d,first,last) ) 
{ if ( first == last ) return; 
  // else first specifies common denominator:
  CGAL_assertion_msg(*first!=FT(0),
    "VectorCd::constructor: denominator must be nonzero.");
  for (register int i=0; i<d; ++i) entry(i)/=*first;
}

template <class InputIterator>
VectorCd(int d, InputIterator first, InputIterator last, 
         const FT& D) : Base( Tuple(d,first,last) )
{ CGAL_assertion_msg(D!=FT(0), "VectorCd::constructor: D must be nonzero.");
  for (register int i=0; i<d; ++i) entry(i)/=D;
}

#else
#define FIXVECCD(I) \
VectorCd(int d, I first, I last) : Base( Tuple(d,first,last) ) \
{ if ( first == last ) return; \
  CGAL_assertion_msg(*first!=FT(0), \
    "VectorCd::constructor: denominator must be nonzero."); \
  for (register int i=0; i<d; ++i) entry(i)/=*first; \
} \
VectorCd(int d, I first, I last, const FT& D):Base( Tuple(d,first,last) )\
{ CGAL_assertion_msg(D!=FT(0), "VectorCd::constructor: D must be nonzero.");\
  for (register int i=0; i<d; ++i) entry(i)/=D;\
}

FIXVECCD(int*)
FIXVECCD(const int*)
FIXVECCD(RT*)
FIXVECCD(const RT*)
#undef FIXVECCD
#endif

VectorCd(int d, Base_vector, int i) : Base( Tuple(d) )
{ if ( d == 0 ) return;
  CGAL_assertion_msg((0<=i&&i<d),"VectorCd::base: index out of range.");
  entry(i) = 1;
}

VectorCd(const FT& x, const FT& y, const FT& w = 1) 
  : Base( Tuple(x,y) ) 
{ CGAL_assertion_msg((w!=0), "VectorCd::construction: w == 0.");
  vector_rep()/=w; }

VectorCd(int x, int y, int w = 1) 
  : Base( Tuple((FT)x,(FT)y) ) 
{ CGAL_assertion_msg((w!=0), "VectorCd::construction: w == 0.");
  vector_rep()/=w; }

VectorCd(const FT& x, const FT& y, const FT& z, const FT& w) 
  : Base( Tuple(x,y,z) ) 
{ CGAL_assertion_msg((w!=0), "VectorCd::construction: w == 0.");
  vector_rep()/=w; }

VectorCd(int x, int y, int z, int w) :
  Base( Tuple((FT)x,(FT)y,(FT)z) )
{ CGAL_assertion_msg((w!=0), "VectorCd::construction: w == 0.");
  vector_rep()/=w; }

VectorCd(const VectorCd<FT,LA>& p) : Base(p)  {}
~VectorCd() {}     

int dimension() const { return ptr()->size(); } 

FT cartesian(int i) const 
{ CGAL_assertion_msg((0<=i && i<(dimension())), 
    "VectorCd::cartesian(): index out of range.");
  return entry(i); 
}
FT operator[](int i) const { return cartesian(i); }
FT homogeneous(int i) const 
{ CGAL_assertion_msg((0<=i && i<=(dimension())), 
    "VectorCd::homogeneous(): index out of range.");
  if (i!=dimension()) return entry(i); else return FT(1);
}

FT squared_length() const
{ return vector_rep()*vector_rep(); }

Cartesian_const_iterator cartesian_begin() const 
{ return ptr()->begin(); }
Cartesian_const_iterator cartesian_end() const 
{ return ptr()->end(); }

Homogeneous_const_iterator homogeneous_begin() const 
{ return Homogeneous_const_iterator(ptr()->begin(),ptr()->end()); }
Homogeneous_const_iterator homogeneous_end() const 
{ return Homogeneous_const_iterator(ptr()->beyondend()); }

inline PointCd<FT,LA> to_point() const;

inline DirectionCd<FT,LA> direction() const; 
/*{\Mop returns the direction of |\Mvar|. }*/

VectorCd<FT,LA> transform(const Aff_transformationCd<FT,LA>& t) const; 

VectorCd<FT,LA> scale(const FT& m) const
{ VectorCd<FT,LA> result(*this);
  result.copy_on_write(); 
  result.vector_rep() *= m;
  return result; 
}

void self_scale(const FT& m)
{ copy_on_write();
  vector_rep() *= m;
}

VectorCd<FT,LA>& operator*=(const FT& n) 
{ self_scale(n); return *this; }
VectorCd<FT,LA>& operator*=(int n) 
{ self_scale(n); return *this; }

VectorCd<FT,LA> operator/(int n) const
{ return scale(FT(1)/FT(n)); }
VectorCd<FT,LA> operator/(const FT& n) const
{ return scale(FT(1)/n); }

VectorCd<FT,LA>& operator/=(const FT& n)
{ self_scale(FT(1)/n); return *this; }
VectorCd<FT,LA>& operator/=(int n) 
{ self_scale(FT(1)/FT(n)); return *this; }

FT operator* (const VectorCd<FT,LA>& w) const
{ return vector_rep()*w.vector_rep(); }

VectorCd<FT,LA> operator+(const VectorCd<FT,LA>& w) const 
{ VectorCd<FT,LA> result(w.dimension()); 
  result.ptr()->cartesian_add(ptr(),w.ptr());
  return result; }

VectorCd<FT,LA> operator-(const VectorCd<FT,LA>& w) const 
{ VectorCd<FT,LA> result(w.dimension());
  result.ptr()->cartesian_sub(ptr(),w.ptr());
  return result; }

VectorCd<FT,LA> operator-() const 
{ VectorCd<FT,LA> result(*this);
  result.copy_on_write(); // creates a copied object!
  result.ptr()->invert();
  return result; 
}

VectorCd<FT,LA>& operator+=(const VectorCd<FT,LA>& w) 
{ copy_on_write(); vector_rep() += w.vector_rep(); 
  return *this; }

VectorCd<FT,LA>& operator-=(const VectorCd<FT,LA>& w) 
{ copy_on_write(); vector_rep() -= w.vector_rep(); 
  return *this; }

static Comparison_result cmp(
  const VectorCd<FT,LA>& x, const VectorCd<FT,LA>& y) 
{ Compare_componentwise<FT,LA> cmpobj;
  return cmpobj(x.vector_rep(),y.vector_rep());
}

bool operator==(const VectorCd<FT,LA>& w) const
{ if ( identical(w) ) return true;
  if ( dimension() != w.dimension() ) return false;
  return vector_rep()==w.vector_rep();
}
bool operator!=(const VectorCd<FT,LA>& w) const
{ return !operator==(w); }

bool is_zero() const
{ return vector_rep().is_zero(); }

FT hx() const { return cartesian(0); }
FT hy() const { return cartesian(1); }
FT hz() const { return cartesian(2); }
FT hw() const { return FT(1); }
FT x()  const { return cartesian(0); }
FT y()  const { return cartesian(1); }
FT z()  const { return cartesian(2); }

friend std::istream& operator>> CGAL_NULL_TMPL_ARGS
  (std::istream& I, VectorCd<FT,LA>& v);
friend std::ostream& operator<< CGAL_NULL_TMPL_ARGS
  (std::ostream& O, const VectorCd<FT,LA>& v);

}; // end of class VectorCd

#undef PointCd
CGAL_END_NAMESPACE
#endif // CGAL_VECTORCD_H 
//----------------------- end of file ----------------------------------
