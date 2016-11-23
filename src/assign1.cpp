
// made changes in g2p to use as a function.

#include "g2p.cpp"

/*
void getTraj(double r , double x, double y , double xtraj[45] , double ytraj[45])
{
     for (int m =0; m<45 ; m++)
     {
        xtraj[m] = x-r*cos(2.0*m);
        ytraj[m] = y+r*sin(2.0*m); 
     }
}
*/


int main(int argc, char *argv[])
{
  double targetx1,targety1,targetx2,targety2;

    // Print usage.
  if(argc < 5){
    printf("\n Usage: %s <ip of server> <id> <targetx> <targety>\n",argv[0]);
    return 1;
  }

    // Get target Data from the user 
  string ip = string(argv[1]);
  int id1 = atoi(argv[2]);
  int id2 = atoi(argv[3]);
  double goalx1 = atoi(argv[4]);
  double goaly1 = atoi(argv[5]);
  double goalx2 = atoi(argv[6]);
  double goaly2 = atoi(argv[7]);
    // Initialize the field computer.
  FieldComputer fc(ip);
  

  
  

  FieldData data = fc.getFieldData();
  vector<int> queryIds;
  while (data.entities.size() < 6)
  {
    if (data.entities.size() > 1) {
      queryIds.push_back(data.entities[0].id());
    }
    

    data = fc.getFieldData(queryIds);
    
  }    

     // Get starting position of the boxes
  for(unsigned i = 0; i < data.entities.size(); i++){
    if( data.entities[i].id() == 101 )
    {
      targetx1 = data.entities[i].x() -35;
      targety1 = data.entities[i].y() +10;
      std::cout << "found 101 co-ordinates"<< std::endl;

    }
    if( data.entities[i].id() == 102 )
    {
      targetx2 = data.entities[i].x() -40 ;
      targety2 = data.entities[i].y() -10;
      std::cout << "found 102 co-ordinates"<< std::endl;
    }
    
  }
  std::cout << "101 x =" << targetx1 << std::endl;
  std::cout << "101 y =" << targety1 << std::endl;
  std::cout << "102 x =" << targetx2 <<std::endl;
  std::cout << "102 y =" << targety2 <<std::endl;

   // Take the sparkies to starting position of the box
  std::cout << "stuff is happening " << std::endl;
  g2p(ip,id1,targetx1,targety1);
  std::cout << "more stuff is happening " << std::endl;
  g2p(ip,id2,targetx2,targety2); 
  
   // Find how much to move in x and y
  double delx1 = goalx1 - targetx1;
  double dely1 = goaly1 - targety1 ;
  double delx2 = goalx2 - targetx2;
  double dely2 = goaly2 - targety2;
  

   // Create a Step size to move for each box in x and y direction
  double stepx1 = delx1/10.0 ;    
  double stepy1 = dely1/10.0 ;
  double stepx2 = delx2/10.0 ;
  double stepy2 = dely2/10.0 ;

   // Take one step at a time to reach goal position.

  for (int m = 1; m<= 10 ; m++  )
  {
   
   std::cout << "step " << m << "target_1 = " << targetx1+m*stepx1 -20 << "  "<< targety1+m*stepy1 +10 << std::endl;
   std::cout << "step " << m << "target_2 = " << targetx2+m*stepx2 -20 << "  "<< targety2+m*stepy2 -20 << std::endl;
   
   // Take one step towaards goal position
   g2p(ip,id1,targetx1+m*stepx1 -20,targety1+m*stepy1 -15);
   g2p(ip,id2,targetx2+m*stepx2 -20,targety2+m*stepy2 -15); 
   

 }


 return 0;
}