
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OpenAIChatManager.generated.h"

//방학때 시도해보기

class FHttpRequestPtr;
class FHttpResponsePtr;

UCLASS()
class OTHERLIFEFARM_API UOpenAIChatManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SendMessageToGPT(const FString& UserMessage);

private:
	FString Apikey;
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Reponse, bool bWasSucceessful);
	
};
