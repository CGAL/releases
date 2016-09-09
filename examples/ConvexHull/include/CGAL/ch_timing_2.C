// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// 
// 
// 
//
// ----------------------------------------------------------------------------
// release       :
// release_date  :
//
// file          : ch_timing_2.C
// source        : convex_hull_2.lw
// revision      : 1.2.2
// revision_date : 27 Mar 1998
// author(s)     : Stefan Schirra <Stefan.Schirra@@mpi-sb.mpg.de>
//
// coordinator   : MPI, Saarbruecken
// ============================================================================


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

