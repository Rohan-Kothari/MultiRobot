#include <iostream>
#include <string>
#include "rbe510.hpp"

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
	// 	if(data.entities[i].id() >= CORNER_STARTING_INDEX-1){
	// 		cout << " - Entity id: " << data.entities[i].id() << endl;
	// 		// cout << "x: " << data.entities[i].x() << endl;
	// 		// cout << "y: " << data.entities[i].y() << endl;
	// 		// cout << "theta: " << data.entities[i].theta() << endl;
	// 		cout << "width: " << data.entities[i].width() << endl;
	// 		cout << "height: " << data.entities[i].height() << endl;
	// 	}
	// }
	// for(unsigned i = 0; i < 4; i++){
	// 	cout<<field[i].x_()<<","<<field[i].y_()<<endl;
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
	int grid[h][w];
	// memset(grid, 0, sizeof grid);
	// for(int i = 0; i<h;i++){
	// 	for(int j = 0; j<w;j++){
	// 		cout<<grid[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
}

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("\n Usage: %s <ip of server> \n",argv[0]);
		return 1;
	}

	string ip = string(argv[1]);
	FieldComputer fc(ip);
	fc.enableVerbose();
	FieldData data = fc.getFieldData();
	int width, height, rows, cols;
	// we get width, height and matrix
	getWH(fc, data,width,height,rows,cols);
	vector<vector<int> > grid(rows, vector<int>(cols,0));
	fillGrid(fc, data,grid);
	// printFieldData(fc, data);
	cout<<width<<endl;
	cout<<height<<endl;
	cout<<rows<<endl;
	cout<<cols<<endl;
	vector<int> queryIds;
	if (data.robots.size() > 1) {
		queryIds.push_back(data.robots[0].id());
	}
	if (data.entities.size() > 1) {
		queryIds.push_back(data.entities[0].id());
	}
	if (queryIds.size() == 0) {
		// Push back some dummy data to test log output
		cout<<"Query empty"<<endl;
	}
	return 0;
}
