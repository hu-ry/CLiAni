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
    meshCount++;

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
        std::cout << std::to_string(mesh_to_construct.vertices[i].x) << std::to_string(mesh_to_construct.vertices[i].y) << std::to_string(mesh_to_construct.vertices[i].z) << startPos << std::endl;

        startPos = stringData.find(kmmDelim, thirdEnd + kmmDelim.length());
        startPos = stringData.find(kmmDelim, startPos + kmmDelim.length()) + kmmDelim.length();
    }

    // Insert constructed mesh
    meshes.push_back(mesh_to_construct);
}

void Raytracer::calc_triangle_plane(size_t mesh_to_calc) {
    Raytracer::Mesh& mesh = meshes[mesh_to_calc];
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