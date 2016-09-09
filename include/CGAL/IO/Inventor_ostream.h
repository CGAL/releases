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
// file          : include/CGAL/IO/Inventor_ostream.h
// package       : Inventor (2.5)
// source        : $RCSfile: Inventor_ostream.h,v $
// revision      : $Revision: 1.7 $
// revision_date : $Date: 1999/12/06 13:13:31 $
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


#ifndef CGAL_IO_INVENTOR_OSTREAM_H
#define CGAL_IO_INVENTOR_OSTREAM_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

// OpenInventor and VRML 1.0 are quite similar formats, so
// output operators could be shared if they use the following
// base class, which is common for both output streams.

CGAL_BEGIN_NAMESPACE

class Inventor_ostream_base {
private:
    std::ostream*  m_os;
public:
    Inventor_ostream_base()           : m_os(0)  {}
    Inventor_ostream_base(std::ostream& o) : m_os(&o) {}
    ~Inventor_ostream_base()  { close(); }
    void open(std::ostream& o)        { m_os = &o; }
    void close() {
        if ( m_os)
            os() << std::endl;
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
};


class Inventor_ostream : public  Inventor_ostream_base
{
public:
    Inventor_ostream() {}
    Inventor_ostream(std::ostream& o) : Inventor_ostream_base(o) {
        header();
    }
    void open(std::ostream& o) {
        Inventor_ostream_base::open(o);
        header();
    }
private:
    void header() {
        os() << "#Inventor V2.0 ascii" << std::endl;
        os() << "# File written with the help of the CGAL Library" 
	     << std::endl;
    }
};

CGAL_END_NAMESPACE
#endif // CGAL_IO_INVENTOR_OSTREAM_H


#ifdef CGAL_TETRAHEDRON_3_H
#ifndef CGAL_INVENTOR_TETRAHEDRON_3
#define CGAL_INVENTOR_TETRAHEDRON_3

CGAL_BEGIN_NAMESPACE

template <class R >
Inventor_ostream&
operator<<(Inventor_ostream& os,
           const Tetrahedron_3<R > &t)
{
  const char *Indent = "   ";
  os.os() << "\n Separator {";
  os.os() << "\n   Coordinate3 { \n"
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
          << "\n   } #Coordinate3" ;
  os.os() << "\n   IndexedFaceSet {"
          << Indent << "coordIndex  [ 0,1,2,-1, 1,3,2,-1,\n"
          << Indent << "              0,2,3,-1, 0,3,1,-1 ]\n"
          << "\n   } #IndexedFaceSet"
          << "\n } #Separator\n";
  return os;
}

CGAL_END_NAMESPACE

#endif // CGAL_INVENTOR_TETRAHEDRON_3
#endif // CGAL_TETRAHEDRON_3_H



