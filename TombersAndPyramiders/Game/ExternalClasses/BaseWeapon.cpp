/*===================================================================================*//**
	BaseWeapon
	
	Abstract class for a base weapon.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseWeapon.h"
#include "Inventory.h"
#include <memory>

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseWeapon::BaseWeapon(int damage, float attackCooldownTime) :
	m_damage{ damage }, 
	m_attackCooldownTime{ attackCooldownTime }, 
	m_isAttacking{ false }
{}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
std::shared_ptr<BaseItem> BaseWeapon::addSubclassToInventory()
{
	return m_inventory->setWeapon(shared_from_this());
}
