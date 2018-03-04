#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System.hpp>

class Drawable : public sf::Drawable
{
	public:

		Drawable() = default;
		virtual ~Drawable() = default;

		void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const noexcept override;
		virtual void update(const sf::Time& time) = 0;

		void hide() noexcept { _visible = false; }
		void show() noexcept { _visible = true; }
		bool isVisible() const noexcept { return _visible == true; }

	protected:

		virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept = 0;

	private:

		bool _visible {true};
};

using DrawableSP = std::shared_ptr<Drawable>;

#endif // DRAWABLE_HPP
