/*
 * room.h
 *
 *  Created on: May 29, 2017
 *      Author: Tommyisr
 */

#ifndef ROOM_H_
#define ROOM_H_
#include "mtm_ex3.h"
#include "set.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct room_t* Room;

// copying a Room
Room copyRoom(Room room);

// destroying a Room by function free
void destroyRoom(Room room);

// comparing between two Rooms by their ID
int compareRoomId(Room room1, Room room2);

// function that returns an ID of the Room
int getRoomId(Room room);

// function that returns a Price of the Room
int getRoomPrice(Room room);

// function that returns a recommend number of people for the Room
//int getRoomNum_ppl(Room room);

// function that returns a level of difficulty for the Room
int getRoomdDifficulty(Room room);

// function that checks if order time is valid for this Room according to its open hours
bool entranceTimeInvalid(Room room, int time);

// creating a new Room by arguments: ID, price, number of people, open hours and level of difficulty
Room createRoom(int id, int price, int num_ppl, int timeOpen, int timeClose,
		int difficulty);

// function that returns a time when the Room is open
int getTimeOpen(Room room);

// function that returns a time when the Room is closed
int getTimeClose(Room room);

// function that returns a recommend number of people for the Room
int getNum_ppl(Room room);

// function that changing the Total Price by paying for the room
void payForRoom(Room room, int newprice);

// function that returns an amount of money that Room is paid
int getTotaPrice(Room room);

#endif /* ROOM_H_ */
