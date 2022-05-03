#include "DoublyLinkedMatrix.h"
#include "TextAdventureGame.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	LinkedMatrix<Room> map;
	map.expandX(10);
	map.expandY(10);
	//11x11 tile map

	map.set(Room("Hot tub","You are in a very foggy room. Through the fog, you can see a nice warm bubbling hot tub, lined in wood. A large window looms above the hot tub, making up part of the ceiling extending from the ceiling to the floor. There is nothing but black void outside."), 5, 4);
	map.set(Room("Shed", "You are in a small wooden shed. Dim light comes in the crack of the door behind you from the black sky outside. Various garden tools and other outdoor equipment lie disorganized on the floor and the walls. You vaguely smell the scent of mold and chemicals."), 7, 4);
	map.set(Room("Bathroom", "You are in a bathroom. An offshoot of the bedroom, you notice yourself in the mirror above a sink in front of you. The only source of light is a set of three bulbs above the mirror, one of them burnt out. A small shower and a toilet sit adjacent to each other. The shower is built in a stand-alone porcelain tub, which does not match the wood-lined toilet."), 3, 5);
	map.set(Room("Bedroom", "You are in a bedroom. A single queen-sized bed is in the center of the room. The floor is hard concrete, but has been layered with a sticker to appear like carpet."), 4, 5);
	map.set(Room("Living room", "You are in a spacious living room. A crackling wood fire has been burning for several hours now in the fireplace, seemingly with unlimited fuel. Other than the rather large and comfortable couch, the only other furniture in the room is a bookshelf full of blank books of varying color."), 5, 5);
	map.set(Room("Vestibule", "You are in a vestibule. Both sides of the hallway are lined with shoe racks, holding multitudes of the same black leather pair of shoes. An indent that looks like it originally held jackets now only holds a single wood pole that held the jackets. The door outside is made of marbled glass. You can see the well-lit distorted driveway outside, but the sky is completely black."), 6, 5);
	map.set(Room("Driveway", "You are outside on the driveway of the house. Grass extends on both sides, leading to a standard suburban wooden fence. Beyond the fence, past the end of the driveway, and the sky are nothing but black void, imperceivable emptiness. The ambient noise that could be heard from the crackling of the indoor fireplace can no longer be heard, leaving you in deafening and uncomfortable silence."), 7, 5);
	map.set(Room("Kitchen", "You are in what originally seems to have been a kitchen. There is no longer any furniture in this room, other than the kitchen island that stands alone in the center of the room. Piled on the island is a mountain of seemingly endless cans of beans. Patches in the paint on the walls show where counters, cabinets, and a fridge might have been."), 5, 6);
	map.set(Room("Dining Room", "You are in a dining room. A large grandiose table streches to the other side of the room. There are two dozen grandfather clocks lining the walls of the room, yet none of them tick or move. Upon further inspection, they seem to be a single part, with their features appearing to be moulded and painted on. There is only one plate and set of utensils at the dinner table, at the seat to the right of the head seat."), 5, 7);
	map.set(Room("Balcony", "You are on a balcony. There is nothing but silence and black void out here. Peering over the side of the balcony, the only thing you can see are copies of the same house and balcony immediately below, repeating endlessly. There are no repeating houses above. Nothing can be made out in the black void."), 5, 8);

	map.walkerSetPosition(5, 5);

	cout << "Controls: north, south, west, east, look" << endl << endl;
	cout << map.walkerGetData().getDescription() << endl;

	while (true) {
		string input;
		
		cout << ">";
		getline(cin, input);
		cout << endl;

		if (input == "north") {
			bool sc = map.walkerWalk(0, -1,false);
			if(sc){
				cout << map.walkerGetData().getDescription() << endl;	
			}
		} else if (input == "south") {
			bool sc = map.walkerWalk(0, 1, false);
			if (sc) {
				cout << map.walkerGetData().getDescription() << endl;
			}
		} else if (input == "west") {
			bool sc = map.walkerWalk(-1, 0, true);
			if (sc) {
				cout << map.walkerGetData().getDescription() << endl;
			}
		} else if (input == "east") {
			bool sc = map.walkerWalk(1, 0, true);
			if (sc) {
				cout << map.walkerGetData().getDescription() << endl;
			}
		} else if (input == "look") {
			cout << map.walkerGetData().getDescription() << endl;
		}
	}

	/* leftover test code that proves that it's all linked properly and that the walker works

	LinkedMatrix<int> m;

	//starts as 1x1

	m.expandX(5);
	m.expandY(5);

	m.expandX(3);
	m.expandY(3);

	//should be 9x9 now

	m.formatForDebug();
	m.debugPrintConnections();

	cout << m.walkerWalk(5,5,false) << endl;
	cout << m.walkerGetData() << endl;

	cout << m.walkerWalk(-1,-1, false) << endl;
	cout << m.walkerGetData() << endl;

	cout << m.walkerWalk(11, 11, true) << endl; //shouldnt work
	cout << m.walkerGetData() << endl;

	*/
}
