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
// chapter       : $CGAL_Chapter: Optimisation $
// file          : include/CGAL/Min_sphere_d_traits_3.h
// package       : Min_sphere_d (1.13)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/04/12 09:31:10 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zurich (Bernd Gärtner)
//
// implementation: dD Smallest Enclosing Sphere
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_MIN_SPHERE_D_TRAITS_3_H
#define CGAL_MIN_SPHERE_D_TRAITS_3_H

// Class declarations
// ==================

// Class interface and implementation
// ==================================
// includes
#ifndef CGAL_PROTECT_ITERATOR
#include <iterator>
#define CGAL_PROTECT_ITERATOR
#endif

#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class R>
class Point_3_iterator :
    public CGAL_STD::input_iterator<typename R::RT, ptrdiff_t>
{
    private:
        typedef typename R::RT                      RT;
        typedef Point_3<R>                  Point;

        typename R::Rep_tag                         tag;

        Point                                       p;
        int                                         pos;

    public:
        Point_3_iterator ()
        {}

        Point_3_iterator (const Point& point, int position = 0)
            : p(point), pos(position)
        {}

        // assignment; not actually necessary but explicitly defined
        // to please egcs
        Point_3_iterator& operator= (const Point_3_iterator& i)
        {
            p = i.p;
            pos = i.pos;
            return *this;
        }

        Point_3_iterator operator++() // prefix
        {
            ++pos;
            return (*this);
        }

        Point_3_iterator operator++(int dummy) // postfix
        {
            Point_3_iterator it(p, pos++);
            return it;
        }

        RT operator*()
        {
            return dereference (tag);
        }

        RT dereference (Cartesian_tag t)
        {
            switch (pos) {
                case 0:
                    return p.x();
                case 1:
                    return p.y();
                case 2:
                    return p.z();
                default:
                    CGAL_optimisation_assertion(false);
                    return RT(0);
            }
        }

        RT dereference (Homogeneous_tag t)
        {
            switch (pos) {
                case 0:
                    return p.hx();
                case 1:
                    return p.hy();
                case 2:
                    return p.hz();
                case 3:
                    return p.hw();
                default:
                    CGAL_optimisation_assertion(false);
                    return RT(0);
            }
        }
};


template <class R>
class DA_3
{
    private:
        typedef typename R::RT              RT;
        typedef Point_3<R>          Point;

        typename R::Rep_tag                 tag;
        bool                                check;

    public:
        typedef Point_3_iterator<R> InputIterator;

        // construction
        DA_3 (bool checked = false)
            : check (checked)
        {}

        // get_dimension
        // -----------------------------------------------------------
        int get_dimension (const Point& p) const
        {
            return 3;
        }

        // get_begin
        // -----------------------------------------------------------
        InputIterator get_begin (const Point& p) const
        {
            if (check)
                CGAL_optimisation_assertion (correctly_accesses (p));
            return InputIterator (p);
        }

        // set
        // -----------------------------------------------------------
        void set (Point& p, RT* first, RT* last) const
        {
            if (last-first==3)
                p = Point_3<R>(*first, *(first+1), *(first+2));
            else
                p = Point_3<R>(*first, *(first+1), *(first+2),
                                    *(first+3));
        }

        // check
        bool correctly_accesses (const Point& p) const
        {
            return correctly_accesses (p, tag);
        }

        bool correctly_accesses (const Point& p, Cartesian_tag t)
        const
        {
            InputIterator it(p);
            for (int i=0; i<3; ++i, ++it)
                if (p.cartesian(i) != *it)
                    return false;
            return true;
        }

        bool correctly_accesses (const Point& p, Homogeneous_tag t)
        const
        {
            InputIterator it(p);
            for (int i=0; i<4; ++i, ++it)
                if (p.homogeneous(i) != *it) return false;
            return true;
        }
};


template <class R>
class Min_sphere_d_traits_3
{
    public:
        typedef typename R::Rep_tag         Rep_tag;
        typedef typename R::RT              NT;
        typedef Point_3<R>                  Point;
        typedef DA_3<R>                     DA;

        DA                                  da;

        Min_sphere_d_traits_3 (bool checked = false)
            : da (checked)
        {}
};



 CGAL_END_NAMESPACE

#endif // CGAL_MIN_SPHERE_D_TRAITS_3_H

// ===== EOF ==================================================================

