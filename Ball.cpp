#include "Ball.h"
#include "Player.h"

bool Ball::isRandInitialized = false;


double Ball::randomizeAngle()
{
	if (!isRandInitialized) {
		srand(time(NULL));
		isRandInitialized = true;
	}


	return (((double)rand() / (double)RAND_MAX) * 60.0) - 30.0;
}

void Ball::setAngle(double angle)
{
	direction.x = sin(angle);
	direction.y = -cos(angle);
}

Ball::Ball(int x, int y, int radius, float speed)
{
	position.x = x;
	position.y = y;
	oldPosition = position;
	shape.setFillColor(sf::Color(sf::Color::White));
	this->radius = radius;
	shape.setRadius(radius);
	this->speed = speed;

	setAngle(randomizeAngle());

}

Ball::~Ball()
{
}

void Ball::move(float ellapsedTime)
{
	position += ellapsedTime * speed * direction;
}

void Ball::draw(sf::RenderWindow& window)
{
	shape.setPosition(position);
	window.draw(shape);
}

float Ball::getSpeed()
{
	return speed;
}

void Ball::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Ball::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	oldPosition = position;
}

sf::Vector2f Ball::getPosition()
{
	return position;
}

void Ball::setDirection(sf::Vector2f newDirection)
{
	direction = newDirection;
}

void Ball::update(float deltaTime, Player& player, sf::RenderWindow& window)
{
    position += direction * speed * deltaTime;
    shape.setPosition(position);

    manageCollisionWith(player, window);

    // Si la balle reste collée au joueur, réinitialise sa position
    if (collisionCount > 5) {
        position.y = player.getPosition().y - 2 * radius;
        collisionCount = 0;
    }
}

void Ball::manageCollisionWith(Player& player, sf::RenderWindow& window)
{
    float MAX_ANGLE = 45;
    const int MARGE = 2;

    // Vérifie si la balle touche le joueur
    if (position.y + 2 * radius >= player.getPosition().y &&
        position.y + 2 * radius <= player.getPosition().y + player.getSize().y &&
        position.x + 2 * radius >= player.getPosition().x &&
        position.x <= player.getPosition().x + player.getSize().x)
    {
        // Calcule la position relative de la balle par rapport au joueur
        double relativeIntersectX = position.x + radius - player.getPosition().x - player.getSize().x / 2.0;

        // Normalise la position relative de la balle
        double normalizedRelativeIntersectionX = relativeIntersectX / (player.getSize().x / 2.0);

        // Calcule l'angle de rebond de la balle
        double angle = normalizedRelativeIntersectionX * MAX_ANGLE;

        // Change la direction de la balle en fonction de l'angle de rebond
        setAngle(angle);

        // Déplace la balle en dehors du joueur
        position.y = player.getPosition().y - 2 * radius - 0.1f;
        direction.y = -std::abs(direction.y);
    }

    // Vérifie si la balle touche le bord supérieur de l'écran
    if (position.y <= 0)
    {
        // Inverse la direction sur l'axe y :
        direction.y = std::abs(direction.y);
    }

    // Vérifie si la balle touche le bord inférieur de l'écran
    if (position.y >= (window.getSize().y) - 2 * radius)
    {
        // Inverse la direction sur l'axe y :
        direction.y = -std::abs(direction.y);
    }

    // Vérifie si la balle touche le bord gauche de l'écran
    if (position.x <= 0)
    {
        // Inverse la direction sur l'axe x :
        direction.x = std::abs(direction.x);
    }

    // Vérifie si la balle touche le bord droit de l'écran
    if (position.x >= (window.getSize().x) - 2 * radius)
    {
        // Inverse la direction sur l'axe x :
        direction.x = -std::abs(direction.x);
    }
}