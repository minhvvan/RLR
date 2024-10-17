// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/SkillStructs.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/RLRStruct.h"

const FSkillData FSkillData::EmptySkillData;
const FSkillClass FSkillClass::EmptySkillClass = FSkillClass();

FString FSkillData::ToString() const
{
    FString SkillString;

    auto AppendFloat = [&SkillString](const FString& Name, float Value)
        {
            if (!SkillString.IsEmpty())
                SkillString.Append(TEXT("\n"));

            SkillString.Append(FString::Printf(TEXT("%s = %.2f"), *Name, Value));
        };

    auto AppendInt = [&SkillString](const FString& Name, int32 Value)
        {
            if (!SkillString.IsEmpty())
                SkillString.Append(TEXT("\n"));

            SkillString.Append(FString::Printf(TEXT("%s = %d"), *Name, Value));
        };

    auto AppendString = [&SkillString](const FString& Name, FString Value)
        {
            if (!SkillString.IsEmpty())
                SkillString.Append(TEXT("\n"));

            SkillString.Append(FString::Printf(TEXT("%s = %s"), *Name, *Value));
        };

    /*
        지금은 스킬 디테일 정보를 띠워주는데 사용 중.
        나중에 UI에서 보여줄 정보에 따라 코드를 수정할 예정
    */

    AppendString(TEXT("Name"), Name.ToString());
    AppendString(TEXT("Job"), ECharacterMainJobTypeToString(MainJobType));
    AppendInt(TEXT("Level"), Level);
    AppendString(TEXT("CostType"), UEnum::GetValueAsString(CostType));
    AppendInt(TEXT("Cost"), CostValue);
    AppendFloat(TEXT("CoolTime"), DefaultCoolDown);
    AppendString(TEXT("SkillInfo"), SkillInfo.ToString());

    return SkillString;
}

void FSkillData::MakeSkillData(Protocol::SkillInfo skill) {

    SkillSeq = skill.skillseq();

    Name = FText::FromString(skill.skillname().c_str());

    Level = skill.skilllevel();

    //Cost = skill.cost();

    //CoolTime = skill.cooltime();

    //Cind = skill.skillkind();

    Damage = skill.skillactivestatus().skilldamage();

    Duration = skill.skillactivestatus().skillduration();

    SkillId = skill.skillid();

    SkillIdx = skill.skillidx();

    SkillRange.X = skill.skilldistance() * 20;

    SkillType = static_cast<ESkillType>(skill.skillactivestatus().skilltype());

}

void FSkillClass::MakeSkillData(Protocol::SkillInfo skill)
{
    SkillSeq = skill.skillseq();

    const FSkillClass& OriginData = GameInstance->GetDataManager()->GetSkillResource(SkillSeq);
    if (OriginData == FSkillClass::EmptySkillClass)
        return;

    SkillClass = OriginData.SkillClass;
    SkillImage = OriginData.SkillImage;
}