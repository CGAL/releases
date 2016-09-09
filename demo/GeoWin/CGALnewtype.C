#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Circle_2.h>
#include<list>

#include <CGAL/Line_3.h>
#include <LEDA/point.h>
#include <LEDA/line.h>
#include <LEDA/window.h>
#include <LEDA/ps_file.h>

// 3d line ...
typedef CGAL::Cartesian<double>  RP;
typedef CGAL::Line_3< RP >        CGAL3dLine;
typedef std::list<CGAL3dLine>      CGAL3dLinelist;

// 2 forward decls.
bool geowin_IntersectsBox(const leda_line& obj, double x1,double y1,double x2, double y2,bool f);
void geowin_BoundingBox(const leda_line& obj, double& x1, double& x2,double& y1, double& y2);

leda_line convert_to_leda(const CGAL3dLine& l)
{
 CGAL::Point_3<RP>  p1=l.point(1);
 CGAL::Point_3<RP>  p2=l.point(2);

 leda_point lp1(p1.x(),p1.y());
 leda_point lp2(p2.x(),p2.y());
 
 leda_line lc(lp1,lp2);

 return lc;
}

ps_file& operator<<(ps_file& F,const CGAL3dLine& o) { return F; }  // only a dummy
const char* leda_tname(CGAL3dLine* p) {  return "CGAL 3d line"; }
leda_window& operator << (leda_window& w, const CGAL3dLine& obj)
{
  w << convert_to_leda(obj); return w;
}

leda_window& operator >> (leda_window& w, CGAL3dLine& obj)
{
  leda_line l1;
  if( w >> l1 ) {
    obj = CGAL3dLine(CGAL::Point_3<RP>(l1.point1().xcoord(),l1.point1().ycoord(),0), CGAL::Point_3<RP>(l1.point2().xcoord(),l1.point2().ycoord(),0));
  }
  return w;
}

bool geowin_IntersectsBox(const CGAL3dLine& obj, double x1,double y1,double x2, double y2,bool f)
{ return geowin_IntersectsBox(convert_to_leda(obj),x1,y1,x2,y2,f); }

void geowin_BoundingBox(const CGAL3dLine& obj, double& x1, double& x2,double& y1, double& y2)
{ geowin_BoundingBox(convert_to_leda(obj),x1,x2,y1,y2); }

void geowin_Translate(CGAL3dLine& obj, double dx, double dy)
{ CGAL::Point_3<RP> p1 = obj.point(1), p2 = obj.point(2);
  CGAL::Point_3<RP> p3 = CGAL::Point_3<RP>(p1.x()+dx,p1.y()+dy,0), p4 = CGAL::Point_3<RP>(p2.x()+dx,p2.y()+dy,0); 
  obj = CGAL3dLine(p3,p4); 
}

void geowin_Rotate(CGAL3dLine& obj, double x, double y, double a) 
{ }

leda_string geowin_info_fcn(const std::list<CGAL3dLine>& L)
{ leda_string str("~~~\\black \\tt STL-list of %d %ss", L.size(), "3d line");  return str; }

#include <CGAL/geowin_support.h>

void geowin_generate_objects(GeoWin& gw, std::list<CGAL3dLine>& L)
{
}

int main()
{
  geowin_init_default_type((CGAL3dLinelist*)0, leda_string("CGAL3dLineList"));

  GeoWin GW("GeoWin - CGAL type 3d line demonstration...");
  GW.edit();
  return 0;  
}
