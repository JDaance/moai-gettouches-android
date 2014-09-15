Because of "stuck" touches in my control intensive game I'm trying this approach of directly getting touches from the latest MotionEvent, bypassing any event order.

You need to add MoaiGetTouches.java to your android host (in the correct package folder), and feed it the latest motion event on each update as so

MoaiActivity.java

```
@Override
public boolean onTouchEvent ( MotionEvent event ) {
	MoaiGetTouches.setLatestMotionEvent(event);
	...
}
```

And then in your render/update loop you need to call the update method before you update the sim

```
	...
    MoaiGetTouches.update();
	Moai.update();
	...
```
