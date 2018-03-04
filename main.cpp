#include <iostream>
#include <list>

#include <SFML/Graphics.hpp>

#include <graphics/drawable.hpp>
#include <graphics/circle.hpp>
#include <graphics/point.hpp>
#include "utils/timer.hpp"

constexpr size_t CIRCLE_RADIUS = 30;
constexpr size_t STARTING_X = 50;
constexpr size_t STARTING_Y = 50;
constexpr float ROTATION_SPEED = 0.002;
constexpr float ROTATION_SPEED_GROW = 0.001;
constexpr size_t POINTS_CREATION_TIME = 35; // in ms
constexpr size_t POINT_LIFE_TIME = 2000; // in ms

int main()
{
	// Set anti aliasing
	sf::ContextSettings context;
//    context.antialiasingLevel = 8;

	// Create window
	sf::RenderWindow window ({1000, 1000}, "Circle Effects", sf::Style::Default, context);
	window.setFramerateLimit(60);

	constexpr size_t NBR_CIRCLES {5};
	const sf::Color background_color {0, 0, 0};
	utils::time::Timer timer;

	std::vector<CircleSP> h_circles;
	std::vector<CircleSP> v_circles;
	std::list<PointSP> points;
	h_circles.reserve(NBR_CIRCLES);
	v_circles.reserve(NBR_CIRCLES);

	// Horizontal circles
	size_t padding = (window.getSize().x - STARTING_X) / (NBR_CIRCLES + 1);
	float x = STARTING_X;
	float y = STARTING_Y;
	size_t line_length = window.getSize().x - STARTING_X;
	for(size_t i = 0; i < NBR_CIRCLES; ++i)
	{
		x += padding;
		CircleSP circle = std::make_shared<Circle>(sf::Vector2f{x, y}, CIRCLE_RADIUS, line_length, Circle::Orientation::Vertical, ROTATION_SPEED + i * ROTATION_SPEED_GROW);
		h_circles.emplace_back(circle);
	}

	// Vertical circles
	x = STARTING_X;
	y = STARTING_Y;
	line_length = window.getSize().y- STARTING_Y;
	for(size_t i = 0; i < NBR_CIRCLES; ++i)
	{
		y += padding;
		CircleSP circle = std::make_shared<Circle>(sf::Vector2f{x, y}, CIRCLE_RADIUS, line_length, Circle::Orientation::Horizontal, ROTATION_SPEED + i * ROTATION_SPEED_GROW);
		v_circles.emplace_back(circle);
	}

	// Main loop
	size_t time_since_points_creation {0};
	while(window.isOpen())
	{
		const sf::Time elapsed_time {timer.restart()};

		// Handle SFML events
		sf::Event event;
		while(window.pollEvent(event))
		{
			// Close program
			if( event.type == sf::Event::Closed )
				window.close();
		}

		// Update circles
		for(const auto& drawable : v_circles)
			drawable->update(elapsed_time);
		for(const auto& drawable : h_circles)
			drawable->update(elapsed_time);

		// Update points
		for(auto& point : points)
			point->update(elapsed_time);

		// Manage points
		time_since_points_creation += elapsed_time.asMilliseconds();
		if(time_since_points_creation >= POINTS_CREATION_TIME)
		{
			time_since_points_creation = 0;

			// Delete old points
			points.remove_if([] (const PointSP& point) {
				return point->isFinished();
			});

			// Create new points
			for(size_t i = 0; i < NBR_CIRCLES; ++i)
			{
				const CircleSP& circle_a = h_circles[i];

				sf::Color color;
				if(i % 2 == 0)
					color = sf::Color{255, 255, 255};
				else if(i % 3 == 0)
					color = sf::Color{255, 0, 255};
				else if(i % 5 == 0)
					color = sf::Color{255, 255, 0};
				else
					color = sf::Color{255, 125, 125};

				for(size_t j = 0; j < NBR_CIRCLES; ++j)
				{
					const CircleSP& circle_b = v_circles[j];
					PointSP point = std::make_shared<Point>(sf::Vector2f{circle_a->getLinePosX(), circle_b->getLinePosY()}, POINT_LIFE_TIME, color);
					points.emplace_back(point);
				}
			}
		}

		// Draw
		window.clear(background_color);
		for(const auto& drawable : v_circles)
			window.draw(*drawable);
		for(const auto& drawable : h_circles)
			window.draw(*drawable);
		for(const auto& point : points)
			window.draw(*point);
		window.display();
	}

	return EXIT_SUCCESS;
}
