// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SpaceInvaders_FDSEditorTarget : TargetRules
{
	public SpaceInvaders_FDSEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "SpaceInvaders_FDS" } );
	}
}
