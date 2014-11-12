package com.ziplinegames.moai;

import android.view.MotionEvent;

public class MoaiGetTouches {	
	private final static int IDX 	= 0;	
	private final static int X 		= 1;	
	private final static int Y 		= 2;

    private static MotionEvent latestMotionEvent;
    private static Object lockObject = new Object();

	private static native void AKUSetActiveTouches(int[][] touches);

	public static void setLatestMotionEvent(MotionEvent event) {
        // synchronized since events seem to be posted at the same time (rarely)
        synchronized (MoaiGetTouches.class) {
            if (latestMotionEvent != null) latestMotionEvent.recycle();
            latestMotionEvent = MotionEvent.obtain(event);
        }
	}

    /**
     * MotionEvent contains all current pointers, but on a UP event the pointer
     * associated with UP will have been released so don't pass that one to native
     */
    public static void update() {
        MotionEvent event;
        // synchronized copy since events seem to be posted while updating
        synchronized (MoaiGetTouches.class) {
            if (latestMotionEvent == null) return;
            event = MotionEvent.obtain(latestMotionEvent);
        }

        int skipIndex = -1;
        int action = event.getActionMasked();
        int originalPointerCount = event.getPointerCount();
        int pointerCount = originalPointerCount;
        if (action == MotionEvent.ACTION_UP || action == MotionEvent.ACTION_POINTER_UP) {
            skipIndex = event.getActionIndex();
            pointerCount -= 1;
        }
        int[][] touches = new int[pointerCount][3];
        int count = 0;
        for (int i = 0; i < event.getPointerCount(); ++i) {
            if (i != skipIndex) {
                try {
                    int idx = event.getPointerId(i);
                    touches[count][IDX] = idx; // count == 1, touches.length == 1
                    touches[count][X] = Math.round(event.getX(i));
                    touches[count][Y] = Math.round(event.getY(i));
                    ++count;
                } catch (ArrayIndexOutOfBoundsException ae) {
                    String message = String.format(
                            "Out of bounds with skipIndex: %d, originalPointerCount: %d, pointerCount: %d, event.getPointerCount(): %d, count: %d, touches.length: %d, i: %d",
                            skipIndex, originalPointerCount, pointerCount, event.getPointerCount(), count, touches.length, i);
                    throw new RuntimeException(message, ae);
                }
            }
        }
        AKUSetActiveTouches(touches);
        event.recycle();
    }
}
