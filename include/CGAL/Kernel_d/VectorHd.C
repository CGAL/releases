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
// file          : include/CGAL/Kernel_d/VectorHd.C
// package       : Kernel_d (0.9.47)
// author(s)     : Michael Seel
// coordinator   : Susan Hert
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_VECTORHD_C
#define CGAL_VECTORHD_C
CGAL_BEGIN_NAMESPACE

template <class RT,class LA>
PointHd<RT,LA> VectorHd<RT,LA>::to_point() const
{ return PointHd<RT,LA>(Base(*this)); }

template <class RT,class LA>
PointHd<RT,LA> 
operator+ (const Origin&, const VectorHd<RT,LA>& v)
{ return v.to_point(); }

template <class RT, class LA>
DirectionHd<RT,LA>  VectorHd<RT,LA>::
direction() const
{ CGAL_assertion_msg(!is_zero(), "VectorHd::direction: \
  zero vector cannot be a direction."); 
  return DirectionHd<RT,LA>(*this); 
}

template <class RT, class LA>
VectorHd<RT,LA> VectorHd<RT,LA>::
transform(const Aff_transformationHd<RT,LA>& t) const
{ typename LA::Matrix m_at = t.matrix(); 
  int d = t.dimension(); 
  for (int i = 0; i < d; i++) m_at(i,d) = 0;
  typename LA::Vector res(m_at*vector_rep());
  return VectorHd<RT,LA>(dimension(),res.begin(),res.end()); 
}

template <class RT, class LA>
std::istream& operator>>(std::istream& I, VectorHd<RT,LA>& v)
{ v.copy_on_write(); v.ptr->read(I); 
  CGAL_assertion_msg((v.homogeneous(v.dimension()) > 0),
  "operator>>: denominator of vector must be larger than zero.");
  return I; 
}

template <class RT, class LA>
std::ostream& operator<<(std::ostream& O, const VectorHd<RT,LA>& v)
{ v.ptr->print(O,"VectorHd"); return O; } 

template <class RT, class LA>
inline CGAL::io_Operator io_tag(const VectorHd<RT,LA>&) 
{ return CGAL::io_Operator(); }


CGAL_END_NAMESPACE
#endif // CGAL_VECTORHD_C

