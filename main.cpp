#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

class Button{
	void(*pressCallback)(void) ;
	void(*holdCallback)(void) ;
	void(*releaseCallback)(void) ;
	bool isClicked=false;
	unsigned char pin;

	public:
	Button(const unsigned char& pin) : pin(pin) {}
	void setButtonPressCallback(void(*ptr)(void)){
		pressCallback=ptr;
	}
	void setButtonHoldCallback(void(*ptr)(void)){
		holdCallback=ptr;
	}
	void setButtonReleaseCallback(void(*ptr)(void)){
		releaseCallback=ptr;
	}
	void setPin(const unsigned char& pin){
		Button::pin=pin;
	}
	bool check(){
		const bool b = ((PINB & (1<<pin)) == 0);
		if(isClicked &&!b){
			isClicked=false;

			releaseCallback();
		}
		if(!b){
			return false;
		}
		if(b&&!isClicked){
			isClicked=true;
			pressCallback();


		}
		if(isClicked){
			holdCallback();

		}
		
		
		
		
		return b;
	}
	
};
#define Blue PB4
#define Green PB5
#define Red PB2

void enableRedLed(void);
void enableGreenLed(void);
void enableBlueLed(void);


int main(void)
{
	
	DDRB|=(1<<Red);
	DDRB|=(1<<Green);
	DDRB|=(1<<Blue);

	DDRB&=~(1<<PB0);
	PORTB|=(1<<PB0);
	
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
	
	while (true)
	{
		
		button.check();
		
	}
	return 0;

}



void enableRedLed(){
	PORTB |=(1<<Red);
}
void enableBlueLed(){
	PORTB |=(1<<Blue);
}
void enableGreenLed(){
	PORTB |=(1<<Green);
}
