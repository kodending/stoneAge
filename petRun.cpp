#include "stdafx.h"
#include "pet.h"
#include "petStand.h"
#include "petAttack.h"
#include "petHurt.h"
#include "petDefense.h"
#include "petDead.h"
#include "petRun.h"
#include "petCatch.h"

petState * petRun::inputHandle(pet * pet)
{
	if (pet->getIsMove() == false)
	{
		pet->setEnumPetState(PET_STAND);
		return new petStand();
	}

	if (pet->getEnumPetState() == PET_ATTACK) 	return new petAttack();
	if (pet->getEnumPetState() == PET_DEAD) 	return new petDead();
	if (pet->getEnumPetState() == PET_HURT) 	return new petHurt();
	if (pet->getEnumPetState() == PET_DEFENSE) 	return new petDefense();
	if (pet->getEnumPetState() == PET_CATCHED)	return new petCatch();

	return nullptr;
}

void petRun::update(pet * pet)
{
	//플레이어 frame에 맞춘 방향 설정
	pet->setCurrentFrameY((int)(pet->getPetDirection()));
	updatePetImage(pet);
}

void petRun::enter(pet * pet)
{
	setPetImage(pet);
	pet->setCurrentFrameX(0);
}

void petRun::exit(pet * pet)
{
}

void petRun::setPetImage(pet * pet)
{
	if (pet->getPetName() == DURI)
	{
		pet->setPetRenderName("duri_run");
		pet->setImage(IMAGEMANAGER->findImage("duri_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(5);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-10.5f);
		}
	}

	if (pet->getPetName() == SPOTTEDURI)
	{
		pet->setPetRenderName("spottedUri_run");
		pet->setImage(IMAGEMANAGER->findImage("spottedUri_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(5);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-10.5);
		}
	}

	if (pet->getPetName() == URI)
	{
		pet->setPetRenderName("uri_run");
		pet->setImage(IMAGEMANAGER->findImage("uri_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(5);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-10.5f);
		}
	}

	if (pet->getPetName() == MAMONAS)
	{
		pet->setPetRenderName("mamonas_run");
		pet->setImage(IMAGEMANAGER->findImage("mamonas_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(-10);
			pet->setImageMoveY(-35.5f);
		}
	}

	if (pet->getPetName() == MANMO)
	{
		pet->setPetRenderName("manmo_run");
		pet->setImage(IMAGEMANAGER->findImage("manmo_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(-10);
			pet->setImageMoveY(-35.5f);
		}
	}

	if (pet->getPetName() == MANMOR)
	{
		pet->setPetRenderName("manmor_run");
		pet->setImage(IMAGEMANAGER->findImage("manmor_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(-10);
			pet->setImageMoveY(-35.5f);
		}
	}

	if (pet->getPetName() == MOGAROS)
	{
		pet->setPetRenderName("mogaros_run");
		pet->setImage(IMAGEMANAGER->findImage("mogaros_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-23.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == OGAROS)
	{
		pet->setPetRenderName("ogaros_run");
		pet->setImage(IMAGEMANAGER->findImage("ogaros_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-23.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == GORGOR)
	{
		pet->setPetRenderName("gorgor_run");
		pet->setImage(IMAGEMANAGER->findImage("gorgor_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(-8);
			pet->setImageMoveY(-15.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-15.5f);
		}
	}

	if (pet->getPetName() == VERGA)
	{
		pet->setPetRenderName("verga_run");
		pet->setImage(IMAGEMANAGER->findImage("verga_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(-8);
			pet->setImageMoveY(-15.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-15.5f);
		}
	}

	if (pet->getPetName() == VERURU)
	{
		pet->setPetRenderName("veruru_run");
		pet->setImage(IMAGEMANAGER->findImage("veruru_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(-8);
			pet->setImageMoveY(-15.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-15.5f);
		}
	}

	if (pet->getPetName() == BANBORO)
	{
		pet->setPetRenderName("banboro_run");
		pet->setImage(IMAGEMANAGER->findImage("banboro_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == BANGINO)
	{
		pet->setPetRenderName("bangino_run");
		pet->setImage(IMAGEMANAGER->findImage("bangino_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == BURDON)
	{
		pet->setPetRenderName("burdon_run");
		pet->setImage(IMAGEMANAGER->findImage("burdon_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == RIBINO)
	{
		pet->setPetRenderName("ribino_run");
		pet->setImage(IMAGEMANAGER->findImage("ribino_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == YANGIRO)
	{
		pet->setPetRenderName("yangiro_run");
		pet->setImage(IMAGEMANAGER->findImage("yangiro_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == NORNOR)
	{
		pet->setPetRenderName("nornor_run");
		pet->setImage(IMAGEMANAGER->findImage("nornor_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(-8);
			pet->setImageMoveY(-15.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-15.5f);
		}
	}

	if (pet->getPetName() == GOLROS)
	{
		pet->setPetRenderName("golros_run");
		pet->setImage(IMAGEMANAGER->findImage("golros_run"));

		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-23.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}
	}

}

void petRun::updatePetImage(pet * pet)
{
	if (pet->getPetName() == DURI)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(5);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-10.5f);
		}
	}

	if (pet->getPetName() == SPOTTEDURI)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(5);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-10.5);
		}
	}

	if (pet->getPetName() == URI)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(5);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-10.5f);
		}
	}

	if (pet->getPetName() == MAMONAS)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(-10);
			pet->setImageMoveY(-35.5f);
		}
	}

	if (pet->getPetName() == MANMO)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(-10);
			pet->setImageMoveY(-35.5f);
		}
	}

	if (pet->getPetName() == MANMOR)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-10.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(-10);
			pet->setImageMoveY(-35.5f);
		}
	}

	if (pet->getPetName() == MOGAROS)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-23.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == OGAROS)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-23.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == GORGOR)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(-8);
			pet->setImageMoveY(-15.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-15.5f);
		}
	}

	if (pet->getPetName() == VERGA)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(-8);
			pet->setImageMoveY(-15.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-15.5f);
		}
	}

	if (pet->getPetName() == VERURU)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(-8);
			pet->setImageMoveY(-15.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-15.5f);
		}
	}

	if (pet->getPetName() == BANBORO)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == BANGINO)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == BURDON)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == RIBINO)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == YANGIRO)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(16);
			pet->setImageMoveY(-30.5f);
		}
	}

	if (pet->getPetName() == NORNOR)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(-8);
			pet->setImageMoveY(-15.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-15.5f);
		}
	}

	if (pet->getPetName() == GOLROS)
	{
		if (pet->getPetDirection() == DIR_FIVE)
		{
			pet->setImageMoveX(8);
			pet->setImageMoveY(-23.5f);
		}

		if (pet->getPetDirection() == DIR_ELEVEN)
		{
			pet->setImageMoveX(0);
			pet->setImageMoveY(-30.5f);
		}
	}
}
