#pragma once

class Game
{

public:
  static void Start();
  static bool IsExiting();
  static void GameLoop();

  enum GameState { Uninitialized, Playing, Exiting };

  static GameState _gameState;

private:
 };