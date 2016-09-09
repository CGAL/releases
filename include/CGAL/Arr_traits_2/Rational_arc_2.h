// Copyright (c) 2005  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Arrangement_2/include/CGAL/Arr_traits_2/Rational_arc_2.h $
// $Id: Rational_arc_2.h 38368 2007-04-20 11:28:33Z efif $
// 
//
// Author(s)     : Ron Wein <wein@post.tau.ac.il>

#ifndef CGAL_RATIONAL_ARC_2_H
#define CGAL_RATIONAL_ARC_2_H

/*! \file
 * Header file for the _Rational_arc_2 class.
 */

#include <vector>
#include <list>
#include <ostream>
#include <CGAL/Arr_enums.h>

CGAL_BEGIN_NAMESPACE

/*! \class
 * Representation of an segment of a rational function, given as:
 *
 *        D(x)
 *   y = ------              x_l <= x <= x_r
 *        N(x)
 *
 * where D and N are polynomial with integer (or rational) coefficients.
 * The class is templated with two parameters: 
 * Alg_kernel A geometric kernel, where Alg_kernel::FT is the number type
 *            for the coordinates of arrangement vertices, which are algebraic
 *            numbers (defined by Nt_traits::Algebraic).
 * Nt_traits A traits class for performing various operations on the integer,
 *           rational and algebraic types. 
 */

template <class Alg_kernel_, class Nt_traits_>
class _Rational_arc_2
{
public:

  typedef Alg_kernel_                             Alg_kernel;
  typedef Nt_traits_                              Nt_traits;
  typedef _Rational_arc_2<Alg_kernel, Nt_traits>  Self;
  
  typedef typename Alg_kernel::FT                 Algebraic;
  typedef typename Alg_kernel::Point_2            Point_2;

  typedef typename Nt_traits::Integer             Integer;
  typedef typename Nt_traits::Rational            Rational;
  typedef std::vector<Rational>                   Rat_vector;
  typedef typename Nt_traits::Polynomial          Polynomial;

private:

  typedef std::pair<Point_2, unsigned int>        Intersection_point_2;

  enum
  {
    SRC_AT_X_MINUS_INFTY = 1,
    SRC_AT_X_PLUS_INFTY = 2,
    SRC_AT_Y_MINUS_INFTY = 4,
    SRC_AT_Y_PLUS_INFTY = 8,

    SRC_INFO_BITS = SRC_AT_X_MINUS_INFTY + SRC_AT_X_PLUS_INFTY +
                    SRC_AT_Y_MINUS_INFTY + SRC_AT_Y_PLUS_INFTY,

    TRG_AT_X_MINUS_INFTY = 16,
    TRG_AT_X_PLUS_INFTY = 32,
    TRG_AT_Y_MINUS_INFTY = 64,
    TRG_AT_Y_PLUS_INFTY = 128,

    TRG_INFO_BITS = TRG_AT_X_MINUS_INFTY + TRG_AT_X_PLUS_INFTY +
                    TRG_AT_Y_MINUS_INFTY + TRG_AT_Y_PLUS_INFTY,

    IS_DIRECTED_RIGHT = 256,
    IS_CONTINUOUS = 512,
    IS_VALID = 1024
  };
 
  Polynomial        _numer;       // The polynomial in the numerator.
  Polynomial        _denom;       // The polynomial in the denominator.
  Point_2           _ps;          // The source point.
  Point_2           _pt;          // The target point.
  int               _info;        // A set of Boolean flags.  

public:

  /// \name Constrcution methods.
  //@{

  /*!
   * Default constructor.
   */
  _Rational_arc_2 () :
    _info (0)
  {}

  /*!
   * Constructor of a whole polynomial curve.
   * \param pcoeffs The rational coefficients of the polynomial p(x).
   */
  _Rational_arc_2 (const Rat_vector& pcoeffs) :
    _info (0)
  {
    // Mark that the endpoints of the polynomial are unbounded (the source is
    // at x = -oo and the target is at x = +oo).
    _info = (_info | SRC_AT_X_MINUS_INFTY);
    _info = (_info | TRG_AT_X_PLUS_INFTY);
    _info = (_info | IS_DIRECTED_RIGHT);

    // Set the numerator polynomial.
    Nt_traits    nt_traits;
    Integer      p_factor;

    nt_traits.construct_polynomial (&(pcoeffs[0]),
                                    pcoeffs.size() - 1,
                                    _numer,
                                    p_factor);

    // Define the denominator to be a constant polynomial.
    Integer      denom_coeffs[1];

    denom_coeffs [0] = p_factor;
    _denom = nt_traits.construct_polynomial (denom_coeffs, 0);
    
    // Check whether the end points lie at y = -oo or at y = +oo.
    const int    deg_num = nt_traits.degree (_numer);
    CGAL::Sign   lead_sign;

    if (deg_num > 0)
    {
      // Check if the degree is even or odd and check the sign of the leading
      // coefficient of the polynomial.
      lead_sign = CGAL::sign (nt_traits.get_coefficient (_numer, deg_num));
      CGAL_assertion (lead_sign != CGAL::ZERO);

      if (deg_num % 2 == 0)
      {
        // Polynomial of an even degree.
        if (lead_sign == CGAL::NEGATIVE)
          _info = (_info | SRC_AT_Y_MINUS_INFTY | TRG_AT_Y_MINUS_INFTY);
        else
          _info = (_info | SRC_AT_Y_PLUS_INFTY | TRG_AT_Y_PLUS_INFTY);
      }
      else
      {
        // Polynomial of an odd degree.
        if (lead_sign == CGAL::NEGATIVE)
          _info = (_info | SRC_AT_Y_PLUS_INFTY | TRG_AT_Y_MINUS_INFTY);
        else
          _info = (_info | SRC_AT_Y_MINUS_INFTY | TRG_AT_Y_PLUS_INFTY);
      }
    }
    else
    {
      // In the case of a constant polynomial it is possible to set a finite
      // y-coordinate for the source and target points.
      Integer lead_coeff = (deg_num < 0) ? Integer(0) : 
        nt_traits.get_coefficient (_numer, deg_num);

      _ps = _pt = Point_2 (Algebraic(), nt_traits.convert (lead_coeff));
    }

    // Mark that the arc is continuous and valid.
    _info = (_info | IS_CONTINUOUS);
    _info = (_info | IS_VALID);
  }

  /*!
   * Constructor of a polynomial ray, defined by y = p(x), for x_s <= x if the
   * ray is directed to the right, or for x_s >= x if it is directed to the
   * left.
   * \param pcoeffs The rational coefficients of the polynomial p(x).
   * \param x_s The x-coordinate of the source point.
   * \param dir_right Is the ray directed to the right (to +oo)
   *                  or to the left (to -oo).
   */
  _Rational_arc_2 (const Rat_vector& pcoeffs,
                   const Algebraic& x_s, bool dir_right) :
    _info (0)
  {
    // Mark that the target points of the polynomial is unbounded.
    if (dir_right)
    {
      _info = (_info | TRG_AT_X_PLUS_INFTY);
      _info = (_info | IS_DIRECTED_RIGHT);
    }
    else
    {
      _info = (_info | TRG_AT_X_MINUS_INFTY);
    }

    // Set the numerator polynomial.
    Nt_traits    nt_traits;
    Integer      p_factor;

    nt_traits.construct_polynomial (&(pcoeffs[0]),
                                    pcoeffs.size() - 1,
                                    _numer,
                                    p_factor);

    // Define the denominator to be a constant polynomial.
    Integer      denom_coeffs[1];

    denom_coeffs [0] = p_factor;
    _denom = nt_traits.construct_polynomial (denom_coeffs, 0);

    // Set the source point.
    _ps = Point_2 (x_s, nt_traits.evaluate_at (_numer, x_s));
    
    // Check whether the target point lies at y = -oo or at y = +oo.
    const int    deg_num = nt_traits.degree (_numer);
    CGAL::Sign   lead_sign;

    if (deg_num > 0)
    {
      // Check if the degree is even or odd and check the sign of the leading
      // coefficient of the polynomial.
      lead_sign = CGAL::sign (nt_traits.get_coefficient (_numer, deg_num));
      CGAL_assertion (lead_sign != CGAL::ZERO);

      if (dir_right)
      {
        // The target is at x= +oo, thus:
        if (lead_sign == CGAL::POSITIVE)
          _info = (_info | TRG_AT_Y_PLUS_INFTY);
        else
          _info = (_info | TRG_AT_Y_MINUS_INFTY);
      }
      else
      {
        // The target is at x= -oo, thus:
        if ((deg_num % 2 == 0 && lead_sign == CGAL::POSITIVE) ||
            (deg_num % 2 == 1 && lead_sign == CGAL::NEGATIVE))
          _info = (_info | TRG_AT_Y_PLUS_INFTY);
        else
          _info = (_info | TRG_AT_Y_MINUS_INFTY);
      }
    }
    else
    {
      // In the case of a constant polynomial it is possible to set a finite
      // y-coordinate for the target point.
      Integer lead_coeff = (deg_num < 0) ? Integer(0) : 
        nt_traits.get_coefficient (_numer, deg_num);

      _pt = Point_2 (Algebraic(), nt_traits.convert (lead_coeff));
    }

    // Mark that the arc is continuous and valid.
    _info = (_info | IS_CONTINUOUS);
    _info = (_info | IS_VALID);
  }

  /*!
   * Constructor of a polynomial arc, defined by y = p(x), x_min <= x <= x_max.
   * \param pcoeffs The rational coefficients of the polynomial p(x).
   * \param x_s The x-coordinate of the source point.
   * \param x_t The x-coordinate of the target point.
   * \pre The two x-coordinate must not be equal.
   */
  _Rational_arc_2 (const Rat_vector& pcoeffs,
		   const Algebraic& x_s, const Algebraic& x_t) :
    _info (0)
  {
    // Compare the x-coordinates and determine the direction.
    Comparison_result   x_res = CGAL::compare (x_s, x_t);

    CGAL_precondition (x_res != EQUAL);
    if (x_res == EQUAL)
      return;

    if (x_res == SMALLER)
      _info = (_info | IS_DIRECTED_RIGHT);

    // Set the numerator polynomial.
    Nt_traits    nt_traits;
    Integer      p_factor;

    nt_traits.construct_polynomial (&(pcoeffs[0]),
                                    pcoeffs.size() - 1,
                                    _numer,
                                    p_factor);

    // Define the denominator to be a constant polynomial.
    Integer      denom_coeffs[1];

    denom_coeffs [0] = p_factor;
    _denom = nt_traits.construct_polynomial (denom_coeffs, 0);
    
    // Set the endpoints.
    _ps = Point_2 (x_s, nt_traits.evaluate_at (_numer, x_s));
    _pt = Point_2 (x_t, nt_traits.evaluate_at (_numer, x_t));

    // Mark that the arc is continuous and valid.
    _info = (_info | IS_CONTINUOUS);
    _info = (_info | IS_VALID);
  }    

  /*!
   * Constructor of a polynomial function, defined by y = p(x)/q(x) for any x.
   * \param pcoeffs The rational coefficients of the polynomial p(x).
   * \param qcoeffs The rational coefficients of the polynomial q(x).
   */
  _Rational_arc_2 (const Rat_vector& pcoeffs, const Rat_vector& qcoeffs) :
    _info (0)
  {
    // Mark that the endpoints of the rational functions are unbounded (the
    // source is at x = -oo and the target is at x = +oo).
    _info = (_info | SRC_AT_X_MINUS_INFTY);
    _info = (_info | TRG_AT_X_PLUS_INFTY);
    _info = (_info | IS_DIRECTED_RIGHT);

    // Set the numerator and denominator polynomials.
    Nt_traits    nt_traits;
    const bool   valid = 
      nt_traits.construct_polynomials (&(pcoeffs[0]),
					pcoeffs.size() - 1,
                                       &(qcoeffs[0]),
					qcoeffs.size() - 1,
                                       _numer, _denom);

    CGAL_precondition_msg (valid,
                           "The denominator polynomial must not be 0.");
    if (! valid)
      return;

    // Analyze the bahaviour of the rational function at x = -oo (the source).
    Algebraic           y0;
    const Boundary_type inf_s = _analyze_at_minus_infinity (_numer, _denom,
                                                            y0);

    if (inf_s == MINUS_INFINITY)
      _info = (_info | SRC_AT_Y_MINUS_INFTY);
    else if (inf_s == PLUS_INFINITY)
      _info = (_info | SRC_AT_Y_PLUS_INFTY);
    else // if (inf_s == NO_BOUNDARY)
      _ps = Point_2 (0, y0);

    // Analyze the bahaviour of the rational function at x = +oo (the target).
    const Boundary_type inf_t = _analyze_at_plus_infinity (_numer, _denom,
                                                           y0);

    if (inf_t == MINUS_INFINITY)
      _info = (_info | TRG_AT_Y_MINUS_INFTY);
    else if (inf_t == PLUS_INFINITY)
      _info = (_info | TRG_AT_Y_PLUS_INFTY);
    else // if (inf_t == NO_BOUNDARY)
      _pt = Point_2 (0, y0);

    // Mark that the arc is valid. As it may have poles, we do not mark it
    // as continuous.
    _info = (_info | IS_VALID);
  }

  /*!
   * Constructor of a ray of a rational function, defined by y = p(x)/q(x),
   * for x_s <= x if the ray is directed to the right, or for x_s >= x if it
   * is directed to the left.
   * \param pcoeffs The rational coefficients of the polynomial p(x).
   * \param qcoeffs The rational coefficients of the polynomial q(x).
   * \param x_s The x-coordinate of the source point.
   * \param dir_right Is the ray directed to the right (to +oo)
   *                  or to the left (to -oo).
   */
  _Rational_arc_2 (const Rat_vector& pcoeffs, const Rat_vector& qcoeffs,
                   const Algebraic& x_s, bool dir_right) :
    _info (0)
  {
    // Mark that the target points of the polynomial is unbounded.
    if (dir_right)
    {
      _info = (_info | TRG_AT_X_PLUS_INFTY);
      _info = (_info | IS_DIRECTED_RIGHT);
    }
    else
    {
      _info = (_info | TRG_AT_X_MINUS_INFTY);
    }

    // Set the numerator and denominator polynomials.
    Nt_traits    nt_traits;
    const bool   valid = 
      nt_traits.construct_polynomials (&(pcoeffs[0]),
					pcoeffs.size() - 1,
                                       &(qcoeffs[0]),
					qcoeffs.size() - 1,
                                       _numer, _denom);

    CGAL_precondition_msg (valid,
                           "The denominator polynomial must not be 0.");
    if (! valid)
      return;

    // The source point has a bounded x-coordinate. Set the source point
    // and check if it lies next to a pole.
    if (CGAL::sign (nt_traits.evaluate_at (_denom, x_s)) != CGAL::ZERO)
    {
      // We have a nomral endpoint.
      _ps = Point_2 (x_s, nt_traits.evaluate_at (_numer, x_s) /
                     nt_traits.evaluate_at (_denom, x_s));
    }
    else
    {
      // The y-coodinate is unbounded, but we can set its sign.
      _ps = Point_2 (x_s, 0);
      
      std::pair<CGAL::Sign, CGAL::Sign>  signs = _analyze_near_pole (x_s);
      const CGAL::Sign                   sign_s = 
        (dir_right ? signs.second : signs.first);

      if (sign_s == CGAL::NEGATIVE)
        _info = (_info | SRC_AT_Y_MINUS_INFTY);
      else
        _info = (_info | SRC_AT_Y_PLUS_INFTY);
    }

    // Set the properties of the target.
    Algebraic           y0;

    if (dir_right)
    {
      // The target point is at x = +oo.
      const Boundary_type inf_t = _analyze_at_plus_infinity (_numer, _denom,
                                                             y0);

      if (inf_t == MINUS_INFINITY)
        _info = (_info | TRG_AT_Y_MINUS_INFTY);
      else if (inf_t == PLUS_INFINITY)
        _info = (_info | TRG_AT_Y_PLUS_INFTY);
      else // if (inf_t == NO_BOUNDARY)
        _pt = Point_2 (0, y0);
    }
    else
    {
      // The target point is at x = -oo.
      const Boundary_type inf_t = _analyze_at_minus_infinity (_numer, _denom,
                                                              y0);

      if (inf_t == MINUS_INFINITY)
        _info = (_info | TRG_AT_Y_MINUS_INFTY);
      else if (inf_t == PLUS_INFINITY)
        _info = (_info | TRG_AT_Y_PLUS_INFTY);
      else // if (inf_t == NO_BOUNDARY)
        _pt = Point_2 (0, y0);
    }

    // Mark that the arc is valid. As it may have poles, we do not mark it
    // as continuous.
    _info = (_info | IS_VALID);
  }
  
  /*!
   * Constructor of a bounded rational arc, defined by y = p(x)/q(x), 
   * where: x_min <= x <= x_max.
   * \param pcoeffs The rational coefficients of the polynomial p(x).
   * \param qcoeffs The rational coefficients of the polynomial q(x).
   * \param x_s The x-coordinate of the source point.
   * \param x_t The x-coordinate of the target point.
   * \pre The two x-coordinate must not be equal,
   *      and q(x) != 0 for all x_min <= x <= x_max.
   */
  _Rational_arc_2 (const Rat_vector& pcoeffs, const Rat_vector& qcoeffs,
		   const Algebraic& x_s, const Algebraic& x_t) :
    _info (0)
  {
    // Compare the x-coordinates and determine the direction.
    Comparison_result   x_res = CGAL::compare (x_s, x_t);

    CGAL_precondition (x_res != EQUAL);
    if (x_res == EQUAL)
      return;

    if (x_res == SMALLER)
      _info = (_info | IS_DIRECTED_RIGHT);

    // Set the numerator and denominator polynomials.
    Nt_traits    nt_traits;
    const bool   valid = 
      nt_traits.construct_polynomials (&(pcoeffs[0]),
					pcoeffs.size() - 1,
                                       &(qcoeffs[0]),
					qcoeffs.size() - 1,
                                       _numer, _denom);

    CGAL_precondition_msg (valid,
                           "The denominator polynomial must not be 0.");
    if (! valid)
      return;

    // Set the source point and check if it lies next to a pole.
    if (CGAL::sign (nt_traits.evaluate_at (_denom, x_s)) != CGAL::ZERO)
    {
      // We have a nomral endpoint.
      _ps = Point_2 (x_s, nt_traits.evaluate_at (_numer, x_s) /
                          nt_traits.evaluate_at (_denom, x_s));
    }
    else
    {
      // The y-coodinate is unbounded, but we can set its sign.
      _ps = Point_2 (x_s, 0);

      std::pair<CGAL::Sign, CGAL::Sign>  signs = _analyze_near_pole (x_s);
      const CGAL::Sign                   sign_s =
        ((_info & IS_DIRECTED_RIGHT) != 0) ? signs.second : signs.first;

      if (sign_s == CGAL::NEGATIVE)
        _info = (_info | SRC_AT_Y_MINUS_INFTY);
      else
        _info = (_info | SRC_AT_Y_PLUS_INFTY);
    }

    // Set the target point and check if it lies next to a pole.
    if (CGAL::sign (nt_traits.evaluate_at (_denom, x_t)) != CGAL::ZERO)
    {
      // We have a nomral endpoint.
      _pt = Point_2 (x_t, nt_traits.evaluate_at (_numer, x_t) /
                     nt_traits.evaluate_at (_denom, x_t));
    }
    else
    {
      // The y-coodinate is unbounded, but we can set its sign.
      _pt = Point_2 (x_t, 0);
      
      std::pair<CGAL::Sign, CGAL::Sign>  signs = _analyze_near_pole (x_t);
      const CGAL::Sign                   sign_t =
        ((_info & IS_DIRECTED_RIGHT) != 0) ? signs.first : signs.second;

      if (sign_t == CGAL::NEGATIVE)
        _info = (_info | TRG_AT_Y_MINUS_INFTY);
      else
        _info = (_info | TRG_AT_Y_PLUS_INFTY);
    }

    // Mark that the arc is valid. As it may have poles, we do not mark it
    // as continuous.
    _info = (_info | IS_VALID);
  }

  /*!
   * Break an arc of a rational function into continuous sub-arcs, splitting
   * it at its poles.
   */
  template <class OutputIterator>
  OutputIterator make_continuous (OutputIterator oi) const
  {
    // Compute the roots of the denominator polynomial.
    std::list<Algebraic>                 q_roots;
    bool                                 root_at_ps, root_at_pt;

    if ((_info & IS_CONTINUOUS) == 0)
      _denominator_roots (std::back_inserter (q_roots),
                          root_at_ps, root_at_pt);

    // Check the case of a continuous arc:
    if (q_roots.empty())
    {
      Self    arc = *this;

      arc._info = (arc._info | IS_CONTINUOUS);
      *oi = arc;
      ++oi;
      return (oi);
    }

    // Split the arc accordingly.
    typename std::list<Algebraic>::const_iterator iter;
    Self                                          arc = *this;

    for (iter = q_roots.begin(); iter != q_roots.end(); ++iter)
    {
      *oi = arc._split_at_pole (*iter);
      ++oi;
    }

    // Add the final x-monotone sub-arc.
    arc._info = (arc._info | IS_CONTINUOUS);
    *oi = arc;
    ++oi;

    return (oi);
  }
  //@}

  /// \name Accessing the arc properties.
  //@{

  /*! Get the numerator polynomial of the underlying rational function. */
  const Polynomial& numerator () const
  {
    return (_numer);
  }

  /*! Get the denominator polynomial of the underlying rational function. */
  const Polynomial& denominator () const
  {
    return (_denom);
  }

  /*! Check if the x-coordinate of the source point is infinite. */
  Boundary_type source_boundary_in_x () const
  {
    if ((_info & SRC_AT_X_MINUS_INFTY) != 0)
      return (MINUS_INFINITY);
    else if ((_info & SRC_AT_X_PLUS_INFTY) != 0)
      return (PLUS_INFINITY);
    else
      return (NO_BOUNDARY);
  }

  /*! Check if the y-coordinate of the source point is infinite. */
  Boundary_type source_boundary_in_y () const
  {
    if ((_info & SRC_AT_Y_MINUS_INFTY) != 0)
      return (MINUS_INFINITY);
    else if ((_info & SRC_AT_Y_PLUS_INFTY) != 0)
      return (PLUS_INFINITY);
    else
      return (NO_BOUNDARY);
  }

  /*! Check if the x-coordinate of the target point is infinite. */
  Boundary_type target_boundary_in_x () const
  {
    if ((_info & TRG_AT_X_MINUS_INFTY) != 0)
      return (MINUS_INFINITY);
    else if ((_info & TRG_AT_X_PLUS_INFTY) != 0)
      return (PLUS_INFINITY);
    else
      return (NO_BOUNDARY);
  }

  /*! Check if the y-coordinate of the target point is infinite. */
  Boundary_type target_boundary_in_y () const
  {
    if ((_info & TRG_AT_Y_MINUS_INFTY) != 0)
      return (MINUS_INFINITY);
    else if ((_info & TRG_AT_Y_PLUS_INFTY) != 0)
      return (PLUS_INFINITY);
    else
      return (NO_BOUNDARY);
  }

  /*! Get the source point. */
  const Point_2& source () const
  {
    CGAL_precondition ((_info & IS_VALID) != 0 &&
                       source_boundary_in_x() == NO_BOUNDARY &&
                       source_boundary_in_y() == NO_BOUNDARY);
    return (_ps);
  }

  /*! Get the x-coordinate of the source point. */
  Algebraic source_x () const
  {
    CGAL_precondition ((_info & IS_VALID) != 0 &&
                       source_boundary_in_x() == NO_BOUNDARY);
    return (_ps.x());
  }

  /*! Get the y-coordinate of the source point. */
  Algebraic source_y () const
  {
    CGAL_precondition ((_info & IS_VALID) != 0 &&
                       source_boundary_in_y() == NO_BOUNDARY);
    return (_ps.y());
  }

  /*! Get the target point. */
  const Point_2& target () const
  {
    CGAL_precondition ((_info & IS_VALID) != 0 &&
                       target_boundary_in_x() == NO_BOUNDARY &&
                       target_boundary_in_y() == NO_BOUNDARY);
    return (_pt);
  }

  /*! Get the x-coordinate of the target point. */
  Algebraic target_x () const
  {
    CGAL_precondition ((_info & IS_VALID) != 0 &&
                       target_boundary_in_x() == NO_BOUNDARY);
    return (_pt.x());
  }

  /*! Get the y-coordinate of the target point. */
  Algebraic target_y () const
  {
    CGAL_precondition ((_info & IS_VALID) != 0 &&
                       target_boundary_in_y() == NO_BOUNDARY);
    return (_pt.y());
  }

  /*! Check if the x-coordinate of the left point is infinite. */
  Boundary_type left_boundary_in_x () const
  {
    if ((_info & IS_DIRECTED_RIGHT) != 0)
      return (source_boundary_in_x());
    else
      return (target_boundary_in_x());
  }

  /*! Check if the y-coordinate of the left point is infinite. */
  Boundary_type left_boundary_in_y () const
  {
    if ((_info & IS_DIRECTED_RIGHT) != 0)
      return (source_boundary_in_y());
    else
      return (target_boundary_in_y());
  }

  /*! Check if the x-coordinate of the right point is infinite. */
  Boundary_type right_boundary_in_x () const
  {
    if ((_info & IS_DIRECTED_RIGHT) != 0)
      return (target_boundary_in_x());
    else
      return (source_boundary_in_x());
  }

  /*! Check if the y-coordinate of the right point is infinite. */
  Boundary_type right_boundary_in_y () const
  {
    if ((_info & IS_DIRECTED_RIGHT) != 0)
      return (target_boundary_in_y());
    else
      return (source_boundary_in_y());
  }

  /*! Get the left endpoint. */
  const Point_2& left () const
  {
    CGAL_precondition (left_boundary_in_x() == NO_BOUNDARY &&
                       left_boundary_in_y() == NO_BOUNDARY);
    return ((_info & IS_DIRECTED_RIGHT) ? _ps : _pt);
  }

  /*! Get the right endpoint. */
  const Point_2& right () const
  {
    CGAL_precondition (right_boundary_in_x() == NO_BOUNDARY &&
                       right_boundary_in_y() == NO_BOUNDARY);
    return ((_info & IS_DIRECTED_RIGHT) ? _pt : _ps);
  }

  /*! Check if the arc is valid. */
  bool is_valid () const
  {
    return ((_info & IS_VALID) != 0);
  }

  /*! Check if the arc is continuous. */
  bool is_continuous () const
  {
    return ((_info & IS_CONTINUOUS) != 0);
  }

  /*! Check if the arc is directed right. */
  bool is_directed_right () const
  {
    return ((_info & IS_DIRECTED_RIGHT) != 0);
  }
  //@}

  /// \name Predicates.
  //@{

  /*!
   * Get the relative position of the point with respect to the rational arc.
   * \param p The query point.
   * \pre p is in the x-range of the arc.
   * \return SMALLER if the point is below the arc;
   *         LARGER if the point is above the arc;
   *         EQUAL if p lies on the arc.
   */
  Comparison_result point_position (const Point_2& p) const
  {
    // Make sure that p is in the x-range of the arc and check whether it
    // has the same x-coordinate as one of the endpoints.
    CGAL_precondition (is_continuous());
    CGAL_precondition (_is_in_true_x_range (p.x()));

    // Evaluate the rational function at x(p), which lies at the interior
    // of the x-range.
    Nt_traits   nt_traits;
    Algebraic   y = nt_traits.evaluate_at (_numer, p.x()) /
                    nt_traits.evaluate_at (_denom, p.x());
    
    // Compare the resulting y-coordinate with y(p):
    return (CGAL::compare (p.y(), y));
  }

  /*!
   * Compare the x-coordinate of a vertical asymptote of the arc (one of its
   * ends) and the given point.
   */
  Comparison_result compare_end (const Point_2& p,
                                 Curve_end ind) const
  {
    Algebraic                x0;

    if (ind == MIN_END)
    {
      CGAL_assertion (left_boundary_in_x() == NO_BOUNDARY &&
                      left_boundary_in_y() != NO_BOUNDARY);
      if ((_info & IS_DIRECTED_RIGHT) != 0)
        x0 = _ps.x();
      else
        x0 = _pt.x();
    }
    else
    {
      CGAL_assertion (right_boundary_in_x() == NO_BOUNDARY &&
                      right_boundary_in_y() != NO_BOUNDARY);
      if ((_info & IS_DIRECTED_RIGHT) != 0)
        x0 = _pt.x();
      else
        x0 = _ps.x();
    }

    // Compare the x-coordinates.
    const Comparison_result  res = CGAL::compare (p.x(), x0);

    if (res != EQUAL)
      return (res);

    return ((ind == MIN_END) ? SMALLER : LARGER);
  }

  /*!
   * Compare the x-coordinate of a vertical asymptotes of the two arcs.
   */
  Comparison_result compare_ends (Curve_end ind1,
                                  const Self& arc, Curve_end ind2) const
  {
    // Get the x-coordinates of the first vertical asymptote.
    Algebraic                x1;

    if (ind1 == MIN_END)
    {
      CGAL_assertion (left_boundary_in_x() == NO_BOUNDARY &&
                      left_boundary_in_y() != NO_BOUNDARY);
      if ((_info & IS_DIRECTED_RIGHT) != 0)
        x1 = _ps.x();
      else
        x1 = _pt.x();
    }
    else
    {
      CGAL_assertion (right_boundary_in_x() == NO_BOUNDARY &&
                      right_boundary_in_y() != NO_BOUNDARY);
      if ((_info & IS_DIRECTED_RIGHT) != 0)
        x1 = _pt.x();
      else
        x1 = _ps.x();
    }

    // Get the x-coordinates of the second vertical asymptote.
    Algebraic                x2;

    if (ind2 == MIN_END)
    {
      CGAL_assertion (arc.left_boundary_in_x() == NO_BOUNDARY &&
                      arc.left_boundary_in_y() != NO_BOUNDARY);
      if ((arc._info & IS_DIRECTED_RIGHT) != 0)
        x2 = arc._ps.x();
      else
        x2 = arc._pt.x();
    }
    else
    {
      CGAL_assertion (arc.right_boundary_in_x() == NO_BOUNDARY &&
                      arc.right_boundary_in_y() != NO_BOUNDARY);
      if ((arc._info & IS_DIRECTED_RIGHT) != 0)
        x2 = arc._pt.x();
      else
        x2 = arc._ps.x();
    }

    // Compare the x-coordinates. In case they are not equal we are done.
    const Comparison_result  res = CGAL::compare (x1, x2);

    if (res != EQUAL)
      return (res);

    // If the x-coordinates of the asymptote are equal, but one arc is
    // defined to the left of the vertical asymptote and the other to its
    // right, we can easily determine the comparison result.
    if (ind1 == MAX_END && ind2 == MIN_END)
      return (SMALLER);
    else if (ind1 == MIN_END && ind2 == MAX_END)
      return (LARGER);

    // Determine the multiplicities of the pole for the two arcs.
    Nt_traits         nt_traits;
    int               mult1 = 1;
    Polynomial        p_der = nt_traits.derive (_denom);

    while (CGAL::sign (nt_traits.evaluate_at (p_der, x1)) == CGAL::ZERO)
    {
      mult1++;
      p_der = nt_traits.derive (p_der);
    }

    int               mult2 = 1;

    p_der = nt_traits.derive (arc._denom);
    while (CGAL::sign (nt_traits.evaluate_at (p_der, x1)) == CGAL::ZERO)
    {
      mult2++;
      p_der = nt_traits.derive (p_der);
    }

    if (mult1 != mult2)
    {
      if (ind1 == MIN_END)
      {
        // In case we compare to the right of the pole, the curve with larger
        // multiplicity is to the left.
        return ((mult1 > mult2) ? SMALLER : LARGER);
      }
      else
      {
        // In case we compare to the left of the pole, the curve with larger
        // multiplicity is to the right.
        return ((mult1 < mult2) ? SMALLER : LARGER);
      }
    }

    // The pole multiplicities are the same. If we denote the two rational
    // functions we have as P1(x)/Q1(x) and P2(X)/Q2(x), then we can divide
    // Q1(x) and Q2(x). As Q1(x') = Q2(x') = 0 (where x' is our current pole),
    // the zeros cancel themselves and we consider the value of our function
    // at x'.
    int            deg_q1 = nt_traits.degree (_denom);
    Rat_vector     coeffs_q1 (deg_q1 + 1);
    int            deg_q2 = nt_traits.degree (arc._denom);
    Rat_vector     coeffs_q2 (deg_q2 + 1);
    int            k;

    for (k = 0; k <= deg_q1; k++)
      coeffs_q1[k] = Rational (nt_traits.get_coefficient (_denom, k), 1);

    for (k = 0; k <= deg_q2; k++)
      coeffs_q2[k] = Rational (nt_traits.get_coefficient (arc._denom, k), 1);

    Polynomial         norm_q1, norm_q2;
    nt_traits.construct_polynomials (&(coeffs_q1[0]), deg_q1,
                                     &(coeffs_q2[0]), deg_q2,
                                     norm_q1, norm_q2);

    const Algebraic    val_q1 = CGAL::abs (nt_traits.evaluate_at (norm_q1, x1));
    const Algebraic    val_q2 = CGAL::abs (nt_traits.evaluate_at (norm_q2, x1));
    Comparison_result  val_res = CGAL::compare (val_q1, val_q2);
    
    if (val_res != EQUAL)
    {
      if (ind1 == MIN_END)
        // Swap the comparison result.
        val_res = (val_res == LARGER ? SMALLER : LARGER);

      return (val_res);
    }

    // Both arcs are defined to the same side (left or right) of the vertical
    // asymptote. If one is defined at y = -oo and the other at y = +oo, we
    // preform a "lexicographic" comparison.
    const Boundary_type  inf_y1 = 
      (ind1 == MIN_END ? left_boundary_in_y() : right_boundary_in_y());
    const Boundary_type  inf_y2 = 
      (ind2 == MIN_END ? arc.left_boundary_in_y() : arc.right_boundary_in_y());

    if (inf_y1 == MINUS_INFINITY && inf_y2 == PLUS_INFINITY)
      return (SMALLER);
    else if (inf_y1 == PLUS_INFINITY && inf_y2 == MINUS_INFINITY)
      return (LARGER);

    // If we reached here, the denominators Q1 and Q2 are equal. We therefore
    // evaluate P1(x') and P2(x') and find the relative x-positions of the
    // curve ends by considering their comparison result.
    const Algebraic    val_p1 = nt_traits.evaluate_at (_numer, x1);
    const Algebraic    val_p2 = nt_traits.evaluate_at (arc._numer, x1);
    
    val_res = CGAL::compare (val_p1, val_p2);

    if (val_res == EQUAL)
    {
      CGAL_assertion (_has_same_base (arc));
      return (EQUAL);
    }

    if (ind1 == MAX_END)
      // Swap the comparison result.
      val_res = (val_res == LARGER ? SMALLER : LARGER);

    return (val_res);
  }

  /*!
   * Compare the slopes of the arc with another given arc at their given 
   * intersection point.
   * \param cv The given arc.
   * \param p The intersection point.
   * \param mult Output: The mutiplicity of the intersection point.
   * \return SMALLER if (*this) slope is less than cv's;
   *         EQUAL if the two slopes are equal;
   *         LARGER if (*this) slope is greater than cv's.
   */
  Comparison_result compare_slopes (const Self& arc,
				    const Point_2& p,
				    unsigned int& mult) const
  {
    // Make sure that p is in the x-range of both arcs.
    CGAL_precondition (is_valid());
    CGAL_precondition (arc.is_valid());
    CGAL_precondition (_is_in_true_x_range (p.x()) &&
		       arc._is_in_true_x_range (p.x()));

    // Check the case of overlapping arcs.
    if (_has_same_base (arc))
      return (EQUAL);

    // The intersection point may have a maximal multiplicity value of:
    //   max (deg(p1) + deg(q2), deg(q1) + deg(p2)).
    const Algebraic&  _x = p.x();
    Nt_traits         nt_traits;
    Polynomial        pnum1 = this->_numer;
    Polynomial        pden1 = this->_denom;
    const bool        simple_poly1 = (nt_traits.degree (pden1) <= 0);
    Polynomial        pnum2 = arc._numer;
    Polynomial        pden2 = arc._denom;
    const bool        simple_poly2 = (nt_traits.degree (pden2) <= 0);
    int               max_mult;
    Algebraic         d1, d2;
    Comparison_result res;

    max_mult = nt_traits.degree (pnum1) + nt_traits.degree (pden2);

    if (nt_traits.degree (pden1) + nt_traits.degree (pnum2) > max_mult)
      max_mult = nt_traits.degree (pden1) + nt_traits.degree (pnum2);

    for (mult = 1; mult <= static_cast<unsigned int>(max_mult); mult++)
    {
      // Compute the current derivative. Use the equation:
      //
      // (p(x) / q(x))' = (p'(x)*q(x) - p(x)*q'(x)) / q^2(x)
      if (simple_poly1)
      {
	pnum1 = nt_traits.derive(pnum1);
      }
      else
      {
	pnum1 = nt_traits.derive(pnum1)*pden1 - pnum1*nt_traits.derive(pden1);
	pden1 *= pden1;
      }

      if (simple_poly2)
      {
	pnum2 = nt_traits.derive(pnum2);
      }
      else
      {
	pnum2 = nt_traits.derive(pnum2)*pden2 - pnum2*nt_traits.derive(pden2);
	pden2 *= pden2;
      }

      // Compute the two derivative values and compare them. 
      d1 = nt_traits.evaluate_at (pnum1, _x) / 
	   nt_traits.evaluate_at (pden1, _x);
      d2 = nt_traits.evaluate_at (pnum2, _x) / 
	   nt_traits.evaluate_at (pden2, _x);

      res = CGAL::compare (d1, d2);

      // Stop here in case the derivatives are not equal.
      if (res != EQUAL)
	return (res);
    }

    // If we reached here, there is an overlap.
    return (EQUAL);
  }

  /*!
   * Compare the two arcs at x = -oo.
   * \param arc The given arc.
   * \pre Both arcs have a left end which is unbounded in x.
   * \return SMALLER if (*this) lies below the other arc;
   *         EQUAL if the two supporting functions are equal;
   *         LARGER if (*this) lies above the other arc.
   */
  Comparison_result compare_at_minus_infinity (const Self& arc) const
  {
    CGAL_precondition (left_boundary_in_x() == MINUS_INFINITY &&
                       arc.left_boundary_in_x() == MINUS_INFINITY);

    // Check for easy cases, when the infinity at y of both ends is different.
    const Boundary_type  inf_y1 = left_boundary_in_y();
    const Boundary_type  inf_y2 = arc.left_boundary_in_y();

    if (inf_y1 != inf_y2)
    {
      if (inf_y1 == MINUS_INFINITY || inf_y2 == PLUS_INFINITY)
        return (SMALLER);
      else if (inf_y1 == PLUS_INFINITY || inf_y2 == MINUS_INFINITY)
        return (LARGER);
      else
        CGAL_assertion (false);
    }

    // First compare the signs of the two denominator polynomials at x = -oo.
    const CGAL::Sign  sign1 = _sign_at_minus_infinity (_denom);
    const CGAL::Sign  sign2 = _sign_at_minus_infinity (arc._denom);
   
    CGAL_assertion (sign1 != CGAL::ZERO && sign2 != CGAL::ZERO);

    const bool        flip_res = (sign1 != sign2);

    // We wish to compare the two following functions:
    //
    //   y = p1(x)/q1(x)    and     y = p2(x)/q2(x)
    //
    // It is clear that we should look at the sign of the polynomial
    // p1(x)*q2(x) - p2(x)*q1(x) at x = -oo.
    const CGAL::Sign  sign_ip = _sign_at_minus_infinity (_numer*arc._denom - 
                                                         arc._numer*_denom);

    if (sign_ip == CGAL::ZERO)
    {
      CGAL_assertion (_has_same_base (arc));
      return (EQUAL);
    }

    if (sign_ip == CGAL::NEGATIVE)
      return (flip_res ? LARGER : SMALLER);
    else
      return (flip_res ? SMALLER : LARGER);
  }

  /*!
   * Compare the two arcs at x = +oo.
   * \param arc The given arc.
   * \pre Both arcs are have a right end which is unbounded in x.
   * \return SMALLER if (*this) lies below the other arc;
   *         EQUAL if the two supporting functions are equal;
   *         LARGER if (*this) lies above the other arc.
   */
  Comparison_result compare_at_plus_infinity (const Self& arc) const
  {
    CGAL_precondition (right_boundary_in_x() == PLUS_INFINITY &&
                       arc.right_boundary_in_x() == PLUS_INFINITY);

    // Check for easy cases, when the infinity at y of both ends is different.
    const Boundary_type  inf_y1 = right_boundary_in_y();
    const Boundary_type  inf_y2 = arc.right_boundary_in_y();

    if (inf_y1 != inf_y2)
    {
      if (inf_y1 == MINUS_INFINITY || inf_y2 == PLUS_INFINITY)
        return (SMALLER);
      else if (inf_y1 == PLUS_INFINITY || inf_y2 == MINUS_INFINITY)
        return (LARGER);
      else
        CGAL_assertion (false);
    }

    // First compare the signs of the two denominator polynomials at x = +oo.
    const CGAL::Sign  sign1 = _sign_at_plus_infinity (_denom);
    const CGAL::Sign  sign2 = _sign_at_plus_infinity (arc._denom);
   
    CGAL_assertion (sign1 != CGAL::ZERO && sign2 != CGAL::ZERO);

    const bool        flip_res = (sign1 != sign2);

    // We wish to compare the two following functions:
    //
    //   y = p1(x)/q1(x)    and     y = p2(x)/q2(x)
    //
    // It is clear that we should look at the sign of the polynomial
    // p1(x)*q2(x) - p2(x)*q1(x) at x = +oo.
    const CGAL::Sign  sign_ip = _sign_at_plus_infinity (_numer*arc._denom - 
                                                        arc._numer*_denom);

    if (sign_ip == CGAL::ZERO)
    {
      CGAL_assertion (_has_same_base (arc));
      return (EQUAL);
    }

    if (sign_ip == CGAL::NEGATIVE)
      return (flip_res ? LARGER : SMALLER);
    else
      return (flip_res ? SMALLER : LARGER);
  }

  /*!
   * Check whether the two arcs are equal (have the same graph).
   * \param arc The compared arc.
   * \return (true) if the two arcs have the same graph; (false) otherwise.
   */
  bool equals (const Self& arc) const
  {
    // The two arc must have the same base rational function.
    CGAL_precondition (is_valid());
    CGAL_precondition (arc.is_valid());
    if (! _has_same_base (arc))
      return (false);

    // Check that the arc endpoints are the same.
    Boundary_type inf1 = left_boundary_in_x ();
    Boundary_type inf2 = arc.left_boundary_in_x ();

    if (inf1 != inf2)
      return (false);

    if (inf1 == NO_BOUNDARY && CGAL::compare(left().x(), arc.left().x()) != EQUAL)
      return (false);

    inf1 = right_boundary_in_x ();
    inf2 = arc.right_boundary_in_x ();

    if (inf1 != inf2)
      return (false);

    if (inf1 == NO_BOUNDARY && CGAL::compare(right().x(), arc.right().x()) != EQUAL)
      return (false);

    // If we reached here, the two arc are equal:
    return (true);
  }

  /*!
   * Check whether it is possible to merge the arc with the given arc.
   * \param arc The query arc.
   * \return (true) if it is possible to merge the two arcs;
   *         (false) otherwise.
   */
  bool can_merge_with (const Self& arc) const
  {
    // In order to merge the two arcs, they should have the same base rational
    // function.
    CGAL_precondition (is_valid());
    CGAL_precondition (arc.is_valid());
    if (! _has_same_base (arc))
      return (false);

    // Check if the left endpoint of one curve is the right endpoint of the
    // other.
    Alg_kernel   ker;

    return ((right_boundary_in_x() == NO_BOUNDARY &&
             right_boundary_in_y() == NO_BOUNDARY &&
             arc.left_boundary_in_x() == NO_BOUNDARY &&
             arc.left_boundary_in_y() == NO_BOUNDARY &&
             ker.equal_2_object() (right(), arc.left())) ||
            (left_boundary_in_x() == NO_BOUNDARY &&
             left_boundary_in_y() == NO_BOUNDARY &&
             arc.right_boundary_in_x() == NO_BOUNDARY &&
             arc.right_boundary_in_y() == NO_BOUNDARY &&
             ker.equal_2_object() (left(), arc.right())));
  }
  //@}

  /// \name Constructions of points and curves.
  //@{
  
  /*!
   * Compute the intersections with the given arc.
   * \param arc The given intersecting arc.
   * \param oi The output iterator.
   * \return The past-the-end iterator.
   */
  template<class OutputIterator>
  OutputIterator intersect (const Self& arc,
                            OutputIterator oi) const
  {
    CGAL_precondition (is_valid() && is_continuous());
    CGAL_precondition (arc.is_valid() && arc.is_continuous());

    if (_has_same_base (arc))
    {
      Alg_kernel       ker;

      // Get the left and right endpoints of (*this) and their information
      // bits.
      const Point_2&   left1 = (is_directed_right() ? _ps : _pt);
      const Point_2&   right1 = (is_directed_right() ? _pt : _ps);
      int              info_left1, info_right1;

      if (is_directed_right())
      {
        info_left1 = (_info & SRC_INFO_BITS);
        info_right1 = ((_info & TRG_INFO_BITS) >> 4);
      }
      else
      {
        info_right1 = (_info & SRC_INFO_BITS);
        info_left1 = ((_info & TRG_INFO_BITS) >> 4);
      }

      // Get the left and right endpoints of the other arc and their
      // information bits.
      const Point_2&   left2 = (arc.is_directed_right() ? arc._ps : arc._pt);
      const Point_2&   right2 = (arc.is_directed_right() ? arc._pt : arc._ps);
      int              info_left2, info_right2;

      if (arc.is_directed_right())
      {
        info_left2 = (arc._info & SRC_INFO_BITS);
        info_right2 = ((arc._info & TRG_INFO_BITS) >> 4);
      }
      else
      {
        info_right2 = (arc._info & SRC_INFO_BITS);
        info_left2 = ((arc._info & TRG_INFO_BITS) >> 4);
      }

      // Locate the left curve-end with larger x-coordinate.
      bool             at_minus_infinity = false;
      Boundary_type    inf_l1 = left_boundary_in_x();
      Boundary_type    inf_l2 = arc.left_boundary_in_x();
      Point_2          p_left;
      int              info_left;

      if (inf_l1 == NO_BOUNDARY && inf_l2 == NO_BOUNDARY)
      {
        // Let p_left be the rightmost of the two left endpoints.
        if (ker.compare_x_2_object() (left1, left2) == LARGER)
        {
          p_left = left1;
          info_left = info_left1;
        }
        else
        {
          p_left = left2;
          info_left = info_left2;
        }
      }
      else if (inf_l1 == NO_BOUNDARY)
      {
        // Let p_left be the left endpoint of (*this).
        p_left = left1;
        info_left = info_left1;
      }
      else if (inf_l2 == NO_BOUNDARY)
      {
        // Let p_left be the left endpoint of the other arc.
        p_left = left2;
        info_left = info_left2;
      }
      else
      {
        // Both arcs are defined at x = -oo.
        at_minus_infinity = true;
        info_left = info_left1;
      }

      // Locate the right curve-end with smaller x-coordinate.
      bool             at_plus_infinity = false;
      Boundary_type    inf_r1 = right_boundary_in_x();
      Boundary_type    inf_r2 = arc.right_boundary_in_x();
      Point_2          p_right;
      int              info_right;

      if (inf_r1 == NO_BOUNDARY && inf_r2 == NO_BOUNDARY)
      {
        // Let p_right be the rightmost of the two right endpoints.
        if (ker.compare_x_2_object() (right1, right2) == SMALLER)
        {
          p_right = right1;
          info_right = info_right1;
        }
        else
        {
          p_right = right2;
          info_right = info_right2;
        }
      }
      else if (inf_r1 == NO_BOUNDARY)
      {
        // Let p_right be the right endpoint of (*this).
        p_right = right1;
        info_right = info_right1;
      }
      else if (inf_r2 == NO_BOUNDARY)
      {
        // Let p_right be the right endpoint of the other arc.
        p_right = right2;
        info_right = info_right2;
      }
      else
      {
        // Both arcs are defined at x = +oo.
        at_plus_infinity = true;
        info_right = info_right2;
      }

      // Check the case of two bounded (in x) ends.
      if (! at_minus_infinity && ! at_plus_infinity)
      {
        Comparison_result res = ker.compare_x_2_object() (p_left, p_right);

        if (res == LARGER)
        {
          // The x-range of the overlap is empty, so there is no overlap.
          return (oi);
        }
        else if (res == EQUAL)
        {
          // We have a single overlapping point. Just make sure this point
          // is not at y = -/+ oo.
          if (info_left && (SRC_AT_Y_MINUS_INFTY | SRC_AT_Y_PLUS_INFTY) == 0 &&
              info_right && (SRC_AT_Y_MINUS_INFTY | SRC_AT_Y_PLUS_INFTY) == 0)
          {
            Intersection_point_2  ip (p_left, 0);
	
            *oi = make_object (ip);
            ++oi;
          }

          return (oi);
        }
      }

      // Create the overlapping portion of the rational arc by properly setting
      // the source (left) and target (right) endpoints and their information
      // bits.
      Self      overlap_arc (*this);

      overlap_arc._ps = p_left;
      overlap_arc._pt = p_right;

      overlap_arc._info = ((info_left) | (info_right << 4) |
                           IS_DIRECTED_RIGHT | IS_CONTINUOUS | IS_VALID);

      *oi = make_object (overlap_arc);
      ++oi;

      return (oi);
    }
    
    // We wish to find the intersection points between:
    //
    //   y = p1(x)/q1(x)    and     y = p2(x)/q2(x)
    //
    // It is clear that the x-coordinates of the intersection points are
    // the roots of the polynomial: ip(x) = p1(x)*q2(x) - p2(x)*q1(x).
    Nt_traits            nt_traits;
    Polynomial           ipoly = _numer*arc._denom - arc._numer*_denom;
    std::list<Algebraic>                           xs;
    typename std::list<Algebraic>::const_iterator  x_iter;

    nt_traits.compute_polynomial_roots (ipoly,
					std::back_inserter(xs));
    
    // Go over the x-values we obtained. For each value produce an
    // intersection point if it is contained in the x-range of both curves.
    unsigned int                     mult;

    for (x_iter = xs.begin(); x_iter != xs.end(); ++x_iter)
    {
      if (_is_in_true_x_range (*x_iter) &&
          arc._is_in_true_x_range (*x_iter))
      {
	// Compute the intersection point and obtain its multiplicity.
	Point_2    p (*x_iter, nt_traits.evaluate_at (_numer, *x_iter) /
                               nt_traits.evaluate_at (_denom, *x_iter));

	this->compare_slopes (arc, p, mult);
    
	// Output the intersection point:
	Intersection_point_2  ip (p, mult);
	
	*oi = make_object (ip);
	++oi;
      }
    }

    return (oi);
  }

  /*!
   * Split the arc into two at a given split point.
   * \param p The split point.
   * \param c1 Output: The first resulting arc, lying to the left of p.
   * \param c2 Output: The first resulting arc, lying to the right of p.
   * \pre p lies in the interior of the arc (not one of its endpoints).
   */
  void split (const Point_2& p,
              Self& c1, Self& c2) const
  {
    CGAL_precondition (is_valid() && is_continuous());

    // Make sure that p lies on the interior of the arc.
    CGAL_precondition_code (
      Alg_kernel   ker;
    );
    CGAL_precondition (this->point_position(p) == EQUAL &&
                       (source_boundary_in_x() != NO_BOUNDARY ||
                        source_boundary_in_y() != NO_BOUNDARY ||
                        ! ker.equal_2_object() (p, _ps)) &&
                       (target_boundary_in_x() != NO_BOUNDARY ||
                        target_boundary_in_y() != NO_BOUNDARY ||
                        ! ker.equal_2_object() (p, _pt)));

    // Make copies of the current arc.
    c1 = *this;
    c2 = *this;

    // Split the arc, such that c1 lies to the left of c2.
    if ((_info & IS_DIRECTED_RIGHT) != 0)
    {
      c1._pt = p;
      c1._info = (c1._info & ~TRG_INFO_BITS);
      c2._ps = p;
      c2._info = (c2._info & ~SRC_INFO_BITS);
    }
    else
    {
      c1._ps = p;
      c1._info = (c1._info & ~SRC_INFO_BITS);
      c2._pt = p;
      c2._info = (c2._info & ~TRG_INFO_BITS);
   }

    return;
  }

  /*!
   * Merge the current arc with the given arc.
   * \param arc The arc to merge with.
   * \pre The two arcs are mergeable.
   */
  void merge (const Self& arc)
  {
    CGAL_precondition (is_valid() && is_continuous());
    CGAL_precondition (arc.is_valid() && arc.is_continuous());
    CGAL_precondition (this->can_merge_with (arc));

    // Check if we should extend the arc to the left or to the right.
    Alg_kernel   ker;

    if (right_boundary_in_x() == NO_BOUNDARY &&
        right_boundary_in_y() == NO_BOUNDARY &&
        arc.left_boundary_in_x() == NO_BOUNDARY &&
        arc.left_boundary_in_y() == NO_BOUNDARY &&
        ker.equal_2_object() (right(), arc.left()))
    {
      // Extend the arc to the right.
      if ((_info & IS_DIRECTED_RIGHT) != 0)
      {
        if (arc.right_boundary_in_x() == NO_BOUNDARY &&
            arc.right_boundary_in_y() == NO_BOUNDARY)
        {
          _pt = arc.right();
        }
        else
        {
          if (arc.right_boundary_in_x() == MINUS_INFINITY)
            _info = (_info | TRG_AT_X_MINUS_INFTY);
          else if (arc.right_boundary_in_x() == PLUS_INFINITY)
            _info = (_info | TRG_AT_X_PLUS_INFTY);

          if (arc.right_boundary_in_y() == MINUS_INFINITY)
            _info = (_info | TRG_AT_Y_MINUS_INFTY);
          else if (arc.right_boundary_in_y() == PLUS_INFINITY)
            _info = (_info | TRG_AT_Y_PLUS_INFTY);
        }
      }
      else
      {
        if (arc.right_boundary_in_x() == NO_BOUNDARY &&
            arc.right_boundary_in_y() == NO_BOUNDARY)
        {
          _ps = arc.right();
        }
        else
        {
          if (arc.right_boundary_in_x() == MINUS_INFINITY)
            _info = (_info | SRC_AT_X_MINUS_INFTY);
          else if (arc.right_boundary_in_x() == PLUS_INFINITY)
            _info = (_info | SRC_AT_X_PLUS_INFTY);

          if (arc.right_boundary_in_y() == MINUS_INFINITY)
            _info = (_info | SRC_AT_Y_MINUS_INFTY);
          else if (arc.right_boundary_in_y() == PLUS_INFINITY)
            _info = (_info | SRC_AT_Y_PLUS_INFTY);
        }
      }
    }
    else
    {
      CGAL_precondition (left_boundary_in_x() == NO_BOUNDARY &&
                         left_boundary_in_y() == NO_BOUNDARY &&
                         arc.right_boundary_in_x() == NO_BOUNDARY &&
                         arc.right_boundary_in_y() == NO_BOUNDARY &&
                         ker.equal_2_object() (left(), arc.right()));

      // Extend the arc to the left.
      if ((_info & IS_DIRECTED_RIGHT) != 0)
      {
        if (arc.left_boundary_in_x() == NO_BOUNDARY &&
            arc.left_boundary_in_y() == NO_BOUNDARY)
        {
          _ps = arc.left();
        }
        else
        {
          if (arc.left_boundary_in_x() == MINUS_INFINITY)
            _info = (_info | SRC_AT_X_MINUS_INFTY);
          else if (arc.left_boundary_in_x() == PLUS_INFINITY)
            _info = (_info | SRC_AT_X_PLUS_INFTY);

          if (arc.left_boundary_in_y() == MINUS_INFINITY)
            _info = (_info | SRC_AT_Y_MINUS_INFTY);
          else if (arc.left_boundary_in_y() == PLUS_INFINITY)
            _info = (_info | SRC_AT_Y_PLUS_INFTY);
        }
      }
      else
      {
        if (arc.left_boundary_in_x() == NO_BOUNDARY &&
            arc.left_boundary_in_y() == NO_BOUNDARY)
        {
          _pt = arc.left();
        }
        else
        {
          if (arc.left_boundary_in_x() == MINUS_INFINITY)
            _info = (_info | TRG_AT_X_MINUS_INFTY);
          else if (arc.left_boundary_in_x() == PLUS_INFINITY)
            _info = (_info | TRG_AT_X_PLUS_INFTY);

          if (arc.left_boundary_in_y() == MINUS_INFINITY)
            _info = (_info | TRG_AT_Y_MINUS_INFTY);
          else if (arc.left_boundary_in_y() == PLUS_INFINITY)
            _info = (_info | TRG_AT_Y_PLUS_INFTY);
        }
      }
    }

    return;
  }

  /*!
   * Flip the arc (swap its source and target).
   * \return The flipped arc.
   */
  Self flip () const
  {
    CGAL_precondition (is_valid());

    // Create the flipped arc.
    Self   arc;

    arc._numer = _numer;
    arc._denom = _denom;
    arc._ps = _pt;
    arc._pt = _ps;

    // Manipulate the information bits.
    int    src_info = (_info & SRC_INFO_BITS);
    int    trg_info = (_info & TRG_INFO_BITS);
    arc._info = (src_info << 4) | (trg_info >> 4) | IS_VALID;

    if ((_info & IS_DIRECTED_RIGHT) == 0)
      arc._info = (arc._info | IS_DIRECTED_RIGHT);

    if ((_info & IS_CONTINUOUS) != 0)
      arc._info = (arc._info | IS_CONTINUOUS);
    
    return (arc);
  }

  /*!
   * Print the rational arc.
   */
  std::ostream& print (std::ostream& os) const
  {    
    // Print y as a rational function of x.
    os << "y = (";
    _print_polynomial (os, _numer, 'x');
    os << ") / (";
    _print_polynomial (os, _denom, 'x');
    os << ") on ";

    // Print the definition range.
    Boundary_type      inf_x = source_boundary_in_x();
    if (inf_x == MINUS_INFINITY) 
      os << "(-oo";
    else if (inf_x == PLUS_INFINITY)
      os << "(+oo";
    else if (source_boundary_in_y() != NO_BOUNDARY)
      os << '(' << source_x();
    else
      os << '[' << source().x();
 
    os << ", ";
    inf_x = target_boundary_in_x();

    if (inf_x == MINUS_INFINITY) 
      os << "-oo)";
    else if (inf_x == PLUS_INFINITY)
      os << "+oo)";
    else if (target_boundary_in_y() != NO_BOUNDARY)
      os << target_x() << ')';
    else
      os << target().x() << ']';

    return (os);
  }

  //@}

private:

  /// \name Auxiliary (private) functions.
  //@{

  /*!
   * Check if the given x-value is in the x-range of the arc.
   * \param x The x-value.
   * \param eq_src Output: Is this value equal to the x-coordinate of the
   *                       source point.
   * \param eq_trg Output: Is this value equal to the x-coordinate of the
   *                       target point.
   */
  bool _is_in_x_range (const Algebraic& x,
                       bool& eq_src, bool& eq_trg) const
  {
    Comparison_result  res1;

    eq_src = eq_trg = false;
    if ((_info & IS_DIRECTED_RIGHT) != 0)
    {
      // Compare to the left endpoint (the source in this case).
      if ((_info & SRC_AT_X_MINUS_INFTY) != 0)
      {
        res1 = LARGER;
      }
      else
      {
        res1 = CGAL::compare (x, _ps.x());

        if (res1 == SMALLER)
          return (false);
        
        if (res1 == EQUAL)
        {
          eq_src = true;
          return (true);
        }
      }
      
      // Compare to the right endpoint (the target in this case).
      if ((_info & TRG_AT_X_PLUS_INFTY) != 0)
        return (true);

      const Comparison_result  res2 = CGAL::compare (x, _pt.x());
      
      if (res2 == LARGER)
          return (false);
       
      if (res2 == EQUAL)
        eq_trg = true;

      return (true);      
    }
    
    // Compare to the left endpoint (the target in this case).
    if ((_info & TRG_AT_X_MINUS_INFTY) != 0)
    {
      res1 = LARGER;
    }
    else
    {
      res1 = CGAL::compare (x, _pt.x());

      if (res1 == SMALLER)
        return (false);
        
      if (res1 == EQUAL)
      {
        eq_trg = true;
        return (true);
      }
    }
      
    // Compare to the right endpoint (the source in this case).
    if ((_info & SRC_AT_X_PLUS_INFTY) != 0)
      return (true);

    const Comparison_result  res2 = CGAL::compare (x, _ps.x());
      
    if (res2 == LARGER)
      return (false);
       
    if (res2 == EQUAL)
      eq_src = true;
    
    return (true);
  }

  /*!
   * Check if the given x-value is in the x-range of the arc, excluding its
   * open ends.
   */
  bool _is_in_true_x_range (const Algebraic& x) const
  {
    bool          eq_src, eq_trg;
    const bool    is_in_x_range_closure = _is_in_x_range (x, eq_src, eq_trg);

    if (! is_in_x_range_closure)
      return (false);

    // Check if we have a vertical asymptote at the source point.
    if (eq_src &&
        (_info & (SRC_AT_Y_MINUS_INFTY | SRC_AT_Y_PLUS_INFTY)) != 0)
      return (false);

    // Check if we have a vertical asymptote at the target point.
    if (eq_trg &&
        (_info & (TRG_AT_Y_MINUS_INFTY | TRG_AT_Y_PLUS_INFTY)) != 0)
      return (false);

    // If we reached here, the value is in the true x-range of the arc.
    return (true);
  }

  /*!
   * Check if the underlying rational fucntion is the same in the given arc.
   * \param arc The given arc.
   * \return (true) if arc's underlying rational fucntion is the same
   *         as of *this; (false) otherwise.
   */
  bool _has_same_base (const Self& arc) const
  {
    // p1(x)/q1(x) == p2(x)/q2(x) if and only if p1*q2 = p2*q1:
    return (_numer * arc._denom == _denom * arc._numer);
  }

  /*!
   * Compute the sign of the given polynomial at x = -oo.
   */
  CGAL::Sign _sign_at_minus_infinity (const Polynomial& poly) const
  {
    // Get the degree.
    Nt_traits    nt_traits;
    const int    degree = nt_traits.degree (poly);

    if (degree < 0)
      return (CGAL::ZERO);

    // Get the leading coefficient. Its sign is the sign of the polynomial
    // at x = -oo if the degree is even, and the opposite sign if it is odd.
    const CGAL::Sign  lead_sign = 
      CGAL::sign (nt_traits.get_coefficient (poly, degree));

    CGAL_assertion (lead_sign != CGAL::ZERO);

    if (degree % 2 == 0)
      return (lead_sign);
    else
      return ((lead_sign == CGAL::POSITIVE) ? CGAL::NEGATIVE : CGAL::POSITIVE);
  }

  /*!
   * Compute the sign of the given polynomial at x = +oo.
   */
  CGAL::Sign _sign_at_plus_infinity (const Polynomial& poly) const
  {
    // Get the degree.
    Nt_traits    nt_traits;
    const int    degree = nt_traits.degree (poly);

    if (degree < 0)
      return (CGAL::ZERO);

    // Get the leading coefficient. Its sign is the sign of the polynomial
    // at x = +oo.
    return (CGAL::sign (nt_traits.get_coefficient (poly, degree)));
  }

  /*!
   * Compute infinity type of the rational function P(x)/Q(x) at x = -oo.
   * \param y Output: The value of the horizontal asymptote (if exists).
   * \return The infinity type for the y-coordinate at x = -oo.
   */
  Boundary_type _analyze_at_minus_infinity (const Polynomial& P,
                                            const Polynomial& Q,
                                            Algebraic& y) const
  {
    // Get the degree of the polynomials.
    Nt_traits    nt_traits;
    const int    deg_p = nt_traits.degree (P);
    const int    deg_q = nt_traits.degree (Q);

    if (deg_p < 0 || deg_p < deg_q)
    {
      // We have a zero polynomial or a zero asymptote.
      y = 0;
      return (NO_BOUNDARY);
    }

    // Get the leading coefficients.
    Integer      p_lead = nt_traits.get_coefficient (P, deg_p);
    Integer      q_lead = nt_traits.get_coefficient (Q, deg_q);
    
    if (deg_p == deg_q)
    {
      // We have a horizontal asymptote.
      y = p_lead / q_lead;
      return (NO_BOUNDARY);
    }

    // We have a tendency to infinity.
    const int    def_diff = deg_p - deg_q;

    if (CGAL::sign (p_lead) == CGAL::sign (q_lead))
      return ((def_diff % 2 == 0) ? PLUS_INFINITY : MINUS_INFINITY);
    else
      return ((def_diff % 2 == 0) ? MINUS_INFINITY : PLUS_INFINITY);
  }

  /*!
   * Compute infinity type of the rational function P(x)/Q(x) at x = +oo.
   * \param y Output: The value of the horizontal asymptote (if exists).
   * \return The infinity type for the y-coordinate at x = +oo.
   */
  Boundary_type _analyze_at_plus_infinity (const Polynomial& P,
                                           const Polynomial& Q,
                                           Algebraic& y) const
  {
    // Get the degree of the polynomials.
    Nt_traits    nt_traits;
    const int    deg_p = nt_traits.degree (P);
    const int    deg_q = nt_traits.degree (Q);

    if (deg_p < 0 || deg_p < deg_q)
    {
      // We have a zero polynomial or a zero asymptote.
      y = 0;
      return (NO_BOUNDARY);
    }

    // Get the leading coefficients.
    Integer      p_lead = nt_traits.get_coefficient (P, deg_p);
    Integer      q_lead = nt_traits.get_coefficient (Q, deg_q);
    
    if (deg_p == deg_q)
    {
      // We have a horizontal asymptote.
      y = p_lead / q_lead;
      return (NO_BOUNDARY);
    }

    // We have a tendency to infinity.
    if (CGAL::sign (p_lead) == CGAL::sign (q_lead))
      return (PLUS_INFINITY);
    else
      return (MINUS_INFINITY);
  }

  /*!
   * Compute all zeros of the denominator polynomial that lie within the
   * x-range of the arc.
   */
  template <class OutputIterator>
  OutputIterator _denominator_roots (OutputIterator oi,
                                     bool& root_at_ps, bool& root_at_pt) const
  {
    Nt_traits         nt_traits;

    root_at_ps = root_at_pt = false;

    if (nt_traits.degree (_denom) <= 0)
      return (oi);

    // Compute the roots of the denominator polynomial.
    std::list<Algebraic>                           q_roots;
    bool                                           eq_src, eq_trg;
    typename std::list<Algebraic>::const_iterator  x_iter;

    nt_traits.compute_polynomial_roots (_denom,
                                        std::back_inserter (q_roots));

    // Go over the roots and check whether they lie in the x-range of the arc.
    for (x_iter = q_roots.begin(); x_iter != q_roots.end(); ++x_iter)
    {
      if (_is_in_x_range (*x_iter, eq_src, eq_trg))
      {
        if (eq_src)
        {
          root_at_ps = true;
        }
        else if (eq_trg)
        {
          root_at_pt = true;
        }
        else
        {
          // The root lies in the interior of the arc.
          *oi = *x_iter;
          ++oi;
        }
      }
    }

    return (oi);
  }

  /*!
   * Determine the signs of the rational functions infinitisimally to the left
   * and to the right of the given pole.
   * \param x0 The x-coordinate of the pole.
   * \pre x0 lies in the interior of the arc.
   * \return The signs to the left and to the right of x0.
   */
  std::pair<CGAL::Sign, CGAL::Sign>
  _analyze_near_pole (const Algebraic& x0) const
  {
    // Note that as the rational function is always normalized, the numerator
    // value is non-zero at the pole x0.
    Nt_traits         nt_traits;
    const Algebraic   numer_at_x0 = nt_traits.evaluate_at (_numer, x0);
    const CGAL::Sign  numer_sign = CGAL::sign (numer_at_x0);

    CGAL_assertion (numer_sign != CGAL::ZERO);

    // Determine the multiplicity of the pole and the sign of the first
    // non-zero derivative of the denominator polynomial at x0.
    int               mult = 1;
    Polynomial        p_der = nt_traits.derive (_denom);
    CGAL::Sign        der_sign;

    while ((der_sign = CGAL::sign (nt_traits.evaluate_at (p_der,
                                                          x0))) == CGAL::ZERO)
    {
      mult++;
      p_der = nt_traits.derive (p_der);
    }

    // Determine the tendency of the rational function to the left and to the
    // right of the pole (to y = -oo or to y = +oo).
    CGAL::Sign        sign_left, sign_right;

    if (mult % 2 == 1)
    {
      // Odd pole multiplicity: different signs from both sides of the pole.
      if (der_sign == numer_sign)
      {
        sign_left = CGAL::NEGATIVE;
        sign_right = CGAL::POSITIVE;
      }
      else
      {
        sign_left = CGAL::POSITIVE;
        sign_right = CGAL::NEGATIVE;
      }
    }
    else
    {
      // Even pole multiplicity: equal signs from both sides of the pole.
      if (der_sign == numer_sign)
      {
        sign_left = CGAL::POSITIVE;
        sign_right = CGAL::POSITIVE;
      }
      else
      {
        sign_left = CGAL::NEGATIVE;
        sign_right = CGAL::NEGATIVE;
      }
    }

    return (std::make_pair (sign_left, sign_right));
  }

  /*!
   * Split the arc into two at a given pole. The function returns the sub-arc
   * to the left of the pole and sets (*this) to be the right sub-arc.
   * \param x0 The x-coordinate of the pole.
   * \pre x0 lies in the interior of the arc.
   * \return The sub-arc to the left of the pole.
   */
  Self _split_at_pole (const Algebraic& x0)
  {
    // Analyze the behaviour of the function near the given pole.
    const std::pair<CGAL::Sign, CGAL::Sign>  signs = _analyze_near_pole (x0);
    const CGAL::Sign    sign_left = signs.first;
    const CGAL::Sign    sign_right = signs.second;

    // Create a fictitious point that represents the x-coordinate of the pole.
    Point_2    p0 (x0, 0);

    // Make a copy of the current arc.
    Self       c1 = *this;

    // Split the arc, such that c1 lies to the left of the pole and (*this)
    // to its right.
    if ((_info & IS_DIRECTED_RIGHT) != 0)
    {
      c1._pt = p0;
      c1._info = (c1._info & ~TRG_INFO_BITS);
      if (sign_left == CGAL::NEGATIVE)
        c1._info = (c1._info | TRG_AT_Y_MINUS_INFTY);
      else
        c1._info = (c1._info | TRG_AT_Y_PLUS_INFTY);

      this->_ps = p0;
      this->_info = (this->_info & ~SRC_INFO_BITS);
      if (sign_right == CGAL::NEGATIVE)
        this->_info = (this->_info | SRC_AT_Y_MINUS_INFTY);
      else
        this->_info = (this->_info | SRC_AT_Y_PLUS_INFTY);
    }
    else
    {
      c1._ps = p0;
      c1._info = (c1._info & ~SRC_INFO_BITS);
      if (sign_left == CGAL::NEGATIVE)
        c1._info = (c1._info | SRC_AT_Y_MINUS_INFTY);
      else
        c1._info = (c1._info | SRC_AT_Y_PLUS_INFTY);

      this->_pt = p0;
       this->_info = (this->_info & ~TRG_INFO_BITS);
      if (sign_right == CGAL::NEGATIVE)
        this->_info = (this->_info | TRG_AT_Y_MINUS_INFTY);
      else
        this->_info = (this->_info | TRG_AT_Y_PLUS_INFTY);
    }

    // Mark the sub-arc c1 as continuous.
    c1._info = (c1._info | IS_CONTINUOUS);

    return (c1);
  }

  /*!
   * Print a polynomial nicely.
   */
  std::ostream& _print_polynomial (std::ostream& os,
                                   const Polynomial& poly,
                                   char var) const
  {
    Nt_traits   nt_traits;
    const int   deg = nt_traits.degree (poly);
    Integer     coeff;
    CGAL::Sign  sgn;
    int         k;

    if (deg < 0)
    {
      os << '0';
      return (os);
    }

    for (k = deg; k >= 0; k--)
    {
      coeff = nt_traits.get_coefficient (poly, k);

      if (k == deg)
        os << coeff;
      else if ((sgn = CGAL::sign (coeff)) == POSITIVE)
        os << " + " << coeff;
      else if (sgn == NEGATIVE)
        os << " - " << -coeff;
      else
        continue;

      if (k > 1)
        os << '*' << var << '^' << k;
      else if (k == 1)
        os << '*' << var;
    }

    return (os);
  }
  //@}
};

/*!
 * Exporter for rational arcs.
 */
template <class Alg_kernel, class Nt_traits>
std::ostream& operator<< (std::ostream& os, 
                          const _Rational_arc_2<Alg_kernel, Nt_traits>& arc)
{
  return (arc.print (os));
}

CGAL_END_NAMESPACE

#endif
