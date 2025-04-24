#include "Game.h"

void Main();

#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
    Main();
}
void Main()
{
   Game game;

   while (game.getGameRunning())
   {
       game.Update();
       game.Render();
   }
}