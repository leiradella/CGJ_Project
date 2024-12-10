#include "scene-graph.hpp"

SceneNode::SceneNode(mgl::Mesh* mesh, glm::vec4 color, mgl::ShaderProgram* Shaders) {
	this->mesh = mesh;
	this->color = color;
	parent = NULL;
	this->Shaders = Shaders;
}

void SceneNode::draw(GLint ModelMatrixId, GLint ColorId) {
	if (mesh) {
		Shaders->bind();
		glUniformMatrix4fv(ModelMatrixId, 1, GL_FALSE, glm::value_ptr(ModelMatrix * ScaleMatrix));
		glUniform4fv(ColorId, 1, glm::value_ptr(color));
		mesh->draw();
		Shaders->unbind();
	}
	for (int i = 0; i < children.size(); i++) {
		children[i]->draw(ModelMatrixId, ColorId);
	}
}

void SceneNode::addChild(SceneNode* child) {
	children.push_back(child);
	child->parent = this;
}

void SceneNode::setMatrix(glm::mat4 matrix) {
	this->ModelMatrix = matrix;
	std::vector<SceneNode*> children = this->getChildren();
	for (int i = 0; i < children.size(); i++) {
		children[i]->update(matrix);
	}
}

void SceneNode::update(glm::mat4 matrix) {
	this->ModelMatrix = matrix * ModelMatrix;
	std::vector<SceneNode*> children = this->getChildren();
	for (int i = 0; i < children.size(); i++) {
		children[i]->update(matrix);
	}
}