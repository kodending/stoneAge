#include "stdafx.h"
#include "mapTool.h"
#include "toolEmpty.h"
#include "toolTile.h"
#include "toolStructure.h"
#include "toolObject.h"
#include "toolFence.h"
#include "toolGate.h"
#include "toolPlants.h"
#include "toolDisplay.h"
#include "toolWallBasic.h"
#include "toolWallDungeon.h"
#include "toolNpc.h"
#include "toolEraser.h"
#include "toolTileType.h"
#include "toolRock.h"
#include "toolSave.h"

toolType * toolEmpty::inputHandle(mapTool * mapTool)
{
	//�޴����ٿ��� Ÿ�� �޴��� Ŭ��������
	if (PtInRect(&mapTool->getTileRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolTile();
	}

	//�޴����ٿ��� ���๰ �޴��� Ŭ��������
	if (PtInRect(&mapTool->getStructureRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolStructure();
	}

	//�޴����ٿ��� ������ �޴��� Ŭ��������
	if (PtInRect(&mapTool->getObjectRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolObject();
	}

	//�޴����ٿ��� NPC �޴��� Ŭ��������
	if (PtInRect(&mapTool->getNpcRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolNpc();
	}

	//�޴����ٿ��� ���찳 �޴��� Ŭ��������
	if (PtInRect(&mapTool->getEraserRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolGate(false);
		return new toolEraser();
	}

	//�޴����ٿ��� ���̺� �޴��� Ŭ��������
	if (PtInRect(&mapTool->getSaveRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolSave();
	}

	return nullptr;
}

void toolEmpty::update(mapTool * mapTool)
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

	//saveButton �̹��� �� rc ��Ȱ��ȭ
	mapTool->_saveInput.saveRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
	mapTool->_saveInput.saveButtonRect = RectMake(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
	mapTool->_saveInput.cancelButtonRect = RectMake(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
	mapTool->_saveInput.textInputRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
}

void toolEmpty::enter(mapTool * mapTool)
{
	mapTool->_popUp.img = IMAGEMANAGER->findImage("popUp");

	mapTool->_sampleTile.terrainFrameX = 0;
	mapTool->_sampleTile.terrainFrameY = 0;

	mapTool->_currentTile.x = 0;
	mapTool->_currentTile.y = 0;

	mapTool->setIsExitButton(false);
}

void toolEmpty::render(mapTool * mapTool)
{
}

void toolEmpty::exit(mapTool * mapTool)
{

}
