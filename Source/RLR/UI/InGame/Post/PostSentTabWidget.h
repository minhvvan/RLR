#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h" // 스크롤 박스를 포함
#include "PostSentTabWidget.generated.h"

UCLASS()
class RLR_API UPostSentTabWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

public:
    // 서버에서 받은 우편 데이터를 기반으로 버튼을 생성하는 함수
    UFUNCTION()
    void AddSentMailButton(int32 PostId, const FString& ReceiverName, const FString& Subject);

    // 서버로부터 받은 우편들을 표시할 스크롤박스
    UPROPERTY(meta = (BindWidget))
    UScrollBox* SentPostScrollBox;
};
