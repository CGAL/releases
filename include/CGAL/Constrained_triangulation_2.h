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
// file          : include/CGAL/Constrained_triangulation_2.h
// package       : Triangulation (3.17)
// source        : $RCSfile: Constrained_triangulation_2.h,v $
// revision      : $Revision: 1.4.1.11 $
// revision_date : $Date: 1999/03/24 14:18:12 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CONSTRAINED_TRIANGULATION_2_H
#define CGAL_CONSTRAINED_TRIANGULATION_2_H

#include <utility>
#include <list>
#include <vector>

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Constrained_triangulation_face_base_2.h>
#include <CGAL/Constrained_triangulation_sweep_2.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds>
class Constrained_triangulation_2
  : public Triangulation_2<Gt,Tds>
{

public:
  typedef Triangulation_2<Gt,Tds> Triangulation;
  typedef Constrained_triangulation_2<Gt,Tds> Constrained_triangulation;
  typedef std::pair<Point,Point> Constraint;

  typedef Constrained_triangulation_sweep_2<Gt,Tds>  Sweep;

  Constrained_triangulation_2() : Triangulation() { }

  Constrained_triangulation_2(const Gt& gt) : Triangulation(gt) { }

  Constrained_triangulation_2(const Constrained_triangulation_2& ct)
    : Triangulation(ct) {}

  Constrained_triangulation_2(const Vertex_handle&  v, const Gt& gt) 
    : Triangulation(v,gt) {}

  Constrained_triangulation_2(std::list<Constraint>& lc, const Gt& gt=Gt())
      : Triangulation_2<Gt,Tds>(gt)
  {
    Sweep sweep(lc,gt);
    Triangulation_2<Gt,Tds> Tr ( sweep.vertex(), gt);
    swap(Tr);
  }

 #ifdef CGAL_CFG_NO_MEMBER_TEMPLATES
  
  #if defined(LIST_H) || defined(__SGI_STL_LIST_H)
  Constrained_triangulation_2(std::list<Constraint>::const_iterator first,
                                   std::list<Constraint>::const_iterator last,
                                   const Gt& gt=Gt() )
     : Triangulation_2<Gt,Tds>(gt)
  {
      std::list<Constraint> lc;
      while(first != last){
          lc.push_back(*first); ++first;
      }
      Sweep sweep(lc,gt);
      Triangulation_2<Gt,Tds> Tr ( sweep.vertex(), gt);
      swap(Tr);
      //init(sweep.vertex());
      CGAL_triangulation_postcondition( is_valid() );
  }
  #endif // LIST_H
  
  #if defined(VECTOR_H) || defined(__SGI_STL_VECTOR_H)
  Constrained_triangulation_2(std::vector<Constraint>::const_iterator first,
                              std::vector<Constraint>::const_iterator last,
			      const Gt& gt=Gt() )
     : Triangulation_2<Gt,Tds>(gt)
  {
      std::list<Constraint> lc;
      while(first != last){
          lc.push_back(*first); ++first;
      }
      Sweep sweep(lc,gt);
      Triangulation_2<Gt,Tds> Tr ( sweep.vertex(), gt);
      swap(Tr);
    //init(sweep.vertex());
      CGAL_triangulation_postcondition( is_valid() );
  }
  #endif // VECTOR_H
  
  #ifdef ITERATOR_H
  Constrained_triangulation_2(
			   std::istream_iterator<Constraint,ptrdiff_t> first,
			   std::istream_iterator<Constraint,ptrdiff_t> last,
			   const Gt& gt=Gt() )
     : Triangulation_2<Gt,Tds>(gt)
  {
      std::list<Constraint> lc;
      while(first != last){
          lc.push_back(*first); ++first;
      }
      Sweep sweep(lc,gt);
      Triangulation_2<Gt,Tds> Tr ( sweep.vertex(), gt);
      swap(Tr);
      //init(sweep.vertex());
      CGAL_triangulation_postcondition( is_valid() );
  }
  #endif // ITERATOR_H
  
  Constrained_triangulation_2(Constraint* first,
                                   Constraint* last,
                                    const Gt& gt=Gt() )
     : Triangulation_2<Gt,Tds>(gt)
  {
      std::list<Constraint> lc;
      while(first != last){
          lc.push_back(*first); ++first;
      }
      Sweep sweep(lc,gt);
      Triangulation_2<Gt,Tds> Tr ( sweep.vertex(), gt);
      swap(Tr);
      //init(sweep.vertex());
      CGAL_triangulation_postcondition( is_valid() );
  }
  
  #else
  
  template<class InputIterator>
  Constrained_triangulation_2(InputIterator first,
                                   InputIterator last,
                                   const Gt& gt=Gt() )
     : Triangulation_2<Gt,Tds>(gt)
  {
      std::list<Constraint> lc;
      while(first != last){
          lc.push_back(*first++);
      }
      Sweep sweep(lc,gt);
      Triangulation_2<Gt,Tds> Tr ( sweep.vertex(), gt);
      swap(Tr);
          //init(sweep.vertex());
      CGAL_triangulation_postcondition( is_valid() );
  }
  
  #endif // CGAL_CFG_NO_MEMBER_TEMPLATES
  
  // private:
  // private part of class Constrained_triangulation_2
};

template < class Gt, class Tds >
std::ostream &
operator<<(std::ostream& os, const Constrained_triangulation_2<Gt,Tds> &Ct)
{
  return os << (const Triangulation_2<Gt,Tds>&)Ct;
}

CGAL_END_NAMESPACE

#endif //CGAL_CONSTRAINED_TRIANGULATION_2_H
