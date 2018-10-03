/*
 * escaper.h
 *
 *  Created on: May 29, 2017
 *      Author: Tommyisr
 */

#ifndef ESCAPER_H_
#define ESCAPER_H_

#include "mtm_ex3.h"
#include "set.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct escaper_t* Escaper;

// copying an Escaper
Escaper copyEscaper(Escaper escaper);

// destroying an Escaper by function free
void destroyEscaper(Escaper escaper);

// comparing between two Escapers by their Email
int compareEscaperEmail(Escaper escaper1, Escaper escaper2);


// function that returns an Email of this Escaper
char* getEmailEscaper(Escaper escaper);

// function that returns a Skill of this Escaper
int getSkillEscaper(Escaper escaper);

// function that returns a Faculty of this Escaper
TechnionFaculty getFacultyEscaper(Escaper escaper);

// creating a temporary escaper for the function SetIsIn
Escaper createEmailEscaper(char* email);

// function that creates a new Escaper by getting an Email, Faculty and Skill_level
Escaper createEscaper(char* email, int faculty, int skill_level);




#endif /* ESCAPER_H_ */
