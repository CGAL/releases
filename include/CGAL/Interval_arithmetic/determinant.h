// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Interval_arithmetic/determinant.h
// package       : Interval_arithmetic (4.15)
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

// This is a file containing overloading functions of
// include/CGAL/determinant.h for the Interval_nt_advanced type.
// The most important one is sign_of_det_2x2() for the moment.
//
// Sylvain Pion.

template <>
inline
Sign
sign_of_determinant2x2( const Interval_nt_advanced& px,
			const Interval_nt_advanced& py,
                        const Interval_nt_advanced& qx,
			const Interval_nt_advanced& qy)
{
  // We have to determine the extreme point (the corners of the intervals that
  // define their cones wrt the origin).

  double p1x, p2x, p1y, p2y, q1x, q2x, q1y, q2y;
  unsigned int pc = 0, qc = 0;

// Sets p1x and p2x.

  if (py.inf() >= 0) // P > (Ox) // These tests must be strict for the filter.
  {
    p1x = px.sup();
    p2x = px.inf();
  }
  else if (py.sup() <= 0) // P < (Ox)
  {
    p1x = px.inf();
    p2x = px.sup();
    pc = 2;
  }
  else // P cuts (Ox)
  { // We decide to use the generic function here ?
    if (px.inf() >= 0) // P > (Oy)
      p1x = p2x = px.inf();
    else if (px.sup() <= 0) // P < (Oy)
      p1x = p2x = px.sup();
    else return // P contains 0 => sign unknown => throw exception.
  }

// Sets p1y and p2y.

  if (px.inf() >= 0) // P > (Oy)
  {
    p1y = py.inf();
    p2y = py.sup();
    if (pc!=0) pc = 3;
  }
  else if (px.sup() <= 0) // P < (Oy)
  {
    p1y = py.sup();
    p2y = py.inf();
    if (pc!=2) pc = 1;
  }
  else // P cuts (Oy)
  {
    if (py.inf() >= 0) // P > (Ox)
      p1y = p2y = py.inf();
    else if (py.sup() <= 0) // P < (Ox)    // Useless test, previously tested
      p1y = p2y = py.sup();
    else return // P contains 0.  Cannot happen, already tested.
  }

// Admit the same is done for q{12}{xy}.  (we can also already conclude from
// there sooner in some cases)

// What we now have to compare is the sign_of_det2x2(p1,q2) AND
// sign_of_det2x2(p2,q1), right ?


// What the default template version does :
// return static_cast<Sign>(static_cast<int>(compare( px*qy, py*qx)));
}

