#include"enemy.h"
#include"player.h"
#include"character_manager.h"
#include"enemy_state_nodes.h"
#include"collision_manager.h"

EnemyAttack1State::EnemyAttack1State() {
	timer.set_wait_time(0.40f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_attack1(false);
		enemy->set_attacking(false);
		enemy->set_changeDirection(true);
		});
}

void EnemyAttack1State::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_attack1");

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->set_changeDirection(false);


	enemy->set_attack1(true);
	enemy->set_attacking(true);
	enemy->on_attack1();
	CollisionBox* box = CollisionManager::instance()->get_enemy_attack1_box();

	box->set_enabled(true);
	box->set_stage(CollisionBox::Stage::one);

	timer.restart();
	box->get_timer_stage1_to_2()->restart();
	box->get_timer_stage2_to_3()->restart();

	switch (range_random(1, 3)) {
	case 1:
		play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		play_audio(_T("player_attack_3"), false);
		break;
	}
}

void EnemyAttack1State::on_update(float delta) {
	timer.on_update(delta);

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);
	enemy->set_velocity({ (pos_enemy.x < pos_player.x ? attack_speed : -attack_speed) * (max(min(d / attack_dis,1),0.5f)),0 });

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack1_box();

	box->update_enemy_attack1_box_size();
	box->update_enemy_attack1_box_position(enemy->get_logic_center(), enemy->get_is_facing_left());

	box->get_timer_stage1_to_2()->on_update(delta);

	if (box->get_stage() == CollisionBox::Stage::two)
		box->get_timer_stage2_to_3()->on_update(delta);


	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	else if (!enemy->get_attacking()) {
		if (enemy->get_velocity().y > 0) {
			enemy->switch_state("enemy_fall");
		}
		else if (enemy->is_on_floor()) {
			enemy->switch_state("enemy_idle");
		}
	}

}
void EnemyAttack1State::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();


	enemy->set_attack1(false);
	enemy->set_attacking(false);
	enemy->set_velocity({ 0, enemy->get_velocity().y });
}

EnemyAttack2State::EnemyAttack2State() {
	timer.set_wait_time(0.40f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_attack2(false);
		enemy->set_attacking(false);
		enemy->set_changeDirection(true);
		});

}

void EnemyAttack2State::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_attack2");

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->set_changeDirection(false);

	enemy->set_attack2(true);
	enemy->set_attacking(true);
	enemy->on_attack2();

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack2_box();

	box->set_enabled(true);
	box->set_stage(CollisionBox::Stage::one);

	timer.restart();

	box->get_timer_stage1_to_2()->restart();
	box->get_timer_stage2_to_3()->restart();

	switch (range_random(1, 3)) {
	case 1:
		play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		play_audio(_T("player_attack_3"), false);
		break;
	}
}

void EnemyAttack2State::on_update(float delta) {
	timer.on_update(delta);

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);
	enemy->set_velocity({ (pos_enemy.x < pos_player.x ? attack_speed : -attack_speed) * (max(min(d / attack_dis,1),0.5f)),0 });


	CollisionBox* box = CollisionManager::instance()->get_enemy_attack2_box();

	box->update_enemy_attack2_box_size();
	box->update_enemy_attack2_box_position(enemy->get_logic_center(), enemy->get_is_facing_left());


	box->get_timer_stage1_to_2()->on_update(delta);

	if (box->get_stage() == CollisionBox::Stage::two)
		box->get_timer_stage2_to_3()->on_update(delta);

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	else if (!enemy->get_attacking()) {
		if (enemy->get_velocity().y > 0) {
			enemy->switch_state("enemy_fall");
		}
		else if (enemy->is_on_floor()) {
			enemy->switch_state("enemy_idle");
		}
	}

}
void EnemyAttack2State::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->set_attack2(false);
	enemy->set_attacking(false);

	enemy->set_velocity({ 0, enemy->get_velocity().y });

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack2_box();

	box->set_enabled(false);

}


EnemyAttack3State::EnemyAttack3State() {
	timer1.set_wait_time(0.50f);
	timer1.set_one_shot(true);
	timer1.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_attack3(false);
		enemy->set_attacking(false);
		enemy->set_changeDirection(true);

		enemy->set_attack3_vfx_visible(true);

		CollisionBox* vfx_box = CollisionManager::instance()->get_enemy_attack3_vfx_box();

		vfx_box->update_enemy_attack3_vfx_box_position(enemy->get_logic_center(), enemy->get_is_facing_left());
		vfx_box->update_enemy_attack3_vfx_box_size();

		enemy->get_attack3_vfx()->set_position(vfx_box->get_position() + vector2{ 0,64 });

		});

}

void EnemyAttack3State::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_attack3");

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	CollisionBox* box = CollisionManager::instance()->get_enemy_attack3_box();
	CollisionBox* vfx_box = CollisionManager::instance()->get_enemy_attack3_vfx_box();

	enemy->set_changeDirection(false);
	enemy->set_attack3(true);
	enemy->set_attacking(true);
	enemy->on_attack3();

	box->set_enabled(true);
	vfx_box->set_enabled(true);
	box->set_stage(CollisionBox::Stage::one);
	vfx_box->set_stage(CollisionBox::Stage::one);

	timer1.restart();
	vfx_box->get_timer_stage1_to_2()->restart();
	box->get_timer_stage1_to_2()->restart();
	box->get_timer_stage2_to_3()->restart();


	switch (range_random(1, 3)) {
	case 1:
		play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		play_audio(_T("player_attack_3"), false);
		break;
	}

	if (range_random(1, 8) <= 2) {
		play_audio(_T("dange"), false);
	}
}

void EnemyAttack3State::on_update(float delta) {
	timer1.on_update(delta);

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	CollisionBox* box = CollisionManager::instance()->get_enemy_attack3_box();
	CollisionBox* vfx_box = CollisionManager::instance()->get_enemy_attack3_vfx_box();

	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);
	enemy->set_velocity({ (pos_enemy.x < pos_player.x ? attack_speed : -attack_speed) * (max(min(d / attack_dis,1),0.5f)),0 });

	box->update_enemy_attack3_box_size();
	box->update_enemy_attack3_box_position(enemy->get_logic_center(), enemy->get_is_facing_left());

	box->get_timer_stage1_to_2()->on_update(delta);

	if (box->get_stage() == CollisionBox::Stage::two)
		box->get_timer_stage2_to_3()->on_update(delta);

	if (enemy->get_attack3_vfx_visible())
		vfx_box->get_timer_stage1_to_2()->on_update(delta);

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	else if (!enemy->get_attacking()) {
		if (enemy->get_velocity().y > 0) {
			enemy->switch_state("enemy_fall");
		}
		else if (enemy->is_on_floor()) {
			enemy->switch_state("enemy_idle");
		}
	}
}
void EnemyAttack3State::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->set_attack3(false);
	enemy->set_attacking(false);

	enemy->set_velocity({ 0, enemy->get_velocity().y });

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack3_box();
	CollisionBox* vfx_box = CollisionManager::instance()->get_enemy_attack3_vfx_box();

	box->set_enabled(false);
	vfx_box->set_enabled(false);
}

EnemyAttack4State::EnemyAttack4State() {
	timer1.set_wait_time(0.50f);
	timer1.set_one_shot(true);
	timer1.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_attack4(false);
		enemy->set_attacking(false);
		enemy->set_changeDirection(true);
		enemy->set_attack4_vfx_visible(true);

		CollisionBox* vfx_box = CollisionManager::instance()->get_enemy_attack4_vfx_box();
		vfx_box->update_enemy_attack4_vfx_box_position(enemy->get_logic_center(), enemy->get_is_facing_left());
		vfx_box->update_enemy_attack4_vfx_box_size();

		enemy->get_attack4_vfx()->set_position(vfx_box->get_position() + vector2{ 0,64 });

		});

}

void EnemyAttack4State::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_attack4");

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	CollisionBox* box = CollisionManager::instance()->get_enemy_attack4_box();
	CollisionBox* vfx_box = CollisionManager::instance()->get_enemy_attack4_vfx_box();

	enemy->set_changeDirection(false);
	enemy->set_attack4(true);
	enemy->set_attacking(true);
	enemy->on_attack4();

	box->set_enabled(true);
	vfx_box->set_enabled(true);
	box->set_stage(CollisionBox::Stage::one);
	vfx_box->set_stage(CollisionBox::Stage::one);


	timer1.restart();
	vfx_box->get_timer_stage1_to_2()->restart();
	box->get_timer_stage1_to_2()->restart();
	box->get_timer_stage2_to_3()->restart();


	switch (range_random(1, 3)) {
	case 1:
		play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		play_audio(_T("player_attack_3"), false);
		break;
	}

	if (range_random(1, 8) <= 2) {
		play_audio(_T("dange"), false);
	}
}

void EnemyAttack4State::on_update(float delta) {
	timer1.on_update(delta);

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack4_box();
	CollisionBox* vfx_box = CollisionManager::instance()->get_enemy_attack4_vfx_box();

	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);
	enemy->set_velocity({ (pos_enemy.x < pos_player.x ? attack_speed : -attack_speed) * (max(min(d / attack_dis,1),0.5f)),0 });

	box->update_enemy_attack4_box_size();
	box->update_enemy_attack4_box_position(enemy->get_logic_center(), enemy->get_is_facing_left());
	box->get_timer_stage1_to_2()->on_update(delta);


	if (box->get_stage() == CollisionBox::Stage::two)
		box->get_timer_stage2_to_3()->on_update(delta);

	if (enemy->get_attack4_vfx_visible())
		vfx_box->get_timer_stage1_to_2()->on_update(delta);


	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	else if (!enemy->get_attacking()) {
		if (enemy->get_velocity().y > 0) {
			enemy->switch_state("enemy_fall");
		}
		else if (enemy->is_on_floor()) {
			enemy->switch_state("enemy_idle");
		}
	}
}
void EnemyAttack4State::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	CollisionBox* box = CollisionManager::instance()->get_enemy_attack4_box();
	CollisionBox* vfx_box = CollisionManager::instance()->get_enemy_attack4_vfx_box();
	enemy->set_attack4(false);
	enemy->set_attacking(false);

	enemy->set_velocity({ 0, enemy->get_velocity().y });

	box->set_enabled(false);
	vfx_box->set_enabled(false);
}



EnemyAttackDownState::EnemyAttackDownState() {
	timer.set_wait_time(0.40f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_attack_down(false);
		enemy->set_attacking(false);
		enemy->set_changeDirection(true);
		});
}

void EnemyAttackDownState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_attack_down");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	std::cout << "enter_attack down" << std::endl;


	enemy->set_changeDirection(false);
	enemy->set_attack_down(true);
	enemy->set_attacking(true);
	enemy->on_attack_down();

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_down_box();

	enemy->get_attack_down_vfx()->set_position(enemy->get_position() + vector2{ 0,-50 });

	box->update_enemy_attack_down_box_size();
	box->update_enemy_attack_down_box_position(enemy->get_logic_center());
	box->set_enabled(true);

	timer.restart();

	switch (range_random(1, 3)) {
	case 1:
		play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		play_audio(_T("player_attack_3"), false);
		break;
	}
}

void EnemyAttackDownState::on_update(float delta) {
	timer.on_update(delta);

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_down_box();

	box->update_enemy_attack_down_box_size();
	box->update_enemy_attack_down_box_position(enemy->get_logic_center());
	enemy->get_attack_down_vfx()->set_position(enemy->get_position() + vector2{ 0,-50 });

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	else if (!enemy->get_attacking()) {
		if (enemy->get_velocity().y > 0) {
			enemy->switch_state("enemy_fall");
		}
		else {
			enemy->switch_state("enemy_idle");
		}
	}


}
void EnemyAttackDownState::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->set_attack_down(false);
	enemy->set_attacking(false);
	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_down_box();
	enemy->set_velocity({ 0, enemy->get_velocity().y });
	box->set_enabled(false);

}

EnemyAttackUpState::EnemyAttackUpState() {
	timer.set_wait_time(0.40f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_attack_up(false);
		enemy->set_attacking(false);
		enemy->set_changeDirection(true);
		});
}

void EnemyAttackUpState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_attack_up");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->set_changeDirection(false);
	enemy->set_attack_up(true);
	enemy->set_attacking(true);
	enemy->on_attack_up();

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_up_box();

	enemy->get_attack_up_vfx()->set_position(enemy->get_position() + vector2{ 0,-75 });

	box->set_enabled(true);
	box->update_enemy_attack_down_box_size();
	box->update_enemy_attack_down_box_position(enemy->get_logic_center());

	timer.restart();

	switch (range_random(1, 3)) {
	case 1:
		play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		play_audio(_T("player_attack_3"), false);
		break;
	}
}

void EnemyAttackUpState::on_update(float delta) {
	timer.on_update(delta);

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_up_box();

	enemy->get_attack_up_vfx()->set_position(enemy->get_position() + vector2{ 0,-75 });

	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);

	if (d > 200) {
		enemy->set_velocity({ (pos_enemy.x < pos_player.x ? attack_speed : -attack_speed) * (max(min(d / attack_dis,1),0.4f)),0 });
	}
	else if (d < 200) {
		enemy->set_velocity({ (pos_enemy.x < pos_player.x ? attack_speed : -attack_speed) * 0.2f,0 });
	}

	box->update_enemy_attack_up_box_size();
	box->update_enemy_attack_up_box_position(enemy->get_logic_center());


	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	else if (!enemy->get_attacking()) {
		enemy->switch_state("enemy_idle");
	}

}
void EnemyAttackUpState::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->set_attack_up(false);
	enemy->set_attacking(false);

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_up_box();
	enemy->set_velocity({ 0, enemy->get_velocity().y });
	box->set_enabled(false);

}
EnemyAttackUp_2_State::EnemyAttackUp_2_State() {
	timer.set_wait_time(0.40f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_attack_up_2(false);
		enemy->set_attacking(false);
		enemy->set_changeDirection(true);
		});
}

void EnemyAttackUp_2_State::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_attack_up");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->set_changeDirection(false);
	enemy->set_attack_up_2(true);
	enemy->set_attacking(true);
	enemy->on_attack_up_2();

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_up_2_box();

	box->set_enabled(true);
	box->update_enemy_attack_up_2_box_size();
	box->update_enemy_attack_up_2_box_position(enemy->get_logic_center());

	enemy->get_attack_up_2_vfx()->set_position(box->get_position());

	timer.restart();

	switch (range_random(1, 3)) {
	case 1:
		play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		play_audio(_T("player_attack_3"), false);
		break;
	}
}

void EnemyAttackUp_2_State::on_update(float delta) {
	timer.on_update(delta);

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_up_2_box();

	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);

	if (d > 200) {
		enemy->set_velocity({ (pos_enemy.x < pos_player.x ? attack_speed : -attack_speed) * (max(min(d / attack_dis,1),0.4f)),0 });
	}
	else if (d < 200) {
		enemy->set_velocity({ (pos_enemy.x < pos_player.x ? attack_speed : -attack_speed) * 0.2f,0 });
	}

	box->update_enemy_attack_up_2_box_size();
	box->update_enemy_attack_up_2_box_position(enemy->get_logic_center());


	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	else if (!enemy->get_attacking()) {
		enemy->switch_state("enemy_idle");
	}

}
void EnemyAttackUp_2_State::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->set_attack_up_2(false);
	enemy->set_attacking(false);

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_up_2_box();
	enemy->set_velocity({ 0, enemy->get_velocity().y });
	box->set_enabled(false);
}



EnemyAttackShiftState::EnemyAttackShiftState() {
	timer.set_wait_time(0.4f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_attack_shift(false);
		enemy->set_attacking(false);
		enemy->set_changeDirection(true);
	});
}

void EnemyAttackShiftState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_run");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();


	enemy->set_changeDirection(false);
	enemy->set_attack_shift(true);
	enemy->set_attacking(true);
	enemy->on_smoke();

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_shift_box();

	box->update_enemy_attack_shift_box_size();
	box->update_enemy_attack_shift_box_position(enemy->get_logic_center(),enemy->get_is_facing_left());

	enemy->get_current_attack_shift()->set_position(enemy->get_position() + vector2{ (enemy->get_is_facing_left() ? -1 : 1) * 35.0f,0 });
	timer.restart();

	switch (range_random(1, 3)) {
	case 1:
		play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		play_audio(_T("player_attack_3"), false);
		break;
	}
}

void EnemyAttackShiftState::on_update(float delta) {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();


	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_shift_box();


	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);
	if(d>=100)
	enemy->set_velocity({ (pos_enemy.x < pos_player.x ? attack_speed : -attack_speed) ,0 });

	if (d <= attack_dis_min) {
		can_show_attack = true;
	}
	if (can_show_attack) {
		CharacterManager::instance()->get_enemy()->set_animation("enemy_attack_up");
		enemy->on_attack_shift();
		enemy->set_is_character_visible(true);
		box->set_enabled(true);
		timer.on_update(delta);
	}

	box->update_enemy_attack_shift_box_size();
	box->update_enemy_attack_shift_box_position(enemy->get_logic_center(),enemy->get_is_facing_left());

	enemy->get_current_attack_shift()->set_position(enemy->get_position() + vector2{ (enemy->get_is_facing_left() ? -1 : 1) * 85.0f,-85.0f });

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	else if (!enemy->get_attacking()&&enemy->get_is_character_visible()) {
		enemy->switch_state("enemy_idle");
	}

}
void EnemyAttackShiftState::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->set_attack_shift(false);
	enemy->set_attacking(false);

	CollisionBox* box = CollisionManager::instance()->get_enemy_attack_shift_box();
	enemy->set_velocity({ 0, enemy->get_velocity().y });
	box->set_enabled(false);

	can_show_attack = false;
}


EnemyDeadState::EnemyDeadState() {
	timer.set_wait_time(2.5f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]() {
		MessageBox(GetHWnd(), _T("很好，你已战胜Martial_Hero。"), _T("挑战成功"), MB_OK);
		exit(0);
		});
}

void EnemyDeadState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_dead");

}

void EnemyDeadState::on_update(float delta) {
	timer.on_update(delta);
}



void EnemyFallState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_fall");
}

void EnemyFallState::on_update(float delta) {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	if (d <= 150 && enemy->get_position().y > 350 && enemy->can_attack_down()) {
		enemy->switch_state("enemy_attack_down");
	}
	else if (enemy->is_on_floor()) {
		enemy->switch_state("enemy_idle");
		enemy->on_land();
		play_audio(_T("player_land"), false);
	}

}


EnemyIdleState::EnemyIdleState() {
	timer.set_one_shot(true);
	timer.set_on_timeout([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		Player* player = (Player*)CharacterManager::instance()->get_player();
		const vector2& pos_enemy = enemy->get_position();
		const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
		float d = abs(pos_enemy.x - pos_player.x);

		int x = range_random(0, 100);
		if (!player->is_on_floor() && d <= 300.0f && enemy->can_attack_up()) {
			if(x<=50)
			enemy->switch_state("enemy_attack_up");
			else {
				enemy->switch_state("enemy_attack_up_2");
			}
		}

		if (d > 350) {
			enemy->switch_state("enemy_attack_shift");
		}
		else if (enemy->get_hp() >= 75) {
			if (d <= 350 && d >= 100) {
				if (x <= 30 && enemy->can_attack1()) {
					enemy->switch_state("enemy_attack1");
				}
				else if (x <= 60 && enemy->can_attack2()) {
					enemy->switch_state("enemy_attack2");
				}
				else if (x <= 75 && enemy->can_attack3()) {
					enemy->switch_state("enemy_attack3");
				}
				else if (x <= 90 && enemy->can_attack4()) {
					enemy->switch_state("enemy_attack4");
				}
				else if (enemy->can_jump()) {
					enemy->switch_state("enemy_jump");
				}
				else {
					enemy->switch_state("enemy_idle");
				}
			}
			else {
				enemy->switch_state("enemy_run");
			}
		}
		else if (enemy->get_hp() >= 45) {
			if (d <= 400 && d >= 100) {
				if (x <= 25 && enemy->can_attack1()) {
					enemy->switch_state("enemy_attack1");
				}
				else if (x <= 50 && enemy->can_attack2()) {
					enemy->switch_state("enemy_attack2");
				}
				else if (x <= 65 && enemy->can_attack3()) {
					enemy->switch_state("enemy_attack3");
				}
				else if (x <= 80 && enemy->can_attack4()) {
					enemy->switch_state("enemy_attack4");
				}
				else if (enemy->can_jump()) {
					enemy->switch_state("enemy_jump");
				}
				else {
					enemy->switch_state("enemy_idle");
				}
			}
			else {
				enemy->switch_state("enemy_run");
			}
		}
		else {
			if (d <= 450 && d >= 100) {
				if (x <= 10 && enemy->can_attack1()) {
					enemy->switch_state("enemy_attack1");
				}
				else if (x <= 20 && enemy->can_attack2()) {
					enemy->switch_state("enemy_attack2");
				}
				else if (x <= 50 && enemy->can_attack3()) {
					enemy->switch_state("enemy_attack3");
				}
				else if (x <= 80 && enemy->can_attack4()) {
					enemy->switch_state("enemy_attack4");
				}
				else if (enemy->can_jump()) {
					enemy->switch_state("enemy_jump");
				}
				else {
					enemy->switch_state("enemy_idle");
				}
			}
			else {
				enemy->switch_state("enemy_run");
			}
		}
		});
}
void EnemyIdleState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_run");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	float wait_time = 0;
	if (enemy->get_hp() >= 75) {
		wait_time = range_random(1, 2) * 0.25f;
	}
	else if (enemy->get_hp() >= 50) {
		wait_time = range_random(1, 2) * 0.20f;
	}
	else {
		wait_time = range_random(0, 2) * 0.15f;
	}
	timer.set_wait_time(wait_time);
	timer.restart();
}

void EnemyIdleState::on_update(float delta) {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);

	enemy->set_velocity({ (pos_enemy.x < pos_player.x ? idle_speed : -idle_speed),enemy->get_velocity().y });

	timer.on_update(delta);

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	if (enemy->get_velocity().y > 0) {
		enemy->switch_state("enemy_fall");
	}
}

void EnemyJumpState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_jump");

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->on_jump();

	play_audio(_T("player_jump"), false);

}

void EnemyJumpState::on_update(float delta) {

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	Player* player = (Player*)CharacterManager::instance()->get_player();
	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);
	enemy->set_velocity({ (pos_enemy.x < pos_player.x ? jump_x_speed : -jump_x_speed) * (max(min(d / dis,1),0.5f)),enemy->get_velocity().y });

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	else if (enemy->get_velocity().y > 0) {
		enemy->switch_state("enemy_fall");
	}

}


void EnemyRunState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_run");

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	enemy->on_run();

	play_audio(_T("player_run"), true);

}

void EnemyRunState::on_update(float delta) {

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);
	enemy->set_velocity({ (pos_enemy.x < pos_player.x ? speed_run : -speed_run) * (max(min(d / dis,1),0.5f)),0 });


	if (enemy->get_hp() <= 0) {
		enemy->switch_state("enemy_dead");
	}
	else if (d <= dis && d >= 100) {
		int rand_num = range_random(0, 100);
		if (enemy->get_hp() > 75) {
			if (rand_num <= 20) {
				enemy->switch_state("enemy_attack1");
			}
			else if (rand_num <= 40) {
				enemy->switch_state("enemy_attack2");
			}
			else if (rand_num <= 60) {
				enemy->switch_state("enemy_attack3");
			}
			else if(rand_num<=80){
				enemy->switch_state("enemy_attack4");
			}
			else {
				enemy->switch_state("enemy_idle");
			}
		}
		else if (enemy->get_hp() > 50) {
			if (rand_num <= 15) {
				enemy->switch_state("enemy_attack1");
			}
			else if (rand_num <= 30) {
				enemy->switch_state("enemy_attack2");
			}
			else if (rand_num <= 55) {
				enemy->switch_state("enemy_attack3");
			}
			else if(rand_num<=80) {
				enemy->switch_state("enemy_attack4");
			}
			else {
				enemy->switch_state("enemy_idle");
			}
		}
		else {
			if (rand_num <= 10) {
				enemy->switch_state("enemy_attack1");
			}
			else if (rand_num <= 20) {
				enemy->switch_state("enemy_attack2");
			}
			else if (rand_num <= 50) {
				enemy->switch_state("enemy_attack3");
			}
			else if(rand_num<=80) {
				enemy->switch_state("enemy_attack4");
			}
			else {
				enemy->switch_state("enemy_idle");
			}
		}
		stop_audio(_T("enemy_run"));
	}
	else if (d < 100) {
		int x = range_random(0, 100);
		if (x <= 50) {
			enemy->switch_state("enemy_back");
		}
		else {
			enemy->switch_state("enemy_jump");
		}
	}
}

void EnemyRunState::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->set_velocity({ 0,0 });
}


EnemyTakeHitState::EnemyTakeHitState() {
	timer.set_wait_time(0.50f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_taking_hit(false);
		});
}

void EnemyTakeHitState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("enemy_take_hit");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->get_hurt_box()->set_enabled(false);
	enemy->set_taking_hit(true);
	enemy->on_take_hit();
	timer.restart();
	
}

void EnemyTakeHitState::on_update(float delta) {
	timer.on_update(delta);

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	if (!enemy->get_is_taking_hit()) {
		enemy->switch_state("enemy_idle");
	}
}

void EnemyTakeHitState::on_exit() {
	CharacterManager::instance()->get_enemy()->get_hurt_box()->set_enabled(true);
}

void EnemyBackState::on_enter() {

	CharacterManager::instance()->get_enemy()->set_animation("enemy_run");

	timer.set_wait_time(1.0f + range_random(2, 4) * 0.5f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		int rand_num = range_random(0, 100);
		if (rand_num <= 20) {
			enemy->switch_state("enemy_attack1");
		}
		else if (rand_num <= 40) {
			enemy->switch_state("enemy_attack2");
		}
		else if (rand_num <= 60) {
			enemy->switch_state("enemy_attack3");
		}
		else if (rand_num <= 80) {
			enemy->switch_state("enemy_attack4");
		}
		else {
			enemy->switch_state("enemy_jump");
		}
	});
}

void EnemyBackState::on_update(float delta) {

	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();

	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	float d = abs(pos_enemy.x - pos_player.x);

	enemy->set_velocity({ (pos_enemy.x < pos_player.x ? -back_speed : back_speed),0 });

	int rand_num = range_random(0, 100);
	if (enemy->get_position().x <= 100) {
		if (rand_num <= 50)
			enemy->switch_state("enemy_attack3");
		else {
			enemy->switch_state("enemy_attack4");
		}
	}
	if (enemy->get_position().x >= getwidth() - 100) {
		if (rand_num <= 50)
			enemy->switch_state("enemy_attack3");
		else {
			enemy->switch_state("enemy_attack4");
		}
	}
	if (d > dis_max) {
		if (rand_num < 30) {
			enemy->switch_state("enemy_jump");
		}
		else {
			enemy->switch_state("enemy_attack_shift");
		}
	}

	if (d <= dis_max && d >= dis_min) {
		if (rand_num <= 20) {
			enemy->switch_state("enemy_attack1");
		}
		else if (rand_num <= 40) {
			enemy->switch_state("enemy_attack2");
		}
		else if (rand_num <= 70) {
			enemy->switch_state("enemy_attack3");
		}
		else {
			enemy->switch_state("enemy_attack4");
		}
	}
}

void EnemyBackState::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->set_velocity({ 0,0 });
	const vector2& pos_enemy = enemy->get_position();
	const vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	enemy->set_is_facing_left(pos_enemy.x > pos_player.x);
}