#pragma once

#include <utility/Model.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void drawModel(Model& object, Shader& shader, glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection) {
	shader.use();
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	object.Draw(shader);
}