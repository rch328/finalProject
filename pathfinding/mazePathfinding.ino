#include <ArduinoSTL.h>
#include <NewPing.h>
#include <map>
#include <set>
#include <stack>

//Pg 202

NewPing leftSonar(8, 9);
NewPing sonar(10,11);
NewPing rightSonar(12, 13);

//Motor port constants
int leftMotorBow = 3;//Bow: forward, Aft:back
int leftMotorAft = 4;
int rightMotorBow = 5;
int rightMotorAft = 6;
int eleMotorUp = 7; //elevator motor 
int eleMotorDown = 2;

//We have to use global variables because Arduino sucks
bool firstRun = true;

//Prevents Multiple Nodes From Being Added Until We Have Finished Our Decision
bool preventMultipleNodes = true;

//What is the diameter of our distance wheel?

double diameter;
double wheelCir = diameter * M_PI;

//xy coords for the data
struct Coord{
  double x=0;
  double y=0;
};

//We created SensorData class to be able to add/remove variables easily
struct SensorData{
  int sonarLeft=0;
  int sonarRight=0;
  int sonarFront=0;
  //int betweenDistance=0;
  //Coord location;
  double turns=5;
};

class Node{
  public:
  //Constructor for nodes
  Node(int distance, SensorData &data, Node *currNode, char direction);

  //How far from previous node
  double distance;

  //What direction relative from previous node
  // (current)       <-(previous)
  //The above example is left because it is
  char direction;
  
  //I don't know if we need this yet
  Coord nodeLocation;
  
  //Does this lead to a dead end? Yes or no
  bool possible;
  
  //We might not need this because we can use maps
  //std::vector <Node *> paths;
  
  //But we will need this to backedge.
  Node *backedge;
};

//OOP is useful, so this is why I will be using it. In this essay I will....
struct List{
  bool left=false;
  bool center=false;
  bool right=false;
};


//Node constructor
Node::Node(int distance, SensorData &data, Node *currNode, char direction){
  //This line might be dumb
  //Uses distance from previous node
  this->distance = distance;
  
  //The node starts off possible
  possible = true;

  //If we want x y coords
  //nodeLocation = data.location;
  
  //Sets backedge to previous node
  backedge = currNode;

  //We need a direction relative to the previous node
  this->direction = direction;
}

class Maze{
  public:
  
  Maze(Node *start, Node *actualStart);
  std::map <Node *, std::set<Node *>> adj;

  std::stack<Node *> path;
  
  //When our robot gets to a choice with options, add the options (which are Nodes)
  void addNode(int distance, SensorData &data, List &list);
  
  //When we get to a dead end, we can eliminate each node backwards until we get to one with multiple paths
  void pathEliminator(Node *currentNode);

  //Returns the number of paths that a node has
  int numBranches(Node *currentNode);

  //Basically cout for the nodes
  void clout();

  //Makes the thing travel backwards
  void backwards();

  void sensorCheck(SensorData &data);
  
  private:
    void letsMakeADecision(Node *currentNode);
    Coord mainLocation;
    Node *mainNode;
    Node *goal;
    char currentDirection;
  
};

Maze::Maze(Node *start, Node *actualStart){
  mainLocation.x=0;
  mainLocation.y=0;
  mainNode = start;
  goal = actualStart;
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
void refreshSensorData(SensorData &data){
  data.sonarLeft = leftSonar.ping_in();
  data.sonarFront = sonar.ping_in(); 
  data.sonarRight = rightSonar.ping_in();
}

//Adds the nodes from the current node depending on the the sensor data
void Maze::addNode(int distance, SensorData &data, List &list){

  //Prevents this function from firing multiple times
  //We want to make sure the vehicle is away before it tries to place a node again
  preventMultipleNodes = false;

  Serial.print("addNode");
  char temp;
  Node *newNode;

  goal->distance = distance;

  //True means there is a wall, so we need to run when there isn't a wall
  if(!list.left){
    newNode = new Node(0, data, goal, 'l');
    adj[goal].insert(newNode);
  }

  if(!list.center){
    newNode = new Node(0, data, goal, 'c');
    adj[goal].insert(newNode);
  }

  if(!list.right){
    newNode = new Node(0, data, goal, 'r');
    adj[goal].insert(newNode);
  }

  //Update coords
  path.push(goal);

  //Once we add the node, we can make a decision on where the robot should go
  letsMakeADecision(goal);
  
}

//This is called whenever we need to go to a path
void Maze::letsMakeADecision(Node *currentNode){
  std::set <Node *>::iterator literator;
  for(literator = adj[currentNode].begin(); literator != adj[currentNode].end(); literator++){
    Node *temp = *literator;
    if(temp->possible && temp->direction == 'l'){
      Serial.println("Left");
      moveRobot("hardleft", 175);
      moveRobot("forward", 175);
      delay(5000);
      preventMultipleNodes = true;
      break;
    }
    else if(temp->possible && temp->direction == 'c'){
      Serial.println("Straight");
      moveRobot("forward", 175);
      delay(5000);
      preventMultipleNodes = true;
      break;
    }
    else if(temp->possible && temp->direction == 'r'){
      Serial.println("Right");
      moveRobot("hardright", 175);
      moveRobot("forward", 175);
      delay(5000);
      preventMultipleNodes = true;
      break;
    }
  }
}

//We check if certain logic is true, if so, we need to add a new node and make decisions.
//We need to also check to make sure we are at the right nodes etc.
void Maze::sensorCheck(SensorData &data){
  //Oh crap, we have a sensor that is open and huge.
  //Therefore, we will have to add a node probably

  int sensorSum=0;
  int errorConstant = 6;
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
  
  //If we are at a dead end, go backwards
  if(!sensorSum && list.center){
    //backwards();
  }

  //If the front wall exists but there are paths
  if(sensorSum || list.center){
    if(preventMultipleNodes){
      //Let the robot move just a tiny bit
      delay(200);
      addNode(0, data, list);
    }
  }

  //True if there is a wall
}

//TODO Make code that will center the vehicle in the maze, ie leftSensorData == rightSensorData.
//This is important to ensure that turning and distance measurements are consistent because we need low percent error
void centerRobot(SensorData &data){
  int difference;
  difference = data.sonarLeft - data.sonarRight;

  if(difference > 1){
    realign(data.sonarRight, data.sonarLeft);
  }
  else if(difference < -1){
    realign(data.sonarRight, data.sonarLeft);
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(leftMotorBow, OUTPUT);
  pinMode(rightMotorBow, OUTPUT);
  pinMode(eleMotorUp, OUTPUT);
}

void loop(){

  //Creates and updates data
  SensorData data;
  refreshSensorData(data);
  
  //Creates 1st Pointer and Maze Object
  Node *headDaddy = new Node(0, data, nullptr, 'b');
  Node *firstRealBro = new Node(0, data, headDaddy, 'c');

  Maze *maze = new Maze(headDaddy, firstRealBro);

  //Push first node onto path
  maze->path.push(headDaddy);

  moveRobot("forward", 175);
  delay(500);

  //We don't have anything that will stop it, it will hopefully just get out of the maze
  while(1){
    refreshSensorData(data);
    
    Serial.print("Left  ");
    Serial.println(data.sonarLeft);
    
    Serial.print("Center  ");
    Serial.println(data.sonarFront);
    
    Serial.print("Right  ");
    Serial.println(data.sonarRight);
    
    maze->sensorCheck(data);
    myDelay(50);
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


