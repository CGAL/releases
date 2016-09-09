// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/function_objects.h
// package       : STL_Extension (1.14)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/03/24 13:39:06 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Function objects.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_FUNCTION_OBJECTS_H
#define CGAL_FUNCTION_OBJECTS_H 1
template < class Value>
struct CGAL_Identity {
    typedef Value argument_type;
    typedef Value result_type;
    Value&       operator()( Value& x)       const { return x; }
    const Value& operator()( const Value& x) const { return x; }
};

// Composes two function objects: result is
// Fct1 o Fct2 o x == Fct1()( Fct2()(x)).
template < class Fct1, class Fct2>
struct CGAL_Compose {
    typedef typename  Fct2::argument_type  argument_type;
    typedef typename  Fct1::result_type    result_type;
    result_type&       operator()( argument_type& x)       const {
        Fct1 fct1;
        Fct2 fct2;
        return fct1( fct2(x));
    }
    const result_type& operator()( const argument_type& x) const {
        Fct1 fct1;
        Fct2 fct2;
        return fct1( fct2(x));
    }
};

template < class Value>
struct CGAL_Dereference {
    typedef Value* argument_type;
    typedef Value  result_type;
    Value&         operator()( Value* x)       const { return *x;}
    const Value&   operator()( const Value* x) const { return *x;}
};

template < class Value>
struct CGAL_Get_address {
    typedef Value  argument_type;
    typedef Value* result_type;
    Value*         operator()( Value& x)       const { return &x;}
    const Value*   operator()( const Value& x) const { return &x;}
};

template < class Arg, class Result>
struct CGAL_Cast_function_object {
    typedef Arg    argument_type;
    typedef Result result_type;
    Result&       operator()( Arg& x)       const { return (Result&)(x); }
    const Result& operator()( const Arg& x) const {
                      return (const Result&)(x);
    }
};

template < class Node>
struct CGAL_Project_vertex {
    typedef Node                  argument_type;
    typedef typename Node::Vertex Vertex;
    typedef Vertex                result_type;
    Vertex&       operator()( Node& x)       const { return x.vertex(); }
    const Vertex& operator()( const Node& x) const { return x.vertex(); }
};

template < class Node>
struct CGAL_Project_facet {
    typedef Node                  argument_type;
    typedef typename Node::Facet  Facet;
    typedef Facet                 result_type;
    Facet&       operator()( Node& x)       const { return x.facet(); }
    const Facet& operator()( const Node& x) const { return x.facet(); }
};

template < class Node>
struct CGAL_Project_point {
    typedef Node                  argument_type;
    typedef typename Node::Point  Point;
    typedef Point                 result_type;
    Point&       operator()( Node& x)       const { return x.point(); }
    const Point& operator()( const Node& x) const { return x.point(); }
};

template < class Node>
struct CGAL_Project_normal {
    typedef Node                  argument_type;
    typedef typename Node::Normal Normal;
    typedef Normal                result_type;
    Normal&       operator()( Node& x)       const { return x.normal(); }
    const Normal& operator()( const Node& x) const { return x.normal(); }
};

template < class Node>
struct CGAL_Project_plane {
    typedef Node                  argument_type;
    typedef typename Node::Plane  Plane;
    typedef Plane                 result_type;
    Plane&       operator()( Node& x)       const { return x.plane(); }
    const Plane& operator()( const Node& x) const { return x.plane(); }
};

// The following four adaptors are used to create the circulators
// for polyhedral surfaces.
template < class Node>
struct CGAL_Project_next {
    typedef Node*   argument_type;
    typedef Node*   result_type;
    Node*       operator()( Node* x)       const { return x->next(); }
    const Node* operator()( const Node* x) const { return x->next(); }
};

template < class Node>
struct CGAL_Project_prev {
    typedef Node*   argument_type;
    typedef Node*   result_type;
    Node*       operator()( Node* x)       const { return x->prev(); }
    const Node* operator()( const Node* x) const { return x->prev(); }
};

template < class Node>
struct CGAL_Project_next_opposite {
    typedef Node*   argument_type;
    typedef Node*   result_type;
    Node*       operator()( Node* x)       const {
                    return x->next()->opposite();
    }
    const Node* operator()( const Node* x) const {
                    return x->next()->opposite();
    }
};

template < class Node>
struct CGAL_Project_opposite_prev {
    typedef Node*   argument_type;
    typedef Node*   result_type;
    Node*       operator()( Node* x)       const {
                    return x->opposite()->prev();
    }
    const Node* operator()( const Node* x) const {
                    return x->opposite()->prev();
    }
};
template < class Arg, class  Result >
class CGAL_Creator_1 {
public:
    typedef Arg    argument_type;
    typedef Arg    argument1_type;
    typedef Result result_type;
    Result operator()(Arg a) const { return Result(a);}
};

template < class Arg1, class Arg2, class  Result >
class CGAL_Creator_2 {
public:
    typedef Arg1   argument1_type;
    typedef Arg2   argument2_type;
    typedef Result result_type;
    Result operator()(Arg1 a1, Arg2 a2) const { return Result(a1,a2);}
};

template < class Arg1, class Arg2, class Arg3, class  Result >
class CGAL_Creator_3 {
public:
    typedef Arg1   argument1_type;
    typedef Arg2   argument2_type;
    typedef Arg3   argument3_type;
    typedef Result result_type;
    Result operator()(Arg1 a1, Arg2 a2, Arg3 a3) const {
        return Result(a1,a2,a3);
    }
};

template < class Arg1, class Arg2, class Arg3, class Arg4, class  Result >
class CGAL_Creator_4 {
public:
    typedef Arg1   argument1_type;
    typedef Arg2   argument2_type;
    typedef Arg3   argument3_type;
    typedef Arg4   argument4_type;
    typedef Result result_type;
    Result operator()(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4) const {
        return Result(a1,a2,a3,a4);
    }
};

template < class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
           class  Result >
class CGAL_Creator_5 {
public:
    typedef Arg1   argument1_type;
    typedef Arg2   argument2_type;
    typedef Arg3   argument3_type;
    typedef Arg4   argument4_type;
    typedef Arg5   argument5_type;
    typedef Result result_type;
    Result operator()(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5) const {
        return Result(a1,a2,a3,a4,a5);
    }
};

template < class Arg, class  Result >
class CGAL_Creator_uniform_2 {
public:
    typedef Arg    argument_type;
    typedef Arg    argument1_type;
    typedef Arg    argument2_type;
    typedef Result result_type;
    Result operator()(Arg a1, Arg a2) const { return Result(a1,a2);}
};

template < class Arg, class  Result >
class CGAL_Creator_uniform_3 {
public:
    typedef Arg    argument_type;
    typedef Arg    argument1_type;
    typedef Arg    argument2_type;
    typedef Arg    argument3_type;
    typedef Result result_type;
    Result operator()(Arg a1, Arg a2, Arg a3) const {
        return Result(a1,a2,a3);
    }
};

template < class Arg, class  Result >
class CGAL_Creator_uniform_4 {
public:
    typedef Arg    argument_type;
    typedef Arg    argument1_type;
    typedef Arg    argument2_type;
    typedef Arg    argument3_type;
    typedef Arg    argument4_type;
    typedef Result result_type;
    Result operator()(Arg a1, Arg a2, Arg a3, Arg a4) const {
        return Result(a1,a2,a3,a4);
    }
};

template < class Arg, class  Result >
class CGAL_Creator_uniform_5 {
public:
    typedef Arg    argument_type;
    typedef Arg    argument1_type;
    typedef Arg    argument2_type;
    typedef Arg    argument3_type;
    typedef Arg    argument4_type;
    typedef Arg    argument5_type;
    typedef Result result_type;
    Result operator()(Arg a1, Arg a2, Arg a3, Arg a4, Arg a5) const {
        return Result(a1,a2,a3,a4,a5);
    }
};

template < class Arg, class  Result >
class CGAL_Creator_uniform_6 {
public:
    typedef Arg    argument_type;
    typedef Arg    argument1_type;
    typedef Arg    argument2_type;
    typedef Arg    argument3_type;
    typedef Arg    argument4_type;
    typedef Arg    argument5_type;
    typedef Arg    argument6_type;
    typedef Result result_type;
    Result operator()(Arg a1, Arg a2, Arg a3, Arg a4, Arg a5, Arg a6
                      ) const {
        return Result(a1,a2,a3,a4,a5,a6);
    }
};

template < class Arg, class  Result >
class CGAL_Creator_uniform_7 {
public:
    typedef Arg    argument_type;
    typedef Arg    argument1_type;
    typedef Arg    argument2_type;
    typedef Arg    argument3_type;
    typedef Arg    argument4_type;
    typedef Arg    argument5_type;
    typedef Arg    argument6_type;
    typedef Arg    argument7_type;
    typedef Result result_type;
    Result operator()(Arg a1, Arg a2, Arg a3, Arg a4, Arg a5, Arg a6,
                      Arg a7) const {
        return Result(a1,a2,a3,a4,a5,a6,a7);
    }
};

template < class Arg, class  Result >
class CGAL_Creator_uniform_8 {
public:
    typedef Arg    argument_type;
    typedef Arg    argument1_type;
    typedef Arg    argument2_type;
    typedef Arg    argument3_type;
    typedef Arg    argument4_type;
    typedef Arg    argument5_type;
    typedef Arg    argument6_type;
    typedef Arg    argument7_type;
    typedef Arg    argument8_type;
    typedef Result result_type;
    Result operator()(Arg a1, Arg a2, Arg a3, Arg a4, Arg a5, Arg a6,
                      Arg a7, Arg a8) const {
        return Result(a1,a2,a3,a4,a5,a6,a7,a8);
    }
};

template < class Arg, class  Result >
class CGAL_Creator_uniform_9 {
public:
    typedef Arg    argument_type;
    typedef Arg    argument1_type;
    typedef Arg    argument2_type;
    typedef Arg    argument3_type;
    typedef Arg    argument4_type;
    typedef Arg    argument5_type;
    typedef Arg    argument6_type;
    typedef Arg    argument7_type;
    typedef Arg    argument8_type;
    typedef Arg    argument9_type;
    typedef Result result_type;
    Result operator()(Arg a1, Arg a2, Arg a3, Arg a4, Arg a5, Arg a6,
                      Arg a7, Arg a8, Arg a9) const {
        return Result(a1,a2,a3,a4,a5,a6,a7,a8,a9);
    }
};

// Classes for composing function objects by Michael Hoffmann.

#ifndef CGAL_PROTECT_FUNCTION_H
#include <function.h>
#define CGAL_PROTECT_FUNCTION_H
#endif // CGAL_PROTECT_FUNCTION_H

template < class Operation1,
           class Operation2 >
class CGAL_Unary_compose_2
: public binary_function< typename Operation2::first_argument_type,
                          typename Operation2::second_argument_type,
                          typename Operation1::result_type >
{
protected:
  Operation1 op1;
  Operation2 op2;

public:
  CGAL_Unary_compose_2( const Operation1& x,
                        const Operation2& y)
  : op1(x), op2(y)
  {}

  result_type
  operator()( const first_argument_type& x,
              const second_argument_type& y) const
  { return op1( op2( x, y)); }
};

template < class Operation1,
           class Operation2 >
CGAL_Unary_compose_2< Operation1,
                      Operation2 >
CGAL_compose1_2( const Operation1& op1,
                 const Operation2& op2)
{
  return CGAL_Unary_compose_2< Operation1,
                               Operation2 >( op1, op2);
}


template < class Operation1,
           class Operation2,
           class Operation3 >
class CGAL_Binary_compose_2
: public binary_function< typename Operation2::argument_type,
                          typename Operation3::argument_type,
                          typename Operation1::result_type >
{
protected:
  Operation1 op1;
  Operation2 op2;
  Operation3 op3;

public:
  CGAL_Binary_compose_2( const Operation1& x,
                         const Operation2& y,
                         const Operation3& z)
  : op1(x), op2(y), op3(z)
  {}

  result_type
  operator()( const first_argument_type& x,
              const second_argument_type& y) const
  { return op1( op2( x), op3( y)); }
};

template < class Operation1,
           class Operation2,
           class Operation3 >
CGAL_Binary_compose_2< Operation1,
                       Operation2,
                       Operation3 >
CGAL_compose2_2( const Operation1& op1,
                 const Operation2& op2,
                 const Operation3& op3)
{
  return CGAL_Binary_compose_2< Operation1,
                                Operation2,
                                Operation3 >( op1, op2, op3);
}
#endif // CGAL_FUNCTION_OBJECTS_H //
// EOF //
