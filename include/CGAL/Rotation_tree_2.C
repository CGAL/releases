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
// file          : include/CGAL/Rotation_tree_2.C
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2002/01/17 11:20:34 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Rotation tree for visibility graph computation
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <iostream>

namespace CGAL {


// makes *p the rightmost child of *q
template<class Traits>
void Rotation_tree_2<Traits>::set_rightmost_child(Self_iterator p, 
                                                  Self_iterator q)
{
   CGAL_assertion(q != end());

   if (p != end())
   {
      (*p).clear_right_sibling();
      if (rightmost_child(q) != end())
      {
         (*p).set_left_sibling(rightmost_child(q));
         (*rightmost_child(q)).set_right_sibling(p);
      }
      else
         (*p).clear_left_sibling();
      (*p).set_parent(q);
      (*q).set_rightmost_child(p);
   }
   else
   {
      (*q).clear_rightmost_child();
   }
}

// makes *p the left sibling of *q
template <class Traits>
void Rotation_tree_2<Traits>::set_left_sibling(Self_iterator p, 
                                               Self_iterator q)
{
   if (q == end()) return;
       
   if (p != end())
   {
      if (left_sibling(q) != end())
      {
         (*left_sibling(q)).set_right_sibling(p);
         (*p).set_left_sibling(left_sibling(q));
      }
      else
         (*p).clear_left_sibling();

      (*q).set_left_sibling(p);
      (*p).set_right_sibling(q);
      set_parent(parent(q),p);
   }
   else
   {
      if (left_sibling(q) != end())
         (*(*q).left_sibling()).clear_right_sibling();
      (*q).clear_left_sibling();
   }
}

// makes p the right sibling of q
template <class Traits>
void Rotation_tree_2<Traits>::set_right_sibling(Self_iterator p, 
                                                Self_iterator q)
{
   if (q == end()) return;
       
   if (p != end())
   {
      if (right_sibling(q) != end())
      {
         (*right_sibling(q)).set_left_sibling(p);
         (*p).set_right_sibling(right_sibling(q));
      }
      else
         (*p).clear_right_sibling();
      (*q).set_right_sibling(p);
      (*p).set_left_sibling(q);
      set_parent(parent(q),p);
   }
   else
   {
      if (right_sibling(q) != end())
         (*right_sibling(q)).clear_left_sibling();
      (*q).clear_right_sibling();
   }
}

// NOTE:  this function does not actually remove the node p from the
//        list; it only reorganizes the pointers so this node is not
//        in the tree structure anymore
template <class Traits>
void Rotation_tree_2<Traits>::erase(Self_iterator p)
{
   CGAL_assertion((*p).is_a_leaf());

   Self_iterator s;
   s = right_sibling(p);
   if (s != end())
      set_left_sibling(left_sibling(p),s);
   s = left_sibling(p);
   if (s != end())
      set_right_sibling(right_sibling(p),s);
   s = parent(p);
   // if p was the rightmost child of its parent, then set its left
   // sibling as the new rightmost child
   if (rightmost_child(s) == p)
      set_rightmost_child(left_sibling(p),s);
}

template <class Traits>
std::ostream& operator<<(std::ostream& os, const Rotation_tree_2<Traits>& tree)
{
    typename Rotation_tree_2<Traits>::const_iterator it;
    for (it = tree.begin(); it != tree.end(); it++)
         os << *it << " " << std::endl;
    return os;
}

}
