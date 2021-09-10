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

toolType * toolNpc::inputHandle(mapTool * mapTool)
{
	//������ ��ư�� �������� ���� ����
	if (PtInRect(&mapTool->_popUp.exitButtonRc,
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolNpc(false);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new toolEmpty();
	}

	//�޴����ٿ��� ���๰ �޴��� Ŭ��������
	if (PtInRect(&mapTool->getStructureRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolNpc(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolStructure();
	}

	//�޴����ٿ��� Ÿ�� �޴��� Ŭ��������
	if (PtInRect(&mapTool->getTileRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolNpc(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolTile();
	}

	//�޴����ٿ��� ������ �޴��� Ŭ��������
	if (PtInRect(&mapTool->getObjectRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolNpc(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolObject();
	}

	//�޴����ٿ��� ���찳 �޴��� Ŭ��������
	if (PtInRect(&mapTool->getEraserRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolNpc(false);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new toolEraser();
	}

	//�޴����ٿ��� ���̺� �޴��� Ŭ��������
	if (PtInRect(&mapTool->getSaveRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolNpc(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolSave();
	}

	return nullptr;
}

void toolNpc::update(mapTool * mapTool)
{
	mapTool->_popUp.PopUpRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - mapTool->_popUp.img->getWidth(),
		CAMERAMANAGER->getCameraBOTTOM() - mapTool->_popUp.img->getHeight() - 24,
		mapTool->_popUp.img->getWidth(), mapTool->_popUp.img->getHeight());

	mapTool->_popUp.exitButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 146, CAMERAMANAGER->getCameraBOTTOM() - 73,
		124, 27);

	mapTool->_popUp.leftButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 616, CAMERAMANAGER->getCameraBOTTOM() - 336 - 24,
		32, 32);

	mapTool->_popUp.upButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 336, CAMERAMANAGER->getCameraBOTTOM() - 582 - 24,
		32, 32);

	mapTool->_popUp.rightButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 54, CAMERAMANAGER->getCameraBOTTOM() - 336 - 24,
		32, 32);

	mapTool->_popUp.downButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 336, CAMERAMANAGER->getCameraBOTTOM() - 54 - 24,
		32, 32);

	mapTool->_sampleTile.rcTile = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 310, CAMERAMANAGER->getCameraBOTTOM() - 310 - 24,
		100, 100);

	mapTool->_toolName.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 320, CAMERAMANAGER->getCameraBOTTOM() - 610 - 24,
		200, 45);

	//����Ʈ ����Ʈ ��ư ���ֱ�
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

void toolNpc::enter(mapTool * mapTool)
{
	mapTool->_popUp.img = IMAGEMANAGER->findImage("popUp");
	mapTool->_sampleTile.img = IMAGEMANAGER->findImage("npc");
	mapTool->_currentTile.img = IMAGEMANAGER->findImage("npc");
	mapTool->_toolName.img = IMAGEMANAGER->findImage("toolName");
	mapTool->setIsExitButton(true);
	mapTool->setIsToolNpc(true);

	mapTool->_sampleTile.terrainFrameX = 0;
	mapTool->_sampleTile.terrainFrameY = 0;

	mapTool->_toolName.currentFrameX = 10;
	mapTool->_toolName.currentFrameY = 0;
}

void toolNpc::render(mapTool * mapTool)
{
	mapTool->_popUp.img->render(getMemDC(), mapTool->_popUp.PopUpRc.left, mapTool->_popUp.PopUpRc.top);

	mapTool->_sampleTile.img->frameRender(getMemDC(), mapTool->_sampleTile.rcTile.left, mapTool->_sampleTile.rcTile.top,
		mapTool->_sampleTile.terrainFrameX, mapTool->_sampleTile.terrainFrameY);

	mapTool->_toolName.img->frameRender(getMemDC(), mapTool->_toolName.rc.left, mapTool->_toolName.rc.top,
		mapTool->_toolName.currentFrameX, mapTool->_toolName.currentFrameY);
}

void toolNpc::exit(mapTool * mapTool)
{

}