#pragma once

#include "polyhedron.hpp"
#include <CGAL/HalfedgeDS_vertex_base.h>
#include <CGAL/Polyhedron_items_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/tags.h>

namespace cmg {
template <class R, typename Tag, class Point>
class Vertex_with_normal : public CGAL::HalfedgeDS_vertex_base<R, Tag, Point> {
  CGAL::Vector_3<k> Normal = {0, 1, 0};
};

class Mesh_elements_default : public CGAL::Polyhedron_items_3 {
  // TODO: problem is definitely in here.
  // TODO: problem is definitely in here.
  // TODO: problem is definitely in here.
  // TODO: problem is definitely in here.
public:
  template <class R, class Tr> struct Vertex_wrapper {
    using Point = typename Tr::Point_3;
    using Vertex = Vertex_with_normal<R, CGAL::Tag_true, Point>;
  };
};

template<typename Elements>
class Mesh {
private:
  poly<Elements> p;

public:
  Mesh() {
    k::Point_3 pt0(1, 0, 0);
    k::Point_3 pt1(0, 1, 0);
    k::Point_3 pt2(0, 0, 1);
    k::Point_3 pt3(0, 0, 0);
    
    p.make_tetrahedron(pt0, pt1, pt2, pt3);
  }
  friend class Fbx_exporter;
};

} // namespace cmg