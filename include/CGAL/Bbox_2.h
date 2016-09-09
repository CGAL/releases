// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Bbox_2.h
// author(s)     : Andreas Fabri
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
 

#ifndef CGAL_BBOX_2_H
#define CGAL_BBOX_2_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_CARTESIAN_CLASSES_H
#include <CGAL/cartesian_classes.h>
#endif // CGAL_CARTESIAN_CLASSES_H
#ifndef CGAL_FOURTUPLE_H
#include <CGAL/Fourtuple.h>
#endif // CGAL_FOURTUPLE_H

class CGAL_Bbox_2 : public CGAL_Handle
{
public:
                         CGAL_Bbox_2();
                         CGAL_Bbox_2(const CGAL_Bbox_2 &);
                         CGAL_Bbox_2(double x_min, double y_min,
                                   double x_max, double y_max);
                         ~CGAL_Bbox_2();
  CGAL_Bbox_2            &operator=(const CGAL_Bbox_2 &b);
  bool                   operator==(const CGAL_Bbox_2 &b) const;
  bool                   operator!=(const CGAL_Bbox_2 &b) const;

  int                    dimension() const;
  double                 xmin() const;
  double                 ymin() const;
  double                 xmax() const;
  double                 ymax() const;

  double                 max(int i) const;
  double                 min(int i) const;

  CGAL_Bbox_2              operator+(const CGAL_Bbox_2 &b) const;

private:
  CGAL__Fourtuple<double>*   ptr() const;
};


inline CGAL__Fourtuple<double>* CGAL_Bbox_2::ptr() const
{
  return (CGAL__Fourtuple<double>*)PTR;
}

inline int CGAL_Bbox_2::dimension() const
{
  return 2;
}

inline double CGAL_Bbox_2::xmin() const
{
  return ptr()->e0;
}

inline double CGAL_Bbox_2::ymin() const
{
  return ptr()->e1;
}

inline double CGAL_Bbox_2::xmax() const
{
  return ptr()->e2;
}

inline double CGAL_Bbox_2::ymax() const
{
  return ptr()->e3;
}

inline double CGAL_Bbox_2::min(int i) const
{
  CGAL_kernel_precondition( (i == 0 ) || ( i == 1 ) );
  if(i == 0) {
    return xmin();
  }
  return ymin();
}

inline double CGAL_Bbox_2::max(int i) const
{
  CGAL_kernel_precondition( (i == 0 ) || ( i == 1 ) );
  if(i == 0) {
    return xmax();
  }
  return ymax();
}
inline CGAL_Bbox_2 CGAL_Bbox_2::operator+(const CGAL_Bbox_2 &b) const
{
  return CGAL_Bbox_2(CGAL_min(xmin(), b.xmin()),
                     CGAL_min(ymin(), b.ymin()),
                     CGAL_max(xmax(), b.xmax()),
                     CGAL_max(ymax(), b.ymax()));
}
inline bool CGAL_do_overlap(const CGAL_Bbox_2 &bb1, const CGAL_Bbox_2 &bb2)
{
    // check for emptiness ??
    if (bb1.xmax() < bb2.xmin() || bb2.xmax() < bb1.xmin())
        return false;
    if (bb1.ymax() < bb2.ymin() || bb2.ymax() < bb1.ymin())
        return false;
    return true;
}

#ifndef CGAL_NO_OSTREAM_INSERT_BBOX_2
inline
ostream&
operator<<(ostream &os, const CGAL_Bbox_2 &b)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        os << b.xmin() << ' ' << b.ymin() << ' '
           << b.xmax() << ' ' << b.ymax();
        break;
    case CGAL_IO::BINARY :
        CGAL_write(os, b.xmin());
        CGAL_write(os, b.ymin());
        CGAL_write(os, b.xmax());
        CGAL_write(os, b.ymax());
        break;
    default:
        os << "Bbox_2(" << b.xmin() << ", " << b.ymin() << ", "
                        << b.xmax() << ", " << b.ymax() << ")";
        break;
    }
    return os;
}
#endif // CGAL_NO_OSTREAM_INSERT_BBOX_2



#ifndef CGAL_NO_ISTREAM_EXTRACT_BBOX_2
inline
istream&
operator>>(istream &is, CGAL_Bbox_2 &b)
{
    double xmin, ymin, xmax, ymax;

    switch(is.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        is >> xmin >> ymin >> xmax >> ymax;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, xmin);
        CGAL_read(is, ymin);
        CGAL_read(is, xmax);
        CGAL_read(is, ymax);
        break;
    }
    b = CGAL_Bbox_2(xmin, ymin, xmax, ymax);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_BBOX_2



#endif // CGAL_BBOX_2_H
