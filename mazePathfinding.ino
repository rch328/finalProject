#include <ArduinoSTL.h>
//#include <vector>
#include <map>
#include <set>
#include <stack>


//So let me get this straight, maps are part of the STL but vectors are NOT?
//Update, this ain't good chief
//We need very precise movement data, because if we are off, then this will be screwed.

//So many edge cases, I want to make sure this is correct but the simpler the better, but I don't know how simple I can make this.

//We created SensorData class to be able to add/remove variables easily
struct Coord{
  int x;
  int y;
};

struct SensorData{
  int sonarLeft;
  int sonarRight;
  int sonarFront;
  int betweenDistance;
  Coord location;
};

class Node{
  public:
  //Constructor for nodes
  Node(int distance, SensorData &data, Node *currNode);
  int distance;
  //I don't know if we need this yet
  Coord nodeLocation;
  //Does this lead to a dead end? Yes or no
  bool possible;
  //We might not need this because we can use maps
  std::vector <Node *> paths;
  //But we will need this to backedge.
  Node *backedge;
};

Node::Node(int distance, SensorData &data, Node *currNode){
  this->distance = distance;
  possible = true;
  nodeLocation = data.location;
  backedge = currNode;
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
  std::stack<Coord> path;
  
  //Wait, using maps is the dumbest thing I have ever done. Why don't I just use a list lol
  //std::map <int, std::vector<Node *>> xloc;
  //std::map <int, std::vector<Node *>> yloc;
  
  //When our robot gets to a choice with options, add the options (which are Nodes)
  void addNode(int distance, SensorData &data);
  
  //When we get to a dead end, we can eliminate each node backwards until we get to one with multiple paths
  void pathEliminator(Node *currentNode);

  //Returns the number of paths that a node has
  int numBranches(Node *currentNode);
  
  private:
    Coord mainLocation;
    Node *mainNode;
  
};

Maze::Maze(Node *start){
  mainLocation.x=0;
  mainLocation.y=0;
  mainNode == start;
}

void Maze::pathEliminator(Node *currentNode){
   Node *temp = currentNode;
   //Put adjancency list checking code
   while(temp != nullptr && numBranches(temp) < 2){
      temp->possible = false;
   }
}

int Maze::numBranches(Node *currentNode){
  int temp = adj[currentNode].size();
  return temp;
}



//Refreshes data by reading sensor inputs
//We might not need this, depending on if we put this in void loop
void refreshSensorData(SensorData &data){


  
}

void Maze::addNode(int distance, SensorData &data){
  //Check if we are near other node (Implement Later)
  //If we are, this may not be an actual node, but a loop to a previous one

  Node *newNode = new Node(distance, data, mainNode);
  adj[mainNode].insert(newNode);
  mainNode = newNode;

  //Update coords
  //path.push(newNode);
}

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

//TODO Make code that will center the vehicle in the maze, ie leftSensorData == rightSensorData.
//This is important to ensure that turning and distance measurements are consistent because we need low percent error

//We check if certain logic is true, if so, we need to add a new node and make decisions.
//We need to also check to make sure we are at the right nodes etc.
void sensorCheck(SensorData &data){
  
}

void setup() {
  // put your setup code here, to run once:
  SensorData data;
  refreshSensorData(data);
  Node *headDaddy = new Node(0, data, nullptr);
  Maze *maze = new Maze(headDaddy);
}

void loop() {
  // put your main code here, to run repeatedly:

}
