#pragma once

#include"vector2.h"
#include"collision_layer.h"
#include"timer.h"
#include<graphics.h>
#include<functional>

class CollisionManager;

class CollisionBox {

	friend class CollisionManager;
public:
	enum class  Stage {
		one, two, three, end,
	};
	enum class State {
		valid, invalid,
	};
protected:
	vector2 size;
	vector2 position;  //碰撞箱中心点所处位置
	bool enabled = true;
	std::function<void(int)>on_collide;
	CollisionLayer layer_src = CollisionLayer::None;    //src代表源 source
	CollisionLayer layer_dst = CollisionLayer::None;	//dst代表目的


	Timer timer_stage1_to_2;
	Timer timer_stage2_to_3;
	Timer timer_stage3_to_end;

	Stage stage = Stage::one;


	int damage = 0;

public:

	CollisionBox() = default;
	~CollisionBox() = default;
public:
	void set_enabled(bool flag) {
		enabled = flag;
	}
	bool get_enabled()const {
		return enabled;
	}
	void set_layer_src(CollisionLayer layer) {
		layer_src = layer;
	}
	void set_layer_dst(CollisionLayer layer) {
		layer_dst = layer;
	}
	void set_on_collide(std::function<void(int)> on_collide) {
		this->on_collide = on_collide;
	}
	void set_size(const vector2& size) {
		this->size = size;
	}
	const vector2& get_size()const {
		return size;
	}
	void set_position(const vector2& position) {
		this->position = position;
	}
	const vector2& get_position()const {
		return position;
	}

	void set_damage(int x) {
		damage = x;
	}
	int get_damage()const {
		return damage;
	}
	//新加接口

	void update_attack1_position(const vector2& position, bool is_facing_left) {
		int x = is_facing_left == 1 ? 1 : -1;
		if (stage == Stage::one) {
			set_position({ position.x + x * get_size().x / 2,position.y + 25.0f });
		}
		else if (stage == Stage::two) {
			set_position({ position.x - get_size().x / 2 * x,position.y });
		}
		else if (stage == Stage::three) {
			set_position({ position.x - get_size().x / 2 * x,position.y });
		}
	}
	void update_attack1_size() {
		if (stage == Stage::one) {
			set_size({ 80.0f,75.0f });
		}
		else if (stage == Stage::two) {
			set_size({ 110.0f,100.0f });
		}
		else if (stage == Stage::three) {
			set_size({ 110.0f,100.0f });
		}
	}

	void update_attack2_position(const vector2& position, bool is_facing_left) {
		int x = is_facing_left == 1 ? 1 : -1;
		if (stage == Stage::one) {
			set_position({ position.x - x * get_size().x / 2,position.y - get_size().y / 2 });
		}
		else if (stage == Stage::two) {
			set_position({ position.x - x * get_size().x / 2 ,position.y });
		}
		else if (stage == Stage::three) {
			set_position({ position.x + x * get_size().x / 2,position.y });
		}
	}
	void update_attack2_size() {
		if (stage == Stage::one) {
			set_size({ 50.0f,50.0f });
		}
		else if (stage == Stage::two) {
			set_size({ 100.0f,100.0f });
		}
		else if (stage == Stage::three) {
			set_size({ 100.0f,100.0f });
		}
	}


	void update_attack3_position(const vector2& position, bool is_facing_left) {
		int x = is_facing_left == 1 ? 1 : -1;
		if (stage == Stage::one) {
			set_position({ position.x + 20.0f * x ,position.y - get_size().y / 2 - 50 });
		}
		else if (stage == Stage::two) {
			set_position({ position.x - x * (-25 + get_size().x / 2) ,position.y - 40.0f });
		}
		else if (stage == Stage::three) {
			set_position({ position.x - x * (-25 + get_size().x / 2),position.y - 40.0f });
		}
	}
	void update_attack3_size() {
		if (stage == Stage::one) {
			set_size({ 160.0f,60.0f });
		}
		else if (stage == Stage::two) {
			set_size({ 140.0f,200.0f });
		}
		else if (stage == Stage::three) {
			set_size({ 140.0f,200.0f });
		}
	}


	void update_enemy_attack1_box_size() {
		if (stage == Stage::one) {
			set_size({ 0,0 });
		}
		else if (stage == Stage::two) {
			set_size({ 200,150 });
		}
		else {
			set_size({ 0,0 });
		}

	}
	void update_enemy_attack1_box_position(const vector2& position, bool is_facing_left) {
		int x = (is_facing_left == 1) ? 1 : -1;
		set_position({ position.x - x * (-35 + get_size().x / 2) ,position.y - 40.0f });
	}



	void update_enemy_attack2_box_size() {
		if (stage == Stage::one) {
			set_size({ 0,0 });
		}
		else if (stage == Stage::two) {
			set_size({ 200,150 });
		}
		else {
			set_size({ 0,0 });
		}
	}
	void update_enemy_attack2_box_position(const vector2& position, bool is_facing_left) {
		int x = (is_facing_left == 1) ? 1 : -1;
		set_position({ position.x - x * (-35 + get_size().x / 2) ,position.y - 40.0f });
	}



	void update_enemy_attack3_box_size() {
		if (stage == Stage::one) {
			set_size({ 0,0 });
		}
		else if (stage == Stage::two) {
			set_size({ 200,150 });
		}
		else {
			set_size({ 0,0 });
		}
	}
	void update_enemy_attack3_box_position(const vector2& position, bool is_facing_left) {
		int x = (is_facing_left == 1) ? 1 : -1;
		set_position({ position.x - x * (-45 + get_size().x / 2) ,position.y - 40.0f });
	}

	void update_enemy_attack4_box_size() {
		if (stage == Stage::one) {
			set_size({ 0,0 });
		}
		else if (stage == Stage::two) {
			set_size({ 200,150 });
		}
		else {
			set_size({ 0,0 });
		}
	}
	void update_enemy_attack4_box_position(const vector2& position, bool is_facing_left) {
		int x = (is_facing_left == 1) ? 1 : -1;
		set_position({ position.x - x * (-45 + get_size().x / 2) ,position.y - 40.0f });
	}

	void update_enemy_attack3_vfx_box_size() {
		if (stage == Stage::one) {
			set_size({ 128,128 });
		}
		else {
			set_size({ 0,0 });
		}
	}
	void update_enemy_attack3_vfx_box_position(const vector2& position, bool is_facing_left) {
		int x = (is_facing_left == 1) ? -1 : 1;
		float pos_x = position.x + 180.0f * x;
		float pos_y = position.y;
		if (pos_x + get_size().x / 2 >= getwidth()) {
			pos_x = getwidth() - get_size().x / 2;
		}
		else if (pos_x - get_size().x / 2 <= 0) {
			pos_x = get_size().x / 2;
		}

		set_position({ pos_x,pos_y });
	}

	void update_enemy_attack4_vfx_box_size() {
		if (stage == Stage::one) {
			set_size({ 128,128 });
		}
		else {
			set_size({ 0,0 });
		}
	}
	void update_enemy_attack4_vfx_box_position(const vector2& position, bool is_facing_left) {
		int x = (is_facing_left == 1) ? -1 : 1;
		float pos_x = position.x + 180.0f * x;
		float pos_y = position.y;
		if (pos_x + get_size().x / 2 >= getwidth()) {
			pos_x = getwidth() - get_size().x / 2;
		}
		else if (pos_x - get_size().x / 2 <= 0) {
			pos_x = get_size().x / 2;
		}

		set_position({ pos_x,pos_y });
	}


	void update_enemy_attack_up_box_position(const vector2& position) {
		set_position(position + vector2{ 0,-50 });
	}

	void update_enemy_attack_up_box_size() {
		set_size(vector2{ 150,150 });
	}

	void update_enemy_attack_down_box_position(const vector2& position) {
		set_position(position + vector2{ 0,50 });
	}

	void update_enemy_attack_down_box_size() {
		set_size(vector2{ 150,150 });
	}


	void update_enemy_attack_up_2_box_position(const vector2& position) {
		set_position(position+vector2{0,-60.0f});
	}

	void update_enemy_attack_up_2_box_size() {
		set_size(vector2{ 160,160 });
	}


	void update_enemy_attack_shift_box_size() {
		set_size({ 150,150 });
	}
	void update_enemy_attack_shift_box_position(const vector2& position, bool is_facing_left) {
		int x = (is_facing_left == 1) ? 1 : -1;
		set_position({ position.x - x * (-60 + get_size().x / 2) ,position.y-30 });
	}


	Timer* get_timer_stage1_to_2() {
		return &timer_stage1_to_2;
	}

	Timer* get_timer_stage2_to_3() {
		return &timer_stage2_to_3;
	}

	Timer* get_timer_stage3_to_end() {
		return &timer_stage3_to_end;
	}


	const Stage& get_stage() const {
		return stage;
	}
	void set_stage(Stage stage) {
		this->stage = stage;
	}


	void on_debug_render() const {
		setlinecolor(enabled ? RGB(255, 195, 195) : RGB(115, 115, 175));
		rectangle((int)(position.x - size.x / 2),
			(int)(position.y - size.y / 2),
			(int)(position.x + size.x / 2),
			(int)(position.y + size.y / 2));
	}
};


