#pragma once
#include <RootComponent.h>
#include <utility>

#include "GameObject.h"
#include "InputComponent.h"

struct Fvec2
{
	Fvec2();
	Fvec2(float x, float y);

	float x;
	float y;
};


class MovementComponent final : public cycle::RootComponent
{
public:
	MovementComponent(cycle::GameObject* owner, float moveSpeed = 1.f);
	virtual ~MovementComponent() override = default;
	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) noexcept = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) noexcept = delete;

	virtual void Update() override;
	virtual void FixedUpdate() override {}
	virtual void Render() const override;

	Fvec2 GetDir() const { return m_Dir; }

	void UpdateDir(const Fvec2& dir);

private:
	Fvec2 m_Dir;

	const float m_MoveSpeed;
	

};

class Move : public cycle::Command
{
public:
	Move(InputType type, const cycle::InputComponent* input, MovementComponent* movement)
		: Command(type, input), m_Movement(movement)
	{
	}

protected:
	MovementComponent* m_Movement;
};

class MoveUp final : public Move
{
public:
	MoveUp(InputType type, const cycle::InputComponent* input, MovementComponent* movement)
		: Move(type, input, movement)
	{
	}

	virtual void Execute() override
	{
		//std::cout << "up\n";
		m_Movement->UpdateDir(Fvec2{ 0, -1 });
	}
};

class MoveLeft final : public Move
{
public:
	MoveLeft(InputType type, const cycle::InputComponent* input, MovementComponent* movement)
		: Move(type, input, movement)
	{
	}

	virtual void Execute() override
	{
		//std::cout << "left\n";
		m_Movement->UpdateDir(Fvec2{ -1, 0 });
	}
};

class MoveDown final : public Move
{
public:
	MoveDown(InputType type, const cycle::InputComponent* input, MovementComponent* movement)
		: Move(type, input, movement)
	{
	}

	virtual void Execute() override
	{
		//std::cout << "down\n";
		m_Movement->UpdateDir(Fvec2{ 0, 1 });
	}
};

class MoveRight final : public Move
{
public:
	MoveRight(InputType type, const cycle::InputComponent* input, MovementComponent* movement)
		: Move(type, input, movement)
	{
	}

	virtual void Execute() override
	{
		//std::cout << "right\n";
		m_Movement->UpdateDir(Fvec2{ 1, 0 });
	}
};

class MoveStick final : public Move
{
public:
	MoveStick(InputType type, const cycle::InputComponent* input, MovementComponent* movement)
		: Move(type, input, movement)
	{
	}

	virtual void Execute() override
	{
		//std::cout << "stick\n";
		const auto stick{ m_Input->GetLeftStickValues() };
		if(abs(stick.first) > abs(stick.second))
		{
			if(stick.first > 0.001f)
			{
				m_Movement->UpdateDir(Fvec2{ 1, 0 });
			}
			else
			{
				m_Movement->UpdateDir(Fvec2{ -1, 0 });
			}
		}
		else
		{
			if (stick.second > 0.001f)
			{
				m_Movement->UpdateDir(Fvec2{ 0, 1 });
			}
			else
			{
				m_Movement->UpdateDir(Fvec2{ 0, -1 });
			}
		}
		m_Movement->UpdateDir(Fvec2{ 0, 1 });
	}
};