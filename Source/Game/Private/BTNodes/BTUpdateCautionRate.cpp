// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNodes/BTUpdateCautionRate.h"

UBTUpdateCautionRate::UBTUpdateCautionRate() {
	NodeName = "Update Value of Caution";
}

EBTNodeResult::Type UBTUpdateCautionRate::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	return EBTNodeResult::Type();
}

FString UBTUpdateCautionRate::GetStaticDescription() const
{
	return FString();
}
