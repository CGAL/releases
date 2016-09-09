// ============================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : online.fw
// file          : demo/Robustness/include/CGAL/intersection_test_statistics.h
// revision      : 1.5
// revision_date : 20 Sep 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_INTERSECTION_TEST_STATISTICS_H
#define CGAL_INTERSECTION_TEST_STATISTICS_H

#include <CGAL/Timer.h>

template <class ForwardIterator1, class ForwardIterator2, class Traits>
void
intersection_statistics( ForwardIterator1 first1, ForwardIterator1 last1,
                         ForwardIterator2 first2, ForwardIterator2 last2,
                         leda_string& str, const Traits& T )
{
    typename Traits::Point_2      p;
    typename Traits::Intersect_2  intersection = T.intersect_2_object();
    CGAL::Timer watch;
    int is_count = 0;
    int ol_count = 0;
    int bl_count = 0;
    watch.start();
    for( ForwardIterator1 i = first1; i != last1; ++i)
        for( ForwardIterator2 j = first2; j != last2; ++j)
        {
            if ( assign(p, intersection(*i,*j)) )
            {
                is_count++;
                int ok1 = ( i->has_on(p)) ? 1 : 0;
                int ok2 = ( j->has_on(p)) ? 1 : 0;
                bl_count += ok1*ok2;
                ol_count += ok1+ok2;
            }
        }
    watch.stop();

    str  = leda_string();
    str += leda_string("%d intersection points found,\n",
                       is_count);
    str += leda_string("%d of them (%2.2f%%) lie on both\n segments. ",
                       bl_count, (double)bl_count/is_count * 100);
    str += leda_string("Out of the %d \npoint-on-segment tests, \n%d ",
                       2*is_count, ol_count );
    str += leda_string("(%2.2f%%) are positive.\n",
                       (double)ol_count/is_count * 50);
    str += leda_string("Computation time %2.2f secs.\n",
                       watch.time() );
}


template <class Stream, class ForwardIterator1, class ForwardIterator2,
          class Traits>
void
draw_errors( Stream& S,
             ForwardIterator1 first1, ForwardIterator1 last1,
             ForwardIterator2 first2, ForwardIterator2 last2,
             const Traits& T )
{
    typename Traits::Point_2      p;
    typename Traits::Intersect_2  intersection = T.intersect_2_object();
    int is_count = 0;
    int ol_count = 0;
    int bl_count = 0;
    for( ForwardIterator1 i = first1; i != last1; ++i)
        for( ForwardIterator2 j = first2; j != last2; ++j)
        {
            if ( assign(p, intersection(*i,*j)) )
            {
                is_count++;
                int ok1 = ( i->has_on(p)) ? 1 : 0;
                int ok2 = ( j->has_on(p)) ? 1 : 0;
                bl_count += ok1*ok2;
                ol_count += ok1+ok2;
                if ( !( ok1 && ok2 ) )
                {
                    if ( ok1 || ok2 )
                        S << CGAL::ORANGE;
                    else
                        S << CGAL::RED;
                    S << p;
                }
            }
        }
}

#endif // CGAL_INTERSECTION_TEST_STATISTICS_H
