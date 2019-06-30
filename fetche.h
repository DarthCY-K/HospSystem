#pragma once 

#include "stdafx.h"
#include <Windows.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")  
using namespace std;

void EncodeBase64(char* dbuf, char* buf128, int len);
char ConvertToBase64(char uc);