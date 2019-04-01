#include <ArduinoSTL.h>
//#include <vector>
#include <map>
#include <set>


//So let me get this straight, maps are part of the STL but vectors are NOT?
//Update, this ain't good chief
//We need very precise movement data, because if we are off, then this will be screwed.

//So many edge cases, I want to make sure this is correct but the simpler the better, but I don't know how simple I can make this.

//We created SensorData class to be able to add/remove variables easily
struct SensorData{
  int sonarLeft;
  int sonarRight;
  int sonarFront;
  int betweenDistance;
  int x;
  int y;
};

class Node{
  //Constructor for nodes
  Node(int distance, SensorData &data);
  int distance;
  //I don't know if we need this yet
  int xrel;
  int yrel;
  //Does this lead to a dead end? Yes or no
  bool possible;
  //We might not need this because we can use maps
  std::vector <Node *> paths;
  
};

Node::Node(int distance, SensorData &data){
  this->distance = distance;
  possible = true;
  xrel = data.x;
  yrel = data.y;
}

class Maze{
  public:
  //Maze(
  std::map <Node *, std::set<Node *>> adj;

  //When we gotta check to see if a loop is found, we need to quickly error check to see if two are close without using recursion and huge runtimes
  std::map <int, std::vector<Node *>> xloc;
  std::map <int, std::vector<Node *>> yloc;
  //When our robot gets to a choice with options, add the options
  void addNode(int distance, SensorData &data);
  //When we get to a dead end, we can eliminate each node backwards until we get to one with multiple paths
  void pathEliminator(Node *currentNode);
  private:
    int xlocation;
    int ylocation;
  
};






//Refreshes data by reading sensor inputs
//We might not need this, depending on if we put this in void loop
void refreshSensorData(SensorData &data){


  
}

void Maze::addNode(int distance, SensorData &data){
  //Check if we are near other node
  //If we are, this may not be an actual node, but a loop to a previous one
}

void centerRobot(SensorData &data){
  int difference;
  //difference = sonarLeft - sonarRight;
  if(difference == 0){
    //continue;
  }
  else if(difference > 0){
    //Slight left
  }
  else if(difference < 0){
    //Slight right
  }
}

//TODO Make code that will center the vehicle in the maze, ie leftSensorData == rightSensorData.
//This is important to ensure that turning and distance measurements are consistent because we need low percent error

//We check if certain logic is true, if so, we need to add a new node and make decisions.
void sensorCheck(SensorData data){
  
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
