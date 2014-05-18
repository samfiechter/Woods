#ifndef STRING_FMT
#define STRING_FMT 1
#include <stdarg.h>
#include <string>
#include <stdio.h>
#include <iostream>
/*
From: Igor Ivanov (igivanov@yahoo.com)  // I pulled out some EH stuff
Subject: Re: std::string and format specification fields
Newsgroups: comp.lang.c++.moderated
View: Complete Thread (10 articles) | Original Format
Date: 2002-04-09 14:42:49 PST 
*/

namespace {
  const int cMaxBufferLen = 4096;
  char buffer[cMaxBufferLen];
}

std::string vFormat(const char* format, va_list arg_ptr);
std::string Format(const char* format, ...);

#endif