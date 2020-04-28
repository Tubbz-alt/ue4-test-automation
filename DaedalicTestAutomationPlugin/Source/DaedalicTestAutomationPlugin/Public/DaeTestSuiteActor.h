#pragma once

#include "DaeTestSuiteResult.h"
#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "DaeTestSuiteActor.generated.h"

class ADaeTestActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDaeTestSuiteActorTestSuiteSuccessfulSignature,
                                            ADaeTestSuiteActor*, TestSuite);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDaeTestSuiteActorTestSuiteFailedSignature,
                                            ADaeTestSuiteActor*, TestSuite);

/** Collection of automated tests. */
UCLASS()
class DAEDALICTESTAUTOMATIONPLUGIN_API ADaeTestSuiteActor : public AActor
{
    GENERATED_BODY()

public:
    ADaeTestSuiteActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    /** Runs all tests of this suite, in order. */
    void RunAllTests();

    /** Whether this test suite is currently running. */
    bool IsRunning() const;

    /** Gets the test that is currently running. */
    ADaeTestActor* GetCurrentTest() const;

    /** Results of the whole test suite. */
    FDaeTestSuiteResult GetResult() const;

    /** Event when this test suite has successfully finished all tests. */
    FDaeTestSuiteActorTestSuiteSuccessfulSignature OnTestSuiteSuccessful;

    /** Event when any tests of this test suite have failed. */
    FDaeTestSuiteActorTestSuiteFailedSignature OnTestSuiteFailed;

private:
    /** Tests to run in this level. */
    UPROPERTY(EditInstanceOnly)
    TArray<ADaeTestActor*> Tests;

    /** Whether to automatically run this test suite on BeginPlay in Play In Editor. */
    UPROPERTY(EditInstanceOnly)
    bool bRunInPIE;

    /** Index of the current test. */
    int32 TestIndex;

    /** Time the current test has been running, in seconds. */
    float TestTimeSeconds;

    /** Results of the whole test suite. */
    FDaeTestSuiteResult Result;

    /** Runs the next test in this test suite. */
    void RunNextTest();

    UFUNCTION()
    void OnTestSuccessful(ADaeTestActor* Test);

    UFUNCTION()
    void OnTestFailed(ADaeTestActor* Test, const FString& FailureMessage);
};