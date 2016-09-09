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
// chapter       : $CGAL_Chapter: Optimisation $
// file          : include/CGAL/Rep_distinguisher.h
// package       : Min_sphere_d (1.9)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1998/07/01 10:00:10 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zurich (Bernd Gärtner)
//
// implementation: dD Smallest Enclosing Sphere
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_REP_DISTINGUISHER_H
#define CGAL_REP_DISTINGUISHER_H

// Class Declaration
// =================
// includes
#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif // CGAL_REP_CLASS_DEFINED

// Class interface and implementation
// ==================================
template < class C, class H, class Rep_tag >
class CGAL_Rep_distinguisher
{
    private:
        void *p;

    public:
        // Construction
        CGAL_Rep_distinguisher()
        {
            init (Rep_tag());
        }
        void init (CGAL_Cartesian_tag t)
        {
            p = new C;
        }
        void init (CGAL_Homogeneous_tag t)
        {
            p = new H;
        }

        // copy constructor
        CGAL_Rep_distinguisher (const CGAL_Rep_distinguisher& rd)
        {
            init (Rep_tag());
        }

        // assignment operator
        CGAL_Rep_distinguisher& operator=(const CGAL_Rep_distinguisher& rd)
        {
            delete ptr(Rep_tag());
            init (Rep_tag());
            return (*this);
        }

        // Destruction
        ~CGAL_Rep_distinguisher()
        {
            delete ptr(Rep_tag());
        }

        // ptr methods
        C* ptr (CGAL_Cartesian_tag)
        {
            return (C*)p;
        }
        H* ptr (CGAL_Homogeneous_tag)
        {
            return (H*)p;
        }
        const C* ptr (CGAL_Cartesian_tag) const
        {
            return (const C*)p;
        }
        const H* ptr (CGAL_Homogeneous_tag) const
        {
            return (const H*)p;
        }
};



#endif // CGAL_REP_DISTINGUISHER_H

// ===== EOF ==================================================================

