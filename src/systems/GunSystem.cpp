#include "systems/GunSystem.h"
#include "systems/Events.h"
#include "components/PlayerMotionControl.h"
#include "components/Position.h"
#include "components/Gun.h"
#include "KeyHandler.h"
#include "EntityCreator.h"

using namespace entityx;

GunSystem::GunSystem(const KeyHandler& keyHandler)
: m_keyHandler(keyHandler)
{
}

void GunSystem::update(EntityManager &entities,
                       EventManager &events,
                       double dt)
{
   PlayerMotionControl::Handle playerControl;
   Position::Handle position;
   Gun::Handle gun;
   for (Entity entity : entities.entities_with_components(playerControl, position, gun))
   {
      if (m_keyHandler.isPressed(playerControl->shoot))
      {
         if (!gun->isShooting)
         {            
            BulletCreator(position->position,
                          Vector2(0.0, -500.0)).create(entities.create());

            events.emit<EvPlaySound>(GUN_SHOOT);

            gun->isShooting = true;
         }
      }
      else
      {
         gun->isShooting = false;
      }
   }
}
