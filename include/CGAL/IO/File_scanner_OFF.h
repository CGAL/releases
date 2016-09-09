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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/IO/File_scanner_OFF.h
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// File scanner for an object in an object file format (OFF) file
//
// email         : cgal@cs.uu.nl
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

#ifndef CGAL_PROTECT_STDDEF_H
#include <stddef.h>
#define CGAL_PROTECT_STDDEF_H
#endif // CGAL_PROTECT_STDDEF_H

#ifndef CGAL_IO_BINARY_FILE_IO_H
#include <CGAL/IO/binary_file_io.h>
#endif // CGAL_IO_BINARY_FILE_IO_H

#ifndef CGAL_IO_FILE_HEADER_OFF_H
#include <CGAL/IO/File_header_OFF.h>
#endif // CGAL_IO_FILE_HEADER_OFF_H

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

class CGAL_File_scanner_OFF : public CGAL_File_header_OFF {
    istream&  m_in;
    bool      normals_read;
    void skip_comment() { m_in >> CGAL_skip_comment_OFF; }
public:
    CGAL_File_scanner_OFF( istream& in, bool verbose = false)
    :   CGAL_File_header_OFF(verbose),
        m_in(in),
        normals_read(false)
    {
        in >> CGAL_static_cast(CGAL_File_header_OFF&, *this);
    }
    CGAL_File_scanner_OFF( istream& in, const CGAL_File_header_OFF& header)
    : CGAL_File_header_OFF(header), m_in(in), normals_read(false) {}

    istream& in() { return m_in; }

    // The scan_vertex() routine is provided for multiple
    // coordinate types to support parameterized polytopes.
    void scan_vertex( float&  x, float&  y, float&  z) {
        if ( binary()) {
            CGAL__Binary_read_float32( m_in, x);
            CGAL__Binary_read_float32( m_in, y);
            CGAL__Binary_read_float32( m_in, z);
            if ( is_homogeneous()) {
                float w;
                CGAL__Binary_read_float32( m_in, w);
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
            CGAL__Binary_read_float32( m_in, f);
            x = f;
            CGAL__Binary_read_float32( m_in, f);
            y = f;
            CGAL__Binary_read_float32( m_in, f);
            z = f;
            if ( is_homogeneous()) {
                CGAL__Binary_read_float32( m_in, f);
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
            CGAL__Binary_read_float32( m_in, fx);
            CGAL__Binary_read_float32( m_in, fy);
            CGAL__Binary_read_float32( m_in, fz);
            if ( is_homogeneous()) {
                float fw;
                CGAL__Binary_read_float32( m_in, fw);
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
            CGAL__Binary_read_float32( m_in, x);
            CGAL__Binary_read_float32( m_in, y);
            CGAL__Binary_read_float32( m_in, z);
            if ( is_homogeneous())
                CGAL__Binary_read_float32( m_in, w);
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
            CGAL__Binary_read_float32( m_in, f);
            x = f;
            CGAL__Binary_read_float32( m_in, f);
            y = f;
            CGAL__Binary_read_float32( m_in, f);
            z = f;
            if ( is_homogeneous()) {
                CGAL__Binary_read_float32( m_in, f);
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
            CGAL__Binary_read_float32( m_in, f);
            x = int(f);
            CGAL__Binary_read_float32( m_in, f);
            y = int(f);
            CGAL__Binary_read_float32( m_in, f);
            z = int(f);
            if ( is_homogeneous()) {
                CGAL__Binary_read_float32( m_in, f);
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
                CGAL__Binary_read_float32( m_in, x);
                CGAL__Binary_read_float32( m_in, y);
                CGAL__Binary_read_float32( m_in, z);
                if ( is_homogeneous()) {
                    float w;
                    CGAL__Binary_read_float32( m_in, w);
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
                CGAL__Binary_read_float32( m_in, fx);
                CGAL__Binary_read_float32( m_in, fy);
                CGAL__Binary_read_float32( m_in, fz);
                if ( is_homogeneous()) {
                    float fw;
                    CGAL__Binary_read_float32( m_in, fw);
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
                CGAL__Binary_read_float32( m_in, fx);
                CGAL__Binary_read_float32( m_in, fy);
                CGAL__Binary_read_float32( m_in, fz);
                if ( is_homogeneous()) {
                    float fw;
                    CGAL__Binary_read_float32( m_in, fw);
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
                CGAL__Binary_read_float32( m_in, x);
                CGAL__Binary_read_float32( m_in, y);
                CGAL__Binary_read_float32( m_in, z);
                if ( is_homogeneous())
                    CGAL__Binary_read_float32( m_in, w);
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
                CGAL__Binary_read_float32( m_in, f);
                x = f;
                CGAL__Binary_read_float32( m_in, f);
                y = f;
                CGAL__Binary_read_float32( m_in, f);
                z = f;
                if ( is_homogeneous()) {
                    CGAL__Binary_read_float32( m_in, f);
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
                CGAL__Binary_read_float32( m_in, f);
                x = int(f);
                CGAL__Binary_read_float32( m_in, f);
                y = int(f);
                CGAL__Binary_read_float32( m_in, f);
                z = int(f);
                if ( is_homogeneous()) {
                    CGAL__Binary_read_float32( m_in, f);
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

    void scan_facet( CGAL_Integer32& size, int current_facet) {
        CGAL_assertion( current_facet < size_of_facets());
        if ( binary())
            CGAL__Binary_read_integer32( m_in, size);
        else {
            skip_comment();
            m_in >> size;
        }
    }

    void scan_facet_vertex_index( CGAL_Integer32& index,
                                  int current_facet) {
        if ( binary())
            CGAL__Binary_read_integer32( m_in, index);
        else
            m_in >> index;
        if( ! m_in) {
            if ( verbose()) {
                cerr << " " << endl;
                cerr << "CGAL_File_scanner_OFF::" << endl;
                cerr << "scan_facet_vertex_index(): input error: cannot "
                        "read OFF file beyond facet " << current_facet
                     << "." << endl;
            }
            set_off_header( false);
            return;
        }
        index -= index_offset();
        if( index < 0 || index >= size_of_vertices()) {
            m_in.clear( ios::badbit);
            if ( verbose()) {
                cerr << " " << endl;
                cerr << "CGAL_File_scanner_OFF::" << endl;
                cerr << "scan_facet_vertex_index(): input error: facet "
                     << current_facet << ": vertex index "
                     << index + index_offset() << ": is out of range."
                     << endl;
            }
            set_off_header( false);
            return;
        }
    }

    void skip_to_next_facet( int current_facet);
};

#ifdef CGAL_IO_FILE_SCANNER_OFF_H

template < class R> class CGAL_Point_3;
template < class R> class CGAL_Vector_3;

template < class R> inline
CGAL_Point_3<R>&
CGAL_file_scan_vertex( CGAL_File_scanner_OFF& scanner,
                      CGAL_Point_3<R>& p) {
    typedef typename R::RT  RT;
    double x, y, z, w;
    scanner.scan_vertex( x, y, z, w);
    if ( w == 1)
        p = CGAL_Point_3<R>( RT(x), RT(y), RT(z));
    else
        p = CGAL_Point_3<R>( RT(x), RT(y), RT(z), RT(w));
    return p;
}

template < class R> inline
CGAL_Vector_3<R>&
CGAL_file_scan_normal( CGAL_File_scanner_OFF& scanner,
                      CGAL_Vector_3<R>& v) {
    typedef typename R::RT  RT;
    double x, y, z, w;
    scanner.scan_normal( x, y, z, w);
    if ( w == 1)
        v = CGAL_Vector_3<R>( RT(x), RT(y), RT(z));
    else
        v = CGAL_Vector_3<R>( RT(x), RT(y), RT(z), RT(w));
    return v;
}

#else  // CGAL_IO_FILE_SCANNER_OFF_H //
// This is code from the CEBAP project now useless in CGAL.

#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif
#ifndef CGAL_VECTOR_3_H
#include <CGAL/Vector_3.h>
#endif
#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif
#ifndef CGAL_VECTOR_3_H
#include <CGAL/Vector_3.h>
#endif

template < class Pt, class RT> inline
Pt&
CGAL_file_scan_vertex( CGAL_File_scanner_OFF& scanner, Pt& p,
                      CGAL_Cartesian_tag, RT*) {
    double x, y, z;
    scanner.scan_vertex( x, y, z);
    p = Pt( RT(x), RT(y), RT(z));
    return p;
}

inline CGAL_Point_3<float>&
CGAL_file_scan_vertex( CGAL_File_scanner_OFF& scanner,
                      CGAL_Point_3<float>& p,
                      CGAL_Cartesian_tag,
                      float*) {
    scanner.scan_vertex( p.x(), p.y(), p.z());
    return p;
}

inline CGAL_Point_3<double>&
CGAL_file_scan_vertex( CGAL_File_scanner_OFF& scanner,
                      CGAL_Point_3<double>& p,
                      CGAL_Cartesian_tag,
                      double*) {
    scanner.scan_vertex( p.x(), p.y(), p.z());
    return p;
}

inline CGAL_Point_3<int>&
CGAL_file_scan_vertex( CGAL_File_scanner_OFF& scanner,
                      CGAL_Point_3<int>& p,
                      CGAL_Cartesian_tag,
                      int*) {
    scanner.scan_vertex( p.x(), p.y(), p.z());
    return p;
}

template < class Pt, class RT> inline
Pt&
CGAL_file_scan_vertex( CGAL_File_scanner_OFF& scanner, Pt& p,
                      CGAL_Rational_tag, RT*) {
    double x, y, z, w;
    scanner.scan_vertex( x, y, z, w);
    p = Pt( RT(x), RT(y), RT(z), RT(w));
    return p;
}

inline CGAL_Point_3<float,float>&
CGAL_file_scan_vertex( CGAL_File_scanner_OFF& scanner,
                      CGAL_Point_3<float,float>& p,
                      CGAL_Rational_tag, float*) {
    scanner.scan_vertex( p.hx(), p.hy(), p.hz(), p.rw());
    return p;
}

inline CGAL_Point_3<double,double>&
CGAL_file_scan_vertex( CGAL_File_scanner_OFF& scanner,
                      CGAL_Point_3<double,double>& p,
                      CGAL_Rational_tag, double*) {
    scanner.scan_vertex( p.hx(), p.hy(), p.hz(), p.rw());
    return p;
}

inline CGAL_Point_3<double,int>&
CGAL_file_scan_vertex( CGAL_File_scanner_OFF& scanner,
                      CGAL_Point_3<double,int>& p,
                      CGAL_Rational_tag, int*) {
    scanner.scan_vertex( p.hx(), p.hy(), p.hz(), p.rw());
    return p;
}

template < class Pt> inline
Pt&
CGAL_file_scan_vertex( CGAL_File_scanner_OFF& scanner, Pt& p) {
    typedef typename Pt::RT  RT;
    return CGAL_file_scan_vertex( scanner, p, CGAL_query_representation(p),
                                 (RT*)(0));
}

template < class V, class RT> inline
V&
CGAL_file_scan_normal( CGAL_File_scanner_OFF& scanner, V& v,
                      CGAL_Cartesian_tag, RT*) {
    double x, y, z;
    scanner.scan_normal( x, y, z);
    v = V( RT(x), RT(y), RT(z));
    return v;
}

inline CGAL_Vector_3<float>&
CGAL_file_scan_normal( CGAL_File_scanner_OFF& scanner,
                      CGAL_Vector_3<float>& v,
                      CGAL_Cartesian_tag,
                      float*) {
    scanner.scan_normal( v.x(), v.y(), v.z());
    return v;
}

inline CGAL_Vector_3<double>&
CGAL_file_scan_normal( CGAL_File_scanner_OFF& scanner,
                      CGAL_Vector_3<double>& v,
                      CGAL_Cartesian_tag, double*) {
    scanner.scan_normal( v.x(), v.y(), v.z());
    return v;
}

inline CGAL_Vector_3<int>&
CGAL_file_scan_normal( CGAL_File_scanner_OFF& scanner,
                      CGAL_Vector_3<int>& v,
                      CGAL_Cartesian_tag,
                      int*) {
    scanner.scan_normal( v.x(), v.y(), v.z());
    return v;
}

template < class V, class RT> inline
V&
CGAL_file_scan_normal( CGAL_File_scanner_OFF& scanner, V& v,
                      CGAL_Rational_tag, RT*) {
    double x, y, z, w;
    scanner.scan_normal( x, y, z, w);
    v = V( RT(x), RT(y), RT(z), RT(w));
    return v;
}

inline CGAL_Vector_3<float,float>&
CGAL_file_scan_normal( CGAL_File_scanner_OFF& scanner,
                      CGAL_Vector_3<float,float>& v,
                      CGAL_Rational_tag, float*) {
    scanner.scan_normal( v.hx(), v.hy(), v.hz(), v.rw());
    return v;
}

inline CGAL_Vector_3<double,double>&
CGAL_file_scan_normal( CGAL_File_scanner_OFF& scanner,
                      CGAL_Vector_3<double,double>& v,
                      CGAL_Rational_tag, double*) {
    scanner.scan_normal( v.hx(), v.hy(), v.hz(), v.rw());
    return v;
}

inline CGAL_Vector_3<double,int>&
CGAL_file_scan_normal( CGAL_File_scanner_OFF& scanner,
                      CGAL_Vector_3<double,int>& v,
                      CGAL_Rational_tag, int*) {
    scanner.scan_normal( v.hx(), v.hy(), v.hz(), v.rw());
    return v;
}

template < class V> inline
V&
CGAL_file_scan_normal( CGAL_File_scanner_OFF& scanner, V& v) {
    typedef typename V::RT  RT;
    return CGAL_file_scan_normal( scanner, v,
                                 CGAL_query_representation(v),
                                 (RT*)(0));
}

#endif // CGAL_IO_FILE_SCANNER_OFF_H //
#endif // CGAL_IO_FILE_SCANNER_OFF_H //
// EOF //
