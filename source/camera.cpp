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


#include "main.h"
#include "camera.h"
#include "vetor.h"
#include "jogo.h"
#include "partida.h"

Camera::Camera(Jogo *jogo, Vetor origem, Vetor alvo) {
	this->origem = origem;
	this->alvo = alvo;
	
	this->contador = 0;
	this->jogo = jogo;
}

void Camera::atualiza(float tempo) {
	switch (this->modo) {
		case CAM_GIRO:
			// tempo: 2 segundos
			// origem (x, y): rotacao, de pi/3 a -pi/2
			//             z: 10 a 100
			// alvo x: 0
			//      y: de 100 a 0
			//      z: de 10 a 0

			contador += tempo;
			
			if (contador > 2000)
				contador = 2000;

			origem.x = (120 + 0.03 * contador) * cos(M_PI/3 - 5*M_PI/12000 * contador);
			origem.y = (120 + 0.03 * contador) * sin(M_PI/3 - 5*M_PI/12000 * contador);
			origem.z = 10 + 0.045 * contador;

			alvo.x = 0;
			alvo.y = 100 - 0.05 * contador;
			alvo.z = 10 - 0.005 * contador;

			if (contador == 2000) {
				this->setModo(CAM_ESTATICA);
				contador = 0;
			}
			
			break;
		case CAM_TV:
			alvo = jogo->getPartida()->getDisco()->getPos();
			break;
	}
}

void Camera::setModo(int modo)
{
	switch (modo) {
		case CAM_ESTATICA:
			break;
		case CAM_GIRO:
			break;
		case CAM_TV:
			break;
	}

	this->modo = modo;
}

/******************* Movimentacao da camera *******************/

void Camera::zoomup(void){
	if (this->origem.z < 300)
		this->origem.z+=10;
}

void Camera::zoomdown(void){
	if (this->origem.z > -300)
		this->origem.z-=10;
}

void Camera::moveup(void) {
	Vetor v = (alvo - origem);
	if (v.norma() > 20)
		this->origem += v.versor() * 10;
}

void Camera::movedown(void) {
	Vetor v = (alvo - origem);
	if (v.norma() < 300)
		this->origem -= v.versor() * 10;
}

void Camera::moveleft(void) {
	if (this->origem.x < 300)
		this->origem.x+=10;
}

void Camera::moveright(void) {
	if (this->origem.x > -300)
	this->origem.x-=10;
}

void Camera::rotatez(double theta) {
	float cx,cy;
//	double theta = M_PI/10;
	
	cx = origem.x;
	cy = origem.y;

	this->origem.x = cx*cos(theta) - cy*sin(theta);
	this->origem.y = cx*sin(theta) + cy*cos(theta);
}


void Camera::rotatex(double theta) {
	float cy,cz;
//	double theta = M_PI/10;
	
	cy = origem.y;
	cz = origem.z;

	this->origem.y = cy*cos(theta) - cz*sin(theta);
	this->origem.z = cy*sin(theta) + cz*cos(theta);
}
/*****************************************************************/
