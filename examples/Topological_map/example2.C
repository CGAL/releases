#include <CGAL/basic.h>
#include <iostream.h>

#include <CGAL/Topological_map_bases.h>
#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Topological_map.h>


class Face_with_info : public CGAL_Tpm_face_base {
  int inf;
public:
  Face_with_info() : CGAL_Tpm_face_base(), inf(0) {}

  int info() {return inf;}
  void set_info(int i) {inf=i;}
};



typedef CGAL_Pm_dcel<CGAL_Tpm_vertex_base,
                     CGAL_Tpm_halfedge_base,
                     Face_with_info > Dcel;  

typedef CGAL_Topological_map<Dcel> Tpm;

typedef  Tpm::Halfedge_handle Halfedge_handle;
typedef  Tpm::Vertex_handle   Vertex_handle;
typedef  Tpm::Face_handle     Face_handle;


main() {
  
  Tpm t;

  Face_handle uf=t.unbounded_face();

  cout << "inserting e1 in face interior..." << endl;
  Halfedge_handle e1 = t.insert_in_face_interior(uf);
  CGAL_assertion(t.is_valid());

  cout << "inserting e2 from vertex..." << endl;
  Halfedge_handle e2=t.insert_from_vertex(e1);
  CGAL_assertion(t.is_valid());

  cout << "inserting e3 between vertices of e2 and e1->twin()..." << endl;
  Halfedge_handle e3=t.insert_at_vertices(e2,e1->twin());
  CGAL_assertion(t.is_valid());
  
  cout << "\nsetting info of the new face to 10..." << endl;
  Face_handle nf=e3->face() ;
  nf->set_info(10);

  cout << "\nunbounded face info = " << uf->info() << endl;
  cout << "new face info = " << nf->info() << endl;

  return 0;
}
















