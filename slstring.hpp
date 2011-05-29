#include <string>
#include <iostream>
using std::string;
using std::ostream;
using std::istream;

namespace skorpion9312 {
	
	class slstring;
	class slchar;
	class slexception;

	class slexception {
		private:
			char* message;
		public:
			slexception(const char* msg);
			const char* getMessage();
	};

	class slchar {
		private:
			slchar* next;
			slchar* prev;
			char schar;
		public:
			slchar(slchar* prev, slchar* next, char c);
			slchar(char c);
			void set(char newChar);
			char get() const;

			friend class slstring;
	};

	class slstring {
		private:
			slchar* begin;
			slchar* end;
			char* search;
			long size;
			bool replace;
			bool reversed;

			void _appendFront(char c);
			void _append(char c);
		public:
			slstring();
			slstring(const char* baseString);
			slstring(char* baseString);
			slstring(const string& baseString);
			slstring(string baseString);	
			slstring(const slstring& baseString);
			slchar* next(const slchar* c) const;
			slchar* prev(const slchar* c) const;
			slchar* setNext(slchar* source, slchar* destination);
			slchar* setPrev(slchar* source, slchar* destination);
			slchar* head() const;
			slchar* tail() const;
			slchar* setHead(slchar* h);
			slchar* setTail(slchar* t);
			void appendFront(char c);
			void append(char c);
			void append(char* str);
			void append(const char* str);
			void reverse();
			bool isReversed() const;
			long length() const;
			slchar* remove(slchar* c);
			slchar* remove(const slchar* c);
			slchar* rewind(long number) const throw(slexception);
			slchar* getChar(const char c) const throw(slexception);
			slchar* getChar(const char c, long from) const throw(slexception);
			long getCharPosition(const char c) const throw(slexception);
			long getCharPosition(const char c, long start) const throw(slexception);
			char operator[](unsigned long index) const throw(slexception);
			long operator()(const char c) const;
			long operator()(const char c, long start) const;
			slstring& operator+=(const char* str);
			slstring& operator+=(char* str);
			slstring& operator+=(char c);
			slstring& operator--();
			slstring operator--(int);
			slstring& operator-=(long count);
			slstring& operator-=(char del);
			slstring& operator-=(const char* sequence);
			slstring& operator-=(char* sequence);
	};

}

ostream& operator<<(ostream& out, const skorpion9312::slstring& str);
ostream& operator<<(ostream& out, const skorpion9312::slstring* str);
ostream& operator<<(ostream& out, const skorpion9312::slchar& c);
ostream& operator<<(ostream& out, const skorpion9312::slchar* c);

