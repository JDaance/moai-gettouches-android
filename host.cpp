// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-gettouches-android/host.h>
#include <moai-gettouches-android/MOAIGetTouchesAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
static bool getTouchesImpossibleCondition = rand() < 0;
void MOAIGetTouchesAndroidAppInitialize () {
	// trick compiler/linker to include function
	if (getTouchesImpossibleCondition) {
		Java_com_ziplinegames_moai_MoaiGetTouches_AKUSetActiveTouches(NULL, NULL, NULL);
	}
}

//----------------------------------------------------------------//
void MOAIGetTouchesAndroidAppFinalize () {
}

//----------------------------------------------------------------//
void MOAIGetTouchesAndroidContextInitialize () {
	REGISTER_LUA_CLASS ( MOAIGetTouchesAndroid )
}