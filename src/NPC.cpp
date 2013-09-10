#include "../include/NPC.hpp"


NPC::~NPC() {
	
}

SDL_Rect NPC::getCurrentFrame() {
	return frameCycle[getFrameKey()];
}

std::string NPC::getSpeech() {
	return speech;
}
void NPC::setSpeech(std::string text) {
	speech = text;
}

// associates a key string to an array of rectangles
// used for cutting walk frames
void NPC::generateSpriteFrame(SDL_Surface* tileImage, int tileWidth, int tileHeight) {
	int ctr=0;
	for (int i=0; i<tileImage->w;i+=tileWidth) {
    	for (int j=0; j<tileImage->h; j+=tileHeight) {
    		SDL_Rect temp;
    		temp.x = i;
    		temp.y = j;
    		temp.w = tileWidth;
    		temp.h = tileHeight;
    		frameCycle[keys[ctr]]=temp;
    		ctr++;
    	}
	}
}

// changes your direction by either updating the 
// frameCycle or setting it to the new direction
// fixme 100 could be a frame rate number
void NPC::updateSpriteFrame(std::string key, int ticks) {
	if (key.compare("2")==0) {
		if (getFrameKey().compare("20")==0 || getFrameKey().compare("21")==0 || getFrameKey().compare("22")==0 || getFrameKey().compare("23")==0) {
			cycleSpriteFrame(ticks);
		}else {
			setFrameKey("21");
		}
	}else if (key.compare("1")==0) {
		if (getFrameKey().compare("10")==0 || getFrameKey().compare("11")==0 || getFrameKey().compare("12")==0 || getFrameKey().compare("13")==0) {
			cycleSpriteFrame(ticks);
		}else {
			setFrameKey("11");
		}
	}else if (key.compare("4")==0) {
		if (getFrameKey().compare("40")==0 || getFrameKey().compare("41")==0 || getFrameKey().compare("42")==0 || getFrameKey().compare("43")==0) {
			cycleSpriteFrame(ticks);
		}else {
			setFrameKey("40");
		}
	}else if (key.compare("3")==0) {
		if (getFrameKey().compare("30")==0 || getFrameKey().compare("31")==0 || getFrameKey().compare("32")==0 || getFrameKey().compare("33")==0) {
			cycleSpriteFrame(ticks);
		}else {
			setFrameKey("30");
		}
	}
}

void NPC::cycleSpriteFrame() {
		// moving 1
		if (getFrameKey().compare(keys[4]) == 0 ) {
			setFrameKey(keys[8]);
		}else if (getFrameKey().compare(keys[8]) == 0) {
			setFrameKey(keys[12]);
		}else if (getFrameKey().compare(keys[12]) == 0) {
			setFrameKey(keys[0]);
		}else if (getFrameKey().compare(keys[0]) == 0) {
			setFrameKey(keys[4]);
		}

		// moving up
		if (getFrameKey().compare(keys[5]) == 0) {
			setFrameKey(keys[9]);
		}else if (getFrameKey().compare(keys[9]) == 0) {
			setFrameKey(keys[13]);
		}else if (getFrameKey().compare(keys[13]) == 0) {
			setFrameKey(keys[1]);
		}else if (getFrameKey().compare(keys[1]) == 0) {
			setFrameKey(keys[5]);
		}

		// moving 3
		if (getFrameKey().compare(keys[2]) == 0) {
			setFrameKey(keys[6]);
		}else if (getFrameKey().compare(keys[6]) == 0) {
			setFrameKey(keys[10]);
		}else if (getFrameKey().compare(keys[10]) == 0) {
			setFrameKey(keys[14]);
		}else if (getFrameKey().compare(keys[14]) == 0) {
			setFrameKey(keys[2]);
		}

		// moving 4
		if (getFrameKey().compare(keys[3]) == 0) {
			setFrameKey(keys[7]);
		}else if (getFrameKey().compare(keys[7]) == 0) {
			setFrameKey(keys[11]);
		}else if (getFrameKey().compare(keys[11]) == 0) {
			setFrameKey(keys[15]);
		}else if (getFrameKey().compare(keys[15]) == 0) {
			setFrameKey(keys[3]);
		}
}

// altering the walk frames by
// changing the direction key
void NPC::cycleSpriteFrame(int ticks) {
	if ((ticks-lastUpdate)>100) {
		// moving 1
		if (getFrameKey().compare(keys[4]) == 0 ) {
			setFrameKey(keys[8]);
		}else if (getFrameKey().compare(keys[8]) == 0) {
			setFrameKey(keys[12]);
		}else if (getFrameKey().compare(keys[12]) == 0) {
			setFrameKey(keys[0]);
		}else if (getFrameKey().compare(keys[0]) == 0) {
			setFrameKey(keys[4]);
		}

		// moving up
		if (getFrameKey().compare(keys[5]) == 0) {
			setFrameKey(keys[9]);
		}else if (getFrameKey().compare(keys[9]) == 0) {
			setFrameKey(keys[13]);
		}else if (getFrameKey().compare(keys[13]) == 0) {
			setFrameKey(keys[1]);
		}else if (getFrameKey().compare(keys[1]) == 0) {
			setFrameKey(keys[5]);
		}

		// moving 3
		if (getFrameKey().compare(keys[2]) == 0) {
			setFrameKey(keys[6]);
		}else if (getFrameKey().compare(keys[6]) == 0) {
			setFrameKey(keys[10]);
		}else if (getFrameKey().compare(keys[10]) == 0) {
			setFrameKey(keys[14]);
		}else if (getFrameKey().compare(keys[14]) == 0) {
			setFrameKey(keys[2]);
		}

		// moving 4
		if (getFrameKey().compare(keys[3]) == 0) {
			setFrameKey(keys[7]);
		}else if (getFrameKey().compare(keys[7]) == 0) {
			setFrameKey(keys[11]);
		}else if (getFrameKey().compare(keys[11]) == 0) {
			setFrameKey(keys[15]);
		}else if (getFrameKey().compare(keys[15]) == 0) {
			setFrameKey(keys[3]);
		}

		lastUpdate = ticks;
	}
}
