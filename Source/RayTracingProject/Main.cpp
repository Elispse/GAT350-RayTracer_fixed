#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include <iostream>
#include "Sphere.h"

int main(int args, char* argv[])
{
	std::cout << "Hello, World!";
	seedRandom((unsigned int)time(nullptr));

	// create renderer
	Renderer renderer = Renderer();
	// initialize renderer
	renderer.Initialize();
	// create renderer window with size of 400, 300
	renderer.CreateWindow("Ray tracer", 400, 300);
	

	Canvas canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene(20);
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = (std::rand() and %to randomly pick the material) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(random(glm::vec3{ -10,-10,-10 }, glm::vec3{ 8,8,-1 }), 1, material);
		scene.AddObject(std::move(sphere));
	}

	bool quit = false;
	while (!quit) 
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}
		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas, 50);
		canvas.Update();
		bool quit = false;
		while (!quit)
		{
			renderer.PresentCanvas(canvas);
		}
	}
	// shutdown renderer
	renderer.Shutdown();

	return 0;
}