/*
 * order.h
 *
 *  Created on: May 29, 2017
 *      Author: Tommyisr
 */

#ifndef ORDER_H_
#define ORDER_H_
#include "mtm_ex3.h"
#include "set.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct order_t* Order;

// copying an Order
Order copyOrder(Order order);

// destroying an Order by function free
void destroyOrder(Order order);

// function that returns a Faculty of the Room from this Order
TechnionFaculty getRoomFacultyOrder(Order order);

// function that returns an ID of the Room from this Order
int getIdRoom(Order order);

// function that returns an Email of Clint from this Order
char* getEmailClientOrder(Order order);

// function that returns an Email of Company from this Order
char* getEmailCompanyOrder(Order order);

// function that returns a time in Hours for this Order
int getTimeHour(Order order);

// function that returns a time in Days for this Order
int getTimeDay(Order order);

// creating an new Order by arguments: email and faculty of client and company, id of room,
//number of people, skill, price and time
Order createOrder(char* company_email, char* client_email,
		TechnionFaculty room_faculty, int id, int timeHour, int timeDay,
		int num_ppl, int totalPrice, int difficulty,
		TechnionFaculty client_faculty, int skill);

// changing the date(day +1) for all the orders
void changeNextDay(Order order);

// function that returns a Faculty of the Client from this Order
TechnionFaculty getClientFacultyOrder(Order order);

// function that returns a number of people who made this Order
int getNumPplOrder(Order order);

// function that returns a skill for this Order
int getSkillOrder(Order order);

// function that returns a difficulty for this Order
int getDifficultyOrder(Order order);

#endif /* ORDER_H_ */
