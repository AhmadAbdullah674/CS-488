#ifndef cube_hpp
#define cube_hpp

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"

#include <memory>
#include <chrono>
#include <string>
#include <glm/glm.hpp>


class Cube {
public:
	Cube();
	Cube(glm::vec3 &postion);
	~Cube();
	void init(ShaderProgram const& shader);
	void draw(ShaderProgram const& shader);
protected:
	void enableVertexAttribIndices(ShaderProgram const& shader);
	void uploadCubeDataToVbo();
	void mapVboDataToShaderAttributeLocation(ShaderProgram const& shader);

	GLuint m_vao; // Vertex Array Object
	GLuint m_vbo; // Vertex Buffer Object

	float m_rotation;
	glm::vec3 m_translation;
	glm::vec3 m_color;
	float m_size;

};

#endif // cube_hpp

