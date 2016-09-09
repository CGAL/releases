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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Triangulation_vertex_base_2.h
// package       : Triangulation (2.10)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_vertex_base_2.h,v $
// revision      : $Revision: 1.3.1.4 $
// revision_date : $Date: 1998/12/03 17:15:36 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGULATION_VERTEX_BASE_2_H
#define CGAL_TRIANGULATION_VERTEX_BASE_2_H

#include <CGAL/Triangulation_short_names_2.h>

template < class GT >
class CGAL_Triangulation_vertex_base_2 {

public:
    typedef typename GT::Point Point;


  CGAL_Triangulation_vertex_base_2 ()
        : _f(NULL)
    {}
    
    CGAL_Triangulation_vertex_base_2(const Point & p)
        :  _p(p), _f(NULL)
    {}
    
    CGAL_Triangulation_vertex_base_2(const Point & p, void* f)
        :  _p(p), _f(f)
    {}

    inline void set_point(const Point & p)
    {
        _p = p;
    }
    
    inline void set_face(void* f)
    {
        _f = f;
    }

    inline 
    const Point&  point() const
    {
        return _p;
    }
    
    
    inline void* face() const
    {
        return _f;
    }
    
  //the following trivial is_valid to allow
  // the user of derived face base classes 
  // to add their own purpose checking
  bool is_valid() const
  {return true;}

private:
        Point _p;
        void * _f;

};

#endif //CGAL_TRIANGULATION_VERTEX_BASE_2_H
