// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Cartesian/Aff_transformation_2.C
// package       : C2 (4.4)
// revision      : $Revision: 1.20 $
// revision_date : $Date: 2000/06/26 15:00:19 $
// author(s)     : Andreas Fabri, Lutz Kettner
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_AFF_TRANSFORMATION_2_C
#define CGAL_CARTESIAN_AFF_TRANSFORMATION_2_C

#include <CGAL/determinant.h>
#include <CGAL/Cartesian/Aff_transformation_rep_2.C>

#ifndef CGAL_CARTESIAN_REDEFINE_NAMES_2_H
#define CGAL_CTAG
#endif

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

CGAL_BEGIN_NAMESPACE

template < class R >
Aff_transformationC2<R CGAL_CTAG>::
Aff_transformationC2()
{
  PTR = new Aff_transformation_repC2<R>(FT(1), FT(0), FT(0), FT(1));
}

template < class R >
Aff_transformationC2<R CGAL_CTAG>::
Aff_transformationC2(const Identity_transformation)
{
  PTR = new Aff_transformation_repC2<R>(FT(1), FT(0), FT(0), FT(1));
}

template < class R >
Aff_transformationC2<R CGAL_CTAG>::Aff_transformationC2
  (const Aff_transformationC2<R CGAL_CTAG> &t)
  : Handle(t)
{}

template < class R >
Aff_transformationC2<R CGAL_CTAG>::
Aff_transformationC2(
        const typename Aff_transformationC2<R CGAL_CTAG>::FT & m11,
        const typename Aff_transformationC2<R CGAL_CTAG>::FT & m12,
        const typename Aff_transformationC2<R CGAL_CTAG>::FT & m21,
	const typename Aff_transformationC2<R CGAL_CTAG>::FT & m22,
        const typename Aff_transformationC2<R CGAL_CTAG>::FT & w)
{
    PTR = new Aff_transformation_repC2<R>(m11/w, m12/w, m21/w, m22/w);
}

template < class R >
Aff_transformationC2<R CGAL_CTAG>::
Aff_transformationC2(
	const Translation,
        const typename Aff_transformationC2<R CGAL_CTAG>::Vector_2 &v)
{
  PTR = new Translation_repC2<R>(v);
}

template < class R >
Aff_transformationC2<R CGAL_CTAG>::
Aff_transformationC2(
        const Rotation,
        const typename Aff_transformationC2<R CGAL_CTAG>::Direction_2 &d,
        const typename Aff_transformationC2<R CGAL_CTAG>::FT &num,
	const typename Aff_transformationC2<R CGAL_CTAG>::FT &den)
{
  PTR = new Rotation_repC2<R>(d, num, den);
}

template < class R >
Aff_transformationC2<R CGAL_CTAG>::
Aff_transformationC2(
        const Rotation,
        const typename Aff_transformationC2<R CGAL_CTAG>::FT &sine,
	const typename Aff_transformationC2<R CGAL_CTAG>::FT &cosine,
	const typename Aff_transformationC2<R CGAL_CTAG>::FT &w)
{
  if (w != FT(1)) // Idem...
    PTR = new Rotation_repC2<R>(sine/w, cosine/w);
  else
    PTR = new Rotation_repC2<R>(sine, cosine);
}

template < class R >
Aff_transformationC2<R CGAL_CTAG>::
Aff_transformationC2(const Scaling,
                     const typename Aff_transformationC2<R CGAL_CTAG>::FT &s,
		     const typename Aff_transformationC2<R CGAL_CTAG>::FT &w)
{
  if (w != FT(1)) // ....
    PTR = new Scaling_repC2<R>(s/w);
  else
    PTR = new Scaling_repC2<R>(s);
}

// and a 3x2 matrix for the operations combining rotation, scaling, translation
template < class R >
Aff_transformationC2<R CGAL_CTAG>::
Aff_transformationC2(
	const typename Aff_transformationC2<R CGAL_CTAG>::FT &m11,
        const typename Aff_transformationC2<R CGAL_CTAG>::FT &m12,
	const typename Aff_transformationC2<R CGAL_CTAG>::FT &m13,
        const typename Aff_transformationC2<R CGAL_CTAG>::FT &m21,
	const typename Aff_transformationC2<R CGAL_CTAG>::FT &m22,
	const typename Aff_transformationC2<R CGAL_CTAG>::FT &m23,
        const typename Aff_transformationC2<R CGAL_CTAG>::FT &w)
{
  if (w != FT(1)) // ...
    PTR = new Aff_transformation_repC2<R>(m11/w, m12/w, m13/w,
                                          m21/w, m22/w, m23/w);
  else
    PTR = new Aff_transformation_repC2<R>(m11, m12, m13,
                                          m21, m22, m23);
}

template < class R >
Aff_transformationC2<R CGAL_CTAG>::~Aff_transformationC2()
{}

template < class R >
Aff_transformationC2<R CGAL_CTAG> &
Aff_transformationC2<R CGAL_CTAG>::
operator=(const Aff_transformationC2<R CGAL_CTAG> &t)
{
  Handle::operator=(t);
  return *this;
}

template < class R >
std::ostream&
Aff_transformationC2<R CGAL_CTAG>::print(std::ostream &os) const
{
  ptr()->print(os);
  return os;
}

#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATIONC2
template < class R >
std::ostream&
operator<<(std::ostream& os, const Aff_transformationC2<R CGAL_CTAG>& t)
{
  t.print(os);
  return os;
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATIONC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATIONC2
#endif // CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATIONC2

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

#endif // CGAL_CARTESIAN_AFF_TRANSFORMATION_2_C
