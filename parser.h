/*
 * parser.h
 *
 *  Created on: Jun 9, 2017
 *      Author: Tommyisr
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "escapeTechnion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void gameOn(FILE* in, FILE* out, FILE* err, EscapeTechnion system);

void getInput(char* buffer, FILE* out, FILE* err, EscapeTechnion system);

void companyCommand(char* str,FILE* in,FILE* out,FILE* err,EscapeTechnion system);

void escaperCommand(char* str,FILE* in,FILE* out,FILE* err,EscapeTechnion system);

void roomCommand(char* str,FILE* in,FILE* out,FILE* err,EscapeTechnion system);

void reportCommand(char* str,FILE* in,FILE* out,FILE* err,EscapeTechnion system);

int funcTranslateCharToInt(char* str);

#endif /* PARSER_H_ */
