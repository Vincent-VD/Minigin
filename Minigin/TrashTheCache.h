#pragma once
#include <iostream>
#include <vector>
#include <chrono>

struct TransformMat
{
	float matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
};

class GameObject3D
{
public:
	TransformMat transform;
	int ID;
};

class GameObject3DAlt
{
public:
	TransformMat* transform;
	int ID;
};

class TrashTheCache
{
public:
	TrashTheCache() = default;
	~TrashTheCache() = default;

	std::vector<float> Exercise1(int samples);
	std::vector<float> Exercise2(int samples);
	std::vector<float> Exercise3(int samples);
};