/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

#ifndef CGAL_TRIANGULATION_VERTEX_CIRCULATOR_H
#define CGAL_TRIANGULATION_VERTEX_CIRCULATOR_H

#include <iterator.h>
#include <CGAL/Circulator.h>

template < class Vertex, class Face >
class CGAL_Triangulation_vertex_circulator :
    public CGAL_Bidirectional_circulator_base<Vertex*,ptrdiff_t> {
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
        typedef Vertex *         value_type;
        typedef Vertex * &       reference;
        typedef const Vertex * & const_reference;
        typedef unsigned int     size_type;
        typedef int              distance_type;
        CGAL_Triangulation_vertex_circulator()
          : _v(NULL), _f(NULL)
        {}
        
        
        CGAL_Triangulation_vertex_circulator(Vertex *v, Face *f)
          : _v(v), _f(f)
        {
            if( _f != NULL ){
                int i = _f->index(_v);
                _ri = ccw(i);
            }
        }
        
        
        CGAL_Triangulation_vertex_circulator(const Vertex_circulator &vc)
          : _ri(vc._ri), _v(vc._v), _f(vc._f)
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
            Face* n = _f;
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
        
        
        Vertex_circulator operator++(int)
        {
            Vertex_circulator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        
        Vertex_circulator& operator--()
        {
            Face* n = _f;
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
        
        
        Vertex_circulator operator--(int)
        {
            Vertex_circulator tmp(*this);
            --(*this);
            return tmp;
        }
        
        
        Vertex*
        operator*()
        {
            if( _f == NULL) {
                return NULL;
            }
            return _f->vertex(_ri);
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
            CGAL_kernel_assertion( n == NULL);
            return (_v == NULL) && (_f == NULL);
        }
        
        
        bool operator!=(CGAL_NULL_TYPE n) const
        {
            CGAL_kernel_assertion( n == NULL);
            return !(*this == NULL);
        }
        
private:
        
        int _ri;
        Vertex* _v;
        Face* _f;
        
};

#endif // CGAL_TRIANGULATION_VERTEX_CIRCULATOR_H
