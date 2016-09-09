// Source: Aff_transformation_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_AFF_TRANSFORMATION_2_H
#define CGAL_AFF_TRANSFORMATION_2_H

#include <CGAL/Aff_transformationC2.h>
template < class R >
class Transform;

template < class R >
class CGAL_Aff_transformation_base_2
  //#ifndef CGAL_REPCLASS
 :  virtual public R::Aff_transformation_base_2
  //#endif
{
public:
  virtual                      ~CGAL_Aff_transformation_base_2() {}

  virtual CGAL_Point_2<R>     transform(const CGAL_Point_2<R> &p) const  = 0;
  virtual CGAL_Vector_2<R>    transform(const CGAL_Vector_2<R> &v) const  = 0;
  virtual CGAL_Direction_2<R> transform(const CGAL_Direction_2<R> &d) const  = 0;

  virtual CGAL_Point_2<R>     operator()(const CGAL_Point_2<R> &p) const = 0;

  virtual CGAL_Vector_2<R>    operator()(const CGAL_Vector_2<R> &v) const = 0;

  virtual CGAL_Direction_2<R> operator()(const CGAL_Direction_2<R> &d) const = 0;

  virtual CGAL_Line_2<R>      transform(const CGAL_Line_2<R> &l) const = 0;
  virtual CGAL_Line_2<R>      operator()(const CGAL_Line_2<R> &l) const = 0;

  virtual CGAL_Ray_2<R>       transform(const CGAL_Ray_2<R> &r) const = 0;
  virtual CGAL_Ray_2<R>       operator()(const CGAL_Ray_2<R> &r) const = 0;

  virtual CGAL_Segment_2<R>   transform(const CGAL_Segment_2<R> &s) const = 0;
  virtual CGAL_Segment_2<R>   operator()(const CGAL_Segment_2<R> &s) const = 0;

  virtual CGAL_Triangle_2<R>  transform(const CGAL_Triangle_2<R> &t) const = 0;
  virtual CGAL_Triangle_2<R>  operator()(const CGAL_Triangle_2<R> &t) const = 0;
  /*
  virtual CGAL_Iso_rectangle_2<R> transform(const CGAL_Iso_rectangle_2<R> &r) const = 0;
  virtual CGAL_Iso_rectangle_2<R> operator()(const CGAL_Iso_rectangle_2<R> &r) const = 0;
  */
  //  virtual CGAL_Aff_transformation_2<R> general_form() const  = 0;

  virtual CGAL_Aff_transformation_2<R> * castToAff_Transformation() { return NULL;}
  virtual CGAL_Rotation_2<R> * castToRotation() { return NULL;}
  virtual CGAL_Translation_2<R> * castToTranslation() { return NULL;}
  virtual CGAL_Scaling_2<R> * castToScaling() { return NULL;}
  virtual char               * isa() const = 0;
  virtual Transform<R>         inverse_transform() const = 0;
  virtual bool                 is_even() const  = 0;
  virtual bool                 is_odd() const { return !is_even(); }
 ;
};

template < class R >
class CGAL_Aff_transformation_2 :
  public R::Aff_transformation_2,
  public CGAL_Aff_transformation_base_2<R>
{
public:
  CGAL_Aff_transformation_2()
  {}

  // copy constructor
  CGAL_Aff_transformation_2(const CGAL_Aff_transformation_2<R> &t)
    : R::Aff_transformation_2(t)
  {}

  // up cast constructor
  CGAL_Aff_transformation_2(const R::Aff_transformation_2 &t)
    : R::Aff_transformation_2(t)
  {}

  CGAL_Aff_transformation_2(const R::RT &m11, const R::RT &m12, const R::RT &m13,
                            const R::RT &m21, const R::RT &m22, const R::RT &m23,
                            const R::RT &m33 = R::RT(1.0))
    : R::Aff_transformation_2(m11, m12, m13,
                              m21, m22, m23,
                                             m33)
  {}

  CGAL_Aff_transformation_2(const R::RT &m11, const R::RT &m12,
                            const R::RT &m21, const R::RT &m22,
                            const R::RT &m33 = R::RT(1.0))
    : R::Aff_transformation_2(m11, m12,
                              m21, m22,
                                        m33)
  {}

  ~CGAL_Aff_transformation_2()
  {}

  CGAL_Point_2<R>     transform(const CGAL_Point_2<R> &p) const
  {
    return R::Aff_transformation_2::transform(p);
  }

  CGAL_Point_2<R>     operator()(const CGAL_Point_2<R> &p) const
  {
    return R::Aff_transformation_2::transform(p);
  }

  CGAL_Vector_2<R>    transform(const CGAL_Vector_2<R> &v) const
  {
    return R::Aff_transformation_2::transform(v);
  }

  CGAL_Vector_2<R>    operator()(const CGAL_Vector_2<R> &v) const
  {
    return transform(v);
  }

  CGAL_Direction_2<R> transform(const CGAL_Direction_2<R> &d) const
  {
    return R::Aff_transformation_2::transform(d);
  }

  CGAL_Direction_2<R> operator()(const CGAL_Direction_2<R> &d) const
  {
    return transform(d);
  }


  CGAL_Line_2<R>      transform(const CGAL_Line_2<R> &l) const
  {
    return l.transform(*this);
  }

  CGAL_Line_2<R>      operator()(const CGAL_Line_2<R> &l) const
  {
    return transform(l);
  }


  CGAL_Ray_2<R>       transform(const CGAL_Ray_2<R> &r) const
  {
    return r.transform(*this);
  }

  CGAL_Ray_2<R>       operator()(const CGAL_Ray_2<R> &r) const
  {
    return transform(r);
  }


  CGAL_Segment_2<R>   transform(const CGAL_Segment_2<R> &s) const
  {
    return s.transform(*this);
  }

  CGAL_Segment_2<R>   operator()(const CGAL_Segment_2<R> &s) const
  {
    return transform(s);
  }


  CGAL_Triangle_2<R>  transform(const CGAL_Triangle_2<R> &t) const
  {
    return t.transform(*this);
  }

  CGAL_Triangle_2<R>  operator()(const CGAL_Triangle_2<R> &t) const
  {
    return transform(t);
  }
  /*
  CGAL_Iso_rectangle_2<R>  transform(const CGAL_Iso_rectangle_2<R> &r) const
  {
    return r.transform(*this);
  }

  CGAL_Iso_rectangle_2<R>  operator()(const CGAL_Iso_rectangle_2<R> &r) const
  {
    return transform(r);
  }
  */

  CGAL_Aff_transformation_2<R>  inverse() const
  {
    return R::Aff_transformation_2::inverse();
  }

  CGAL_Aff_transformation_2<R>  transpose() const
  {
    return CGAL_Aff_transformation_2<R>(R::Aff_transformation_2::transpose());
  }
  /*
  CGAL_Aff_transformation_2<R>  general_form() const
  {
    return *this;
  }
  */
 CGAL_Aff_transformation_2<R> * castToAff_Transformation()
  {
    return this;
  }

  char * isa() const
  {
    return "general affine transformation";
  }

  Transform<R> inverse_transform() const
  {
    return Transform<R>(inverse());
  }

  bool                 is_even() const
  {
    return R::Aff_transformation_2::is_even();
  }

  bool                 is_odd() const
  {
    return !is_even();
  }

  CGAL_Aff_transformation_2<R> operator*(const CGAL_Aff_transformation_2<R> &t) const
  {
    return R::Aff_transformation_2::operator*(t);
  }

  CGAL_Aff_transformation_2<R> operator*(const CGAL_Rotation_2<R> &t) const
  {
    return R::Aff_transformation_2::operator*(t.general_form());
  }

  CGAL_Aff_transformation_2<R> operator*(const CGAL_Translation_2<R> &t) const
  {
    return R::Aff_transformation_2::operator*(t.general_form());
  }

  CGAL_Aff_transformation_2<R> operator*(const CGAL_Scaling_2<R> &t) const
  {
    return R::Aff_transformation_2::operator*(t.general_form());
  }
};

template < class R >
class CGAL_Rotation_2 :
  public R::Rotation_2,
  public CGAL_Aff_transformation_base_2<R>
{
public:
  CGAL_Rotation_2()
  {}
  // copy constructor
  CGAL_Rotation_2(const CGAL_Rotation_2<R> &t)
    : R::Rotation_2(t)
  {}

  // up cast constructor
  CGAL_Rotation_2(const R::Rotation_2 &t)
    : R::Rotation_2(t)
  {}

  CGAL_Rotation_2(const CGAL_Direction_2<R> &d)
    : R::Rotation_2(R::Direction_2(d))
  {}

  CGAL_Rotation_2(const R::FT &sinus, const R::FT &cosinus, const R::FT &hw = R::FT(1.0))
    : R::Rotation_2(sinus, cosinus, hw)
  {}

  ~CGAL_Rotation_2()
  {}

  CGAL_Point_2<R>     transform(const CGAL_Point_2<R> &p) const
  {
    return R::Rotation_2::transform(p);
  }

  CGAL_Point_2<R>     operator()(const CGAL_Point_2<R> &p) const
  {
    return R::Rotation_2::transform(p);
  }

  CGAL_Vector_2<R>    transform(const CGAL_Vector_2<R> &v) const
  {
    return R::Rotation_2::transform(v);
  }

  CGAL_Vector_2<R>    operator()(const CGAL_Vector_2<R> &v) const
  {
    return transform(v);
  }

  CGAL_Direction_2<R> transform(const CGAL_Direction_2<R> &d) const
  {
    return R::Rotation_2::transform(d);
  }

  CGAL_Direction_2<R> operator()(const CGAL_Direction_2<R> &d) const
  {
    return transform(d);
  }


  CGAL_Line_2<R>      transform(const CGAL_Line_2<R> &l) const
  {
    return l.transform(*this);
  }

  CGAL_Line_2<R>      operator()(const CGAL_Line_2<R> &l) const
  {
    return transform(l);
  }


  CGAL_Ray_2<R>       transform(const CGAL_Ray_2<R> &r) const
  {
    return r.transform(*this);
  }

  CGAL_Ray_2<R>       operator()(const CGAL_Ray_2<R> &r) const
  {
    return transform(r);
  }


  CGAL_Segment_2<R>   transform(const CGAL_Segment_2<R> &s) const
  {
    return s.transform(*this);
  }

  CGAL_Segment_2<R>   operator()(const CGAL_Segment_2<R> &s) const
  {
    return transform(s);
  }


  CGAL_Triangle_2<R>  transform(const CGAL_Triangle_2<R> &t) const
  {
    return t.transform(*this);
  }

  CGAL_Triangle_2<R>  operator()(const CGAL_Triangle_2<R> &t) const
  {
    return transform(t);
  }
  /*
  CGAL_Iso_rectangle_2<R>  transform(const CGAL_Iso_rectangle_2<R> &r) const
  {
    return r.transform(*this);
  }

  CGAL_Iso_rectangle_2<R>  operator()(const CGAL_Iso_rectangle_2<R> &r) const
  {
    return transform(r);
  }
  */

  CGAL_Rotation_2<R>  inverse() const
  {
    return R::Rotation_2::inverse();
  }

  CGAL_Rotation_2<R>  transpose() const
  {
    return CGAL_Rotation_2<R>(R::Rotation_2::transpose());
  }
  /*
  CGAL_Aff_transformation_2<R>  general_form() const
  {
    return CGAL_Aff_transformation_2<R>(R::Rotation_2::general_form());
  }
  */

  virtual CGAL_Rotation_2<R> * castToRotation()
  {
    return this;
  }

  char * isa() const
  {
    return "rotation";
  }

  Transform<R> inverse_transform() const
  {
    return(Transform<R>(inverse()));
  }

  bool                 is_even() const
  {
    return R::Rotation_2::is_even();
  }

  bool                 is_odd() const
  {
    return !is_even();
  }


  CGAL_Rotation_2<R> operator*(const CGAL_Rotation_2<R> &t) const
  {
    return R::Rotation_2::operator*(t);
  }

  CGAL_Aff_transformation_2<R> operator*(const CGAL_Translation_2<R> &t) const
  {
    return general_form() * t.general_form();
  }
  CGAL_Aff_transformation_2<R> operator*(const CGAL_Scaling_2<R> &t) const
  {
    return general_form() * t.general_form();
  }

  CGAL_Aff_transformation_2<R> operator*(const CGAL_Aff_transformation_2<R> &t) const
  {
    return t * (*this);
  }
};

template < class R >
class CGAL_Translation_2 :
  public R::Translation_2,
  public CGAL_Aff_transformation_base_2<R>
{
public:
  CGAL_Translation_2()
  {}

  // copy constructor
  CGAL_Translation_2(const CGAL_Translation_2<R> &t)
    : R::Translation_2(t)
  {}

  // up cast constructor
  CGAL_Translation_2(const R::Translation_2 &t)
    : R::Translation_2(t)
  {}

  // Translation:
  CGAL_Translation_2(const CGAL_Vector_2<R> &v)
    : R::Translation_2(v)
  {}

  ~CGAL_Translation_2()
  {}

  CGAL_Point_2<R>     transform(const CGAL_Point_2<R> &p) const
  {
    return R::Translation_2::transform(p);
  }

  CGAL_Point_2<R>     operator()(const CGAL_Point_2<R> &p) const
  {
    return R::Translation_2::transform(p);
  }

  CGAL_Vector_2<R>    transform(const CGAL_Vector_2<R> &v) const
  {
    return R::Translation_2::transform(v);
  }

  CGAL_Vector_2<R>    operator()(const CGAL_Vector_2<R> &v) const
  {
    return R::Translation_2::transform(v);
  }

  CGAL_Direction_2<R> transform(const CGAL_Direction_2<R> &d) const
  {
    return R::Translation_2::transform(d);
  }

  CGAL_Direction_2<R> operator()(const CGAL_Direction_2<R> &d) const
  {
    return transform(d);
  }


  CGAL_Line_2<R>      transform(const CGAL_Line_2<R> &l) const
  {
    return l.transform(*this);
  }

  CGAL_Line_2<R>      operator()(const CGAL_Line_2<R> &l) const
  {
    return transform(l);
  }


  CGAL_Ray_2<R>       transform(const CGAL_Ray_2<R> &r) const
  {
    return r.transform(*this);
  }

  CGAL_Ray_2<R>       operator()(const CGAL_Ray_2<R> &r) const
  {
    return transform(r);
  }


  CGAL_Segment_2<R>   transform(const CGAL_Segment_2<R> &s) const
  {
    return s.transform(*this);
  }

  CGAL_Segment_2<R>   operator()(const CGAL_Segment_2<R> &s) const
  {
    return transform(s);
  }


  CGAL_Triangle_2<R>  transform(const CGAL_Triangle_2<R> &t) const
  {
    return t.transform(*this);
  }

  CGAL_Triangle_2<R>  operator()(const CGAL_Triangle_2<R> &t) const
  {
    return transform(t);
  }
  /*
  CGAL_Iso_rectangle_2<R>  transform(const CGAL_Iso_rectangle_2<R> &r) const
  {
    return r.transform(*this);
  }

  CGAL_Iso_rectangle_2<R>  operator()(const CGAL_Iso_rectangle_2<R> &r) const
  {
    return transform(r);
  }
  */

  CGAL_Translation_2<R>  inverse() const
  {
    return R::Translation_2::inverse();
  }
  /*
  CGAL_Aff_transformation_2<R>  general_form() const
  {
    return CGAL_Aff_transformation_2<R>(R::Translation_2::general_form());
  }
  */


  virtual CGAL_Translation_2<R> * castToTranslation()
  {
    return this;
  }

  char * isa() const
  {
    return "translation";
  }

  Transform<R> inverse_transform() const
  {
    return Transform<R>(inverse());
  }

  bool                 is_even() const
  {
    return R::Translation_2::is_even();
  }

  bool                 is_odd() const
  {
    return !is_even();
  }

  CGAL_Translation_2<R> operator*(const CGAL_Translation_2<R> &t) const
  {
    return R::Translation_2::operator*(t);
  }

  CGAL_Aff_transformation_2<R> operator*(const CGAL_Rotation_2<R> &t) const
  {
    return general_form() * t.general_form();
  }
  CGAL_Aff_transformation_2<R> operator*(const CGAL_Scaling_2<R> &t) const
  {
    return general_form() * t.general_form();
  }

  CGAL_Aff_transformation_2<R> operator*(const CGAL_Aff_transformation_2<R> &t) const
  {
    return t * (*this);
  }
};

template < class R >
class CGAL_Scaling_2 :
  public R::Scaling_2,
  public CGAL_Aff_transformation_base_2<R>
{
public:
  CGAL_Scaling_2()
  {}

  // copy constructor
  CGAL_Scaling_2(const CGAL_Scaling_2<R> &t)
    : R::Scaling_2(t)
  {}

  // up cast constructor
  CGAL_Scaling_2(const R::Scaling_2 &t)
    : R::Scaling_2(t)
  {}

  // Scaling:
  CGAL_Scaling_2(const R::RT &s,
                 const R::RT &w= R::RT(1.0))
    : R::Scaling_2(s, w)
  {}

  ~CGAL_Scaling_2()
  {}

  CGAL_Point_2<R>     transform(const CGAL_Point_2<R> &p) const
  {
    return R::Scaling_2::transform(p);
  }

  CGAL_Point_2<R>     operator()(const CGAL_Point_2<R> &p) const
  {
    return R::Scaling_2::transform(p);
  }

  CGAL_Vector_2<R>    transform(const CGAL_Vector_2<R> &v) const
  {
    return R::Scaling_2::transform(v);
  }

  CGAL_Vector_2<R>    operator()(const CGAL_Vector_2<R> &v) const
  {
    return transform(v);
  }

  CGAL_Direction_2<R> transform(const CGAL_Direction_2<R> &d) const
  {
    return R::Scaling_2::transform(d);
  }

  CGAL_Direction_2<R> operator()(const CGAL_Direction_2<R> &d) const
  {
    return transform(d);
  }


  CGAL_Line_2<R>      transform(const CGAL_Line_2<R> &l) const
  {
    return l.transform(*this);
  }

  CGAL_Line_2<R>      operator()(const CGAL_Line_2<R> &l) const
  {
    return transform(l);
  }


  CGAL_Ray_2<R>       transform(const CGAL_Ray_2<R> &r) const
  {
    return r.transform(*this);
  }

  CGAL_Ray_2<R>       operator()(const CGAL_Ray_2<R> &r) const
  {
    return transform(r);
  }


  CGAL_Segment_2<R>   transform(const CGAL_Segment_2<R> &s) const
  {
    return s.transform(*this);
  }

  CGAL_Segment_2<R>   operator()(const CGAL_Segment_2<R> &s) const
  {
    return transform(s);
  }


  CGAL_Triangle_2<R>  transform(const CGAL_Triangle_2<R> &t) const
  {
    return t.transform(*this);
  }

  CGAL_Triangle_2<R>  operator()(const CGAL_Triangle_2<R> &t) const
  {
    return transform(t);
  }
  /*
  CGAL_Iso_rectangle_2<R>  transform(const CGAL_Iso_rectangle_2<R> &r) const
  {
    return r.transform(*this);
  }

  CGAL_Iso_rectangle_2<R>  operator()(const CGAL_Iso_rectangle_2<R> &r) const
  {
    return transform(r);
  }
  */

  CGAL_Scaling_2<R>  inverse() const
  {
    return R::Scaling_2::inverse();
  }
  /*
  CGAL_Aff_transformation_2<R>  general_form() const
  {
    return CGAL_Aff_transformation_2<R>(R::Scaling_2::general_form());
  }
  */

  virtual CGAL_Scaling_2<R> * castToScaling()
  {
    return this;
  }


  char * isa() const
  {
    return "scaling";
  }

  Transform<R> inverse_transform() const
  {
    return(Transform<R>(inverse()));
  }

  bool                 is_even() const
  {
    return R::Scaling_2::is_even();
  }

  bool                 is_odd() const
  {
    return !is_even();
  }


  CGAL_Scaling_2<R> operator*(const CGAL_Scaling_2<R> &t) const
  {
    return R::Scaling_2::operator*(t);
  }

  CGAL_Aff_transformation_2<R> operator*(const CGAL_Rotation_2<R> &t) const
  {
    return general_form() * t.general_form();
  }
  CGAL_Aff_transformation_2<R> operator*(const CGAL_Translation_2<R> &t) const
  {
    return general_form() * t.general_form();
  }

  CGAL_Aff_transformation_2<R> operator*(const CGAL_Aff_transformation_2<R> &t) const
  {
    return t * (*this);
  }
};


template < class R >
ostream &operator<<(ostream &os, const CGAL_Aff_transformation_2<R> &t)
{
  os << R::Aff_transformation_2(t);
  return os;
}

template < class R >
ostream &operator<<(ostream &os, const CGAL_Translation_2<R> &t)
{
  os << R::Translation_2(t);
  return os;
}

template < class R >
ostream &operator<<(ostream &os, const CGAL_Rotation_2<R> &t)
{
  os << R::Rotation_2(t);
  return os;
}

template < class R >
ostream &operator<<(ostream &os, const CGAL_Scaling_2<R> &t)
{
  os << R::Scaling_2(t);
  return os;
}


#endif // CGAL_AFF_TRANSFORMATION_2_H
