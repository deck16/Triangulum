#include "EntityCreator.h"
#include "components/PlayerMotionControl.h"
#include "components/Motion.h"
#include "components/Position.h"
#include "components/Animation.h"
#include "components/Display.h"
#include "components/Gun.h"
#include "graphics/SpaceShipView.h"
#include "graphics/BulletView.h"

using namespace entityx;

EntityCreator::EntityCreator(EntityManager& entityManager)
: m_entityManager(entityManager)
{
}

void EntityCreator::createSpaceShip()
{
   auto pSsv = new SpaceShipView();
   auto spaceShip = m_entityManager.create();
   spaceShip.assign<PlayerMotionControl>();
   spaceShip.assign<Motion>();
   spaceShip.assign<Position>();
   spaceShip.assign<Gun>();
   spaceShip.assign<Animation>(pSsv);
   spaceShip.assign<Display>(pSsv);
}

void EntityCreator::createBullet(const Vector2& position,
                                 const Vector2& velocity)
{
   auto pBv = new BulletView();
   auto bullet = m_entityManager.create();
   bullet.assign<Motion>(velocity);
   bullet.assign<Position>(position);
   bullet.assign<Display>(pBv);
}
