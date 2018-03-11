#pragma once
#include "BasePossessableController.h"

extern class Rigidbody;

class BoulderController : public BasePossessableController {
private:
	static const float MAX_MOVESPEED;
	static const float FRICTION;
	static const float COOLDOWN;
	std::shared_ptr<Rigidbody> m_rigidBody;
	float m_cooldownTicker;

public:
	BoulderController(GameObject* parentGameobject, BasePilot* pilot);
	virtual void onPossessionStart();
	virtual void onPossessionEnd();
	virtual void move(Vector2 direction);
	virtual void trigger(Vector2 direction);
};