/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

// Author: Stefan Schirra
// Source: cgal_convex_hull_2.lw


#ifndef CGAL_CH_TIMING_2_C
#define CGAL_CH_TIMING_2_C

#include <CGAL/ch_timing_2.h>

template <class ForwardIterator, class OutputIterator, class Traits>
void
CGAL_ch_timing( ForwardIterator first, ForwardIterator last,
                OutputIterator result,
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

  #ifdef CGAL_USE_LEDA
  t = used_time();
  #else
  t = clock();
  #endif // CGAL_USE_LEDA

  for (i=0; i < iterations; i++)
      CGAL_ch_eddy( first, last , result, ch_traits);
  #ifdef CGAL_USE_LEDA
  delta_t = used_time(t);
  #else
  delta_t = clock() - t;
  #endif // CGAL_USE_LEDA

  cout << "CGAL_ch_eddy:               " << delta_t << endl;

  #ifdef CGAL_USE_LEDA
  t = used_time();
  #else
  t = clock();
  #endif // CGAL_USE_LEDA

  for (i=0; i < iterations; i++)
      CGAL_ch_akl_toussaint( first, last , result, ch_traits);
  #ifdef CGAL_USE_LEDA
  delta_t = used_time(t);
  #else
  delta_t = clock() - t;
  #endif // CGAL_USE_LEDA

  cout << "CGAL_ch_akl_toussaint:      " << delta_t << endl;

  #ifdef CGAL_USE_LEDA
  t = used_time();
  #else
  t = clock();
  #endif // CGAL_USE_LEDA

  for (i=0; i < iterations; i++)
      CGAL_ch_graham_andrew( first, last , result, ch_traits);
  #ifdef CGAL_USE_LEDA
  delta_t = used_time(t);
  #else
  delta_t = clock() - t;
  #endif // CGAL_USE_LEDA

  cout << "CGAL_ch_graham_andrew:      " << delta_t << endl;

  #ifdef CGAL_USE_LEDA
  t = used_time();
  #else
  t = clock();
  #endif // CGAL_USE_LEDA

  for (i=0; i < iterations; i++)
      CGAL_ch_jarvis( first, last , result, ch_traits);
  #ifdef CGAL_USE_LEDA
  delta_t = used_time(t);
  #else
  delta_t = clock() - t;
  #endif // CGAL_USE_LEDA

  cout << "CGAL_ch_jarvis:             " << delta_t << endl;

}


#endif // CGAL_CH_TIMING_2_C

