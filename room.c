/*
 * room.c
 *
 *  Created on: May 29, 2017
 *      Author: Tommyisr
 */
#include "room.h"

struct room_t {

	int id;
	int price;
	int num_ppl;
	int timeOpen;
	int timeClose;
	int totalPrice;
	int difficulty;
};

// copying a Room
Room copyRoom(Room room) {
	assert(room!=NULL);
	Room copy = malloc(sizeof(*copy));
	if (!copy)
		return NULL;
	copy->id = room->id;
	copy->price = room->price;
	copy->num_ppl = room->num_ppl;
	copy->timeOpen = room->timeOpen;
	copy->timeClose = room->timeClose;
	copy->difficulty = room->difficulty;
	copy->totalPrice = room->totalPrice;
	return copy;
}

// destroying a Room by function free
void destroyRoom(Room room) {
	if (!room)
		return;
	free(room);
}

// comparing between two Rooms by their ID
int compareRoomId(Room room1, Room room2) {
	assert(room1!=NULL && room2!=NULL);
	if (room1->id > room2->id)
		return 1;
	else if (room1->id < room2->id)
		return -1;
	else
		return 0;
}

// function that returns an ID of the Room
int getRoomId(Room room) {
	assert(room!=NULL);
	return room->id;
}

// function that returns a Price of the Room
int getRoomPrice(Room room) {
	assert(room!=NULL);
	return room->price;
}

// function that returns a level of difficulty for the Room
int getRoomdDifficulty(Room room) {
	assert(room!=NULL);
	return room->difficulty;
}

// function that checks if order time is valid for this Room according to its open hours
bool entranceTimeInvalid(Room room, int time) {
	assert(room!=NULL);
	return (time >= room->timeOpen && time <= room->timeClose);
}

// creating a new Room by arguments: ID, price, number of people, open hours and level of difficulty
Room createRoom(int id, int price, int num_ppl, int timeOpen, int timeClose,
		int difficulty) {
	Room newRoom = malloc(sizeof(*newRoom));
	if (!newRoom)
		return NULL;
	newRoom->id = id;
	newRoom->price = price;
	newRoom->num_ppl = num_ppl;
	newRoom->timeOpen = timeOpen;
	newRoom->timeClose = timeClose;
	newRoom->difficulty = difficulty;
	newRoom->totalPrice = 0;
	return newRoom;
}

// function that returns a time when the Room is open
int getTimeOpen(Room room) {
	assert(room!=NULL);
	return room->timeOpen;
}

// function that returns a time when the Room is closed
int getTimeClose(Room room) {
	assert(room!=NULL);
	return room->timeClose;
}

// function that returns a recommend number of people for the Room
int getNum_ppl(Room room) {
	assert(room!=NULL);
	return room->num_ppl;
}

// function that changing the Total Price by paying for the room
void payForRoom(Room room, int newprice) {
	assert(room!=NULL);
	room->totalPrice += newprice;
}

// function that returns an amount of money that Room is paid
int getTotaPrice(Room room) {
	assert(room!=NULL);
	return room->totalPrice;
}

