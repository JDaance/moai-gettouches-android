package com.ziplinegames.moai;

import android.view.MotionEvent;

public class MoaiGetTouches {	
	private final static int IDX 	= 0;	
	private final static int X 		= 1;	
	private final static int Y 		= 2;

    private static MotionEvent latestMotionEvent;
    private static Object lockObject = new Object();

	private static native void AKUSetActiveTouches(int[][] touches);

    // synchronized since events seem to be posted at the same time (rarely)
	public static synchronized void setLatestMotionEvent(MotionEvent event) {
        if (latestMotionEvent != null) latestMotionEvent.recycle();
        latestMotionEvent = MotionEvent.obtain(event);
	}

    /**
     * MotionEvent contains all current pointers, but on a UP event the pointer
     * associated with UP will have been released so don't pass that one to native
     */
    public static void update() {
        MotionEvent event = latestMotionEvent;
        if (event == null) return;

        int skipIndex = -1;
        int action = event.getActionMasked();
        if (action == MotionEvent.ACTION_UP || action == MotionEvent.ACTION_POINTER_UP) {
            skipIndex = event.getActionIndex();
        }
        int pointerCount = event.getPointerCount() - (skipIndex != -1 ? 1 : 0);
        int[][] touches = new int[pointerCount][3];
        int count = 0;
        for (int i = 0; i < event.getPointerCount(); ++i) {
            if (i != skipIndex) {
                int idx = event.getPointerId(i);
                touches[count][IDX] = idx;
                touches[count][X] = Math.round(event.getX(i));
                touches[count][Y] = Math.round(event.getY(i));
                ++count;
            }
        }
        AKUSetActiveTouches(touches);
    }
}
