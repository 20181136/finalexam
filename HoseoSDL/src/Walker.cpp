#define WIDTH (600)
#define HEIGHT (400)

#include "Walker.h"
#include <random>


Walker::Walker(int m, int x, int y) 
{
  Obs.setX(x);
  Obs.setY(y);
  hunterLocation.setX(x);
  hunterLocation.setY(y);
  hiderLocation.setX(x);
  hiderLocation.setY(y);
  mass = m;
}

void Walker::update() 
{
	hunterLocation += velocity;
	velocity += acceleration;
	acceleration *= 0;
}
void Walker :: applyForce(Vector2D& force)
{
	acceleration= force / mass;
}

Vector2D& Walker::movingObj()
{
	return moving;
}

void Walker::huntercheckEdge()
{
	if (hunterLocation.getX() > WIDTH)
	{
		hunterLocation.setX(-mass);
	}
	else if (hunterLocation.getX() < -mass)
	{
		hunterLocation.setX(WIDTH + mass);
	}

	if (hunterLocation.getY() > HEIGHT)
	{
		hunterLocation.setY(-mass);
	}
	else if (hunterLocation.getY() < 0)
	{
		hunterLocation.setY(HEIGHT + mass);
	}
}

void Walker::hidercheckEdge()
{
	if (hiderLocation.getX() > WIDTH)
	{
		hiderLocation.setX(-mass);
	}
	else if (hiderLocation.getX() < -mass)
	{
		hiderLocation.setX(WIDTH + mass);
	}

	if (hiderLocation.getY() > HEIGHT)
	{
		hiderLocation.setY(-mass);
	}
	else if (hiderLocation.getY() < 0)
	{
		hiderLocation.setY(HEIGHT + mass);
	}
}

void Walker::drawHunter(SDL_Renderer* renderer)
{
 filledCircleColor(renderer, mouse->getX(), mouse->getY(),mass, 0xFFFFFFFF); 
}

void Walker::drawHider(SDL_Renderer* renderer)
{
	filledCircleColor(renderer, hiderLocation.getX(), hiderLocation.getY(), mass, 0xFFFFFFFF);
}

void Walker::obstacleObj(SDL_Renderer* renderer)
{
	filledCircleColor(renderer, Obs.getX(), Obs.getY(), mass, 0xFFFFFFFF);
}

Vector2D Walker::GetHidingPosition(const Vector2D& posObstacle, const double radiusObstacle, const Vector2D& posHunter)
{
	const double DistanceFromBoundary = 30.0;
	double DistAway = mass + DistanceFromBoundary;
	
	Vector2D ToOb = Vector2D((posObstacle - posHunter).getX(),(posObstacle-posHunter).getY());
	ToOb.normalize();

	return (ToOb * DistAway) + posObstacle;
}

Vector2D Walker::GetHiderPosition()
{
	Vector2D hideSpot = GetHidingPosition(Obs, mass, hunterLocation);
	hiderLocation -= hideSpot;
	hiderLocation *= (-0.02);
	hiderLocation.normalize();
	
	return hiderLocation;
}

Vector2D& Walker::hide()
{
	Vector2D a = GetHiderPosition();
	return a;
}

//hidingspot = obs-hunterlocation+radius+30;
//hider = hidingspot - Hiderlocation
