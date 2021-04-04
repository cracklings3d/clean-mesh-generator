#pragma once

#include "mesh.hpp"
#include "polyhedron.hpp"

#include <fbxsdk.h>

#include <cstdio>
#include <gsl/gsl>
#include <unordered_map>

namespace cmg {
class Fbx_exporter {

public:
  template <typename Elements>
  static bool export_to_file(const std::string &path, const poly<Elements> &p) {
    FbxManager *fbx_manager = FbxManager::Create();
    // FbxIOSettings *io_settings = FbxIOSettings::Create(fbx_manager, IOSROOT);
    // fbx_manager->SetIOSettings(io_settings);

    FbxExporter *fbx_exporter = FbxExporter::Create(fbx_manager, path.c_str());
    auto exporter_init_result = fbx_exporter->Initialize(path.c_str());
    Ensures(exporter_init_result);

    FbxScene *scene = FbxScene::Create(fbx_manager, "scene");
    FbxNode *root_node = scene->GetRootNode();

    FbxNode *mesh_node = FbxNode::Create(fbx_manager, "mesh node");
    FbxMesh *mesh = FbxMesh::Create(fbx_manager, "mesh");
    mesh_node->AddNodeAttribute(mesh);
    root_node->AddChild(mesh_node);

    std::unordered_map<cmg::ci_v<Elements>, size_t> hds_vertex_index_map;
    int i = 0;
    for (auto v_it = p.vertices_begin(); v_it != p.vertices_end(); v_it++) {
      hds_vertex_index_map[v_it] = i;
      auto fbx_point =
          FbxVector4(v_it->point().x(), v_it->point().y(), v_it->point().z());
      mesh->SetControlPointAt(fbx_point, i);
      printf("Vertex #%d: (%f, %f, %f)\n", i, v_it->point().x(),
             v_it->point().y(), v_it->point().z());
      i++;
    }

    printf("%d vertices added.\n", i);

    int j = 0;
    for (auto f_it = p.facets_begin(); f_it != p.facets_end(); f_it++) {
      mesh->BeginPolygon();
      printf("Face #%d: ", j);

      auto v_it = f_it->halfedge();
      do {
        mesh->AddPolygon(hds_vertex_index_map[v_it->vertex()]);
        printf("%d ", j);
        j++;
      } while (v_it != f_it->halfedge());
      mesh->EndPolygon();
      printf("\n");
    }

    return fbx_exporter->Export(scene);
  }

  template <typename Elements>
  static bool export_to_file(const std::string &path, const Mesh<Elements> &m) {
    return Fbx_exporter::export_to_file(path, m.p);
  }
};
} // namespace cmg