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
// file          : include/CGAL/Triangulation_face_circulator.h
// author(s)     : Andreas Fabri
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
//
// coordinator   : Herve Bronnimann
//
// ============================================================================


#ifndef CGAL_TRIANGULATION_FACE_CIRCULATOR_H
#define CGAL_TRIANGULATION_FACE_CIRCULATOR_H

#include <iterator.h>
#include <CGAL/circulator.h>
#include <CGAL/triangulation_assertions.h>


template < class Vertex, class Face >
class CGAL_Triangulation_face_circulator
    : public CGAL_Bidirectional_circulator_base<Face,ptrdiff_t,size_t>
    , public Face::Face_handle  {
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
        typedef Face           value_type;
        typedef Face   &       reference;
        typedef const Face   & const_reference;
        typedef unsigned int   size_type;
        typedef int            distance_type;
        
        // BUG These typedef do not work
        typedef typename Vertex::Vertex_handle Vertex_handle;
        typedef typename Face::Face_handle Face_handle;
        CGAL_Triangulation_face_circulator()
          : Face::Face_handle(), _v(NULL)
        {}
        
        
        CGAL_Triangulation_face_circulator(const Vertex_handle& v,
                                           const Face_handle& f)
          : Face::Face_handle(f),_v(v)
        {}
        
        
        CGAL_Triangulation_face_circulator(const Face_circulator &fc)
          : Face::Face_handle(fc),_v(fc._v)
        {}
        
        
        CGAL_Triangulation_face_circulator &operator=(const Face_circulator &fc)
        {
            _v = fc._v;
            ptr() = fc->ptr();
            return *this;
        }
        Face_circulator& operator++()
        {
            CGAL_triangulation_precondition( (ptr() != NULL) && (_v != NULL) );
            int i = ptr()->index(_v);
            ptr() = &(*ptr()->neighbor(ccw(i)));
            if(ptr() == NULL){
                ptr() = &(*_v->face());
            }
            return *this;
        }
        
        Face_circulator operator++(int)
        {
            CGAL_triangulation_precondition( (ptr() != NULL) && (_v != NULL) );
            Face_circulator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        
        Face_circulator& operator--()
        {
            CGAL_triangulation_precondition( (ptr() != NULL) && (_v != NULL) );
            int i = ptr()->index(_v);
            Face_handle f = ptr()->neighbor(cw(i));
            if(f == NULL){
                Face_handle n;
                do{
                    i = ptr()->index(_v);
                    n = ptr()->neighbor(cw(i));
                    if(n != NULL){
                        ptr() = &(*n);
                    }
                }while(n != NULL);
            }else{
                ptr() = &(*f);
            }
            return *this;
        }
        
        
        Face_circulator operator--(int)
        {
            CGAL_triangulation_precondition( (ptr() != NULL) && (_v != NULL) );
            Face_circulator tmp(*this);
            --(*this);
            return tmp;
        }
        
        
        bool operator==(const Face_circulator &fc) const
        {
            return (_v == fc._v) &&  (ptr() == fc.ptr());
        }
        
        
        bool operator!=(const Face_circulator &fc) const
        {
            return ! (*this == fc);
        }
        
        
        bool
        operator==(CGAL_NULL_TYPE n) const
        {
            CGAL_triangulation_assertion( n == NULL);
            return (_v == NULL) && (ptr() == NULL);
        }
        
        bool
        operator!=(CGAL_NULL_TYPE n) const
        {
            CGAL_triangulation_assertion( n == NULL);
            return ! (*this == NULL);
        }
        
private:
        
        
        Vertex_handle _v;
        
};

#endif // CGAL_TRIANGULATION_FACE_CIRCULATOR_H
