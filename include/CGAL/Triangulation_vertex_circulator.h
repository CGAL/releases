// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Triangulation_vertex_circulator.h
// author(s)     : Andreas Fabri
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_TRIANGULATION_VERTEX_CIRCULATOR_H
#define CGAL_TRIANGULATION_VERTEX_CIRCULATOR_H

#include <iterator.h>
#include <CGAL/circulator.h>
#include <CGAL/triangulation_assertions.h>

template < class Vertex, class Face >
class CGAL_Triangulation_vertex_circulator :
    public CGAL_Bidirectional_circulator_base<Vertex,ptrdiff_t,size_t>,
    public Vertex::Vertex_handle {
public:

    static int ccw(int i)
    {
        return (i+1) % 3;
    }


    static int cw(int i)
    {
        return (i+2) % 3;
    }
        typedef CGAL_Triangulation_vertex_circulator<Vertex, Face> Vertex_circulator;
        typedef Vertex           value_type;
        typedef Vertex   &       reference;
        typedef const Vertex   & const_reference;
        typedef unsigned int     size_type;
        typedef int              distance_type;
        
        typedef typename Vertex::Vertex_handle Vertex_handle;
        typedef typename Face::Face_handle Face_handle;
        CGAL_Triangulation_vertex_circulator()
          : Vertex::Vertex_handle(), _v(), _f(NULL)
        {}
        
        
        CGAL_Triangulation_vertex_circulator(const Vertex_handle& v,
                                             const Face_handle&   f)
          : Vertex::Vertex_handle(), _v( v ), _f(f)
        {
            if( _f != NULL ){
                int i = _f->index( _v );
                _ri = ccw(i);
                ptr() = &(*_f->vertex(_ri));
            }
        }
        
        
        CGAL_Triangulation_vertex_circulator(const Vertex_circulator &vc)
          : Vertex::Vertex_handle(vc), _ri(vc._ri), _v(vc._v), _f(vc._f)
        {}
        
        
        Vertex_circulator &operator=(const Vertex_circulator &vc)
        {
            _v = vc._v;
            _ri = vc._ri;
            _f = vc._f;
            return *this;
        }
        
        Vertex_circulator& operator++()
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
          ptr() = &(*_f->vertex(_ri));
          return *this;
        }
        
        
        Vertex_circulator operator++(int)
        {
            Vertex_circulator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        
        Vertex_circulator& operator--()
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
            ptr() = &(*_f->vertex(_ri));
            return *this;
        }
        
        
        Vertex_circulator operator--(int)
        {
            Vertex_circulator tmp(*this);
            --(*this);
            return tmp;
        }
        
        bool operator==(const Vertex_circulator &vc) const
        {
            return (_v == vc._v) &&  (_ri == vc._ri) && (_f == vc._f);
        }
        
        
        bool operator!=(const Vertex_circulator &vc) const
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

#endif // CGAL_TRIANGULATION_VERTEX_CIRCULATOR_H
