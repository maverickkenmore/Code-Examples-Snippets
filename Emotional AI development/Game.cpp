#include "Game.h"



void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;

  _gameState = Game::Playing;
  
  while(!IsExiting())
  {
    GameLoop();
  }

}



bool Game::IsExiting()
{
  if(_gameState == Game::Exiting) 
    return true;
  else 
    return false;
}

void Game::GameLoop()
{
  while(_gameState = Game::Playing)
  {
  
    
      
    
  }
}