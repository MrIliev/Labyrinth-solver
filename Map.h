#pragma once
#include "Cell.h"
#include <fstream>
#include <vector>

// class used for labyrinth which have rows and columns and matrix(map) of cells which representing labyrint;
class map     
{
private:
	int rows;
	int columns;
	Node** cells;
public:
	map():cells(NULL),rows(0),columns(0){};
	~map()
	{
		clearMap();
	}

	void fill_map(std::istream &in,int rws,int cols) // function which fills matrix and set its dimensions used above
	{
		rows=rws;
		columns=cols;
		cells = new Node* [rows];
		for (int i =0;i<rows;++i)
		{
			cells[i]=new Node[cols];
		}
		for (int i =0;i<rows;++i)
		{
			for (int j =0;j<columns;++j)
			{
				char pnt;
				//cout<<"enter symbol ";
				in>>pnt;
				cells[i][j].set_Node(i,j,0,pnt,0,0);
			}
		}
	}
	void clearMap()// clearing matrix , making it empty
	{
		for (int i=0;i<rows;++i)
		{
			delete [] cells[i];
		}
		delete [] cells;
	}
	void printMap()// printing matrix
	{
		for (int i=0;i<rows;++i)
		{
			for(int j=0;j<columns;++j)
			{
				cells[i][j].print_Node();
			}
			std::cout<<std::endl;
		}
	}
	int get_Rows() const   // returns rows of matrix
	{
		return rows;
	}
	int get_Columns() const     // returns cloumns of matrix
	{
		return columns;
	}
	void read_Map_from_file(std::ifstream & inputfile,int rows,int cols)//reading matrix from file and set it
	{
		inputfile.clear();
		inputfile.seekg(0,std::ios::beg);
		fill_map(inputfile,rows,cols);
	}
	bool read_Dimensions_from_File(std::ifstream& inputfile)// reading dimensions of matrix from file ,
	{
		inputfile.clear();
		inputfile.seekg(0,std::ios::beg);
		int counter=0,buffrows=0,buffcols=0;
		char c;
		while (inputfile.get(c) && c != '\n')
		{

			buffcols++;
		}
		if (buffcols>0)
		{
			buffrows++;

			//inputfile.seekg(0,std::ios::app);
			while (inputfile.get(c))
			{
				if (c == '\n')
				{
					// the number of columns on each line must be the same
					if (buffcols != counter)
					{
						rows=buffrows;
						columns=buffcols;
						return true;
					}

					buffrows++;
					counter = 0;
				}
				else
				{
					counter++;

				}


			}

		}
		return false;
	}
	bool read_From_File(char* path)// upper 2 functions in one, first reading dimensions, then reading matrix
	{
		std:: ifstream in(path);
		if (!in)
		{
			return false;
		}

		//int rows,cols;
		if (read_Dimensions_from_File(in))
		{
			read_Map_from_file(in,rows,columns);
		}
		return true;
	}
	Node* get_Cell(int row,int column) // returns pointer to cell with entered row and column if we have one,else returns NULL;
	{
		if ((row>=0 && row<rows)&&(column>=0 && column<columns))
		{
			return &cells[row][column];
		}
		else
		{
			return NULL;
		}
	}
	

	void get_neighbours(std::vector<Node*>& neighbours, int i, int j)
	{
		if (i >= 0 && i < rows && j >= 0 && j < columns)
		{
			Node* temp = get_Cell(i-1, j-1);
			if (temp && !(temp->visited) && (temp->isWalkable()) && !(temp->inQueue))
				neighbours.push_back(temp);
			temp = get_Cell(i-1, j);
			if (temp && !(temp->visited) && (temp->isWalkable()) && !(temp->inQueue))
				neighbours.push_back(temp);
			temp = get_Cell(i-1, j+1);
			if (temp && !(temp->visited) && (temp->isWalkable()) && !(temp->inQueue))
				neighbours.push_back(temp);
			temp = get_Cell(i, j - 1);
			if (temp && !(temp->visited) && (temp->isWalkable()) && !(temp->inQueue))
				neighbours.push_back(temp);
			temp = get_Cell(i, j + 1);
			if (temp && !(temp->visited) && (temp->isWalkable()) && !(temp->inQueue))
				neighbours.push_back(temp);
			temp = get_Cell(i+1, j -1);
			if (temp && !(temp->visited) && (temp->isWalkable()) && !(temp->inQueue))
				neighbours.push_back(temp);
			temp = get_Cell(i+1, j);
			if (temp && !(temp->visited) && (temp->isWalkable()) && !(temp->inQueue))
				neighbours.push_back(temp);
			temp = get_Cell(i+1, j + 1);
			if (temp && !(temp->visited) && (temp->isWalkable()) && !(temp->inQueue))
				neighbours.push_back(temp);
		}
	}
	Node* get_neighbour(int i, int j)
	{
		if (i >= 0 && i < rows && j >= 0 && j < columns)
		{
			return &cells[i][j];
		}
	}

	void calculate_priority(Node* from, Node* to/*, Node* end*/)
	{
		float cost;
		if (from->symbol = '~')
			cost = 2;
		else
		{
			if (from->PosX != to->PosX && from->PosY != to->PosY)
			{
				cost = 1.5;
			}
			else
			{
				cost = 1;
			}
		}
		to->parent = from;

		to->priority = from->priority + cost;
		to->distance = to->priority + to->distance;
	}

	//double getDistanceCell(Node& pCell, int i, int j) // setst distance to cell, calculate distance from this cell to other ;
	//{
	//	int posx = pCell.PosX;
	//	int posy = pCell.PosY;
	//	double buffU, buffS;
	//	buffU = std::abs(posx - i);
	//	buffS = std::abs(posy - j);
	//	if (buffU < buffS)
	//	{
	//		return buffS - buffU + buffU * 1.5;
	//	}
	//	else
	//	{
	//		return buffU - buffS + buffS * 1.5;
	//	}
	//}
	void setDistanceCell(Node& pCell, int i, int j) // setst distance to cell, calculate distance from this cell to other ;
	{ 
		int posx = pCell.PosX;
		int posy = pCell.PosY;
		double buffU, buffS;

		buffU = std::abs(posx - i);
		buffS = std::abs(posy - j);

		if (buffU < buffS)
		{
			pCell.distance = buffS - buffU + buffU * 1.5;
		}
		else
		{
			pCell.distance = buffU - buffS + buffS * 1.5;
		}
	}
	double calculateDistance(Node& pCell, int i, int j)
	{
		int posx = pCell.PosX;
		int posy = pCell.PosY;
		double buffU, buffS;

		buffU = std::abs(posx - i);
		buffS = std::abs(posy - j);

		if (buffU < buffS)
		{
			return buffS - buffU + buffU * 1.5;
		}
		else
		{
			return buffU - buffS + buffS * 1.5;
		}
	}
	void setDistance(int posX, int posY ) // setting distance from every cell to end
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j<columns; j++)
			{
				setDistanceCell(cells[i][j],posX,posY);
			}
	}


	void get_visited_neighbours(std::vector<Node*>& neighbours, int i, int j)
	{
		if (i >= 0 && i < rows && j >= 0 && j < columns)
		{
			Node* temp = get_Cell(i - 1, j - 1);
			if (temp && temp->visited && temp->isWalkable())
				neighbours.push_back(temp);
			temp = get_Cell(i - 1, j);
			if (temp && temp->visited && temp->isWalkable())
				neighbours.push_back(temp);
			temp = get_Cell(i - 1, j + 1);
			if (temp && temp->visited && temp->isWalkable())
				neighbours.push_back(temp);
			temp = get_Cell(i, j - 1);
			if (temp && temp->visited && temp->isWalkable())
				neighbours.push_back(temp);
			temp = get_Cell(i, j + 1);
			if (temp && temp->visited && temp->isWalkable())
				neighbours.push_back(temp);
			temp = get_Cell(i + 1, j - 1);
			if (temp && temp->visited && temp->isWalkable())
				neighbours.push_back(temp);
			temp = get_Cell(i + 1, j);
			if (temp && temp->visited && temp->isWalkable())
				neighbours.push_back(temp);
			temp = get_Cell(i + 1, j + 1);
			if (temp && temp->visited && temp->isWalkable())
				neighbours.push_back(temp);
		}
	}


};