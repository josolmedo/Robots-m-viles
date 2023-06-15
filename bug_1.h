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
#include <math.h>


// State Machine 
void bug_1(
float intensity,
float *light_values, 
float *observations, 
int size, 
float laser_value, 
int  dest, 
int obs , 
movement *movements  ,
int *next_state ,
float Mag_Advance ,
float max_twist, 
float robot_x,
float robot_y,
float *qLx,
float *qLy,
float *qHx,
float *qHy,
float *distancialuz,
int *regreso)
{

 int state = *next_state;
 int i;

 printf("intensity %f\n",intensity);
 printf("quantized destination %d\n",dest);
 printf("quantized obs %d\n",obs);

 for(int i = 0; i < 8; i++)
        printf("light_values[%d] %f\n",i,light_values[i]);
 for (int i = 0; i < size ; i++ ) 
         printf("laser observations[%d] %f\n",i,observations[i]);
	
	switch(obs)
	{	
	case 0:{
	  if(*qHx==0){
	  printf("Seguir luz\n");
	  int flg_result = light_follower
	  (intensity,light_values,movements,Mag_Advance,max_twist);
                if(flg_result == 1) stop();
	  }
	  else{
	  printf("rodeo de ostaculo\n");

          if(state==0){
	  *movements=generate_output(RIGHT,Mag_Advance,max_twist/10);
	  *next_state=2;
          }
	  else
	  {
	  *movements=generate_output(FORWARD,Mag_Advance/10,max_twist);
	  *next_state=0;
	  }  
        }
	}
	break;
	case 1:{
	if(*qHx==0)
	{
	*qHx=robot_x;
	*qHy=robot_y;
	printf("colicion en %f\n",*qHx);
	}else
	{
	    printf("qhx %f robot_x %f\n",*qHx,robot_x);
	    if((fabs(*qHx-robot_x)<0.03)&&(fabs(*qHy-robot_y)<0.03))
	    {
	    printf("regreso a qH\n");
	    *regreso=1;
	    }
	}

	if(*distancialuz<intensity){
	*qLx=robot_x;
	*qLy=robot_y;
	*distancialuz=intensity;
	printf("nuevo punto qL\n");
	}
	if(fabs(*qLx-robot_x)<0.04&&fabs(*qLy-robot_y)<0.04&&*regreso==1)
	{
	  printf("siguiente obstaculo\n");
	  *qHx=0;
 	  *qHy=0;
	  *regreso=0;
	  *movements=generate_output(LEFT,Mag_Advance,max_twist*2);
	}
	else{
	    if(observations[4]==0.05f)
	      *movements=generate_output(FORWARD,Mag_Advance,max_twist);
	    else
	      *movements=generate_output(LEFT,Mag_Advance,max_twist/10);
	}
	break;	
	}
 	case 2:{
	*movements=generate_output(LEFT,Mag_Advance,max_twist);
	break;		
	}
        case 3:{
	*movements=generate_output(LEFT,Mag_Advance,max_twist);        
	break;       
	}


	default:
	break;
	}


if(intensity > 30)
 {

	movements->twist = 0.0;
 	movements->advance = 0.0;
	printf("\n **************** Reached light source ******************************\n");
stop();
 }
}
