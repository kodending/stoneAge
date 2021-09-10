#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);

	addImage();
	addSoundEffect();

	SCENEMANAGER->addScene("맵툴", new mapToolScene);
	SCENEMANAGER->addScene("마을", new villageScene);
	SCENEMANAGER->addScene("메인", new mainScene);
	SCENEMANAGER->addScene("캐릭터선택", new selectScene);
	SCENEMANAGER->addScene("생성화면", new createScene);
	SCENEMANAGER->addScene("플레이어초기설정", new playerSetting);
	SCENEMANAGER->addScene("던전1", new firstDungeonScene);
	SCENEMANAGER->addScene("배틀1", new firstBattleScene);
	SCENEMANAGER->addScene("아이템상점", new itemShopScene);
	SCENEMANAGER->changeScene("메인"); //시작은 메인 또는 맵툴임
	
	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();
}


void playGround::update()
{
	gameNode::update();
	
	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, BACKGROUNDX, BACKGROUNDY, WHITENESS);
	//================제발 이 사이에 좀 그립시다==========================

	SCENEMANAGER->render();

	//==================================================
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
}


void playGround::addImage()
{
	IMAGEMANAGER->addImage("mouse", "image/UI/mouse.bmp", 31, 32, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("tileSelect", "image/UI/tile_select.bmp", 64, 47, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("eraser", "image/UI/eraser.bmp", 100, 50, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("underBar", "image/HUD/under_bar.bmp", 1024, 24, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("underBar2", "image/HUD/under_bar2.bmp", 800, 24, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("menuBar", "image/HUD/menu_bar.bmp", 800, 24, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("toolBar", "image/HUD/tool_bar.bmp", 1024, 24, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("popUp", "image/HUD/tool_select.bmp", 640, 640, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("saveInput", "image/HUD/saveinput.bmp", 271, 118, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("toolName", "image/HUD/tooltype.bmp", 2200, 45, 11, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("leftButton", "image/HUD/leftbutton.bmp", 60, 30, 2, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("rightButton", "image/HUD/rightbutton.bmp", 60, 30, 2, 1, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("display", "image/maptool/display.bmp", 4250, 350, 17, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("fence", "image/maptool/fence.bmp", 1500, 150, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("gate", "image/maptool/gate.bmp", 1200, 450, 4, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("npc", "image/maptool/npc.bmp", 5600, 100, 56, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("object", "image/maptool/object.bmp", 24800, 450, 62, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("plants", "image/maptool/plants.bmp", 6300, 300, 21, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("rock", "image/maptool/rock.bmp", 1700, 100, 17, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("structure", "image/maptool/structure.bmp", 18200, 1600, 26, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("tile", "image/maptool/tile.bmp", 896, 1034, 14, 22, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("tileType", "image/maptool/tiletype.bmp", 704, 47, 11, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("wall_basic", "image/maptool/wall_basic.bmp", 18400, 400, 46, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("wall_dungeon", "image/maptool/wall_dungeon.bmp", 21600, 600, 54, 1, true, RGB(255, 0, 255), true);

	//플레이어 이미지 등록(레드)
	IMAGEMANAGER->addFrameImage("red_angry_basic", "image/player/red/basic/angry_basic.bmp", 609, 672, 7, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_attack_basic", "image/player/red/basic/attack_basic.bmp", 1044, 672, 12, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_catch_basic", "image/player/red/basic/attack_basic.bmp", 1044, 672, 12, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_cry_basic", "image/player/red/basic/cry_basic.bmp", 348, 672, 4, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_dead_basic", "image/player/red/basic/dead_basic.bmp", 522, 672, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_defense_basic", "image/player/red/basic/defense_basic.bmp", 174, 672, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_happy_basic", "image/player/red/basic/happy_basic.bmp", 174, 672, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_hello_basic", "image/player/red/basic/hello_basic.bmp", 609, 672, 7, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_hurt_basic", "image/player/red/basic/hurt_basic.bmp", 174, 672, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_run_basic", "image/player/red/basic/run_basic.bmp", 522, 672, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_seat_basic", "image/player/red/basic/seat_basic.bmp", 174, 672, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("red_stand_basic", "image/player/red/basic/stand_basic.bmp", 348, 672, 4, 8, true, RGB(255, 0, 255), true);

	//플레이어 이미지 등록(블루)
	IMAGEMANAGER->addFrameImage("blue_angry_basic", "image/player/blue/basic/angry_basic.bmp", 522, 800, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_attack_basic", "image/player/blue/basic/attack_basic.bmp", 1218, 800, 14, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_catch_basic", "image/player/blue/basic/attack_basic.bmp", 1218, 800, 14, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_cry_basic", "image/player/blue/basic/cry_basic.bmp", 522, 800, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_dead_basic", "image/player/blue/basic/dead_basic.bmp", 1044, 800, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_defense_basic", "image/player/blue/basic/defense_basic.bmp", 174, 800, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_happy_basic", "image/player/blue/basic/happy_basic.bmp", 1044, 800, 12, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_hello_basic", "image/player/blue/basic/hello_basic.bmp", 174, 800, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_hurt_basic", "image/player/blue/basic/hurt_basic.bmp", 174, 800, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_run_basic", "image/player/blue/basic/run_basic.bmp", 522, 800, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_seat_basic", "image/player/blue/basic/seat_basic.bmp", 174, 800, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("blue_stand_basic", "image/player/blue/basic/stand_basic.bmp", 348, 800, 4, 8, true, RGB(255, 0, 255), true);


	//메인 화면 이미지 등록
	IMAGEMANAGER->addImage("main", "image/HUD/main.bmp", 800, 600, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("mainMenu", "image/HUD/main_menu.bmp", 193, 216, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("mainMenuBack", "image/HUD/main_menuBack.bmp", 174, 198, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("inputWindow", "image/HUD/입력창틀.bmp", 271, 118, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("inputWindowBack", "image/HUD/입력창배경.bmp", 251, 96, true, RGB(255, 0, 255), true);

	//캐릭터 선택 이미지 등록
	IMAGEMANAGER->addImage("characterSelect", "image/HUD/character_select.bmp", 800, 600, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("playerFace", "image/HUD/player_face.bmp", 156, 118, 2, 1, true, RGB(255, 0, 255), true);

	//버튼이미지 등록
	IMAGEMANAGER->addImage("button", "image/HUD/button.bmp", 96, 30, true, RGB(255, 0, 255), true);

	//캐릭터 생성창 등록
	IMAGEMANAGER->addImage("characterCreate", "image/HUD/character_create.bmp", 800, 600, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("return", "image/HUD/return.bmp", 64, 64, true, RGB(255, 0, 255), true);

	//캐릭터 초기세팅창 등록
	IMAGEMANAGER->addImage("playerSetting", "image/HUD/character_input.bmp", 800, 600, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("playerAttribute", "image/HUD/player_attribute.bmp", 32, 12, 4, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("playerFaceSetting", "image/HUD/player_face(setting).bmp", 126, 69, 2, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("inputWindow2", "image/HUD/입력창틀2.bmp", 271, 118, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("baseLeft", "image/HUD/base_left.bmp", 250, 67, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("baseRight", "image/HUD/base_right.bmp", 200, 78, true, RGB(255, 0, 255), true);

	//액션윈도우창등록
	IMAGEMANAGER->addImage("actionWindow", "image/HUD/action_window.bmp", 250, 280, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("actionWindowBack", "image/HUD/action_window_back.bmp", 227, 258, true, RGB(255, 0, 255), true);

	//상태창 윈도우 등록
	IMAGEMANAGER->addImage("stateWindow", "image/HUD/state_window.bmp", 283, 371, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("stateWindowBack", "image/HUD/state_window_back.bmp", 274, 365, true, RGB(255, 0, 255), true);

	//펫 윈도우 등록
	IMAGEMANAGER->addImage("petWindow", "image/HUD/pet_window.bmp", 300, 353, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("petWindowBack", "image/HUD/pet_window_back.bmp", 290, 345, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("petInfoWindow", "image/HUD/pet_info_window.bmp", 500, 360, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("petInfoWindowBack", "image/HUD/pet_info_window_back.bmp", 489, 353, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("petSkillWindow", "image/HUD/pet_skill_window.bmp", 300, 384, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("petSkillWindowBack", "image/HUD/pet_skill_window_back.bmp", 290, 375, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("petButton", "image/HUD/petButton.bmp", 62, 28, true, RGB(255, 0, 255), true);

	//펫이미지등록
	//두리
	IMAGEMANAGER->addFrameImage("duri_attack", "image/pet/duriType/duri/duri_attack.bmp", 900, 800, 9, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("duri_dead", "image/pet/duriType/duri/duri_dead.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("duri_defense", "image/pet/duriType/duri/duri_defense.bmp", 100, 800, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("duri_hurt", "image/pet/duriType/duri/duri_hurt.bmp", 400, 800, 4, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("duri_run", "image/pet/duriType/duri/duri_run.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("duri_stand", "image/pet/duriType/duri/duri_stand.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255), true);

	//얼룩우리
	IMAGEMANAGER->addFrameImage("spottedUri_attack", "image/pet/duriType/spottedUri/spottedUri_attack.bmp", 2600, 800, 26, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("spottedUri_dead", "image/pet/duriType/spottedUri/spottedUri_dead.bmp", 2000, 800, 20, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("spottedUri_defense", "image/pet/duriType/spottedUri/spottedUri_defense.bmp", 100, 800, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("spottedUri_hurt", "image/pet/duriType/spottedUri/spottedUri_hurt.bmp", 400, 800, 4, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("spottedUri_run", "image/pet/duriType/spottedUri/spottedUri_run.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("spottedUri_stand", "image/pet/duriType/spottedUri/spottedUri_stand.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255), true);

	//우리
	IMAGEMANAGER->addFrameImage("uri_attack", "image/pet/duriType/uri/uri_attack.bmp", 900, 800, 9, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("uri_dead", "image/pet/duriType/uri/uri_dead.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("uri_defense", "image/pet/duriType/uri/uri_defense.bmp", 100, 800, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("uri_hurt", "image/pet/duriType/uri/uri_hurt.bmp", 400, 800, 4, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("uri_run", "image/pet/duriType/uri/uri_run.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("uri_stand", "image/pet/duriType/uri/uri_stand.bmp", 600, 800, 6, 8, true, RGB(255, 0, 255), true);

	//마모나스
	IMAGEMANAGER->addFrameImage("mamonas_attack", "image/pet/manmoType/mamonas/mamonas_attack.bmp", 2200, 1760, 10, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mamonas_dead", "image/pet/manmoType/mamonas/mamonas_dead.bmp", 1320, 1760, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mamonas_defense", "image/pet/manmoType/mamonas/mamonas_defense.bmp", 220, 1760, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mamonas_hurt", "image/pet/manmoType/mamonas/mamonas_hurt.bmp", 440, 1760, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mamonas_run", "image/pet/manmoType/mamonas/mamonas_run.bmp", 1320, 1760, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mamonas_stand", "image/pet/manmoType/mamonas/mamonas_stand.bmp", 10340, 1760, 47, 8, true, RGB(255, 0, 255), true);

	//만모
	IMAGEMANAGER->addFrameImage("manmo_attack", "image/pet/manmoType/manmo/manmo_attack.bmp", 2200, 1760, 10, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("manmo_dead", "image/pet/manmoType/manmo/manmo_dead.bmp", 1320, 1760, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("manmo_defense", "image/pet/manmoType/manmo/manmo_defense.bmp", 220, 1760, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("manmo_hurt", "image/pet/manmoType/manmo/manmo_hurt.bmp", 440, 1760, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("manmo_run", "image/pet/manmoType/manmo/manmo_run.bmp", 1320, 1760, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("manmo_stand", "image/pet/manmoType/manmo/manmo_stand.bmp", 10340, 1760, 47, 8, true, RGB(255, 0, 255), true);

	//만모르
	IMAGEMANAGER->addFrameImage("manmor_attack", "image/pet/manmoType/manmor/manmor_attack.bmp", 2200, 1760, 10, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("manmor_dead", "image/pet/manmoType/manmor/manmor_dead.bmp", 1320, 1760, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("manmor_defense", "image/pet/manmoType/manmor/manmor_defense.bmp", 220, 1760, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("manmor_hurt", "image/pet/manmoType/manmor/manmor_hurt.bmp", 440, 1760, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("manmor_run", "image/pet/manmoType/manmor/manmor_run.bmp", 1320, 1760, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("manmor_stand", "image/pet/manmoType/manmor/manmor_stand.bmp", 10340, 1760, 47, 8, true, RGB(255, 0, 255), true);

	//골로스
	IMAGEMANAGER->addFrameImage("golros_attack", "image/pet/ogarosType/golros/golros_attack.bmp", 3300, 1200, 22, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("golros_dead", "image/pet/ogarosType/golros/golros_dead.bmp", 1350, 1200, 9, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("golros_defense", "image/pet/ogarosType/golros/golros_defense.bmp", 150, 1200, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("golros_hurt", "image/pet/ogarosType/golros/golros_hurt.bmp", 150, 1200, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("golros_run", "image/pet/ogarosType/golros/golros_run.bmp", 900, 1200, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("golros_stand", "image/pet/ogarosType/golros/golros_stand.bmp", 9900, 1200, 66, 8, true, RGB(255, 0, 255), true);

	//모가로스
	IMAGEMANAGER->addFrameImage("mogaros_attack", "image/pet/ogarosType/mogaros/mogaros_attack.bmp", 3060, 1440, 17, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mogaros_dead", "image/pet/ogarosType/mogaros/mogaros_dead.bmp", 1620, 1440, 9, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mogaros_defense", "image/pet/ogarosType/mogaros/mogaros_defense.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mogaros_hurt", "image/pet/ogarosType/mogaros/mogaros_hurt.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mogaros_run", "image/pet/ogarosType/mogaros/mogaros_run.bmp", 1080, 1440, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("mogaros_stand", "image/pet/ogarosType/mogaros/mogaros_stand.bmp", 11880, 1440, 66, 8, true, RGB(255, 0, 255), true);

	//오가로스
	IMAGEMANAGER->addFrameImage("ogaros_attack", "image/pet/ogarosType/ogaros/ogaros_attack.bmp", 1500, 1200, 10, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ogaros_dead", "image/pet/ogarosType/ogaros/ogaros_dead.bmp", 1350, 1200, 9, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ogaros_defense", "image/pet/ogarosType/ogaros/ogaros_defense.bmp", 150, 1200, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ogaros_hurt", "image/pet/ogarosType/ogaros/ogaros_hurt.bmp", 150, 1200, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ogaros_run", "image/pet/ogarosType/ogaros/ogaros_run.bmp", 900, 1200, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ogaros_stand", "image/pet/ogarosType/ogaros/ogaros_stand.bmp", 9900, 1200, 66, 8, true, RGB(255, 0, 255), true);

	//고르고르
	IMAGEMANAGER->addFrameImage("gorgor_attack", "image/pet/vergaType/gorgor/gorgor_attack.bmp", 1080, 1440, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("gorgor_dead", "image/pet/vergaType/gorgor/gorgor_dead.bmp", 1440, 1440, 8, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("gorgor_defense", "image/pet/vergaType/gorgor/gorgor_defense.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("gorgor_hurt", "image/pet/vergaType/gorgor/gorgor_hurt.bmp", 360, 1440, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("gorgor_run", "image/pet/vergaType/gorgor/gorgor_run.bmp", 1620, 1440, 9, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("gorgor_stand", "image/pet/vergaType/gorgor/gorgor_stand.bmp", 5940, 1440, 33, 8, true, RGB(255, 0, 255), true);

	//노르노르
	IMAGEMANAGER->addFrameImage("nornor_attack", "image/pet/vergaType/nornor/nornor_attack.bmp", 1620, 1440, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("nornor_dead", "image/pet/vergaType/nornor/nornor_dead.bmp", 1440, 1440, 8, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("nornor_defense", "image/pet/vergaType/nornor/nornor_defense.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("nornor_hurt", "image/pet/vergaType/nornor/nornor_hurt.bmp", 360, 1440, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("nornor_run", "image/pet/vergaType/nornor/nornor_run.bmp", 1620, 1440, 9, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("nornor_stand", "image/pet/vergaType/nornor/nornor_stand.bmp", 5940, 1440, 33, 8, true, RGB(255, 0, 255), true);

	//베르가
	IMAGEMANAGER->addFrameImage("verga_attack", "image/pet/vergaType/verga/verga_attack.bmp", 1620, 1440, 9, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("verga_dead", "image/pet/vergaType/verga/verga_dead.bmp", 1440, 1440, 8, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("verga_defense", "image/pet/vergaType/verga/verga_defense.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("verga_hurt", "image/pet/vergaType/verga/verga_hurt.bmp", 360, 1440, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("verga_run", "image/pet/vergaType/verga/verga_run.bmp", 1620, 1440, 9, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("verga_stand", "image/pet/vergaType/verga/verga_stand.bmp", 5940, 1440, 33, 8, true, RGB(255, 0, 255), true);

	//베루루
	IMAGEMANAGER->addFrameImage("veruru_attack", "image/pet/vergaType/veruru/veruru_attack.bmp", 1080, 1440, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("veruru_dead", "image/pet/vergaType/veruru/veruru_dead.bmp", 1440, 1440, 8, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("veruru_defense", "image/pet/vergaType/veruru/veruru_defense.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("veruru_hurt", "image/pet/vergaType/veruru/veruru_hurt.bmp", 360, 1440, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("veruru_run", "image/pet/vergaType/veruru/veruru_run.bmp", 1620, 1440, 9, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("veruru_stand", "image/pet/vergaType/veruru/veruru_stand.bmp", 5940, 1440, 33, 8, true, RGB(255, 0, 255), true);

	//반보로
	IMAGEMANAGER->addFrameImage("banboro_attack", "image/pet/yangiroType/banboro/banboro_attack.bmp", 2160, 1440, 12, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("banboro_dead", "image/pet/yangiroType/banboro/banboro_dead.bmp", 2340, 1440, 13, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("banboro_defense", "image/pet/yangiroType/banboro/banboro_defense.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("banboro_hurt", "image/pet/yangiroType/banboro/banboro_hurt.bmp", 360, 1440, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("banboro_run", "image/pet/yangiroType/banboro/banboro_run.bmp", 1080, 1440, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("banboro_stand", "image/pet/yangiroType/banboro/banboro_stand.bmp", 4680, 1440, 26, 8, true, RGB(255, 0, 255), true);

	//반기노
	IMAGEMANAGER->addFrameImage("bangino_attack", "image/pet/yangiroType/bangino/bangino_attack.bmp", 1440, 1440, 8, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("bangino_dead", "image/pet/yangiroType/bangino/bangino_dead.bmp", 2340, 1440, 13, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("bangino_defense", "image/pet/yangiroType/bangino/bangino_defense.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("bangino_hurt", "image/pet/yangiroType/bangino/bangino_hurt.bmp", 360, 1440, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("bangino_run", "image/pet/yangiroType/bangino/bangino_run.bmp", 1080, 1440, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("bangino_stand", "image/pet/yangiroType/bangino/bangino_stand.bmp", 5400, 1440, 30, 8, true, RGB(255, 0, 255), true);

	//부르돈
	IMAGEMANAGER->addFrameImage("burdon_attack", "image/pet/yangiroType/burdon/burdon_attack.bmp", 1440, 1440, 8, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("burdon_dead", "image/pet/yangiroType/burdon/burdon_dead.bmp", 2340, 1440, 13, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("burdon_defense", "image/pet/yangiroType/burdon/burdon_defense.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("burdon_hurt", "image/pet/yangiroType/burdon/burdon_hurt.bmp", 360, 1440, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("burdon_run", "image/pet/yangiroType/burdon/burdon_run.bmp", 1080, 1440, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("burdon_stand", "image/pet/yangiroType/burdon/burdon_stand.bmp", 5400, 1440, 30, 8, true, RGB(255, 0, 255), true);

	//리비노
	IMAGEMANAGER->addFrameImage("ribino_attack", "image/pet/yangiroType/ribino/ribino_attack.bmp", 1440, 1440, 8, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ribino_dead", "image/pet/yangiroType/ribino/ribino_dead.bmp", 2340, 1440, 13, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ribino_defense", "image/pet/yangiroType/ribino/ribino_defense.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ribino_hurt", "image/pet/yangiroType/ribino/ribino_hurt.bmp", 360, 1440, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ribino_run", "image/pet/yangiroType/ribino/ribino_run.bmp", 1080, 1440, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ribino_stand", "image/pet/yangiroType/ribino/ribino_stand.bmp", 5400, 1440, 30, 8, true, RGB(255, 0, 255), true);

	//얀기로
	IMAGEMANAGER->addFrameImage("yangiro_attack", "image/pet/yangiroType/yangiro/yangiro_attack.bmp", 2160, 1440, 12, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("yangiro_dead", "image/pet/yangiroType/yangiro/yangiro_dead.bmp", 2340, 1440, 13, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("yangiro_defense", "image/pet/yangiroType/yangiro/yangiro_defense.bmp", 180, 1440, 1, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("yangiro_hurt", "image/pet/yangiroType/yangiro/yangiro_hurt.bmp", 360, 1440, 2, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("yangiro_run", "image/pet/yangiroType/yangiro/yangiro_run.bmp", 1080, 1440, 6, 8, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("yangiro_stand", "image/pet/yangiroType/yangiro/yangiro_stand.bmp", 4680, 1440, 26, 8, true, RGB(255, 0, 255), true);

	//배틀맵 관련 이미지설정
	IMAGEMANAGER->addImage("dungeon1_map", "image/mapTool/battleMap1.bmp", 800, 600, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("battleWindow", "image/HUD/battle_window.bmp", 2000, 145, 8, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("battleTime", "image/HUD/number.bmp", 300, 62, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("selectSkillWindow", "image/HUD/select_skill_window.bmp", 240, 88, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("escape", "image/HUD/escape.bmp", 73, 22, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("guard", "image/HUD/guard.bmp", 78, 25, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("miss", "image/HUD/miss.bmp", 76, 24, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("battleItemWindow", "image/HUD/battle_item_window.bmp", 304, 315, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("battleItemWindowBack", "image/HUD/battle_item_window_back.bmp", 272, 287, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("petSkillWindow2", "image/HUD/pet_skill_window2.bmp", 300, 384, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("battleClose", "image/HUD/battle_close.bmp", 800, 600, true, RGB(255, 0, 255), true);

	//아이템창 관련 이미지 설정
	IMAGEMANAGER->addImage("itemWindow", "image/HUD/item_window.bmp", 307, 446, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("itemWindowBack", "image/HUD/item_window_back.bmp", 274, 438, true, RGB(255, 0, 255), true);

	//아이템관련이미지
	IMAGEMANAGER->addFrameImage("item", "image/item/item.bmp", 1050, 70, 15, 1, true, RGB(255, 0, 255), true);

	//샵관련 이미지
	IMAGEMANAGER->addImage("shopWindow", "image/HUD/shop_window.bmp", 427, 414, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("shopWindowBack", "image/HUD/shop_window_back.bmp", 414, 404, true, RGB(255, 0, 255), true);
}

void playGround::addSoundEffect()
{
	//백그라운드 사운드
	SOUNDMANAGER->addSound("battle1_bg", "sound/background/battle1.wav", true, true);
	SOUNDMANAGER->addSound("battle2_bg", "sound/background/battle2.wav", true, true);
	SOUNDMANAGER->addSound("dungeon1_bg", "sound/background/dungeon1.wav", true, true);
	SOUNDMANAGER->addSound("select_bg", "sound/background/select.wav", true, true);
	SOUNDMANAGER->addSound("village_bg", "sound/background/village.wav", true, true);
	SOUNDMANAGER->addSound("catch_success_bg", "sound/background/catch_success.wav", false, false);

	//이펙트사운드
	SOUNDMANAGER->addSound("battle_convert", "sound/battle_convert.wav", false, false);
	SOUNDMANAGER->addSound("click", "sound/click.wav", false, false);
	SOUNDMANAGER->addSound("scene_start", "sound/scene_start.wav", false, false);
	SOUNDMANAGER->addSound("window_down", "sound/window_down.wav", false, false);
	SOUNDMANAGER->addSound("window_up", "sound/window_up.wav", false, false);
	SOUNDMANAGER->addSound("dead", "sound/dead/dead.wav", false, false);
	SOUNDMANAGER->addSound("duri", "sound/attack/duri.wav", false, false);
	SOUNDMANAGER->addSound("manmo", "sound/attack/manmo.wav", false, false);
	SOUNDMANAGER->addSound("verga", "sound/attack/verga.wav", false, false);
	SOUNDMANAGER->addSound("one_heat", "sound/attack/one_heat.wav", false, false);
	SOUNDMANAGER->addSound("two_heat", "sound/attack/two_heat.wav", false, false);
}
