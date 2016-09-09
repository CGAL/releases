// Copyright (c) 2006  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Envelope_3/include/CGAL/envelope_3.h $
// $Id: envelope_3.h 33987 2006-09-11 10:22:10Z baruchzu $
// 
//
// Author(s)     : Ron Wein           <wein@post.tau.ac.il>
//                 Baruch Zukerman    <baruchzu@post.tau.ac.il>

#ifndef CGAL_ENVELOPE_3_H
#define CGAL_ENVELOPE_3_H

#include <CGAL/Envelope_3/Envelope_divide_and_conquer_3.h>
#include <CGAL/Envelope_3/Envelope_pm_dcel.h>
#include <CGAL/Envelope_3/Envelope_overlay_functor.h>
#include <CGAL/Arr_accessor.h>

CGAL_BEGIN_NAMESPACE

/*! \class
 * Representation of an envelope diagram (a minimization diagram or a
 * maximization diagram).
 */
template <class Traits_> class Envelope_diagram_2 :
  public Arrangement_2<Traits_,
                       Envelope_pm_dcel<Traits_,
                                        typename Traits_::Xy_monotone_surface_3> >
{
public:
  typedef Traits_                                       Traits_3;
  typedef typename Traits_3::Xy_monotone_surface_3      Xy_monotone_surface_3;

protected:
  typedef Envelope_pm_dcel<Traits_3,
                           Xy_monotone_surface_3>       Env_dcel;
  typedef Envelope_diagram_2<Traits_3>                  Self;
  friend class Arr_accessor<Self>;

public:
  typedef Arrangement_2<Traits_3, Env_dcel>             Base;
  typedef typename Env_dcel::Dcel_data_const_iterator   Surface_const_iterator;

  /*! Default constructor. */
  Envelope_diagram_2() :
    Base()
  {}

  /*! Constructor with a traits-class instance. */
  Envelope_diagram_2 (Traits_3* tr) :
    Base (tr)
  {}

};

/*!
 * Construct the lower envelope of a given set of surfaces.
 * \param begin An iterator for the first surface.
 * \param end A past-the-end iterator for the surfaces in the range.
 * \param min_diag Output: The minimization diagram.
 * \pre The value-type of InputIterator is Traits::Surface_3.
 */
template <class InputIterator, class Traits>
void lower_envelope_3 (InputIterator begin, InputIterator end,
                       Envelope_diagram_2<Traits>& min_diagram)
{
  typedef Traits                                       Traits_3;
  typedef typename Envelope_diagram_2<Traits_3>::Base  Base_arr_2;
  typedef Envelope_divide_and_conquer_3<Traits_3,
                                        Base_arr_2>    Envelope_algorithm;
  Envelope_algorithm   env_alg (min_diagram.get_traits(), LOWER);
  env_alg.construct_lu_envelope (begin, end, min_diagram);

  return;
}

/*!
 * Construct the upper envelope of a given set of surfaces.
 * \param begin An iterator for the first surface.
 * \param end A past-the-end iterator for the surfaces in the range.
 * \param max_diag Output: The maximization diagram.
 * \pre The value-type of InputIterator is Traits::Surface_3.
 */
template <class InputIterator, class Traits>
void upper_envelope_3 (InputIterator begin, InputIterator end,
                       Envelope_diagram_2<Traits>& max_diagram)
{
  typedef Traits                                       Traits_3;
  typedef typename Envelope_diagram_2<Traits_3>::Base  Base_arr_2;
  typedef Envelope_divide_and_conquer_3<Traits_3,
                                        Base_arr_2>    Envelope_algorithm;

  Envelope_algorithm   env_alg (max_diagram.get_traits(), UPPER);
  env_alg.construct_lu_envelope (begin, end, max_diagram);

  return;
}

/*!
 * Construct the lower envelope of a given set of xy_monotone surfaces.
 * \param begin An iterator for the first xy-monotone surface.
 * \param end A past-the-end iterator for the xy_monotone surfaces in the range.
 * \param min_diag Output: The minimization diagram.
 * \pre The value-type of InputIterator is Traits::Surface_3.
 */
template <class InputIterator, class Traits>
void lower_envelope_xy_monotone_3 (InputIterator begin, InputIterator end,
                                   Envelope_diagram_2<Traits>& min_diagram)
{
  typedef Traits                                       Traits_3;
  typedef typename Envelope_diagram_2<Traits_3>::Base  Base_arr_2;
  typedef Envelope_divide_and_conquer_3<Traits_3,
                                        Base_arr_2>    Envelope_algorithm;
  Envelope_algorithm   env_alg (min_diagram.get_traits(), LOWER);
  env_alg.construct_envelope_xy_monotone (begin, end, min_diagram);

  return;
}

/*!
 * Construct the upper envelope of a given set of xy_monotone surfaces.
 * \param begin An iterator for the first xy_monotone surface.
 * \param end A past-the-end iterator for the xy_monotone surfaces in the range.
 * \param max_diag Output: The maximization diagram.
 * \pre The value-type of InputIterator is Traits::Surface_3.
 */
template <class InputIterator, class Traits>
void upper_envelope_xy_monotone_3 (InputIterator begin, InputIterator end,
                                   Envelope_diagram_2<Traits>& max_diagram)
{
  typedef Traits                                       Traits_3;
  typedef typename Envelope_diagram_2<Traits_3>::Base  Base_arr_2;
  typedef Envelope_divide_and_conquer_3<Traits_3,
                                        Base_arr_2>    Envelope_algorithm;

  Envelope_algorithm   env_alg (max_diagram.get_traits(), UPPER);
  env_alg.construct_envelope_xy_monotone (begin, end, max_diagram);

  return;
}

CGAL_END_NAMESPACE

#endif
