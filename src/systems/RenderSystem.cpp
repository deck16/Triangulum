#include "SDL_opengl.h"
#include "systems/RenderSystem.h"
#include "components/Position.h"
#include "components/Display.h"

using namespace entityx;

RenderSystem::RenderSystem(SDL_Window* pWindow)
: m_pWindow(pWindow)
{
}

void RenderSystem::update(EntityManager &entities,
                          EventManager &events,
                          double dt)
{
   glClear(GL_COLOR_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);

   Position::Handle position;
   Display::Handle display;
   for (Entity entity : entities.entities_with_components(position, display))
   {
      glLoadIdentity();
      display->spDrawable->draw(*position.get());
   }

   SDL_GL_SwapWindow(m_pWindow);
}
