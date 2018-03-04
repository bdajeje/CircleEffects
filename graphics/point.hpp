#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics/CircleShape.hpp>

#include <graphics/drawable.hpp>

class Point final : public Drawable
{
	public:

		Point(sf::Vector2f pos, size_t life_time, sf::Color init_color);

		virtual void update(const sf::Time& time) override;

		bool isFinished() const noexcept { return _remaining_life_time <= 0; }

	protected:

		virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

	protected:

		sf::CircleShape _shape;
		const int _total_life_time {0};
		int _remaining_life_time {0};
		const sf::Color _init_color;
};

using PointSP = std::shared_ptr<Point>;

#endif // POINT_HPP
