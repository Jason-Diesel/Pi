#include "BufferCreator.h"

uint32_t CreateVertexArray()
{
    uint32_t buffer = 0;

    GLTest(glGenVertexArrays(1, &buffer));
    GLTest(glBindVertexArray(buffer));

    return buffer;
}

uint32_t CreateIndeciesBuffer(std::vector<uint32_t>& vertecies)
{
	uint32_t buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * vertecies.size(), vertecies.data(), GL_STATIC_DRAW);
    return buffer;
}

void setUniform(std::string uniformName, const uint32_t uniformBuffer, GLuint bindingIndex)
{
    GLTest(glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, uniformBuffer));
    GLint v;
    glGetIntegerv(GL_CURRENT_PROGRAM, &v);

	GLuint blockIndex = glGetUniformBlockIndex(v, uniformName.c_str());
    GLTest(glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, uniformBuffer));
	GLTest(glUniformBlockBinding(v, blockIndex, bindingIndex));

}

void createDepthStencil(uint32_t Width, uint32_t Height, uint32_t &depthBufferFBO, uint32_t &depthBuffer)
{
    glGenFramebuffers(1, &depthBufferFBO);

    glGenTextures(1, &depthBuffer);
    glBindTexture(GL_TEXTURE_2D, depthBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    static const float clampColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

    glBindFramebuffer(GL_FRAMEBUFFER, depthBufferFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
