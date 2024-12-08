#pragma once

#include < vector >
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../mgl/mgl.hpp"

class SceneNode {
public:
	SceneNode(mgl::Mesh* m, glm::vec4 color, mgl::ShaderProgram* Shaders);
	void addChild(SceneNode* child);
	void draw(GLint ModelMatrixId, GLint ColorId);
	std::vector<SceneNode*> getChildren();
	void transform(glm::mat4 transformMatrix);
	glm::mat4 getModelMatrix();

protected:
	SceneNode* parent;
	std::vector<SceneNode*> children;
	mgl::Mesh* mesh;
	glm::vec4 color;
	glm::mat4 ModelMatrix;
	mgl::ShaderProgram* Shaders;
};