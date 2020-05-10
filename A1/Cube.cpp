#include "cube.hpp"
#include "cs488-framework/GlErrorCheck.hpp"
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

Cube::Cube()
{
    m_shader = std::make_shared<ShaderProgram>();
	m_rotation = 0.0f;
	m_translation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_color = glm::vec3(1.0f);
	m_size = 1.0f;
}

Cube::Cube(glm::vec3& postion, ShaderProgram *shader)
{
	//if (!shader)
	//{
	//	throw std::logic_error("No shader");
	//}
	//m_shader = std::shared_ptr<ShaderProgram>(shader);
	m_rotation = 0.0f;
	m_translation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_color = glm::vec3(1.0f);
	m_size = 1.0f;
}

Cube::~Cube()
{
    m_shader.reset();
}

void Cube::init(ShaderProgram* shader)
{
    if (!shader)
    {
    	throw std::logic_error("No shader");
    }
    m_shader = std::shared_ptr<ShaderProgram>(shader);
	enableVertexAttribIndices();
	uploadCubeDataToVbo();
    mapVboDataToShaderAttributeLocation();

}

void Cube::enableVertexAttribIndices()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	GLint positionAttribLocation = m_shader.get()->getAttribLocation("position");
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
void Cube::mapVboDataToShaderAttributeLocation()
{
    glBindVertexArray(m_vao);

    // Tell GL how to map data from the vertex buffer "m_vbo_triangle" into the
    // "position" vertex attribute index of our shader program.
    // This mapping information is stored in the Vertex Array Object "m_vao_triangle".
    // That is why we must bind "m_vao_triangle" first in the line above, so
    // that "m_vao_triangle" captures the data mapping issued by the call to
    // glVertexAttribPointer(...).
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    GLint positionAttribLocation = m_shader.get()->getAttribLocation("position");
    glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //-- Unbind target, and restore default values:
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    CHECK_GL_ERRORS;
}

void Cube::draw()
{
    glBindVertexArray(m_vao);

    m_shader.get()->enable();
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_shader.get()->disable();


    // Restore defaults
    glBindVertexArray(0);

    CHECK_GL_ERRORS;
}