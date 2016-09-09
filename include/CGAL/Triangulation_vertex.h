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

#ifndef CGAL_TRIANGULATION_VERTEX_H
#define CGAL_TRIANGULATION_VERTEX_H

template <class V >
class CGAL_Triangulation_face;

template <class Vertex, class Face >
class CGAL_Triangulation_vertex_circulator;


template <class Vertex, class Face >
class CGAL_Triangulation_face_circulator;


template < class P >
class CGAL_Triangulation_vertex {
public:
    typedef P Point;
    typedef CGAL_Triangulation_vertex<Point> Vertex;
    typedef CGAL_Triangulation_face< CGAL_Triangulation_vertex<Point> > Face;
    typedef CGAL_Triangulation_vertex_circulator<Vertex,Face> Vertex_circulator;
    typedef CGAL_Triangulation_face_circulator<Vertex,Face> Face_circulator;
    
    CGAL_Triangulation_vertex()
        : _f(NULL)
    {}
    
    CGAL_Triangulation_vertex(const Point & p)
        :  _p(p), _f(NULL)
    {}
    
    CGAL_Triangulation_vertex(const Point & p, Face *f)
        :  _p(p), _f(f)
    {}
    
    ~CGAL_Triangulation_vertex()
    {}
    void
    set_point(const Point & p)
    {
        _p = p;
    }
    
    
    void
    set_face(Face *f)
    {
        _f = f;
    }
    Point
    point() const
    {
        return _p;
    }
    
    
    Face*
    face() const
    {
        return _f;
    }
    
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
    
    bool
    is_on_boundary() const
    {
        Vertex * ncthis = (Vertex*)this;
        Face *f = face();
        int i = f->index(ncthis);
        return f->neighbor(cw(i)) == NULL;
    }
    
    int
    degree() const
    {
        Vertex * ncthis = (Vertex*)this;
        Face *f = face();
    
        if (f == NULL) {
            return 0;
        }
        int i = f->index(ncthis);
    
        Face *ptr1 = f->neighbor(ccw(i)),
             *ptr2 = f;
        f = f->neighbor(cw(i));
    
        int count = 2;
    
        while(ptr1 != f){
            count++;
            i = ptr1->index(ptr2);
            ptr2 = ptr1;
            ptr1 = ptr1->neighbor(cw(i));
        }
        return count;
    }
    
    Vertex_circulator
    incident_vertices()
    {
        return Vertex_circulator(this, face());
    }
    
    
    Face_circulator
    incident_faces()
    {
        return Face_circulator(this, face());
    }
    
    
    Face_circulator
    incident_faces(Face *f)
    {
        return Face_circulator(this, f);
    }
    
private:
    
    private:
        Point _p;
        Face * _f;
    
};

#endif // CGAL_TRIANGULATION_H
