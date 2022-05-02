#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

//ListNode class
class ListNode {
private:
	//Fields
	int data;
	ListNode* up;
	ListNode* down; 
	ListNode* left;
	ListNode* right;
public:
	//Constructors
	ListNode(int item) {
		//Basic ListNode constructor

		data = item;
		up = nullptr;
		down = nullptr;
		right = nullptr;
		left = nullptr;
	}

	ListNode(ListNode* newUp, ListNode* newDown, ListNode* newLeft, ListNode* newRight) {
		//empty Listnode constructor with all pointer parameters
		data = 0;

		this->up = newUp;
		this->down = newDown;
		this->right = newRight;
		this->left = newLeft;
	}

	//Methods
	int getData() {
		return data; 
	}

	void setData(int item) {
		data = item;
	}

	void setUp(ListNode* newUp) {
		this->up = newUp;
	}

	ListNode* getUp() {
		return up;
	}

	void setDown(ListNode* newDown) {
		this->down = newDown;
	}

	ListNode* getDown() {
		return down;
	}

	void setLeft(ListNode* newLeft) {
		this->left = newLeft;
	}

	ListNode* getLeft() {
		return left;
	}

	void setRight(ListNode* newRight) {
		this->right = newRight;
	}

	ListNode* getRight() {
		return right;
	}
};

class LinkedMatrix {
private:
	//Fields
	ListNode* head{nullptr}; //ptr to head of a chain of nodes
	int width{1}, height{1};
	std::vector<ListNode*> allNodes;
public:
	//Constructor
	LinkedMatrix() { 
		head = new ListNode{ 0 };
	}

	//Destructor
	~LinkedMatrix() {
		for (int i = 0; i < allNodes.size(); i++) {
			delete allNodes[i];
		}
	}


	//Methods
	void expandX(int n) {
		ListNode* curY = head;
		ListNode* curX = nullptr;
		std::vector<ListNode*> lastSubRowAdded;
		ListNode* last = nullptr;

		//premake the lastSubRow with nullptrs
		for (int i = 0; i < n; i++) {
			lastSubRowAdded.push_back(nullptr);
		}

		//for every row,
		for (int y = 1; y <= height; y++) {
			curX = curY;

			//move to the end of the row
			for (int x = 1; x <= width - 1; x++) {
				curX = curX->getRight();
			}

			//set last ptr to the end of the row we're currently working with
			last = curX;

			//add new nodes to the end of the row we're working with using last as a reference
			for (int xExpand = 0; xExpand < n; xExpand++) {
				//new node, attaching it to the row above
				ListNode* newNode = new ListNode{ lastSubRowAdded[xExpand],nullptr,last,nullptr };

				//also attach the last node made (to the left) to the new node
				last->setRight(newNode);

				//also attach the old row above to this new row below (if it exists!!)
				if(lastSubRowAdded[xExpand] != nullptr){
					lastSubRowAdded[xExpand]->setDown(newNode);
				}

				//also overwrite lastSubrowAdded with data from this row as we traverse along it
				lastSubRowAdded[xExpand] = newNode;

				//save our new node to allnode vector
				allNodes.push_back(newNode);

				last = newNode;
			}

			if(y != height){ //prepare next loop
				curY = curY->getDown();
			}
		}

		width += n;
	}

	void expandY(int n) {
		ListNode* curX = head;
		ListNode* curY = nullptr;
		std::vector<ListNode*> lastSubColumnAdded;
		ListNode* last = nullptr;

		//premake the lastSubRow with nullptrs
		for (int i = 0; i < n; i++) {
			lastSubColumnAdded.push_back(nullptr);
		}

		//for every column,
		for (int x = 1; x <= width; x++) {
			curY = curX;

			//move to the bottom of the column
			for (int y = 1; y <= height - 1; y++) {
				//std::cout << "height:" << height << "|y:" << y << std::endl;
				curY = curY->getDown();
			}

			//set last ptr to the bottom of the column we're currently working with
			last = curY;

			//add new nodes to the bottom of the column we're working with using last as a reference
			for (int yExpand = 0; yExpand < n; yExpand++) {
				//new node, attaching it to the row above
				ListNode* newNode = new ListNode{ last,nullptr,lastSubColumnAdded[yExpand],nullptr };

				//also attach the last node made (above) to the new node
				last->setDown(newNode);

				//also attach the old row to the left to this new row to the right (if it exists!!)
				if (lastSubColumnAdded[yExpand] != nullptr) {
					lastSubColumnAdded[yExpand]->setRight(newNode);
				}

				//also overwrite lastSubrowAdded with data from this row as we traverse along it
				lastSubColumnAdded[yExpand] = newNode;

				//save our new node to allnode vector
				allNodes.push_back(newNode);

				last = newNode;
			}

			if (x != width) { //prepare next loop
				curX = curX->getRight();
			}
		}

		height += n;
	}

	int get(int x,int y) {

	}

	void insert(int item, int x, int y) {

	}

	void set(int item, int index) {

	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}

	//only to be used in method debugPrintConnections()
	//sets the data of every node to its position in the matrix (formatted as a 2-digit number xy)
	//only really designed to test matrixes with dimensions that dont extend beyond 2 dimensions :P
	void formatForDebug(){
		ListNode* curY = head;
		ListNode* curX = nullptr;
		for (int y = 1; y <= height; y++) {
			curX = curY;
			for (int x = 1; x <= width; x++) {
				////////////
				int data = stoi(std::to_string(x - 1) + std::to_string(y - 1));
				curX->setData(data);
				////////////
				if (x != width) {
					curX = curX->getRight();
				}
			}

			if (y != height) {
				curY = curY->getDown();
			}
		}
	}

	//this function tests the connections of the matrix
	//THIS FUNCTION WILL OVERWRITE YOUR DATA
	void debugPrintConnections() {
		this->formatForDebug();

		ListNode* curY = head;
		ListNode* curX = nullptr;
		for (int y = 1; y <= height; y++) {
			curX = curY;
			for (int x = 1; x <= width; x++) {
				////////////
				if (curX->getUp() != nullptr) {
					std::cout << "|u:" << std::setfill('0') << std::setw(2) << curX->getUp()->getData();
				} else {
					std::cout << "|u:" << std::setw(2) << "nc";
				}

				if (curX->getDown() != nullptr) {
					std::cout << "|d:" << std::setfill('0') << std::setw(2) << curX->getDown()->getData();
				} else {
					std::cout << "|d:" << std::setw(2) << "nc";
				}

				if (curX->getLeft() != nullptr) {
					std::cout << "|l:" << std::setfill('0') << std::setw(2) << curX->getLeft()->getData();
				} else {
					std::cout << "|l:" << std::setw(2) << "nc";
				}

				if (curX->getRight() != nullptr) {
					std::cout << "|r:" << std::setfill('0') << std::setw(2) << curX->getRight()->getData();
				} else {
					std::cout << "|r:" << std::setw(2) << "nc";
				}

				std::cout << "|";

				////////////
				if (x != width) {
					curX = curX->getRight();
					std::cout << "  ";
				}
			}
			std::cout << std::endl << std::endl;
			if (y != height) {
				curY = curY->getDown();
			}
		}
		std::cout << std::endl;
	}


void printMatrix() {
	ListNode* curY = head;
	ListNode* curX = nullptr;
	for (int y = 1; y <= height; y++) {
		curX = curY;
		for (int x = 1; x <= width; x++) {
			std::cout << curX->getData();
			if (x != width) {
				curX = curX->getRight();
				std::cout << ",";
			}
		}
		std::cout << std::endl;
		if (y != height) {
			curY = curY->getDown();
		}
	}
	std::cout << std::endl;
}


};
