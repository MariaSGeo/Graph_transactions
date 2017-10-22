#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


/*
	functions to proccess input correctly
	each returns true if the input is correnct
	false if not
*/


bool handle_addtrans(int * n1,int * n2,float * amount){
	char * k;
	if((k = strtok(NULL," "))==NULL)
		return false;
	else{
		(*n1) = atoi(k);
		if((k = strtok(NULL," "))==NULL)
			return false;
		else{	
			(*n2) = atoi(k);
			if((k = strtok(NULL," "))==NULL)
				return false;
			else{
				(*amount) = atof(k);
				return true;
			}
		}
	}
}

bool handle_deltrans(int * n1,int * n2){
	char * k;
	if((k = strtok(NULL," "))==NULL)
		return false;
	else{
		(*n1) = atoi(k);
		if((k = strtok(NULL," "))==NULL)
			return false;
		else{	
			(*n2) = atoi(k);
			return true;
		}
	}
}

bool handle_lookup(int * type,int * n){
	char * k=strtok(NULL," ");
	if(k==NULL)
		return false;
	if(strcmp(k,"in")==0)
		(*type) = 1;
	else if(strcmp(k,"out")==0)
		(*type) = 2;
	else
		(*type) = 3;
	k=strtok(NULL," ");
	if(k==NULL)
		return false;
	else{
		(*n)=atoi(k);
		return true;
	}
}


bool handle_triangle(int * n,float * amount){
char * k;
	if((k = strtok(NULL," "))==NULL)
		return false;
	else{
		(*n) = atoi(k);
		if((k = strtok(NULL," "))==NULL)
			return false;
		else{	
			(*amount) = atof(k);
			return true;
		}
	}
}

bool handle_conn(int * n1,int * n2){
	char * k;
	if((k = strtok(NULL," "))==NULL)
		return false;
	else{
		(*n1) = atoi(k);
		if((k = strtok(NULL," "))==NULL)
			return false;
		else{	
			(*n2) = atoi(k);
			return true;
		}
	}
}


bool handle_allcycles(int * n){

	char * k;
	if((k = strtok(NULL," "))==NULL)
		return false;
	else{
		(*n) = atoi(k);
		return true;
	}
}
	

bool handle_traceflow(int * n,int * depth){
	char * k;
	if((k = strtok(NULL," "))==NULL)
		return false;
	else{
		(*n) = atoi(k);
		if((k = strtok(NULL," "))==NULL)
			return false;
		else{	
			(*depth) = atoi(k);
			return true;
		}
	}
}


bool handle_bye(){

}
bool handle_print(){

}
