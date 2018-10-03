/*
 * order.c
 *
 *  Created on: May 29, 2017
 *      Author: Tommyisr
 */
#include "order.h"

struct order_t {
	char* company_email;
	char* client_email;
	int skill;
	int timeDay;
	int timeHour;
	int id;
	int difficulty;
	int num_ppl;
	int TotalPrice;
	TechnionFaculty room_faculty;
	TechnionFaculty client_faculty;
};

// copying an Order
Order copyOrder(Order order) {
	if (!order)
		return NULL;

	Order copy = malloc(sizeof(*copy));
	if (!copy)
		return NULL;

	copy->company_email = malloc((strlen(order->company_email) + 1));
	if (!(copy->company_email)) {
		free(copy);
		return NULL;
	}
	copy->client_email = malloc((strlen(order->client_email) + 1));
	if (!(copy->client_email)) {
		free(copy->company_email);
		free(copy);
		return NULL;
	}
	strcpy(copy->company_email, order->company_email);
	strcpy(copy->client_email, order->client_email);

	copy->client_faculty = order->client_faculty;
	copy->room_faculty = order->room_faculty;
	copy->TotalPrice = order->TotalPrice;
	copy->difficulty = order->difficulty;
	copy->num_ppl = order->num_ppl;
	copy->skill = order->skill;
	copy->id = order->id;
	copy->timeDay = order->timeDay;
	copy->timeHour = order->timeHour;

	return copy;
}

// destroying an Order by function free
void destroyOrder(Order order) {
	if (!order)
		return;
	free(order->company_email);
	free(order->client_email);
	free(order);
}

// function that returns an Email of Company from this Order
char* getEmailCompanyOrder(Order order) {
	assert(order!=NULL);
	return order->company_email;
}

// function that returns a Faculty of the Room from this Order
TechnionFaculty getRoomFacultyOrder(Order order) {
	assert(order!=NULL);

	return order->room_faculty;
}

// function that returns a Faculty of the Client from this Order
TechnionFaculty getClientFacultyOrder(Order order) {
	assert(order!=NULL);

	return order->client_faculty;
}

// function that returns an ID of the Room from this Order
int getIdRoom(Order order) {
	assert(order!=NULL);
	return order->id;
}

// function that returns an Email of Clint from this Order
char* getEmailClientOrder(Order order) {
	assert(order!=NULL);
	return order->client_email;
}

// function that returns a time in Hours for this Order
int getTimeHour(Order order) {
	assert(order!=NULL);
	return order->timeHour;
}

// function that returns a time in Days for this Order
int getTimeDay(Order order) {
	assert(order!=NULL);
	return order->timeDay;
}

// creating an new Order by arguments: email and faculty of client and company, id of room,
//number of people, skill, price and time
Order createOrder(char* company_email, char* client_email,
		TechnionFaculty room_faculty, int id, int timeHour, int timeDay,
		int num_ppl, int totalPrice, int difficulty,
		TechnionFaculty client_faculty, int skill) {
	Order new = malloc(sizeof(*new));
	if (!new)
		return NULL;

	new->company_email = malloc((strlen(company_email) + 1));
	if (!(new->company_email)) {
		free(new);
		return NULL;
	}
	strcpy(new->company_email, company_email);

	new->client_email = malloc((strlen(client_email) + 1));
	if (!(new->client_email)) {
		free(new->company_email);
		free(new);
		return NULL;
	}
	strcpy(new->client_email, client_email);
	new->room_faculty = room_faculty;
	new->TotalPrice = totalPrice;
	new->client_faculty = client_faculty;
	new->difficulty = difficulty;
	new->num_ppl = num_ppl;
	new->skill = skill;
	new->timeDay = timeDay;
	new->timeHour = timeHour;
	new->id = id;
	return new;
}

// changing the date(day +1) for all the orders
void changeNextDay(Order order) {
	assert(order!=NULL);
	order->timeDay--;

}

// function that returns a number of people who made this Order
int getNumPplOrder(Order order) {
	assert(order!=NULL);
	return order->num_ppl;
}

// function that returns a skill for this Order
int getSkillOrder(Order order) {
	assert(order!=NULL);
	return order->skill;

}

// function that returns a difficulty for this Order
int getDifficultyOrder(Order order) {
	assert(order!=NULL);
	return order->difficulty;

}
