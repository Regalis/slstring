#include "slstring.hpp"
#include <cstring>
using namespace std;
using namespace skorpion9312;

/* slexception */

slexception::slexception(const char* msg) {
	message = new char[strlen(msg)];
	strcpy(message, msg);
}

const char* slexception::getMessage() {
	return message;
}

/* slchar */

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
	replace = false;
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
	size = newSize;
	replace = false;
}

slstring::slstring(const string& base) {
	slstring(base.c_str());
}

void slstring::append(char c) {
	slchar* tmp = new slchar(end, NULL, c);
	end->next = tmp;
	end = tmp;
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
	end = tmpPrev;
	size += length;
}

slchar* slstring::rewind(long index) const throw(slexception) {
	if(index > size)
		throw slexception("Index out of range");
	slchar* current = begin;
	for(long int i = 0; i < index; i++) {
		current = current->next;	
	}
	return current;
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

slchar* slstring::remove(slchar* c) {
	this->remove((const slchar*)c);
}

slchar* slstring::remove(const slchar* c) {
	slchar* tmp = c->next;
	if(c == end)
		end = c->prev;
	else if(c == begin)
		begin = c->next;
	c->next->prev = c->prev;
	c->prev->next = c->next;
	delete c;
	--size;
	return tmp;
}

slchar* slstring::getChar(const char c, long from) const throw(slexception) {
	slchar* current = rewind(from);
	while(current != NULL) {
		if(current->get() == c)
			return current;
		current = current->next;
	}
	return NULL;
}

slchar* slstring::getChar(const char c) const throw(slexception) {
	return getChar(c, 0);
}

long slstring::getCharPosition(const char c, long from) const throw(slexception) {
	slchar* current = rewind(from);
	while(current != NULL) {
		if(current->get() == c) 
			return from;
		from++;
		current = current->next;
	}
	return -1;
}

long slstring::getCharPosition(const char c) const throw(slexception) { 
	return getCharPosition(c, 0);
}


char slstring::operator[](unsigned long index) const throw(slexception) {
	slchar* tmp = rewind(index);	
	return tmp->get();
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

slstring& slstring::operator--() {
	slchar* tmp = end->prev;
	tmp->next = NULL;
	delete end;
	end = tmp;
	--size;
	return *this;
}

slstring& slstring::operator-=(long count) {
	if(count > size)
		count = size;
	for(long i = 0; i < count; i++) {
		--(*this);
	}
	return *this;
}

slstring& slstring::operator-=(char del) {
	slchar* current = begin;
	while(current != NULL) {
		if(current->get() == del)
			current = this->remove(current);
		else
			current = current->next;
	}
	return *this;
}

slstring& slstring::operator-=(char* sequence) {
	return this->operator-=((const char*)sequence);
}


slstring& slstring::operator-=(const char* sequence) {
	long seqLen = strlen(sequence);
	slchar* current = begin;
	while(current != NULL) {
		bool found = false;
		for(long i = 0; i < seqLen; i++) {
			if(current->get() == sequence[i]) {
				current = this->remove(current);
				found = true;
				break;
			}
		}
		if(!found && current != NULL)
			current = current->next;
	}
	return *this;
}

/* external operators */

ostream& operator<<(ostream& out, const skorpion9312::slstring& str) {
	return operator<<(out, &str);
}

ostream& operator<<(ostream& out, const skorpion9312::slstring* str) {	
	const slchar* current = str->head();
	while(current != NULL) {
		out << current->get();
		current = current->getNext();
	}
	return out;
}

ostream& operator<<(ostream& out, const skorpion9312::slchar& c) {
	out << c.get();
	return out;
}

ostream& operator<<(ostream& out, const skorpion9312::slchar* c) {
	out << c->get();
	return out;
}
