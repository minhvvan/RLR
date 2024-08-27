#pragma once

#include "CoreMinimal.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"

#include "RLRToolWidget.generated.h"

/**

	RLR 작업용 툴.
		
		현재 기능

			1.치트

			2.데이터 테이블 추출(예정)
		

 */
UCLASS(BlueprintType)
class RLRTOOL_API URLRToolWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	URLRToolWidget();
	~URLRToolWidget();
};
