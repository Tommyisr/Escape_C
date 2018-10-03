/*
 * EscapeTechnion.h
 *
 *  Created on: May 29, 2017
 *      Author: Tommyisr
 */

#ifndef ESCAPETECHNION_H_
#define ESCAPETECHNION_H_

#include "set.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"
#include "escaper.h"
#include "company.h"
#include "room.h"
#include <assert.h>
typedef struct escapeTechnion_t* EscapeTechnion;

// creating a new ADT for EscapeTechnion
EscapeTechnion createEscapeTechnion();

// destroying EscapeTechnion and all of its containers(set,list etc.)
void destroyEscapeTechnion(EscapeTechnion escapetechnion);

//adding a new Company for EscapeTechnion
MtmErrorCode companyAdd(EscapeTechnion system, char* email,
		TechnionFaculty faculty);

// removing a Company by its Email
MtmErrorCode companyRemove(EscapeTechnion system, char* email);

// adding a Room to special Company in the system
MtmErrorCode roomAdd(EscapeTechnion system, char* email, int id, int price,
		int num_ppl, int timeOpen, int timeClose, int difficulty);

// removing a room from special Faculty by its ID
MtmErrorCode roomRemove(EscapeTechnion system, TechnionFaculty faculty, int id);

// adding a Client to the system
MtmErrorCode escaperAdd(EscapeTechnion system, char* email, int faculty,
		int skill_level);

// removing a Client from the system and all its orders
MtmErrorCode escaperRmove(EscapeTechnion system, char* email);

// ordering a Room
MtmErrorCode escaperOrder(EscapeTechnion system, char* email,
		TechnionFaculty faculty, int id, int timeHour, int timeDay, int num_ppl);

// ordering a recommend Room by formula
MtmErrorCode escaperRecommend(EscapeTechnion system, char* email, int num_ppl);

// prints all the orders for today
MtmErrorCode reportDay(EscapeTechnion system, FILE* out);

// prints the best faculties that earn most money
MtmErrorCode reportBest(EscapeTechnion system, FILE* out);

#endif /* ESCAPETECHNION_H_ */
