#include "Brick.h"

Brick::Brick(int x, int y, int width, int height, int health) :
    position(sf::Vector2f(x, y)), size(sf::Vector2f(width, height)), health(health)
{
    // Cr�ation de la forme rectangulaire repr�sentant la brique
    shape = sf::RectangleShape(size);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
    shape.setPosition(position);
    shape.setFillColor(getColorFromLife());
}

Brick::~Brick()
{
    // Rien � faire dans le destructeur
}

void Brick::draw(sf::RenderWindow& window)
{
    // Dessine la brique si celle-ci est "en vie"
    if (isAlive()) {
        window.draw(shape);
    }
}

sf::Color Brick::getColorFromLife()
{
    // Renvoie la couleur de la brique en fonction de son �tat de sant�
    switch (health) {
    case 1:
        return sf::Color::Red;
    case 2:
        return sf::Color::Yellow;
    case 3:
        return sf::Color::Green;
    default:
        return sf::Color::White;
    }
}

bool Brick::isAlive()
{
    // Renvoie true si health est sup�rieur � 0, false sinon
    return health > 0;
}

void Brick::hit()
{
    // M�thode � appeler lorsque la brique est touch�e
    // D�cr�mente l'attribut health de 1
    health--;
    shape.setFillColor(getColorFromLife());
}

sf::Vector2f Brick::getPosition()
{
    // Accesseur de l'attribut position
    return position;
}

sf::Vector2f Brick::getSize()
{
    // Accesseur de l'attribut size
    return size;
}

sf::RectangleShape Brick::getShape()
{
    // Renvoyer la forme de la brique
    return shape;
}

void Brick::destroyAndDelete(std::deque<Brick*>& bricks)
{
    // Retirer la brique de la deque de briques
    bricks.erase(std::remove(bricks.begin(), bricks.end(), this), bricks.end());
    // Supprimer l'objet de la m�moire
    delete this;
}