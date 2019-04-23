#include <ArduinoSTL.h>
//#include <NewPing.h>
//#include <vector>
#include <map>
#include <set>
#include <stack>


//So let me get this straight, maps are part of the STL but vectors are NOT?
//Update, this ain't good chief
//We need very precise movement data, because if we are off, then this will be screwed.

//So many edge cases, I want to make sure this is correct but the simpler the better, but I don't know how simple I can make this.

//Sirvoz evntually bby ;)
//NewPing sonar(8, 9);
//NewPing sonar(8, 9);
//NewPing sonar(8, 9);


//We have to use global variables because Arduino sucks
bool firstRun = true;

struct Coord{
  int x;
  int y;
};

//We created SensorData class to be able to add/remove variables easily
struct SensorData{
  int sonarLeft;
  int sonarRight;
  int sonarFront;
  int betweenDistance;
  Coord location;
  double turns;
};

class Node{
  public:
  //Constructor for nodes
  Node(int distance, SensorData &data, Node *currNode, char direction);
  int distance;
  char direction;
  //I don't know if we need this yet
  Coord nodeLocation;
  //Does this lead to a dead end? Yes or no
  bool possible;
  //We might not need this because we can use maps
  std::vector <Node *> paths;
  //But we will need this to backedge.
  Node *backedge;
};

//OOP is useful, so this is why I will be using it. In this essay I will....
struct List{
  bool left=false;
  bool center=false;
  bool right=false;
};

Node::Node(int distance, SensorData &data, Node *currNode, char direction){
  //This line might be dumb
  this->distance = distance;
  possible = true;
  nodeLocation = data.location;
  backedge = currNode;
  this->direction = direction;
}

bool errorApproximate(Coord &left, Coord &right){
   //If the values are close enough that they are the same, return true.
   //Else return false
    
   return true;
}

class Maze{
  public:
  Maze(Node *start);
  std::map <Node *, std::set<Node *>> adj;

  //Breadcrumb trail
  //std::stack<Coord> path;

  std::stack<Node *> path;
  
  //Wait, using maps is the dumbest thing I have ever done. Why don't I just use a list lol
  //std::map <int, std::vector<Node *>> xloc;
  //std::map <int, std::vector<Node *>> yloc;
  
  //When our robot gets to a choice with options, add the options (which are Nodes)
  void addNode(int distance, SensorData &data, List &list);
  
  //When we get to a dead end, we can eliminate each node backwards until we get to one with multiple paths
  void pathEliminator(Node *currentNode);

  //Returns the number of paths that a node has
  int numBranches(Node *currentNode);

  //Basically cout
  void clout();

  //void ertoerhgeori(Maze &why);

  //Makes the thing travel backwards
  void backwards();

  void sensorCheck(SensorData &data);
  
  private:
    void letsMakeADecision(Node *currentNode);
    Coord mainLocation;
    Node *mainNode;
    Node *goal;
    char currentDirection;
    //Is M_PI PI?
    //int wheelDiameter = 10 * M_PI;

  
};

Maze::Maze(Node *start){
  mainLocation.x=0;
  mainLocation.y=0;
  mainNode = start;
  currentDirection = 's';
}

void Maze::backwards(){
   //Node *temp = currentNode;
   Node *temp = mainNode;
   //Put adjancency list checking code
   while(temp != nullptr && numBranches(temp) < 2){
      temp->possible = false;
      temp = temp->backedge;
   }
}

//Eliminates the path until we get to a node with multiple options
void Maze::pathEliminator(Node *currentNode){
   Node *temp = currentNode;
   //Put adjancency list checking code
   while(temp != nullptr && numBranches(temp) < 2){
      temp->possible = false;
      temp = temp->backedge;
   }
}

int Maze::numBranches(Node *currentNode){
  int temp = adj[currentNode].size();
  return temp;
}

//Refreshes data by reading sensor inputs
//We might not need this, depending on if we put this in void loop
void refreshSensorData(SensorData &data){
  //Measure sensor input and update class?!
}

void Maze::addNode(int distance, SensorData &data, List &list){
  //Check if we are near other node (Implement Later)
  //If we are, this may not be an actual node, but a loop to a previous one

  char temp;
  Node *newNode;

  goal->distance = distance;
  
  if(list.left){
    newNode = new Node(0, data, goal, 'l');
    adj[goal].insert(newNode);
  }

  if(list.center){
    newNode = new Node(0, data, goal, 'c');
    adj[goal].insert(newNode);
  }

  if(list.left){
    newNode = new Node(0, data, goal, 'r');
    adj[goal].insert(newNode);
  }

  
  //mainNode = newNode;

  //Update coords
  path.push(goal);

  letsMakeADecision(goal);
  
  //Once we add the node, we can make a decision on where we should go
}

//This is called whenever we need to go to a path
void Maze::letsMakeADecision(Node *currentNode){
  std::set <Node *>::iterator literator;
  for(literator = adj[currentNode].begin(); literator != adj[currentNode].end(); literator++){
    Node *temp = *literator;
  }
}

//We check if certain logic is true, if so, we need to add a new node and make decisions.
//We need to also check to make sure we are at the right nodes etc.
void Maze::sensorCheck(SensorData &data){
  //Oh crap, we have a sensor that is open and huge.
  //Therefore, we will have to add a node probably

  int sensorSum=0;
  int errorConstant = 8;
  List list;
  bool frontEnd;

  
  //If we reach a wall
  //Divide by 2 because it will approach wall, for extra confidence
  if(data.sonarFront < errorConstant/2){
     list.center = true;
  }

  
  if(data.sonarLeft > errorConstant){
    list.left = true;
    sensorSum++;
  }
  if(data.sonarRight > errorConstant){
    list.right = true; 
    sensorSum++;
  }

  //If we are at a dead end, backtrace
  if(!sensorSum && list.center){
    //backwards();
  }

  //If the front wall exists but there are paths
  if(sensorSum || list.center){
    //maize.addNode(0, data, list);
  }

  
}

//TODO Make code that will center the vehicle in the maze, ie leftSensorData == rightSensorData.
//This is important to ensure that turning and distance measurements are consistent because we need low percent error
void centerRobot(SensorData &data){
  int difference;
  difference = data.sonarLeft - data.sonarRight;
  if(difference == 0){
    //continue;
  }
  else if(difference > 1){
    //Slight left
  }
  else if(difference < -1){
    //Slight right
  }
}

void setup(){
  // put your setup code here, to run once:
  SensorData data;
  refreshSensorData(data);

  //Construct our maze objects
  Node *headDaddy = new Node(0, data, nullptr, 'b');
  Maze *maze = new Maze(headDaddy);
}

void loop(){

  /*
  SensorData data;//Maze maze;
  refreshSensorData(data);
  
  // put your main code here, to run repeatedly:
  if(firstRun){
    Node *headDaddy = new Node(0, data, nullptr, 'b');
    Maze *maze = new Maze(headDaddy);
    firstRun = false;
    maze->pathEliminator(headDaddy);
  }
  
  //maze->pathEliminator(headDaddy);
  
  sensorCheck(data);
  myDelay(10);
  //maze->addNode(7, data);
  */

  //This is one of the most evil things that I will ever do.

  SensorData data;//Maze maze;
  refreshSensorData(data);
  

  Node *headDaddy = new Node(0, data, nullptr, 'b');
  Maze *maze = new Maze(headDaddy);
    
  while(1){
    refreshSensorData(data);
    maze->sensorCheck(data);
    myDelay(10);
  }
  
}

//In case we need the CS 130 lab delay function, idk if we do though
void myDelay(int ms){
  int start_ms = millis();
  int current_ms;
  while(true){
    current_ms = millis();
    //Do stuff
    if(current_ms >= (start_ms+ms)){
      break;
    }
  }
}

//Outputs node details
void Maze::clout(){
  std::map <Node *, std::set<Node *>>::iterator literator;
  std::set <Node *>::iterator siterator;
  for(literator = adj.begin(); literator != adj.end(); literator++){
    siterator = literator->second.begin();
    for(; siterator != literator->second.end(); siterator++){
      Node *temp = *siterator;
      //std::cout << " " << *siterator->distance << endl;
      std::cout << temp->distance << "  " << temp->direction << std::endl;
    }
  }
}


