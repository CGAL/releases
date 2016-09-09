
// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// date          :
//
// file          : include/CGAL/IO/VRML_1_ostream.h
// package       : Inventor (1.2)
// source        : web/Inventor_ostream.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1998/06/29 13:58:51 $
// author(s)     : Andreas Fabri
//                 Lutz Kettner
//                 Herve bronnimann
//                 <Herve.Bronnimann>
//
// coordinator   : Herve Bronnimann
//
// release_date  : 1998, July 24
// email         : cgal@cs.uu.nl
//
// ======================================================================



#ifndef CGAL_IO_VRML_1_OSTREAM_H
#define CGAL_IO_VRML_1_OSTREAM_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

// Declare the common base class for OpenInventor and VRML 1.0 format.
#ifndef CGAL_IO_INVENTOR_OSTREAM_H
#include <CGAL/IO/Inventor_ostream.h>
#endif // CGAL_IO_INVENTOR_OSTREAM_H

// OpenInventor and VRML 1.0 are quite similar formats, so
// output operators could be shared if they use the common
// base class CGAL_Inventor_ostream_base, which is common for
// both output streams.


class CGAL_VRML_1_ostream : public CGAL_Inventor_ostream_base {
public:
    CGAL_VRML_1_ostream() {}
    CGAL_VRML_1_ostream(ostream& o) : CGAL_Inventor_ostream_base(o) {
        header();
    }
    void open(ostream& o) {
        CGAL_Inventor_ostream_base::open(o);
        header();
    }
private:
    void header() {
        os() << "#VRML V1.0 ascii" << endl;
        os() << "# File written with the help of the CGAL Library" << endl;
    }
};


#endif // CGAL_IO_VRML_1_OSTREAM_H

#ifdef CGAL_TETRAHEDRON_3_H
#ifndef CGAL_IO_VRML_1_TETRAHEDRON_3
#define CGAL_IO_VRML_1_TETRAHEDRON_3


template <class R >
CGAL_VRML_1_ostream&
operator<<(CGAL_VRML_1_ostream& os,
           const CGAL_Tetrahedron_3<R > &t)
{
  const char *Indent = "   ";
  os.os() << "\n Separator {";
  os.os() << "\n   Coordinate3 { \n"
          << Indent << "point [\n"
          << Indent << "  "
          << CGAL_to_double(t[0].x()) << " "
          << CGAL_to_double(t[0].y()) << " "
          << CGAL_to_double(t[0].z()) << " ,\n"
          << Indent << "  "
          << CGAL_to_double(t[1].x()) << " "
          << CGAL_to_double(t[1].y()) << " "
          << CGAL_to_double(t[1].z()) << " ,\n"
          << Indent << "  "
          << CGAL_to_double(t[2].x()) << " "
          << CGAL_to_double(t[2].y()) << " "
          << CGAL_to_double(t[2].z()) << " ,\n"
          << Indent << "  "
          << CGAL_to_double(t[3].x()) << " "
          << CGAL_to_double(t[3].y()) << " "
          << CGAL_to_double(t[3].z()) << " ]"
          << "\n   } #Coordinate3" ;
  os.os() << "\n   IndexedFaceSet {"
          << Indent << "coordIndex  [ 0,1,2,-1, 1,3,2,-1,\n"
          << Indent << "              0,2,3,-1, 0,3,1,-1 ]\n"
          << "\n   } #IndexedFaceSet"
          << "\n } #Separator\n";
  return os;
}


#endif // CGAL_IO_VRML_1_TETRAHEDRON_3
#endif // CGAL_TETRAHEDRON_3_H
