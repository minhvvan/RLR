// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/Quest/GuildQuestUI.h"
#include "UI/InGame/Guild/Quest/GuildQuestCardUI.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"

#include "GameManager/GameManager.h"
#include "GameManager/GuildManager.h"

void UGuildQuestUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitQuestBoard();
}
/* Quest*/
void UGuildQuestUI::RefreshUI()
{
    if(CreatedQuestCards.Num() == 0) return;

	const TArray<FGuildQuest>& GuildQuestData = GameInstance->GetGuildManager()->GetGuildQuestData();
	if(GuildQuestData.Num() == 0) return;

	for (int32 i = 0; i < CreatedQuestCards.Num(); i++)
	{
		if (CreatedQuestCards[i] && GuildQuestData.IsValidIndex(i))
		{
            CreatedQuestCards[i]->SetColorAsQuestType(GuildQuestData[i]);
		}
	}
}
/* 퀘스트 보드에 퀘스트카드 랜덤 배치(서로 겹치지않음), 퀘스트카드 정보 */
void UGuildQuestUI::InitQuestBoard()
{
	if(!GuildQuestCardUI || !QuestBoard) return;

	QuestBoard->ClearChildren();

	const int32 QuestCount = 8;
	TArray<FVector2D> OccupiedPosition;
	/* 보드 크기 가져오기 */
	const FVector2D BoardSize(QuestBoard->GetDesiredSize().X, QuestBoard->GetDesiredSize().Y);
	const FVector2D CardSize(150.0f, 200.0f);
	/* 겹침 방지 최대 시도  횟수*/
	const int32 MaxRetries = 50;

    for (int32 i = 0; i < QuestCount; i++)
    {
        // 동적으로 UGuildQuestCardUI 생성
        UGuildQuestCardUI* NewCard = CreateWidget<UGuildQuestCardUI>(this, GuildQuestCardUI);
        if (!NewCard) continue;

        // 랜덤 위치 생성
        FVector2D RandomPosition;
        bool bValidPosition = false;
        int32 RetryCount = 0;

        while (!bValidPosition && RetryCount < MaxRetries)
        {
            RandomPosition.X = FMath::RandRange(0.0f, static_cast<float>(BoardSize.X - CardSize.X));
            RandomPosition.Y = FMath::RandRange(0.0f, static_cast<float>(BoardSize.Y - CardSize.Y));

            // 겹치는지 확인
            bValidPosition = true;
            for (const FVector2D& UsedPosition : OccupiedPosition)
            {
                // 겹침 방지 검사 (X, Y 각각의 거리를 고려)
                if (FMath::Abs(RandomPosition.X - UsedPosition.X) < CardSize.X &&
                    FMath::Abs(RandomPosition.Y - UsedPosition.Y) < CardSize.Y)
                {
                    bValidPosition = false;
                    break;
                }
            }

            RetryCount++;
        }

        // 위치가 유효하면 추가
        if (bValidPosition)
        {
            OccupiedPosition.Add(RandomPosition);

            // Slot 설정
            UCanvasPanelSlot* NewSlot = Cast<UCanvasPanelSlot>(QuestBoard->AddChild(NewCard));
            if (NewSlot)
            {
                NewSlot->SetPosition(RandomPosition);
                NewSlot->SetSize(CardSize); // 카드 크기 설정
            }

            // 초기화 시 추가로 사용 가능
            CreatedQuestCards.Add(NewCard);
        }
    }

}