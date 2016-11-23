#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include<vector>
#include<math.h>
// class Definition for single node
class node
{
public :
    int x,y;
    double f,g,h;
    node * parent = NULL;
    int isEmpty;

    node& operator= (const node& other)
    {
        if (this != &other) {
            this->x = other.x;
            this->y = other.y;
            this->f = other.f;
            this->g = other.g;
            this->h = other.h;
            this->parent = other.parent;
            this->isEmpty = other.isEmpty;
        }
        return *this;
    }

};

// class that includes 2D map of nodes and perform path planning
class tree{

public:
    std::vector<std::vector<node> > graph;

    std::vector<node*> open_list;
    std::vector<node*> closed_list;
    node start ;
    node goal ;
    int goalReached = 0 ;
    double fmin = 10000;
    // constructor
    tree (int m , int n , int p,int q)
    {
        start.x = m;
        start.y = n;
        goal.x = p;
        goal.y = q;

        start.g = 0;
        start.h = sqrt((m-p)*(m-p) + (n-q)*(n-q));
        start.f = start.g+start.h ;
    }


     void setTarget (int m , int n , int p,int q)
    {
        start.x = m;
        start.y = n;
        goal.x = p;
        goal.y = q;

        start.g = 0;
        start.h = sqrt((m-p)*(m-p) + (n-q)*(n-q));
        start.f = start.g+start.h ;
    }

    void build_map(std::vector<std::vector<int> > a)
    {

        for(int p =0; p< a.size() ;p++)

        {
            std::vector<node> t ;
            for (int q=0;q<a[0].size();q++)
            {
                node *temp = new node();
               // std::cout<<"APQ ---  "<<a[p][q] << std::endl;
                temp->isEmpty = a[p][q];
                temp->x = p;
                temp->y = q;
                t.push_back(*temp);
            }
            graph.push_back(t);
        }
    }



    void getNeighbours(node*t,std::vector<node*> & neighbours )
    {

        int tx = t->x;
        int ty = t->y;
/*
        for(int m =-1 ; m<2;m++)
        {
            for(int n =-1 ; n<2;n++)
            {
                if (tx + m < graph.size() && tx +m  >= 0 && ty + n < graph[tx].size()&& ty+n >=0)
                {
                    if (graph[tx+m][ty+n].isEmpty)
                    {
                        neighbours. push_back(&graph[tx+m][ty+n]);

                        //std::cout << " neighbour node returned : "<<tx<<"  "<<ty<<" = " << tx+m  << "  y : " << ty+n<<std::endl;
                    }
                }
            }
        }

*/        ////std::cout << " A.Nodes in neighbour list  " << neighbours.size() <<std::endl;
      int m = -1;
       int n = 0;
        if (tx + m < graph.size() && tx +m  >= 0 && ty + n < graph[tx].size()&& ty+n >=0)
         {
             if (graph[tx+m][ty+n].isEmpty == 0)
             {
                 neighbours. push_back(&graph[tx+m][ty+n]);
                 std::cout << " neighbour node returned : "<<tx<<"  "<<ty<<" = " << graph[tx+m][ty+n].x  << "  y : " << graph[tx+m][ty+n].y << "Empty ?" <<graph[tx+m][ty+n].isEmpty <<std::endl;

             }
         }

         m = 0;
         n = -1;
          if (tx + m < graph.size() && tx +m  >= 0 && ty + n < graph[tx].size()&& ty+n >=0)
           {
               if (graph[tx+m][ty+n].isEmpty == 0)
               {neighbours. push_back(&graph[tx+m][ty+n]);
                std::cout << " neighbour node returned : "<<tx<<"  "<<ty<<" = " << graph[tx+m][ty+n].x  << "  y : " << graph[tx+m][ty+n].y << "Empty ?" <<graph[tx+m][ty+n].isEmpty <<std::endl;
               }
           }


          m = 1;
          n = 0;
           if (tx + m < graph.size() && tx +m  >= 0 && ty + n < graph[tx].size()&& ty+n >=0)
            {
                if (graph[tx+m][ty+n].isEmpty == 0)
                {
                 neighbours. push_back(&graph[tx+m][ty+n]);
                 std::cout << " neighbour node returned : "<<tx<<"  "<<ty<<" = " << graph[tx+m][ty+n].x  << "  y : " << graph[tx+m][ty+n].y << "Empty ?" <<graph[tx+m][ty+n].isEmpty <<std::endl;
                }
            }

           m = 0;
           n = 1;
            if (tx + m < graph.size() && tx +m  >= 0 && ty + n < graph[tx].size()&& ty+n >=0)
             {
                 if (graph[tx+m][ty+n].isEmpty == 0)

                 {neighbours. push_back(&graph[tx+m][ty+n]);
                  std::cout << " neighbour node returned : "<<tx<<"  "<<ty<<" = " << graph[tx+m][ty+n].x  << "  y : " << graph[tx+m][ty+n].y << "Empty ?" <<graph[tx+m][ty+n].isEmpty <<std::endl;
                 }
             }

        return ;
    }

    void show()
    {
        for(int p =0; p< graph.size() ;p++)

        {
            for (int q=0;q<graph[p].size();q++)
            {
                std::cout<< graph[p][q].isEmpty << " " ;
            }
            std::cout<<std::endl;
        }

    }

    void getCost(node *c,std::vector<node*> t)
    {
        for ( int m = 0 ; m < t.size() ; m++)
        {
            t[m]->g = c->g + sqrt((t[m]->x - c->x)*(t[m]->x - c->x)+ (t[m]->y - c->y)*(t[m]->y - c->y));
            t[m]->h = sqrt((t[m]->x - goal.x)*(t[m]->x - goal.x)+ (t[m]->y - goal.y)*(t[m]->y - goal.y));
            t[m]->f = t[m]->g+ t[m]->h;
        }
    }

    void start_search()
    {
        open_list.push_back(&start);
        node *curr = & start ;
        node *next;

        std::cout<<" search started"<<std::endl;
        int mt;
        while( goalReached == 0 )
        {
           // std::cout<<"number of elements in openlist = "<<open_list.size() <<std::endl;
            fmin = 1000;
            for ( int m = 0 ; m < open_list.size() ; m++)
            {
                if(fmin > open_list[m]->f)
                {
                    fmin = open_list[m]->f;
                    curr =  open_list[m];
                    mt = m;
                }
            }
            closed_list.push_back(curr);
            std::cout << "--------------------------------------------------------------------"<<std::endl;
            //std::cout <<  "  node deleted from open list x : " << open_list[mt]->x <<std::endl;
            //std::cout << "  node deleted from open list y : " << open_list[mt]->y <<std::endl;

            std::cout<< "  node x : " << curr->x<< "  node  y : " << curr->y <<std::endl;
            open_list.erase(open_list.begin()+ mt);
            if ( curr->x == goal.x && curr->y ==goal.y)
            {
                goalReached = 1;
            }
            std::vector<node*> neighbours;
            getNeighbours(curr ,neighbours);
            getCost(curr,neighbours) ;
            //std::cout<<" cost returned "<<std::endl;
            ////std::cout << " A.Nodes neighbours " << neighbours.size() <<std::endl;

            for(int m = 0 ;  m < open_list.size() ; m++)
            {
                for(int n = 0 ; n < neighbours.size();n++)
                {
                    if(open_list[m]->x == neighbours[n]->x && open_list[m]->y == neighbours[n]->y)
                    {
                        if (open_list[m]->f > neighbours[n]->f)
                        {
                            open_list.erase(open_list.begin()+m  );
                            m--;
                        }
                        else
                        {
                            neighbours.erase(neighbours.begin() + n );
                            n--;
                        }
                    }
                }
            }

            //std::cout << "B. Nodes neighbours " << neighbours.size() <<std::endl;

            for(int m = 0 ;  m < closed_list.size() ; m++)
            {
                for(int n = 0 ; n < neighbours .size();n++)
                {
                    //std::cout <<  " n out = " <<n<<std::endl;
                    //std::cout << "Nodes neighbours in closed " << neighbours.size() <<std::endl;

                    if(closed_list[m]->y == neighbours[n]->y && closed_list[m]->x == neighbours[n]->x)
                    {
                        /* if (closed_list[m]->f > neighbours[n]->f)
                              {
                                  closed_list.erase(closed_list.begin()+m);
                              }
                              else
                              {
                                  neighbours.erase(neighbours.begin() + n);
                              }*/

                        //std::cout <<  " closed node x nei: " << neighbours[n]->x <<std::endl;
                        //std::cout <<  " closed node y nei: " << neighbours[n]->y<<std::endl;
                        //std::cout <<  " closed node x clo: " << closed_list[m]->x <<std::endl;
                        //std::cout <<  " closed node y clo: " <<  closed_list[m]->y<<std::endl;
                        //std::cout <<  " n before = " <<n<<std::endl;
                        neighbours.erase(neighbours.begin() + n );
                        n--;
                        //std::cout <<  " n after= " <<n<<std::endl;
                        //std::cout<<"xxxxxxxxx GOT HIT  xxxxxxxxx"<<std::endl;
                    }

                    //std::cout<<"completed a round"<<std::endl;
                }
            }

            //std::cout<<"remaining neighbours to be added to open list"<<std::endl;

            for(int m = 0 ; m < neighbours.size();m++)
            {
               // std::cout<<" A.neighbours added to open list"<<std::endl;

                next = neighbours[m];
                //std::cout<<" B.neighbours added to open list"<<std::endl;

                next->parent = curr ;
               // std::cout<<" C.neighbours added to open list"<<std::endl;

                open_list.push_back(next);
               // std::cout<<" D.neighbours added to open list"<<std::endl;

            }





            //std::cout << " Nodes in closed list" << closed_list.size() <<std::endl;
           // curr = next ;
        }
        //std::cout << " Nodes in closed list after target reached " << closed_list.size() <<std::endl;
        //std::cout<<"number of elements in openlist = "<<open_list.size() <<std::endl;

        return ;
    }


    void showPath(std::vector <node *> &path)
    {
        node *curr = &graph[goal.x][goal.y];
        graph[start.x][start.y].parent = nullptr;




        while(curr)
        {

            std::cout << " x : " << curr->x <<std::endl;
            std::cout << " y : " << curr->y <<std::endl;
            path.push_back(curr);
            curr = curr->parent;

            // //std::cout << " Going to parent"<<std::endl;
        }
        return;
    }


};

#endif // ASTAR_HPP




