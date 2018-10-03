/*
 * escaper.c
 *
 *  Created on: May 29, 2017
 *      Author: Tommyisr
 */

#include "escaper.h"

struct escaper_t {

	char* email;
	int skill_level;
	TechnionFaculty faculty;
};

// copying an Escaper
Escaper copyEscaper(Escaper escaper) {
	assert(escaper!=NULL);
	Escaper visitor = malloc(sizeof(*visitor));
	if (!visitor)
		return NULL;
	visitor->email = malloc((strlen(escaper->email) + 1));
	if (!(visitor->email)) {
		free(visitor);
		return NULL;
	}
	strcpy(visitor->email, escaper->email);
	visitor->faculty = escaper->faculty;
	visitor->skill_level = escaper->skill_level;
	return visitor;
}

// destroying an Escaper by function free
void destroyEscaper(Escaper escaper) {
//	assert(escaper!=NULL);
	if (!escaper)
		return;
	free(escaper->email);
	free(escaper);
}

// comparing between two Escapers by their Email
int compareEscaperEmail(Escaper escaper1, Escaper escaper2) {
	assert(escaper1!=NULL && escaper2!=NULL);
	return strcmp(escaper1->email, escaper2->email);
}

// function that returns an Email of this Escaper
char* getEmailEscaper(Escaper escaper) {
	assert(escaper!=NULL);
	return escaper->email;
}

// function that returns a Skill of this Escaper
int getSkillEscaper(Escaper escaper) {
	assert(escaper!=NULL);
	return escaper->skill_level;
}

// function that returns a Faculty of this Escaper
TechnionFaculty getFacultyEscaper(Escaper escaper) {
	assert(escaper!=NULL);
	return escaper->faculty;
}

// creating a temporary escaper for the function SetIsIn
Escaper createEmailEscaper(char* email) {
	Escaper justEmail = malloc(sizeof(*justEmail));
	justEmail->email = malloc(strlen(email) + 1);
	if (!justEmail->email) {
		free(justEmail);
		return NULL;
	}
	strcpy(justEmail->email, email);
	return justEmail;
}

// function that creates a new Escaper by getting an Email, Faculty and Skill_level
Escaper createEscaper(char* email, int faculty, int skill_level) {
	Escaper escaper = malloc(sizeof(*escaper));
	if (!escaper)
		return NULL;
	escaper->email = malloc(strlen(email) + 1);
	if (!escaper->email) {
		destroyEscaper(escaper);
		return NULL;
	}
	strcpy(escaper->email, email);
	escaper->faculty = faculty;
	escaper->skill_level = skill_level;
	return escaper;
}

