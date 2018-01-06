#include "camera.hpp"

Camera::Camera(int state){
	currentState = state;
}

Camera::~Camera(){
}

bool Camera::cameraChange(){
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	// CLAVIER TOUCHE C
	if (state[SDL_SCANCODE_C]){
		if (currentState == firstPerson){
			currentState = thirdPerson;
		}
		else if (currentState == thirdPerson){
			currentState = firstPerson;
		}
		SDL_Delay(150);
		return true;
	}
	else {
		return false;
	}
}