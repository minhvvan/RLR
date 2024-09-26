#include "PostSentTabWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UPostSentTabWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 초기화 작업이 필요하다면 이곳에 추가
}

void UPostSentTabWidget::AddSentMailButton(int32 PostId, const FString& ReceiverName, const FString& Subject)
{
    if (!SentPostScrollBox) return;

    // 새로 생성할 우편 버튼을 위한 위젯 생성
    UButton* NewMailButton = NewObject<UButton>(SentPostScrollBox);

    // 우편 정보 표시를 위한 텍스트블럭 생성
    UTextBlock* ButtonText = NewObject<UTextBlock>(NewMailButton);
    ButtonText->SetText(FText::FromString(FString::Printf(TEXT("To: %s - %s"), *ReceiverName, *Subject)));

    // 버튼에 텍스트를 추가, 스크롤 박스에 버튼 추가
    NewMailButton->AddChild(ButtonText);
    SentPostScrollBox->AddChild(NewMailButton);

    /* 버튼에 PostId를 연결할 이벤트나 로직 추가 가능 (버튼 누르면 우편 상세내용 나와야함) */
}