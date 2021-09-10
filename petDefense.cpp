#include "stdafx.h"
#include "pet.h"
#include "petStand.h"
#include "petAttack.h"
#include "petHurt.h"
#include "petDefense.h"
#include "petDead.h"
#include "petRun.h"
#include "petCatch.h"

petState * petDefense::inputHandle(pet * pet)
{
	if (pet->getIsMove() == true)
	{
		pet->setEnumPetState(PET_RUN);
		return new petRun();
	}

	if (pet->getEnumPetState() == PET_ATTACK) 	return new petAttack();
	if (pet->getEnumPetState() == PET_DEAD) 	return new petDead();
	if (pet->getEnumPetState() == PET_HURT) 	return new petHurt();
	if (pet->getEnumPetState() == PET_STAND)    return new petStand();
	if (pet->getEnumPetState() == PET_CATCHED)	return new petCatch();

	return nullptr;
}

void petDefense::update(pet * pet)
{
	//플레이어 frame에 맞춘 방향 설정
	pet->setCurrentFrameY((int)(pet->getPetDirection()));

	updatePetImage(pet);
}

void petDefense::enter(pet * pet)
{
	setPetImage(pet);
	pet->setCurrentFrameX(0);
}

void petDefense::exit(pet * pet)
{
}

void petDefense::setPetImage(pet * pet)
{
	if (pet->getPetName() == DURI)
	{
		pet->setPetRenderName("duri_defense");
		pet->setImage(IMAGEMANAGER->findImage("duri_defense"));

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
		pet->setPetRenderName("spottedUri_defense");
		pet->setImage(IMAGEMANAGER->findImage("spottedUri_defense"));

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
		pet->setPetRenderName("uri_defense");
		pet->setImage(IMAGEMANAGER->findImage("uri_defense"));

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
		pet->setPetRenderName("mamonas_defense");
		pet->setImage(IMAGEMANAGER->findImage("mamonas_defense"));

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
		pet->setPetRenderName("manmo_defense");
		pet->setImage(IMAGEMANAGER->findImage("manmo_defense"));

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
		pet->setPetRenderName("manmor_defense");
		pet->setImage(IMAGEMANAGER->findImage("manmor_defense"));

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
		pet->setPetRenderName("mogaros_defense");
		pet->setImage(IMAGEMANAGER->findImage("mogaros_defense"));

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
		pet->setPetRenderName("ogaros_defense");
		pet->setImage(IMAGEMANAGER->findImage("ogaros_defense"));

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
		pet->setPetRenderName("gorgor_defense");
		pet->setImage(IMAGEMANAGER->findImage("gorgor_defense"));

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
		pet->setPetRenderName("verga_defense");
		pet->setImage(IMAGEMANAGER->findImage("verga_defense"));

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
		pet->setPetRenderName("veruru_defense");
		pet->setImage(IMAGEMANAGER->findImage("veruru_defense"));

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
		pet->setPetRenderName("banboro_defense");
		pet->setImage(IMAGEMANAGER->findImage("banboro_defense"));

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
		pet->setPetRenderName("bangino_defense");
		pet->setImage(IMAGEMANAGER->findImage("bangino_defense"));

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
		pet->setPetRenderName("burdon_defense");
		pet->setImage(IMAGEMANAGER->findImage("burdon_defense"));

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
		pet->setPetRenderName("ribino_defense");
		pet->setImage(IMAGEMANAGER->findImage("ribino_defense"));

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
		pet->setPetRenderName("yangiro_defense");
		pet->setImage(IMAGEMANAGER->findImage("yangiro_defense"));

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
		pet->setPetRenderName("nornor_defense");
		pet->setImage(IMAGEMANAGER->findImage("nornor_defense"));

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
		pet->setPetRenderName("golros_defense");
		pet->setImage(IMAGEMANAGER->findImage("golros_defense"));

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

void petDefense::updatePetImage(pet * pet)
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
