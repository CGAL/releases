#include <CGAL/basic.h>
#include <iostream.h>

#include <CGAL/Topological_map_bases.h>
#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Topological_map.h>


typedef CGAL_Pm_dcel<CGAL_Tpm_vertex_base,
                     CGAL_Tpm_halfedge_base,
                     CGAL_Tpm_face_base> Dcel;  

typedef CGAL_Topological_map<Dcel> Tpm;

typedef  Tpm::Halfedge_handle Halfedge_handle;
typedef  Tpm::Vertex_handle   Vertex_handle;
typedef  Tpm::Face_handle     Face_handle;


int main() {

  Tpm t;

  Face_handle uf=t.unbounded_face();

  cout << "inserting edge e1 in face interior ..." ;
  Halfedge_handle e1 = t.insert_in_face_interior(uf);
  CGAL_assertion(t.is_valid());
  cout << "map is valid." << endl;

  cout << "inserting edge e2 from target vertex of e1 ..." ;
  Halfedge_handle e2=t.insert_from_vertex(e1);
  CGAL_assertion(t.is_valid());
  cout <<  "map is valid." << endl;

  cout << "inserting edge e3 between target vertices of e2 and e1->twin() ...";
  //  Halfedge_handle e3=
  t.insert_at_vertices(e2,e1->twin());

  CGAL_assertion(t.is_valid());
  cout << "map is valid." << endl;

  return 0;
}
















