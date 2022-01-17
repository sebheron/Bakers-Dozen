#include "Block.h"

Block::Block(bool breakable, ofTexture* texture) : GridItem(false, false, breakable)
{
	this->texture = texture;
}

void Block::draw()
{
	if (active) {
		texture->bind();
		ofDrawBox(glm::vec3(x * 2 - 15, 0, y * 2 - 15), 2);
		texture->unbind();
	}
}
