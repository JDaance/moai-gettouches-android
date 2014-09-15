// Copyright (c) 2010-2013 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIGETTOUCHESANDROID_H
#define	MOAIGETTOUCHESANDROID_H

#include <jni.h>

#include <moai-core/headers.h>

struct Touch {
	int idx;
	int x;
	int y;

	Touch(int a, int b, int c): idx(a), x(b), y(c) {};
};

class MOAIGetTouchesAndroid :
	public MOAIGlobalClass < MOAIGetTouchesAndroid, MOAILuaObject > {
private:
	std::vector<Touch>	mTouches;
	std::vector<Touch>	mTouchesPending;

	bool				mHasPendingTouches;

	static int	_getActiveTouches	( lua_State* L );
	static int	_getTouch			( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIGetTouchesAndroid )

			MOAIGetTouchesAndroid				();
			~MOAIGetTouchesAndroid				();

	void 	Update 						();
	void	RegisterLuaClass			( MOAILuaState& state );
	void	SetActiveTouches 			( jobjectArray touches );

};

extern "C" {
	JNIEXPORT void JNICALL Java_com_ziplinegames_moai_MoaiGetTouches_AKUSetActiveTouches ( JNIEnv* env, jclass obj, jobjectArray touches );
}

#endif
