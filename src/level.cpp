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
		else {
			createObjectFromLine(typeMObject,line);
			nLineObj++;
		}
		nLine++;
	}

	readImageFile(imageFile);

	for (int i = 0 ; i < 4 ; i++ ){
		ghosts.push_back(Ghost(glm::vec2(10,10),0,i));
	}
}

Level::~Level(){
}

void Level::createObjectFromLine(int type, string line){
	/*if (type == chest){
		vector<string> ChestDetails = split(line, ':');
		// chargement texture
		GLuint * texture = NULL;
		ObjectCollectable content(stoi(ChestDetails[5]),stoi(ChestDetails[6]),ChestDetails[4]);
		chests.push_back(Chest(glm::vec2(stoi(ChestDetails[1]),stoi(ChestDetails[2])),stoi(ChestDetails[3]),texture,content));
	}
	if (type == monster){
		vector<string> MonsterDetails = split(line, ':');
		// chargement texture
		GLuint * texture = NULL;
		TypeMonster typeMons(MonsterDetails[4],stoi(MonsterDetails[5]),stoi(MonsterDetails[6]),stoi(MonsterDetails[7]));
		monsters.push_back(Monster(glm::vec2(stoi(MonsterDetails[1]),stoi(MonsterDetails[2])),stoi(MonsterDetails[3]),texture,typeMons));
	}*/
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
	
	int row = 0, col = 0;
	for (int n = 0 ; n < (int)elems.size() ; n++){
		if (elems[n][0] == 0 && elems[n][1] == 0 && elems[n][2] == 0) map.push_back(Case(glm::vec2(row,col), empty));
		else if (elems[n][0] == 255 && elems[n][1] == 255 && elems[n][2] == 255) map.push_back(Case(glm::vec2(row,col), path));
		else if (elems[n][0] == 0 && elems[n][1] == 255 && elems[n][2] == 0) {
			map.push_back(Case(glm::vec2(row,col), in));
			begin = Case(glm::vec2(row,col),in);
		}
		else if (elems[n][0] == 255 && elems[n][1] == 0 && elems[n][2] == 0) {
			map.push_back(Case(glm::vec2(row,col), out));
			out1 = Case(glm::vec2(row,col),out);
			//out2 = Case(glm::vec2(row,col),out);
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


void Level::moveObjects(Player *player){
  if (player->direction == NORD && getCaseFromPos(glm::vec2(player->position.x, player->position.y -1)).type != 0) player->position.y -= 1;
  else if (player->direction == SUD && getCaseFromPos(glm::vec2(player->position.x, player->position.y +1)).type != 0) player->position.y += 1;
  else if (player->direction == OUEST && getCaseFromPos(glm::vec2(player->position.x -1, player->position.y)).type != 0) player->position.x -= 1;
  else if (player->direction == EST && getCaseFromPos(glm::vec2(player->position.x +1, player->position.y)).type != 0) player->position.x += 1;

  for(int i=0; i < (int)ghosts.size(); i++){
  	ghosts[i].move(player->position, player->direction, this->map);
  }
  if (player->nbMoves == 5) ghosts[0].position = ghosts[1].beginPos;
  //if (player->nbMoves == 15) ghosts[1].position = ghosts[1].beginPos;
  if (player->nbMoves == 25) ghosts[2].position = ghosts[2].beginPos;
  if (player->nbMoves == 30) ghosts[3].position = ghosts[3].beginPos;
}