// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/IO/File_scanner_OFF.h
// package       : Polyhedron_IO (2.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/06/22 16:00:50 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// File scanner for an object in an object file format (OFF) file
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_FILE_SCANNER_OFF_H
#define CGAL_IO_FILE_SCANNER_OFF_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_KNOWN_BIT_SIZE_INTEGERS_H
#include <CGAL/known_bit_size_integers.h>
#endif
#ifndef CGAL_PROTECT_CSTDDEF
#include <cstddef>
#define CGAL_PROTECT_CSTDDEF
#endif
#ifndef CGAL_IO_BINARY_FILE_IO_H
#include <CGAL/IO/binary_file_io.h>
#endif // CGAL_IO_BINARY_FILE_IO_H
#ifndef CGAL_IO_FILE_HEADER_OFF_H
#include <CGAL/IO/File_header_OFF.h>
#endif // CGAL_IO_FILE_HEADER_OFF_H
#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif

CGAL_BEGIN_NAMESPACE

class File_scanner_OFF : public File_header_OFF {
    std::istream&  m_in;
    bool           normals_read;
    void skip_comment() { m_in >> skip_comment_OFF; }
public:
    File_scanner_OFF( std::istream& in, bool verbose = false)
      : File_header_OFF(verbose), m_in(in), normals_read(false) {
        in >> static_cast<File_header_OFF&>( *this);
    }
    File_scanner_OFF( std::istream& in, const File_header_OFF& header)
      : File_header_OFF(header), m_in(in), normals_read(false) {}

    std::istream& in() { return m_in; }

    // The scan_vertex() routine is provided for multiple
    // coordinate types to support parameterized polytopes.
    void scan_vertex( float&  x, float&  y, float&  z) {
        if ( binary()) {
            _Binary_read_float32( m_in, x);
            _Binary_read_float32( m_in, y);
            _Binary_read_float32( m_in, z);
            if ( is_homogeneous()) {
                float w;
                _Binary_read_float32( m_in, w);
                x /= w;
                y /= w;
                z /= w;
            }
        } else {
            skip_comment();
            m_in >> x >> y >> z;
            if ( is_homogeneous()) {
                float w;
                m_in >> w;
                x /= w;
                y /= w;
                z /= w;
            }
        }
    }
    void scan_vertex( double& x, double& y, double& z) {
        if ( binary()) {
            float f;
            _Binary_read_float32( m_in, f);
            x = f;
            _Binary_read_float32( m_in, f);
            y = f;
            _Binary_read_float32( m_in, f);
            z = f;
            if ( is_homogeneous()) {
                _Binary_read_float32( m_in, f);
                x /= f;
                y /= f;
                z /= f;
            }
        } else {
            skip_comment();
            m_in >> x >> y >> z;
            if ( is_homogeneous()) {
                double w;
                m_in >> w;
                x /= w;
                y /= w;
                z /= w;
            }
        }
    }
    void scan_vertex( int& x, int& y, int& z) {
        if ( binary()) {
            float fx, fy, fz;
            _Binary_read_float32( m_in, fx);
            _Binary_read_float32( m_in, fy);
            _Binary_read_float32( m_in, fz);
            if ( is_homogeneous()) {
                float fw;
                _Binary_read_float32( m_in, fw);
                x = int( fx / fw);
                y = int( fy / fw);
                y = int( fz / fw);
            } else {
                x = int(fx);
                y = int(fy);
                z = int(fz);
            }
        } else {
            skip_comment();
            if ( is_homogeneous()) {
                double fx, fy, fz, fw;
                m_in >> fx >> fy >> fz >> fw;
                x = int( fx / fw);
                y = int( fy / fw);
                y = int( fz / fw);
            } else {
                double d;
                m_in >> d;
                x = int(d);
                m_in >> d;
                y = int(d);
                m_in >> d;
                z = int(d);
            }
        }
    }

    void scan_vertex( float&  x, float&  y, float&  z, float&  w) {
        w = 1;
        if ( binary()) {
            _Binary_read_float32( m_in, x);
            _Binary_read_float32( m_in, y);
            _Binary_read_float32( m_in, z);
            if ( is_homogeneous())
                _Binary_read_float32( m_in, w);
        } else {
            skip_comment();
            m_in >> x >> y >> z;
            if ( is_homogeneous())
                m_in >> w;
        }
    }
    void scan_vertex( double& x, double& y, double& z, double& w) {
        w = 1;
        if ( binary()) {
            float f;
            _Binary_read_float32( m_in, f);
            x = f;
            _Binary_read_float32( m_in, f);
            y = f;
            _Binary_read_float32( m_in, f);
            z = f;
            if ( is_homogeneous()) {
                _Binary_read_float32( m_in, f);
                w = f;
            }
        } else {
            skip_comment();
            m_in >> x >> y >> z;
            if ( is_homogeneous())
                m_in >> w;
        }
    }
    void scan_vertex( int& x, int& y, int& z, int& w) {
        w = 1;
        if ( binary()) {
            float f;
            _Binary_read_float32( m_in, f);
            x = int(f);
            _Binary_read_float32( m_in, f);
            y = int(f);
            _Binary_read_float32( m_in, f);
            z = int(f);
            if ( is_homogeneous()) {
                _Binary_read_float32( m_in, f);
                w = int(f);
            }
        } else {
            skip_comment();
            double d;
            m_in >> d;
            x = int(d);
            m_in >> d;
            y = int(d);
            m_in >> d;
            z = int(d);
            if ( is_homogeneous()) {
                m_in >> d;
                w = int(d);
            }
        }
    }

    void scan_normal( float&  x, float&  y, float&  z) {
        if ( has_normals()) {
            normals_read = true;
            if ( binary()) {
                _Binary_read_float32( m_in, x);
                _Binary_read_float32( m_in, y);
                _Binary_read_float32( m_in, z);
                if ( is_homogeneous()) {
                    float w;
                    _Binary_read_float32( m_in, w);
                    x /= w;
                    y /= w;
                    z /= w;
                }
            } else {
                m_in >> x >> y >> z;
                if ( is_homogeneous()) {
                    float w;
                    m_in >> w;
                    x /= w;
                    y /= w;
                    z /= w;
                }
            }
        }
    }
    void scan_normal( double& x, double& y, double& z) {
        if ( has_normals()) {
            normals_read = true;
            if ( binary()) {
                float fx, fy, fz;
                _Binary_read_float32( m_in, fx);
                _Binary_read_float32( m_in, fy);
                _Binary_read_float32( m_in, fz);
                if ( is_homogeneous()) {
                    float fw;
                    _Binary_read_float32( m_in, fw);
                    x = fx / fw;
                    y = fy / fw;
                    y = fz / fw;
                } else {
                    x = fx;
                    y = fy;
                    z = fz;
                }
            } else {
                if ( is_homogeneous()) {
                    float fx, fy, fz, fw;
                    m_in >> fx >> fy >> fz >> fw;
                    x = fx / fw;
                    y = fy / fw;
                    y = fz / fw;
                } else
                    m_in >> x >> y >> z;
            }
        }
    }
    void scan_normal( int& x, int& y, int& z) {
        if ( has_normals()) {
            normals_read = true;
            if ( binary()) {
                float fx, fy, fz;
                _Binary_read_float32( m_in, fx);
                _Binary_read_float32( m_in, fy);
                _Binary_read_float32( m_in, fz);
                if ( is_homogeneous()) {
                    float fw;
                    _Binary_read_float32( m_in, fw);
                    x = int( fx / fw);
                    y = int( fy / fw);
                    y = int( fz / fw);
                } else {
                    x = int(fx);
                    y = int(fy);
                    z = int(fz);
                }
            } else {
                if ( is_homogeneous()) {
                    float fx, fy, fz, fw;
                    m_in >> fx >> fy >> fz >> fw;
                    x = int( fx / fw);
                    y = int( fy / fw);
                    y = int( fz / fw);
                } else {
                    double d;
                    m_in >> d;
                    x = int(d);
                    m_in >> d;
                    y = int(d);
                    m_in >> d;
                    z = int(d);
                }
            }
        }
    }

    void scan_normal( float&  x, float&  y, float&  z, float&  w) {
        w = 1;
        if ( has_normals()) {
            normals_read = true;
            if ( binary()) {
                _Binary_read_float32( m_in, x);
                _Binary_read_float32( m_in, y);
                _Binary_read_float32( m_in, z);
                if ( is_homogeneous())
                    _Binary_read_float32( m_in, w);
            } else {
                m_in >> x >> y >> z;
                if ( is_homogeneous())
                    m_in >> w;
            }
        }
    }
    void scan_normal( double& x, double& y, double& z, double& w) {
        w = 1;
        if ( has_normals()) {
            normals_read = true;
            if ( binary()) {
                float f;
                _Binary_read_float32( m_in, f);
                x = f;
                _Binary_read_float32( m_in, f);
                y = f;
                _Binary_read_float32( m_in, f);
                z = f;
                if ( is_homogeneous()) {
                    _Binary_read_float32( m_in, f);
                    w = f;
                }
            } else {
                m_in >> x >> y >> z;
                if ( is_homogeneous())
                    m_in >> w;
            }
        }
    }
    void scan_normal( int& x, int& y, int& z, int& w) {
        w = 1;
        if ( has_normals()) {
            normals_read = true;
            if ( binary()) {
                float f;
                _Binary_read_float32( m_in, f);
                x = int(f);
                _Binary_read_float32( m_in, f);
                y = int(f);
                _Binary_read_float32( m_in, f);
                z = int(f);
                if ( is_homogeneous()) {
                    _Binary_read_float32( m_in, f);
                    w = int(f);
                }
            } else {
                double d;
                m_in >> d;
                x = int(d);
                m_in >> d;
                y = int(d);
                m_in >> d;
                z = int(d);
                if ( is_homogeneous()) {
                    m_in >> d;
                    w = int(d);
                }
            }
        }
    }

    void skip_to_next_vertex( int current_vertex);

    void scan_facet( Integer32& size, int current_facet) {
        CGAL_assertion( current_facet < size_of_facets());
        if ( binary())
            _Binary_read_integer32( m_in, size);
        else {
            skip_comment();
            m_in >> size;
        }
    }

    void scan_facet_vertex_index( Integer32& index,
                                  int current_facet) {
        if ( binary())
            _Binary_read_integer32( m_in, index);
        else
            m_in >> index;
        if( ! m_in) {
            if ( verbose()) {
                std::cerr << " " << std::endl;
                std::cerr << "File_scanner_OFF::" << std::endl;
                std::cerr << "scan_facet_vertex_index(): input error:  "
                             "cannot read OFF file beyond facet "
                          << current_facet << "." << std::endl;
            }
            set_off_header( false);
            return;
        }
        index -= index_offset();
        if( index < 0 || index >= size_of_vertices()) {
            m_in.clear( std::ios::badbit);
            if ( verbose()) {
                std::cerr << " " << std::endl;
                std::cerr << "File_scanner_OFF::" << std::endl;
                std::cerr << "scan_facet_vertex_index(): input error: "
                             "facet " << current_facet << ": vertex index "
                          << index + index_offset() << ": is out of range."
                          << std::endl;
            }
            set_off_header( false);
            return;
        }
    }

    void skip_to_next_facet( int current_facet);
};

template < class R> class Point_3;
template < class R> class Vector_3;

template < class R> inline
Point_3<R>&
file_scan_vertex( File_scanner_OFF& scanner, Point_3<R>& p) {
    typedef typename R::RT  RT;
    double x, y, z, w;
    scanner.scan_vertex( x, y, z, w);
    if ( w == 1)
        p = Point_3<R>( RT(x), RT(y), RT(z));
    else
        p = Point_3<R>( RT(x), RT(y), RT(z), RT(w));
    return p;
}

template < class R> inline
Vector_3<R>&
file_scan_normal( File_scanner_OFF& scanner, Vector_3<R>& v) {
    typedef typename R::RT  RT;
    double x, y, z, w;
    scanner.scan_normal( x, y, z, w);
    if ( w == 1)
        v = Vector_3<R>( RT(x), RT(y), RT(z));
    else
        v = Vector_3<R>( RT(x), RT(y), RT(z), RT(w));
    return v;
}

CGAL_END_NAMESPACE
#endif // CGAL_IO_FILE_SCANNER_OFF_H //
// EOF //
