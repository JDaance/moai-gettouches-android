// Copyright (c) 2010-2013 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"

#include <moai-android/moaiext-jni.h>

#include <moai-gettouches-android/MOAIGetTouchesAndroid.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	getActiveTouches
	@text	Returns the IDs of all of the touches currently occurring (for use with getTouch).

	@out	number idx1
	@out	...
	@out	number idxN
*/
int MOAIGetTouchesAndroid::_getActiveTouches ( lua_State* L ) {

    MOAILuaState state( L);
	
	u32 count = MOAIGetTouchesAndroid::Get().mTouches.size();
	if (!lua_checkstack( L, count )) {
		MOAIPrint("Warning: lua stack full for MOAIGetTouchesAndroid::_getActiveTouches");
		return 0;
	}
	
	//MOAIPrint("_getActiveTouches called, touch count is: %d\n", count);

	for ( u32 i = 0; i < count; ++i ) {
		lua_pushnumber ( state, MOAIGetTouchesAndroid::Get().mTouches.at(i).idx);
	}
	return count;
}

//----------------------------------------------------------------//
/**	@name	getTouch
	@text	Checks to see if there are currently touches being made on the screen.

	@in		number id				The ID of the touch.
	@out	number x
	@out	number y
*/
int MOAIGetTouchesAndroid::_getTouch ( lua_State* L ) {

    MOAILuaState state( L);
	
	u32 idx = state.GetValue < u32 >( 1, 0 );

	u32 count = MOAIGetTouchesAndroid::Get().mTouches.size();

	//MOAIPrint("_getTouch called with idx: %d\n", idx);
	
	for ( u32 i = 0; i < count; ++i ) {
		Touch touch = MOAIGetTouchesAndroid::Get().mTouches [ i ];
		//MOAIPrint("Looping touch idx: %d, x: %d, y:%d\n", touch.idx, touch.x, touch.y);
		if (touch.idx == idx) {
			//MOAIPrint("HIT");
			lua_pushnumber ( state, touch.x );
			lua_pushnumber ( state, touch.y );
				
			return 2;			
		}
	}
	return 0;
}

//================================================================//
// MOAIGetTouchesAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIGetTouchesAndroid::MOAIGetTouchesAndroid () {

	RTTI_SINGLE ( MOAILuaObject );

}

//----------------------------------------------------------------//
MOAIGetTouchesAndroid::~MOAIGetTouchesAndroid () {

}

//----------------------------------------------------------------//
void MOAIGetTouchesAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "getActiveTouches",		_getActiveTouches },
		{ "getTouch",				_getTouch },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
// This has to be called in a thread safe manner
void MOAIGetTouchesAndroid::SetActiveTouches ( jobjectArray touches ) {

	JNI_GET_ENV ( jvm, env );

	mTouches.clear();
	mHasPendingTouches = true;

	jsize touchCount = env->GetArrayLength(touches);

	//MOAIPrint("SetActiveTouches called with touch count: %d\n", touchCount);

	for(int i = 0; i < touchCount; ++i){
		jintArray touchJ = (jintArray)env->GetObjectArrayElement(touches, i);
		jint *element = env->GetIntArrayElements(touchJ, 0);

		Touch touch(element[0], element[1], element[2]);
		mTouches.push_back(touch);

		env->ReleaseIntArrayElements(touchJ, element, JNI_ABORT);
		env->DeleteLocalRef(touchJ);
	}
}


//================================================================//
// JNI
//================================================================//

//----------------------------------------------------------------//

extern "C" {
	// This has to be called in a thread safe manner
	JNIEXPORT void JNICALL Java_com_ziplinegames_moai_MoaiGetTouches_AKUSetActiveTouches ( JNIEnv* env, jclass obj, jobjectArray touches ) {

		MOAIGetTouchesAndroid::Get ().SetActiveTouches (touches);
	}
}