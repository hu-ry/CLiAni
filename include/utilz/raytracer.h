//##############################################################################
//## Project: ClAni ############################# Created by hury on 15.03.24 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_RAYTRACER_H
#define CLIANIMATION_RAYTRACER_H

#include <filesystem>
#include <vector>
#include <humath.h>

struct Raytracer {
    struct Mesh {
        enum MaterialProperty {
            MATERIAL_NONE = 0,
            MATERIAL_VANTABLACK = 1,
            MATERIAL_MIRROR = 2
        };
        // raw vertices read out from file or resource
        std::vector<humath::v3f> vertices;
        size_t verticeCount = 0;

        std::vector<humath::v4f> triangles;
        size_t triangleCount = 0;

        MaterialProperty material = MaterialProperty::MATERIAL_NONE;
    };

    // Reads out file into internal mesh datastructure
    void load_mesh_from_file(std::filesystem::path& path_to_mesh);
    void load_mesh_from_string(std::string& mesh_string);
    // Calculates triangle planes from vertices and normals
    inline humath::v4f calc_plane();

private:
    std::vector<Mesh> meshes;
    size_t meshCount = 0;

};

#endif //CLIANIMATION_RAYTRACER_H
