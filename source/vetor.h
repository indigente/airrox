/*
	This project was developed by:
		Alexandre Amoedo Amorim (amoedo@im.ufba.br)
		Jailson A. de Brito Júnior (jailson@im.ufba.br)
		Rodrigo Rocha Gomes de Souza (rodrigo@im.ufba.br)
	This project was started at 2004.
	
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#ifndef _VETOR_H
#define _VETOR_H

class Vetor
{
	public:
		float x, y, z;
		
		Vetor(float x, float y, float z=0);
		Vetor(const Vetor &v);
		Vetor() { };
		
		Vetor &operator=(const Vetor &v);
		Vetor &operator=(float f);

		Vetor &set(float x, float y, float z=0);
		
		// vetor inverso
		Vetor &operator-() const;
		// soma entre vetores
		Vetor &operator+(const Vetor &v) const;
		Vetor &operator+=(const Vetor &v);
		// subtracao de vetores
		Vetor &operator-(const Vetor &v) const;
		Vetor &operator-=(const Vetor &v);
		// produto entre vetor e escalar
		Vetor &operator*(float f) const;
		Vetor &operator*=(float f);
		friend Vetor &operator*(float f, const Vetor v);
		// divisao entre vetor e escalar
		Vetor &operator/(float f) const;
		Vetor &operator/=(float f);

		// comparacao
		bool operator==(const Vetor &v);
		bool operator==(float f);


		
		// produtos entre vetores
		float prodEscalar(const Vetor &v) const;
		Vetor prodVetorial(const Vetor &v) const;
		
		// norma ou modulo
		float norma() const;
		Vetor &versor() const;

		// transformacoes 'in place'
		void normaliza();
		void inverte();
};

#endif
