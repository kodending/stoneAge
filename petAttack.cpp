#include "stdafx.h"
#include "pet.h"
#include "petStand.h"
#include "petAttack.h"
#include "petHurt.h"
#include "petDefense.h"
#include "petDead.h"
#include "petRun.h"
#include "petCatch.h"

petState * petAttack::inputHandle(pet * pet)
{
	if (pet->getIsMove() == true)
	{
		pet->setEnumPetState(PET_RUN);
		return new petRun();
	}

	if (pet->getEnumPetState() == PET_DEAD) 	return new petDead();
	if (pet->getEnumPetState() == PET_HURT) 	return new petHurt();
	if (pet->getEnumPetState() == PET_DEFENSE) 	return new petDefense();
	if (pet->getEnumPetState() == PET_STAND)    return new petStand();
	if (pet->getEnumPetState() == PET_CATCHED)	return new petCatch();

	return nullptr;
}

void petAttack::update(pet * pet)
{
	//플레이어 frame에 맞춘 방향 설정
	pet->setCurrentFrameY((int)(pet->getPetDirection()));
	updatePetImage(pet);

	if (_isSound1 == false)
	{
		if (pet->getPetName() == DURI) SOUNDMANAGER->play("duri", 0.4f);
		if (pet->getPetName() == URI) SOUNDMANAGER->play("duri", 0.4f);
		if (pet->getPetName() == SPOTTEDURI) SOUNDMANAGER->play("duri", 0.4f);
		if (pet->getPetName() == MAMONAS) SOUNDMANAGER->play("manmo", 0.4f);
		if (pet->getPetName() == MANMO) SOUNDMANAGER->play("manmo", 0.4f);
		if (pet->getPetName() == MANMOR) SOUNDMANAGER->play("manmo", 0.4f);
		if (pet->getPetName() == GORGOR) SOUNDMANAGER->play("verga", 0.4f);
		if (pet->getPetName() == NORNOR) SOUNDMANAGER->play("verga", 0.4f);
		if (pet->getPetName() == VERURU) SOUNDMANAGER->play("verga", 0.4f);
		if (pet->getPetName() == VERGA) SOUNDMANAGER->play("verga", 0.4f);
		if (pet->getPetName() == MOGAROS) SOUNDMANAGER->play("one_heat", 0.4f);
		if (pet->getPetName() == OGAROS) SOUNDMANAGER->play("one_heat", 0.4f);
		if (pet->getPetName() == BURDON) SOUNDMANAGER->play("one_heat", 0.4f);
		if (pet->getPetName() == BANGINO) SOUNDMANAGER->play("one_heat", 0.4f);
		if (pet->getPetName() == RIBINO) SOUNDMANAGER->play("one_heat", 0.4f);
		if (pet->getPetName() == BANBORO) SOUNDMANAGER->play("one_heat", 0.4f);
		if (pet->getPetName() == YANGIRO) SOUNDMANAGER->play("one_heat", 0.4f);
		_isSound1 = true;
	}

}

void petAttack::enter(pet * pet)
{
	setPetImage(pet);
	pet->setCurrentFrameX(0);
	_isSound1 = false;
	_isSound2 = false;
	_isSound3 = false;
}

void petAttack::exit(pet * pet)
{
}

void petAttack::setPetImage(pet * pet)
{
	if (pet->getPetName() == DURI)
	{
		pet->setPetRenderName("duri_attack");
		pet->setImage(IMAGEMANAGER->findImage("duri_attack"));

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
		pet->setPetRenderName("spottedUri_attack");
		pet->setImage(IMAGEMANAGER->findImage("spottedUri_attack"));

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
		pet->setPetRenderName("uri_attack");
		pet->setImage(IMAGEMANAGER->findImage("uri_attack"));

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
		pet->setPetRenderName("mamonas_attack");
		pet->setImage(IMAGEMANAGER->findImage("mamonas_attack"));

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
		pet->setPetRenderName("manmo_attack");
		pet->setImage(IMAGEMANAGER->findImage("manmo_attack"));

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
		pet->setPetRenderName("manmor_attack");
		pet->setImage(IMAGEMANAGER->findImage("manmor_attack"));

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
		pet->setPetRenderName("mogaros_attack");
		pet->setImage(IMAGEMANAGER->findImage("mogaros_attack"));

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
		pet->setPetRenderName("ogaros_attack");
		pet->setImage(IMAGEMANAGER->findImage("ogaros_attack"));

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
		pet->setPetRenderName("gorgor_attack");
		pet->setImage(IMAGEMANAGER->findImage("gorgor_attack"));

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
		pet->setPetRenderName("verga_attack");
		pet->setImage(IMAGEMANAGER->findImage("verga_attack"));

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
		pet->setPetRenderName("veruru_attack");
		pet->setImage(IMAGEMANAGER->findImage("veruru_attack"));

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
		pet->setPetRenderName("banboro_attack");
		pet->setImage(IMAGEMANAGER->findImage("banboro_attack"));

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
		pet->setPetRenderName("bangino_attack");
		pet->setImage(IMAGEMANAGER->findImage("bangino_attack"));

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
		pet->setPetRenderName("burdon_attack");
		pet->setImage(IMAGEMANAGER->findImage("burdon_attack"));

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
		pet->setPetRenderName("ribino_attack");
		pet->setImage(IMAGEMANAGER->findImage("ribino_attack"));

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
		pet->setPetRenderName("yangiro_attack");
		pet->setImage(IMAGEMANAGER->findImage("yangiro_attack"));

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
		pet->setPetRenderName("nornor_attack");
		pet->setImage(IMAGEMANAGER->findImage("nornor_attack"));

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
		pet->setPetRenderName("golros_attack");
		pet->setImage(IMAGEMANAGER->findImage("golros_attack"));

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

void petAttack::updatePetImage(pet * pet)
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
