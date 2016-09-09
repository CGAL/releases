// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Pointer.h
// package       : Triangulation (3.17)
// source        : $RCSfile: Pointer.h,v $
// revision      : $Revision: 1.1.2.4 $
// revision_date : $Date: 1999/03/11 13:22:59 $
// author(s)     : Olivier Devillers, Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================



#ifndef CGAL_POINTER_H
#define CGAL_POINTER_H

#include <cassert>
#include <iterator>
#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE 

template<class T>
class Pointer
{

    private:
    T* _pointer;
    
    public:
    typedef T value_type;
  //typedef Pointer<T> Pointer;

    inline Pointer<T>()
        : _pointer(NULL)
    {}
    
    inline Pointer<T>(const T* p)
        : _pointer((T*)p)
    {}
    
    inline Pointer<T>& operator=(const T*& p)
    {
        ptr() = p ;
        return *this;
    }
    
    inline Pointer<T>& operator=(const Pointer<T>& p)
    {
        ptr() = p.ptr();
        return *this;
    }
    inline T& operator*() const
    {
        return *ptr();
    }
    
    inline T* operator->() const
    {
        return ptr();
    }
    inline void Delete()
    {
        delete ptr();
        clear();
    }
    
    inline void clear()
    {
        ptr() = NULL;
    }
    
    
    inline bool operator==(const Pointer<T>& p) const
    {
        return ( ptr() == p.ptr() );
    }
    
    inline bool operator!=(const Pointer<T>& p) const
    {
        return !(*this == p);
    }
    
  inline bool is_null()
  {
    return (ptr() == NULL );
  }


  inline bool operator==(CGAL_NULL_TYPE n) const
    {
        assert( n == 0);
        return ( ptr() == NULL );
    }
    
    inline bool operator!=(CGAL_NULL_TYPE n) const
    {
        return !(*this == n);
    }

 
    public:
    inline T*& ptr()       {return _pointer;}
    inline T*  ptr() const {return _pointer;}
    

};

CGAL_END_NAMESPACE

#endif // CGAL_POINTER_H
