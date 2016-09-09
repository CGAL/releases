// ============================================================================
//
// Copyright (c) 1999 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       :
// release_date  :
//
// file          : src/GeoWin/geo_ledaobj.c
// package       : GeoWin (1.0.8)
// revision      : 1.0.8
// revision_date : 17 December 1999 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken@informatik.uni-halle.de>)
// ============================================================================

#include <LEDA/geowin_init.h>

GEOWIN_BEGIN_NAMESPACE

void geowin_Translate(point& obj, double dx, double dy)
{ 
  point obnew = obj.translate(dx,dy);
  obj = obnew;
}

void geowin_Translate(segment& obj, double dx, double dy)
{ 
  segment obnew = obj.translate(dx,dy);
  obj = obnew;
}

void geowin_Translate(ray& obj, double dx, double dy)
{ 
  ray obnew = obj.translate(dx,dy);
  obj = obnew;
}

void geowin_Translate(line& obj, double dx, double dy)
{ 
  line obnew = obj.translate(dx,dy);
  obj = obnew;
}

void geowin_Translate(circle& obj, double dx, double dy)
{ 
  circle obnew = obj.translate(dx,dy);
  obj = obnew;
}

void geowin_Translate(polygon& obj, double dx, double dy)
{ 
  polygon obnew = obj.translate(dx,dy);
  obj = obnew;
}

void geowin_Translate(gen_polygon& obj, double dx, double dy)
{ 
  gen_polygon obnew = obj.translate(dx,dy);
  obj = obnew;
}

void geowin_Translate(d3_point& obj, double dx, double dy)
{ 
  d3_point obnew = obj.translate(dx,dy,0);
  obj = obnew;
}

void geowin_Translate(rectangle& obj, double dx, double dy)
{ 
  rectangle obnew = obj.translate(dx,dy);
  obj = obnew;
}



void geowin_Rotate(point& obj, double x, double y, double a)
{ 
 point objnew = obj.rotate(point(x,y), a); 
 obj = objnew;
}

void geowin_Rotate(segment& obj, double x, double y, double a)
{ 
 segment objnew = obj.rotate(point(x,y), a); 
 obj = objnew;
}

void geowin_Rotate(ray& obj, double x, double y, double a)
{ 
 ray objnew = obj.rotate(point(x,y), a); 
 obj = objnew;
}

void geowin_Rotate(line& obj, double x, double y, double a)
{ 
 line objnew = obj.rotate(point(x,y), a); 
 obj = objnew;
}

void geowin_Rotate(circle& obj, double x, double y, double a)
{ 
 circle objnew = obj.rotate(point(x,y), a); 
 obj = objnew;
}

void geowin_Rotate(polygon& obj, double x, double y, double a)
{ 
 polygon objnew = obj.rotate(point(x,y), a); 
 obj = objnew;
}

void geowin_Rotate(gen_polygon& obj, double x, double y, double a)
{ 
 gen_polygon objnew = obj.rotate(point(x,y), a); 
 obj = objnew;
}

void geowin_Rotate(d3_point& obj, double x, double y, double a)
{ return ; }

void geowin_Rotate(rectangle& obj, double x, double y, double a)
{ return; } 






// IntersectsBox and BoundingBox for leda-types

// ************************************************************************
// ******************** begin intersects **********************************

bool geowin_IntersectsBox(const point& p, double x1, double y1,
		       double x2, double y2,bool filled)
{ 
  double x = p.xcoord(), y = p.ycoord();
  
  if ( x < x1 || x > x2 ) return false;
  if ( y < y1 || y > y2 ) return false;
  
  return true; 
}

bool geowin_IntersectsBox(const segment& s, double x1, double y1,
		       double x2, double y2,bool filled)
{
  segment s1(x1, y1, x2, y1);
  segment s2(x1, y2, x2, y2);
  segment s3(x1, y1, x1, y2);
  segment s4(x2, y1, x2, y2);
  point p;
  
  return 
    ( geowin_IntersectsBox(s.start(), x1, y1, x2, y2,filled) ||
      geowin_IntersectsBox(s.end(), x1, y1, x2, y2,filled)   ||
      s1.intersection(s,p) || s2.intersection(s,p) ||
      s3.intersection(s,p) || s4.intersection(s,p) );
}


bool geowin_IntersectsBox(const ray& r, double x1, double y1,
		       double x2, double y2,bool filled )
{
  segment s1(x1, y1, x2, y1);
  segment s2(x1, y2, x2, y2);
  segment s3(x1, y1, x1, y2);
  segment s4(x2, y1, x2, y2);
  point p;
  
  return 
    (  r.intersection(s1,p) || r.intersection(s2,p) ||
       r.intersection(s3,p) || r.intersection(s4,p)  );
}


bool geowin_IntersectsBox(const line& l, double x1, double y1,
		       double x2, double y2 ,bool filled)
{ 
  segment s1(x1, y1, x2, y1);
  segment s2(x1, y2, x2, y2);
  segment s3(x1, y1, x1, y2);
  segment s4(x2, y1, x2, y2);
  point p;
  
  return 
    (  l.intersection(s1,p) || l.intersection(s2,p) ||
       l.intersection(s3,p) || l.intersection(s4,p)  );
}

bool geowin_IntersectsBox(const circle& c, double x1, double y1,
		       double x2, double y2 ,bool filled)
{
  if (!c.orientation())
    return geowin_IntersectsBox(segment(c.point1(), c.point2()), x1, y1, x2, y2, filled );
  
  segment s1(x1, y1, x2, y1);
  segment s2(x1, y2, x2, y2);
  segment s3(x1, y1, x1, y2);
  segment s4(x2, y1, x2, y2);
  
  if ( !c.intersection(s1).empty() ) return true;
  if ( !c.intersection(s2).empty() ) return true;
  if ( !c.intersection(s3).empty() ) return true;
  if ( !c.intersection(s4).empty() ) return true;
  
  if( c.inside(point(x1, y1)) ) return filled;
  return geowin_IntersectsBox(c.center(), x1, y1, x2, y2, filled);
}

bool geowin_IntersectsBox(const polygon& p,  double x1, double y1,
		       double x2, double y2 , bool filled)
{
  segment s1(x1, y1, x2, y1);
  segment s2(x1, y2, x2, y2);
  segment s3(x1, y1, x1, y2);
  segment s4(x2, y1, x2, y2);
  
  if ( !p.intersection(s1).empty() ) return true;
  if ( !p.intersection(s2).empty() ) return true;
  if ( !p.intersection(s3).empty() ) return true;
  if ( !p.intersection(s4).empty() ) return true;
  
  if( p.inside(point(x1, y1)) ) return filled;
  return geowin_IntersectsBox(p.vertices().head(), x1, y1, x2, y2, filled);
}

bool geowin_IntersectsBox(const gen_polygon& p,  double x1, double y1,
		       double x2, double y2 , bool filled)
{
  segment s1(x1, y1, x2, y1);
  segment s2(x1, y2, x2, y2);
  segment s3(x1, y1, x1, y2);
  segment s4(x2, y1, x2, y2);
  
  if ( !p.intersection(s1).empty() ) return true;
  if ( !p.intersection(s2).empty() ) return true;
  if ( !p.intersection(s3).empty() ) return true;
  if ( !p.intersection(s4).empty() ) return true;
  
  if( p.inside(point(x1, y1)) ) return filled;

  list<polygon>  pli= p.polygons();
  polygon pl;

  forall(pl,pli) {
   if (geowin_IntersectsBox(pl.vertices().head(), x1, y1, x2, y2, filled)) return true;
  }
  return false;
}

bool geowin_IntersectsBox(const rectangle& obj, double x1,double y1,double x2, double y2,bool f)
{
 point p1(x1,y1),p2(x2,y2);

 list<rectangle> lr=obj.intersection(rectangle(p1,p2));
 if (lr.size()>0 ) return true; else return false;
}

bool geowin_IntersectsBox(const d3_point& p,double x1,double y1,double x2, double y2,bool f)
{ double xw=p.xcoord(), yw=p.ycoord();  
  if (x1<=xw && x2>=xw && y1<=yw && y2>=yw) return true; else return false;
}


// ********************* end  intersects **********************************
// ************************************************************************


// ************************************************************************
// ******************** begin BB *****************************************

void geowin_BoundingBox(const point& p, double& x1, double& x2, double& y1, 
		double& y2)
{
   x1 = p.xcoord(); x2 = p.xcoord();
   y1 = p.ycoord(); y2 = p.ycoord();
}

void geowin_BoundingBox(const segment& s, double& x1, double& x2, 
		double& y1, double& y2)
{
  if (s.xcoord1()<s.xcoord2()) { x1=s.xcoord1(); x2=s.xcoord2(); }
  else { x2=s.xcoord1(); x1=s.xcoord2(); }

  if (s.ycoord1()<s.ycoord2()) { y1=s.ycoord1(); y2=s.ycoord2(); }
  else { y2=s.ycoord1(); y1=s.ycoord2(); }

}

void geowin_BoundingBox(const ray& r, double& x1, double& x2,
		double& y1, double& y2)
{ 
  geowin_BoundingBox(segment(r.source(),r.point2()), x1, x2, y1, y2);
}

void geowin_BoundingBox(const line& l, double& x1, double& x2, double& y1, double& y2)
{ 
  geowin_BoundingBox(segment(l.point1(),l.point2()), x1, x2, y1, y2);
}

void geowin_BoundingBox(const circle& c, double& x1, double& x2, 
		double& y1, double& y2)
{
  point mp = c.center();
  double cx=mp.xcoord();
  double cy=mp.ycoord();
  double r = c.radius();
  
  x1= cx-r; x2=cx+r; y1=cy-r; y2=cy+r;
}
 

void geowin_BoundingBox(const polygon& P, double& x1, double& x2,
		double& y1, double& y2)
{
  point p;
  const list<point>&  L = P.vertices(); // polygons with 0 points ??

  if (L.empty()) return;

  x1= (L.head()).xcoord(); x2=x1;
  y1= (L.head()).ycoord(); y2=x1;
  double xakt,yakt;

  forall(p, L){
   xakt=p.xcoord(); yakt=p.ycoord();
   if (xakt<x1) x1=xakt;
   if (xakt>x2) x2=xakt;
   if (yakt<y1) y1=yakt;
   if (yakt>y2) y2=yakt;
  }
}

void geowin_BoundingBox(const gen_polygon& P, double& x1, double& x2,
		double& y1, double& y2)
{
  point p;
  const list<point>&  L = P.vertices(); // polygons with 0 points ??
  x1= (L.head()).xcoord(); x2=x1;
  y1= (L.head()).ycoord(); y2=x1;
  double xakt,yakt;

  forall(p, L){
   xakt=p.xcoord(); yakt=p.ycoord();
   if (xakt<x1) x1=xakt;
   if (xakt>x2) x2=xakt;
   if (yakt<y1) y1=yakt;
   if (yakt>y2) y2=yakt;
  }
}

void geowin_BoundingBox(const rectangle& obj, double& x1, double& x2,double& y1, double& y2)
{
  x1=obj.xmin(); x2=obj.xmax(); y1=obj.ymin(); y2=obj.ymax(); 
}

void geowin_BoundingBox(const d3_point& p, double& x1, double& x2, double& y1, double& y2)
{ x1=p.xcoord(); x2=p.xcoord(); y1=p.ycoord(); y2=p.ycoord(); }


// ********************* end BB   *****************************************
// ************************************************************************





#if !defined(NO_RAT_ALGORITHMS)

void geowin_Translate(rat_point& p, double dx, double dy)
{ p = rat_point(p.to_point().translate(dx, dy), 20); }

void geowin_Translate(rat_segment& s, double dx, double dy)
{ s = rat_segment(s.to_segment().translate(dx, dy), 20); }

void geowin_Translate(rat_ray& r, double dx, double dy)
{ r = rat_ray(r.to_ray().translate(dx, dy), 20); }

void geowin_Translate(rat_line& l, double dx, double dy)
{ l = rat_line(l.to_line().translate(dx, dy), 20); }

void geowin_Translate(rat_circle& ci, double dx, double dy)
{ ci = rat_circle(ci.to_circle().translate(dx, dy), 20); }

void geowin_Translate(rat_polygon& p, double dx, double dy)
{ p = rat_polygon(p.to_polygon().translate(dx, dy), 20); }

void geowin_Translate(rat_gen_polygon& p, double dx, double dy)
{ p = rat_gen_polygon(p.to_gen_polygon().translate(dx, dy), 20); }

void geowin_Translate(d3_rat_point& p, double dx, double dy)
{ d3_point phelp= p.to_d3_point().translate(dx,dy,0);
  double x=phelp.xcoord(), y=phelp.ycoord(), z=phelp.zcoord();
  p = d3_rat_point(integer(x*100000),integer(y*100000), integer(z*100000),
                                                                   100000);
}

void geowin_Translate(rat_rectangle& obj, double dx, double dy)
{  
  return;
}


void geowin_Rotate(rat_point& p, double x, double y,double a)
{ p = rat_point(p.to_point().rotate(point(x, y), a), 20); }

void geowin_Rotate(rat_segment& s, double x, double y,double a)
{ s = rat_segment(s.to_segment().rotate(point(x, y), a), 20); }

void geowin_Rotate(rat_ray& r, double x, double y,double a)
{ r = rat_ray(r.to_ray().rotate(point(x, y), a), 20); }

void geowin_Rotate(rat_line& l, double x, double y,double a)
{ l = rat_line(l.to_line().rotate(point(x, y), a), 20); }

void geowin_Rotate(rat_circle& ci, double x, double y,double a)
{ ci = rat_circle(ci.to_circle().rotate(point(x, y), a), 20); }

void geowin_Rotate(rat_polygon& p, double x, double y,double a)
{ p = rat_polygon(p.to_polygon().rotate(point(x, y), a), 20); }

void geowin_Rotate(rat_gen_polygon& p, double x, double y,double a)
{ p = rat_gen_polygon(p.to_gen_polygon().rotate(point(x, y), a), 20); }

void geowin_Rotate(d3_rat_point& p, double x, double y,double a) 
{ return; }

void geowin_Rotate(rat_rectangle& obj, double x, double y, double a)
{ return; }




// *********************************************`***************************
// ******************** begin intersects **********************************

bool geowin_IntersectsBox(const rat_point& p, double x1, double y1, 
		       double x2, double y2 ,bool filled)
{ return geowin_IntersectsBox( p.to_point(), x1, y1, x2, y2, filled ); }

bool geowin_IntersectsBox(const rat_segment& s,double x1, double y1, 
		       double x2, double y2,bool filled ) 
{ return geowin_IntersectsBox( s.to_segment(),x1, y1, x2, y2, filled ); }

bool geowin_IntersectsBox(const rat_ray& r, double x1, double y1, 
		       double x2, double y2,bool filled )
{ return geowin_IntersectsBox(r.to_ray(), x1, y1, x2, y2, filled ); }

bool geowin_IntersectsBox(const rat_line& l, double x1, double y1, 
		       double x2, double y2, bool filled )
{ return geowin_IntersectsBox(l.to_line(), x1, y1, x2, y2, filled ); }

bool geowin_IntersectsBox(const rat_circle& c, double x1, double y1, 
		       double x2, double y2, bool filled ) 
{ return geowin_IntersectsBox( c.to_circle(), x1, y1, x2, y2, filled ); }

bool geowin_IntersectsBox(const rat_polygon& p, double x1, double y1, 
		       double x2, double y2, bool filled )  
{ return geowin_IntersectsBox( p.to_polygon(), x1, y1, x2, y2, filled ); }

bool geowin_IntersectsBox(const rat_gen_polygon& p, double x1, double y1, 
		       double x2, double y2, bool filled )  
{ return geowin_IntersectsBox( p.to_gen_polygon(), x1, y1, x2, y2, filled ); }

bool geowin_IntersectsBox(const rat_rectangle& obj, double x1,double y1,double x2, double y2,bool f)
{ return geowin_IntersectsBox(obj.to_rectangle(),x1,y1,x2,y2,f); }

bool geowin_IntersectsBox(const d3_rat_point& p,double x1,double y1,double x2, double y2,bool f)
{ double xw=p.xcoord().to_double(), yw=p.ycoord().to_double();  
  if (x1<=xw && x2>=xw && y1<=yw && y2>=yw) return true; else return false;
}



// ********************* end  intersects **********************************
// ************************************************************************


// ************************************************************************
// ******************** begin bounding box ********************************



void geowin_BoundingBox(const rat_point& p, double& x1, double& x2, 
		double& y1, double& y2)
{ geowin_BoundingBox( p.to_point(), x1, x2, y1, y2); }

void geowin_BoundingBox(const rat_segment& s, double& x1, double& x2,
		double& y1, double& y2)
{ geowin_BoundingBox( s.to_segment(), x1, x2, y1, y2); }

void geowin_BoundingBox(const rat_ray& r, double& x1, double& x2,
		double& y1, double& y2)
{ geowin_BoundingBox( r.to_ray(), x1, x2, y1, y2); }

void geowin_BoundingBox(const rat_line& l, double& x1, double& x2,
		double& y1, double& y2)
{ geowin_BoundingBox( l.to_line(), x1, x2, y1, y2); }

void geowin_BoundingBox(const rat_circle& c, double& x1, double& x2,
		double& y1, double& y2)
{ geowin_BoundingBox( c.to_circle(), x1, x2, y1, y2); }


void geowin_BoundingBox(const rat_polygon& p, double& x1, double& x2,
		double& y1, double& y2)
{ geowin_BoundingBox( p.to_polygon(), x1, x2, y1, y2); }

void geowin_BoundingBox(const rat_gen_polygon& p, double& x1, double& x2,
		double& y1, double& y2)
{ geowin_BoundingBox( p.to_gen_polygon(), x1, x2, y1, y2); }

void geowin_BoundingBox(const rat_rectangle& obj, double& x1, double& x2,double& y1, double& y2)
{  geowin_BoundingBox(obj.to_rectangle(),x1,x2,y1,y2); }

void geowin_BoundingBox(const d3_rat_point& p, double& x1, double& x2, double& y1, double& y2)
{ x1=p.xcoordD(); x2=p.xcoordD(); y1=p.ycoordD(); y2=p.ycoordD(); }


// ********************* end  bounding box ********************************
// ************************************************************************


void set_rational_precision(int prec)
{
  rat_point::default_precision = prec;
}

#else

void set_rational_precision(int)
{}

#endif // NO_RAT_ALGORITHMS

GEOWIN_END_NAMESPACE
