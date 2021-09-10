#include "stdafx.h"
#include "mapTool.h"
#include "toolEmpty.h"
#include "toolTile.h"
#include "toolStructure.h"
#include "toolObject.h"
#include "toolFence.h"
#include "toolGate.h"
#include "toolDisplay.h"
#include "toolPlants.h"
#include "toolRock.h"
#include "toolWallBasic.h"
#include "toolWallDungeon.h"
#include "toolNpc.h"
#include "toolEraser.h"
#include "toolTileType.h"
#include "toolSave.h"
#include "gameNode.h"

toolType * toolSave::inputHandle(mapTool * mapTool)
{
	//나가기 버튼을 눌렀을때 비우기 위한
	if (PtInRect(&mapTool->_popUp.exitButtonRc,
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())) ||
		PtInRect(&mapTool->_saveInput.cancelButtonRect,
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsSaveInput(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new toolEmpty();
	}

	//메뉴툴바에서 건축물 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getStructureRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsSaveInput(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolStructure();
	}

	//메뉴툴바에서 타일 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getTileRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsSaveInput(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolTile();
	}

	//메뉴툴바에서 구조물 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getObjectRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsSaveInput(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolObject();
	}

	//메뉴툴바에서 NPC 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getNpcRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsSaveInput(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolNpc();
	}

	//메뉴툴바에서 지우개 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getEraserRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsSaveInput(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new toolEraser();
	}
	
	//세이브버튼을 눌렀을때 세이브 되도록하기위함
	if (PtInRect(&mapTool->_saveInput.saveButtonRect,
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->saveMap();
		mapTool->setIsSaveInput(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolEmpty();
	}

	return nullptr;
}

void toolSave::update(mapTool * mapTool)
{
	mapTool->_popUp.PopUpRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + mapTool->_popUp.img->getWidth(),
		CAMERAMANAGER->getCameraBOTTOM() + mapTool->_popUp.img->getHeight() - 24,
		mapTool->_popUp.img->getWidth(), mapTool->_popUp.img->getHeight());

	mapTool->_popUp.exitButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 146, CAMERAMANAGER->getCameraBOTTOM() + 73,
		124, 27);

	mapTool->_popUp.leftButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 616, CAMERAMANAGER->getCameraBOTTOM() + 336 - 24,
		32, 32);

	mapTool->_popUp.upButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 336, CAMERAMANAGER->getCameraBOTTOM() + 582 - 24,
		32, 32);

	mapTool->_popUp.rightButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 54, CAMERAMANAGER->getCameraBOTTOM() + 336 - 24,
		32, 32);

	mapTool->_popUp.downButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 336, CAMERAMANAGER->getCameraBOTTOM() + 54 - 24,
		32, 32);

	mapTool->_sampleTile.rcTile = RectMake(CAMERAMANAGER->getCameraRIGHT() + 353, CAMERAMANAGER->getCameraBOTTOM() + 344 - 24,
		64, 47);

	mapTool->_toolName.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 320, CAMERAMANAGER->getCameraBOTTOM() + 610 - 24,
		200, 45);

	mapTool->_leftButton.rc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 516, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24,
		32, 32);

	mapTool->_rightButton.rc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24,
		32, 32);

	//saveButton 이미지 및 rc 활성화
	mapTool->_saveInput.saveRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(), 271, 118);
	mapTool->_saveInput.saveButtonRect = RectMake(CAMERAMANAGER->getCameraCenterX() - 107, CAMERAMANAGER->getCameraCenterY() + 2, 97, 31);
	mapTool->_saveInput.cancelButtonRect = RectMake(CAMERAMANAGER->getCameraCenterX() + 14, CAMERAMANAGER->getCameraCenterY() + 2, 97, 31);
	mapTool->_saveInput.textInputRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY() - 13, 200, 20);

	mapTool->dialogInput();
}

void toolSave::enter(mapTool * mapTool)
{
	mapTool->setIsSaveInput(true);
	mapTool->setIsExitButton(false);

	mapTool->_saveInput.img = IMAGEMANAGER->findImage("saveInput");

	if (mapTool->getNameSize() != 0)
	{
		mapTool->setName(mapTool->getName().erase());
	}
}

void toolSave::render(mapTool * mapTool)
{
	mapTool->_saveInput.img->render(getMemDC(), mapTool->_saveInput.saveRect.left, mapTool->_saveInput.saveRect.top);

	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);

	Rectangle(getMemDC(), mapTool->_saveInput.textInputRect);

	DeleteObject(SelectObject(getMemDC(), oldPen));

	mapTool->renderDialog();
}

void toolSave::exit(mapTool * mapTool)
{
}
