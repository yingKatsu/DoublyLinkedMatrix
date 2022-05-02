#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

//ListNode class
template <typename T>
class ListNode {
private:
	//Fields
	T data{};

	ListNode<T>* up;
	ListNode<T>* down;
	ListNode<T>* left;
	ListNode<T>* right;
public:
	ListNode(ListNode<T>* newUp, ListNode<T>* newDown, ListNode<T>* newLeft, ListNode<T>* newRight) {
		//empty Listnode constructor with all pointer parameters
		this->up = newUp;
		this->down = newDown;
		this->right = newRight;
		this->left = newLeft;
	}

	//Methods
	T getData() {
		return data; 
	}

	void setData(T itemptr) {
		data = itemptr;
	}

	void setUp(ListNode<T>* newUp) {
		this->up = newUp;
	}

	ListNode<T>* getUp() {
		return up;
	}

	void setDown(ListNode<T>* newDown) {
		this->down = newDown;
	}

	ListNode<T>* getDown() {
		return down;
	}

	void setLeft(ListNode<T>* newLeft) {
		this->left = newLeft;
	}

	ListNode<T>* getLeft() {
		return left;
	}

	void setRight(ListNode<T>* newRight) {
		this->right = newRight;
	}

	ListNode<T>* getRight() {
		return right;
	}
};

template <typename T>
class LinkedMatrix {
private:
	//Fields
	ListNode<T>* head{nullptr}; //ptr to head of a chain of nodes
	int width{1}, height{1};
	std::vector<ListNode<T>*> allNodes;
public:
	//Constructor
	LinkedMatrix() { 
		head = new ListNode<T>{nullptr,nullptr,nullptr,nullptr};
	}

	//Destructor
	~LinkedMatrix() {
		for (int i = 0; i < allNodes.size(); i++) {
			delete allNodes[i];
		}
	}


	//Methods
	void expandX(int n) {
		ListNode<T>* curY = head;
		ListNode<T>* curX = nullptr;
		std::vector<ListNode<T>*> lastSubRowAdded;
		ListNode<T>* last = nullptr;

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
				ListNode<T>* newNode = new ListNode<T>{ lastSubRowAdded[xExpand],nullptr,last,nullptr };

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
		ListNode<T>* curX = head;
		ListNode<T>* curY = nullptr;
		std::vector<ListNode<T>*> lastSubColumnAdded;
		ListNode<T>* last = nullptr;

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
				ListNode<T>* newNode = new ListNode<T>{ last,nullptr,lastSubColumnAdded[yExpand],nullptr };

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

	T get(int xDest,int yDest) {
		ListNode<T>* cur = head;

		for (int y = 0; y < yDest; y++) {
			cur = cur->getDown();
		}

		for (int x = 0; x < xDest; x++) {
			cur = cur->getRight();
		}

		return cur->getData();
	}

	void insert(T item, int xDest, int yDest) {
		ListNode<T>* cur = head;

		for (int y = 0; y < yDest; y++) {
			cur = cur->getDown();
		}

		for (int x = 0; x < xDest; x++) {
			cur = cur->getRight();
		}

		cur->setData(item);
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
		ListNode<T>* curY = head;
		ListNode<T>* curX = nullptr;
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
	//ONLY WORKS IN AN INT MATRIX
	void debugPrintConnections() {
		this->formatForDebug();

		ListNode<T>* curY = head;
		ListNode<T>* curX = nullptr;
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
	ListNode<T>* curY = head;
	ListNode<T>* curX = nullptr;
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
