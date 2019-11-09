#include "Window.h"

Window::Window(unsigned int screenWidth, unsigned int screenHeight, const char* title)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	pixels = new sf::Uint8[screenWidth * screenHeight * 4];
	m_window.create(sf::VideoMode(screenWidth, screenHeight), title);
	m_texture.create(m_screenWidth, m_screenHeight);
	m_sprite.setTexture(m_texture);
}

Window::~Window()
{
	CloseWindow();
	delete pixels;
}

bool Window::IsOpen() const
{
	return m_window.isOpen();
}

void Window::Clear()
{
	m_window.clear();
}

void Window::Display()
{
	m_texture.update(pixels);
	m_window.draw(m_sprite);
	m_window.display();
}

void Window::UpdatePollEvent()
{
	// Process events
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		// Close window: exit
		if (event.type == sf::Event::Closed) {
			CloseWindow();
		}
	}
}

void Window::CloseWindow()
{
	m_window.close();
}

unsigned int const & Window::GetScreenWidth() const
{
	return m_screenWidth;
}

unsigned int const & Window::GetScreenHeight() const
{
	return m_screenHeight;
}

sf::Uint8 * Window::GetPixels() const
{
	return pixels;
}

void Window::SetScreenWidth(unsigned int const & screenWidth)
{
	m_screenWidth = screenWidth;
}

void Window::SetScreenHeight(unsigned int const & screenHeight)
{
	m_screenHeight = screenHeight;
}
