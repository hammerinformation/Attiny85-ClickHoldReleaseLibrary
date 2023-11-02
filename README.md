# GPIO-Button-Driver


![PHR_GIF](https://github.com/hammerinformation/ue-fps/assets/51826786/8e84d4cb-a346-4ceb-bfcd-ec31ce09ec52)





# Example

```cpp
Button button(PB0);
	button.setButtonPressCallback([]()->void{
		enableRedLed();
		_delay_ms(250);
		PORTB&=~(1<<Red);
	});
	button.setButtonHoldCallback(&enableGreenLed);
	button.setButtonReleaseCallback([&]()->void
	{
		PORTB&=~(1<<Green);
		enableBlueLed();
		_delay_ms(500);
		PORTB&=~(1<<Blue);

		
	});
```

# C++11 

Sets the function to be called when the button is pressed.
```cpp
void setButtonPressCallback(void(*ptr)(void)){
		pressCallback=ptr;
	}
```


Sets the function to be called when the button is held down.
```cpp

	void setButtonHoldCallback(void(*ptr)(void)){
		holdCallback=ptr;
	}
```


Sets the function to be called when the button is released.
```cpp
	void setButtonReleaseCallback(void(*ptr)(void)){
		releaseCallback=ptr;
	}

```


