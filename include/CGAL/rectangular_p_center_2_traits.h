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
// file          : include/CGAL/rectangular_p_center_2_traits.h
// package       : Matrix_search (1.17)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : pcenter.aw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/06/01 14:08:19 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// 2-4-Center Computation for Axis-Parallel 2D-Rectangles
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (RECTANGULAR_P_CENTER_2_TRAITS_H)
#define RECTANGULAR_P_CENTER_2_TRAITS_H 1

#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#include <CGAL/optimisation_assertions.h>
#endif // CGAL_OPTIMISATION_ASSERTIONS_H
#ifndef CGAL_ISO_RECTANGLE_2_H
#include <CGAL/Iso_rectangle_2.h>
#endif // CGAL_ISO_RECTANGLE_2_H
#include <vector>

#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
  !defined(CGAL_CFG_MATCHING_BUG_2)

#ifndef CGAL_PROTECT_ITERATOR
#include <iterator>
#define CGAL_PROTECT_ITERATOR
#endif

#endif // ! (CGAL_CFG_NO_ITERATOR_TRAITS) && ...

CGAL_BEGIN_NAMESPACE

#ifdef CGAL_CARTESIAN_REP_H
template < class ForwardIterator,
           class OutputIterator,
           class FT >
inline
OutputIterator
_CGAL_rectangular_p_center_2(
  ForwardIterator f,
  ForwardIterator l,
  OutputIterator o,
  FT& r,
  int p,
  Point_2< Cartesian< FT > >*)
{
  typedef
    //!!! egcs111 sucks here
    Piercing_squares_traits_cartesian< Cartesian< FT > >
    //Piercing_traits_cartesian< Cartesian< FT > >
  PTraits;

  return rectangular_p_center_2( f, l, o, r, p, PTraits());
} // rectangular_p_center_2( ... )
#endif // CGAL_CARTESIAN_REP_H

#ifdef CGAL_HOMOGENEOUS_REP_H
template < class ForwardIterator,
           class OutputIterator,
#ifdef CGAL_CFG_MATCHING_BUG_1
           class FT,
#endif
           class RT >
inline
OutputIterator
_CGAL_rectangular_p_center_2(
  ForwardIterator f,
  ForwardIterator l,
  OutputIterator o,
#ifndef CGAL_CFG_MATCHING_BUG_1
  Homogeneous< RT >::FT& r,
#else
  FT& r,
#endif
  int p,
  Point_2< Homogeneous< RT > >*)
{
  typedef
    //!!! egcs111 sucks here
    //Piercing_squares_traits_homogeneous< Homogeneous< RT > >
    Piercing_traits_homogeneous< Homogeneous< RT > >
  PTraits;

  return rectangular_p_center_2( f, l, o, r, p, PTraits());
} // rectangular_p_center_2( ... )
#endif // CGAL_HOMOGENEOUS_REP_H

template < class ForwardIterator, class FT >
struct Blow_up_iso_square_static_2
{
  void
  operator()( ForwardIterator b, ForwardIterator e, FT v) const
  {
    if ( b != e)
      (*b).set_radius( v / FT( 2));
  }
};
/*
template < class ForwardIterator, class FT, class R >
void
_rectangle_blow_up_to( ForwardIterator f,
                            ForwardIterator l,
                            FT diameter,
                            Iso_rectangle_2< R >*)
{
  for ( ForwardIterator i( f); i != l; ++i) {
    Point_2< R > c(
      ((*i).xmin() + (*i).xmax()) / FT( 2),
      ((*i).ymin() + (*i).ymax()) / FT( 2));
    Vector_2< R > t( diameter / FT( 2),
                          diameter / FT( 2));
    (*i) = Iso_rectangle_2< R >( c - t, c + t);
  }
}
*/


template < class _PiercingFunction >
class Pcenter_default_traits {
public:
  typedef _PiercingFunction                            PiercingFunction;
  typedef typename _PiercingFunction::Iso_rectangle_2  Iso_rectangle_2;
  typedef typename _PiercingFunction::Point_2          Point_2;
  typedef typename _PiercingFunction::FT               FT;
  typedef typename _PiercingFunction::X                X;
  typedef typename _PiercingFunction::Y                Y;
  typedef typename _PiercingFunction::Build_point      Build_point;
  typedef typename _PiercingFunction::Build_rectangle  Build_rectangle;
  typedef std::vector< Iso_rectangle_2 >               Cont;
  typedef typename Cont::size_type                     size_type;
  typedef typename Cont::iterator                      iterator;
  typedef Blow_up_iso_square_static_2< iterator, FT >  Blow_up_rectangles;

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class InputIterator >
#else
  typedef std::vector< Point_2 >::iterator               InputIterator;
  typedef std::back_insert_iterator< vector< Point_2 > > OutputIterator;
#endif // CGAL_CFG_NO_MEMBER_TEMPLATES
  Pcenter_default_traits(
    InputIterator f,
    InputIterator l,
    const PiercingFunction& pf)
  : _pf( pf)
  {
    CGAL_optimisation_precondition( f != l);
#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
    !defined(CGAL_CFG_MATCHING_BUG_2)
    typedef typename iterator_traits< InputIterator >::iterator_category
      iterator_category;
    _data_init( f, l, iterator_category());
#else
    _data_init( f, l);
#endif
    CGAL_optimisation_postcondition( !input_data.empty());
  }

  size_type
  number_of_points() const
  { return input_data.size(); }

  bool
  operator()( FT v)
  {
    CGAL_optimisation_assertion( !input_data.empty());
    bool ok;
    this->operator()( v,
                      Wastebasket< Point_2 >(),
                      ok);
    return ok;
  }

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class OutputIterator >
#else
  Wastebasket< Point_2 >
  operator()( FT v, Wastebasket< Point_2 > o, bool& ok)
  {
    CGAL_optimisation_assertion( !input_data.empty());
    Blow_up_rectangles blow_it;
    blow_it( input_data.begin(), input_data.end(), v);
    return _pf( input_data.begin(),
                input_data.end(),
                o,
                ok);
  }
#endif // CGAL_CFG_NO_MEMBER_TEMPLATES
  OutputIterator
  operator()( FT v, OutputIterator o, bool& ok)
  {
    CGAL_optimisation_assertion( !input_data.empty());
    Blow_up_rectangles blow_it;
    blow_it( input_data.begin(), input_data.end(), v);
    return _pf( input_data.begin(),
                input_data.end(),
                o,
                ok);
  }

protected:

#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
  !defined(CGAL_CFG_MATCHING_BUG_2)

  template < class InputIterator >
  void
  _data_init( InputIterator f,
              InputIterator l,
              random_access_iterator_tag)
  {
    input_data.reserve( iterator_distance( f, l));
    _data_init( f, l, input_iterator_tag());
  }

  template < class InputIterator, class IteratorCategory >
  void
  _data_init( InputIterator f,
              InputIterator l,
              IteratorCategory)
#else
#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class InputIterator >
#endif // CGAL_CFG_NO_MEMBER_TEMPLATES
  void
  _data_init( InputIterator f, InputIterator l)
#endif // ! (CGAL_CFG_NO_ITERATOR_TRAITS) && ...
  {
    while ( f != l) {
      Point_2 p( *(f++));
      input_data.push_back( Build_rectangle()( p));
    }
  } // _data_init( ... )


  // data members:
  PiercingFunction                _pf;
  std::vector< Iso_rectangle_2 >  input_data;

}; // Pcenter_default_traits< PiercingFunction >

CGAL_END_NAMESPACE


#endif // ! (RECTANGULAR_P_CENTER_2_TRAITS_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

