// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// file          : include/CGAL/Kernel_d/DirectionHd.C
// package       : Kernel_d (0.9.47)
// author(s)     : Michael Seel
// coordinator   : Susan Hert
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_DIRECTIONHD_C
#define CGAL_DIRECTIONHD_C
CGAL_BEGIN_NAMESPACE

template <class RT, class LA> 
DirectionHd<RT,LA>::DirectionHd(const VectorHd<RT,LA>& v) : Base(v) {}

template <class RT, class LA>
VectorHd<RT,LA>  DirectionHd<RT,LA>::vector() const
{ return VectorHd<RT,LA>(*this); }

template <class RT, class LA>
DirectionHd<RT,LA>  DirectionHd<RT,LA>::
transform(const Aff_transformationHd<RT,LA>& t) const
{ return vector().transform(t).direction(); }

template <class RT, class LA>
Comparison_result DirectionHd<RT,LA>::
cmp(const DirectionHd<RT,LA>& h1, 
    const DirectionHd<RT,LA>& h2) 
{ 
  if (h1.identical(h2)) return EQUAL; 
  int i, d = h1.dimension(); 
  for (i = 0; i < d && h1.delta(i)==0 && 
              h2.delta(i)==0; i++) ; // no body
  int c1 = CGAL_NTS sign(h1.delta(i)); 
  int c2 = CGAL_NTS sign(h2.delta(i)); 
  if (c1 != c2) return CGAL_NTS compare(c1,c2); 
 
  RT s1 = (RT) CGAL_NTS sign(h2.delta(i)) * h2.delta(i); 
  RT s2 = (RT) CGAL_NTS sign(h1.delta(i)) * h1.delta(i); 

  i++; 
  Comparison_result c; 
  while (i < d) { 
    c = CGAL_NTS compare(s1 * h1.delta(i), s2 * h2.delta(i)); 
    if (c != EQUAL) return c;
    i++; 
  }
  return EQUAL; 
}

template <class RT, class LA>
std::istream& operator>>(std::istream& I, DirectionHd<RT,LA>& dir)
{ dir.copy_on_write(); dir.ptr->read(I); 
  CGAL_assertion_msg((dir.D()>=0), 
  "operator>>: denominator of direction must be nonnegative."); 
  return I; 
} 

template <class RT, class LA>
std::ostream& operator<<(std::ostream& O, const DirectionHd<RT,LA>& dir)
{ dir.ptr->print(O,"DirectionHd"); return O; } 

template <class RT, class LA>
inline CGAL::io_Operator io_tag(const DirectionHd<RT,LA>&) 
{ return CGAL::io_Operator(); }


//----------------------- end of file ----------------------------------


CGAL_END_NAMESPACE
#endif // CGAL_DIRECTIONHD_C


