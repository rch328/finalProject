/*
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

  //How far from previous node
  int distance;

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
*/
