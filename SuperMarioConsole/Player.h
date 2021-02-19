#pragma once

#include "ConsoleMario.h"
#include "PhysicsBody.h"

class Player : public PhysicsBody
{
public:
	Player(Vector2D _position);

	void BindPlayerInput(class PlayerInput* _input);

	void UpdateMove(Map& _map, float _deltaTime, float _gravity) override;

	void Destroy() override;

	bool GetIsDead() const;

	bool GetIsClear() const;

protected:
	void OnCollision(Map& _map, Map::TileType _tileType, Object* _hitObject, Vector2D _hitPoint,
		Vector2D _velocity) override;

private:
	bool bIsDead = false;

	bool bIsClear = false;

	class PlayerInput* Input;
};
