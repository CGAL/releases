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


// | $Revision: 1.1 $
// | $Date: 1997/06/13 00:17:03 $
// | 1997   Lutz Kettner 

#ifndef CGAL_SEGMENT_GENERATOR_H
#define CGAL_SEGMENT_GENERATOR_H 1

#ifndef ITERATOR_H
#include <iterator.h>
#endif

template < class S, class P1, class P2 >
class CGAL_Segment_generator : public input_iterator<S,size_t> {
    // g is an input iterator creating segments of type `S' from two
    // input points, one chosen from `p1', the other chosen from `p2'.
    // `p1' and `p2' are allowed be be same point
    // generator.Precondition: S must provide a constructor with two
    // arguments, such that the value type of `P1' and the value type
    // of `P2' can be used to construct a segment.
private:
    P1& _p1;
    P2& _p2;
public:
    CGAL_Segment_generator() {}
    CGAL_Segment_generator( const CGAL_Segment_generator<S,P1,P2>& g)
        : _p1( g._p1), _p2( g._p2) {}
    CGAL_Segment_generator( P1& p1, P2& p2)
        : _p1( p1), _p2( p2) {}
    bool operator==( const CGAL_Segment_generator<S,P1,P2>& g) const {
        return (_p1 == g._p1 && _p2 == g._p2);
    }
    bool operator!=( const CGAL_Segment_generator<S,P1,P2>& g) const {
        return ! operator==( g);
    }
    CGAL_Segment_generator<S,P1,P2>& operator++()    { return *this; }
    CGAL_Segment_generator<S,P1,P2>  operator++(int) { return *this; }
    S operator*() const;
};

template < class S, class P1, class P2 >
S
CGAL_Segment_generator<S,P1,P2>::
operator*() const {
    return S( *_p1++, *_p2++);
}
#line 619 "generators.any"
 
#endif // CGAL_SEGMENT_GENERATOR_H //
// EOF //
