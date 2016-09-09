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
// file          : include/CGAL/Min_sphere_d_traits_d.h
// package       : Min_sphere_d (1.9)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1999/01/08 10:38:24 $
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

#ifndef CGAL_MIN_SPHERE_D_TRAITS_D_H
#define CGAL_MIN_SPHERE_D_TRAITS_D_H

// Class declarations
// ==================
template <class FT>
class CGAL_DACd;

template <class FT, class RT>
class CGAL_DAHd;

// Class interface and implementation
// ==================================
// includes
#ifndef CGAL_POINT_D_H
#include <CGAL/Point_d.h>
#endif

#ifndef CGAL_POINTHD_H
#   include <CGAL/PointHd.h>
#endif

#ifndef CGAL_POINTCD_H
#include <CGAL/PointCd.h>
#endif

#ifndef CGAL_REP_DISTINGUISHER_H
#include <CGAL/Rep_distinguisher.h>
#endif

template <class FT, class RT>
class CGAL_DAHd
{
    private:
        typedef CGAL_PointHd<FT,RT> Point;

    public:
        int get_dimension (const Point& p) const
        {
            return p.dimension();
        }

        const RT* get_begin (const Point& p) const
        {
            return p.ptr()->e;
        }

        void set (Point& p, const RT* first, const RT* last) const
        {
            p = Point(last-first-1, first, last);
        }

        // check function
        bool correctly_accesses (const Point& p) const
        {
            const RT* it = get_begin(p);
            for (int i=0; i<p.dimension()+1; ++i, ++it)
                if (p.homogeneous(i) != *it) return false;
            return true;
        }

};


template <class FT>
class CGAL_DACd
{
    private:
        typedef CGAL_PointCd<FT>    Point;

    public:
        int get_dimension (const Point& p) const
        {
            return p.dimension();
        }

        const FT* get_begin (const Point& p) const
        {
            return p.ptr()->e;
        }

        void set (Point& p, const FT* first, const FT* last) const
        {
            p = Point(last-first, first, last);
        }

        // check function
        bool correctly_accesses (const Point& p) const
        {
            const FT* it=get_begin(p);
            for (int i=0; i<p.dimension(); ++i, ++it)
                if (p.cartesian(i) != *it) return false;
            return true;
        }
};


template <class R>
class CGAL_DA_d
{
    private:
        typedef typename R::FT              FT;
        typedef typename R::RT              RT;
        typedef CGAL_Point_d<R>             Point;
        typedef CGAL_DACd<FT>               DAC;
        typedef CGAL_DAHd<FT,RT>            DAH;

        typename R::Rep_tag                 tag;
        CGAL_Rep_distinguisher<DAC, DAH, typename R::Rep_tag>       rd;
        bool                                check;

    public:
        typedef const RT*           InputIterator;

        // construction
        CGAL_DA_d (bool checked = false)
            : check (checked)
        {}

        // assignment; not actually necessary, but explicitly included to
        // deal with egcs compiler problems
        // -----------------------------------------------------------
        CGAL_DA_d & operator=(const CGAL_DA_d &o)
        {
            rd = o.rd;
            check = o.check;
            return *this;
        }

        // get_dimension
        // -----------------------------------------------------------
        int get_dimension (const Point& p) const
        {
            return rd.ptr(tag)->get_dimension (p);
        }

        // get_begin
        // -----------------------------------------------------------
        InputIterator get_begin (const Point& p) const
        {
            if (check)
                CGAL_optimisation_assertion (correctly_accesses (p));
            return rd.ptr(tag)->get_begin (p);
        }

        // set
        // -----------------------------------------------------------
        void set (Point& p, RT* first, RT* last) const
        {
            rd.ptr(tag)->set (p, first, last);
        }

        // check
        // -----------------------------------------------------------
        bool correctly_accesses (const Point& p) const
        {
            return rd.ptr(tag)->correctly_accesses (p);
        }

    };


template <class _R>
class CGAL_Min_sphere_d_traits_d
{
    public:
        typedef _R                          R;
        typedef CGAL_Point_d<R>             Point;
        typedef CGAL_DA_d<R>                DA;

        DA                                  da;

        CGAL_Min_sphere_d_traits_d (bool checked = false)
            : da (checked)
        {}
};



#endif // CGAL_MIN_SPHERE_D_TRAITS_D_H

// ===== EOF ==================================================================

