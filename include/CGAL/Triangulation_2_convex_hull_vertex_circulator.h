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

#ifndef CGAL_TRIANGULATION_2_CONVEX_HULL_VERTEX_CIRCULATOR_H
#define CGAL_TRIANGULATION_2_CONVEX_HULL_VERTEX_CIRCULATOR_H

#include <iterator.h>
#include <CGAL/Circulator.h>

template <class Vertex, class Face>
class CGAL_Triangulation_2_convex_hull_vertex_circulator :
    public CGAL_Bidirectional_circulator_base<Vertex*, ptrdiff_t> {
public:
    static
    int
    ccw(int i)
    {
        return (i+1) % 3;
    }


    static
    int
    cw(int i)
    {
        return (i+2) % 3;
    }

    typedef CGAL_Triangulation_2_convex_hull_vertex_circulator<Vertex,Face>
                             Convex_hull_vertex_circulator;
    
    typedef Vertex *         value_type;
    typedef Vertex * &       reference;
    typedef const Vertex * & const_reference;
    typedef unsigned int     size_type;
    typedef int              distance_type;
    
    CGAL_Triangulation_2_convex_hull_vertex_circulator()
        : pos(NULL), f(NULL)
    {}
    
    
    ~CGAL_Triangulation_2_convex_hull_vertex_circulator()
    {}
    
    
    CGAL_Triangulation_2_convex_hull_vertex_circulator(Face* fa,
                                                       Vertex* ve)
        : pos(ve), f(fa)
    {
        CGAL_kernel_precondition( ve != NULL);
    }
    
    
    Convex_hull_vertex_circulator&
    operator=(const Convex_hull_vertex_circulator& chc)
    {
        f = chc.f;
        pos = chc.pos;
        return *this;
    }
    Convex_hull_vertex_circulator&
    operator++()
    {
        if(f != NULL){
            int i = f->index(pos);
            pos = f->vertex(ccw(i));
            f = f->neighbor(i);
        }
        return *this;
    }
    
    
    Convex_hull_vertex_circulator&
    operator--()
    {
        if(f != NULL){
            int i = f->index(pos);
            f = f->neighbor(ccw(i));
            i = cw(f->index(pos));
            pos = f->vertex(i);
        }
        return *this;
    }
    
    
    Convex_hull_vertex_circulator
    operator++(int)
    {
        Convex_hull_vertex_circulator tmp(*this);
        ++(*this);
        return tmp;
    }
    
    
    Convex_hull_vertex_circulator
    operator--(int)
    {
        Convex_hull_vertex_circulator tmp(*this);
        --(*this);
        return tmp;
    }
    Vertex*
    operator*() const
    {
        return pos;
    }
    
    
    bool
    operator==(const Convex_hull_vertex_circulator& chc) const
    {
        CGAL_kernel_precondition( pos != NULL  &&  chc.pos != NULL );
        return pos == chc.pos;
    }
    
    bool
    operator!=(const Convex_hull_vertex_circulator& chc) const
    {
        return pos != chc.pos;
    }
    
    
    bool
    operator==(CGAL_NULL_TYPE n) const
    {
        CGAL_kernel_assertion( n == NULL);
        return pos == NULL;
    }
    
    
    bool
    operator!=(CGAL_NULL_TYPE n) const
    {
        CGAL_kernel_assertion( n == NULL);
        return pos != NULL;
    }
    
private:
    Vertex *pos;
    Face *f;
    
};

#endif // CGAL_TRIANGULATION_2_CONVEX_HULL_VERTEX_CIRCULATOR_H
