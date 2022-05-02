#include "DoublyLinkedMatrix.h"
#include <iostream>

using namespace std;

int main() {
	LinkedMatrix<int> m;

	
	m.expandX(2);
	m.expandY(2);

	m.expandX(1);
	m.expandY(1);

	m.formatForDebug();
	m.debugPrintConnections();

	cout << m.get(1, 2) << endl;
}
