/*
 * company.h
 *
 *  Created on: May 29, 2017
 *      Author: Tommyisr
 */

#ifndef COMPANY_H_
#define COMPANY_H_
#include "mtm_ex3.h"
#include "set.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "room.h"

//
typedef struct company_t* Company;

// copying a Company
Company copyCompany(Company company);

// destroying a Company by function free
void destroyCompany(Company company);

// comparing between two Companies by their Email
int compareEmailCompany(Company company1, Company company2);

// function that returns an Email of this Company
char* getEmailCompany(Company company);

// function that returns a Faculty of this Company
TechnionFaculty getFacultyCompany(Company company);

// function that returns a Set of Rooms of this Company
Set getSetRoomsCompany(Company company);

// function that creates a new Company by getting an Email and Faculty
Company createCompany(char* email, TechnionFaculty faculty);

#endif /* COMPANY_H_ */
