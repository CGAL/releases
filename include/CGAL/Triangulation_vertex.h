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
// file          : include/CGAL/Triangulation_vertex.h
// package       : Triangulation (1.23)
// source        : web/Triangulation_vertex.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/03/05 14:14:57 $
// author(s)     : Olivier Devillers
//                 Andreas Fabri
//
// coordinator   : Herve Bronnimann
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGULATION_VERTEX_H
#define CGAL_TRIANGULATION_VERTEX_H

#include <CGAL/Pointer.h>

template <class P >
class CGAL_Triangulation_Vertex;

template <class V >
class CGAL_Triangulation_face;

template <class Vertex, class Face >
class CGAL_Triangulation_vertex_circulator;

template <class Vertex, class Face >
class CGAL_Triangulation_edge_circulator;


template <class Vertex, class Face >
class CGAL_Triangulation_face_circulator;

template < class P >
class CGAL_Triangulation_vertex {

public:
    typedef P Point;
    typedef CGAL_Triangulation_vertex<Point> Vertex;
    typedef CGAL_Triangulation_face<Vertex>  Face;
    typedef CGAL_Pointer<Vertex>             Vertex_handle;
    typedef typename Face::Face_handle       Face_handle;
    typedef CGAL_Triangulation_vertex_circulator<Vertex,Face> Vertex_circulator;
    typedef CGAL_Triangulation_edge_circulator<Vertex,Face>   Edge_circulator;
    typedef CGAL_Triangulation_face_circulator<Vertex,Face>   Face_circulator;
    CGAL_Triangulation_vertex()
        : _f(NULL)
    {}
    
    CGAL_Triangulation_vertex(const Point & p)
        :  _p(p), _f(NULL)
    {}
    
    CGAL_Triangulation_vertex(const Point & p, Face_handle f)
        :  _p(p), _f(f)
    {}
    inline void set_point(const Point & p)
    {
        _p = p;
    }
    
    inline void set_face(const Face_handle& f)
    {
        _f = f;
    }
    inline Point point() const
    {
        return _p;
    }
    
    
    inline const Face_handle& face() const
    {
        return _f;
    }
    
    static int ccw(int i)
    {
        return (i+1) % 3;
    }
    
    
    static int cw(int i)
    {
        return (i+2) % 3;
    }
    
    bool is_on_boundary() const
    {
        Face_handle f = face();
        int i = f->index(handle());
        return f->neighbor(cw(i)) == NULL;
    }
    
    inline Vertex_handle handle() const
    {
        return Vertex_handle(this);
    }
    
    int degree() const
    {
        Face_handle f = face();
    
        if (f == NULL) {
            return 0;
        }
        int i = f->index(handle());
    
        Face_handle ptr1 = f->neighbor(ccw(i));
        Face_handle ptr2 = f;
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
    
    inline Vertex_circulator incident_vertices()
    {
        return Vertex_circulator(handle(), face());
    }
    
    
    inline Face_circulator incident_faces()
    {
        return Face_circulator(this, face());
    }
    
    
    inline Face_circulator incident_faces(const Face_handle& f)
    {
        return Face_circulator(this, f);
    }
    
    inline Edge_circulator incident_edges()
    {
        return Edge_circulator(this, face());
    }
    
    
    inline Edge_circulator incident_edges(const Face_handle& f)
    {
        return Edge_circulator(this, f);
    }
    
private:
    
    private:
        Point _p;
        Face_handle _f;
    
};

#endif // CGAL_TRIANGULATION_H
