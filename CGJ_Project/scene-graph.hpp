#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include < vector >
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "../mgl/mgl.hpp"

//start and end values for interpolation
//root
const glm::vec3 startCoordsRoot = { 0.0f, 0.0f, 0.0f };
const float startAngleRoot = 0.0f;
const glm::vec3 endCoordsRoot = { 0.0f, 0.0f, 0.0f };
const float endAngleRoot = 90.0f;

//child 0
const glm::vec3 startCoords0 = { -sqrt(2), -2*sqrt(2), 0.0f };
const float startAngle0 = 135.0f;
const glm::vec3 endCoords0 = { -4 + sqrt(2), -2 * sqrt(2) + 1, 0.0f};
const float endAngle0 = 315.0f;

//child 1
const glm::vec3 startCoords1 = { 0.0f, 2*sqrt(2), 0.0f };
const float startAngle1 = 315.0f;
const glm::vec3 endCoords1 = { -4.0f, -2 * sqrt(2) + 1, 0.0f };
const float endAngle1 = 135.0f;

//child 2
const glm::vec3 startCoords2 = { -2*sqrt(2), 0.0f, 0.0f };
const float startAngle2 = 45.0f;
const glm::vec3 endCoords2 = { -2.0f, -1.0f, 0.0f};
const float endAngle2 = 90.0f;

//child 3
const glm::vec3 startCoords3 = { sqrt(2), 0.0f, 0.0f };
const float startAngle3 = 225.0f;
const glm::vec3 endCoords3 = { -0.34f, 2.0f, 0.0f };
const float endAngle3 = 0.0f;

//child 4
const glm::vec3 startCoords4 = { sqrt(2), -sqrt(2), 0.0f };
const float startAngle4 = 0.0f;
const glm::vec3 endCoords4 = { 6.0f, -1.62f, 0.0f };
const float endAngle4 = 225.0f;

//child 5
const glm::vec3 startCoords5 = { 0.0f, -sqrt(2), 0.0f };
const float startAngle5 = 45.0f;
const glm::vec3 endCoords5 = { 1.0f, 0.0f, 0.0f };
const float endAngle5 = 0.0f;

//child 6
const glm::vec3 startCoords6 = { 1.5 * sqrt(2), 0.5 * sqrt(2), 0.0f };
const float startAngle6 = 225.0f;
const glm::vec3 endCoords6 = { 3.0f, -1.0f, 0.0f };
const float endAngle6 = 90.0f;

static glm::mat4 ModelMatrix(1.0f);

class SceneNode {
public:
	SceneNode(mgl::Mesh* m, glm::vec4 color, mgl::ShaderProgram* Shaders);
	void addChild(SceneNode* child);
	void draw(GLint ModelMatrixId, GLint ColorId);
	std::vector<SceneNode*> getChildren();

	void setCoordinates(glm::vec3 coords);
	glm::vec3 getCoordinates();
	void setAngle(float angle);
	float getAngle();
	void setRotationAxis(glm::vec3 axis);
	glm::vec3 getRotationAxis();
	void setScale(float scale);
	float getScale();

protected:
	SceneNode* parent;
	std::vector<SceneNode*> children;
	mgl::Mesh* mesh;
	glm::vec4 color;
	mgl::ShaderProgram* Shaders;

	//default atributes for each object
	glm::vec3 coordinates = { 0.0f, 0.0f, 0.0f };
	float angle = 0.0f;
	glm::vec3 rotAxis = { 0.0f, 0.0f, 1.0f };
	float scale = 1.0f;
};