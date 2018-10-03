#include "parser.h"
#define CHUNK_SIZE 256

void gameOn(FILE* in, FILE* out, FILE* err, EscapeTechnion system) {
	char buffer[CHUNK_SIZE];
	while (fgets(buffer, CHUNK_SIZE, in) != NULL) {
		char* str = buffer;
		char* str2;
		str2 = strtok(str, " \t\n\0");
		if (str2 == NULL)
			continue;

		if (strcmp(str2, "company") == 0) {
			companyCommand(str, in, out, err, system);
		}
		if (strcmp(str2, "escaper") == 0) {
			escaperCommand(str, in, out, err, system);
		}
		if (strcmp(str2, "room") == 0) {
			roomCommand(str, in, out, err, system);
		}
		if (strcmp(str2, "report") == 0) {
			reportCommand(str, in, out, err, system);
		}
	}
}

void companyCommand(char* str, FILE* in, FILE* out, FILE* err,
		EscapeTechnion system) {
	char* str2 = strtok(NULL, " \t");
	char* email = strtok(NULL, " \t\n\0");
	if (strcmp(str2, "add") == 0) {
		char* fac = strtok(NULL, " \t\n\0");
		MtmErrorCode result = companyAdd(system, email,
				funcTranslateCharToInt(fac));
		if (result != MTM_SUCCESS)
			mtmPrintErrorMessage(err, result);

	}
	if (strcmp(str2, "remove") == 0) {
		MtmErrorCode result = companyRemove(system, email);
		if (result != MTM_SUCCESS)
			mtmPrintErrorMessage(err, result);
	}
}

void escaperCommand(char* str, FILE* in, FILE* out, FILE* err,
		EscapeTechnion system) {
	char* str2 = strtok(NULL, " \t\n\0");
	char* email = strtok(NULL, " \t\n\0");
	MtmErrorCode result;
	if (strcmp(str2, "add") == 0) {
		char* fac = strtok(NULL, " \t\n\0");
		char* skill = strtok(NULL, " \t\n\0");
		result = escaperAdd(system, email, funcTranslateCharToInt(fac),
				funcTranslateCharToInt(skill));
	}
	if (strcmp(str2, "remove") == 0) {
		result = escaperRmove(system, email);
	}
	if (strcmp(str2, "order") == 0) {
		char* fac = strtok(NULL, " \t");
		char* id = strtok(NULL, " \t");
		char* timeDay = strtok(NULL, " -");
		char* timeHour = strtok(NULL, " \t");
		char* num_ppl = strtok(NULL, " \t\n\0");

		result = escaperOrder(system, email, funcTranslateCharToInt(fac),
				funcTranslateCharToInt(id), funcTranslateCharToInt(timeHour),
				funcTranslateCharToInt(timeDay),
				funcTranslateCharToInt(num_ppl));
	}
	if (strcmp(str2, "recommend") == 0) {
		char* num_ppl = strtok(NULL, " \t\n\0");
		result = escaperRecommend(system, email,
				funcTranslateCharToInt(num_ppl));
	}
	if (result != MTM_SUCCESS)
		mtmPrintErrorMessage(err, result);
}

void roomCommand(char* str, FILE* in, FILE* out, FILE* err,
		EscapeTechnion system) {
	char* str2 = strtok(NULL, " \t");
	MtmErrorCode result;
	if (strcmp(str2, "add") == 0) {
		char* email = strtok(NULL, " \t");
		char* id = strtok(NULL, " \t");
		char* price = strtok(NULL, " \t");
		char* num_ppl = strtok(NULL, " \t");
		char* work_open = strtok(NULL, " \t-");
		char* work_close = strtok(NULL, " \t");
		char* diff = strtok(NULL, " \t\n\0");
		result = roomAdd(system, email, funcTranslateCharToInt(id),
				funcTranslateCharToInt(price), funcTranslateCharToInt(num_ppl),
				funcTranslateCharToInt(work_open),
				funcTranslateCharToInt(work_close),
				funcTranslateCharToInt(diff));

	}
	if (strcmp(str2, "remove") == 0) {
		char* fac = strtok(NULL, " \t");
		char* id = strtok(NULL, " \t\n\0");
		result = roomRemove(system, funcTranslateCharToInt(fac),
				funcTranslateCharToInt(id));
	}

	if (result != MTM_SUCCESS)
		mtmPrintErrorMessage(err, result);
}

void reportCommand(char* str, FILE* in, FILE* out, FILE* err,
		EscapeTechnion system) {
	char* str2 = strtok(NULL, " \t\n\0");
	MtmErrorCode result;
	if (strcmp(str2, "day") == 0) {
		result = reportDay(system, out);
	}
	if (strcmp(str2, "best") == 0) {
		result = reportBest(system, out);
	}
	if (result != MTM_SUCCESS)
		mtmPrintErrorMessage(err, result);
}

int funcTranslateCharToInt(char* str) {
	int a, sum = 0;
	int len = strlen(str);
	bool minus = true;
	int i = 0;
	if (str[0] == '-') {
		i++;
		minus = false;
	}
	while (i < len) {
		sum = sum * 10;
		a = str[i] - '0';
		sum += a;
		i++;
	}
	if (minus == false)
		sum = -sum;
	return sum;
}

