#include "stdafx.h"
#include "pet.h"
#include "petStand.h"
#include "petAttack.h"
#include "petHurt.h"
#include "petDefense.h"
#include "petDead.h"
#include "petRun.h"
#include "petCatch.h"

petState * petStand::inputHandle(pet * pet)
{
	if (pet->getIsMove() == true)
	{
		pet->setEnumPetState(PET_RUN);
		return new petRun();
	}

	if (pet->getEnumPetState() == PET_ATTACK) 	return new petAttack();
	if (pet->getEnumPetState() == PET_DEAD) 	return new petDead();
	if (pet->getEnumPetState() == PET_HURT) 	return new petHurt();
	if (pet->getEnumPetState() == PET_DEFENSE) 	return new petDefense();
	if (pet->getEnumPetState() == PET_CATCHED)	return new petCatch();

	return nullptr;
}

void petStand::update(pet * pet)
{
	//플레이어 frame에 맞춘 방향 설정
	pet->setCurrentFrameY((int)(pet->getPetDirection()));

	updatePetImage(pet);
}

void petStand::enter(pet * pet)
{
	setPetImage(pet);
	pet->setCurrentFrameX(0);
}

void petStand::exit(pet * pet)
{
}

void petStand::setPetImage(pet * pet)
{
	if (pet->getPetName() == DURI)
	{
		pet->setPetRenderName("duri_stand");
		pet->setImage(IMAGEMANAGER->findImage("duri_stand"));

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
		pet->setPetRenderName("spottedUri_stand");
		pet->setImage(IMAGEMANAGER->findImage("spottedUri_stand"));

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
		pet->setPetRenderName("uri_stand");
		pet->setImage(IMAGEMANAGER->findImage("uri_stand"));

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
		pet->setPetRenderName("mamonas_stand");
		pet->setImage(IMAGEMANAGER->findImage("mamonas_stand"));

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
		pet->setPetRenderName("manmo_stand");
		pet->setImage(IMAGEMANAGER->findImage("manmo_stand"));

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
		pet->setPetRenderName("manmor_stand");
		pet->setImage(IMAGEMANAGER->findImage("manmor_stand"));

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
		pet->setPetRenderName("mogaros_stand");
		pet->setImage(IMAGEMANAGER->findImage("mogaros_stand"));

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
		pet->setPetRenderName("ogaros_stand");
		pet->setImage(IMAGEMANAGER->findImage("ogaros_stand"));

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
		pet->setPetRenderName("gorgor_stand");
		pet->setImage(IMAGEMANAGER->findImage("gorgor_stand"));

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
		pet->setPetRenderName("verga_stand");
		pet->setImage(IMAGEMANAGER->findImage("verga_stand"));

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
		pet->setPetRenderName("veruru_stand");
		pet->setImage(IMAGEMANAGER->findImage("veruru_stand"));

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
		pet->setPetRenderName("banboro_stand");
		pet->setImage(IMAGEMANAGER->findImage("banboro_stand"));

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
		pet->setPetRenderName("bangino_stand");
		pet->setImage(IMAGEMANAGER->findImage("bangino_stand"));

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
		pet->setPetRenderName("burdon_stand");
		pet->setImage(IMAGEMANAGER->findImage("burdon_stand"));

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
		pet->setPetRenderName("ribino_stand");
		pet->setImage(IMAGEMANAGER->findImage("ribino_stand"));

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
		pet->setPetRenderName("yangiro_stand");
		pet->setImage(IMAGEMANAGER->findImage("yangiro_stand"));

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
		pet->setPetRenderName("nornor_stand");
		pet->setImage(IMAGEMANAGER->findImage("nornor_stand"));

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
		pet->setPetRenderName("golros_stand");
		pet->setImage(IMAGEMANAGER->findImage("golros_stand"));

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

void petStand::updatePetImage(pet * pet)
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
