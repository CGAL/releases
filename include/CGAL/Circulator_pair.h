// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Circulator_pair.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/01/19 10:08:39 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: pair of circulators that represents a chain of vertices
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_CIRC_PAIR_H
#define CGAL_CIRC_PAIR_H

namespace CGAL {

//
// "before" always means a point between front and back in the indicated
// direction
//
// "after" always means a point just beyond the range of [front,back]
//
template <class BidirectionalCirculator>
class Circ_pair 
{

public:
    Circ_pair(BidirectionalCirculator back, BidirectionalCirculator front) : 
        _front(front), _back(back), _direction(COUNTERCLOCKWISE) {}

    Circ_pair(BidirectionalCirculator back, BidirectionalCirculator front, 
              Orientation dir) : _front(front), _back(back), _direction(dir) {}

    Circ_pair(BidirectionalCirculator front_and_back, Orientation dir) : 
          _front(front_and_back), _back(front_and_back), _direction(dir) {}

    void initialize(BidirectionalCirculator new_back_and_front) 
    {
       _back = _front = new_back_and_front;
    }

    void push_back(BidirectionalCirculator new_back) 
    {
       _back = new_back;
    }

    void pop_back() 
    {
       _back = before_back();
    }

    void push_front(BidirectionalCirculator new_front)
    {
       _front = new_front;
    }

    void pop_front()
    {
       _front = before_front();
    }

    BidirectionalCirculator front() const
    {
       return _front;
    }

    BidirectionalCirculator back() const
    {
       return _back;
    }

    Orientation direction() const
    {
       return _direction;
    }

    void set_direction(Orientation direction) 
    {
       _direction = direction;
    }

    void change_dir()
    {
        if (_direction == CLOCKWISE)
           _direction = COUNTERCLOCKWISE;
        else
           _direction = CLOCKWISE;
    }

    BidirectionalCirculator before_back()
    {
        BidirectionalCirculator temp = _back;
        if (_direction == COUNTERCLOCKWISE)
           return ++temp;
        else
           return --temp;
    }
    BidirectionalCirculator after_back()
    {
        BidirectionalCirculator temp = _back;
        if (_direction == COUNTERCLOCKWISE)
           return --temp;
        else
           return ++temp;
    }
    BidirectionalCirculator before_front()
    {
        BidirectionalCirculator temp = _front;
        if (_direction == COUNTERCLOCKWISE)
           return --temp;
        else
           return ++temp;
    }
    BidirectionalCirculator after_front()
    {
        BidirectionalCirculator temp = _front;
        if (_direction == COUNTERCLOCKWISE)
           return ++temp;
        else
           return --temp;
    }
private:
    BidirectionalCirculator _front, _back;
    Orientation _direction;
};

}

#endif // CGAL_CIRC_PAIR_H
