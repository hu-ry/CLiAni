//##############################################################################
//## Project: ClAni ############################# Created by hury on 15.03.24 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_RAYTRACER_H
#define CLIANIMATION_RAYTRACER_H

#include <filesystem>
#include <type_traits>
#include <optional>
#include <vector>
#include <humath.h>
#include <scene/scene.h>

// Enum to specify the Buffer Type
enum class BufferType { SingleBuffer, DoubleBuffer, TripleBuffer };

template <typename T, BufferType E>
class FrameBuffer {
public:
    explicit FrameBuffer(size_t _size) {
        if constexpr (E == BufferType::SingleBuffer) {
            // Only one array
            _data1.reserve(_size);
        } else if constexpr (E == BufferType::DoubleBuffer) {
            // Two arrays
            _data1.reserve(_size);
            _data2.reserve(_size);
        } else if constexpr (E == BufferType::TripleBuffer) {
            // Three arrays
            _data1.reserve(_size);
            _data2.reserve(_size);
            _data3.reserve(_size);
        }
    }

    // Accessors for individual arrays (if present)
    auto& GetData1() { return _data1; }
    auto& GetData2() { return _data2; }
    auto& GetData3() { return _data3; }

private:
    // Optional arrays based on the specified type
    std::optional<std::vector<T>> _data1;
    std::optional<std::vector<T>> _data2;
    std::optional<std::vector<T>> _data3;
};


struct Raytracer {
    struct Mesh {
        enum MaterialProperty {
            MATERIAL_NONE = 0,
            MATERIAL_VANTABLACK = 1,
            MATERIAL_MIRROR = 2
        };
        // raw vertices read out from file or resource
        std::vector<humath::v3f> vertices;
        size_t vertexCount = 0;

        std::vector<humath::v4f> triangles;
        size_t triangleCount = 0;

        MaterialProperty material = MaterialProperty::MATERIAL_NONE;
    };

public:
    Raytracer() = delete;
    Raytracer(uint32_t width, uint32_t height);

    // Reads out given filepath into internal mesh datastructure
    void load_mesh_from_file(const std::filesystem::path& path_to_mesh);
    // Reads out given string into internal mesh datastructure
    void load_mesh_from_string(const std::string& mesh_string);
    // Calculates triangle planes from vertices and normals
    void calc_triangle_plane(size_t mesh_to_calc);
    // This sets up the calculation of ray lines
    void setup_raylines_calc(std::shared_ptr<tasty::Camera> camera);
    // Simulate rays
    void run_ray_simulation();
    // Rasterize rays
    std::shared_ptr<FrameBuffer<float, BufferType::SingleBuffer>> rasterize_rays();


    // Getter & Setter
    size_t GetMeshCount() { return m_MeshCount; }

public:
    // Data accessible by the user
    std::vector<Mesh> m_Meshes;

    std::shared_ptr<FrameBuffer<float, BufferType::SingleBuffer>> m_Framebuffer;

private:
    size_t m_MeshCount = 0;
    struct {
        uint32_t height;
        uint32_t width;
    } m_Dimension;
    std::shared_ptr<tasty::Camera> m_Camera;

    std::vector<humath::v3f> m_RayAngles;
};

#endif //CLIANIMATION_RAYTRACER_H
