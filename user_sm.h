/********************************************************
 *                                                      *
 *                                                      *
 *      user_sm.h			          	*
 *                                                      *
 *							*
 *		FI-UNAM					*
 *		17-2-2019                               *
 *                                                      *
 ********************************************************/
#define _USE_MATH_DEFINES
#include<math.h>
/*@Dareliuth: Hay que usar el 8.*/
// State Machine 
void user_sm(float intensity, float *light_values, float *observations, int size, float laser_value, int  dest, int obs, movement *movements  ,int *next_state ,float Mag_Advance ,float max_twist)
{

 int state = *next_state;
 int i;
 

 for(int i = 0; i < 8; i++)
        printf("light_values[%d] %f\n",i,light_values[i]);
 for (int i = 0; i < size ; i++ ) 
         printf("laser observations[%d] %f\n",i,observations[i]);

 switch ( state ) {

        case 0:

		*movements=generate_output(FORWARD,Mag_Advance,max_twist);
                *next_state = 1;

               	break;

        case 1:
               *movements=generate_output(LEFT,Mag_Advance,max_twist);
               *next_state = 0;
                break;


	default:
		//printf("State %d not defined used ", state);
                *movements=generate_output(STOP,Mag_Advance,max_twist);
                *next_state = 0;
                break;

                
 }

 printf("Next State: %d\n", *next_state);
}

/*
@Daredliuth: Algóritmo Bug0
*/
void Bug0(float lx, float ly, float rx, float ry, float rang, movement *movements,int *next_state, float Mag_advance, float max_twist, float *light_values, float *observations, float intensity, int size){
	float qx, qy, q, p0x, p0y;
	float angulo;
	int state = *next_state;
	int cuadrante = 0;
	int cuadrante_ant = 0;
	int obs_der = 0;
	int obs_izq = 0;
	int obs_frente = 0;
	int rango_frente = 3;
	float laser_max_d = 0.06;
	float ang_rango = 1.5; 
	//float ang_rango = 0.02*1.5;

	qx = (lx - rx);
	qy = (ly - ry);
	q = sqrt(pow(qx,2) + pow(qy,2));
	//@Daredliuth: Todo esto para una sola gota de sangre (Encontrar el ángulo adecuado al cuál dirigirse).
	//Cuadrante superior
	if(qy >= 0){
		//Derecho
		if(qx>=0){
			printf("Superior derecho\n");
			angulo = asin(qx/q)*(180/M_PI);
			//angulo = asin(qx/q);
			cuadrante = 1;
		//Izquierdo
		}else{
			printf("Superior izquierdo\n");
			//angulo = M_PI - abs(asin(qx/q));
			angulo = 180 - abs(asin(qx/q)*(180/M_PI));
			cuadrante = 2;
		}
	//Cuadrante inferior
	}else{
		//Derecho
		if(qx>=0){
			printf("Inferior derecho\n");
			//angulo = (2*M_PI) - (asin(qx/q));
			angulo = 360 - (asin(qx/q)*(180/M_PI));
			cuadrante = 4;
		//Izquierdo
		}else{
			printf("Inferior izquierdo\n");
			//angulo = M_PI + abs(asin(qx/q));
			angulo = 180 + abs(asin(qx/q)*(180/M_PI));
			cuadrante = 3;
		}
	}
	

	//printf("qx: %f\nqy: %f\nq: %f\ntheta: %f\nangulo: %f\n",qx,qy,q,(rang*180/M_PI),angulo*180/M_PI);
	printf("qx: %f\nqy: %f\nq: %f\ntheta: %f\nangulo: %f\n",qx,qy,q,(rang*180/M_PI),angulo);
/*
	for(int i = 0; i < 8; i++){
		printf("light_values[%d] %f\n",i,light_values[i]);
	}
*/
/*
	for (int i = 0; i < size ; i++ ){
		printf("laser observations[%d] %f\n",i,observations[i]);
	}
*/
/*
	for (int i = 0; i < size ; i++ ){
		//printf("laser observations[%d] %f\n",i,observations[i]);
		if(i < size/3 && observations[i]<5 && obs_der != 1){
			obs_der = 1;
			printf("Chingaderas a la derecha.\n");
		}else if(i < (size/3)*2  && observations[i]<5 && obs_frente != 1){
			obs_frente = 1;
			obs_der = 0;
			printf("Chingaderas en frente.\n");
		}else if(i > (size/3)*2  && observations[i]<5 && obs_izq != 1){
			obs_izq = 1;
			obs_der = 0;
			obs_frente = 0;
			printf("Chingaderas a la izquierda.\n");
		}else{
			printf("Nada a la vista.\n");
			obs_izq = 0;
			obs_der = 0;
			obs_frente = 0;			
		}
	}
*/
	printf("Intensidad: %f\n",intensity);
	printf("Estado: %d\n",state);
	
	switch(state){
		//@Daredliuth: Busca la dirección a la luz.
		case 0:
			*movements = generate_output(LEFT, Mag_advance, max_twist);

			//@Daredliuth: Todo esto para una sola gota de sangre (Encontrar el ángulo adecuado al cuál dirigirse).
			qx = (lx - rx);
			qy = (ly - ry);
			q = sqrt(pow(qx,2) + pow(qy,2));
			//Cuadrante superior
			if(qy >= 0){
				//Derecho
				if(qx>=0){
					printf("Superior derecho\n");
					angulo = asin(qx/q)*(180/M_PI);
					//angulo = asin(qx/q);
					cuadrante = 1;
				//Izquierdo
				}else{
					printf("Superior izquierdo\n");
					//angulo = M_PI - abs(asin(qx/q));
					angulo = 180 - abs(asin(qx/q)*(180/M_PI));
					cuadrante = 2;
				}
			//Cuadrante inferior
			}else{
				//Derecho
				if(qx>=0){
					printf("Inferior derecho\n");
					//angulo = (2*M_PI) - (asin(qx/q));
					angulo = 360 - (asin(qx/q)*(180/M_PI));
					cuadrante = 4;
				//Izquierdo
				}else{
					printf("Inferior izquierdo\n");
					//angulo = M_PI + abs(asin(qx/q));
					angulo = 180 + abs(asin(qx/q)*(180/M_PI));
					cuadrante = 3;
				}
			}					

			//if(abs(rang - angulo) < ang_rango){
			if(abs((rang*180/M_PI) - angulo) < ang_rango){
				*next_state = 1;
				p0x = rx;
				p0y = ry;
				cuadrante_ant = cuadrante;
			}
		break;
		
		//@Daredliuth: Avanza hacía la luz.
		case 1:
			/*
			//@Daredliuth: Esto funciona para el Bug1.
			if(abs(rx - p0x) > 0.1 || abs(ry - p0y) > 0.1){
				*next_state = 0;
			}*/

			/*
			if(cuadrante_ant != cuadrante){
				*next_state = 0;
			}
			*/

			for (int i = 0; i < size ; i++ ){
				if(i > rango_frente && i < (size - rango_frente)  && observations[i]<laser_max_d){
				obs_frente = 1;
				printf("Chingaderas en frente.\n");
				*next_state = 2;
				}
			}			

			if(intensity > 100){
				*next_state = 4;
			}
			*movements = generate_output(FORWARD, Mag_advance, max_twist);
		break;
	
		//@Daredliuth: Gira a la izquierda hasta poder avanzar hacia en frente.
		case 2:
			*movements=generate_output(LEFT,Mag_advance,max_twist);
			for (int i = 0; i < size ; i++ ){
				if(i > rango_frente && i < size-rango_frente){
					if(observations[i]<laser_max_d){
						obs_frente = 1;
						printf("Chingaderas en frente. Sensor[%d]:%f\n",i,observations[i]);
						*next_state = 2;	
					}
					else if(obs_frente == 0){
						printf("Nada en frente.\n");
						*next_state = 3;
						*movements=generate_output(LEFT,Mag_advance,max_twist);
						*movements=generate_output(LEFT,Mag_advance,max_twist);
					}
				}
			}
			obs_frente = 0;
			if(intensity > 100){
				*next_state = 4;
			}
		break;
		//@Daredliuth: Avanzamos hasta que no haya obstáculos a la derecha.
		case 3:
			*movements = generate_output(FORWARD, Mag_advance, max_twist);
			for (int i = 0; i < size ; i++ ){
				if(i < rango_frente){
					if(observations[i]<laser_max_d){
						obs_der = 1;
						printf("Chingaderas a la derecha. Sensor[%d]:%f\n",i,observations[i]);	
					}
					else if(obs_der == 0){
						printf("Nada a la derecha.\n");
						*next_state = 0;
						*movements=generate_output(FORWARD,Mag_advance,max_twist);
						*movements=generate_output(FORWARD,Mag_advance,max_twist);
					}
				}
				if(i > rango_frente && i < size-rango_frente){
					if(observations[i]<laser_max_d){
						obs_frente = 1;
						printf("Chingaderas en frente. Sensor[%d]:%f\n",i,observations[i]);
						*next_state = 2;	
					}
					else if(obs_frente == 0){
						printf("Nada en frente.\n");
					}
				}

			}
			obs_der = 0;
			obs_frente = 0;
			if(intensity > 100){
				*next_state = 4;
			}
		break;
		//@Daredliuth: Llegamos a la luz.
		case 4:
			*movements=generate_output(STOP,Mag_advance,max_twist);
		break;
		//@Daredliuth: Cómo me encanta buguear programas.
		default:
			printf("En que caso estoy?\n");
		break;

	}
}

//@Daredliuth: Todo esto para una sola gota de sangre (Encontrar el ángulo adecuado al cuál dirigirse).
float DeterminarAngulo(float deltaX, float deltaY, float delta){
	//Cuadrante superior
	if(deltaY >= 0){
		//Derecho
		if(deltaX>=0){
			//printf("Superior derecho\n");
			return acosf(deltaX/delta);
		//Izquierdo
		}else{
			//printf("Superior izquierdo\n");
			//return (M_PI - asinf(deltaX/delta));
			return acosf(deltaX/delta);
		}
	//Cuadrante inferior
	}else{
		//Derecho
		if(deltaX>=0){
			//printf("Inferior derecho\n");
			return ((2*M_PI) - (acosf(deltaX/delta)));
		//Izquierdo
		}else{
			//printf("Inferior izquierdo\n");
			//Moverle a estos ángulos.
			//return (M_PI + asinf(deltaX/delta));
			return (M_PI - asinf(deltaY/delta));
		}
	}

	return 0;
}

//@Daredliuth: Determinamos el cuadrante en el que se encuentra el ángulo (puede no ser necesario).
int DeterminarCuadrante(float angulo){
	if(angulo <= (M_PI/2)){
		return 1;
	}
	else if(angulo <= M_PI){
		return 2;
	}
	else if(angulo <= (M_PI*1.5)){
		return 3;
	}else{
		return 4;
	}
	return 0;
}

//@Daredliuth: Determina si los valores de X y Y están dentro de un rango.
bool DentroRango(float x, float y, float xObjetivo, float yObjetivo){
	float rango = 0.01;
	if(fabs(x - xObjetivo) < rango && fabs(y - yObjetivo) < rango ){
		printf("Dentro del rango.\n");
		return true;
	}
	return false;
}

//@Daredliuth: Determina si hay un obstáculo en frente.
bool ObstaculoFrente(int rangoLasers, int cantidadLasers, float *observaciones, float dLaser){
	for (int i = 0; i < cantidadLasers ; i++ ){
		if(i > rangoLasers && i < (cantidadLasers - rangoLasers)  && observaciones[i]<dLaser){
			//obs_frente = 1;
			printf("Obstáculo en frente.\n");
			return true;
		}
	}
	return false;
}

void RealizarMovimiento(int *seleccion, int rutina, movement *movimiento, float avance, float twist, float giroNav){
	if(rutina == 1){
		switch(*seleccion){
			case 1:
				*movimiento=generate_output(LEFT,avance,giroNav);
				printf("Movimiento hacia izquierda.\nMovimiento: %d\n",*seleccion);
				*seleccion = 2;
				//printf("Yo digo que es: %d\n", *seleccion);
			break;
			case 2:
				*movimiento=generate_output(FORWARD,avance,twist);
				printf("Movimiento hacia adelante.\nMovimiento: %d\n",*seleccion);
				*seleccion = 3;
				//printf("Yo digo que es: %d\n", *seleccion);
			break;
			case 3:
				*movimiento=generate_output(RIGHT,avance,giroNav);
				printf("Movimiento hacia derecha.\nMovimiento: %d\n",*seleccion);
				*seleccion = 4;
				//printf("Yo digo que es: %d\n", *seleccion);
			break;
			case 4:
				*movimiento=generate_output(FORWARD,avance * 1.5,twist);
				printf("Movimiento hacia adelante * 1.5.\nMovimiento: %d\n",*seleccion);
				*seleccion = 5;
				//printf("Yo digo que es: %d\n", *seleccion);
			break;
			default:
				//printf("Esto no debería pasar.\n");
			break;
		}
	}
	else{
		switch(*seleccion){
			case 1:
				*movimiento=generate_output(RIGHT,avance,giroNav);
				printf("Movimiento hacia derecha.\nMovimiento: %d\n",*seleccion);
				*seleccion = 2;
				//printf("Yo digo que es: %d\n", *seleccion);
			break;
			case 2:
				*movimiento=generate_output(FORWARD,avance,twist);
				printf("Movimiento hacia adelante.\nMovimiento: %d\n",*seleccion);
				*seleccion = 3;
				//printf("Yo digo que es: %d\n", *seleccion);
			break;
			case 3:
				*movimiento=generate_output(LEFT,avance,giroNav);
				printf("Movimiento hacia izquierda.\nMovimiento: %d\n",*seleccion);
				*seleccion = 4;
				//printf("Yo digo que es: %d\n", *seleccion);
			break;
			case 4:
				*movimiento=generate_output(FORWARD,avance * 1.5,twist);
				printf("Movimiento hacia adelante * 1.5.\nMovimiento: %d\n",*seleccion);
				*seleccion = 5;
				//printf("Yo digo que es: %d\n", *seleccion);
			break;
			default:
				//printf("Esto no debería pasar.\n");
			break;
		}
	}
}

void FocoAlcanzado(float intensidad, int *siguiente){
	if(intensidad > 100){
		*siguiente = 4;
	}
}

void Atorado(int movimiento, float xAnt, float yAnt, float x, float y, movement *movimientos, float advance, float twist, int *ator){
	int caso = 0;
	if(xAnt == x && yAnt == y){
		(*ator)++;
		if(*ator >= 5){
			srand((int) (*ator * xAnt * yAnt * movimiento));
			caso = rand()%(2-0) + 0;
			printf("Número aleatorio: %d\n", caso);
			switch(caso){
				case 0:
					*movimientos = generate_output(BACKWARD, advance/2, twist);
				break;

				case 1:
					*movimientos = generate_output(LEFT, advance, twist);
				break;

				case 2:
					*movimientos = generate_output(RIGHT, advance, twist);
				break;

				default:
				printf("EL numero aleatorio no funcióno: %d", caso);
				break;
			}
			
			printf("Tamos atorados.\n");
			*ator = 0;
		}
	}else{
		*ator = 0;
	}
	printf("Veces atorado: %d\n", *ator);
}

bool MismaPendiente(float robX, float robY, float chX, float chY, float fX, float fY){
	float rango = 0.9;
	float m1 = (fY - chY)/(fX - chX);
	float m2 = (robY - chY)/(robX - chX);
	printf("M1: %f\nM2: %f\nDeltaM: %f\n", m1, m2, (m1 - m2));
	if(fabs(m1 - m2) < rango){
		printf("Volvimos a la recta.\n");
		return true;
	}
	printf("No hemos llegado a la pendiente.\n");
	return false;
}

void Bug1(float lx, float ly, float rx, float ry, float rang, movement *movements,int *next_state, float Mag_advance, float max_twist, float *light_values, float *observations, float intensity, int size, float p0x, float p0y, float m, float *qMin, float *xMin, float *yMin, float *xChoque, float *yChoque, bool *choque, bool *circunnav, int *mov, float xAnterior, float yAnterior, int *atoradoCuenta){
	float qx, qy, q;
	float angulo;
	int state = *next_state;
	int cuadrante = 0;
	int cuadrante_ant = 0;
	int obs_der = 0;
	int obs_izq = 0;
	int obs_frente = 0;
	int rango_frente = 3;
	float laser_max_d = 0.06;
	float ang_rango = 0.02;
	float angGiroNav = 1.66;
	float angNoObs = 0.52;
	//Aumenta o disminuye los valores de avance para la circunnavegación.
	float factorCorrecion = 0.5;
	
	qx = lx - rx;
	qy = ly - ry;
	q = sqrt(pow(qx,2) + pow(qy,2));
	if (q < *qMin){
		*qMin = q;
		*xMin = rx;
		*yMin = ry;
	}

	angulo = DeterminarAngulo(qx,qy,q);
	cuadrante = DeterminarCuadrante(angulo);
	//printf("qx: %f\nqy: %f\nq: %f\nrang: %f\nangulo: %f\n",qx,qy,q,rang,angulo);
	printf("qx: %f\nqxAnt: %f\nqy: %f\nqyAnt: %f\n", rx, xAnterior, ry, yAnterior);
	printf("xMin: %f\nyMin: %f\nqMin: %f\n", *xMin, *yMin, *qMin);
	//printf("Intensidad: %f\n",intensity);
	printf("Estado: %d\n",state);
	//printf("No estoy roto***********************\n");
	
	switch(state){
		//@Daredliuth: Giramos hacia la luz.
		case 0:
			angulo = DeterminarAngulo(qx,qy,q);
			cuadrante = DeterminarCuadrante(angulo);
			*movements = generate_output(LEFT, Mag_advance, (angulo - rang));
			if(abs((angulo - rang) < ang_rango)){
				*next_state = 1;
				p0x = rx;
				p0y = ry;
				cuadrante_ant = cuadrante;
			}
			FocoAlcanzado(intensity, next_state);
		break;
		//@Daredliuth: Avanzamos hasta encontrar un osbtáculo.
		case 1:
			FocoAlcanzado(intensity, next_state);
			*movements = generate_output(FORWARD, Mag_advance, max_twist);
			if(ObstaculoFrente(rango_frente, size, observations, laser_max_d)){
				*xChoque = rx;
				*yChoque = ry;
				*choque = true;
				*next_state = 2;
				*mov = 1;
				*movements = generate_output(BACKWARD, Mag_advance/2, max_twist);
				//*movements=generate_output(LEFT,Mag_advance,max_twist);
			}
			Atorado(*mov, xAnterior, yAnterior, rx, ry, movements, Mag_advance, max_twist, atoradoCuenta);
			FocoAlcanzado(intensity, next_state);
		break;
		//@Daredliuth: Movimiento de ZigZag para circunnavegar.
		case 2:
			/*
			*movements=generate_output(LEFT,Mag_advance,angGiroNav);
			*movements=generate_output(FORWARD,Mag_advance,max_twist);
			*movements=generate_output(RIGHT,Mag_advance,angGiroNav);
			*movements=generate_output(FORWARD,Mag_advance * 1.5,max_twist);
			*/
			RealizarMovimiento(mov, 1, movements, Mag_advance * factorCorrecion, max_twist, angGiroNav);
			//printf("Movimiento post realizar: %d\n", *mov);
			//Si no hay nada en frente gira 45 grados a la derecha.
			if(*mov == 6){
				//printf("Terminamos los movimientos.\n");
				if(!ObstaculoFrente(rango_frente, size, observations, laser_max_d)){
					*movements=generate_output(RIGHT,Mag_advance,angNoObs);
					//printf("Reencontrando borde del obstáculo.");
				}
				*mov = 1;
			}
			//Si estamos ejecutando el último movimiento de la cricunnavegación.
			if(*mov == 5){
				*mov = 6;
			}
			*choque ? printf("Hay choque.\n") : printf("No hay choque.\n");
			if(DentroRango(rx, ry, *xChoque, *yChoque) && !*choque){
				printf("Llegamos al mismo punto.\n");
				*next_state = 3;
				*mov = 1;
				*movements=generate_output(RIGHT,Mag_advance,angGiroNav);
				//*movements=generate_output(RIGHT,Mag_advance,1.57);
			}
			Atorado(*mov, xAnterior, yAnterior, rx, ry, movements, Mag_advance, max_twist, atoradoCuenta);
			FocoAlcanzado(intensity, next_state);
		break;
		//@Daredliuth: Movimiento de ZigZag para regresar al punto con menor distancia.
		case 3:
			/*
			*movements=generate_output(RIGHT,Mag_advance,angGiroNav);
			*movements=generate_output(FORWARD,Mag_advance,max_twist);
			*movements=generate_output(LEFT,Mag_advance,angGiroNav);
			*movements=generate_output(FORWARD,Mag_advance * 1.5,max_twist);
			*/
			RealizarMovimiento(mov, 0, movements, Mag_advance * factorCorrecion, max_twist, angGiroNav);
			//printf("Movimiento post realizar: %d\n", *mov);
			if(*mov == 6){
				printf("Terminamos los movimientos.\n");
				if(!ObstaculoFrente(rango_frente, size, observations, laser_max_d)){
					*movements=generate_output(LEFT,Mag_advance,angNoObs);
					printf("Reencontrando borde del obstáculo.");
				}
				*mov = 1;
			}
			//Si estamos ejecutando el último movimiento de la cricunnavegación.
			if(*mov == 5){
				*mov = 6;
			}
			//*choque ? printf("Hay choque.\n") : printf("No hay choque.\n");
			if(DentroRango(rx, ry, *xMin, *yMin) && *circunnav){
				*next_state = 0;
				*circunnav = false;
				*mov = 1;
			}
			Atorado(*mov, xAnterior, yAnterior, rx, ry, movements, Mag_advance, max_twist, atoradoCuenta);
			FocoAlcanzado(intensity, next_state);
		break;
		//@Daredliuth: Llegamos al destino.
		case 4:
			*movements=generate_output(STOP,Mag_advance,max_twist);
		break;

		//@Daredliuth: Cómo me encanta buguear programas.
		default:
			printf("En que caso estoy?\n");
		break;
	}
}

void Bug2(float lx, float ly, float rx, float ry, float rang, movement *movements,int *next_state, float Mag_advance, float max_twist, float *light_values, float *observations, float intensity, int size, float p0x, float p0y, float m, float *qMin, float *xMin, float *yMin, float *xChoque, float *yChoque, bool *choque, bool *circunnav, int *mov, float xAnterior, float yAnterior, int *atoradoCuenta){
	float qx, qy, q;
	float angulo;
	int state = *next_state;
	int cuadrante = 0;
	int cuadrante_ant = 0;
	int obs_der = 0;
	int obs_izq = 0;
	int obs_frente = 0;
	int rango_frente = 3;
	float laser_max_d = 0.06;
	float ang_rango = 0.02;
	float angGiroNav = 1.66;
	float angNoObs = 0.52;
	//Aumenta o disminuye los valores de avance para la circunnavegación.
	float factorCorrecion = 0.5;
	
	qx = lx - rx;
	qy = ly - ry;
	q = sqrt(pow(qx,2) + pow(qy,2));
	if (q < *qMin){
		*qMin = q;
		*xMin = rx;
		*yMin = ry;
	}

	angulo = DeterminarAngulo(qx,qy,q);
	cuadrante = DeterminarCuadrante(angulo);
	//printf("qx: %f\nqy: %f\nq: %f\nrang: %f\nangulo: %f\n",qx,qy,q,rang,angulo);
	printf("qx: %f\nqxAnt: %f\nqy: %f\nqyAnt: %f\n", rx, xAnterior, ry, yAnterior);
	printf("xMin: %f\nyMin: %f\nqMin: %f\n", *xMin, *yMin, *qMin);
	//printf("Intensidad: %f\n",intensity);
	printf("Estado: %d\n",state);
	//printf("No estoy roto***********************\n");
	
	switch(state){
		//@Daredliuth: Giramos hacia la luz.
		case 0:
			angulo = DeterminarAngulo(qx,qy,q);
			cuadrante = DeterminarCuadrante(angulo);
			*movements = generate_output(LEFT, Mag_advance, (angulo - rang));
			if(abs((angulo - rang) < ang_rango)){
				*next_state = 1;
				p0x = rx;
				p0y = ry;
				cuadrante_ant = cuadrante;
			}
			FocoAlcanzado(intensity, next_state);
		break;
		//@Daredliuth: Avanzamos hasta encontrar un osbtáculo.
		case 1:
			FocoAlcanzado(intensity, next_state);
			*movements = generate_output(FORWARD, Mag_advance, max_twist);
			if(ObstaculoFrente(rango_frente, size, observations, laser_max_d)){
				*xChoque = rx;
				*yChoque = ry;
				*choque = true;
				*next_state = 2;
				*mov = 1;
				*movements = generate_output(BACKWARD, Mag_advance/2, max_twist);
				//*movements=generate_output(LEFT,Mag_advance,max_twist);
			}
			Atorado(*mov, xAnterior, yAnterior, rx, ry, movements, Mag_advance, max_twist, atoradoCuenta);
			FocoAlcanzado(intensity, next_state);
		break;
		//@Daredliuth: Movimiento de ZigZag para circunnavegar.
		case 2:
			RealizarMovimiento(mov, 1, movements, Mag_advance * factorCorrecion, max_twist, angGiroNav);
			//printf("Movimiento post realizar: %d\n", *mov);
			//Si no hay nada en frente gira 45 grados a la derecha.
			if(*mov == 6){
				//printf("Terminamos los movimientos.\n");
				if(!ObstaculoFrente(rango_frente, size, observations, laser_max_d)){
					*movements=generate_output(RIGHT,Mag_advance,angNoObs);
					//printf("Reencontrando borde del obstáculo.");
				}
				*mov = 1;
			}
			//Si estamos ejecutando el último movimiento de la cricunnavegación.
			if(*mov == 5){
				*mov = 6;
			}
			*choque ? printf("Hay choque.\n") : printf("No hay choque.\n");
			//@Daredliuth: Aquí colocamos la función que evalúa la pendiente.
			if(MismaPendiente(rx, ry, *xChoque, *yChoque, lx, ly) && !*choque){
				printf("Llegamos a la recta.\n");
				*next_state = 0;
				*mov = 1;
				//*movements=generate_output(RIGHT,Mag_advance,angGiroNav);
				//Para concordar con el estado 3 de Bug1:
				*circunnav = false;
			}
			Atorado(*mov, xAnterior, yAnterior, rx, ry, movements, Mag_advance, max_twist, atoradoCuenta);
			FocoAlcanzado(intensity, next_state);
		break;
		//@Daredliuth: Lo dejamos para no afectar el funcionamiento de la función que detecta si llegamos al foco.
		case 3:
			printf("Si es Bug2 no deberíamos estar aquí.\n");
		break;
		//@Daredliuth: Llegamos al destino.
		case 4:
			*movements=generate_output(STOP,Mag_advance,max_twist);
		break;

		//@Daredliuth: Cómo me encanta buguear programas.
		default:
			printf("En que caso estoy?\n");
		break;
	}
}
