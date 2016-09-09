// ============================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.4
// release_date  : 2002, May 16
// 
// file          : demo/Robustness/include/CGAL/intersection_test_statistics.h
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/07/18 13:49:53 $
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

// #include <sstream> // Doesn't work with GCC < 2.95.3
#include <strstream>

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

#if defined(CGAL_USE_CGAL_WINDOW)
   // std::ostringstream OS;
   std::ostrstream OS;
   OS << is_count << " intersection points found,\n";
   OS << bl_count << " of them lie on both segments.\n";
   OS << "Out of the " << 2*is_count << "\npoint-on-segment tests, \n" <<  ol_count;
   OS << " are positive.\n";
   OS << "Computation time " << watch.time() << " secs.\n";
   OS << std::ends;
   str = OS.str();
#else
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
#endif
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
