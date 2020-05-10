#include "cube.hpp"
#include "cs488-framework/GlErrorCheck.hpp"
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

Cube::Cube()
{
	m_rotation = 0.0f;
	m_translation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_color = glm::vec3(1.0f);
	m_size = 1.0f;
}

Cube::Cube(glm::vec3& postion)
{
	m_rotation = 0.0f;
	m_translation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_color = glm::vec3(1.0f);
	m_size = 1.0f;
}

Cube::~Cube()
{
}

void Cube::init(ShaderProgram const& shader)
{
	enableVertexAttribIndices(shader);
	uploadCubeDataToVbo();
    mapVboDataToShaderAttributeLocation(shader);

}

void Cube::enableVertexAttribIndices(ShaderProgram const& shader)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	GLint positionAttribLocation = shader.getAttribLocation("position");
	glEnableVertexAttribArray(positionAttribLocation);

	// Restore defaults
	glBindVertexArray(0);

	CHECK_GL_ERRORS;
}
void Cube::uploadCubeDataToVbo()
{
    static const float g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };
    glGenBuffers(1, &m_vbo);

    //-- Upload triangle vertex data to the vertex buffer:
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data,
        GL_STATIC_DRAW);


    // Unbind the target GL_ARRAY_BUFFER, now that we are finished using it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    CHECK_GL_ERRORS;
}
void Cube::mapVboDataToShaderAttributeLocation(ShaderProgram const& shader)
{
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    GLint positionAttribLocation = shader.getAttribLocation("position");
    glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //-- Unbind target, and restore default values:
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    CHECK_GL_ERRORS;
}

void Cube::draw(ShaderProgram const& shader)
{
    glBindVertexArray(m_vao);

    shader.enable();
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    shader.disable();


    // Restore defaults
    glBindVertexArray(0);

    CHECK_GL_ERRORS;
}