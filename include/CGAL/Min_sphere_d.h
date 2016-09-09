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
// file          : include/CGAL/Min_sphere_d.h
// package       : Min_sphere_d (1.9)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/11/19 10:07:24 $
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

#ifndef CGAL_MIN_SPHERE_D_H
#define CGAL_MIN_SPHERE_D_H

template <class T>
inline T square (const T& a)
{
    return a*a;
}

// Class declarations
// ==================

// Class interface and implementation
// ==================================
// includes
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

#ifndef CGAL_PROTECT_LIST_H
#  include <list.h>
#  define CGAL_PROTECT_LIST_H
#endif

#ifndef CGAL_PROTECT_IOSTREAM_H
#  include <iostream.h>
#  define CGAL_PROTECT_LIST_H
#endif

template <class Traits>
class CGAL_Min_sphere_d
{
    public:
        typedef typename Traits::R              R;      // Representation class
        typedef typename Traits::Point          Point;  // Point type
        typedef typename Traits::DA             DA;     // Data accessor type
    
        typedef typename list<Point>::const_iterator    Point_iterator;
        typedef typename list<Point>::const_iterator    Support_point_iterator;
    
    private:
        typedef typename list<Point>::iterator          It;
        typedef typename R::FT                          FT;
        typedef typename R::RT                          RT;
    
    
    private:
        int                                     d;            // ambient dim
        list<Point>                             points;       // keeps P = Q_n
        CGAL_Optimisation_sphere_d<R,Point,DA>  ms_basis;     // keeps (ms,B)
        It                                      support_end;  // delimites S
        Traits                                  tco;          // traits object
    
    
public:
    CGAL_Min_sphere_d (const Traits& traits = Traits())
        : d(-1), ms_basis (traits.da), support_end(points.begin()),
          tco( traits)
    {}
    
    #ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
    
        // STL-like constructor (member template)
        template <class InputIterator>
        CGAL_Min_sphere_d( InputIterator first,
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
    
    #else
    
        // constructor for arrays and vector<Point>
        CGAL_Min_sphere_d( const Point* first,
                           const Point* last,
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
    
        // constructor for list<Point>
        CGAL_Min_sphere_d( Point_iterator first,
                           Point_iterator last,
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
    
        // constructor for istream_iterator<Point>
        CGAL_Min_sphere_d( istream_iterator<Point,ptrdiff_t> first,
                           istream_iterator<Point,ptrdiff_t> last,
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
    
    #endif // CGAL_CFG_NO_MEMBER_TEMPLATES
    
    CGAL_Min_sphere_d (const CGAL_Min_sphere_d& ms)
        : d(ms.ambient_dim()), points (ms.points_begin(), ms.points_end()),
          ms_basis (ms.traits().da), support_end (points.begin()),
          tco (ms.traits())
    {
        if (d != -1) {
            ms_basis.set_size (d);
            pivot_ms();
        }
    }
    
    CGAL_Min_sphere_d& operator=(const CGAL_Min_sphere_d& ms)
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
    
    
    CGAL_Bounded_side bounded_side (const Point& p) const
    {
        if (d == -1)
           return CGAL_ON_UNBOUNDED_SIDE;
        else {
           CGAL_optimisation_precondition (d == tco.da.get_dimension(p));
           return (CGAL_Bounded_side (CGAL_sign (ms_basis.excess (p))));
        }
    }
    
    bool has_on_bounded_side (const Point& p) const
    {
        if (d == -1)
           return false;
        else {
           CGAL_optimisation_precondition (d == tco.da.get_dimension(p));
           return (CGAL_is_negative (ms_basis.excess (p)));
        }
    }
    
    bool has_on_unbounded_side (const Point& p) const
    {
        if (d == -1)
           return true;
        else {
           CGAL_optimisation_precondition (d == tco.da.get_dimension(p));
           return (CGAL_is_positive (ms_basis.excess (p)));
        }
    }
    
    bool has_on_boundary (const Point& p) const
    {
        if (d == -1)
           return false;
        else {
           CGAL_optimisation_precondition (d == tco.da.get_dimension(p));
           return (CGAL_is_zero (ms_basis.excess (p)));
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
    
    #ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
    
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
    
    #else
    
        // set for arrays and vector<Point>
        void set ( const Point* first,
                   const Point* last)
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
    
        // set for list<Point>
        void set ( Point_iterator first,
                   Point_iterator last)
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
    
        // set for istream_iterator<Point>
        void set ( istream_iterator<Point,ptrdiff_t> first,
                   istream_iterator<Point,ptrdiff_t> last)
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
    
    #endif // CGAL_CFG_NO_MEMBER_TEMPLATES
    
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
    }
    
    #ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
    
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            for (InputIterator i=first; i!=last; ++i)
                insert (*i);
        }
    
    #else
    
        // range insertion for arrays and vector<point>
        void insert (const Point* first, const Point* last)
        {
            for (const Point* i=first; i!=last; ++i)
                insert (*i);
        }
    
        // range insertion for list<point>
        void insert (Point_iterator first, Point_iterator last)
        {
            for (Point_iterator i=first; i!=last; ++i)
                insert (*i);
        }
    
        // range insertion for input stream iterator
        void insert (istream_iterator<Point,ptrdiff_t> first,
                     istream_iterator<Point,ptrdiff_t> last)
        {
            for (istream_iterator<Point,ptrdiff_t> i=first; i!=last; ++i)
                insert (*i);
        }
    
    #endif // CGAL_CFG_NO_MEMBER_TEMPLATES
    
    
    bool is_valid (bool verbose = false, int level = 0) const
    {
        CGAL_Verbose_ostream verr (verbose);
    
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
                return (CGAL__optimisation_is_valid_fail (verr,
                  "sphere does not contain all points"));
    
        // support points
        for (i=points.begin(); i!=support_end; ++i)
            if (!has_on_boundary (*i))
                return (CGAL__optimisation_is_valid_fail (verr,
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
            if (CGAL_is_positive (ms_basis.excess(*j))) {
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
        advance (t, CGAL_min (d+1, (int)points.size()));
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
            if (CGAL_is_positive (excess)) {
                t = support_end;
                ms_basis.push (*pivot);
                mtf_ms (support_end);
                ms_basis.pop();
                move_to_front (pivot);
            }
        } while (CGAL_is_positive (excess));
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
ostream& operator << ( ostream& os, const CGAL_Min_sphere_d<Traits>& ms);

template < class Traits >
istream& operator >> ( istream& is, CGAL_Min_sphere_d<Traits> & ms);

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#  include <CGAL/Min_sphere_d.C>
#endif

#endif // CGAL_MIN_SPHERE_D_H

// ===== EOF ==================================================================

