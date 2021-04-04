#include <cstdio>

#include "mesh.hpp"
#include "fbx_exporter.hpp"

int main(int argc, char *argv[]) {
  cmg::Mesh<cmg::Mesh_elements_default> mesh;
  cmg::Fbx_exporter::export_to_file("../test.fbx", mesh);
  return 0;
}