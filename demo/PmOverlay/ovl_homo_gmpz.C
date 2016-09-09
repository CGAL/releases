/*******************************************************************/
// 
// 	Test for overlay - homogeneous case with double
//
/*******************************************************************/

#include <CGAL/Homogeneous.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Pm_segment_exact_traits.h>
#include <fstream.h>
#include <iostream.h>

#include <CGAL/Pm_overlay_for_bops.h>

typedef CGAL_Gmpz			 	Basetype;
typedef CGAL_Homogeneous<Basetype>	    	Rep_class;
typedef CGAL_Pm_segment_exact_traits<Rep_class>	Pmtraits;

typedef Pmtraits::Point 		Point;
typedef Pmtraits::X_curve		Curve;

typedef CGAL_Pm_default_dcel<Pmtraits>      	Pmdcel;
typedef CGAL_Planar_map_2<Pmdcel, Pmtraits>	Planar_map;

typedef CGAL_Pm_bops_default_dcel<Pmtraits> 	Bops_dcel;
typedef CGAL_Planar_map_2<Bops_dcel, Pmtraits>   Bops_planar_map;

int main()
{
  char nr_filename[20];
  char file_in1[9] = "/pm-1.in";
  char file_in2[9] = "/pm-2.in";
  char in1[20] = "";
  char in2[20] = "";

  cout << "Directory with the example: ";
  cin >> nr_filename;
  
  strcat(in1, nr_filename);
  strcat(in2, nr_filename);
  strcat(in1, file_in1);
  strcat(in2, file_in2);

  Planar_map pm1;
  Planar_map pm2;
  Bops_planar_map pm3;
  
  int nr_points;
  int nr_curves;
  int i, i1, i2, c;
  
  Basetype x, y;

  Point A[30];

  cout << "Constructing pm1...\n";
  
  ifstream f_stream_in1(in1);
  f_stream_in1 >> nr_points; 
 
  for (i=0; i<nr_points; i++){
    f_stream_in1 >> x >> y;
    A[i] = Point(x, y);
  }

  f_stream_in1 >> nr_curves;

  for (i=0; i<nr_curves; i++){
    f_stream_in1 >> i1 >> i2 >> c;
    pm1.insert(Curve(A[i1-1], A[i2-1]));
  }

  cout << "Insertion finished... testing map...\n ";
  
  if (!pm1.is_valid()) {
    cout << "invalid map pm1!\n";
    return -1;
  }
  else cout << "map 1 valid!\n";
  
  cout << "Constructing pm2...\n";

  ifstream f_stream_in2(in2);  
  f_stream_in2 >> nr_points; 
  
  for (i=0; i<nr_points; i++){
    f_stream_in2 >> x >> y;
    A[i] = Point(x,y);
  }

  f_stream_in2 >> nr_curves;

  for (i=0; i<nr_curves; i++){
    f_stream_in2 >> i1 >> i2 >> c;
    pm2.insert(Curve(A[i1-1], A[i2-1]));
  }

  cout << "Insertion finished... testing map... \n";
   
  if (!pm2.is_valid()) {
    cout << "invalid map pm2!\n";
    return -1;
  }
  else cout << "map 2 valid!\n";

  CGAL_Pm_overlay_for_bops<Pmtraits>(pm1, pm2, pm3);

  if (pm3.is_valid()){
    ofstream fout(strcat(nr_filename,"/pm.out"));
    Bops_planar_map::Halfedge_iterator hi;
    Bops_planar_map::Vertex_iterator vi;
    Bops_planar_map::Face_iterator fi;

    int nr_vertices = 0;
    for (vi=pm3.vertices_begin(); vi!=pm3.vertices_end(); ++vi) nr_vertices += 1;
    fout << nr_vertices << endl;
    
    for (vi=pm3.vertices_begin(); vi!=pm3.vertices_end(); ++vi){
      fout << (*vi).point().hx() / (*vi).point().hw() << " " 
	   << (*vi).point().hy() / (*vi).point().hw() << endl;
    }

    int nr_edges = 0;
    for (hi=pm3.halfedges_begin(); hi!=pm3.halfedges_end(); ++hi) nr_edges += 1;
    fout << nr_edges/2 << endl;
    
    for (hi=pm3.halfedges_begin(); hi!=pm3.halfedges_end(); ++hi){
      if ((*hi).source()->point().x()<(*hi).target()->point().x() ||
	  (*hi).source()->point().x()==(*hi).target()->point().x() &&
	  (*hi).source()->point().y()<(*hi).target()->point().y()){
	int v1 = 1;
	vi = pm3.vertices_begin();
	while ((*vi).point() != (*hi).source()->point()) {
	  v1++;
	  vi++;
	}
      
	int v2 = 1;
	vi = pm3.vertices_begin();
	while ((*vi).point() != (*hi).target()->point()){
	  v2++;
	  vi++;
	}
	fout << v1 << " " << v2 << " " << (int)(*hi).info().edge_color << endl;
      }
    }

    Bops_planar_map::Halfedge_handle he, he_next;
    int nr_faces=0;
    for (fi=pm3.faces_begin(); fi!=pm3.faces_end(); ++fi){
      nr_faces+=1;
    }
    nr_faces -= 1;
    fout << nr_faces << endl;

    for (fi=pm3.faces_begin(); fi!=pm3.faces_end(); ++fi){
      if (!(*fi).is_unbounded()){
	he = (*fi).halfedge_on_outer_ccb();
	he_next = he;
	int nr_edges = 0;
	do {
	  nr_edges+=1;
	  he_next = (*he_next).next_halfedge();
	} while (he!=he_next);
	fout << nr_edges << endl;
	
	do{
	  fout << (*he_next).source()->point().hx() / (*he_next).source()->point().hw() 
	       << " " 
	       << (*he_next).source()->point().hy() / (*he_next).source()->point().hw() 
	       << endl;
	  he_next = (*he_next).next_halfedge();
	} while (he!=he_next);
	fout << (int)(*fi).info() << endl;
      }
    }
  }
  else {
    cout << "The overlay is not a valid planar map!\n";
    return -1;
  }

  return 0;

}
