#include "TrashTheCache.h"
#include "Renderer.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl2.h"

std::vector<float> TrashTheCache::Exercise1(int samples)
{
	std::vector<float> res{};
	std::vector<int> arr(samples);
	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		auto prevTime = std::chrono::high_resolution_clock::now();
		for (int iter = 0; iter < arr.size(); iter += stepSize)
		{
			arr[iter] *= 2;
		}
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto deltaT = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - prevTime).count();
		res.push_back(static_cast<float>(deltaT));
		//std::cout << stepSize << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - prevTime).count() << std::endl;
	}
	return res;
}

std::vector<float> TrashTheCache::Exercise2(int samples)
{
	std::vector<float> res{};
	std::vector<GameObject3D> arr(samples);
	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		auto prevTime = std::chrono::high_resolution_clock::now();
		for (int iter = 0; iter < arr.size(); iter += stepSize)
		{
			arr[iter].ID = stepSize * iter;
		}
		auto currentTime = std::chrono::high_resolution_clock::now();
		res.push_back(static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - prevTime).count()));
		//std::cout << stepSize << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - prevTime).count() << std::endl;
	}
	return res;
}

std::vector<float> TrashTheCache::Exercise3(int samples)
{
	std::vector<float> res{};
	std::vector<GameObject3DAlt> arr(samples);
	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		auto prevTime = std::chrono::high_resolution_clock::now();
		for (int iter = 0; iter < arr.size(); iter += stepSize)
		{
			arr[iter].ID = stepSize * iter;
		}
		auto currentTime = std::chrono::high_resolution_clock::now();
		res.push_back(static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - prevTime).count()));
		//std::cout << stepSize << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - prevTime).count() << std::endl;
	}
	return res;
}