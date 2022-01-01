#include "AICharacter.h"

void AICharacter::update(float deltaTime)
{
	//if (state == Thinking && waitTime <= 0) {
	//	index = 0;
	//	//List<GameObject> powerups = CheckForPowerups();
	//	if (board->checkPlaceBomb(x, y) && currentPath != null) {
	//		currentPath.Reverse();
	//		state = Hiding;
	//	}
	//	if (CheckForBombs((int)v2Position.x, (int)v2Position.y).Count > 0) {
	//		waitForBombPosition = new Vector2(Mathf.RoundToInt(transform.position.x), Mathf.RoundToInt(transform.position.z));
	//		currentPath = FindPathToSafePosition();
	//		if (currentPath != null)
	//			State = AIBomberState.Hiding;
	//	}
	//	else if (SceneController.GetPlayerAtPosition((int)v2Position.x, (int)v2Position.y, gameObject)) {
	//		currentPath = FindPathToSafePosition(Random.Range(0, 2));
	//		if (currentPath != null)
	//			State = AIBomberState.Hiding;
	//	}
	//	else if (powerups.Count > 0) {
	//		objective = powerups[0];
	//		currentPath = FindPathToPowerup(objective);
	//		if (currentPath != null)
	//			State = AIBomberState.Seeking;
	//	}
	//	else if (bombsAvailable > 0) {
	//		objective = GetNearestPlayer();
	//		if (objective != null) {
	//			currentPath = FindPathToPlayer(objective);
	//			if (currentPath != null)
	//				State = AIBomberState.Seeking;
	//		}
	//	}
	//	lastAction = State;
	//}
	//else if (currentPath == null) {
	//	State = AIBomberState.Thinking;
	//}
	//else if (State == AIBomberState.Bombing) {
	//	AddBomb(v2Position);
	//	State = AIBomberState.Thinking;
	//	waitTime = 1 / Intelligence;
	//}
	//else if (State == AIBomberState.Seeking) {
	//	if (index < currentPath.Count) {
	//		if (currentPath[index].Position.x == transform.position.x && currentPath[index].Position.y == transform.position.z) {
	//			index++;
	//		}
	//		else {
	//			if (Vector2.Distance(currentPath[index].Position, v2Position) > 1) {
	//				State = AIBomberState.Thinking;
	//			}
	//			if (CheckForPlayers(Mathf.RoundToInt(transform.position.x), Mathf.RoundToInt(transform.position.z)).Count <= 0) {
	//				SetDirectionToMove(currentPath[index].Position - v2Position);
	//				if (objective != GetNearestPlayer()) {
	//					State = AIBomberState.Thinking;
	//				}
	//				else if (!moving) {
	//					State = AIBomberState.Bombing;
	//				}
	//			}
	//			else {
	//				State = AIBomberState.Bombing;
	//			}
	//		}
	//	}
	//	else {
	//		State = AIBomberState.Thinking;
	//		waitTime = 1.5f / Intelligence;
	//	}
	//}
	//else if (State == AIBomberState.Hiding) {
	//	if (index < currentPath.Count) {
	//		if (bombDetonate && CheckForBombs(Mathf.RoundToInt(transform.position.x), Mathf.RoundToInt(transform.position.z)).Count <= 0) {
	//			DetonateBombs();
	//		}
	//		if (currentPath[index].Position.x == transform.position.x && currentPath[index].Position.y == transform.position.z) {
	//			index++;
	//		}
	//		else {
	//			if (Vector2.Distance(currentPath[index].Position, v2Position) > 1) {
	//				State = AIBomberState.Thinking;
	//			}
	//			if (SceneController.GetPlayerAtPosition((int)currentPath[index].Position.x, (int)currentPath[index].Position.y, gameObject) == null) {
	//				SetDirectionToMove(currentPath[index].Position - v2Position);
	//			}
	//			else if (bombDetonate) {
	//				State = AIBomberState.Thinking;
	//			}
	//			if (!moving) {
	//				State = AIBomberState.Thinking;
	//				waitTime = 1 / Intelligence;
	//			}
	//		}
	//	}
	//	else {
	//		State = AIBomberState.Waiting;
	//	}
	//}
	//else if (State == AIBomberState.Waiting) {
	//	if (CheckForBombs(Mathf.RoundToInt(transform.position.x), Mathf.RoundToInt(transform.position.z)).Count > 0 ||
	//		CheckForBombs((int)waitForBombPosition.x, (int)waitForBombPosition.y).Count <= 0) {
	//		State = AIBomberState.Thinking;
	//		waitTime = 1.5f / Intelligence;
	//	}
	//}
	//if (currentPath != null)
	//	print(gameObject.name + " - " + lastAction + " - " + string.Join(",", currentPath.Select(x = > x.Position)));
	//waitTime -= Time.deltaTime;
}

std::vector<GridItem*> findPathTo(int x, int y) {
	/*var path = SceneController.astar.FindPath(v2Position, new Vector2(Mathf.Round(powerup.transform.position.x), Mathf.Round(powerup.transform.position.z)));
	if (path != null)
		return path.ToList();
	else
		return null;*/
}

std::vector<int> AICharacter::findPathToSafePosition()
{
	//std::vector<int> nodes = SceneController.astar.GetAllEmptyNodes()
	//	.Where(x = > x.Position != v2Position)
	//	.Where(x = > CheckForBombs((int)x.Position.x, (int)x.Position.y).Count == 0 && CheckForPlayers((int)x.Position.x, (int)x.Position.y).Count == 0)
	//	.OrderBy(x = > GetPathLength(v2Position, x.Position)).ToList();
	//for (int i = skip; i < nodes.Count; i++) {
	//	var path = SceneController.astar.FindPath(v2Position, nodes[i].Position);
	//	if (path != null) {
	//		return path.ToList();
	//	}
	//}
	//return null;
}

std::vector<Pickup*> AICharacter::checkForRelativePickups()
{
	std::vector<Pickup*> pickups;
	for (int xx = 0; xx < BOARD_SIZE; xx++) {
		for (int yy = 0; yy < BOARD_SIZE; yy++) {
			float dis = glm::vec3(x - xx, 0, y - yy).length();
			//TODO: add check for obtained powerups, ignoring those which are already collected.
			//!ObtainedPowerup(Board[xx, yy].GetComponent<PickupController>())
			//NEEDS PATH LENGTH CHECK TOO!
			//GetPathLength(startPos, pos) < 8
			if (board->checkPlacePickup(xx, yy)) {
				pickups.push_back((Pickup*)board->getGridItem(xx, yy));
			}
		}
	}
	return pickups;
}

std::vector<Bomb*> AICharacter::checkForBombs(int x, int y) {
	std::vector<Bomb*> bombs;
	for (int xx = 0; xx < BOARD_SIZE; xx++) {
		for (int yy = 0; yy < BOARD_SIZE; yy++) {
			if ((xx == x || y == yy) && board->checkPlaceBomb(xx, yy)) {
				float dis = glm::vec3(x - xx, 0, y - yy).length();
				Bomb* bomb = (Bomb*)board->getGridItem(xx, yy);
				if (*bomb->power >= dis) {
					bombs.push_back(bomb);
				}
			}
		}
	}
	return bombs;
}

std::vector<Character*> AICharacter::checkForPlayers(int x, int y) {
	glm::vec3 startPos = glm::vec3(x, 0, y);
	std::vector<Character*> targets;
	for (Character* player : players) {
		glm::vec3 playerPos = player->getPosition();
		float dis = (playerPos - startPos).length();
		if (dis > 0 && (playerPos.x == position.x || playerPos.y == position.y)
			&& dis <= power/2.) {
			//TODO: Sort players by distance
			targets.push_back(player);
		}
	}
	return targets;
}

bool AICharacter::isPlayerThreat(Character* player) {
	return getPowerLevel() <= player->getPowerLevel();
}

Character* AICharacter::getNearestPlayer() {
	Character* bestTarget = 0;
	float closest = INFINITY;
	for(Character* potentialTarget : players) {
		float dis = (potentialTarget->getPosition() - position).length();
		if (dis > 0 && dis < closest) {
			closest = dis;
			bestTarget = potentialTarget;
		}
	}
	return bestTarget;
}
//

//
//
//
//
//queue<Node> lee(int startX, int startY)
//{
//	static int dl[] = { -1, 0, 1, 0 };
//	static int dc[] = { 0, 1, 0, -1 };
//
//	queue<Node> path;
//	path.push(Node{ startX, startY });
//
//	int x, y, xx, yy;
//	while (!path.empty())
//	{
//		x = path.front().x;
//		y = path.front().y;
//		for (int i = 0; i < 4; i++)
//		{
//			xx = x + dl[i];
//			yy = y + dc[i];
//			if (board->)
//			{
//				path.push(Node{ xx, yy });
//				mat[xx][yy] = -1;
//			}
//		}
//		path.pop();
//	}
//}