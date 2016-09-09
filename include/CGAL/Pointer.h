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
// file          : include/CGAL/Pointer.h
// package       : Triangulation (2.10)
// source        : $RCSfile: Pointer.h,v $
// revision      : $Revision: 1.1.2.2 $
// revision_date : $Date: 1998/11/06 18:16:36 $
// author(s)     : Olivier Devillers, Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================



#ifndef CGAL_POINTER_H
#define CGAL_POINTER_H

#include <assert.h>
#include <iterator.h>
#include <CGAL/circulator.h>

template<class T>
class CGAL_Pointer
{

    private:
    T* _pointer;
    
    public:
    typedef T value_type;
    typedef CGAL_Pointer<T> Pointer;
    inline CGAL_Pointer()
        : _pointer(NULL)
    {}
    
    inline CGAL_Pointer(const T* p)
        : _pointer((T*)p)
    {}
    
    inline Pointer& operator=(const T*& p)
    {
        ptr() = p ;
        return *this;
    }
    
    inline Pointer& operator=(const Pointer& p)
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
    
    
    inline bool operator==(const Pointer& p) const
    {
        return ( ptr() == p.ptr() );
    }
    
    inline bool operator!=(const Pointer& p) const
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

#endif // CGAL_POINTER_H
