#pragma once
#include"character.h"
#include"collision_manager.h"

class Enemy : public Character {

protected:
	Timer timer_attack1_cd;
	bool is_attack1 = false;
	bool is_attack1_cd_cmp = true;

	Timer timer_attack2_cd;
	bool is_attack2 = false;
	bool is_attack2_cd_cmp = true;

	Timer timer_attack3_cd;
	bool is_attack3 = false;
	bool is_attack3_cd_cmp = true;

	Timer timer_attack4_cd;
	bool is_attack4 = false;
	bool is_attack4_cd_cmp = true;

	Timer timer_attack_up_cd;
	bool is_attack_up = false;
	bool is_attack_up_cd_cmp = true;

	Timer timer_attack_down_cd;
	bool is_attack_down = false;
	bool is_attack_down_cd_cmp = true;

	Timer timer_attack_up_2_cd;
	bool is_attack_up_2 = false;
	bool is_attack_up_2_cd_cmp = true;

	Timer timer_attack_shift_cd;
	bool is_attack_shift = false;
	bool is_attack_shift_cd_cmp = false;

	bool is_attack_up_2_vfx_visible = false;
	bool is_attack_shift_vfx_visible = false;
	bool is_attack_up_vfx_visible = false;
	bool is_attack_down_vfx_visible = false;

	bool is_attacking = false;

	bool is_jump_vfx_visible = false;
	Animation animation_jump_vfx;

	bool is_land_vfx_visible = false;
	Animation animation_land_vfx;

	bool is_attack3_vfx_visible = false;
	bool is_attack4_vfx_visible = false;

	Animation attack3_vfx;
	Animation attack4_vfx;

	Animation attack_up_vfx;
	Animation attack_down_vfx;

	Animation attack_up_2_vfx;
	Animation attack_shift_vfx_left;
	Animation attack_shift_vfx_right;
	Animation* current_attack_shift = nullptr;

	Animation smoke_vfx_left;
	Animation smoke_vfx_right;
	Animation* current_smoke = nullptr;

	Animation run_slash_vfx;

	Animation hit_vfx_left;
	Animation hit_vfx_right;
	Animation* current_hit = nullptr;

	bool is_run_slash_visible = false;
	bool is_smoke_vfx_visible = false;
	bool is_hit_vfx_visible = false;

	bool is_taking_hit = false;
	bool is_take_hit_cd_cmp = true;
	Timer timer_take_hit_cd;

	bool can_change_direction = true;


protected:
	const float CD_ATTACK = 0.80f;
	const float SPEED_RUN = 300.0f;
	const float SPEED_JUMP = 780.0f;
	const float SPEED_JUMP_RUN = 350.f;

public:

	Enemy();
	~Enemy();

	void on_input(const ExMessage& msg)override {}
	void on_update(float delta)override;
	void on_render()override;

	void on_take_hit()override;
	void decrease_hp(int x)override;

	Animation* get_attack3_vfx() {
		return &attack3_vfx;
	}
	Animation* get_attack4_vfx() {
		return &attack4_vfx;
	}
	Animation* get_current_attack_shift() {
		return current_attack_shift;
	}
	Animation* get_attack_up_2_vfx() {
		return &attack_up_2_vfx;
	}
	Animation* get_attack_down_vfx() {
		return &attack_down_vfx;
	}
	Animation* get_attack_up_vfx() {
		return &attack_up_vfx;
	}

	void set_is_facing_left(bool flag) {
		is_facing_left = flag;
	}

	void set_attacking(bool flag) {
		is_attacking = flag;
	}
	void set_attack1(bool flag) {
		is_attack1 = flag;
	}
	void set_attack2(bool flag) {
		is_attack2 = flag;
	}
	void set_attack3(bool flag) {
		is_attack3 = flag;
	}
	void set_attack4(bool flag) {
		is_attack4 = flag;
	}
	bool get_attacking()const {
		return  is_attacking;
	}
	void set_attack_down(bool flag) {
		is_attack_down = flag;
	}
	bool get_attack_down()const {
		return is_attack_down;
	}
	void set_attack_up(bool flag) {
		is_attack_up = flag;
	}
	bool get_attack_up()const {
		return is_attack_up;
	}
	void set_attack_up_2(bool flag) {
		is_attack_up_2 = flag;
	}
	bool get_attack_up_2()const {
		return is_attack_up_2;
	}
	void set_attack_shift(bool flag) {
		is_attack_shift = flag;
	}
	bool get_attack_shift()const {
		return is_attack_shift;
	}



	void set_taking_hit(bool flag) {
		is_taking_hit = flag;
	}
	bool get_is_taking_hit() const {
		return is_taking_hit;
	}

	void set_attack3_vfx_visible(bool flag) {
		is_attack3_vfx_visible = flag;
	}
	void set_attack4_vfx_visible(bool flag) {
		is_attack4_vfx_visible = flag;
	}

	bool get_attack3_vfx_visible() const {
		return is_attack3_vfx_visible;
	}
	bool get_attack4_vfx_visible() const {
		return is_attack4_vfx_visible;
	}

	void set_attack_shift_visible(bool flag) {
		is_attack_shift_vfx_visible = flag;
	}

	bool can_attack1() const {  //注意实时更新is_attacking
		return !is_attacking && is_attack1_cd_cmp;
	}
	bool can_attack2() const {
		return !is_attacking && is_attack2_cd_cmp;
	}
	bool can_attack3()const {
		return !is_attacking && is_attack3_cd_cmp;
	}
	bool can_attack4()const {
		return !is_attacking && is_attack4_cd_cmp;
	}
	bool can_attack_down()const {
		return !is_attacking && is_attack_down_cd_cmp;
	}
	bool can_attack_up()const {
		return !is_attacking && is_attack_up_cd_cmp;
	}
	bool can_attack_shift()const {
		return !is_attacking && is_attack_shift_cd_cmp;
	}
	bool can_attack_up_2() const{
		return !is_attacking && is_attack_up_2_cd_cmp;
	}


	bool can_changeDirection()const {
		return can_change_direction;
	}
	void set_changeDirection(bool flag) {
		can_change_direction = flag;
	}

	bool can_jump()const {
		return is_on_floor();
	}
	bool get_is_facing_left() {
		return is_facing_left;
	}

	void on_jump();
	void on_land();
	void on_run();
	void on_attack1();
	void on_attack2();
	void on_attack3();
	void on_attack4();
	void on_attack_up();
	void on_attack_down();
	void on_attack_up_2();
	void on_attack_shift();
	void on_shift();
	void on_smoke();
	void draw_hp();

};