// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : ch_timing_2.C
// source        : convex_hull_2.lw
// revision      : 1.3.2
// revision_date : 09 Dec 1998
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CH_TIMING_2_C
#define CGAL_CH_TIMING_2_C

#ifndef CGAL_CH_TIMING_2_H
#include <CGAL/ch_timing_2.h>
#endif // CGAL_CH_TIMING_2_H
template <class ForwardIterator1, class ForwardIterator2, class Traits>
void
CGAL_ch_timing( ForwardIterator1 first, ForwardIterator1 last,
                ForwardIterator2 result,
                int iterations, 
                const Traits& ch_traits)
{
  int i;
  #ifdef CGAL_USE_LEDA
  float t, delta_t;
  #else
  long  t, delta_t;
  #endif // CGAL_USE_LEDA

  cout << endl;
  ForwardIterator2  restart = result;

  #ifdef CGAL_USE_LEDA
  t = used_time();
  #else
  t = clock();
  #endif // CGAL_USE_LEDA

  for (i=0; i < iterations; i++)
  {
      result = restart;
      CGAL_ch_akl_toussaint( first, last , result, ch_traits);
  }
  #ifdef CGAL_USE_LEDA
  delta_t = used_time(t);
  #else
  delta_t = clock() - t;
  #endif // CGAL_USE_LEDA

  cout << "CGAL_ch_akl_toussaint:         " << delta_t << endl;

  #ifdef CGAL_USE_LEDA
  t = used_time();
  #else
  t = clock();
  #endif // CGAL_USE_LEDA

  for (i=0; i < iterations; i++)
  {
      result = restart;
      CGAL_ch_eddy( first, last , result, ch_traits);
  }
  #ifdef CGAL_USE_LEDA
  delta_t = used_time(t);
  #else
  delta_t = clock() - t;
  #endif // CGAL_USE_LEDA

  cout << "CGAL_ch_eddy:                  " << delta_t << endl;

  #ifdef CGAL_USE_LEDA
  t = used_time();
  #else
  t = clock();
  #endif // CGAL_USE_LEDA

  for (i=0; i < iterations; i++)
  {
      result = restart;
      CGAL_ch_bykat( first, last , result, ch_traits);
  }
  #ifdef CGAL_USE_LEDA
  delta_t = used_time(t);
  #else
  delta_t = clock() - t;
  #endif // CGAL_USE_LEDA

  cout << "CGAL_ch_bykat                  " << delta_t << endl;

  #ifdef CGAL_USE_LEDA
  t = used_time();
  #else
  t = clock();
  #endif // CGAL_USE_LEDA

  for (i=0; i < iterations; i++)
  {
      result = restart;
      CGAL_ch_bykat_with_threshold( first, last , result, ch_traits);
  }
  #ifdef CGAL_USE_LEDA
  delta_t = used_time(t);
  #else
  delta_t = clock() - t;
  #endif // CGAL_USE_LEDA

  cout << "CGAL_ch_bykat_with_threshold:  " << delta_t << endl;

  #ifdef CGAL_USE_LEDA
  t = used_time();
  #else
  t = clock();
  #endif // CGAL_USE_LEDA

  for (i=0; i < iterations; i++)
  {
      result = restart;
      CGAL_ch_graham_andrew( first, last , result, ch_traits);
  }
  #ifdef CGAL_USE_LEDA
  delta_t = used_time(t);
  #else
  delta_t = clock() - t;
  #endif // CGAL_USE_LEDA

  cout << "CGAL_ch_graham_andrew:         " << delta_t << endl;

  #ifdef CGAL_USE_LEDA
  t = used_time();
  #else
  t = clock();
  #endif // CGAL_USE_LEDA

  for (i=0; i < iterations; i++)
  {
      result = restart;
      CGAL_ch_jarvis( first, last , result, ch_traits);
  }
  #ifdef CGAL_USE_LEDA
  delta_t = used_time(t);
  #else
  delta_t = clock() - t;
  #endif // CGAL_USE_LEDA

  cout << "CGAL_ch_jarvis:                " << delta_t << endl;

}


#endif // CGAL_CH_TIMING_2_C

