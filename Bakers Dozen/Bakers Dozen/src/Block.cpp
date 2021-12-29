#include "Block.h"

void Block::draw()
{
	if (active) {
		ofDrawBox(glm::vec3(x * 2 - 15, 0, y * 2 - 15), 2);
	}
}
