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
// file          : include/CGAL/Triangulation_edge_circulator.h
// package       : Triangulation (1.23)
// source        : web/Triangulation_edge_circulator.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1998/02/04 16:38:50 $
// author(s)     : Olivier Devillers
//                 Andreas Fabri
//
// coordinator   : Herve Bronnimann
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGULATION_EDGE_CIRCULATOR_H
#define CGAL_TRIANGULATION_EDGE_CIRCULATOR_H

#include <pair.h>
#include <iterator.h>
#include <CGAL/circulator.h>
#include <CGAL/triangulation_assertions.h>

template < class Vertex, class Face >
class CGAL_Triangulation_edge_circulator :
    public CGAL_Bidirectional_circulator_base<
                    pair<typename Face::Face_handle,int>,ptrdiff_t,size_t>
{
public:
    typedef typename Vertex::Vertex_handle Vertex_handle;
    typedef typename Face::Face_handle Face_handle;


    static int ccw(int i)
    {
        return (i+1) % 3;
    }


    static int cw(int i)
    {
        return (i+2) % 3;
    }
        typedef CGAL_Triangulation_edge_circulator<Vertex, Face> edge_circulator;
        typedef pair<Face_handle,int>         Edge;
        typedef Edge                          value_type;
        typedef Edge&       reference;
        typedef const Edge& const_reference;
        typedef unsigned int     size_type;
        typedef int              distance_type;
        CGAL_Triangulation_edge_circulator()
          : _v(NULL), _f(NULL)
        {}
        
        
        CGAL_Triangulation_edge_circulator(const Vertex_handle& v,
                                           const Face_handle&   f)
          : _v(v), _f(f)
        {
            if( _f != NULL ){
                int i = _f->index(_v);
                _ri = ccw(i);
            }
        }
        
        
        CGAL_Triangulation_edge_circulator(const edge_circulator &vc)
          : _ri(vc._ri), _v(vc._v), _f(vc._f)
        {}
        
        
        edge_circulator &operator=(const edge_circulator &vc)
        {
            _v = vc._v;
            _ri = vc._ri;
            _f = vc._f;
            return *this;
        }
        
        edge_circulator& operator++()
        {
            Face_handle n = _f;
            int i = _f->index(_v);
            n = _f->neighbor(ccw(i));
            if(n == NULL){
                if(_ri == ccw(i)){
                    _ri = cw(i);
                } else {
                    _f = _v->face();
                    i = _f->index(_v);
                    _ri = ccw(i);
                }
            } else {
                _f = n;
                i = _f->index(_v);
                _ri = ccw(i);
            }
          return *this;
        }
        
        
        edge_circulator operator++(int)
        {
            edge_circulator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        
        edge_circulator& operator--()
        {
            Face_handle n = _f;
            int i = _f->index(_v);
            n = _f->neighbor(cw(i));
            if(n == NULL){
                do{
                    n = _f->neighbor(ccw(i));
                    if(n != NULL){
                        _f = n;
                        i = _f->index(_v);
                    }
                }while(n != NULL);
                i = _f->index(_v);
                _ri = cw(i);
            } else {
                if(_ri == cw(i)){
                    _ri = ccw(i);
                } else {
                    _f = n;
                    i = _f->index(_v);
                    _ri = ccw(i);
                }
            }
            return *this;
        }
        
        
        edge_circulator operator--(int)
        {
            edge_circulator tmp(*this);
            --(*this);
            return tmp;
        }
        
        
        Edge
        operator*()
        {
            if( _f == NULL) {
                return make_pair(Face_handle(), 0);
            }
            return make_pair(_f, _ri);
        }
        
        bool operator==(const edge_circulator &vc) const
        {
            return (_v == vc._v) &&  (_ri == vc._ri) && (_f == vc._f);
        }
        
        
        bool operator!=(const edge_circulator &vc) const
        {
            return ! (*this == vc);
        }
        
        
        bool operator==(CGAL_NULL_TYPE n) const
        {
            CGAL_triangulation_assertion( n == NULL);
            return (_v == NULL) && (_f == NULL);
        }
        
        
        bool operator!=(CGAL_NULL_TYPE n) const
        {
            CGAL_triangulation_assertion( n == NULL);
            return !(*this == NULL);
        }
        
private:
        
        int _ri;
        Vertex_handle _v;
        Face_handle _f;
        
};

#endif // CGAL_TRIANGULATION_EDGE_CIRCULATOR_H
