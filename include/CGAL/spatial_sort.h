// Copyright (c) 2007  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Spatial_sorting/include/CGAL/spatial_sort.h $
// $Id: spatial_sort.h 56667 2010-06-09 07:37:13Z sloriot $
//
// Author(s)     : Christophe Delage

#ifndef CGAL_SPATIAL_SORT_H
#define CGAL_SPATIAL_SORT_H

#include <CGAL/basic.h>

#include <CGAL/Hilbert_sort_2.h>
#include <CGAL/Hilbert_sort_3.h>

#include <CGAL/Multiscale_sort.h>

#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>

#include <algorithm>

namespace CGAL {

namespace internal {

    template <class RandomAccessIterator, class Kernel>
    void spatial_sort (RandomAccessIterator begin, RandomAccessIterator end,
                       const Kernel &k, typename Kernel::Point_2 *)
    {
        typedef Hilbert_sort_2<Kernel> Sort;
        boost::rand48 random;
        boost::random_number_generator<boost::rand48> rng(random);
        std::random_shuffle(begin,end,rng);

        (Multiscale_sort<Sort> (Sort (k, 4), 16, 0.25)) (begin, end);
    }

    template <class RandomAccessIterator, class Kernel>
    void spatial_sort (RandomAccessIterator begin, RandomAccessIterator end,
                       const Kernel &k, typename Kernel::Point_3 *)
    {
        typedef Hilbert_sort_3<Kernel> Sort;
        boost::rand48 random;
        boost::random_number_generator<boost::rand48> rng(random);
        std::random_shuffle(begin,end, rng);

        (Multiscale_sort<Sort> (Sort (k, 8), 64, 0.125)) (begin, end);
    }
}

template <class RandomAccessIterator, class Kernel>
void spatial_sort (RandomAccessIterator begin, RandomAccessIterator end,
                   const Kernel &k)
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;

    internal::spatial_sort (begin, end, k, static_cast<value_type *> (0));
}

template <class RandomAccessIterator>
void spatial_sort (RandomAccessIterator begin, RandomAccessIterator end)
{
    typedef std::iterator_traits<RandomAccessIterator> ITraits;
    typedef typename ITraits::value_type               value_type;
    typedef CGAL::Kernel_traits<value_type>            KTraits;
    typedef typename KTraits::Kernel                   Kernel;

    spatial_sort (begin, end, Kernel());
}

} //namespace CGAL

#endif//CGAL_SPATIAL_SORT_H
