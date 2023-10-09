//
// Created by bios on 10/9/23.
//

#include "OpenGLModel.h"
#include "GLShader.h"
#include "vector"
#include "memory"

namespace VectorVertex {

    OpenGLModel::OpenGLModel(const char* file) {
        std::string text = get_file_contents(file);
        JSON = json::parse(text);

        OpenGLModel::file = file;
        data = getData();

        traverseNode(0);
    }

    void OpenGLModel::Draw(Shader* shader, Camera &camera) {
        // Go over all meshes and draw each one
        for (unsigned int i = 0; i < meshes.size(); i++)
        {

            meshes[i]->Draw(CONVERT_REF(Shader, shader), camera, matricesMeshes[i]);
        }
    }



    void OpenGLModel::Position(Shader* shader, glm::vec3 newPosition) {

        GLuint OpenGLModelMatrixLocation = glGetUniformLocation(shader->GetID(), "newPos");
        glm::mat4 newOpenGLModelMatrix = glm::translate(glm::mat4(1.0f), newPosition);
        glUniformMatrix4fv(OpenGLModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(newOpenGLModelMatrix));
    }

    void OpenGLModel::Rotation(Shader* shader, glm::vec3 newRotation) {
        GLuint OpenGLModelMatrixLocation = glGetUniformLocation(shader->GetID(), "newRot");
        glm::mat4 newOpenGLModelMatrix = glm::rotate(glm::mat4(1.0f), newRotation.x, {1,0,0})
                                   *glm::rotate(glm::mat4(1.0f), newRotation.y, {0,1,0})
                                   *glm::rotate(glm::mat4(1.0f), newRotation.z, {0,0,1});
        glUniformMatrix4fv(OpenGLModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(newOpenGLModelMatrix));
    }

    void OpenGLModel::Scale(Shader* shader, glm::vec3 newScale) {
        GLuint OpenGLModelMatrixLocation = glGetUniformLocation(shader->GetID(), "newScale");
        glm::mat4 newOpenGLModelMatrix = glm::scale(glm::mat4(1.0f), newScale);
        glUniformMatrix4fv(OpenGLModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(newOpenGLModelMatrix));
    }
    void OpenGLModel::SetTransform(Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        Position(shader, position);
        Rotation(shader, rotation);
        Scale(shader, scale);
    }

    void OpenGLModel::loadMesh(unsigned int indMesh) {
        unsigned int posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
        unsigned int normalAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
        unsigned int texAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
        unsigned int indAccInd = JSON["meshes"][indMesh]["primitives"][0]["indices"];

        std::vector<float> posVec = getFloats(JSON["accessors"][posAccInd]);
        std::vector<glm::vec3> positions = groupFloatsVec3(posVec);
        std::vector<float> normalVec = getFloats(JSON["accessors"][normalAccInd]);
        std::vector<glm::vec3> normals = groupFloatsVec3(normalVec);
        std::vector<float> texVec = getFloats(JSON["accessors"][texAccInd]);
        std::vector<glm::vec2> texUVs = groupFloatsVec2(texVec);

        std::vector<Vertex> vertices = assembleVertices(positions, normals, texUVs);
        std::vector<GLuint> indices = getIndices(JSON["accessors"][indAccInd]);
        std::vector<Scope<Texture>> textures = getTexture();



        Scope<Mesh> newMesh = Mesh::Create(vertices, indices, textures);

        meshes.push_back(newMesh.get());

    }

    void OpenGLModel::traverseNode(unsigned int nextNode, glm::mat4 matrix) {
        json node = JSON["nodes"][nextNode];

        //translation
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
        if(node.find("translation") != node.end()){
            float transValues[3];
            for (unsigned int i = 0; i < node["translation"].size(); ++i) {
                transValues[i] = (node["translation"][i]);
            }
            translation = glm::make_vec3(transValues);
        }
        //rotation
        glm::quat  rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        if(node.find("rotation") != node.end()){
            float rotValues[4] =
                    {
                            node["rotation"][3],
                            node["rotation"][0],
                            node["rotation"][1],
                            node["rotation"][2]
                    };
            rotation = glm::make_quat(rotValues);
        }
        //scale
        glm::vec3 scale = glm::vec3(1.0f);
        if(node.find("scale") != node.end()){
            float scaleValues[3];
            for (unsigned int i = 0; i < node["scale"].size(); ++i) {
                scaleValues[i] = (node["scale"][i]);
            }
            scale = glm::make_vec3(scaleValues);
        }
        //matrix
        glm::mat4 matNode = glm::mat4(1.0f);
        if(node.find("matrix") != node.end()){
            float matValues[16];
            for (unsigned int i = 0; i < node["matrix"].size(); i++){
                matValues[i] = (node["matrix"][i]);
            }
            matNode = glm::make_mat4(matValues);
        }
        // Initialize matrices
        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 rot = glm::mat4(1.0f);
        glm::mat4 sca = glm::mat4(1.0f);

        // Use translation, rotation, and scale to change the initialized matrices
        trans = glm::translate(trans, translation);
        rot = glm::mat4_cast(rotation);
        sca = glm::scale(sca, scale);

        // Multiply all matrices together
        glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

        // Check if the node contains a mesh and if it does load it
        if (node.find("mesh") != node.end())
        {
            translationMeshes.push_back(translation);
            rotationMeshes.push_back(rotation);
            scalesMeshes.push_back(scale);
            matricesMeshes.push_back(matNextNode);

            loadMesh(node["mesh"]);
        }

        // Check if the node has children, and if it does, apply this function to them with the matNextNode
        if (node.find("children") != node.end())
        {
            for (unsigned int i = 0; i < node["children"].size(); i++)
                traverseNode(node["children"][i], matNextNode);
        }
    }

    std::vector<unsigned char> OpenGLModel::getData() {
        std::string bytesText;
        std::string uri = JSON["buffers"][0]["uri"];

        std::string fileStr = std::string(file);
        std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of("/")+1);
        bytesText = get_file_contents((fileDirectory + uri).c_str());

        std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
        return data;
    }

    std::vector<float> OpenGLModel::getFloats(json accessor) {
        std::vector<float> floatVec;

        unsigned int bufferViewInd = accessor.value("bufferView", 1);
        unsigned int count = accessor["count"];
        unsigned int accByteOffset = accessor.value("byteOffset", 0);
        std::string type = accessor["type"];

        json bufferView = JSON["bufferViews"][bufferViewInd];
        unsigned int byteOffset = bufferView["byteOffset"];

        unsigned int numPerVert;
        if(type == "SCALAR") numPerVert =1;
        else if(type == "VEC2") numPerVert = 2;
        else if(type == "VEC3") numPerVert = 3;
        else if(type == "VEC4") numPerVert = 4;
        else throw std::invalid_argument("type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

        unsigned int beginningOfData = byteOffset + accByteOffset;
        unsigned int lengthOfData = count * 4 * numPerVert;
        for(unsigned int i=beginningOfData; i < beginningOfData + lengthOfData; i)
        {
            unsigned char bytes[] = { data[i++],data[i++],data[i++],data[i++]};
            float value;
            std::memcpy(&value, bytes, sizeof(float));
            floatVec.push_back(value);

        }
        return floatVec;
    }

    std::vector<GLuint> OpenGLModel::getIndices(json accessor) {
        std::vector<GLuint> indices;

        unsigned int bufferViewInd = accessor.value("bufferView", 0);
        unsigned int count = accessor["count"];
        unsigned int accByteOffset = accessor.value("byteOffset", 0);
        unsigned int componentType = accessor["componentType"];

        json bufferView = JSON["bufferViews"][bufferViewInd];
        unsigned int byteOffset = bufferView["byteOffset"];

        unsigned int beginningOfData = byteOffset + accByteOffset;
        /*
         * 5125 unsigned int
         * 5123 unsigned short
         * 5122 short
         *
         * */
        if(componentType == 5125){//unsigned int
            for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i){
                unsigned char bytes[] = {data[i++],data[i++],data[i++],data[i++]};
                unsigned int value;
                std::memcpy(&value, bytes, sizeof(unsigned int));

                indices.push_back((GLuint)value);
            }
        } else if(componentType == 5123){//unsigned short
            for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i){
                unsigned char bytes[] = {data[i++],data[i++]};
                unsigned int value;
                std::memcpy(&value, bytes, sizeof(unsigned short));

                indices.push_back((GLuint)value);
            }
        }else if(componentType == 5122){//unsigned int
            for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i){
                unsigned char bytes[] = {data[i++],data[i++]};
                unsigned int value;
                std::memcpy(&value, bytes, sizeof(int));

                indices.push_back((GLuint)value);
            }
        }
        return indices;
    }

    std::vector<Scope<Texture>> OpenGLModel::getTexture() {
        std::vector<Scope<Texture>> textures;

        std::string fileStr = std::string(file);
        std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/')+1);



        for (unsigned int i = 0; i<JSON["images"].size(); i++){
            std::string texPath = JSON["images"][i]["uri"];

            bool skip = false;
            for (unsigned int j = 0; j < loadedTexName.size(); j++){
                if(loadedTexName[j]==texPath){
                    for(const auto& texture : loadedTex){
                        Scope<Texture> texturePtr = Texture::Create(texture->GetData());
                        textures.push_back(std::move(texturePtr));
                        skip = true;
                        break;
                    }
                }
            }
            if(!skip)
            {
                if (texPath.find("baseColor") != std::string::npos) {
                    TextureData diff_data;
                    diff_data.image = (fileDirectory + texPath).c_str();
                    diff_data.type = "diffuse";
                    diff_data.unit = loadedTex.size();
                    Scope<Texture> diffuse = Texture::Create(diff_data);
                    textures.push_back(std::move(diffuse));
                    loadedTex.push_back(std::move(diffuse));
                    loadedTexName.push_back(texPath);
                } else if (texPath.find("metallicRoughness") != std::string::npos) {
                    TextureData specular_data;
                    specular_data.image = (fileDirectory + texPath).c_str();
                    specular_data.type = "specular";
                    specular_data.unit = loadedTex.size();
                    Scope<Texture> specular = Texture::Create(specular_data);
                    textures.push_back(std::move(specular));
                    loadedTex.push_back(std::move(specular));
                    loadedTexName.push_back(texPath);
                }
            }
        }
        return textures;
    }

    std::vector<Vertex> OpenGLModel::assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals,
                                                std::vector<glm::vec2> texUVs) {
        std::vector<Vertex> vertices;
        for (int i=0; i <positions.size(); i++){
            vertices.push_back(
                    Vertex{
                            positions[i],
                            normals[i],
                            glm::vec3 (1.0f, 1.0f, 1.0f),
                            texUVs[i]
                    }
            );
        }
        return vertices;
    }

    std::vector<glm::vec2> OpenGLModel::groupFloatsVec2(std::vector<float> floatVec) {
        std::vector<glm::vec2> vectors;
        for (int i = 0; i < floatVec.size(); i) {
            vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));

        }
        return vectors;
    }

    std::vector<glm::vec3> OpenGLModel::groupFloatsVec3(std::vector<float> floatVec) {
        std::vector<glm::vec3> vectors;
        for (int i = 0; i < floatVec.size(); i) {
            vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));

        }
        return vectors;
    }

    std::vector<glm::vec4> OpenGLModel::groupFloatsVec4(std::vector<float> floatVec) {
        std::vector<glm::vec4> vectors;
        for (int i = 0; i < floatVec.size(); i) {
            vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));

        }
        return vectors;
    }
} // VectorVertex