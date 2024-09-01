#ifndef ENEMY_SCRIPTS_H__
#define ENEMY_SCRIPTS_H__

#include <ai/Script.h>
#include <SFML/Graphics/Sprite.hpp>
#include <core/rec.h>
namespace Enemy_Script
{
	class MoveRight : public Script
	{

		rec& spr;
		float speed;
		float duration;
		float displacement;
		float dt;
	public:
		MoveRight() = delete;
		MoveRight(rec& l_spr, float l_speed, float l_duration);
		~MoveRight() override;
		void execute() override;
		void update() override;
		void render() override;
		bool isDone() override;
	};

	class MoveLeft : public Script
	{
		rec& spr;
		float speed;
		float duration;
		float displacement;
		float dt;
	public:
		MoveLeft() = delete;
		MoveLeft(rec& l_spr, float l_speed, float l_duration);
		~MoveLeft() override;
		void execute() override;
		void update() override;
		void render() override;
		bool isDone() override;
	};

	class MoveUp : public Script
	{
		rec& spr;
		float speed;
		float duration;
		float displacement;
		float dt;
	public:
		MoveUp() = delete;
		MoveUp(rec& l_spr, float l_speed, float l_duration);
		~MoveUp() override;
		void execute() override;
		void update() override;
		void render() override;
		bool isDone() override;
	};

	class MoveDown : public Script
	{
		rec& spr;
		float speed;
		float duration;
		float displacement;
		float dt;
	public:
		MoveDown() = delete;
		MoveDown(rec& l_spr, float l_speed, float l_duration);
		~MoveDown() override;
		void execute() override;
		void update() override;
		void render() override;
		bool isDone() override;
	};

	class MoveUpRight : public Script
	{
		rec& spr;
		float speed;
		float duration;
		float displacement;
		float dt;
	public:
		MoveUpRight() = delete;
		MoveUpRight(rec& l_spr, float l_speed, float l_duration);
		~MoveUpRight() override;
		void execute() override;
		void update() override;
		void render() override;
		bool isDone() override;
	};

	class MoveUpLeft : public Script
	{
		rec& spr;
		float speed;
		float duration;
		float displacement;
		float dt;
	public:
		MoveUpLeft() = delete;
		MoveUpLeft(rec& l_spr, float l_speed, float l_duration);
		~MoveUpLeft() override;
		void execute() override;
		void update() override;
		void render() override;
		bool isDone() override;
	};

	class MoveDownLeft : public Script
	{
		rec& spr;
		float speed;
		float duration;
		float displacement;
		float dt;
	public:
		MoveDownLeft() = delete;
		MoveDownLeft(rec& l_spr, float l_speed, float l_duration);
		~MoveDownLeft() override;
		void execute() override;
		void update() override;
		void render() override;
		bool isDone() override;
	};

	class MoveDownRight : public Script
	{
		rec& spr;
		float speed;
		float duration;
		float displacement;
		float dt;
	public:
		MoveDownRight() = delete;
		MoveDownRight(rec& l_spr, float l_speed, float l_duration);
		~MoveDownRight() override;
		void execute() override;
		void update() override;
		void render() override;
		bool isDone() override;
	};

	class MoveTo : public Script
	{
		rec& from;
		rec& to;
		float speed;
		float duration;
		float displacement;
		float dt;
	public:
		MoveTo() = delete;
		MoveTo(rec& from_, rec& to_, float l_speed, float l_duration);
		~MoveTo() override;
		void execute() override;
		void update() override;
		void render() override;
		bool isDone() override;
	};
}

#endif

