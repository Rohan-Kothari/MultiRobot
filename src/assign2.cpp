//#include <iostream>
#include<astar.h>
//#include "rbe510.hpp"
#include "g2p.cpp"



using namespace std;

#define CORNER_STARTING_INDEX 200

void getWH(FieldComputer& fc, FieldData& data,int& width,int& height,int& rows,int& cols){
  Point field[4];
  int count =0;
  while(count!=3){
    count = 0;
    data = fc.getFieldData();
    for(unsigned i = 0; i < data.entities.size(); i++){
      if(data.entities[i].id() >= CORNER_STARTING_INDEX-1){
        field[data.entities[i].id()-200].set_x(data.entities[i].x());
        field[data.entities[i].id()-200].set_y(data.entities[i].y());
        if(field[i].x_()!=0.0) count++;
      }
    }
  }
  int width1 = field[2].x_() - field[0].x_();
  int width2 = field[3].x_() - field[1].x_();
  int height1 = field[1].y_() - field[0].y_();
  int height2 = field[3].y_() - field[2].y_();
  //W 1180
  //H 620
  // Robot 62 * 56 (depends on rotation)
  width = width1;
  height = height1;
  cols = int(width1/56);
  rows = int(height1/62)+1;
}
void fillGrid(FieldComputer& fc, FieldData& data,vector<vector<int> > &vvi){
  vector< vector<int> >::iterator row;
    vector<int>::iterator col;
    // Get the Robots Data
  // for (row = vvi.begin(); row != vvi.end(); row++) {
 //        for (col = row->begin(); col != row->end(); col++) {
 //            // *col = 9;
 //            cout<<*col<<" ";
 //        }
 //        cout<<endl;
 //    }
  
  for(unsigned i = 0; i < data.robots.size(); i++){
    // This gives the position of the robot respect with the grid, we don't trust w,h of the robot since that depends on orientation 
    cout << " - Robot id: " << data.robots[i].id() << endl;
    int robotx = int(data.robots[i].x()/56);
    int roboty = int(data.robots[i].y()/62);
    cout << "x: " << robotx << endl;
    cout << "y: " << roboty << endl;
    row = vvi.begin()+roboty;
    col = row->begin()+robotx;
    *col = 1;
  }
  for(unsigned i = 0; i < data.entities.size(); i++){
    // This gives the position of the robot respect with the grid, we don't trust w,h of the robot since that depends on orientation 
    if(data.entities[i].id() <= CORNER_STARTING_INDEX-1){
      cout << " - Marker id: " << data.entities[i].id() << endl;
      int markerx = int(data.entities[i].x()/56);
      int markery = int(data.entities[i].y()/62);
      cout << "x: " << markerx << endl;
      cout << "y: " << markery << endl;
      row = vvi.begin()+markery;
      col = row->begin()+markerx;
      *col = 2;
    }
  }
  for (row = vvi.begin(); row != vvi.end(); row++) {
        for (col = row->begin(); col != row->end(); col++) {
            // *col = 9;
            cout<<*col<<" ";
        }
        cout<<endl;
    }
}
void printFieldData(FieldComputer& fc, FieldData& data) {
  // Get the Robots Data
  for(unsigned i = 0; i < data.robots.size(); i++){
    cout << " - Robot id: " << data.robots[i].id() << endl;
    // cout << "x: " << data.robots[i].x() << endl;
    // cout << "y: " << data.robots[i].y() << endl;
    // cout << "theta: " << data.robots[i].theta() << endl;
    cout << "width: " << data.robots[i].width() << endl;
    cout << "height: " << data.robots[i].height() << endl;
  }
  
  Point field[4];
  int count =0;
  while(count!=3){
    count = 0;
    data = fc.getFieldData();
    for(unsigned i = 0; i < data.entities.size(); i++){
      if(data.entities[i].id() >= CORNER_STARTING_INDEX-1){
        field[data.entities[i].id()-200].set_x(data.entities[i].x());
        field[data.entities[i].id()-200].set_y(data.entities[i].y());
        if(field[i].x_()!=0.0) count++;
      }
    }

  }
  // for(unsigned i = 0; i < data.entities.size(); i++){
  //  if(data.entities[i].id() >= CORNER_STARTING_INDEX-1){
  //    cout << " - Entity id: " << data.entities[i].id() << endl;
  //    // cout << "x: " << data.entities[i].x() << endl;
  //    // cout << "y: " << data.entities[i].y() << endl;
  //    // cout << "theta: " << data.entities[i].theta() << endl;
  //    cout << "width: " << data.entities[i].width() << endl;
  //    cout << "height: " << data.entities[i].height() << endl;
  //  }
  // }
  // for(unsigned i = 0; i < 4; i++){
  //  cout<<field[i].x_()<<","<<field[i].y_()<<endl;
  // }
  for(unsigned i = 0; i < data.entities.size(); i++){
    cout << " - Entity id: " << data.entities[i].id() << endl;
    cout << "x: " << data.entities[i].x() << endl;
    cout << "y: " << data.entities[i].y() << endl;
  }
  int width1 = field[2].x_() - field[0].x_();
  int width2 = field[3].x_() - field[1].x_();
  int height1 = field[1].y_() - field[0].y_();
  int height2 = field[3].y_() - field[2].y_();
  // cout<<"W1  "<<width1<<endl;
  // cout<<"W2  "<<width2<<endl;
  // cout<<"H1  "<<height1<<endl;
  // cout<<"H2  "<<height2<<endl;
  //W 1180
  //H 620
  // Robot 62 * 56 (depends on rotation)

  int w = int(width1/56);
  int h = int(height1/62);
  cout<<w<<" --- "<<h<<" --- "<<width1<<" --- "<<height1<<endl;

  int grid[h][w];
  // memset(grid, 0, sizeof grid);
  // for(int i = 0; i<h;i++){
  //  for(int j = 0; j<w;j++){
  //    cout<<grid[i][j]<<" ";
  //  }
  //  cout<<endl;
  // }
}


int main(int argc, char *argv[])
{
   double targetx1,targetx2,targetx3,targetx4,targety1,targety2,targety3,targety4;
   double robot1x,robot1y,robot2x,robot2y;

    cout << "Hello World!" << endl;

    tree t (0,0,4,3);
    cout << "Tree created" << endl;      
    int idblue = 0 ;
    int idgreen =2;
    int idred = 3;
     
    


 // get ocupancy grid 
  string ip = string(argv[1]);

 FieldComputer fc(ip);
 FieldData data = fc.getFieldData();
  int width, height, rows, cols;
  // we get width, height and matrix

  //t.show();

 // get goal positions 


 vector<int> queryIds;
    while ( data.entities.size() <6)
    {
        std::cout << "Trying to get data from filed" << std::endl;   


  
    data = fc.getFieldData();
    }
     for(unsigned i = 0; i < data.entities.size(); i++)
    {
    if( data.entities[i].id() == 101 )
    {
      targetx1 = int(data.entities[i].x()/56)  ;
      targety1 = int(data.entities[i].y()/62) + 1;
         std::cout << "found 101 co-ordinates x : "<< targetx1 << " y : " << targety1 <<std::endl;

    }
    if( data.entities[i].id() == 102 )
    {
      targetx2 = int(data.entities[i].x()/56)  ;
      targety2 = int(data.entities[i].y()/62) + 1;
      std::cout << "found 102 co-ordinates x : "<< targetx2 << " y : " << targety2 << std::endl;
    }

    if( data.entities[i].id() == 103 )
    {
      targetx3 = int(data.entities[i].x()/56)  ;
      targety3 = int(data.entities[i].y()/62) + 1;
      std::cout << "found 103 co-ordinates x : "<< targetx3 << " y : " << targety3<< std::endl;
    }
    
if( data.entities[i].id() == 112 )
    {
      targetx4 = int(data.entities[i].x()/56)  ;
      targety4 = int(data.entities[i].y()/62) +1;
      std::cout << "found 112 co-ordinates x : "<< targetx4 << " y : " << targety4<< std::endl;
     }

   }

    for(unsigned i = 0; i < data.robots.size(); i++)
    {
if( data.robots[i].id() == 2)
    {
      robot1x = int(data.robots[i].x()/56)  ;
      robot1y = int(data.robots[i].y()/62) ;
      std::cout << "found robot2 co-ordinates  x :" << robot1x<<"  y :"<< robot1y << std::endl;
     }

     if( data.robots[i].id() == 3 )
    {
      robot2x = int(data.robots[i].x()/56)  ;
      robot2y = int(data.robots[i].y()/62) ;
      std::cout << "found robot3 co-ordinates  x :" << robot2x<<"  y :"<< robot2y << std::endl;
     }
   



   }
     getWH(fc, data,width,height,rows,cols);
  vector<vector<int> > grid(rows, vector<int>(cols,0));
  printFieldData(fc, data);
  fillGrid(fc, data,grid);
 // generate tree
  t.build_map(grid);
 
  
 // exexcute step 
   


   t.setTarget(robot2x,robot2y,targetx3,targety3);
    std::cout << "found 103 co-ordinates x : "<< targetx3 << " y : " << targety3<< std::endl;
    std::cout << "found robot3 co-ordinates  x :" << robot2x<<"  y :"<< robot2y << std::endl;
   t.start_search();
 
   std::vector<node*> p;

   t.showPath(p);

   for (int m =0 ; m < p.size();m++)
   {    // path is in reverse.
        std::cout<< "Going to given goal " << std::endl;
        
        
        g2p(ip,3,p[p.size()-m]->x,p[p.size()-m]->y);

        

   }
       /*g2p(ip,3,1,1);
        g2p(ip,3,1,2);
        g2p(ip,3,1,3);
        g2p(ip,3,1,4);
*/
 // Repeat   

  std::cout << " Reached Target" << std::endl;





    return 0;
}
