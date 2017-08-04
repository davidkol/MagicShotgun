// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrollingGuardComp.h"


TArray<AActor*> UPatrollingGuardComp::GetPatrolPoints() const
{
	return PatrolPoints;
}

