# include < vector >

#include "../mgl/mgl.hpp"

class SceneNode {
protected:
	SceneNode* parent;
	std::vector<SceneNode> children;
	mgl::Mesh* mesh;
	glm::mat4 ModelMatrix;
	mgl::ShaderProgram* Shaders;
};