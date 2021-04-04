#pragma once_Nonnull

#include <CGAL/Point_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_traits_with_normals_3.h>
#include <CGAL/Simple_cartesian.h>

namespace cmg {
using k = CGAL::Simple_cartesian<double_t>;
template <typename Elements> using poly = CGAL::Polyhedron_3<k, Elements>;
template <typename Elements> using h_h = typename poly<Elements>::Halfedge_handle;
template <typename Elements> using i_v = typename poly<Elements>::Vertex_iterator;
template <typename Elements> using ci_v = typename poly<Elements>::Vertex_const_iterator;
}; // namespace cmg