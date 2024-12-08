# include < vector >

#include "../mgl/mgl.hpp"

class SceneNode {
public:
	SceneNode(mgl::Mesh* m, glm::vec4 color, mgl::ShaderProgram* Shaders);
	void addChild(SceneNode* child);
	void draw();

protected:
	SceneNode* parent;
	std::vector<SceneNode> children;
	mgl::Mesh* mesh;
	glm::vec4 color;
	glm::mat4 ModelMatrix;
	mgl::ShaderProgram* Shaders;
};