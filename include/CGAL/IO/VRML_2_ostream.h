// Copyright (c) 1997  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Inventor/include/CGAL/IO/VRML_2_ostream.h,v $
// $Revision: 1.9 $ $Date: 2003/10/21 12:17:53 $
// $Name: current_submission $
//
// Author(s)     : Andreas Fabri
//                 Lutz Kettner <kettner@inf.ethz.ch>
//                 Herve Bronnimann <Herve.Bronnimann@sophia.inria.fr>
//                 Mariette Yvinec <Mariette.Yvinec@sophia.inria.fr>



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
