#pragma once

#include "main.h"
#include "Vector2D.h"
#include "InputHandler.h"
class Walker 
{
  int _x, _y; 
  int mass;
  float speed=0;
  Vector2D Obs = Vector2D(300, 200);
  Vector2D hiderLocation = Vector2D(30, 200);
  Vector2D hunterLocation = Vector2D(300, 200);
  Vector2D velocity = Vector2D(0, 0);
  Vector2D acceleration = Vector2D(0, 0);
  Vector2D moving = Vector2D(0.02,0);
  Vector2D* mouse = TheInputHandler::Instance()->getMousePosition();
public:
  Walker(int m, int x, int y);
  void drawHunter(SDL_Renderer* renderer);
  void drawHider(SDL_Renderer* renderer);
  void obstacleObj(SDL_Renderer* renderer);
  void update();
  void applyForce(Vector2D& force);
  void huntercheckEdge();
  void hidercheckEdge();
  Vector2D& movingObj();

  Vector2D GetHidingPosition(const Vector2D& posObstacle, const double radiusObstacle, const Vector2D& posHunter);
  Vector2D GetHiderPosition();
  Vector2D& hide();
};