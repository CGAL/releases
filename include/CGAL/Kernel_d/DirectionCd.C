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
// file          : include/CGAL/Kernel_d/DirectionCd.C
// package       : Kernel_d (0.9.68)
// author(s)     : Michael Seel
// coordinator   : Susan Hert
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_DIRECTIONCD_C
#define CGAL_DIRECTIONCD_C
CGAL_BEGIN_NAMESPACE

template <class FT, class LA> 
DirectionCd<FT,LA>::DirectionCd(const VectorCd<FT,LA>& v) : Base(v) {}

template <class FT, class LA>
VectorCd<FT,LA> DirectionCd<FT,LA>::vector() const
{ return VectorCd<FT,LA>(*this); }

template <class FT, class LA>
DirectionCd<FT,LA>  DirectionCd<FT,LA>::
transform(const Aff_transformationCd<FT,LA>& t) const
{ return vector().transform(t).direction(); }

template <class FT, class LA>
Comparison_result DirectionCd<FT,LA>::
cmp(const DirectionCd<FT,LA>& h1, 
    const DirectionCd<FT,LA>& h2) 
{ 
  if (h1.identical(h2)) return EQUAL; 
  int i, d = h1.dimension(); 
  for (i = 0; i < d && h1.delta(i)==FT(0) && 
                       h2.delta(i)==FT(0); ++i) ; // no body
  int c1 = CGAL_NTS sign(h1.delta(i));
  int c2 = CGAL_NTS sign(h2.delta(i));
  if (c1 != c2) return CGAL_NTS compare(c1,c2);
 
  FT s1 = (FT) CGAL_NTS sign(h2.delta(i)) * h2.delta(i); 
  FT s2 = (FT) CGAL_NTS sign(h1.delta(i)) * h1.delta(i); 

  i++;
  Comparison_result c; 
  while (i < d) { 
    c = CGAL_NTS compare(s1 * h1.delta(i), s2 * h2.delta(i));
    if (c != EQUAL) return c;
    i++;
  }
  return EQUAL;
}

template <class FT, class LA>
std::istream& operator>>(std::istream& I, DirectionCd<FT,LA>& dir)
{ dir.copy_on_write(); dir.ptr()->read(I);
  return I; 
} 

template <class FT, class LA>
std::ostream& operator<<(std::ostream& O, const DirectionCd<FT,LA>& dir)
{ dir.ptr()->print(O,"DirectionCd"); return O; } 

template <class FT, class LA>
inline CGAL::io_Operator io_tag(const DirectionCd<FT,LA>&) 
{ return CGAL::io_Operator(); }

CGAL_END_NAMESPACE
#endif // CGAL_DIRECTIONCD_C
//----------------------- end of file ----------------------------------


