#include "circle.hpp"

#include <math.h>

Circle::Circle(sf::Vector2f pos, size_t radius, size_t line_length, Orientation orientation, float rotation_speed)
	: _line {sf::Vector2f{line_length, 1}}
	, _rotation_speed {rotation_speed}
{
	_main_circle.setRadius(radius);
	_main_circle.setOrigin(radius, radius);
	_main_circle.setOutlineColor(sf::Color::White);
	_main_circle.setFillColor(sf::Color::Black);
	_main_circle.setOutlineThickness(1);
	_main_circle.setPosition(pos);

	_orbit_circle.setRadius(radius / 2.5);
	_orbit_circle.setOutlineColor(sf::Color::White);
	_orbit_circle.setFillColor(sf::Color::White);
	_orbit_circle.setOutlineThickness(1);
	_orbit_circle.setOrigin(_orbit_circle.getRadius(), _orbit_circle.getRadius());

	_line.setFillColor(sf::Color{50, 50, 50});
	if(orientation == Orientation::Vertical)
		_line.rotate(90);

	updatePositions(0);
}

void Circle::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(_main_circle, states);
	target.draw(_orbit_circle, states);
	target.draw(_line, states);
}

void Circle::updatePositions(float angle)
{
	const auto& main_pos = _main_circle.getPosition();
	const auto radius = _main_circle.getRadius();
	auto x = main_pos.x + radius * std::sin(angle);
	auto y = main_pos.y + radius * std::cos(angle);

	_orbit_circle.setPosition(x, y);

	const auto& orbit_pos = _orbit_circle.getPosition();
	_line.setPosition(orbit_pos.x, orbit_pos.y);
}

void Circle::update(const sf::Time& time)
{
	_angle += _rotation_speed * time.asMilliseconds();
	if(_angle > 360)
		_angle -= 360;

	updatePositions(_angle);
}
