#include "scene-graph.hpp"

SceneNode::SceneNode(mgl::Mesh* mesh, glm::vec4 color, mgl::ShaderProgram* Shaders) {
	this->mesh = mesh;
	this->color = color;
	parent = NULL;
	ModelMatrix = glm::mat4(1.0f);
	this->Shaders = Shaders;
}

void SceneNode::draw(GLint ModelMatrixId, GLint ColorId) {
	if (mesh) {
		Shaders->bind();
		glUniformMatrix4fv(ModelMatrixId, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		glUniform4fv(ColorId, 1, glm::value_ptr(color));
		mesh->draw();
		Shaders->unbind();
	}
}

void SceneNode::addChild(SceneNode* child) {
	children.push_back(child);
	child->parent = this;
}

std::vector<SceneNode*> SceneNode::getChildren() {
	return children;
}

void SceneNode::setModelMatrix(glm::mat4 model) {
	ModelMatrix = model;
}

void SceneNode::transform(glm::mat4 transformMatrix) {
	ModelMatrix = transformMatrix * ModelMatrix;
	for (int i = 0; i < children.size(); i++) {
		children[i]->transform(transformMatrix);
	}
}

void SceneNode::setCoordinates(glm::vec3 coords) {
	coordinates = coords;
}

glm::vec3 SceneNode::getCoordinates() {
	return coordinates;
}

void SceneNode::setAngle(float angle) {
	this->angle = angle;
}

float SceneNode::getAngle() {
	return angle;
}

void SceneNode::setScale(float scale) {
	this->scale = scale;
}

float SceneNode::getScale() {
	return scale;
}