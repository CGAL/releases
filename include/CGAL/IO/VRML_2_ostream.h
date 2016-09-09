// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/IO/VRML_2_ostream.h
// package       : Inventor (2.5)
// source        : $RCSfile: VRML_2_ostream.h,v $
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1999/12/01 09:14:03 $
// author(s)     : Andreas Fabri
//                 Lutz Kettner
//                 Herve Bronnimann
//                 Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================



#ifndef CGAL_IO_VRML_2_OSTREAM_H
#define CGAL_IO_VRML_2_OSTREAM_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

CGAL_BEGIN_NAMESPACE

class VRML_2_ostream {
public:
    VRML_2_ostream()           : m_os(0)  {}
    VRML_2_ostream(std::ostream& o) : m_os(&o) { header();}
    ~VRML_2_ostream()  { close(); }
    void open(std::ostream& o)   { m_os = &o; header(); }
    void close() {
        if ( m_os)
            footer();
        m_os = 0;
    }
    typedef const void* Const_void_ptr;
    operator Const_void_ptr () const {
        if ( m_os)
            return *m_os;
        return 0;
    }
    std::ostream& os() {
        // The behaviour if m_os == 0 could be changed to return
        // cerr or a file handle to /dev/null. The latter one would
        // mimick the behaviour that one can still use a stream with
        // an invalid stream, but without producing any output.
        CGAL_assertion( m_os);
        return *m_os;
    }
private:
    void header() {
        os() << "#VRML V2.0 utf8\n"
                "# File written with the help of the CGAL Library\n"
                "#-- Begin of file header\n"
                "Group {\n"
                "    children [\n"
                "        Shape {\n"
                "            appearance\n"
                "                Appearance {\n"
                "                    material DEF Material Material {}\n"
                "                }\n"
                "            geometry NULL\n"
                "        }\n"
                "        #-- End of file header" << std::endl;
    }
    void footer() {
        os() << "        #-- Begin of file footer\n"
                "    ]\n"
                "}\n"
                "#-- End of file footer" << std::endl;
    }
    std::ostream*  m_os;
};

CGAL_END_NAMESPACE

#endif // CGAL_IO_VRML_2_OSTREAM_H

#ifdef CGAL_TETRAHEDRON_3_H
#ifndef CGAL_IO_VRML_2_TETRAHEDRON_3
#define CGAL_IO_VRML_2_TETRAHEDRON_3

CGAL_BEGIN_NAMESPACE

template <class R >
VRML_2_ostream&
operator<<(VRML_2_ostream& os,
           const Tetrahedron_3<R > &t)
{
  const char *Indent = "                                    ";
  os.os() << "        Group {\n"
             "            children [\n"
             "                Shape {\n"
             "                    appearance\n"
             "                        Appearance {\n"
             "                            material USE Material\n"
             "                        } #Appearance\n"
             "                    geometry\n"
             "                        IndexedFaceSet {\n"
             "                            coord Coordinate {\n"
             "                                point [ \n"
          << Indent << "point [\n"
          << Indent << "  "
          << CGAL::to_double(t[0].x()) << " "
          << CGAL::to_double(t[0].y()) << " "
          << CGAL::to_double(t[0].z()) << " ,\n"
          << Indent << "  "
          << CGAL::to_double(t[1].x()) << " "
          << CGAL::to_double(t[1].y()) << " "
          << CGAL::to_double(t[1].z()) << " ,\n"
          << Indent << "  "
          << CGAL::to_double(t[2].x()) << " "
          << CGAL::to_double(t[2].y()) << " "
          << CGAL::to_double(t[2].z()) << " ,\n"
          << Indent << "  "
          << CGAL::to_double(t[3].x()) << " "
          << CGAL::to_double(t[3].y()) << " "
          << CGAL::to_double(t[3].z()) << " ]"
             "\n                                ]\n"
             "                            }\n"
             "                            solid   FALSE\n"
          << Indent << "coordIndex  [ 0,1,2,-1, 1,3,2,-1,\n"
          << Indent << "              0,2,3,-1, 0,3,1,-1 ]\n"
             "                        } #IndexedFaceSet\n"
             "                } #Shape\n"
             "            ] #children\n"
             "        } #Group" << std::endl;
  return os;
}

CGAL_END_NAMESPACE

#endif // CGAL_IO_VRML_2_TETRAHEDRON_3
#endif // CGAL_TETRAHEDRON_3_H
