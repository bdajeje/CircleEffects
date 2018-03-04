#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>

#include <SFML/System.hpp>

class Model
{
	public:

		Model();
		virtual ~Model();

		virtual void update(const sf::Time& time) = 0;
};

using ModelSP = std::shared_ptr<Model>;

#endif // MODEL_HPP
