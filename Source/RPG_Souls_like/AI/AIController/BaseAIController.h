// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BaseAIController.generated.h"

/**
 *
 */
UCLASS()
class RPG_SOULS_LIKE_API ABaseAIController : public AAIController
{
    GENERATED_BODY()

public:
    ABaseAIController(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());

    virtual void BeginPlay() override;

    //get blackboard component
    class UBlackboardComponent* GetBlackboard() const;

    //return team id
    virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }

    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

    //blackboard
    //class UBaseBlackboardData* Blackboard;

    virtual void OnPossess(APawn* const InPawn) override;

    virtual void OnUnPossess() override;

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
        //behavior tree component
        class UBehaviorTreeComponent* BehaviorTreeComponent;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
        //behavior tree
        class UBehaviorTree* BehaviorTree;

    //blackboard component
    class UBlackboardComponent* BlackboardComponent;

    //sight sense
    class UAISenseConfig_Sight* SightConfig;

    //UFUNCTION()
    //   void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);

    UFUNCTION()
        void OnUpdated(TArray<AActor*> const& UpdatedActors);

   virtual void SetupPerceptionSystem();

   // team id
   FGenericTeamId TeamId;
    

};
