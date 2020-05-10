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
	Cube(glm::vec3 &postion, ShaderProgram *shader);
	~Cube();
	void init(ShaderProgram* shader);
	void draw();
protected:
	void enableVertexAttribIndices();
	void uploadCubeDataToVbo();
	void mapVboDataToShaderAttributeLocation();

	GLuint m_vao; // Vertex Array Object
	GLuint m_vbo; // Vertex Buffer Object

	float m_rotation;
	glm::vec3 m_translation;
	glm::vec3 m_color;
	float m_size;
	std::shared_ptr<ShaderProgram> m_shader;

};

#endif // cube_hpp

