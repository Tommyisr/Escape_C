#include "escapeTechnion.h"

struct escapeTechnion_t {
	List Order;
	Set Company;
	Set Escaper;
	int days;
	int faculties[19];
};

static void sortList(EscapeTechnion system, Order order) {
	Order current = listGetFirst(system->Order);

	while (current) {
		if (getTimeDay(order) < getTimeDay(current)) {
			listInsertBeforeCurrent(system->Order, order);
			return;
		} else if (getTimeDay(order) == getTimeDay(current)) {
			if (getTimeHour(order) < getTimeHour(current)) {
				listInsertBeforeCurrent(system->Order, order);
				return;
			}

			else if (getTimeHour(order) == getTimeHour(current)) {
				if (getRoomFacultyOrder(order) < getRoomFacultyOrder(current)) {
					listInsertBeforeCurrent(system->Order, order);
					return;
				}

				else if (getRoomFacultyOrder(order)
						== getRoomFacultyOrder(current)) {
					if (getIdRoom(order) < getIdRoom(current)) {
						listInsertBeforeCurrent(system->Order, order);
						return;
					}
				}
			}
		}
		current = listGetNext(system->Order);
	}
	if (listGetSize(system->Order) == 0) {
		listInsertFirst(system->Order, order);
		return;
	}

	listInsertLast(system->Order, order);
	return;
}

/*
 * Function that checked if room's id exist or not
 */
static MtmErrorCode roomIdExist(EscapeTechnion system, int faculty, int id) {
//	Company ourCompany;
//	Company findFaculty = setGetFirst(system->Company);
//	TechnionFaculty name;
//	while (findFaculty) {
//		if (strcmp(getEmailCompany(findFaculty), email) == 0) {
//			ourCompany = findFaculty;
//			name = getFacultyCompany(findFaculty);
//			break;
//		}
//		findFaculty = setGetNext(system->Company);
//	}
	Company findFaculty = setGetFirst(system->Company);
	while (findFaculty) {
		if (faculty == getFacultyCompany(findFaculty)) {
			Set roomFaculty = getSetRoomsCompany(findFaculty);
			Room currentRoom = setGetFirst(roomFaculty);
			while (currentRoom) {
				if (getRoomId(currentRoom) == id) {
					return MTM_ID_ALREADY_EXIST;
				}
				currentRoom = setGetNext(roomFaculty);
			}
		}
		findFaculty = setGetNext(system->Company);
	}
	return MTM_ID_DOES_NOT_EXIST;
}

/*
 * Function that get minimum score for room
 */
static int calMinScore(int pr, int pe, int difficulty, int skill_level) {
	return ((pr - pe) * (pr - pe)
			+ (difficulty - skill_level) * (difficulty - skill_level));
}

/*
 * Function that checked if EMAIL is valid
 */
static MtmErrorCode emailIsValid(char* email) {
	int counter = 0, i = 0;

	while (*(email + i) != '\0') {
		if (*(email + i) == '@')
			counter++;
		i++;
	}
	if (counter == 1)
		return MTM_SUCCESS;
	else
		return MTM_INVALID_PARAMETER;
}

static SetElement copyElementCompany(SetElement company) {
	return copyCompany(company);
}

static void freeElementCompany(SetElement company) {
	destroyCompany(company);
}

static int compareElementCompany(SetElement company1, SetElement company2) {
	return compareEmailCompany(company1, company2);
}

//////static functions for Set Room
//static SetElement copyElementRoom(SetElement room) {
//	return copyRoom(room);
//}
//
//static void freeElementRoom(SetElement room) {
//	destroyRoom(room);
//}
//
//static int compareElementRoom(SetElement room1, SetElement room2) {
//	return compareRoomId(room1, room2);
//}

//////static functions for Set Escaper
static SetElement copyElementEscaper(SetElement escaper) {
	return copyEscaper(escaper);
}

static void freeElementEscaper(SetElement escaper) {
	destroyEscaper(escaper);
}

static int compareElementEscaper(SetElement escaper1, SetElement escaper2) {
	return compareEscaperEmail(escaper1, escaper2);
}

///static functions for List Orders
static ListElement copyElementOrder(ListElement order) {
	return copyOrder(order);
}
static void freeElementOrder(ListElement order) {
	destroyOrder(order);
}

static int numOfOrdersDayZ(List orders) {
	assert(orders!=NULL);
	int count = 0;
	Order order = listGetFirst(orders);
	while (order) {
		if (getTimeDay(order) == 0)
			count++;
		order = listGetNext(orders);
	}
	return count;
}

static void goToNextDay(List orders) {
	assert(orders!=NULL);
	Order order = listGetFirst(orders);
	while (order) {
		changeNextDay(order);
		order = listGetNext(orders);
	}
}

static int totalPrice(EscapeTechnion system, TechnionFaculty roomFaculty,
		TechnionFaculty clientFaculty, int numppl, int id) {
	assert(system!=NULL);
	Company comp = setGetFirst(system->Company);
	while (comp) {
		if (roomFaculty == getFacultyCompany(comp)) {
			Set rooms = getSetRoomsCompany(comp);
			Room room = setGetFirst(rooms);
			while (room) {
				if (getRoomId(room) == id) {
					int newprice = getRoomPrice(room);
					if (roomFaculty == clientFaculty) {
						newprice = getRoomPrice(room) * 0.75 * numppl;
						payForRoom(room, newprice);
						return newprice;
					}
					payForRoom(room, newprice * numppl);
					return newprice * numppl;

				}
				room = setGetNext(rooms);
			}
		}
		comp = setGetNext(system->Company);
	}

	return 0; // IT WON"T HAPPEN!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

// creating a new ADT for EscapeTechnion
EscapeTechnion createEscapeTechnion() {

	EscapeTechnion newSystem = malloc(sizeof(*newSystem));
	if (!newSystem)
		return NULL;
	newSystem->Company = setCreate(copyElementCompany, freeElementCompany,
			compareElementCompany);

	newSystem->Escaper = setCreate(copyElementEscaper, freeElementEscaper,
			compareElementEscaper);

	newSystem->Order = listCreate(copyElementOrder, freeElementOrder);

	newSystem->days = 0;

	if (!(newSystem->Company) || !(newSystem->Escaper) || !(newSystem->Order)) {
		destroyEscapeTechnion(newSystem);
		return NULL;
	}
	for (int i = 0; i < 19; i++) {
		newSystem->faculties[i] = 0;
	}

	return newSystem;
}

// destroying EscapeTechnion and all of its containers(set,list etc.)
void destroyEscapeTechnion(EscapeTechnion escapetechnion) {
	if (!escapetechnion)
		return;
	//if (escapetechnion->Company)
		setDestroy(escapetechnion->Company);
	//if (escapetechnion->Escaper)
		setDestroy(escapetechnion->Escaper);
	//if (escapetechnion->Order)
		listDestroy(escapetechnion->Order);
	free(escapetechnion);
}

//adding a new Company for EscapeTechnion
MtmErrorCode companyAdd(EscapeTechnion system, char* email,
		TechnionFaculty faculty) {
	assert(system!=NULL || email!=NULL);
	if (faculty < 0 || faculty >= 18)
		return MTM_INVALID_PARAMETER;
	if (emailIsValid(email) == MTM_INVALID_PARAMETER)
		return MTM_INVALID_PARAMETER;

	Company company = createCompany(email, faculty);
	Escaper escaper = createEmailEscaper(email);
	if (setIsIn(system->Company, company) == true
			|| setIsIn(system->Escaper, escaper) == true) {
		destroyCompany(company);
		destroyEscaper(escaper);
		return MTM_EMAIL_ALREADY_EXISTS;
	}
	setAdd(system->Company, company);
	destroyCompany(company);
	destroyEscaper(escaper);
	return MTM_SUCCESS;
}

// removing a Company by its Email
MtmErrorCode companyRemove(EscapeTechnion system, char* email) {
	assert(system!=NULL || email!=NULL);
	if (emailIsValid(email) == MTM_INVALID_PARAMETER)
		return MTM_INVALID_PARAMETER;

	Company company = createCompany(email, UNKNOWN);
	if (setIsIn(system->Company, company) == false) {
		destroyCompany(company);
		return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
	}

	Order new = listGetFirst(system->Order);
	while (new) {
		if (strcmp(email, getEmailCompanyOrder(new)) == 0)
			return MTM_RESERVATION_EXISTS;
		new = listGetNext(system->Order);
	}

	//*************TOTAL PRICE FROM FACULTY**********************
	int totalPrice = 0;
	Company comp = setGetFirst(system->Company);
	while (comp) {
		if (strcmp(getEmailCompany(comp), email) == 0) {
			TechnionFaculty name = getFacultyCompany(comp);
			Set rooms = getSetRoomsCompany(comp);
			Room room = setGetFirst(rooms);
			while (room) {
				totalPrice += getTotaPrice(room);
				system->faculties[name] += getTotaPrice(room);
				room = setGetNext(rooms);
			}
		}
		comp = setGetNext(system->Company);
	}
	//**********************************************************

	setRemove(system->Company, company);

	return MTM_SUCCESS;

}

// adding a Room to special Company in the system
MtmErrorCode roomAdd(EscapeTechnion system, char* email, int id, int price,
		int num_ppl, int timeOpen, int timeClose, int difficulty) {
	assert(system!=NULL || email!=NULL);

	if (emailIsValid(email) == MTM_INVALID_PARAMETER || id <= 0 || price <= 0
			|| price % 4 != 0 || num_ppl <= 0 || timeOpen < 0 || timeClose > 24
			|| timeOpen >= timeClose || difficulty < 1 || difficulty > 10)
		return MTM_INVALID_PARAMETER;

	Company company = createCompany(email, UNKNOWN);
	if (setIsIn(system->Company, company) == false) {
		destroyCompany(company);
		return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
	}
	destroyCompany(company);

	Company ourCompany;
	Company findFaculty = setGetFirst(system->Company);
	TechnionFaculty name;
	while (findFaculty) {
		if (strcmp(getEmailCompany(findFaculty), email) == 0) {
			ourCompany = findFaculty;
			name = getFacultyCompany(findFaculty);
			break;
		}
		findFaculty = setGetNext(system->Company);
	}
	if (roomIdExist(system, name, id) == MTM_ID_ALREADY_EXIST)
		return MTM_ID_ALREADY_EXIST;

	Room addRoom = createRoom(id, price, num_ppl, timeOpen, timeClose,
			difficulty);
	setAdd(getSetRoomsCompany(ourCompany), addRoom);
	return MTM_SUCCESS;
}

// removing a room from special Faculty by its ID
MtmErrorCode roomRemove(EscapeTechnion system, TechnionFaculty faculty, int id) {
	assert(system!=NULL);
	if (id < 0 || faculty < 0 || faculty >= 18)
		return MTM_INVALID_PARAMETER;
	Order order = listGetFirst(system->Order);
	while (order) {
		if (getRoomFacultyOrder(order) == faculty && getIdRoom(order) == id)
			return MTM_RESERVATION_EXISTS;
		order = listGetNext(system->Order);
	}

	Company company = setGetFirst(system->Company);
	while (company) {
		if (getFacultyCompany(company) == faculty) {
			Set rooms = getSetRoomsCompany(company);
			Room room = setGetFirst(rooms);
			while (room) {
				if (getRoomId(room) == id) {
					setRemove(rooms, room);
					return MTM_SUCCESS;
				}
				room = setGetNext(rooms);
			}
		}
		company = setGetNext(system->Company);
	}

	return MTM_ID_DOES_NOT_EXIST;
}

// adding a Client to the system
MtmErrorCode escaperAdd(EscapeTechnion system, char* email, int faculty,
		int skill_level) {
	assert(system!=NULL && email!=NULL);
	if (emailIsValid(email) == MTM_INVALID_PARAMETER || faculty < 0
			|| faculty >= 18 || skill_level < 1 || skill_level > 10)
		return MTM_INVALID_PARAMETER;
	Company company = createCompany(email, UNKNOWN);
	Escaper newEscaper = createEmailEscaper(email);
	if (setIsIn(system->Company, company) == true
			|| setIsIn(system->Escaper, newEscaper) == true) {
		destroyCompany(company);
		destroyEscaper(newEscaper);
		return MTM_EMAIL_ALREADY_EXISTS;
	}
	destroyCompany(company);
	destroyEscaper(newEscaper);
	Escaper escaperNew = createEscaper(email, faculty, skill_level);
	setAdd(system->Escaper, escaperNew);
	destroyEscaper(escaperNew);
	return MTM_SUCCESS;
}

// removing a Client from the system and all its orders
MtmErrorCode escaperRmove(EscapeTechnion system, char* email) {
	assert(system!=NULL && email!=NULL);
	if (emailIsValid(email) == MTM_INVALID_PARAMETER)
		return MTM_INVALID_PARAMETER;

	Order findEmail = listGetFirst(system->Order);
	while (findEmail) {
		if (strcmp(getEmailClientOrder(findEmail), email) == 0) {
			listRemoveCurrent(system->Order);
			findEmail=listGetFirst(system->Order);
			continue;
		}
		findEmail = listGetNext(system->Order);
		//if (!findEmail)
			//findEmail = listGetFirst(system->Order);
	}
	Escaper findEscaper = setGetFirst(system->Escaper);
	while (findEscaper) {
		if (strcmp(getEmailEscaper(findEscaper), email) == 0) {
			setRemove(system->Escaper, findEscaper);
			return MTM_SUCCESS;
		}
		findEscaper = setGetNext(system->Escaper);

	}
	return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
}

// ordering a Room
MtmErrorCode escaperOrder(EscapeTechnion system, char* email,
		TechnionFaculty faculty, int id, int timeHour, int timeDay, int num_ppl) {
	assert(system!=NULL && email!=NULL);
	if (emailIsValid(email) == MTM_INVALID_PARAMETER || faculty < 0
			|| faculty >= 18 || id <= 0 || num_ppl <= 0 || timeHour < 0
			|| timeHour > 23 || timeDay < 0)
		return MTM_INVALID_PARAMETER;
	Escaper newEscaper = createEmailEscaper(email);
	if (setIsIn(system->Escaper, newEscaper) == false) {
		destroyEscaper(newEscaper);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}
	destroyEscaper(newEscaper);
	if (roomIdExist(system, faculty, id) == MTM_ID_DOES_NOT_EXIST)
		return MTM_ID_DOES_NOT_EXIST;
	Order findTime = listGetFirst(system->Order);
	while (findTime) {
		if (strcmp(getEmailClientOrder(findTime), email) == 0
				&& getTimeDay(findTime) == timeDay
				&& getTimeHour(findTime) == timeHour)
			return MTM_CLIENT_IN_ROOM;
		if (getRoomFacultyOrder(findTime) == faculty
				&& getIdRoom(findTime) == id && getTimeDay(findTime) == timeDay
				&& getTimeHour(findTime) == timeHour)
			return MTM_ROOM_NOT_AVAILABLE;
		findTime = listGetNext(system->Order);
	}
	Escaper findEscaper = setGetFirst(system->Escaper);
	while (findEscaper) {
		if (strcmp(getEmailEscaper(findEscaper), email) == 0)
			break;
		findEscaper = setGetNext(system->Escaper);
	}
	Room ourRoom;

	Company findFaculty = setGetFirst(system->Company);
	char* companyName;
	while (findFaculty) {
		if (faculty == getFacultyCompany(findFaculty)) {
			Set roomFaculty = getSetRoomsCompany(findFaculty);
			Room currentRoom = setGetFirst(roomFaculty);
			while (currentRoom) {
				if (getRoomId(currentRoom) == id) {
					companyName = getEmailCompany(findFaculty);
					ourRoom = currentRoom;
				}
				currentRoom = setGetNext(roomFaculty);
			}
		}
		findFaculty = setGetNext(system->Company);
	}
	if (getTimeOpen(ourRoom) > timeHour || getTimeClose(ourRoom) <= timeHour)
		return MTM_ROOM_NOT_AVAILABLE;

	Order order = createOrder(companyName, email, faculty, id, timeHour,
			timeDay, num_ppl, 0, getRoomdDifficulty(ourRoom),
			getFacultyEscaper(findEscaper), getSkillEscaper(findEscaper)); // FACULTY BY ESCAPER

	sortList(system, order);
	return MTM_SUCCESS;
}

// ordering a recommend Room by formula
MtmErrorCode escaperRecommend(EscapeTechnion system, char* email, int num_ppl) {
	assert(system!=NULL || email!=NULL);
	if (emailIsValid(email) == MTM_INVALID_PARAMETER || num_ppl <= 0)
		return MTM_INVALID_PARAMETER;
	Escaper newEscaper = createEmailEscaper(email);
	if (setIsIn(system->Escaper, newEscaper) == false) {
		destroyEscaper(newEscaper);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}
	destroyEscaper(newEscaper);
	int count;
	Company countCompany = setGetFirst(system->Company);
	while (countCompany) {
		count += setGetSize(getSetRoomsCompany(countCompany));
		countCompany = setGetNext(system->Company);
	}
	if (count == 0)
		return MTM_NO_ROOMS_AVAILABLE;
	Escaper findEscaper = setGetFirst(system->Escaper);
	while (findEscaper) {
		if (strcmp(getEmailEscaper(findEscaper), email) == 0)
			break;
		findEscaper = setGetNext(system->Escaper);
	}
	int scoreRecommend;
	Room minRoom = setGetFirst(
			getSetRoomsCompany(setGetFirst(system->Company)));
	int minScore = calMinScore(getNum_ppl(minRoom), num_ppl,
			getRoomdDifficulty(minRoom), getSkillEscaper(findEscaper));
	TechnionFaculty facultyName;
	TechnionFaculty ourFaculty;
	Company findRoom = setGetFirst(system->Company);
	while (findRoom) {
		facultyName = getFacultyCompany(findRoom);
		Set roomFaculty = getSetRoomsCompany(findRoom);
		Room currentRoom = setGetFirst(roomFaculty);

		while (currentRoom) {
			scoreRecommend = calMinScore(getNum_ppl(currentRoom), num_ppl,
					getRoomdDifficulty(currentRoom),
					getSkillEscaper(findEscaper));
			if (scoreRecommend < minScore) {
				minScore = scoreRecommend;
				minRoom = currentRoom;
				ourFaculty = facultyName;
			} else if (scoreRecommend == minScore) {
				if (abs(facultyName - getFacultyEscaper(findEscaper))
						< abs(ourFaculty - getFacultyEscaper(findEscaper))) {
					minRoom = currentRoom;
					ourFaculty = facultyName;
				} else if (abs(facultyName - getFacultyEscaper(findEscaper))
						== abs(ourFaculty - getFacultyEscaper(findEscaper))) {
					if (facultyName < ourFaculty) {
						minRoom = currentRoom;
						ourFaculty = facultyName;
					} else if (facultyName == ourFaculty
							&& getRoomId(currentRoom) < getRoomId(minRoom)) // NEW!!!!!!!!!!!!!1
									{
						minRoom = currentRoom; // NEW!!!!!!!!!!!!!!!!
					}

				}
			}
			currentRoom = setGetNext(roomFaculty);
		}
		findRoom = setGetNext(system->Company);
	}
	int j = 0;
	while (1 != 0) {
		for (int i = 0; i < 24; i++) {
			MtmErrorCode result = escaperOrder(system,
					getEmailEscaper(findEscaper), ourFaculty,
					getRoomId(minRoom), i, j, num_ppl);
			if (result == MTM_SUCCESS)
				return MTM_SUCCESS;
		}
		j++;
	}
	return MTM_SUCCESS;
}

// prints all the orders for today
MtmErrorCode reportDay(EscapeTechnion system, FILE* out) {
	assert(system!=NULL);

	int numberOfEvents = numOfOrdersDayZ(system->Order);
	mtmPrintDayHeader(out, system->days, numberOfEvents);
	Order order = listGetFirst(system->Order);
	while (order && getTimeDay(order) == 0) {

		int s = listGetSize(system->Order);
		while (order != NULL && getTimeDay(order) == 0) {
			int totalprice = totalPrice(system, getRoomFacultyOrder(order),
					getClientFacultyOrder(order), getNumPplOrder(order),
					getIdRoom(order));

			mtmPrintOrder(out, getEmailClientOrder(order), getSkillOrder(order),
					getClientFacultyOrder(order), getEmailCompanyOrder(order),
					getRoomFacultyOrder(order), getIdRoom(order),
					getTimeHour(order), getDifficultyOrder(order),
					getNumPplOrder(order), totalprice);
			listGetFirst(system->Order);
			listRemoveCurrent(system->Order);
			s = listGetSize(system->Order);
			order = listGetFirst(system->Order);
			s++;
			s--;
		}
	}
	mtmPrintDayFooter(out, system->days);
	goToNextDay(system->Order);
	system->days++;

	return MTM_SUCCESS;
}

// prints the best faculties that earn most money
MtmErrorCode reportBest(EscapeTechnion system, FILE* out) {
	assert(system!=NULL);
	//int faculties[19]={0};
	int totalPrice = 0;
	for (int i = 0; i < 19; i++) {
		if (system->faculties[i] < 0)
			system->faculties[i] = 0;
	}
	Company comp = setGetFirst(system->Company);
	while (comp) {
		TechnionFaculty name = getFacultyCompany(comp);
		Set rooms = getSetRoomsCompany(comp);
		Room room = setGetFirst(rooms);
		while (room) {
			//totalPrice+=getTotaPrice(room);
			system->faculties[name] += getTotaPrice(room);
			room = setGetNext(rooms);
		}
		comp = setGetNext(system->Company);
	}
	for (int i = 0; i < 19; i++) {
		totalPrice += system->faculties[i];
	}
	mtmPrintFacultiesHeader(out, 18, system->days, totalPrice);
	int max = 0;
	TechnionFaculty index;
	int z = 3;
	while (z) {
		for (int i = 0; i < 19; i++) {
			if (system->faculties[i] > max) {
				max = system->faculties[i];
				index = i;
			}
		}
		mtmPrintFaculty(out, index, max);
		z--;
		system->faculties[index] = -1;
		max = -1;
	}
	fprintf(out, "\n");
	return MTM_SUCCESS;
}

