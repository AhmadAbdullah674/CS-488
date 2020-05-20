#include "cube.hpp"
#include "cs488-framework/GlErrorCheck.hpp"
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

Cube::Cube(glm::vec3 postion, GLfloat size)
{
	m_rotation = 0.0f;
	m_color = glm::vec3(10.0f);
	m_size = size;
    m_translation = glm::vec3(postion);
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
    float half_size = m_size / 2.0f;
    static const float g_vertex_buffer_data[] = {
    -half_size,-half_size,-half_size, // triangle 1 : begin
    -half_size,-half_size, half_size,
    -half_size, half_size, half_size, // triangle 1 : end
    half_size, half_size,-half_size, // triangle 2 : begin
    -half_size,-half_size,-half_size,
    -half_size, half_size,-half_size, // triangle 2 : end
    half_size,-half_size, half_size,
    -half_size,-half_size,-half_size,
    half_size,-half_size,-half_size,
    half_size, half_size,-half_size,
    half_size,-half_size,-half_size,
    -half_size,-half_size,-half_size,
    -half_size,-half_size,-half_size,
    -half_size, half_size, half_size,
    -half_size, half_size,-half_size,
    half_size,-half_size, half_size,
    -half_size,-half_size, half_size,
    -half_size,-half_size,-half_size,
    -half_size, half_size, half_size,
    -half_size,-half_size, half_size,
    half_size,-half_size, half_size,
    half_size, half_size, half_size,
    half_size,-half_size,-half_size,
    half_size, half_size,-half_size,
    half_size,-half_size,-half_size,
    half_size, half_size, half_size,
    half_size,-half_size, half_size,
    half_size, half_size, half_size,
    half_size, half_size,-half_size,
    -half_size, half_size,-half_size,
    half_size, half_size, half_size,
    -half_size, half_size,-half_size,
    -half_size, half_size, half_size,
    half_size, half_size, half_size,
    -half_size, half_size, half_size,
    half_size,-half_size, half_size
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
    GLint uniformLocation_colour = shader.getUniformLocation("colour");

    // Set the uniform's value.
    glUniform3f(uniformLocation_colour, m_color.r, m_color.g, m_color.b);

    //vec3 z_axis(0.0f, half_size, 0.0f);
    //glm::mat4 transform;// = glm::mat4();//glm::translate(mat4(), vec3(m_shape_translation, 0.0f));
    //transform *= glm::scale(glm::mat4(), glm::vec3(m_size));
    //transform *= glm::rotate(mat4(), m_shape_rotation / RAD, z_axis);
    glm::mat4 W;
    W = glm::translate(W, m_translation);
    //W *= glm::scale(glm::mat4(), glm::vec3(m_size));
    GLint uniformLocation_modelMatrix = shader.getUniformLocation("M");
    glUniformMatrix4fv(uniformLocation_modelMatrix, 1, GL_FALSE,
        glm::value_ptr(W));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    shader.disable();


    // Restore defaults
    glBindVertexArray(0);

    CHECK_GL_ERRORS;
}