#include <string>
#include <iostream>
using std::string;
using std::ostream;
using std::istream;

namespace skorpion9312 {
	
	class slstring;
	class slchar;

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

			void append(char c);
			void append(char* str);
			void append(const char* str);
		public:
			slstring();
			slstring(const char* baseString);
			slstring(char* baseString);
			const slchar* head() const;
			const slchar* tail() const;
			long length() const;
			slstring& operator+=(const char* str);
			slstring& operator+=(char* str);
			slstring& operator+=(char c);
	};

}

ostream& operator<<(ostream& out, const skorpion9312::slstring& str);

