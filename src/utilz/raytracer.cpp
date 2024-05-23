//##############################################################################
//## Project: cliAnimation ###################### Created by hury on 16.03.24 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <fstream>
#include <iostream>
#include <algorithm>
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

void Raytracer::load_mesh_from_string(std::string &mesh_string) {

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

    // We parse Mesh Informations specified before the "---" seperator here
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
    size_t startOfMeshDelim = mesh_string.find("---", 0);
    mesh_string = mesh_string.substr(mesh_string.find(nwlnDelim, startOfMeshDelim)+1, std::string::npos);

    // ===================

    std::string stringData;

    // Reset start-position since we cut off string at "---" delimiter
    startPos = 0;
    auto kmmPos = mesh_string.find(kmmDelim, startPos);
    auto SmclnPos = mesh_string.find(smclnDelim, startPos);
    auto nwlnPos = mesh_string.find(nwlnDelim, startPos);

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

    //*sizeArray = std::count(stringData.begin(), stringData.end(), ',') + 1;

    std::cout << ",: " << kmmPos << std::endl;
    std::cout << ";: " << SmclnPos << std::endl;
    std::cout << "newline: " << nwlnPos << std::endl;
    std::cout << "startPos: " << startPos << std::endl;

    std::cout << stringData << std::endl;


    // TODO: Implement conversion from strings to floats and insertion of read-out mesh

    // Insert constructed mesh
    meshes.push_back(mesh_to_construct);
}

humath::v4f Raytracer::calc_plane() {
    return {}; // TODO: calculate triangle planes from vertices and normals
}