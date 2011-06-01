#include "slstring.hpp"
#include <cstring>
using namespace std;
using namespace skorpion9312;

/*
 * 
 * Copyright (C) Patryk Jaworski <skorpion9312@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
*/

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

void slchar::set(char c) {
	schar = c;
}

char slchar::get() const {
	return schar;
}

/* slstring definition */

slstring::slstring() {
	begin = NULL;
	end = NULL;
	search = NULL;
	separators = NULL;
	separatorStart = NULL;
	separatorEnd = NULL;
	separatorsLength = 0;
	size = 0;
	replace = false;
	reversed = false;
	lastToken = false;
}

slstring::slstring(const char* baseString) {
	slstring();
	size_t newSize = strlen(baseString);
	slchar* prevTmp = NULL;
	for(size_t i = 0; i < newSize; i++) {
		slchar* tmp = new slchar(baseString[i]);
		if(prevTmp == NULL) {
			begin = tmp;
			setPrev(tmp, NULL);
		} else {
			setNext(prevTmp, tmp);
			setPrev(tmp, prevTmp);
			if(i == newSize - 1) {
				setNext(tmp, NULL);
				setTail(tmp);
			}
		}
		prevTmp = tmp;
	}
	size = newSize;
	reversed = false;
	separators = NULL;
	lastToken = false;
	separatorStart = NULL;
	separatorEnd = NULL;
}

slstring::slstring(const string& base) {
	slstring(base.c_str());
}


slstring::slstring(const slstring& baseString) {
	begin = NULL;
	end = NULL;
	separators = NULL;
	separatorStart = NULL;
	separatorEnd = NULL;
	size = 0;
	reversed = false;
	lastToken = false;
	slchar* tmp = baseString.head();
	while(tmp != NULL) {
		append(tmp->get());
		tmp = baseString.next(tmp);
	}
}

void slstring::setLastToken(bool t) {
	lastToken = t;
}

bool slstring::isLastToken() const {
	return lastToken;
}

void slstring::_appendFront(char c) {
	if(size == 0) {
		_append(c);
		return;
	}
	slchar* tmp = new slchar(NULL, begin, c);
	begin->prev = tmp;
	begin = tmp;
	++size;
}

void slstring::appendFront(char c) {
	if(reversed) {
		_append(c);
		return;
	}
	_appendFront(c);
}

void slstring::_append(char c) {
	slchar* tmp = new slchar(end, NULL, c);
	if(size == 0)
		begin = tmp;
	else
		end->next = tmp;
	end = tmp;
	++size;
}

void slstring::append(char c) {
	if(reversed) {
		_appendFront(c);
		return;
	}
	_append(c);
}

void slstring::append(char* str) {
	this->append((const char*) str);
}

void slstring::append(const char* str) {
	size_t length = strlen(str);
	for(int i = 0; i < length; i++) {	
		if(reversed)
			_appendFront(str[i]);
		else
			_append(str[i]);
	}
	size += length;
}

slchar* slstring::rewind(size_t index) const throw(slexception) {
	if(index > size)
		throw slexception("Index out of range");
	slchar* current = head();
	for(size_t i = 0; i < index; i++) {
		current = next(current);
	}
	return current;
}

slchar* slstring::head() const {
	if(!reversed)
		return begin;
	return end;
}

slchar* slstring::tail() const {
	if(!reversed)
		return end;
	return end;
}

slchar* slstring::setHead(slchar* h) {
	if(!reversed)
		begin = h;
	else
		end = h;
	return h;
}

slchar* slstring::setTail(slchar* t) {
	if(!reversed)
		end = t;
	else
		begin = t;
	return t;
}

slchar* slstring::next(const slchar* c) const {
	if(!reversed)
		return c->next; 
	return c->prev;
}

slchar* slstring::prev(const slchar* c) const {
	if(!reversed)
		return c->prev;
	return c->next;
}

slchar* slstring::setNext(slchar* source, slchar* destination) {
	if(!reversed)
		source->next = destination;
	else
		source->prev = destination;
	return destination;	
}

slchar* slstring::setPrev(slchar* source, slchar* destination) {
	if(!reversed)
		source->prev = destination;
	else
		source->next = destination;
	return destination;
}

void slstring::reverse() {	
	reversed = !reversed;
}

bool slstring::isReversed() const {
	return reversed;
}

size_t slstring::length() const {
	return size;
}

void slstring::setSeparators(const char* s) {
	if(separators != NULL)
		delete separators;
	size_t length = strlen(s);
	separators = new char[length];
	strcpy(separators, s);
	separatorsLength = length;
	separatorStart = NULL;
}

void slstring::setSeparators(char* s) {
	setSeparators((const char*)s);
}

slchar* slstring::remove(slchar* c) {
	this->remove((const slchar*)c);
}

slchar* slstring::remove(const slchar* c) {
	slchar* tmp = next(c);
	if(c == tail())
		setTail(prev(c));
	else if(c == head())
		setHead(next(c));
	setPrev(next(c), prev(c));
	setNext(prev(c), next(c));
	delete c;
	--size;
	return tmp;
}

slchar* slstring::getChar(const char c, slchar* start) const {
	slchar* current = start;
	while(current != NULL) {
		if(current->get() == c)
			return current;
		current = next(current);
	}
	return NULL;
}

slchar* slstring::getChar(const char c, size_t start) const throw(slexception) {
	slchar* current = rewind(start);
	return getChar(c, current);
}

slchar* slstring::getChar(const char c) const throw(slexception) {
	return getChar(c, head());
}

size_t slstring::getCharPosition(const char c, size_t start) const throw(slexception) {
	slchar* current = rewind(start);
	while(current != NULL) {
		if(current->get() == c) 
			return start;
		++start;
		current = next(current);
	}
	return -1;
}

size_t slstring::getCharPosition(const char c) const throw(slexception) { 
	return getCharPosition(c, 0);
}


char slstring::operator[](size_t index) const throw(slexception) {
	slchar* tmp = rewind(index);	
	return tmp->get();
}

size_t slstring::operator()(const char c) const {
	return getCharPosition(c);
}

size_t slstring::operator()(const char c, size_t start) const {
	return getCharPosition(c, start);
}

slstring& slstring::operator+=(const char* str) {
	append(str);
}

slstring& slstring::operator+=(char* str) {
	append((const char*)str);
}

slstring& slstring::operator+=(char c) {
	append(c);
}

slstring& slstring::operator--() {
	slchar* tmp = prev(end);
	setNext(tmp, NULL);
	delete end;
	setTail(tmp);
	--size;
	return *this;
}

slstring slstring::operator--(int x) {
	slstring tmp = *this;
	this->operator--();
	return tmp;
}

slstring& slstring::operator-=(size_t count) {
	if(count > size)
		count = size;
	for(size_t i = 0; i < count; i++) {
		--(*this);
	}
	return *this;
}

slstring& slstring::operator-=(char del) {
	slchar* current = head();;
	while(current != NULL) {
		if(current->get() == del)
			current = this->remove(current);
		else
			current = next(current);
	}
	return *this;
}

slstring& slstring::operator-=(char* sequence) {
	return this->operator-=((const char*)sequence);
}


slstring& slstring::operator-=(const char* sequence) {
	size_t seqLen = strlen(sequence);
	slchar* current = head();
	while(current != NULL) {
		bool found = false;
		for(size_t i = 0; i < seqLen; i++) {
			if(current->get() == sequence[i]) {
				current = this->remove(current);
				found = true;
				break;
			}
		}
		if(!found && current != NULL)
			current = next(current);
	}
	return *this;
}

slstring& slstring::operator>>(slstring& out) {
	if(separatorStart == NULL)
		separatorStart = head();
	for(size_t i = 0; i < separatorsLength; ++i) {
		// Temporary...
		// TODO: rewrite this for
		separatorEnd = getChar(separators[i], separatorStart);
		if(separatorEnd != NULL) {
			break;
		}
	}
	out = "";
	if(separatorEnd == NULL) {
		out.setLastToken(true);
	}
	slchar* current = separatorStart;
	while(current != separatorEnd) {
		out += current->get();
		current = next(current);
	}
	if(out.isLastToken()) {
		separatorStart = NULL;
		separatorEnd = NULL;
	} else {
		separatorStart = next(separatorEnd);
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
		current = str->next(current);
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
