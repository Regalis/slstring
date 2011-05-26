#include "slstring.hpp"
#include <cstring>
using namespace std;
using namespace skorpion9312;

/* slchar definition */

slchar::slchar(slchar* prev, slchar* next, char c) {
	this->next = next;
	this->prev = prev;
	schar = c;
}

slchar::slchar(char c) {
	schar = c;
	next = NULL;
	prev = NULL;
}

void slchar::setNext(slchar* newNext) {
	next = newNext;
}

void slchar::setPrev(slchar* newPrev) {
	prev = newPrev;
}

void slchar::setChar(char c) {
	schar = c;
}

char slchar::get() const {
	return schar;
}

const slchar* slchar::getNext() const {
	return next;
}

const slchar* slchar::getPrev() const {
	return prev;
}

/* slstring definition */

slstring::slstring() {
	begin = NULL;
	end = NULL;
	size = 0;
}

slstring::slstring(const char* baseString) {
	long newSize = strlen(baseString);
	slchar* prevTmp = NULL;
	for(long i = 0; i < newSize; i++) {
		slchar* tmp = new slchar(baseString[i]);
		if(prevTmp == NULL) {
			begin = tmp;
			tmp->prev = NULL;
		} else {
			prevTmp->next = tmp;		
			tmp->prev = prevTmp;
			if(i == newSize - 1) {
				tmp->next = NULL;
				end = tmp;
			}
		}
		prevTmp = tmp;
	}
}

void slstring::append(char c) {
	slchar* tmp = new slchar(end, NULL, c);
	end->next = tmp;
	size++;
}

void slstring::append(char* str) {
	this->append((const char*) str);
}

void slstring::append(const char* str) {
	long length = strlen(str);
	slchar* tmpPrev = end;
	for(int i = 0; i < length; i++) {	
		slchar* tmp = new slchar(tmpPrev, NULL, str[i]);
		tmpPrev->next = tmp;
		tmpPrev = tmp;
	}
}

const slchar* slstring::head() const {
	return begin;
}

const slchar* slstring::tail() const {
	return end;
}

long slstring::length() const {
	return size;
}

slstring& slstring::operator+=(const char* str) {
	append(str);
}

slstring& slstring::operator+=(char* str) {
	append(str);
}

slstring& slstring::operator+=(char c) {
	append(c);
}

/* external operators */

ostream& operator<<(ostream& out, const skorpion9312::slstring& str) {	
	const slchar* current = str.head();
	while(current != NULL) {
		out << current->get();
		current = current->getNext();
	}
	return out;
}


