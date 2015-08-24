////////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2001 Custom Computer Services            ////
//// This source code may only be used by licensed users of the CCS C   ////
//// compiler.  This source code may only be distributed to other       ////
//// licensed users of the CCS C compiler.  No other use, reproduction  ////
//// or distribution is permitted without written permission.           ////
//// Derivative programs created using this software in object code     ////
//// form are not restricted in any way.                                ////
////////////////////////////////////////////////////////////////////////////
////
//// History:
////		* 9/20/2001	: Improvments are made to sin/cos code. The code
////						  now is smaller, much faster and more accurate.
////
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_H
#define MATH_H


#undef PI
#define PI	3.141592654



float CEIL_FLOOR(float x, int n)
{
   float y, res;
   long l;
   int s;

   s = 0;
   y = x;

   if (x < 0)
   {
      s = 1;
      y = -y;
   }

   if (y <= 32768.0)
  res = (float)(long)y;

 else if (y < 10000000.0)
   {
  l = (long)(y/32768.0);
      y = 32768.0*(y/32768.0 - (float)l);
  res = 32768.0*(float)l;
  res += (float)(long)y;
 }

 else
  res = y;

 y = y - (float)(long)y;

 if (s)
  res = -res;

 if (y != 0)
 {
  if (s == 1 && n == 0)
   res -= 1.0;

  if (s == 0 && n == 1)
   res += 1.0;
 }
 if (x == 0)
    res = 0;

 return (res);
}

////////////////////////////////////////////////////////////////////////////
//	float floor(float x)
////////////////////////////////////////////////////////////////////////////
// Description : rounds down the number x.
// Date : N/A
//
float floor(float x)
{
   float r;
   r = CEIL_FLOOR(x, 0);
}

////////////////////////////////////////////////////////////////////////////
//	float sqrt(float x)
////////////////////////////////////////////////////////////////////////////
// Description : returns the square root of x
// Date : N/A
//
float sqrt(float x)
{
   float y, res;
   byte *p;

   #ifdef _ERRNO
   if(x < 0)
   {
      errno=EDOM;
   }
   #endif

   if( x<=0.0)
      return(0.0);

   y=x;
   p=&y;
   (*p)=(byte)((((int16)(*p)) + 127) >> 1);

   do {
      res=y;
      y+=(x/y);
      (*p)--;
   } while(res != y);

   return(res);


}

////////////////////////////// Trig Functions //////////////////////////////
#undef PI_DIV_BY_TWO
//#define PI_DIV_BY_TWO	1.570796326794896
#define PI_DIV_BY_TWO	1.5707963
#undef TWOBYPI
#define TWOBYPI 			0.6366197724
////////////////////////////////////////////////////////////////////////////
//	float cos(float x)
////////////////////////////////////////////////////////////////////////////
// Description : returns the cosine value of the angle x, which is in radian
// Date : 9/20/2001
//
float cos(float x)
{
	float y, t, t2 = 1.0;
	int quad, i;
	float frac;
	float p[4] = {
		-0.499999993585,
		 0.041666636258,
		-0.0013888361399,
		 0.00002476016134
	};

	if (x < 0) x = -x; 				// absolute value of input

	quad = (int)(x / PI_DIV_BY_TWO);		// quadrant
	frac = (x / PI_DIV_BY_TWO) - quad;  // fractional part of input
	quad = quad % 4;							// quadrant (0 to 3)

	if (quad == 0 || quad == 2)
		t = frac * PI_DIV_BY_TWO;
	else if (quad == 1)
		t = (1-frac) * PI_DIV_BY_TWO;
	else // should be 3
		t = (frac-1) * PI_DIV_BY_TWO;

	y = 0.999999999781;
	t = t * t;
	for (i = 0; i <= 3; i++)
	{
		t2 = t2 * t;
		y = y + p[i] * t2;
	}

	if (quad == 2 || quad == 1)
		y = -y;  // correct sign

	return (y);
}

////////////////////////////////////////////////////////////////////////////
//	float sin(float x)
////////////////////////////////////////////////////////////////////////////
// Description : returns the sine value of the angle x, which is in radian
// Date : 9/20/2001
//
float sin(float x)
{
	return cos(x - PI_DIV_BY_TWO);
}

float const pas[3] = {0.49559947, -4.6145309, 5.6036290};
float const qas[3] = {1.0000000,  -5.5484666, 5.6036290};

float ASIN_COS(float x, int n)
{
   float y, res, r, y2;
   int s;
   #ifdef _ERRNO
   if(x <-1 || x > 1)
   {
      errno=EDOM;
   }
   #endif
   s = 0;
   y = x;
 
   if (x < 0)
   {
      s = 1;
      y = -y;
   }

   if (y > 0.5)
   {
      y = sqrt((1.0 - y)/2.0);
      n += 2;
   }

   y2=y*y;

   res = pas[0]*y2 + pas[1];
   res = res*y2 + pas[2];

   r = qas[0]*y2 + qas[1];
   r = r*y2 + qas[2];

   res = y*res/r;

   if (n & 2)     // |x| > 0.5
      res = PI_DIV_BY_TWO - 2.0*res;
   if (s)
      res = -res;
   if (n & 1)           // take arccos
      res = PI_DIV_BY_TWO - res;

   return(res);
}


////////////////////////////////////////////////////////////////////////////
//	float asin(float x)
////////////////////////////////////////////////////////////////////////////
// Description : returns the arcsine value of the value x.
// Date : N/A
//
float asin(float x)
{
   float r;

   r = ASIN_COS(x, 0);
   return(r);
}
////////////////////////////////////////////////////////////////////////////
//	float acos(float x)
////////////////////////////////////////////////////////////////////////////
// Description : returns the arccosine value of the value x.
// Date : N/A
//
float acos(float x)
{
   float r;

   r = ASIN_COS(x, 1);
   return(r);
}
#endif
