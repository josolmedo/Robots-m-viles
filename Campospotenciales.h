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



// State Machine 
int Campospotenciales(float intensity, float *light_values, float *observations, int size, float laser_value, int  dest, int obs , movement *movements  ,int *next_state ,float Mag_Advance ,float max_twist)
{

 int state = *next_state,result;
 int i,direccionluz,direccionobs;
 float giroA;
 float giroR,giro;
 float val;
 result=0;
if(intensity > THRESHOLD_FOLLOWER)
 {

	movements->twist = 0.0;
 	movements->advance = 0.0;
	result = 1;
	printf("\n **************** Reached light source ******************************\n");
 }else{
 printf("intensity %f\n",intensity);
 printf("quantized destination %d\n",dest);
 printf("quantized obs %d\n",obs);

 for(int i = 0; i < 8; i++){
        printf("light_values[%d] %f\n",i,light_values[i]);
	if(i==0){
	   direccionluz=0;
	   val=light_values[i];
	}
else if(light_values[i]<val){	
	//Guarda el valor menor, es el sensor más cercano a la luz
	direccionluz=i;
	val=light_values[i];
}
}
printf("Min light %d\n",direccionluz);
 for (int i = 0; i < size ; i++ ){
         printf("laser observations[%d] %f\n",i,observations[i]);
	if(i==0){
	  direccionobs=0;
	val=observations[i];
	}
else if(observations[i]<val){
	//Busca menor valor, sensor más cercano a obstáculo
	direccionobs=i;
	val=observations[i];
}
}
printf("Min obs %d\n",direccionobs);

switch(direccionluz)
{
	case 0:
	giroA=4;
	break;

	case 1:
	giroA=3;
	break;

	case 2:
	giroA=2;
	break;
	
	case 3:
	giroA=1;
	break;
	
	case 4:
	giroA=0;
	break;

	case 5:
	giroA=-1;
	break;
	
	case 6:
	giroA=-2;
	break;
		
	case 7:
	giroA=-3;
	break;
	
	default:
	break;

}
if(direccionobs>9)
giroR=(20-direccionobs+1)*(-3.141592654/20);
else
giroR=(direccionobs+1)*(3.141592654/20);//Establece giro de repulsion a obstaculo en muiltiplos de 45°

giroA=-giroA*(3.141592654/4);//Establece un giro de atracción a la luz, en términos de 45°

printf("giroA %f, giroR %f\n",giroA,giroR);
if(obs==0)//Si no hay obstaculo solo gira hacia la luz
  giro=giroA;
else//Sino hace una ponderación
  giro=(giroA)+giroR;
printf("Giro= %f",giro);
if(giro==0||giro==giroR/2)
  giro=giroR;
switch(*next_state){
case 0:
	movements->twist = giro;
 	movements->advance = 0.03;
break;

case 1:
	*movements=generate_output(FORWARD,Mag_Advance/2,max_twist);
	*next_state=0;
break;
default:
break;
}

 printf("Next State: %d\n", *next_state);
}
return result;
}
