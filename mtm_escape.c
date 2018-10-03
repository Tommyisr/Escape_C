/*
 * main.c
 *
 *  Created on: Jun 9, 2017
 *      Author: Tommyisr
 */

#include "escapeTechnion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

static void closeFiles(FILE* a, FILE* b, FILE* c) {
	if (a != NULL)
		fclose(a);
	if (b != NULL)
		fclose(b);
	if (c != NULL)
		fclose(c);

}

int main(int argc, char** argv) {

	//printf("%d \n",argc);
	FILE* err = fopen("err", "w");
	FILE* in = NULL;
	FILE* out = NULL;

	if (argc > 5 || argc == 2 || argc == 4) {
		mtmPrintErrorMessage(err, MTM_INVALID_COMMAND_LINE_PARAMETERS);
		closeFiles(err, NULL, NULL);
		return 0;
	}

	if (argc == 1) {
		in = stdin;
		out = stdout;
	}

	if (argc == 3) {
		if (strcmp(argv[1], "-i") == 0 && strcmp(argv[2], "-o") != 0) {
			in = fopen(argv[2], "r");
			out = stdout;
			if (!in) {
				mtmPrintErrorMessage(err, MTM_CANNOT_OPEN_FILE);
				closeFiles(err, in, out);
			}

		}
		if (strcmp(argv[1], "-o") == 0 && strcmp(argv[2], "-i") != 0) {
			out = fopen(argv[2], "w");
			in = stdin;
			if (!in) {
				mtmPrintErrorMessage(err, MTM_CANNOT_OPEN_FILE);
				closeFiles(err, in, out);
			}

		}

	}

	if (argc == 5 && strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0) {
		in = fopen(argv[2], "r");
		out = fopen(argv[4], "w");
		if (!in || !out) {
			mtmPrintErrorMessage(err, MTM_CANNOT_OPEN_FILE);
			closeFiles(in, out, err);
		}

	}
	if (argc == 5 && strcmp(argv[1], "-o") == 0 && strcmp(argv[3], "-i") == 0) {
			in = fopen(argv[4], "r");
			out = fopen(argv[2], "w");
			if (!in || !out) {
				mtmPrintErrorMessage(err, MTM_CANNOT_OPEN_FILE);
				closeFiles(in, out, err);
			}

		}

//	else {
//
//		mtmPrintErrorMessage(err, MTM_INVALID_COMMAND_LINE_PARAMETERS);
//		closeFiles(in, out, err);
//		return 0;
//	}

	EscapeTechnion system = createEscapeTechnion();
	gameOn(in, out, err, system);

//fprintf(out,"\n");
	//destroyEscapeTechnion(system);
	closeFiles(in, out, err);
	destroyEscapeTechnion(system);
	return 0;
}

