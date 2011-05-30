slstring - Skorpion Linked String
=================================

An alternative string implementation. Reverse, insert, delete works in constant time.

Examples
========

	#include "slstring.hpp"
	(...)
	using namespace skorpion9312;
	int main() {
		slstring hello = "Hello world!"
		cout << hello << endl;
		hello.reverse();
		cout << hello << endl;
		hello.reverse();
		hello += " abc";
		cout << hello << endl;
		hello.appendFront("Front ");
		long pos = hello.getCharPosition('e');
	}
	(...)

License
=======

Copyright (C) Patryk Jaworski <skorpion9312@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses.

License - PL
============

Copyright (C) Patryk Jaworski <skorpion9312@gmail.com>

Niniejszy program jest wolnym oprogramowaniem - możesz go rozpowszechniać dalej
i/lub modyfikować na warunkach Powszechnej Licencji Publicznej GNU wydanej przez
Fundację Wolnego Oprogramowania, według wersji 3 tej Licencji lub dowolnej
z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on użyteczny - jednak
BEZ ŻADNEJ GWARANCJI, nawet domyślnej gwarancji PRZYDATNOŚCI HANDLOWEJ
albo PRZYDATNOŚCI DO OKREŚLONYCH ZASTOSOWAŃ. Bliższe informacje na ten temat
można uzyskać z Powszechnej Licencji Publicznej GNU.

Kopia Powszechnej Licencji Publicznej GNU powinna zostać ci dostarczona razem
z tym programem. Jeżeli nie została dostarczona, odwiedź http://www.gnu.org/licenses.

Nieoficjalne, tłumaczenie licencji znajdziesz pod adresem: http://itlaw.computerworld.pl/index.php/gpl-3/
