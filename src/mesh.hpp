#pragma once

#include "polyhedron.hpp"
#include <CGAL/HalfedgeDS_face_base.h>
#include <CGAL/HalfedgeDS_vertex_base.h>
#include <CGAL/Polyhedron_items_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/tags.h>

namespace cmg {
template <class R, class T, class P, class Tr>
class Vertex_with_normal : public CGAL::HalfedgeDS_vertex_base<R, T, P> {
public:
  using Point_3 = typename Tr::Point_3;

  typename Tr::Vector_3 Normal = typename Tr::Vector_3(0, 1, 0);

  Vertex_with_normal(const Point_3 &point)
      : CGAL::HalfedgeDS_vertex_base<R, T, P>(point) {
    CGAL::HalfedgeDS_vertex_base<R, T, P>();
  }
  Vertex_with_normal() {}
};

template <class R>
class Face_with_color : public CGAL::HalfedgeDS_face_base<R> {
  CGAL::Color color;
};

class Mesh_elements_default : public CGAL::Polyhedron_items_3 {
public:
  template <class R, class Tr> struct Vertex_wrapper {
    using Point = typename Tr::Point_3;
    using Vertex = Vertex_with_normal<R, CGAL::Tag_true, Point, Tr>;
  };
  template <class R, class Tr> struct Face_wrapper {
    using Face = Face_with_color<R>;
  };
};

template <typename Elements> class Mesh {
private:
  using poly_T = poly<Elements>;
  poly_T p;

public:
  Mesh() {
    typename poly_T::Point pt0(1, 0, 0);
    typename poly_T::Point pt1(0, 1, 0);
    typename poly_T::Point pt2(0, 0, 1);
    typename poly_T::Point pt3(0, 0, 0);

    auto t = p.make_tetrahedron(pt0, pt1, pt2, pt3);
  }
  friend class Fbx_exporter;
};

} // namespace cmg