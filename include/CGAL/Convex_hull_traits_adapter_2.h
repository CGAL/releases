// Copyright (c) 2019  GeometryFactory (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-5.0-beta1/Convex_hull_2/include/CGAL/Convex_hull_traits_adapter_2.h $
// $Id: Convex_hull_traits_adapter_2.h 1406fb2 %aI Sebastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Sebastien Loriot


#ifndef CGAL_CONVEX_HULL_TRAITS_ADAPTER_2_H
#define CGAL_CONVEX_HULL_TRAITS_ADAPTER_2_H

#include <CGAL/disable_warnings.h>

#include <boost/call_traits.hpp>

#include <CGAL/property_map.h>


namespace CGAL{
  

template<class Base_traits,class PointPropertyMap>
class Convex_hull_traits_adapter_2:public Base_traits{
  PointPropertyMap ppmap_;
public:
  Convex_hull_traits_adapter_2(Base_traits base=Base_traits()):Base_traits(base){}

  Convex_hull_traits_adapter_2(const PointPropertyMap& ppmap,Base_traits base=Base_traits())
  :Base_traits(base),ppmap_(ppmap){}

  typedef Base_traits Gt;
  typedef typename boost::property_traits<PointPropertyMap>::key_type Point_2;
  typedef typename boost::call_traits<Point_2>::param_type Arg_type;

  struct Less_xy_2 : public Base_traits::Less_xy_2{
    Less_xy_2(const PointPropertyMap& ppmap,const typename Base_traits::Less_xy_2& base):
      Base_traits::Less_xy_2(base),ppmap_(ppmap){}
    const PointPropertyMap& ppmap_;
    bool operator()(Arg_type p,Arg_type q) const {
      return static_cast<const typename Base_traits::Less_xy_2*>(this)->operator()(get(ppmap_,p),get(ppmap_,q));
    }
  };
  
  struct Equal_2 : public Base_traits::Equal_2{
    Equal_2(const PointPropertyMap& ppmap,const typename Base_traits::Equal_2& base):
      Base_traits::Equal_2(base),ppmap_(ppmap){}
    const PointPropertyMap& ppmap_;
    bool operator()(Arg_type p,Arg_type q) const {
      return static_cast<const typename Base_traits::Equal_2*>(this)->operator()(get(ppmap_,p),get(ppmap_,q));
    }
  };
  
  struct Less_yx_2 : public Base_traits::Less_yx_2{
    Less_yx_2(const PointPropertyMap& ppmap,const typename Base_traits::Less_yx_2& base):
      Base_traits::Less_yx_2(base),ppmap_(ppmap){}
    const PointPropertyMap& ppmap_;
    bool operator()(Arg_type p,Arg_type q) const {
      return static_cast<const typename Base_traits::Less_yx_2*>(this)->operator()(get(ppmap_,p),get(ppmap_,q));
    }
  };

  struct Left_turn_2 : public Base_traits::Left_turn_2{
    Left_turn_2(const PointPropertyMap& ppmap,const typename Base_traits::Left_turn_2& base):
      Base_traits::Left_turn_2(base),ppmap_(ppmap){}
    const PointPropertyMap& ppmap_;
    bool operator()(Arg_type p,Arg_type q, Arg_type r) const {
      return static_cast<const typename Base_traits::Left_turn_2*>(this)->operator()(get(ppmap_,p),get(ppmap_,q),get(ppmap_,r));
    }
  };
  
  struct Orientation_2 : public Base_traits::Orientation_2{
    Orientation_2(const PointPropertyMap& ppmap,const typename Base_traits::Orientation_2& base):
      Base_traits::Orientation_2(base),ppmap_(ppmap){}
    const PointPropertyMap& ppmap_;
    CGAL::Orientation operator()(Arg_type p,Arg_type q, Arg_type r) const {
      return static_cast<const typename Base_traits::Orientation_2*>(this)->operator()(get(ppmap_,p),get(ppmap_,q),get(ppmap_,r));
    }
  };
  
  struct Less_rotate_ccw_2 : public Base_traits::Less_rotate_ccw_2{
    Less_rotate_ccw_2(const PointPropertyMap& ppmap,const typename Base_traits::Less_rotate_ccw_2& base):
      Base_traits::Less_rotate_ccw_2(base),ppmap_(ppmap){}
    const PointPropertyMap& ppmap_;
    bool operator()(Arg_type p,Arg_type q, Arg_type r) const {
      return static_cast<const typename Base_traits::Less_rotate_ccw_2*>(this)->operator()(get(ppmap_,p),get(ppmap_,q),get(ppmap_,r));
    }
  };
  
  struct Less_signed_distance_to_line_2 : public Base_traits::Less_signed_distance_to_line_2{
    Less_signed_distance_to_line_2(const PointPropertyMap& ppmap,const typename Base_traits::Less_signed_distance_to_line_2& base):
      Base_traits::Less_signed_distance_to_line_2(base),ppmap_(ppmap){}
    const PointPropertyMap& ppmap_;
    bool operator()(Arg_type p,Arg_type q, Arg_type r, Arg_type s) const {
      return static_cast<const typename Base_traits::Less_signed_distance_to_line_2*>(this)->operator()(get(ppmap_,p),get(ppmap_,q),get(ppmap_,r),get(ppmap_,s));
    }
  };
  
  Equal_2 equal_2_object () const {return Equal_2(ppmap_,static_cast<const Gt*>(this)->equal_2_object() );}
  Left_turn_2 left_turn_2_object () const {return Left_turn_2(ppmap_,static_cast<const Gt*>(this)->left_turn_2_object() );}
  Orientation_2 orientation_2_object () const {return Orientation_2(ppmap_,static_cast<const Gt*>(this)->orientation_2_object() );}
  Less_rotate_ccw_2   less_rotate_ccw_2_object () const {return Less_rotate_ccw_2(ppmap_,static_cast<const Gt*>(this)->less_rotate_ccw_2_object() );}
  Less_signed_distance_to_line_2   less_signed_distance_to_line_2_object () const {return Less_signed_distance_to_line_2(ppmap_,static_cast<const Gt*>(this)->less_signed_distance_to_line_2_object() );}
  Less_xy_2 less_xy_2_object () const {return Less_xy_2(ppmap_,static_cast<const Gt*>(this)->less_xy_2_object() );}
  Less_yx_2 less_yx_2_object () const {return Less_yx_2(ppmap_,static_cast<const Gt*>(this)->less_yx_2_object() );}
  
  const PointPropertyMap& point_property_map() const {return ppmap_;}

};

} //namespace CGAL

#include <CGAL/enable_warnings.h>

#endif //CGAL_CONVEX_HULL_TRAITS_ADAPTER_2_H
