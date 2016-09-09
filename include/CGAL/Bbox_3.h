// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : Bbox_3.fw
// file          : include/CGAL/Bbox_3.h
// package       : _3 (1.4)
// revision      : 1.4
// revision_date : 15 Dec 1998 
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_BBOX_3_H
#define CGAL_BBOX_3_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_CARTESIAN_CLASSES_H
#include <CGAL/cartesian_classes.h>
#endif // CGAL_CARTESIAN_CLASSES_H
#ifndef CGAL_SIXTUPLE_H
#include <CGAL/Sixtuple.h>
#endif // CGAL_SIXTUPLE_H


class CGAL_Bbox_3 : public CGAL_Handle
{
public:
                         CGAL_Bbox_3();
                         CGAL_Bbox_3(const CGAL_Bbox_3 &);
                         CGAL_Bbox_3(double x_min, double y_min, double zmin,
                                    double x_max, double y_max, double z_max);
                         ~CGAL_Bbox_3();
  CGAL_Bbox_3             &operator=(const CGAL_Bbox_3 &b);

  double                 xmin() const;
  double                 ymin() const;
  double                 zmin() const;
  double                 xmax() const;
  double                 ymax() const;
  double                 zmax() const;

  CGAL_Bbox_3             operator+(const CGAL_Bbox_3 &b) const;

private:
  inline CGAL__Sixtuple<double>* ptr() const;
};


inline CGAL_Bbox_3::CGAL_Bbox_3()
{
  PTR = new CGAL__Sixtuple<double>;
}

inline CGAL_Bbox_3::CGAL_Bbox_3(const CGAL_Bbox_3 &b) :
  CGAL_Handle(b)
{}

inline CGAL_Bbox_3::CGAL_Bbox_3(double x_min, double y_min, double z_min,
                              double x_max, double y_max, double z_max)
{
  PTR = new CGAL__Sixtuple<double>(x_min, y_min, z_min, x_max, y_max, z_max);
}

inline CGAL_Bbox_3::~CGAL_Bbox_3()
{}

inline CGAL_Bbox_3 &CGAL_Bbox_3::operator=(const CGAL_Bbox_3 &b)
{
  CGAL_Handle::operator=(b);
  return *this;
}
inline double CGAL_Bbox_3::xmin() const
{
  return ptr()->e0;
}

inline double CGAL_Bbox_3::ymin() const
{
  return ptr()->e1;
}

inline double CGAL_Bbox_3::zmin() const
{
  return ptr()->e2;
}

inline double CGAL_Bbox_3::xmax() const
{
  return ptr()->e3;
}

inline double CGAL_Bbox_3::ymax() const
{
  return ptr()->e4;
}

inline double CGAL_Bbox_3::zmax() const
{
  return ptr()->e5;
}
inline CGAL_Bbox_3 CGAL_Bbox_3::operator+(const CGAL_Bbox_3 &b) const
{
  return CGAL_Bbox_3(CGAL_min(xmin(), b.xmin()),
                     CGAL_min(ymin(), b.ymin()),
                     CGAL_min(zmin(), b.zmin()),
                     CGAL_max(xmax(), b.xmax()),
                     CGAL_max(ymax(), b.ymax()),
                     CGAL_max(zmax(), b.zmax()));
}
inline bool CGAL_do_overlap(const CGAL_Bbox_3 &bb1, const CGAL_Bbox_3 &bb2)
{
    // check for emptiness ??
    if (bb1.xmax() < bb2.xmin() || bb2.xmax() < bb1.xmin())
        return false;
    if (bb1.ymax() < bb2.ymin() || bb2.ymax() < bb1.ymin())
        return false;
    if (bb1.zmax() < bb2.zmin() || bb2.zmax() < bb1.zmin())
        return false;
    return true;
}
inline CGAL__Sixtuple<double>* CGAL_Bbox_3::ptr() const
{
  return (CGAL__Sixtuple<double>*)PTR;
}

#ifndef CGAL_NO_OSTREAM_INSERT_BBOX_3
inline
ostream&
operator<<(ostream &os, const CGAL_Bbox_3 &b)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << b.xmin() << ' ' << b.ymin() << b.zmin();
    case CGAL_IO::BINARY :
        CGAL_write(os, b.xmin());
        CGAL_write(os, b.ymin());
        CGAL_write(os, b.zmin());
        CGAL_write(os, b.xmax());
        CGAL_write(os, b.ymax());
        CGAL_write(os, b.zmax());
        return os;
    default:
        os << "Bbox_3((" << b.xmin()
           << ", "       << b.ymin()
           << ", "       << b.zmin() << "), (";
        os <<               b.xmax()
           << ", "       << b.ymax()
           << ", "       << b.zmax() << "))";
        return os;
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_BBOX_3



#ifndef CGAL_NO_ISTREAM_EXTRACT_BBOX_3
inline
istream&
operator>>(istream &is, CGAL_Bbox_3 &b)
{
  double xmin, ymin, zmin, xmax, ymax, zmax;

  switch(is.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        is >> xmin >> ymin >> xmax >> ymax;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, xmin);
        CGAL_read(is, ymin);
        CGAL_read(is, zmin);
        CGAL_read(is, xmax);
        CGAL_read(is, ymax);
        CGAL_read(is, zmax);
        break;
  }
  b = CGAL_Bbox_3(xmin, ymin, zmin, xmax, ymax, zmax);
  return is;
}

#endif // CGAL_NO_ISTREAM_EXTRACT_BBOX_3



#endif // CGAL_BBOX_3_H
