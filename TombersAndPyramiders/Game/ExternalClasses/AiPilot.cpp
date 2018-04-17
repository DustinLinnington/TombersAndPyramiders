#pragma
#include "AiPilot.h"
#include <cmath>
int attackNumber = 0;
int randomNumber = 0;
int attackCount = 0;

void AiPilot::setController(BaseController* controller)
{
	BasePilot::setController(controller);

	m_characterController = static_cast<CharacterController*>(controller);
}

void AiPilot::onStart()
{
	currentState = walk;
	srand(time(NULL));
	//currentState = run;
}

void AiPilot::CheckingTimer()
{
	if (TimePassed >= 1.0f)
	{
		TimePassed = 0.0f;
		// Get a new target
		if (target == nullptr)
		{
			for (int i = 0; i < SpawnManager::getInstance()->allPlayers.size(); i++)
			{
				float distance = SpawnManager::getInstance()->allPlayers[i]->getTransform()->getDistance(m_characterController->getGameObject()->getTransform());
				if (distance < engageDistance)
				{
					target = SpawnManager::getInstance()->allPlayers[i];
				}
			}
		}
		else if(target != nullptr)
		{
			float distance = target->getTransform()->getDistance(m_characterController->getGameObject()->getTransform());

			if (distance > disengageDistance)
			{
				target = nullptr;
				currentState = walk;
			}
		}
	}
}

void AiPilot::onUpdate(int ticks)
{
	TimePassed =  TimePassed + (float)ticks / 1000.0f;
	CheckingTimer();

	movement = Vector2(0, 0);
	switch (currentState)
	{
	case walk:
		if (target == nullptr)
		{
			m_characterController->move(getRandomMovement());
		}
		else
		{
			m_characterController->move(getMovement());
			if (checkRange() == true)
			{
				currentState = attack;
			}
		}
		break;
	case attack:
		m_characterController->move(stopMovement());
		m_characterController->useWeapon();
		if (checkRange() == false)
		{
			currentState = walk;
		}
		break;
	}
}

bool AiPilot::checkRange()
{
	if (target != nullptr)
	{
		float distance = target->getTransform()->getDistance(m_characterController->getGameObject()->getTransform());
		if (distance < stopDistance)
		{
			return true;
		}
	}

	return false;
}

/* bool checkPlayerStatus();
{
	if (target->Ghost)
	{
		target = nullptr;
		currentState = walk;
		return true;
	}
	return false;
}
*/
	

Vector2 AiPilot::getMovement()
{
	//m_characterController->updateSpeed(Vector2(1, 1));

	if (target != nullptr) {
		float myX = m_characterController->getGameObject()->getTransform()->getX();
		float myY = m_characterController->getGameObject()->getTransform()->getY();
		float targetX = target->getTransform()->getX();
		float targetY = target->getTransform()->getY();

		float x = abs(targetX - myX);
		float y = abs(targetY - myY);
		
		if (myX > targetX)
		{
			x = x *= -1;
		}
		if (myY > targetY)
		{
			y = y *= -1;
		}
		
		if (x < 0)
		{
			x = -0.7;
		}
		if (x > 0)
		{
			x = 0.7;
		}
		if (y < 0)
		{
			y = -0.7;
		}
		if (y > 0)
		{
			y = 0.7;
		}
		movement.setX(x);
		movement.setY(y);
	}

	return movement;
}

Vector2 AiPilot::getRandomMovement()
{
	coun++;
	if (coun == 30)
	{
		randomNumber = rand() % 11;
		coun = 0;
	}
	if (randomNumber == 1)
	{
		movement.setX(-0.8f);
	}
	else if (randomNumber == 2)
	{
		movement.setX(0.8f);
	}
	else if (randomNumber == 3)
	{
		movement.setY(0.8f);
		movement.setX(0.6f);
	}
	else if (randomNumber == 4 )
	{
		movement.setY(-0.8f);
		movement.setX(0.6f);
	}
	if (randomNumber == 5 )
	{
		movement.setX(-0.8f);
		movement.setY(-0.6f);
	}
	else if (randomNumber == 6)
	{
		movement.setX(0.8f);
		movement.setY(-0.6f);
	}
	else if (randomNumber == 7)
	{
		movement.setY(0.8f);
		movement.setX(0);
	}
	else if (randomNumber == 8)
	{
		movement.setY(-0.8f);
		movement.setX(0);
	}

	return movement;
}

 Vector2 AiPilot::stopMovement()
{
	movement.setX(0);
	movement.setY(0);

	return movement;
}

