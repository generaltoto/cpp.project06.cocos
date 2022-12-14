#pragma once

static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);

static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

static const int lemming_collision_mask_id = 0x01;
static const int window_collision_mask_id = 0x02;

static const char *in_game_physics_layer_name_template = "physics_layer_";
static const char *lemming_name_template = "lemming_";
static const char *window_collision_name_template = "window_collider_";