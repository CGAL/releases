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
// file          : include/CGAL/IO/Generic_writer.h
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Generic STL compliant interface to write boundary rep file formats.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_GENERIC_WRITER_H
#define CGAL_IO_GENERIC_WRITER_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_PROTECT_ITERATOR_H
#include <iterator.h>
#define CGAL_PROTECT_ITERATOR_H
#endif // CGAL_PROTECT_ITERATOR_H

template <class Writer>
class CGAL__Generic_writer_vertex_proxy {
    Writer&  m_writer;
public:
    typedef typename Writer::Point Point;
    CGAL__Generic_writer_vertex_proxy( Writer& w) : m_writer(w) {}
    void operator= ( const Point& p) { m_writer.write_vertex(p); }
};

template <class Writer>
class CGAL__Generic_writer_vertex_iterator : public output_iterator {
    Writer&  m_writer;
public:
    typedef CGAL__Generic_writer_vertex_proxy< Writer>    Proxy;
    typedef CGAL__Generic_writer_vertex_iterator< Writer> Self;

    CGAL__Generic_writer_vertex_iterator( Writer& w) : m_writer(w) {}
    Self& operator++()      { return *this; }
    Self& operator++(int)   { return *this; }
    Proxy operator*() const { return Proxy( m_writer); }
};

template <class Writer>
class CGAL__Generic_writer_facet_proxy {
    Writer&  m_writer;
public:
    CGAL__Generic_writer_facet_proxy( Writer& w) : m_writer(w) {}
    void operator= ( size_t i) { m_writer.write_facet_index(i); }
};

template <class Writer>
class CGAL__Generic_writer_facet_iterator : public output_iterator {
    Writer& m_writer;
public:
    typedef  CGAL__Generic_writer_facet_proxy<Writer>    Proxy;
    typedef  CGAL__Generic_writer_facet_iterator<Writer> Self;

    CGAL__Generic_writer_facet_iterator( Writer& w) : m_writer(w) {}
    Self& operator++()      { return *this; }
    Self& operator++(int)   { return *this; }
    Proxy operator*() const { return Proxy( m_writer); }
};

// The Generic_writer class contains also the state necessary for all
// its iterators. Since these iterators are of the category
// output_iterator, they could not be used more than once and their
// positional state can be kept in Generic_writer, which simplifies
// the situation where the iterators are copied by value.

template < class Writer, class Pt >
class CGAL_Generic_writer {
    Writer  m_writer;
    size_t  m_vertices;
    size_t  m_halfedges;
    size_t  m_facets;

    size_t  m_vcnt;
    size_t  m_fcnt;
    size_t  m_icnt;
public:
    typedef Pt                                         Point;
    typedef CGAL_Generic_writer< Writer, Pt>            Self;
    typedef CGAL__Generic_writer_vertex_iterator<Self>  Vertex_iterator;
    typedef CGAL__Generic_writer_facet_iterator<Self>   Facet_iterator;

    CGAL_Generic_writer( const Writer& writer, ostream& out,
                        size_t v, size_t h, size_t f)
        : m_writer( writer), m_vertices(v), m_halfedges(h), m_facets(f),
          m_vcnt(0), m_fcnt(0), m_icnt(0)
    {
        m_writer.write_header( out, v, h, f);
    }
    const Writer& writer()     const  { return m_writer;    }
    size_t size_of_vertices()  const  { return m_vertices;  }
    size_t size_of_halfedges() const  { return m_halfedges; }
    size_t size_of_facets()    const  { return m_facets;    }

    Vertex_iterator  vertices_begin() { return Vertex_iterator( *this); }
    Facet_iterator   facets_begin() {
        if ( m_vcnt != m_vertices) {
            cerr << "error: CGAL_Generic_writer: wrong number of "
                    "vertices written, " << m_vcnt << " instead of "
                 << m_vertices << "." << endl;
            m_writer.out().clear( ios::badbit);
        }
        m_writer.write_facet_header();
        if ( m_facets == 0)
            m_writer.write_footer();
        return Facet_iterator( *this);
    }

    // Interface used by the iterators and their proxies.
    void write_vertex( const Point& p) {
        ++m_vcnt;
        m_writer.write_vertex( CGAL_to_double( p.x()),
                               CGAL_to_double( p.y()),
                               CGAL_to_double( p.z()));
    }
    void write_facet_index( size_t i) {
        if ( m_fcnt > m_facets) {
            cerr << "error: CGAL_Generic_writer: too many facets written."
                 << endl;
            m_writer.out().clear( ios::badbit);
        }
        if ( m_icnt == 0) {
            m_writer.write_facet_begin( i);
            m_icnt = i;
        } else {
            m_writer.write_facet_vertex_index( i);
            m_icnt --;
            if ( m_icnt == 0) {
                m_writer.write_facet_end();
                m_fcnt ++;
                if (m_fcnt == m_facets)
                    m_writer.write_footer();
            }
        }
    }
};
#endif // CGAL_IO_GENERIC_WRITER_H //
// EOF //
