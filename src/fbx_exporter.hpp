#pragma once

#include "mesh.hpp"
#include "polyhedron.hpp"

#include <fbxsdk.h>

#include <cstdio>
#include <fbxsdk/scene/geometry/fbxlayer.h>
#include <gsl/gsl>
#include <unordered_map>

namespace cmg {
class Fbx_exporter {

public:
  template <typename Elements>
  static bool export_to_file(const std::string &path, const poly<Elements> &p) {
    FbxManager *manager = FbxManager::Create();
    // FbxIOSettings *io_settings = FbxIOSettings::Create(fbx_manager, IOSROOT);
    // fbx_manager->SetIOSettings(io_settings);

    FbxExporter *exporter = FbxExporter::Create(manager, path.c_str());
    auto exporter_init_result = exporter->Initialize(path.c_str());
    Ensures(exporter_init_result);

    FbxScene *scene = FbxScene::Create(manager, "scene");
    FbxNode *root_node = scene->GetRootNode();

    FbxNode *mesh_node = FbxNode::Create(manager, "mesh node");
    FbxMesh *mesh = FbxMesh::Create(manager, "mesh");
    mesh_node->AddNodeAttribute(mesh);
    root_node->AddChild(mesh_node);

    FbxLayerElementNormal *normal =
        FbxLayerElementNormal::Create(mesh, "normal");
    normal->SetMappingMode(FbxLayerElement::EMappingMode::eByControlPoint);

    std::unordered_map<cmg::ci_v<Elements>, size_t> hds_vertex_index_map;
    int i = 0;
    for (auto v_it = p.vertices_begin(); v_it != p.vertices_end(); v_it++) {
      hds_vertex_index_map[v_it] = i;
      auto fbx_point =
          FbxVector4(v_it->point().x(), v_it->point().y(), v_it->point().z());
      mesh->SetControlPointAt(fbx_point, i);
      printf("Vertex #%d: (%f, %f, %f)\n", i, v_it->point().x(),
             v_it->point().y(), v_it->point().z());
      normal->GetDirectArray().SetAt(
          i, FbxVector4(v_it->Normal.x(), v_it->Normal.y(), v_it->Normal.z()));
      printf("Normal #%d: (%f, %f, %f)\n", i, v_it->Normal.x(),
             v_it->Normal.y(), v_it->Normal.z());
      i++;
    }

    printf("%d vertices added.\n", i);

    int j = 0;
    for (auto f_it = p.facets_begin(); f_it != p.facets_end(); f_it++) {
      mesh->BeginPolygon();
      printf("Face #%d: ", j);

      auto h_it = f_it->halfedge();
      do {
        mesh->AddPolygon(hds_vertex_index_map[h_it->vertex()]);
        printf("%ld ", hds_vertex_index_map[h_it->vertex()]);
        h_it = h_it->next();
      } while (h_it != f_it->halfedge());
      mesh->EndPolygon();
      j++;
      printf("\n");
    }

    return exporter->Export(scene);
  }

  template <typename Elements>
  static bool export_to_file(const std::string &path, const Mesh<Elements> &m) {
    return Fbx_exporter::export_to_file(path, m.p);
  }
};
} // namespace cmg