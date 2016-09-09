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
// source        : orientation.fw
// file          : demo/Robustness/orientation_2.C
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
 

#include <CGAL/Interval_arithmetic.h>

template <class ForwardIterator, class Traits>
void
orientation_statistics( ForwardIterator first, ForwardIterator last,
                        CGAL::Orientation* C,
                        leda_string& s1, leda_string& s2,
                        const Traits& T )
{
    typename Traits::Orientation_2  orientation = T.orientation_2_object();
    int c = 0;
    int success = 0;
    for( ForwardIterator i = first; i != last; ++i)
        for( ForwardIterator j = first; j != last; ++j)
            for( ForwardIterator k = first; k != last; ++k)
                if ( C[c++] == orientation(*i, *j, *k)) ++success;

    s1 = leda_string("Out of %d orientation tests, %d", c, success);
    s2 = leda_string("( %2.2f %%) give the correct result.",
                        (double)success/c * 100);
}

template <class ForwardIterator, class Traits>
void
fill_control_field( ForwardIterator first, ForwardIterator last,
                    CGAL::Orientation* C,
                    const Traits& T )
{
    typename Traits::Orientation_2  orientation = T.orientation_2_object();
    int c = 0;
    for( ForwardIterator i = first; i != last; ++i)
        for( ForwardIterator j = first; j != last; ++j)
            for( ForwardIterator k = first; k != last; ++k)
                C[c++] = orientation(*i, *j, *k);
}

template <class ForwardIterator, class Traits>
void
orientation_statistics_IA( ForwardIterator first, ForwardIterator last,
                           leda_string& s1, leda_string& s2,
                           const Traits& T )
{
    typename Traits::Orientation_2  orientation = T.orientation_2_object();
    int c = 0;
    int success = 0;
    for( ForwardIterator i = first; i != last; ++i)
        for( ForwardIterator j = first; j != last; ++j)
            for( ForwardIterator k = first; k != last; ++k)
                {
                  CGAL::Orientation  ori;
                  try
                  {
                    ori = orientation(*i, *j, *k);
                    ++success;
                  }
                  catch ( CGAL::Interval_base::unsafe_comparison )
                  {}
                  ++c;
                }

    s1 = leda_string("Out of %d orientation tests, %d", c, success);
    s2 = leda_string("( %2.2f %%) do not throw an exception.",
                        (double)success/c * 100);
}


