#include <Window.h>
#include <iostream>

#include "Window.h"
#include "Scene1.h"
#include "Renderer.h"

const int screenWidth = 800;
const int screenHeight = 600;

Window* window;
Renderer* renderer;
Scene1* scene1;

void Destroy();

int main() {

	window = new Window(screenWidth, screenHeight, "Ray Tracer");
	scene1 = new Scene1(screenWidth, screenHeight);

	sf::Clock clock;

	while (window->IsOpen())
	{
		window->UpdatePollEvent();
		window->Clear();

		scene1->Run();
		renderer->Draw(scene1, window->GetPixels());
		window->Display();

		printf("Elapsed time: %f\n", clock.restart().asSeconds());
	}

	Destroy();

	return 0;
}

void Destroy() {
	delete window;
	delete renderer;
	delete scene1;
}