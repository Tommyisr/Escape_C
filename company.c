#include "company.h"

struct company_t {
	TechnionFaculty faculty;
	char* email;
	Set rooms;
};

// static functions copy/free/compare for Set Elements
static SetElement copyElementRoom(SetElement room) {
	return copyRoom(room);
}
static void freeElementRoom(SetElement room) {
	destroyRoom(room);
}
static int compareElementRoom(SetElement room1, SetElement room2) {
	return compareRoomId(room1, room2);
}

// copying a Company
Company copyCompany(Company company) {
	assert(company!=NULL);
	Company copy = malloc(sizeof(*copy));
	if (!copy)
		return NULL;
	copy->email = malloc(strlen(company->email) + 1);
	if (!copy->email) {
		free(copy);
		return NULL;
	}
	strcpy(copy->email, company->email);
	copy->rooms = setCopy(company->rooms);
	if (!(copy->rooms)) {
		free(copy->email);
		free(copy);
		return NULL;
	}
	copy->faculty = company->faculty;
	return copy;
}

// destroying a Company by function free
void destroyCompany(Company company) {
	if (company == NULL)
		return;
	setDestroy(company->rooms);
	free(company->email);
	free(company);
}

// comparing between two Companies by their Email
int compareEmailCompany(Company company1, Company company2) {
	assert(company1!=NULL && company2!=NULL);
	return strcmp(company1->email, company2->email);
}

// function that returns an Email of this Company
char* getEmailCompany(Company company) {
	assert(company!=NULL);
	return company->email;
}

// function that returns a Faculty of this Company
TechnionFaculty getFacultyCompany(Company company) {
	assert(company!=NULL);
	return company->faculty;
}

// function that returns a Set of Rooms of this Company
Set getSetRoomsCompany(Company company) {
	assert(company!=NULL);
	return company->rooms;
}

// function that creates a new Company by getting an Email and Faculty
Company createCompany(char* email, TechnionFaculty faculty) {
	Company justEmail = malloc(sizeof(*justEmail));
	justEmail->email = malloc(strlen(email) + 1);
	if (!justEmail->email) {
		free(justEmail);
		return NULL;
	}
	strcpy(justEmail->email, email);
	justEmail->faculty = faculty;
	justEmail->rooms = setCreate(copyElementRoom, freeElementRoom,
			compareElementRoom);
	return justEmail;
}

