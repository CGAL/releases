// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// chapter       : $CGAL_Chapter: Optimisation $
// file          : include/CGAL/Min_sphere_d_traits_d.h
// package       : Min_sphere_d (2.12)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 2.12 $
// revision_date : $Date: 1999/12/20 12:02:17 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zurich (Bernd Gärtner)
//
// implementation: dD Smallest Enclosing Sphere
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_MIN_SPHERE_D_TRAITS_D_H
#define CGAL_MIN_SPHERE_D_TRAITS_D_H

// Class interface and implementation
// ==================================
// includes
#ifndef CGAL_POINT_D_H
#include <CGAL/Point_d.h>
#endif

CGAL_BEGIN_NAMESPACE


template <class R>
class DA_d
{
    private:
        typedef typename R::FT              FT;
        typedef typename R::RT              RT;
        typedef Point_d<R>                  Point;

        typename R::Rep_tag                 tag;
        bool                                check;

    public:
        typedef const RT*           InputIterator;

        // construction
        DA_d (bool checked = false)
            : check (checked)
        {}

        // assignment; not actually necessary, but explicitly included to
        // deal with egcs compiler problems
        // -----------------------------------------------------------
        DA_d & operator=(const DA_d &o)
        {
            check = o.check;
            return *this;
        }

        // get_dimension
        // -----------------------------------------------------------
        int get_dimension (const Point& p) const
        {
            return p.dimension();
        }

        // get_begin
        // -----------------------------------------------------------
        InputIterator get_begin (const Point& p) const
        {
            if (check)
                CGAL_optimisation_assertion (correctly_accesses (p));
            return p.begin();
        }

        // set
        // -----------------------------------------------------------
        void set (Point& p, RT* first, RT* last) const
        {
            set (p, first, last, tag);
        }

        void set (Point& p, const FT* first, const FT* last,
                  Cartesian_tag t) const
        {
            p = Point(last-first, first, last);
        }

        void set (Point& p, const RT* first, const RT* last,
                  Homogeneous_tag t) const
        {
            p = Point(last-first-1, first, last);
        }


        // check
        // -----------------------------------------------------------
        bool correctly_accesses (const Point& p) const
        {
            return correctly_accesses (p, tag);
        }

        bool correctly_accesses (const Point& p, Cartesian_tag t) const
        {
            const FT* it = p.begin();
            for (int i=0; i<p.dimension(); ++i, ++it)
                if (p.cartesian(i) != *it) return false;
            return true;
        }

        bool correctly_accesses (const Point& p, Homogeneous_tag t)
        const
        {
            const RT* it = p.begin();
            for (int i=0; i<p.dimension()+1; ++i, ++it)
                if (p.homogeneous(i) != *it) return false;
            return true;
        }

    };


template <class R>
class Min_sphere_d_traits_d
{
    public:
        typedef typename R::Rep_tag         Rep_tag;
        typedef typename R::RT              NT;
        typedef Point_d<R>                  Point;
        typedef DA_d<R>                     DA;

        DA                                  da;

        Min_sphere_d_traits_d (bool checked = false)
            : da (checked)
        {}
};



 CGAL_END_NAMESPACE

#endif // CGAL_MIN_SPHERE_D_TRAITS_D_H

// ===== EOF ==================================================================

