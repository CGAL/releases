// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Bbox_3.h
// package       : _3 (3.23)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/06/20 12:25:22 $
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_BBOX_3_H
#define CGAL_BBOX_3_H

#include <CGAL/basic.h>
#include <CGAL/cartesian_classes.h>
#include <CGAL/Sixtuple.h>

CGAL_BEGIN_NAMESPACE

class Bbox_3 : public Handle_for< Sixtuple<double> >
{
public:
                         Bbox_3();
                         Bbox_3(double x_min, double y_min, double zmin,
                                double x_max, double y_max, double z_max);

  double                 xmin() const;
  double                 ymin() const;
  double                 zmin() const;
  double                 xmax() const;
  double                 ymax() const;
  double                 zmax() const;

  Bbox_3             operator+(const Bbox_3& b) const;
};

inline
Bbox_3::Bbox_3()
{ new ( static_cast< void*>(ptr)) Sixtuple<double>(); }

inline
Bbox_3::Bbox_3(double x_min, double y_min, double z_min,
               double x_max, double y_max, double z_max)
{
  new ( static_cast< void*>(ptr)) Sixtuple<double>(x_min, y_min, z_min,
                                                   x_max, y_max, z_max);
}

inline
double
Bbox_3::xmin() const
{ return ptr->e0; }

inline
double
Bbox_3::ymin() const
{ return ptr->e1; }

inline
double
Bbox_3::zmin() const
{ return ptr->e2; }

inline
double
Bbox_3::xmax() const
{ return ptr->e3; }

inline
double
Bbox_3::ymax() const
{ return ptr->e4; }

inline
double
Bbox_3::zmax() const
{ return ptr->e5; }

inline Bbox_3 Bbox_3::operator+(const Bbox_3& b) const
{
  return Bbox_3(std::min(xmin(), b.xmin()),
                std::min(ymin(), b.ymin()),
                std::min(zmin(), b.zmin()),
                std::max(xmax(), b.xmax()),
                std::max(ymax(), b.ymax()),
                std::max(zmax(), b.zmax()));
}

inline bool do_overlap(const Bbox_3& bb1, const Bbox_3& bb2)
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

#ifndef CGAL_NO_OSTREAM_INSERT_BBOX_3
inline
std::ostream&
operator<<(std::ostream &os, const Bbox_3& b)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << b.xmin() << ' ' << b.ymin() << ' ' << b.zmin();
    case IO::BINARY :
        write(os, b.xmin());
        write(os, b.ymin());
        write(os, b.zmin());
        write(os, b.xmax());
        write(os, b.ymax());
        write(os, b.zmax());
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
std::istream&
operator>>(std::istream &is, Bbox_3& b)
{
  double xmin, ymin, zmin, xmax, ymax, zmax;

  switch(is.iword(IO::mode))
  {
    case IO::ASCII :
        is >> xmin >> ymin >> xmax >> ymax;
        break;
    case IO::BINARY :
        read(is, xmin);
        read(is, ymin);
        read(is, zmin);
        read(is, xmax);
        read(is, ymax);
        read(is, zmax);
        break;
  }
  b = Bbox_3(xmin, ymin, zmin, xmax, ymax, zmax);
  return is;
}

#endif // CGAL_NO_ISTREAM_EXTRACT_BBOX_3

CGAL_END_NAMESPACE

#endif // CGAL_BBOX_3_H
