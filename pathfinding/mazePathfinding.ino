#include <ArduinoSTL.h>
#include <NewPing.h>
#include <map>
#include <set>
#include <stack>

//Future to do:
//Finish backwards function
//Improve sensor accuracy
//Implement distance for smarter pathfinding and maze representation.
//Start by using https://www.sunfounder.com/learn/Super-Kit-V2-0-for-Arduino/lesson-14-rotary-encoder-super-kit.html

//Some stuff is unfinished, but left in to demonstrate our goals for the project.

//Declare instances of sensors
NewPing leftSonar(8, 9);
NewPing sonar(10,11);
NewPing rightSonar(12, 13);

//Motor port constants
int leftMotorBow = 3;//Bow: forward, Aft:back
int leftMotorAft = 4;
int rightMotorBow = 5;
int rightMotorAft = 6;
int eleMotorUp = 7; //elevator motor (changed to buzzer)


//We have to use global variables because Arduino sucks
bool firstRun = true;
bool finished = true;

//Prevents Multiple Nodes From Being Added Until We Have Finished Our Decision
bool preventMultipleNodes = true;

//What is the diameter of our distance wheel for distance tracking?
double diameter;
double wheelCir = diameter * M_PI;

//xy coords for the location data
struct Coord{
  double x=0;
  double y=0;
};

//We created SensorData class to be able to add/remove variables easily
struct SensorData{
  int sonarLeft=0;
  int sonarRight=0;
  int sonarFront=0;
  double turns=0;
};

//Node data structure
class Node{
  public:
  //Constructor for nodes
  Node(int distance, SensorData &data, Node *currNode, char direction);

  //How far are we from previous node?
  double distance;

  //What direction are relative from previous node
  char direction;
  
  //Store xy location of node
  Coord nodeLocation;
  
  //Does this lead to a dead end? Yes or no
  bool possible;

  //Backedge to previous/original node.
  Node *backedge;
};

//This class stores which sensors have a wall in front of them, useful for addNode
struct List{
  bool left=false;
  bool center=false;
  bool right=false;
};


//Node constructor
Node::Node(int distance, SensorData &data, Node *currNode, char direction){
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

  //Constructor
  Maze(Node *start, Node *actualStart);

  //Adjancency list
  //TODO make these private variables.
  std::map <Node *, std::set<Node *>> adj;

  //Stores what path we are on
  std::stack<Node *> path;
  
  //When our robot gets to a choice with options, add the options (which are Nodes)
  void addNode(int distance, SensorData &data, List &list);
  
  //When we get to a dead end, we can eliminate each node backwards until we get to one with multiple paths
  void pathEliminator(Node *currentNode);

  //Returns the number of paths that a node has
  int numBranches(Node *currentNode);

  //Basically cout for the nodes
  void nodeOut();

  //Makes the thing travel backwards
  void backwards();

  //Checks to see if we need to call addNode()
  void sensorCheck(SensorData &data);
  
  private:
    void letsMakeADecision(Node *currentNode);
    Coord mainLocation;
    //Current node
    Node *mainNode;
    //Destination node
    Node *goal;
    //Orientation of robot
    char currentDirection;
  
};

//Maze constructor
Maze::Maze(Node *start, Node *actualStart){
  mainLocation.x=0;
  mainLocation.y=0;
  mainNode = start;
  goal = actualStart;
  currentDirection = 'c';
}

//This function gave us a compiler error in backwards, so we moved it somewhere else
void weirdfix(){
  moveRobot("180", 175);
}

//Makes the robot go backwards from where it is. Called at dead ends
void Maze::backwards(){
   Node *temp = mainNode;

   //Sets backwards paths to false
   pathEliminator(temp);
   
   if(finished){
    digitalWrite(7, HIGH);
    delay(500);
    digitalWrite(7, LOW);
    finished = false;
   }

   weirdfix();  
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

//Returns number of paths for a node
int Maze::numBranches(Node *currentNode){
  int temp = adj[currentNode].size();
  return temp;
}

//Adds the nodes from the current node depending on the the sensor data
void Maze::addNode(int distance, SensorData &data, List &list){

  //Prevents this function from firing multiple times
  //We want to make sure the vehicle is away before it tries to place a node again
  preventMultipleNodes = false;

  Serial.println("addNode");
  char temp;
  Node *newNode;

  goal->distance = distance;

  //True means there is not a wall for left and right
  //TODO, change 0 to distance with distance sensor
  if(list.left){
    newNode = new Node(0, data, goal, 'l');
    Serial.println("insert left");
    adj[goal].insert(newNode);
  }

  //Remember list.center is the exception
  //True means we are at a wall, so we need to invert that
  if(!list.center){
    newNode = new Node(0, data, goal, 'c');
    Serial.println("insert straight");
    adj[goal].insert(newNode);
  }

  if(list.right){
    newNode = new Node(0, data, goal, 'r');
    Serial.println("insert right");
    adj[goal].insert(newNode);
  }

  //Update coords
  path.push(goal);

  //Once we add the node, we can make a decision on where the robot should go
  letsMakeADecision(goal);
  
}

//Refreshes data by reading sensor inputs
void refreshSensorData(SensorData &data){
  data.sonarLeft = leftSonar.ping_in();
  data.sonarFront = sonar.ping_in(); 
  data.sonarRight = rightSonar.ping_in();
}

//This is called whenever we need to go to a path
//It will pick a direction and go to there
void Maze::letsMakeADecision(Node *currentNode){
  std::set <Node *>::iterator literator;
  for(literator = adj[currentNode].begin(); literator != adj[currentNode].end(); literator++){
    Node *temp = *literator;
    if(temp->possible && temp->direction == 'l'){
      Serial.println("Left");
      delay(500);
      moveRobot("stahp", 175); 
      delay(3000);     
      moveRobot("hardLeft", 175);
      moveRobot("forward", 175);
      delay(1000);
      //currentDirection = 'l';
      preventMultipleNodes = true;
     break;
    }
    else if(temp->possible && temp->direction == 'r'){
      Serial.println("Right");
      delay(500);
      moveRobot("stahp", 175); 
      delay(3000);  
      moveRobot("hardRight", 175);
      moveRobot("forward", 175);
      delay(1000);
      preventMultipleNodes = true;
      break;
    }
    else if(temp->possible && temp->direction == 'c'){
      Serial.println("Straight");
      delay(500);
      moveRobot("stahp", 175); 
      delay(3000);  
      moveRobot("forward", 175);
      delay(1000);
      preventMultipleNodes = true;
      break;
    }
  }
}

//We check if certain logic is true, if so, we need to add a new node and make decisions.
//We need to also check to make sure we are at the right nodes etc.
void Maze::sensorCheck(SensorData &data){
  //If sensors are open, add a node!
  int sensorSum=0;
  int errorConstant = 5;
  List list;
  bool frontEnd;

  //True if we reach a wall (This is different from left/right, opposite)
  if(data.sonarFront < errorConstant){
     list.center = true;
  }

  //True if we aren't at a wall
  if(data.sonarLeft > errorConstant+8){
    list.left = true;
    sensorSum++;
  }

  //True if we aren't at a wall
  if(data.sonarRight > errorConstant+8){
    list.right = true; 
    sensorSum++;
  }
  
  //If we are at a dead end and there are no openings, go backwards
  if(!sensorSum && list.center){
    //We do need to update the node data before we call this function, but that will be done later
    backwards();
    //return (or turn at another point);
  }
  
  //If the front wall exists but there are paths
  if(sensorSum || list.center){
    if(preventMultipleNodes){
      //Let the robot move just a tiny bit
      delay(750);
      //Change 0 to distance once rotary sensor is hooked up
      addNode(0, data, list);
    }
  }
}

//This is code that will center the vehicle in the maze, ie leftSensorData == rightSensorData.
//This is important to ensure that turning and distance measurements are consistent, and WE DON'T RUN INTO A WALL
void centerRobot(SensorData &data){
  int difference;
  difference = data.sonarLeft - data.sonarRight;

  if(difference > 1){
    realign(data.sonarRight, data.sonarLeft);
  }
  else if(difference < -1){
    realign(data.sonarRight, data.sonarLeft);
  }
  else{
      moveRobot("forward", 175);
  }
}

//If this function is finished, it will be used to figure out which character to return when turing.
//For example, if turn='l' and direction='r', then the function would return 'c' for center.
//Used for storing the direction in the node, and for the robot to be able to travel backwards
char returnDirection(char turn, char direction){
  char turns[4] = {'c', 'r', 'c', 'l'};
  //if(direction == 'f'){
  //  //if(turn == 'l')
  //}

}

void setup(){
  Serial.begin(9600);
  pinMode(leftMotorBow, OUTPUT);
  pinMode(rightMotorBow, OUTPUT);
  //This is actually the buzzer
  pinMode(eleMotorUp, OUTPUT);
}

void loop(){
  //Creates and updates data
  SensorData data;
  refreshSensorData(data);
  
  //Creates 1st and 2nd Pointer and Maze Object
  Node *headNode = new Node(0, data, nullptr, 'b');
  Node *firstRealNode = new Node(0, data, headNode, 'c');

  Maze *maze = new Maze(headNode, firstRealNode);

  //Push first node onto path
  maze->path.push(headNode);

  moveRobot("forward", 175);
  delay(500);

  //We don't have anything that will stop it, it will hopefully just get out of the maze
  while(1){
    refreshSensorData(data);

    //Serial.print is essentially but for Arduino. Open up Serial Monitor to see the output
    Serial.print("Left  ");
    Serial.println(data.sonarLeft);
    
    Serial.print("Center  ");
    Serial.println(data.sonarFront);
    
    Serial.print("Right  ");
    Serial.println(data.sonarRight);
    
    maze->sensorCheck(data);
    centerRobot(data);
    myDelay(100);
  } 
}

//Custom made delay function that allows you to run stuff during the delay
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

//Outputs node details, useful for debugging
void Maze::nodeOut(){
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
