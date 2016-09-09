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

#ifndef CGAL_TRIANGULATION_FACE_CIRCULATOR_H
#define CGAL_TRIANGULATION_FACE_CIRCULATOR_H

#include <iterator.h>
#include <CGAL/Circulator.h>


template < class Vertex, class Face >
class CGAL_Triangulation_face_circulator :
    public CGAL_Bidirectional_circulator_base<Face*,ptrdiff_t> {
public:
    static int ccw(int i)
    {
        return (i+1) % 3;
    }


    static int cw(int i)
    {
        return (i+2) % 3;
    }
        typedef CGAL_Triangulation_face_circulator<Vertex, Face> Face_circulator;
        typedef Face *         value_type;
        typedef Face * &       reference;
        typedef const Face * & const_reference;
        typedef unsigned int   size_type;
        typedef int            distance_type;
        CGAL_Triangulation_face_circulator()
          : _v(NULL), _f(NULL)
        {}
        
        
        CGAL_Triangulation_face_circulator(Vertex *v, Face *f)
          : _v(v), _f(f)
        {}
        
        
        CGAL_Triangulation_face_circulator(const Face_circulator &fc)
          : _v(fc._v), _f(fc._f)
        {}
        
        
        CGAL_Triangulation_face_circulator &operator=(const Face_circulator &fc)
        {
            _v = fc._v;
            _f = fc._f;
            return *this;
        }
        Face_circulator& operator++()
        {
            CGAL_kernel_precondition( (_f != NULL) && (_v != NULL) );
            int i = _f->index(_v);
            _f = _f->neighbor(ccw(i));
            if(_f == NULL){
                _f = _v->face();
            }
            return *this;
        }
        
        Face_circulator operator++(int)
        {
            CGAL_kernel_precondition( (_f != NULL) && (_v != NULL) );
            Face_circulator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        
        Face_circulator& operator--()
        {
            CGAL_kernel_precondition( (_f != NULL) && (_v != NULL) );
            int i = _f->index(_v);
            Face *f = _f->neighbor(cw(i));
            if(f == NULL){
                Face* n;
                do{
                    i = _f->index(_v);
                    n = _f->neighbor(cw(i));
                    if(n != NULL){
                        _f = n;
                    }
                }while(n != NULL);
            }else{
                _f = f;
            }
            return *this;
        }
        
        
        Face_circulator operator--(int)
        {
            CGAL_kernel_precondition( (_f != NULL) && (_v != NULL) );
            Face_circulator tmp(*this);
            --(*this);
            return tmp;
        }
        Face* operator*()
        {
            CGAL_kernel_precondition( (_f != NULL) && (_v != NULL) );
            return _f;
        }
        
        
        bool operator==(const Face_circulator &fc) const
        {
            return (_v == fc._v) &&  (_f == fc._f);
        }
        
        
        bool operator!=(const Face_circulator &fc) const
        {
            return ! (*this == fc);
        }
        
        
        bool
        operator==(CGAL_NULL_TYPE n) const
        {
            CGAL_kernel_assertion( n == NULL);
            return (_v == NULL) && (_f == NULL);
        }
        
        bool
        operator!=(CGAL_NULL_TYPE n) const
        {
            CGAL_kernel_assertion( n == NULL);
            return ! (*this == NULL);
        }
        
private:
        
        
        Vertex* _v;
        Face* _f;
        
};

#endif // CGAL_TRIANGULATION_FACE_CIRCULATOR_H
