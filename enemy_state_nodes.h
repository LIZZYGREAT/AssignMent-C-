#pragma once
#include"timer.h"
#include"state_node.h"

class EnemyAttack1State :public StateNode {
public:
	EnemyAttack1State();
	~EnemyAttack1State() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit() override;
private:
	Timer timer;
	float attack_speed = 250.0f;
	float attack_dis = 300.0f;
	float sum_delta_time = 0;
};

class EnemyAttack2State :public StateNode {
public:
	EnemyAttack2State();
	~EnemyAttack2State() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit() override;
private:
	Timer timer;
	float attack_speed = 250.0f;
	float attack_dis = 300.0f;
};

class EnemyAttack3State :public StateNode {
public:
	EnemyAttack3State();
	~EnemyAttack3State() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit() override;
private:
	Timer timer1;
	float attack_speed = 300.0f;
	float attack_dis = 400.0f;

};

class EnemyAttack4State :public StateNode {
public:
	EnemyAttack4State();
	~EnemyAttack4State() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer1;
	float attack_speed = 300.0f;
	float attack_dis = 400.0f;

};

class EnemyAttackUpState :public StateNode {
public:
	EnemyAttackUpState();
	~EnemyAttackUpState() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
	float attack_speed = 300.0f;
	float attack_dis = 400.0f;
};

class EnemyAttackUp_2_State :public StateNode {
public:
	EnemyAttackUp_2_State();
	~EnemyAttackUp_2_State() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
	float attack_speed = 300.0f;
	float attack_dis = 400.0f;
};

class EnemyAttackDownState :public StateNode {
public:
	EnemyAttackDownState();
	~EnemyAttackDownState() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
};

class EnemyAttackShiftState :public StateNode {
public:
	EnemyAttackShiftState();
	~EnemyAttackShiftState() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
	float attack_dis_min = 250.0f;
	float attack_speed = 400;
	bool can_show_attack = false;
};


class EnemyDeadState :public StateNode {
public:
	EnemyDeadState();
	~EnemyDeadState() = default;

	void on_enter()override;
	void on_update(float delta) override;

private:
	Timer timer;

};

class EnemyFallState :public StateNode {
public:
	EnemyFallState() = default;
	~EnemyFallState() = default;

	void on_enter()override;
	void on_update(float delta) override;
};

class EnemyIdleState :public StateNode {
public:
	EnemyIdleState();
	~EnemyIdleState() = default;

	void on_enter()override;
	void on_update(float delta) override;
private:
	Timer timer;
	float idle_speed = 125.0f;
};

class EnemyJumpState :public StateNode {
public:
	EnemyJumpState() = default;
	~EnemyJumpState() = default;

	void on_enter()override;
	void on_update(float delta) override;
private:
	float jump_x_speed = 400.0f;
	float dis = 500.0f;
};

class EnemyRunState :public StateNode {
public:
	EnemyRunState() = default;
	~EnemyRunState() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit() override;
private:
	const float dis = 350.0f;
	float speed_run = 400.0f;
};

class EnemyBackState : public StateNode {
public:
	EnemyBackState() = default;
	~EnemyBackState() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit()override;

private:
	float dis_min = 250.0f;
	float dis_max = 450.0f;
	float back_speed = 300.0f;
	Timer timer;

};


class EnemyTakeHitState : public StateNode {  //¿‡À∆”⁄roll
public:
	EnemyTakeHitState();
	~EnemyTakeHitState() = default;

	void on_enter()override;
	void on_update(float delta) override;
	void on_exit()override;
private:
	Timer timer;
};