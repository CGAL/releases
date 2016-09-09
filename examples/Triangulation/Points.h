
class PVector;
class segment;
class triangle;


class point{
public:
  friend PVector;
  point()
    : _x(0), _y(0)
  {}

  point(const point& p)
    : _x(p._x), _y(p._y)
  {}

  point(double x, double y)
    : _x(x), _y(y)
  {}

  double x() const
  {
    return _x;
  }

  double y() const
  {
    return _y;
  }

  bool operator==(const point& p) const
  {
    return x() == p.x() && y() == p.y();
  }
  
  bool operator!=(const point& p) const
  {
    return x() != p.x() || y() != p.y();
  }
  
private:
  double _x, _y;
};



ostream& operator<<(ostream& os, const point& p)
{
  os << "(" << p.x() << ", " << p.y() << ")";
  return os;
}



class segment{
public:
  segment(point* s, point* t)
    : _s(s), _t(t)
  {}

  segment()
    : _s(0), _t(0)
  {}

  segment(const segment& s)
    : _s(s._s), _t(s._t)
  {}

  point* source() const
  {
    return _s;
  }

  point* target() const
  {
    return _t;
  }

  bool operator==(const segment& s) const
  {
    return source() == s.source() && target() == s.target();
  }
  
  bool operator!=(const segment& s) const
  {
    return source() != s.source() || target() != s.target();
  }
  
private:
  point *_s, *_t;
};

ostream& operator<<(ostream& os, const segment& s)
{
  os << "(" << s.source() << ", " << s.target() << ")";
  return os;
}




class triangle{
public:
  triangle(point* p, point* q, point* r)
    : _p(p), _q(q), _r(r)
  {}

  triangle()
    : _p(0), _q(0), _r(0)
  {}

  triangle(const triangle& t)
    : _p(t._p), _q(t._q), _r(t._r)
  {}

  point* vertex(int i) const
  {
    switch(i){
    case 0:
      return _p;
    case 1:
      return _q;
    }
    return _r;
  }


  bool operator==(const triangle& t) const
  {
    return vertex(0) == t.vertex(0) && vertex(1) == t.vertex(1) && vertex(2) == t.vertex(2) ;
  }
  
  bool operator!=(const triangle& t) const
  {
    return vertex(0) != t.vertex(0) || vertex(1) != t.vertex(1) || vertex(2) != t.vertex(2) ;
  }
  
private:
  point *_p, *_q, *_r;
};

ostream& operator<<(ostream& os, const triangle& t)
{
  os << "(" << t.vertex(0) << ", " << t.vertex(1) << ", " << t.vertex(2) << ")";
  return os;
}



class PVector {
public:
  PVector()
    : V(NULL), _size(0)
  {}

  ~PVector()
  {
    if(V == NULL){
      delete []V;
    }
  }

  int size()
  {
    return _size;
  }

  point* operator[](int i) const
  {
    return V+i;
  }

  void reserve(int n)
  {
    if(V == NULL){
      delete []V;
    }
    V = new point[n];
    _size = n;
  }

  void read(istream& is)
  {
    int n;
    is >> n;

    reserve(n);
    double x,y;
    point* ptr = V;
    for(;n>0;n--){
      is >> x >> y;
      ptr->_x = x;
      ptr->_y = y;
      ++ptr;
    }
  }

private:
  point* V;
  int _size;
};

istream& operator>>(istream& is, PVector &pv)
{
  pv.read(is);
  return is;
}

#include <CGAL/Triangulation_vertex.h>
#include <CGAL/Triangulation_face.h>
#include <CGAL/Triangulation_face_circulator.h>
#include <CGAL/Triangulation_vertex_circulator.h>

class Euclidean_2 {
public:
  typedef ::point*  Point;
  typedef ::segment Segment;
  typedef ::triangle Triangle;

    typedef CGAL_Triangulation_vertex<Point> Vertex;
    typedef CGAL_Triangulation_face<Vertex> Face;

  CGAL_Comparison_result compare_x(const Point &p, const Point &q) const
  {
    return CGAL_compare(p->x(), q->x());
  }

  CGAL_Comparison_result compare_y(const Point &p, const Point &q) const
  {
    return CGAL_compare(p->y(), q->y());
  }

  CGAL_Orientation orientation(const Point &p,
                               const Point &q,
                               const Point &r) const
  {
    if(*p==*q || *p == *r || *q == *r){
      cout << "coll" << endl;
      return CGAL_COLLINEAR;
    }
    return CGAL_orientation(p->x(), p->y(), q->x(), q->y(), r->x(), r->y());
  }


  CGAL_Orientation extremal(const Point &p,
                            const Point &q,
			    const Point &r) const
  {
    if(*p==*q || *p == *r || *q == *r){
      cout << "coll" << endl;
      return CGAL_COLLINEAR;
    }
    return CGAL_orientation(p->x(), p->y(), q->x(), q->y(), r->x(), r->y());
  }
};

