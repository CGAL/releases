// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/IO/Generic_writer.h
// package       : Polyhedron_IO (2.5)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1999/03/24 11:16:26 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Generic STL compliant interface to write boundary rep file formats.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_GENERIC_WRITER_H
#define CGAL_IO_GENERIC_WRITER_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_PROTECT_ITERATOR
#include <iterator>
#define CGAL_PROTECT_ITERATOR
#endif

CGAL_BEGIN_NAMESPACE

template <class Writer>
class _Generic_writer_vertex_proxy {
    Writer&  m_writer;
public:
    typedef typename Writer::Point Point;
    _Generic_writer_vertex_proxy( Writer& w) : m_writer(w) {}
    void operator= ( const Point& p) { m_writer.write_vertex(p); }
};

template <class Writer>
class _Generic_writer_vertex_iterator : public std::output_iterator {
    Writer&  m_writer;
public:
    typedef _Generic_writer_vertex_proxy< Writer>    Proxy;
    typedef _Generic_writer_vertex_iterator< Writer> Self;

    _Generic_writer_vertex_iterator( Writer& w) : m_writer(w) {}
    Self& operator++()      { return *this; }
    Self& operator++(int)   { return *this; }
    Proxy operator*() const { return Proxy( m_writer); }
};

template <class Writer>
class _Generic_writer_facet_proxy {
    Writer&  m_writer;
public:
    _Generic_writer_facet_proxy( Writer& w) : m_writer(w) {}
    void operator= ( std::size_t i) { m_writer.write_facet_index(i); }
};

template <class Writer>
class _Generic_writer_facet_iterator : public std::output_iterator {
    Writer& m_writer;
public:
    typedef  _Generic_writer_facet_proxy<Writer>    Proxy;
    typedef  _Generic_writer_facet_iterator<Writer> Self;

    _Generic_writer_facet_iterator( Writer& w) : m_writer(w) {}
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
class Generic_writer {
    Writer       m_writer;
    std::size_t  m_vertices;
    std::size_t  m_halfedges;
    std::size_t  m_facets;

    std::size_t  m_vcnt;
    std::size_t  m_fcnt;
    std::size_t  m_icnt;
public:
    typedef Pt                                     Point;
    typedef Generic_writer< Writer, Pt>            Self;
    typedef _Generic_writer_vertex_iterator<Self>  Vertex_iterator;
    typedef _Generic_writer_facet_iterator<Self>   Facet_iterator;

    Generic_writer( const Writer& writer, std::ostream& out,
                    std::size_t v, std::size_t h, std::size_t f)
        : m_writer( writer), m_vertices(v), m_halfedges(h), m_facets(f),
          m_vcnt(0), m_fcnt(0), m_icnt(0)
    {
        m_writer.write_header( out, v, h, f);
    }
    const Writer& writer()            const  { return m_writer;    }
    std::size_t   size_of_vertices()  const  { return m_vertices;  }
    std::size_t   size_of_halfedges() const  { return m_halfedges; }
    std::size_t   size_of_facets()    const  { return m_facets;    }

    Vertex_iterator  vertices_begin() { return Vertex_iterator( *this); }
    Facet_iterator   facets_begin() {
        if ( m_vcnt != m_vertices) {
            std::cerr << "error: Generic_writer: wrong number of "
                         "vertices written, " << m_vcnt << " instead of "
                      << m_vertices << "." << std::endl;
            m_writer.out().clear( std::ios::badbit);
        }
        m_writer.write_facet_header();
        if ( m_facets == 0)
            m_writer.write_footer();
        return Facet_iterator( *this);
    }

    // Interface used by the iterators and their proxies.
    void write_vertex( const Point& p) {
        ++m_vcnt;
        m_writer.write_vertex( to_double( p.x()),
                               to_double( p.y()),
                               to_double( p.z()));
    }
    void write_facet_index( std::size_t i) {
        if ( m_fcnt > m_facets) {
            std::cerr << "error: Generic_writer: too many facets written."
                      << std::endl;
            m_writer.out().clear( std::ios::badbit);
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

CGAL_END_NAMESPACE
#endif // CGAL_IO_GENERIC_WRITER_H //
// EOF //
