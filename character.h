﻿#pragma once

#include"animation.h"
#include"state_machine.h"
#include"vector2.h"

#include"collision_box.h"

#include<string>
#include<graphics.h>
#include<unordered_map>

class Character {
protected:
	struct AnimationGroup
	{
		Animation left;
		Animation right;
	};
public:
	Character();
	~Character();

	int get_hp() const {
		return hp;
	}
	void set_is_character_visible(bool flag) {
		is_character_visible = flag;
	}
	bool get_is_character_visible()const {
		return is_character_visible;
	}
	void set_position(const vector2& position) {
		this->position = position;
	}
	const vector2& get_position()const {
		return position;
	}
	void set_velocity(const vector2& velocity) {
		this->velocity = velocity;
	}
	const vector2& get_velocity() const {
		return velocity;
	}
	vector2 get_logic_center() const {
		return vector2(position.x, position.y - logic_height / 2);//Ò»¶¨ÒªÖªµÀÊÇ-¶ø²»ÊÇ+ 1/2height
	}
	void set_gravity_enabled(bool flag) {
		enable_gravity = flag;
	}
	CollisionBox* get_hurt_box() {
		return hurt_box;
	}
	bool is_on_floor()const {
		return position.y >= Floor_y + 100;
	}
	float get_floor_y() const {
		return Floor_y;
	}
	void make_invulnerable() {
		is_invulnerable = true;
		timer_invulnerable_status.restart();
	}


	virtual void on_input(const ExMessage& msg);
	virtual void on_update(float delta);
	virtual void on_render();
	virtual void decrease_hp(int x);
	virtual void on_take_hit();
	void switch_state(const std::string& id);
	void set_animation(const std::string& id);



	AnimationGroup get_animation_group(const std::string& id) {
		return animation_pool[id];
	}

protected:
	const float Floor_y = 680;
	const float gravity = 980 * 1.4;
protected:
	int hp = 10;
	int max_hp = 100;
	vector2 position;
	vector2 velocity;

	float frame_size = 300;
	float logic_height = 0;
	bool is_facing_left = true;

	StateMachine state_machine;

	bool enable_gravity = true;
	bool is_invulnerable = false;
	bool is_character_visible = true;

	Timer timer_invulnerable_status;

	CollisionBox* hurt_box = nullptr;

	AnimationGroup* current_animation = nullptr;

	std::unordered_map<std::string, AnimationGroup> animation_pool;
};