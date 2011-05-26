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
			void setNext(slchar* newNext);
			void setPrev(slchar* newPrev);
			void setChar(char newChar);
			char get() const;
			const slchar* getNext() const;
			const slchar* getPrev() const;

			friend class slstring;
	};

	class slstring {
		private:
			slchar* begin;
			slchar* end;
			long size;
			bool replace;

			void append(char c);
			void append(char* str);
			void append(const char* str);
		public:
			slstring();
			slstring(const char* baseString);
			slstring(char* baseString);
			slstring(const string& baseString);
			slstring(string baseString);	
			const slchar* head() const;
			const slchar* tail() const;
			long length() const;
			slchar* remove(slchar* c);
			slchar* remove(const slchar* c);
			slchar* rewind(long number) const throw(slexception);
			slchar* getChar(const char c) const throw(slexception);
			slchar* getChar(const char c, long from) const throw(slexception);
			void reverse();
			long getCharPosition(const char c) const throw(slexception);
			long getCharPosition(const char c, long from) const throw(slexception);
			char operator[](unsigned long index) const throw(slexception);
			slstring& operator+=(const char* str);
			slstring& operator+=(char* str);
			slstring& operator+=(char c);
			slstring& operator--();
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

