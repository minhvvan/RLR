// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EffectManager.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UEffectManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	/*
	* 이펙트 생성 
	*	스킬 이펙트
	*		어떤 공격인지에 따라 이펙트 설정. 
	*	피격 이펙트
			피격이 누구인지에 따라 다른 이펙트 설정
	* 이펙트 주기관리
	*	단순 이펙트인지, 오버랩을 해야하는 이펙트인지에 따라 이펙트 기능도 필요하다.
	*	DT 에서 긁어올 수 있는지 체크. 
	* 이펙트 삭제
	*	액터에서 처리하는것이 좋아보임.
	*	
	* 이펙트 DB 에서 긁어오기 
	* 
	* 
	* 이펙트 오버랩 이 단순 나이아가라로 되는지, 액터로만 구성을해야하는지 체크.
	* 
	* 
	*/ 
	

};
