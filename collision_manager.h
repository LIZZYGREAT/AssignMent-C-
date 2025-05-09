#pragma once

#include"collision_box.h"
#include<vector>

class CollisionManager {
public:

	static CollisionManager* instance();

private:
	CollisionBox* attack1_box = nullptr;
	CollisionBox* attack2_box = nullptr;
	CollisionBox* attack3_box = nullptr;


	CollisionBox* enemy_attack1_box = nullptr;
	CollisionBox* enemy_attack2_box = nullptr;
	CollisionBox* enemy_attack3_box = nullptr;
	CollisionBox* enemy_attack4_box = nullptr;

	CollisionBox* enemy_attack_up_box = nullptr;
	CollisionBox* enemy_attack_down_box = nullptr;

	CollisionBox* enemy_attack3_vfx_box = nullptr;
	CollisionBox* enemy_attack4_vfx_box = nullptr;

	CollisionBox* enemy_attack_shift_box = nullptr;
	CollisionBox* enemy_attack_up_2_box = nullptr;

public:

	CollisionBox* get_attack1_box() {
		return attack1_box;
	}
	CollisionBox* get_attack2_box() {
		return attack2_box;
	}
	CollisionBox* get_attack3_box() {
		return attack3_box;
	}


	CollisionBox* get_enemy_attack1_box() {
		return enemy_attack1_box;
	}
	CollisionBox* get_enemy_attack2_box() {
		return enemy_attack2_box;
	}
	CollisionBox* get_enemy_attack3_box() {
		return enemy_attack3_box;
	}
	CollisionBox* get_enemy_attack4_box() {
		return enemy_attack4_box;
	}
	CollisionBox* get_enemy_attack3_vfx_box() {
		return enemy_attack3_vfx_box;
	}
	CollisionBox* get_enemy_attack4_vfx_box() {
		return enemy_attack4_vfx_box;
	}
	CollisionBox* get_enemy_attack_up_box() {
		return enemy_attack_up_box;
	}
	CollisionBox* get_enemy_attack_down_box() {
		return enemy_attack_down_box;
	}
	CollisionBox* get_enemy_attack_up_2_box() {
		return enemy_attack_up_2_box;
	}
	CollisionBox* get_enemy_attack_shift_box() {
		return enemy_attack_shift_box;
	}


	CollisionBox* create_collision_box();

	void destroy_collision_box(CollisionBox* collision_box);

	void process_collide();
	void on_debug_render();
private:
	static CollisionManager* manager;

	std::vector<CollisionBox*>collision_box_list;

public:
	CollisionManager();
	~CollisionManager();
};