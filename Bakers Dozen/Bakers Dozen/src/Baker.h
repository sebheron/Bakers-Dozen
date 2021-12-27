#include <string>
#include "Entity.h"
#include "Transform.h"

#ifndef BAKER_H
#define BAKER_H

class Baker: public Entity {
public:
	Baker(std::string url);

	void start();
	void update(float deltaTime);
};

#endif // BAKER_H