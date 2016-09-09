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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Rotation_tree_node_2.h
// package       : Partition_2 (1.18)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/07/11 16:34:12 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Node of a rotation tree used to compute vertex vis. graph
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef  CGAL_ROTATION_TREE_NODE_H
#define  CGAL_ROTATION_TREE_NODE_H

#include <utility>
#include <vector>

namespace CGAL {

template <class Traits> class Rotation_tree_2;

template <class Traits>
class Rotation_tree_node_2 : public Traits::Point_2
{
public:

   typedef typename Traits::Point_2                         Base_point;
   typedef Rotation_tree_node_2<Traits>                     Self;
   typedef typename std::vector< Self >::iterator           Tree_iterator;
   typedef std::pair<Tree_iterator, bool>                   Node_ref;


   Rotation_tree_node_2(Base_point p) : Base_point(p)
   { 
      _parent.second = false;
      _left_sibling.second = false;
      _right_sibling.second = false;
      _rightmost_child.second = false;
   }

   bool has_left_sibling() const
   {  return _left_sibling.second; }

   Tree_iterator left_sibling() const
   {  return _left_sibling.first; }

   bool has_right_sibling() const
   {  return _right_sibling.second; }

   Tree_iterator right_sibling() const
   {  return _right_sibling.first; }

   bool has_parent() const
   {  return _parent.second; }

   Tree_iterator parent() const
   {  return _parent.first; }

   bool has_children() const
   {  return _rightmost_child.second; }

   Tree_iterator rightmost_child() const
   {  return _rightmost_child.first; }

   void set_left_sibling(Tree_iterator ls)
   {
      _left_sibling.first = ls;
      _left_sibling.second = true;
   }

   void clear_left_sibling()
   {
      _left_sibling.second = false;
   }

   void set_right_sibling(Tree_iterator rs)
   {
     _right_sibling.first = rs;
     _right_sibling.second = true;
   }

   void clear_right_sibling()
   {
     _right_sibling.second = false;
   }

   void set_parent(Tree_iterator p)
   {
      _parent.first = p;
      _parent.second = true;
   }

   void clear_parent()
   {
      _parent.second = false;
   }

   void set_rightmost_child(Tree_iterator c)
   {
      _rightmost_child.first = c;
      _rightmost_child.second = true;
   }

   void clear_rightmost_child()
   {
      _rightmost_child.second = false;
   }

   bool is_a_leaf()
   {
      return !_rightmost_child.second;
   }

private:
   Node_ref _parent;
   Node_ref _left_sibling;
   Node_ref _right_sibling;
   Node_ref _rightmost_child;
};

template <class Traits>
std::ostream& operator<<(std::ostream& os,
                         const Rotation_tree_node_2<Traits>& node)
{
   os << node.x() << " " << node.y() << " ";
   if (node.has_parent())
      os << "  parent " << (*node.parent()).x() 
         << " " << (*node.parent()).y() << " ";
   if (node.has_left_sibling())
      os << "  left sibling " << (*node.left_sibling()).x() 
         << " " << (*node.left_sibling()).y() << " ";
   if (node.has_right_sibling())
      os << "  right sibling " << (*node.right_sibling()).x() 
         << " " << (*node.right_sibling()).y() << " ";
   if (node.has_children())
      os << "  rightmost child " << (*node.rightmost_child()).x() 
         << " " << (*node.rightmost_child()).y();
   return os;
}

}

#endif // CGAL_ROTATION_NODE_TREE_H
