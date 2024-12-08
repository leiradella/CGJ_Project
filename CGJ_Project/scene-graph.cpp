#include "scene-graph.hpp"

SceneNode::SceneNode(mgl::Mesh* mesh, glm::vec4 color, mgl::ShaderProgram* Shaders) {
	this->mesh = mesh;
	this->color = color;
	parent = NULL;
	ModelMatrix = glm::mat4(1.0f);
	this->Shaders = Shaders;
}

void SceneNode::draw() {
	if (mesh) {
		mesh->draw();
	}
}

void SceneNode::addChild(SceneNode* child) {
	children.push_back(*child);
	child->parent = this;
}