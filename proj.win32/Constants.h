#pragma once
#include "cocos2d.h"

static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);

static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

static constexpr int lemming_collision_mask_id = 0x01;
static constexpr int window_collision_mask_id = 0x02;
static constexpr int test_collision_mask_id = 0x03;


static const char *in_game_physics_layer_name_template = "physics_layer_";
static const char *lemming_name_template = "lemming_";
static const char *window_collision_name_template = "window_collider_";


static const char *font_path = "fonts/Marker Felt.ttf";

static const char *tileMap_path = "map/Test.tmx";
static const char *tileMap_netherPortal_asset_path = "map/netherPortal.png";

static const char *lemming_asset_filePath = "HelloWorld.png";
static const char *lemming_selector_asset_path = "lemming_selector.png";


static const char *menu_closeButton_path = "CloseNormal.png";
static const char *menu_closeButton_selected_path = "CloseSelected.png";
static const char *menu_mainMenu_background_path = "main_menu.jpg";
static const char *menu_levelMenu_background_path = "map_level.png";
static const char *menu_levelMenu_pointer_path = "CloseSelected.png";
static const char *menu_levelMenu_cursor_path = "map_cursor.png";
