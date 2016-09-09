#ifndef MYKERNEL_H
#define MYKERNEL_H

#include <CGAL/Cartesian.h>
#include "MyPointC2.h"
#include "MySegmentC2.h"

// K_ is the new kernel, and K_Base is the old kernel
template < typename K_, typename K_Base >
class MyCartesian_base
  : public K_Base::template Base<K_>::Type
{
  typedef typename K_Base::template Base<K_>::Type   OldK;
public:
  typedef K_                                Kernel;
  typedef MyPointC2                         Point_2;
  typedef MySegmentC2<Kernel>               Segment_2;
  typedef MyConstruct_point_2<Kernel>       Construct_point_2;
  typedef const double*                     Cartesian_const_iterator_2;
  typedef MyConstruct_coord_iterator        Construct_cartesian_const_iterator_2;
  typedef MyConstruct_bbox_2<typename OldK::Construct_bbox_2> 
                                            Construct_bbox_2;

  template < typename Kernel2 >
  struct Base { typedef MyCartesian_base<Kernel2, K_Base>  Type; };
};


template < typename FT_ >
struct MyKernel
  : public MyCartesian_base<MyKernel<FT_>, CGAL::Cartesian<FT_> >
{};

CGAL_ITERATOR_TRAITS_POINTER_SPEC_TEMPLATE(MyKernel)

#endif // MYKERNEL_H
