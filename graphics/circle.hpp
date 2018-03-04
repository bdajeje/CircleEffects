#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <SFML/Graphics.hpp>

#include <graphics/drawable.hpp>

class Circle final : public Drawable
{
	public:

		enum class Orientation { Horizontal, Vertical };

		Circle(sf::Vector2f pos, size_t radius, size_t line_length, Orientation orientation, float rotation_speed);

		virtual void update(const sf::Time& time) override;

		float getPosX() const noexcept { return _main_circle.getPosition().x; }
		float getPosY() const noexcept { return _main_circle.getPosition().y; }

		float getLinePosX() const noexcept { return _line.getPosition().x; }
		float getLinePosY() const noexcept { return _line.getPosition().y; }

	protected:

		virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
		void updatePositions(float degree);

	protected:

		sf::CircleShape _main_circle;
		sf::CircleShape _orbit_circle;
		sf::RectangleShape _line;

		// Angle grows in milliseconds
		float _rotation_speed {0};

		float _angle {0};
};

using CircleSP = std::shared_ptr<Circle>;

#endif // CIRCLE_HPP
