#include "point.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Point::Point(sf::Vector2f pos, size_t life_time, sf::Color init_color)
	: _total_life_time {life_time}
	, _remaining_life_time {life_time}
	, _init_color {std::move(init_color)}
{
	_shape.setPosition(pos);
	_shape.setFillColor(sf::Color::White);
	_shape.setRadius(2);
	_shape.setOrigin(_shape.getRadius(), _shape.getRadius());
}

void Point::update(const sf::Time& time)
{
	_remaining_life_time -= time.asMilliseconds();
	_shape.setFillColor(sf::Color{_init_color.r * (static_cast<float>(_remaining_life_time) / static_cast<float>(_total_life_time)), _init_color.g, _init_color.b});
}

void Point::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(_shape, states);
}
