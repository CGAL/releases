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
// release_date  : 1998, July 24
//
// file          : include/CGAL/IO/Generic_writer.h
// package       : Polyhedron_IO (1.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1998/06/03 20:34:54 $
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
#ifndef CGAL_PROTECT_ITERATOR_H
#include <iterator.h>
#define CGAL_PROTECT_ITERATOR_H
#endif // CGAL_PROTECT_ITERATOR_H

template < class Writer, class Pt >
class CGAL__Vertex_output_proxy {
    Writer&  _writer;
public:
    CGAL__Vertex_output_proxy( Writer& writer) : _writer(writer) {}
    void
    operator= ( const Pt& p) {
#ifdef CGAL_IO_GENERIC_WRITER
    _writer.write_vertex( CGAL_to_double(p.x()),
                          CGAL_to_double(p.y()),
                          CGAL_to_double(p.z()));
#else
        _writer.write_vertex( double(p.x()), double(p.y()), double(p.z()));
#endif
    }
};

template < class Writer, class Pt >
class CGAL__Vertex_output_iterator : public output_iterator {
    Writer&  _writer;
    size_t   _cnt;
    size_t   _max;
public:
    typedef Pt   Point;
    typedef CGAL__Vertex_output_proxy< Writer, Pt>  Proxy;

    CGAL__Vertex_output_iterator( Writer& writer, size_t v)
        : _writer( writer), _cnt(0), _max(v) {}
    CGAL__Vertex_output_iterator< Writer, Pt>&
    operator++() {
        CGAL_assertion( _cnt < _max);
        _cnt++;
        return *this;
    }
    CGAL__Vertex_output_iterator< Writer, Pt>&
    operator++(int) {
        CGAL_assertion( _cnt < _max);
        ++(*this);
        return *this;
    }
    Proxy
    operator*() const {
        CGAL_assertion( _cnt <= _max);
        return Proxy( _writer);
    }
};

template < class Writer >  class CGAL__Facet_output_iterator;

template < class Writer >
class CGAL__Facet_output_proxy {
    const CGAL__Facet_output_iterator< Writer> &  _foi;
public:
    CGAL__Facet_output_proxy( const CGAL__Facet_output_iterator<Writer>&
                             foi)
        : _foi(foi) {}
    inline
    void  operator= ( size_t i);
};


template < class Writer >
class CGAL__Facet_output_iterator : public output_iterator {
    friend class CGAL__Facet_output_proxy<Writer>;

    Writer& _writer;
    size_t  _fcnt;
    size_t  _icnt;

public:
    typedef  CGAL__Facet_output_proxy<Writer>  Proxy;
    CGAL__Facet_output_iterator( Writer& writer, size_t f)
    : _writer( writer), _fcnt(f), _icnt(0)
    {
        if ( f == 0)
            _writer.footer();
    }
    CGAL__Facet_output_iterator< Writer >&
    operator++()    { return *this; }
    CGAL__Facet_output_iterator< Writer >&
    operator++(int) { return *this; }
    Proxy
    operator*() const {
        CGAL_assertion( _fcnt > 0);
        return Proxy( *this);
    }
};

template < class Writer >
inline
void  CGAL__Facet_output_proxy< class Writer >::
operator= ( size_t i) {
    if (_foi._icnt == 0) {
        _foi._writer.write_facet_begin( i);
        ((CGAL__Facet_output_iterator< Writer >&)(_foi))._icnt = i;
    } else {
        _foi._writer.write_facet_vertex_index( i);
        ((CGAL__Facet_output_iterator< Writer >&)(_foi))._icnt --;
        if (_foi._icnt == 0) {
            _foi._writer.write_facet_end();
            ((CGAL__Facet_output_iterator< Writer >&)(_foi))._fcnt --;
            if (_foi._fcnt == 0)
                _foi._writer.footer();
        }
    }
}


template < class Writer, class Pt >
class CGAL_Generic_writer {
    Writer  _writer;
    size_t  _vertices;
    size_t  _halfedges;
    size_t  _facets;

public:
    typedef Pt                                      Point;
    typedef CGAL__Vertex_output_iterator<Writer,Pt>  Vertex_iterator;
    typedef CGAL__Facet_output_iterator<Writer>      Facet_iterator;

    CGAL_Generic_writer( const Writer& writer, ostream& out,
                        size_t v, size_t h, size_t f)
    : _writer( writer), _vertices(v), _halfedges(h), _facets(f) {
        _writer.header( out, v, h, f);
    }
    const Writer& writer()     const  { return _writer;    }
    size_t size_of_vertices()  const  { return _vertices;  }
    size_t size_of_halfedges() const  { return _halfedges; }
    size_t size_of_facets()    const  { return _facets;    }

    Vertex_iterator  vertices_begin() {
                         return Vertex_iterator( _writer, _vertices);
    }
    Facet_iterator   facets_begin() {
                         _writer.write_facet_header();
                         return Facet_iterator( _writer, _facets);
    }
};
#endif // CGAL_IO_GENERIC_WRITER_H //
// EOF //
