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


#include <math.h>
#include "vetor.h"

Vetor::Vetor(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
/*
Vetor::Vetor(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0;
}
*//*
Vetor::Vetor()
{
	// nada...
}*/

Vetor::Vetor(const Vetor &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vetor &Vetor::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

Vetor &Vetor::operator=(const Vetor &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

Vetor &Vetor::operator=(float f)
{
	this->x = f;
	this->y = f;
	this->z = f;
	return *this;
}

Vetor &Vetor::operator+(const Vetor &v) const
{
	return *(new Vetor(this->x + v.x, this->y + v.y, this->z + v.z));
}

Vetor &Vetor::operator+=(const Vetor &v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vetor &Vetor::operator-(const Vetor &v) const
{
	return *(new Vetor(this->x - v.x, this->y - v.y, this->z - v.z));
}

Vetor &Vetor::operator-=(const Vetor &v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Vetor &Vetor::operator-() const
{
	return *(new Vetor(-this->x, -this->y, -this->z));
}

Vetor &Vetor::operator*(float f) const
{
	return *(new Vetor(this->x * f, this->y * f, this->z * f));
}

Vetor &Vetor::operator/(float f) const
{
	if (f == 0)
		f = 1;
	return *(new Vetor(this->x / f, this->y / f, this->z / f));
}

Vetor &Vetor::operator/=(float f)
{
	if (f == 0)
		f = 1;
	this->x /= f;
	this->y /= f;
	this->z /= f;
	return *this;
}

Vetor &Vetor::operator*=(float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
	return *this;
}

float Vetor::prodEscalar(const Vetor &v) const
{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vetor Vetor::prodVetorial(const Vetor &v) const
{
	return *(new Vetor(
		this->y * v.z - v.y * this->z,
		this->z * v.x - v.z * this->x,
		this->x * v.y - v.x * this->y));	
}

float Vetor::norma() const
{
	return sqrt(
		pow(this->x, 2) +
		pow(this->y, 2) +
		pow(this->z, 2));
}

Vetor &Vetor::versor() const
{
	float n = this->norma();
	return *this / n;
}

void Vetor::normaliza()
{
	float n = this->norma();
	this->x /= n;
	this->y /= n;
	this->z /= n;
}

void Vetor::inverte()
{
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
}

Vetor &operator*(float f, const Vetor v)
{
	return v * f;
}

bool Vetor::operator==(const Vetor &v)
{
	return (x == v.x && y == v.y && z == v.z);
}

bool Vetor::operator==(float f)
{
	return (x == f && y == f && z == f);
}
