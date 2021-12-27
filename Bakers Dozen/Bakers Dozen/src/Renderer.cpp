#include "Renderer.h"

Renderer::Renderer(std::string url) : show(true)
{
	model.loadModel(url, true);
}

void Renderer::draw(ofVec3f& position, ofVec3f& rotation, float& angle, ofVec3f& scale)
{
	if (show) {
		ofPushMatrix();

		model.setPosition(position.x - camera->position.x, position.y - camera->position.y, position.z - camera->position.z);
		model.setRotation(0, angle, rotation.x - camera->rotation.x, rotation.y - camera->rotation.y, rotation.z - camera->rotation.z);
		model.setScale(scale.x, scale.y, scale.z);
		model.drawFaces();

		ofPopMatrix();
	}
}
