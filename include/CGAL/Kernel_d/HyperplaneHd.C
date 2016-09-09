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
// file          : include/CGAL/Kernel_d/HyperplaneHd.C
// package       : Kernel_d (0.9.68)
// author(s)     : Michael Seel
// coordinator   : Susan Hert
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_HYPERPLANEHD_C
#define CGAL_HYPERPLANEHD_C
CGAL_BEGIN_NAMESPACE

template <class RT, class LA>
VectorHd<RT,LA>  HyperplaneHd<RT,LA>::
orthogonal_vector() const
{ VectorHd<RT,LA> res(*this); 
  res.copy_on_write();
  res.entry(dimension()) = 1; 
  return res; 
}

template <class RT, class LA>
Comparison_result HyperplaneHd<RT,LA>::
weak_cmp(const HyperplaneHd<RT,LA>& h1, 
         const HyperplaneHd<RT,LA>& h2)
{ 
  CGAL_assertion_msg((h1.dimension()==h2.dimension()), 
    "HyperplaneHd::weak_cmp: dimensions disagree.");
  if(h1.identical(h2)) return EQUAL;

  int i, d = h1.dimension();
  for (i = 0; i <= d && 
              h1.coefficient(i) == 0 && 
              h2.coefficient(i) == 0; i++); // no body
  if (h1.coefficient(i) == 0) return SMALLER;
  if (h2.coefficient(i) == 0) return LARGER;
 
  int s = CGAL_NTS sign(h1.coefficient(i)) * 
          CGAL_NTS sign(h2.coefficient(i));
  RT s1 = (RT)s * h2.coefficient(i); 
  RT s2 = (RT)s * h1.coefficient(i);
  // |s1 * h1.coefficient(i)| is 
  // $\Labs{ |h1.coefficient(i)*h2.coefficient(i)| }$

  Comparison_result c;
  while (++i <= d) { 
    c = CGAL_NTS compare(s1 * h1.coefficient(i),
                         s2 * h2.coefficient(i));
    if (c != EQUAL) return c;
  }
  return EQUAL;
}

template <class RT, class LA>
Comparison_result HyperplaneHd<RT,LA>::
strong_cmp(const HyperplaneHd<RT,LA>& h1, 
           const HyperplaneHd<RT,LA>& h2)
{ 
  CGAL_assertion_msg((h1.dimension()==h2.dimension()), 
  "HyperplaneHd::strong_cmp: dimensions disagree.");
  if (h1.identical(h2))  return EQUAL;

  int i;
  int d = h1.dimension();
  for (i = 0; i <=d && 
              h1.coefficient(i)==0 && 
              h2.coefficient(i)==0; i++) ; // no body
  int c1 = CGAL_NTS sign(h1.coefficient(i));
  int c2 = CGAL_NTS sign(h2.coefficient(i));
  if (c1 != c2) return CGAL_NTS compare(c1,c2);
  RT s1 = (RT)CGAL_NTS sign(h2.coefficient(i)) * h2.coefficient(i); 
  RT s2 = (RT)CGAL_NTS sign(h1.coefficient(i)) * h1.coefficient(i);

  Comparison_result c;
  while (++i <= d) { 
    c = CGAL_NTS compare(s1 * h1.coefficient(i), 
                         s2 * h2.coefficient(i));
    if (c != EQUAL) return c;
  }
  return EQUAL;
}

template <class RT, class LA>
std::istream& operator>>(std::istream& I, HyperplaneHd<RT,LA>& h) 
{ h.copy_on_write(); h.ptr()->read(I); return I; }

template <class RT, class LA>
std::ostream& operator<<(std::ostream& O, const HyperplaneHd<RT,LA>& h)
{ h.ptr()->print(O,"HyperplaneHd"); return O; } 

template <class RT, class LA>
inline CGAL::io_Operator io_tag(const HyperplaneHd<RT,LA>&) 
{ return CGAL::io_Operator(); }
 

CGAL_END_NAMESPACE
#endif // CGAL_HYPERPLANEHD_C


