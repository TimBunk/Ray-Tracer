#pragma once

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window(unsigned int screenWidth, unsigned int screenHeight, const char* title);
	~Window();

	bool IsOpen() const;
	void Clear();
	// The pixels are read from left to right and from top to bottom
	void Display();
	void UpdatePollEvent();
	void CloseWindow();

	unsigned int const& GetScreenWidth() const;
	unsigned int const& GetScreenHeight() const;
	sf::Uint8* GetPixels() const;

	void SetScreenWidth(unsigned int const& screenWidth);
	void SetScreenHeight(unsigned int const& screenHeight);

private:
	unsigned int m_screenWidth, m_screenHeight;
	sf::Uint8* pixels;
	sf::RenderWindow m_window;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};