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
// file          : include/CGAL/Min_sphere_d.h
// package       : Min_sphere_d (1.13)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/02/26 12:13:50 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zurich (Bernd Gärtner)
//
// implementation: dD Smallest Enclosing Sphere
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_MIN_SPHERE_D_H
#define CGAL_MIN_SPHERE_D_H


// Class declarations
// ==================

// Class interface and implementation
// ==================================
// includes

#ifndef CGAL_BASIC_H
#  include <CGAL/basic.h>
#endif

#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#  include <CGAL/optimisation_assertions.h>
#endif

#ifndef CGAL_OPTIMISATION_BASIC_H
#  include <CGAL/optimisation_basic.h>
#endif

#ifndef CGAL_MIN_SPHERE_D_TRAITS_2_H
#  include <CGAL/Min_sphere_d_traits_2.h>
#endif // CGAL_MIN_SPHERE_D_TRAITS_2_H

#ifndef CGAL_MIN_SPHERE_D_TRAITS_3_H
#  include <CGAL/Min_sphere_d_traits_3.h>
#endif // CGAL_MIN_SPHERE_D_TRAITS_3_H

#ifndef CGAL_MIN_SPHERE_D_TRAITS_D_H
#  include <CGAL/Min_sphere_d_traits_d.h>
#endif // CGAL_MIN_SPHERE_D_TRAITS_D_H

#ifndef CGAL_OPTIMISATION_SPHERE_D_H
#  include <CGAL/Optimisation_sphere_d.h>
#endif // CGAL_OPTIMISATION_SPHERE_D_H

#ifndef CGAL_PROTECT_LIST
#  include <list>
#  define CGAL_PROTECT_LIST
#endif

#ifndef CGAL_PROTECT_IOSTREAM
#  include <iostream>
#  define CGAL_PROTECT_IOSTREAM
#endif

CGAL_BEGIN_NAMESPACE

template <class Rep_tag, class NT>
class NT_rep_traits;

template <class NT>
class NT_rep_traits<Cartesian_tag, NT>
{
     public:
         typedef NT           FT;
         typedef NT           RT;
};

template <class NT>
class NT_rep_traits<Homogeneous_tag, NT>
{
     public:
         typedef Quotient<NT> FT;
         typedef NT           RT;
};



template <class Traits>
class Min_sphere_d
{
    public:
        typedef typename Traits::Rep_tag        Rep_tag;
        typedef typename Traits::NT             NT;
        typedef typename NT_rep_traits<Rep_tag, NT>::FT FT;
        typedef typename NT_rep_traits<Rep_tag, NT>::RT RT;
        typedef typename Traits::Point          Point;  // Point type
        typedef typename Traits::DA             DA;     // Data accessor type
    
        typedef typename std::list<Point>::const_iterator
                Point_iterator;
        typedef typename std::list<Point>::const_iterator
                Support_point_iterator;
    
    private:
        typedef typename std::list<Point>::iterator             It;
    
    
    private:
        int                                     d;            // ambient dim
        std::list<Point>                        points;       // keeps P = Q_n
        Optimisation_sphere_d<Rep_tag, FT, RT, Point,DA>
                                                ms_basis;     // keeps (ms,B)
        It                                      support_end;  // delimites S
        Traits                                  tco;          // traits object
    
    
public:
    Min_sphere_d (const Traits& traits = Traits())
        : d(-1), ms_basis (traits.da), support_end(points.begin()),
          tco( traits)
    {}
    
    // STL-like constructor (member template)
    template <class InputIterator>
    Min_sphere_d( InputIterator first,
                       InputIterator last,
                       const Traits& traits = Traits())
        : d(-1), points( first, last), ms_basis (traits.da),
          support_end(points.begin()), tco( traits)
    {
        if (points.size()>0) {
            d = tco.da.get_dimension (points.front());
            CGAL_optimisation_precondition ((d>=0) && all_points_have_dim(d));
            ms_basis.set_size (d);
            pivot_ms();
        }
    }
    Min_sphere_d (const Min_sphere_d& ms)
        : d(ms.ambient_dim()), points (ms.points_begin(), ms.points_end()),
          ms_basis (ms.traits().da), support_end (points.begin()),
          tco (ms.traits())
    {
        if (d != -1) {
            ms_basis.set_size (d);
            pivot_ms();
        }
    }
    
    Min_sphere_d& operator=(const Min_sphere_d& ms)
    {
        if (this != &ms) {
            points.erase (points.begin(), points.end());
            d = ms.ambient_dim();
            points.insert (points.begin(), ms.points_begin(), ms.points_end());
            ms_basis.set_da(ms.traits().da);
            support_end = points.begin();
            tco = ms.traits();
            if (d != -1) {
                ms_basis.set_size (d);
                pivot_ms();
            }
        }
        return *this;
    }
    
    
    int number_of_points() const
    {
        return points.size();
    }
    
    int number_of_support_points() const
    {
        return ms_basis.number_of_support_points();
    }
    
    Point_iterator points_begin () const
    {
        return points.begin();
    }
    
    Point_iterator points_end () const
    {
        return points.end();
    }
    
    Support_point_iterator support_points_begin () const
    {
        return points.begin();
    }
    
    Support_point_iterator support_points_end () const
    {
        return support_end;
    }
    
    int ambient_dim () const
    {
        return d;
    }
    
    Point center () const
    {
        CGAL_optimisation_precondition (!is_empty());
        return ms_basis.center();
    }
    
    FT squared_radius () const
    {
        CGAL_optimisation_precondition (!is_empty());
        return ms_basis.squared_radius();
    }
    
    
    Bounded_side bounded_side (const Point& p) const
    {
        if (d == -1)
           return ON_UNBOUNDED_SIDE;
        else {
           CGAL_optimisation_precondition (d == tco.da.get_dimension(p));
           return (Bounded_side (-CGAL::sign (ms_basis.excess (p))));
        }
    }
    
    bool has_on_bounded_side (const Point& p) const
    {
        if (d == -1)
           return false;
        else {
           CGAL_optimisation_precondition (d == tco.da.get_dimension(p));
           return (is_negative (ms_basis.excess (p)));
        }
    }
    
    bool has_on_unbounded_side (const Point& p) const
    {
        if (d == -1)
           return true;
        else {
           CGAL_optimisation_precondition (d == tco.da.get_dimension(p));
           return (is_positive (ms_basis.excess (p)));
        }
    }
    
    bool has_on_boundary (const Point& p) const
    {
        if (d == -1)
           return false;
        else {
           CGAL_optimisation_precondition (d == tco.da.get_dimension(p));
           return (is_zero (ms_basis.excess (p)));
        }
    }
    
    bool is_empty () const
    {
        return (d == -1);
    }
    
    bool is_degenerate () const
    {
        return (ms_basis.number_of_support_points() < 2);
    }
    
    
    void clear ()
    {
         d = -1;
         points.erase (points.begin(), points.end());
         ms_basis.set_size (-1);
         support_end = points.begin();
    }
    
    // STL-like set(member template)
    template <class InputIterator>
    void set ( InputIterator first,
               InputIterator last)
    {
        points.erase (points.begin(), points.end());
        points.insert (points.begin(), first, last);
        support_end = points.begin();
        if (points.size()>0) {
            d = tco.da.get_dimension (points.front());
            CGAL_optimisation_precondition ((d>=0) && all_points_have_dim (d));
            ms_basis.set_size (d);
            pivot_ms();
        } else {
            d = -1;
            ms_basis.set_size (-1);
        }
    }
    
    void insert (const Point& p)
    {
        if (has_on_unbounded_side (p)) {
            if (is_empty()) {
                d = tco.da.get_dimension (p);
                CGAL_optimisation_precondition (d>=0);
                ms_basis.set_size (d);
            }
            ms_basis.push (p);      // ensure precondition of pivot_ms
            pivot_ms ();
            ms_basis.pop ();
            points.push_front (p);  // ensure postcondition of insert
        } else
            points.push_back (p);   // just append p
            if (support_end == points.end()) --support_end;
    }
    
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        for (InputIterator i=first; i!=last; ++i)
            insert (*i);
    }
    
    
    bool is_valid (bool verbose = false, int level = 0) const
    {
        Verbose_ostream verr (verbose);
    
        // sphere verification
        verr << "  (a) sphere verification..." << flush;
        if (ms_basis.is_valid (verbose))
            verr << "passed." << endl;
        else
            return false;
    
        // containment check
        verr << "  (b) containment check..." << flush;
    
        // non-support-points
        Point_iterator i;
        for (i=support_end; i!=points.end(); ++i)
            if (has_on_unbounded_side (*i))
                return (_optimisation_is_valid_fail (verr,
                  "sphere does not contain all points"));
    
        // support points
        for (i=points.begin(); i!=support_end; ++i)
            if (!has_on_boundary (*i))
                return (_optimisation_is_valid_fail (verr,
                  "sphere does not have all support points on boundary"));
    
        verr << "passed." << endl;
        verr << "object is valid!" << endl;
        return true;
    }
    
    
    const Traits& traits() const
    {
         return tco;
    }
    
    
private:
    void mtf_ms (It k)
    {
        support_end = points.begin();
        if (ms_basis.size_of_basis()==d+1) return;
        for (It i = points.begin(); i!=k;) {
            It j = i++;
            if (is_positive (ms_basis.excess(*j))) {
                ms_basis.push (*j);
                mtf_ms (j);
                ms_basis.pop();
                move_to_front (j);
            }
        }
    }
    
    
    void pivot_ms ()
    {
        It t = points.begin();
        advance (t, std::min (d+1, (int)points.size()));
        mtf_ms (t);
    
        RT excess, e;
        do {
            excess = RT(0);
            It pivot;
            for (It i=t; i!=points.end(); ++i) {
                e = ms_basis.excess(*i);
                if (e > excess) {
                   excess = e;
                   pivot = i;
                }
            }
            if (is_positive (excess)) {
                t = support_end;
                if (t==pivot) ++t; //  inserted from the esa code
                ms_basis.push (*pivot);
                mtf_ms (support_end);
                ms_basis.pop();
                move_to_front (pivot);
            }
        } while (is_positive (excess));
    }
    
    
    void move_to_front (It j)
    {
        if (support_end == j)
           ++support_end;
        points.splice (points.begin(), points, j);
    }
    
    
    bool all_points_have_dim (int dim) const
    {
        for (Point_iterator i=points.begin(); i!=points.end(); ++i)
            if (tco.da.get_dimension(*i) != dim)
                return false;
        return true;
    }
    
    
};

// Function declarations
// =====================
// I/O
// ---

template < class Traits >
ostream& operator << ( ostream& os, const Min_sphere_d<Traits>& ms);

template < class Traits >
istream& operator >> ( istream& is, Min_sphere_d<Traits> & ms);

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#  include <CGAL/Min_sphere_d.C>
#endif

#endif // CGAL_MIN_SPHERE_D_H

// ===== EOF ==================================================================

