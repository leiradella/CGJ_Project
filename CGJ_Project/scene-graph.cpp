#include "scene-graph.hpp"

SceneNode::SceneNode(mgl::Mesh* mesh, glm::vec4 color, mgl::ShaderProgram* Shaders) {
	this->mesh = mesh;
	this->color = color;
	parent = NULL;
	ModelMatrix = glm::mat4(1.0f);
	this->Shaders = Shaders;
}

void SceneNode::draw(GLint ModelMatrixId, GLint ColorId) {
	ModelMatrix = glm::translate(coordinates) * glm::rotate(glm::radians(angle), rotAxis) * glm::scale(glm::vec3(scale, scale, 1.0f));
	if (mesh) {
		Shaders->bind();
		glUniformMatrix4fv(ModelMatrixId, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
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

std::vector<SceneNode*> SceneNode::getChildren() {
	return children;
}

void SceneNode::setAttributes(glm::vec3 coords, glm::vec3 axis, float angle, float scale) {
	for (int i = 0; i < children.size(); i++) {
		children[i]->transform(coordinates - coords, axis, this->angle - angle, scale/this->scale);
	}
	coordinates = coords;
	rotAxis = axis;
	this->angle = angle;
	this->scale = scale;
}

void SceneNode::transform(glm::vec3 coords, glm::vec3 axis, float angle, float scale) {
	coordinates += coords;
	rotAxis = axis;
	this->angle += angle;
	this->scale *= scale;
	for (int i = 0; i < children.size(); i++) {
		children[i]->transform(coords, axis, angle, scale);
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

void SceneNode::setRotationAxis(glm::vec3 axis) {
	rotAxis = axis;
}

glm::vec3 SceneNode::getRotationAxis() {
	return rotAxis;
}

void SceneNode::setScale(float scale) {
	this->scale = scale;
}

float SceneNode::getScale() {
	return scale;
}