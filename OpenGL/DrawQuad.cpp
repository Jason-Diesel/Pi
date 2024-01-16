#include "DrawQuad.h"

DrawQuad::DrawQuad(ResourceManager* rm, ShaderHandler* sh)
{
	this->rm = rm;
	this->sh = sh;

    VAO = CreateVertexArray();
    std::vector<Vertex> vertecies;
    vertecies.push_back(Vertex(glm::vec3(-1.0, -1.0, 0), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertecies.push_back(Vertex(glm::vec3(-1.0, 1.0, 0), glm::vec2(0, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertecies.push_back(Vertex(glm::vec3(1.0, -1.0, 0), glm::vec2(1, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertecies.push_back(Vertex(glm::vec3(1.0, 1.0, 0), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    VBO = CreateVertexBuffer(vertecies);
    std::vector<uint32_t> indecie = { 0,1,2,3 };
    indecies = CreateIndeciesBuffer(indecie);

    this->rm->createShaderProgram("DrawQuad", rm->getShader("DrawQuadVertex.vert"), rm->getShader("DrawQuadFrag.frag"));
}

void DrawQuad::render()
{
    sh->setCurrentshader("DrawQuad");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE0, texture);

    GLTest(glBindVertexArray(VAO));
    GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indecies));

    GLTest(glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr));
}

void DrawQuad::setTexture(uint32_t tex)
{
    this->texture = tex;
}
