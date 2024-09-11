#include "Mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>


Mesh::Mesh()
    :mLoaded(false)
{
}

Mesh::~Mesh()
{
    va.DeleteArray();
    vb.DeleteBuffer();
}


bool Mesh::loadOBJ(const std::string& filename)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempUVs;
    std::vector<glm::vec3> tempNormals;  // Add this for normals

    if (filename.find(".obj") != std::string::npos)
    {
        std::ifstream fin(filename, std::ios::in);
        if (!fin)
        {
            std::cerr << "Cannot open " << filename << std::endl;
            return false;
        }

        std::cout << "Loading OBJ file " << filename << " ..." << std::endl;

        std::string lineBuffer;
        while (std::getline(fin, lineBuffer))
        {
            if (lineBuffer.substr(0, 2) == "v ")  // Parse vertices
            {
                std::istringstream v(lineBuffer.substr(2));
                glm::vec3 vertex;
                v >> vertex.x; v >> vertex.y; v >> vertex.z;
                tempVertices.push_back(vertex);
            }
            else if (lineBuffer.substr(0, 2) == "vt")  // Parse texture coordinates
            {
                std::istringstream vt(lineBuffer.substr(3));
                glm::vec2 uv;
                vt >> uv.s; vt >> uv.t;
                tempUVs.push_back(uv);
            }
            else if (lineBuffer.substr(0, 2) == "vn")  // Parse normals
            {
                std::istringstream vn(lineBuffer.substr(3));
                glm::vec3 normal;
                vn >> normal.x; vn >> normal.y; vn >> normal.z;
                tempNormals.push_back(normal);
            }
            else if (lineBuffer.substr(0, 2) == "f ")  // Parse faces
            {
                int p1, p2, p3;
                int t1, t2, t3;
                int n1, n2, n3;
                const char* face = lineBuffer.c_str();
                int match = sscanf_s(face, "f %i/%i/%i %i/%i/%i %i/%i/%i",
                    &p1, &t1, &n1,
                    &p2, &t2, &n2,
                    &p3, &t3, &n3);
                if (match != 9)
                    std::cout << "Failed to parse OBJ file using our very simple OBJ loader" << std::endl;

                vertexIndices.push_back(p1);
                vertexIndices.push_back(p2);
                vertexIndices.push_back(p3);

                uvIndices.push_back(t1);
                uvIndices.push_back(t2);
                uvIndices.push_back(t3);

                normalIndices.push_back(n1);
                normalIndices.push_back(n2);
                normalIndices.push_back(n3);
            }
        }

        fin.close();

        // For each vertex of each triangle
        for (unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            glm::vec3 vertex = tempVertices[vertexIndices[i] - 1];
            glm::vec2 uv = tempUVs[uvIndices[i] - 1];
            glm::vec3 normal = tempNormals[normalIndices[i] - 1]; // Get normal

            Vertex meshVertex;
            meshVertex.position = vertex;
            meshVertex.texCoords = uv;
            meshVertex.normal = normal;  // Assign the normal to the vertex

            mVertices.push_back(meshVertex);
        }

        initBuffers();

        return (mLoaded = true);
    }

    return false;
}


void Mesh::initBuffers()
{
    va.GenArray();
    vb.GenBuffer();

    va.Bind();
    vb.Bind();
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    // Vertex Texture Coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));

    // unbind to make sure other code does not change it somewhere else
    va.UnBind();
}
void Mesh::draw()
{
    if (!mLoaded) return;

    va.Bind();
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    va.UnBind();
}
