#include <level.hpp>

using namespace std;

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<string> split(const string &s, char delim) {
    std::vector<string> elems;
    split(s, delim, elems);
    return elems;
}


Level::Level(string fileName){
    ifstream file(fileName);
	
	string line, imageFile;
	int nLine=0, nObj=0, nLineObj = 0;
	vector<string> ObjectDetails;
	int typeMObject;

	while (getline(file,line)){
		if (nLine == 0) typeMObject = 0;
		else if (nLine == 1) imageFile = line;
		else if (nLine == 2 || nLineObj == nObj +1) {
			typeMObject++;
			nObj = stoi(line);
			nLineObj = 1;
		}
		nLine++;
	}

	readImageFile(imageFile);

	for (int i = 0 ; i < 4 ; i++ ){
		if (i == 0) { shadow = Ghost(glm::vec2(10,10),0,i); }
		else if (i == 1) { speedy = Ghost(glm::vec2(10,10),0,i); }
		else if (i == 2) { bashful = Ghost(glm::vec2(10,10),0,i); }
		else if (i == 3) { pokey = Ghost(glm::vec2(10,10),0,i); }
	}

	statePacman = 0;
}

Level::~Level(){
}

void Level::readImageFile(string imageFile){
	ifstream image(imageFile);	

	string line;
	int i=0, j=0, width=0, height=0;
	vector<string> widthHeight;
	vector<vector<int>> elems;
	vector<int> elemsLine;
	
	while (getline(image,line)){
		if (i==0 && line.compare("P3")) break;
		if (i==2) {
			widthHeight = split(line, ' ');
			width = stoi(widthHeight[0]);
			height = stoi(widthHeight[1]);
		}
		if (i > 3){
			if ( i == j-2) {
				elemsLine.push_back(stoi(line));
				i+=3;
				elems.push_back(elemsLine);
				elemsLine.clear();
			}
			else {
				elemsLine.push_back(stoi(line));
			}
		}
		else {i++;}
		j++;
	}
	
	int row = 0, col = 0, nbOutCases = 0;
	for (int n = 0 ; n < (int)elems.size() ; n++){
		if (elems[n][0] == 0 && elems[n][1] == 0 && elems[n][2] == 0) {
			map.push_back(Case(glm::vec2(row,col), empty, noPacgum));
		}
		else if (elems[n][0] == 255 && elems[n][1] == 255 && elems[n][2] == 255) {
			map.push_back(Case(glm::vec2(row,col), path, noPacgum));
		}
		else if (elems[n][0] == 0 && elems[n][1] == 0 && elems[n][2] == 255) {
			map.push_back(Case(glm::vec2(row,col), path, pacgum));
		}
		else if (elems[n][0] == 255 && elems[n][1] == 0 && elems[n][2] == 255) {
			map.push_back(Case(glm::vec2(row,col), path, superPacgum));
		}
		else if (elems[n][0] == 0 && elems[n][1] == 255 && elems[n][2] == 0) {
			map.push_back(Case(glm::vec2(row,col), in, noPacgum));
			begin = Case(glm::vec2(row,col),in, noPacgum);
		}
		else if (elems[n][0] == 255 && elems[n][1] == 0 && elems[n][2] == 0) {
			map.push_back(Case(glm::vec2(row,col), out, noPacgum));
			if (nbOutCases == 0) {
				out1 = Case(glm::vec2(row,col),out, noPacgum);
				nbOutCases ++;
			}
			else {
				out2 = Case(glm::vec2(row,col),out, noPacgum);
			}
		}
		if (row == width -1) row = 0;
		else row++;
		col = (n-row+1)/(width);
	}
	
	this->width = width;
	this->height = height;
}

Case Level::getCaseFromPos(glm::vec2 pos){
	Case caseNull;
	for (int n=0 ; n < (int)map.size() ; n++){
		if (map[n].position.x == pos.x && map[n].position.y == pos.y) return map[n];
	}
	return caseNull;
}

int Level::getMapValueCase(glm::vec2 pos){
	for (int n=0 ; n < (int)map.size() ; n++){
		if (map[n].position.x == pos.x && map[n].position.y == pos.y) return n;
	}
	return 0;
}

static int nbMoves = 0;

void Level::moveObjects(Player *player){

	if (superGumTimer == 20){
		statePacman = 0;
		superGumTimer = 0;
	}

	nbMoves++;

	if (player->direction == NORD && getCaseFromPos(glm::vec2(player->position.x, player->position.y -1)).type != 0) player->position.y -= 1;
	else if (player->direction == SUD && getCaseFromPos(glm::vec2(player->position.x, player->position.y +1)).type != 0) player->position.y += 1;
	else if (player->direction == OUEST && getCaseFromPos(glm::vec2(player->position.x -1, player->position.y)).type != 0) player->position.x -= 1;
	else if (player->direction == EST && getCaseFromPos(glm::vec2(player->position.x +1, player->position.y)).type != 0) player->position.x += 1;

	if (player->position.x == out1.position.x && player->position.y == out1.position.y){
		player->position.x = out2.position.x;
		player->position.y = out2.position.y;
	}
	else if (player->position.x == out2.position.x && player->position.y == out2.position.y) {
		player->position.x = out1.position.x;
		player->position.y = out1.position.y;
	}

	if (getCaseFromPos(glm::vec2(player->position.x, player->position.y)).ifPacgum == 1){
		player->score += 10;
		map[getMapValueCase(glm::vec2(player->position.x, player->position.y))].ifPacgum = 0;
	}
	else if (getCaseFromPos(glm::vec2(player->position.x, player->position.y)).ifPacgum == 2){
		player->score += 50;
		map[getMapValueCase(glm::vec2(player->position.x, player->position.y))].ifPacgum = 0;
		statePacman = pacmanAttack;
		superGumTimer = 0;
	}

	if (shadow.comparePos(shadow.position,player->position)) { playerContact(player,shadow); }
	if (speedy.comparePos(speedy.position,player->position)) { playerContact(player,speedy); }
	if (bashful.comparePos(bashful.position,player->position)) { playerContact(player,bashful); }
	if (pokey.comparePos(pokey.position,player->position)) { playerContact(player,pokey); }

	if (player->nbMoves == 5) {
		shadow.position = shadow.beginPos;
		shadow.lastPos = shadow.beginPos;
	}
	if (player->nbMoves == 15) {
		speedy.position = speedy.beginPos;
		speedy.lastPos = speedy.beginPos;
	}
	if (player->nbMoves == 25) {
		bashful.position = bashful.beginPos;
		bashful.lastPos = bashful.beginPos;
	}
	if (player->nbMoves == 30) {
		pokey.position = pokey.beginPos;
		pokey.lastPos = pokey.beginPos;
	}

	if (nbMoves % 2 == 0){
		if (statePacman == pacmanHunted){
			shadow.move(player->position, player->direction, this->map, this->width);
			speedy.move(player->position, player->direction, this->map, this->width);
			bashful.move(player->position, player->direction, this->map, this->width);
			pokey.move(player->position, player->direction, this->map, this->width);
		}
		else if (statePacman == pacmanAttack){
			shadow.moveAway(player->position, player->direction, this->map);
			speedy.moveAway(player->position, player->direction, this->map);
			bashful.moveAway(player->position, player->direction, this->map);
			pokey.moveAway(player->position, player->direction, this->map);
		}
	}

	if (shadow.comparePos(shadow.position,player->position)) { playerContact(player,shadow); }
	if (speedy.comparePos(speedy.position,player->position)) { playerContact(player,speedy); }
	if (bashful.comparePos(bashful.position,player->position)) { playerContact(player,bashful); }
	if (pokey.comparePos(pokey.position,player->position)) { playerContact(player,pokey); }
	
	if (statePacman == 1){
		superGumTimer++;
	}
}

void Level::playerContact(Player *player, Ghost ghost){
	if (statePacman == pacmanHunted){
		player->takeDamage();
		player->position = player->beginPos;
		player->nbMoves = 0;

		shadow.position = glm::vec2(10,10);
		shadow.lastPos = glm::vec2(10,10);
		speedy.position = glm::vec2(10,10);
		speedy.lastPos = glm::vec2(10,10);
		bashful.position = glm::vec2(10,10);
		bashful.lastPos = glm::vec2(10,10);
		pokey.position = glm::vec2(10,10);
		pokey.lastPos = glm::vec2(10,10);
	}
	else {
		player->score += 200;
		ghost.position = glm::vec2(10,10);
		ghost.lastPos = glm::vec2(10,10);
	}
}