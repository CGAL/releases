// Copyright (c) 2003-2006  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Circular_kernel_2/include/CGAL/IO/Dxf_reader_doubles.h $
// $Id: Dxf_reader_doubles.h 35587 2006-12-18 09:37:55Z lsaboret $
//
// Author(s)     : Monique Teillaud, Sylvain Pion, Andreas Fabri

// Descriptions of the file format can be found at
// http://www.autodesk.com/techpubs/autocad/acad2000/dxf/
// http://www.tnt.uni-hannover.de/soft/compgraph/fileformats/docs/DXF.ascii

#ifndef CGAL_IO_DXF_READER_DOUBLES_H
#define CGAL_IO_DXF_READER_DOUBLES_H

#include <CGAL/basic.h>
#include <iostream>
#include <string>
#include <list>
#include <map>

CGAL_BEGIN_NAMESPACE


class Dxf_reader_doubles {

public:
  typedef double       FT;
  typedef CGAL::Triple<double, double,double>  Triple;
  typedef Triple Point_2_and_bulge;
  typedef Triple Circle_2;
  
  
  typedef std::list<Triple > Polygon;
  typedef std::list<Polygon> Polygons;
  typedef std::list<Circle_2> Circles;
  
private:


  void
  header(std::istream& is)
  {
    int n;
    double xmin, ymin;
    double xmax, ymax;
    is >> n;
    assert(n == 9);
    char c;
    is >> c;
    assert(c == '$');
    std::string str;
    is >> str;
    if(str == std::string("EXTMIN")){
      is >> n;
      assert(n == 10);
    is >> xmin;
    is >> n;
    assert(n == 20);
    is >> ymin;
    }
    is >> n;
    assert(n == 9);
    is >> c;
    assert(c == '$');
    is >> str;
    if(str == "EXTMAX"){
      is >> n;
      assert(n == 10);
      is >> xmax;
      is >> n;
      assert(n == 20);
      is >> ymax;
    }
  }
  
  
  void
  skip_header(std::istream& is)
  {
    int n;
    is >> n;
    assert(n == 0);
    std::string str;
    is >> str;
    assert(str == "SECTION");
    is >> n;
    assert(n == 2);
    is >> str;
    if(str == "HEADER"){
      header(is);
    }
    is >> n;
    assert(n == 0);
    is >> str;
    assert(str == "ENDSEC");
  }
  
  
  
  void 
  read_circle(std::istream& is, Circle_2& circ)
  {
    int n;
    double cx, cy, r;
    std::string str;
    is >> n;
    assert(n == 8);
    is >> n;
    assert(n == 0);
  
  is >> n;
  assert(n == 10);
  is >> cx;
  is >> n;
  assert(n == 20);
  is >> cy;
  is >> n;
  assert(n == 40);
  is >> r;
  FT rft(r);
  
  circ = Circle_2(cx,cy,rft);
}


void
read_polygon(std::istream& is, Polygon& poly)
{
  int n;
  double x, y, len;
  std::string str;

  do {
    is >> n;
    if(n != 0){
      int m;
      is >> m; 
    }
  } while(n != 0);

  do {
    is >> str;
    if(str == "VERTEX"){
      is >> n;
      assert(n == 8);
      is >> n;
      assert(n == 0);
      is >> n;
      assert(n == 10);
      is >> x;
      is >> n;
      assert(n == 20);
      is >> y;
      is >> n;
      len = 0;
      if(n == 42){
	is >> len;
      } else {
	assert(n == 0);
      }
      poly.push_back(Point_2_and_bulge(x,y, len));
    }
    
  } while (str != "SEQEND");
  is >> n;
  assert(n == 8);
  is >> n;
  assert(n == 0);


}


void
read_entities(std::istream& is, Polygons& polys, Circles& circles)
{
  int n;
  //double x, y;
  std::string str;
  is >> n;
  assert(n == 0);
  is >> str;
  assert(str == "SECTION");
  is >> n;
  is >> str;
  assert(str == "ENTITIES");
  do {
    is >> n;
    assert(n == 0);
    is >> str;
    if(str == "POLYLINE"){
      Polygon p;
      polys.push_back(p);
      read_polygon(is, polys.back());
    } else if(str == "CIRCLE"){
      Circle_2 c;
      read_circle(is,c);      
      circles.push_back(c);
    } else if(str == "ENDSEC"){
      
    } else {
      std::cerr << "unknown entity" << std::endl;
      std::exit(0);
    }
  } while(str != "ENDSEC");
  is >> n;
  assert(n == 0);
  is >> str;
  assert(str == "EOF");
}



public:

void operator()(std::istream& is, Polygons& polygons, Circles& circles)
{
  skip_header(is);
  read_entities(is, polygons, circles);
}

};

CGAL_END_NAMESPACE

#endif // CGAL_IO_DXF_READER_DOUBLES_H
