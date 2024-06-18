//##############################################################################
//## Project: cliAnimation ###################### Created by hury on 16.03.24 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include "raytracer.h"


Raytracer::Raytracer(uint32_t width, uint32_t height) :
        m_Dimension({ // Guarantees that we have a center pixel
            height % 2 == 1 ? height : height+1,
            width % 2 == 1 ? width : width+1
        }) {}

void Raytracer::load_mesh_from_file(const std::filesystem::path &path_to_mesh) {
    std::string verticesData;
    std::ifstream verticesFile;

    verticesFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open files
        verticesFile.open(path_to_mesh);
        std::stringstream verticesStream;
        // read file's buffer contents into streams
        verticesStream << verticesFile.rdbuf();
        // close file handlers
        verticesFile.close();
        // convert stream into string
        verticesData = verticesStream.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR::MESHOBJECT::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    std::cout << "data: " << verticesData << std::endl;

    load_mesh_from_string(verticesData);
}

void Raytracer::load_mesh_from_string(const std::string &mesh_string) {

    Mesh mesh_to_construct;
    m_MeshCount++;

    size_t startPos = 0;

    const std::string kmmDelim = ",";
    const std::string equalDelim = "=";
    const std::string smclnDelim = ";";
    const std::string nwlnDelim = "\n";

    // You can add new mesh properties to parse here
    const size_t meshAttributeLUTCount = 1;
    const std::string meshAttributeLUT[meshAttributeLUTCount] =
            {
            "material"
            };

    // We parse Mesh information specified before the "---" separator here
    for(const auto & attribute : meshAttributeLUT) {

        const auto currentDelim = attribute + equalDelim;
        size_t attributePosition = mesh_string.find(currentDelim, startPos);
        if(attributePosition == std::string::npos) {
            continue;
        }

        attributePosition += currentDelim.length();
        size_t attributeEnd = mesh_string.find(nwlnDelim, attributePosition);

        if(attributePosition == attributeEnd) {
            continue;
        }

        std::string attributeValue = mesh_string.substr(attributePosition, attributeEnd - attributePosition);

        // Maybe the range-based for-loop wasn't a good idea now that I have to find out the index again like this...
        switch(std::distance(meshAttributeLUT,
                              std::find(meshAttributeLUT, meshAttributeLUT+meshAttributeLUTCount, attribute)
                            ) ) {
            case 0:
                mesh_to_construct.material = static_cast<Mesh::MaterialProperty>(std::stoul(attributeValue));
                break;
            default:
                continue;
        }

    }

    // This cuts off everything before the triangle-data of the mesh starts
    size_t startOfMeshDelim =  mesh_string.find( nwlnDelim, mesh_string.find("---", 0) )+1;

    // ===================

    std::string stringData;

    // Set start-position since we want to cut off string at "---" delimiter
    startPos = startOfMeshDelim;
    auto kmmPos = mesh_string.find(kmmDelim, startPos);
    auto SmclnPos = mesh_string.find(smclnDelim, startPos);
    auto nwlnPos = mesh_string.find(nwlnDelim, startPos);

    // First pass of string manipulation
    // Parsing for mesh integrity and removing newlines and semicolons
    while (kmmPos != std::string::npos) {
        if (kmmPos < SmclnPos && kmmPos < nwlnPos) {
            stringData += mesh_string.substr(startPos, kmmPos - startPos) + kmmDelim;
            startPos = kmmPos + kmmDelim.length();
            kmmPos = mesh_string.find(kmmDelim, startPos);
        } else {
            if (SmclnPos < kmmPos && SmclnPos < nwlnPos) {
                stringData += mesh_string.substr(startPos, SmclnPos - startPos) + kmmDelim;
                startPos = SmclnPos + smclnDelim.length();
                SmclnPos = mesh_string.find(smclnDelim, startPos);
            } else {
                stringData += mesh_string.substr(startPos, nwlnPos - startPos) + kmmDelim;
                startPos = nwlnPos + nwlnDelim.length();
                nwlnPos = mesh_string.find(nwlnDelim, startPos);
            }
        }
        if(kmmPos == std::string::npos) {
            stringData = stringData.substr(0,startPos-1);
        }
    }

    size_t entries = std::count(stringData.begin(), stringData.end(), ',');

    // Each vertex should have 5 floats per row which are delimited by 5 commas
    if(entries%5 != 0 && entries%3 != 0) {
        std::cout << "ERROR::MESHOBJECT::MESH_CORRUPTED" << std::endl;
        return;
    }

    std::cout << ",: " << kmmPos << std::endl;
    std::cout << ";: " << SmclnPos << std::endl;
    std::cout << "newline: " << nwlnPos << std::endl;
    std::cout << "startPos: " << startPos << std::endl;

    std::cout << stringData << std::endl;

    mesh_to_construct.vertexCount = (size_t)entries/5;
    mesh_to_construct.vertices.reserve(mesh_to_construct.vertexCount);

    // Second pass of string manipulation
    // Removes all occurrences of "f" indicator for floating point numbers which might break std::stof conversion
    stringData = std::regex_replace( stringData, std::regex("f"), "");

    startPos = 0;
    for(int i = 0; i < (int)(entries/5); i++) {
        auto firstEnd = stringData.find(kmmDelim, startPos);
        auto secondEnd = stringData.find(kmmDelim, firstEnd+kmmDelim.length());
        auto thirdEnd = stringData.find(kmmDelim, secondEnd+kmmDelim.length());

        // inplace construction of our vector for the first three entries of a row
        mesh_to_construct.vertices[i] = humath::v3f(
                std::stof(stringData.substr(startPos, firstEnd - startPos)),
                std::stof(stringData.substr(startPos, secondEnd - firstEnd - kmmDelim.length())),
                std::stof(stringData.substr(startPos, thirdEnd - secondEnd - kmmDelim.length()))
        );

        // sanity print debugging...(gdb was playing me like a fiddle)
        //std::cout << std::to_string(mesh_to_construct.vertices[i].x) << std::to_string(mesh_to_construct.vertices[i].y) << std::to_string(mesh_to_construct.vertices[i].z) << startPos << std::endl;

        startPos = stringData.find(kmmDelim, thirdEnd + kmmDelim.length());
        startPos = stringData.find(kmmDelim, startPos + kmmDelim.length()) + kmmDelim.length();
    }

    // Insert constructed mesh
    m_Meshes.push_back(mesh_to_construct);
}

void Raytracer::calc_triangle_plane(size_t mesh_to_calc) {
    Raytracer::Mesh& mesh = m_Meshes[mesh_to_calc];
    const size_t triangleCount = mesh.vertexCount/3;

    // Prepare triangles vector
    mesh.triangleCount = triangleCount;
    mesh.triangles.reserve(triangleCount);

    // Go through every triangle defined by 3 vertices
    for(int triangleIndex = 0; triangleIndex < (int)triangleCount; triangleIndex++) {
        const int triangleOffset = triangleIndex * 3;

        // First we calculate two vectors that cross on the (1)first point of the triangle
        const humath::v3f vectorA(mesh.vertices[triangleOffset+1] - mesh.vertices[triangleOffset]); // Point2 - Point1
        const humath::v3f vectorB(mesh.vertices[triangleOffset+2] - mesh.vertices[triangleOffset]); // Point3 - Point1

        // Now we calculate the normal of the two crossing vectors by calculating the cross-product
        humath::v3f normalVector(vectorA);
        normalVector.cross_product(vectorB);

        // Now we calculate the 4th component that defines our triangle plane with the help of our normal
        // We just use the dot-product from our normal and the first corner of our triangle here
        mesh.triangles[triangleIndex] = humath::v4f(
                normalVector.x,
                normalVector.y,
                normalVector.z,
                -( normalVector.dot_product(mesh.vertices[triangleOffset]) )
                );
    }
}

void Raytracer::setup_raylines_calc(std::shared_ptr<tasty::Camera> camera) {
    m_Camera = std::move(camera);

    m_RayAngles.reserve(m_Dimension.width * m_Dimension.height);

    const float viewPlaneWidth = 5.0f;
    const float viewPlaneHeight = 4.0f;
    const humath::v2i viewPlaneCenter(
            (int) m_Dimension.width / 2,
            (int) m_Dimension.height / 2
            );
    const float pixelWidth = viewPlaneWidth / (float)m_Dimension.width;
    const float pixelHeight = viewPlaneHeight / (float)m_Dimension.height;
    const humath::v3f ViewPlaneDistanceFromCamera(0.0f, 10.0f, 0.0f);
    const tasty::Camera currentCamera = *m_Camera;


    for(uint32_t heightIndex = 0; heightIndex < m_Dimension.width; heightIndex++) {

        for(uint32_t widthIndex = 0; widthIndex < m_Dimension.height; widthIndex++) {
            humath::v3f& currentRayAngle = m_RayAngles[(heightIndex * m_Dimension.width) + widthIndex];

            currentRayAngle = humath::v3f(
                pixelWidth * (float)(widthIndex - viewPlaneCenter.x),
                pixelHeight * (float)(heightIndex - viewPlaneCenter.y),
                0
             ); // initial angle is

             // Adding our current camera position on top of it
            currentRayAngle += currentCamera.Position;
             // Adding our distance from camera to view plane on top
            currentRayAngle += ViewPlaneDistanceFromCamera;

            // Here we do the Y-Axis Rotation (yaw)
            currentRayAngle.rotate_y_axis(currentCamera.Direction.yaw);

            // Here we do the X-Axis Rotation (pitch)
            currentRayAngle.rotate_x_axis(currentCamera.Direction.pitch);

        }
    }
}

void Raytracer::run_ray_simulation() {
    const humath::v3f globalRayOrigin = m_Camera->Position;

    // Calculate by brute force every intersection point for each pair of ray and plane
    for(uint32_t rayIndex = 0; rayIndex < m_RayAngles.size(); rayIndex++) {
        const humath::v3f currentRayAngle = m_RayAngles[rayIndex];

        for(const Mesh& mesh : m_Meshes) {

            for(uint32_t planeIndex = 0; planeIndex < mesh.triangleCount; planeIndex++) {
                //TODO: Calculate distance to plane(Lambda) of ray
                //TODO: With that you calculate intersection-point i and then potentially filter it

                const humath::v3f v3Plane = { mesh.triangles[planeIndex].x,
                                          mesh.triangles[planeIndex].y,
                                          mesh.triangles[planeIndex].z };
                // We calculate the length-factor of the ray as in how far it has to travel to the plane
                float rayLength = v3Plane.dot_product(globalRayOrigin) + mesh.triangles[planeIndex].w / v3Plane.dot_product(currentRayAngle);
                if(rayLength < 0) continue; // skip invalid rayLength

                // Now we calculate the actual intersection point of the ray with our current plane
                humath::v3f intersection = {
                        rayLength * currentRayAngle.x + globalRayOrigin.x,
                        rayLength * currentRayAngle.y + globalRayOrigin.y,
                        rayLength * currentRayAngle.z + globalRayOrigin.z
                };

                // Bounding box check for triangle intersections happens here to be able to quickly exit early:
                if( intersection.x < std::min({ // if intersection is outside of bounding box
                        mesh.vertices[planeIndex*3].x, //TODO: Optimize at  later point
                        mesh.vertices[planeIndex*3+1].x,
                        mesh.vertices[planeIndex*3+2].x }) &&
                        intersection.x > std::max({
                        mesh.vertices[planeIndex*3].x,
                        mesh.vertices[planeIndex*3+1].x,
                        mesh.vertices[planeIndex*3+2].x }) &&
                        intersection.y < std::min({
                        mesh.vertices[planeIndex*3].y,
                        mesh.vertices[planeIndex*3+1].y,
                        mesh.vertices[planeIndex*3+2].y }) &&
                        intersection.y > std::max({
                        mesh.vertices[planeIndex*3].y,
                        mesh.vertices[planeIndex*3+1].y,
                        mesh.vertices[planeIndex*3+2].y }) &&
                        intersection.z < std::min({
                        mesh.vertices[planeIndex*3].z,
                        mesh.vertices[planeIndex*3+1].z,
                        mesh.vertices[planeIndex*3+2].z }) &&
                        intersection.z > std::max({
                        mesh.vertices[planeIndex*3].z,
                        mesh.vertices[planeIndex*3+1].z,
                        mesh.vertices[planeIndex*3+2].z }) ) {
                    continue;
                }

                // Now we perform the more precise filter for every/any remaining plane/ray combinations
                // Check if the intersection point and one of the corner are on the same side divided by a virtual line drawn from the other two points
                // t_2 - t_3
                humath::v3f triangleBorder1, triangleBorder2 = mesh.vertices[planeIndex*3+1] - mesh.vertices[planeIndex*3+2];
                humath::v3f vectorA = triangleBorder1.cross_product( intersection - mesh.vertices[planeIndex*3+2] );
                humath::v3f vectorB = triangleBorder2.cross_product( mesh.vertices[planeIndex*3] - mesh.vertices[planeIndex*3+2] );

                float insideBorderCoefficent = vectorA.dot_product(vectorB);
                if(insideBorderCoefficent < 0) continue;

                // t_1 - t_3
                triangleBorder1 = triangleBorder2 = mesh.vertices[planeIndex*3] - mesh.vertices[planeIndex*3+2];
                vectorA = triangleBorder1.cross_product( intersection - mesh.vertices[planeIndex*3+2] );
                vectorB = triangleBorder2.cross_product( mesh.vertices[planeIndex*3+1] - mesh.vertices[planeIndex*3+2] );

                insideBorderCoefficent = vectorA.dot_product(vectorB);
                if(insideBorderCoefficent < 0) continue;


                // t_1 - t_2
                triangleBorder1 = triangleBorder2 = mesh.vertices[planeIndex*3] - mesh.vertices[planeIndex*3+1];
                vectorA = triangleBorder1.cross_product( intersection - mesh.vertices[planeIndex*3+1] );
                vectorB = triangleBorder2.cross_product( mesh.vertices[planeIndex*3+2] - mesh.vertices[planeIndex*3+1] );

                insideBorderCoefficent = vectorA.dot_product(vectorB);
                if(insideBorderCoefficent < 0) continue;

                // TODO: Now we save the ray-combinaions that didn't get discarded for calculation...


            }

        }
    }


}

std::shared_ptr<FrameBuffer<float, BufferType::SingleBuffer>> Raytracer::rasterize_rays() {
    // TODO: Implement rasterisations of rays
    return {};
}
