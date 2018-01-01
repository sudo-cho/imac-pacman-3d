#include "camera.hpp"

Camera::Camera(){
}

Camera::~Camera(){
}

Camera::Camera(glm::vec2 pos, int state){
	position = pos;
	currentState = state;
}

bool Camera::cameraChange(Level level){
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