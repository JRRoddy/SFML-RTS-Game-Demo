
#pragma once
#include "iostream"

// defining custom image map colour stuctr that will act as a key into the std map created from parsing the file 
// that describes the colours to expect and their tile string identifiers, this information relates to a particualr 
// image map that will be used by a particualr level area type 
 class imageMapColour {

 public:
	 float r, g, b, a;


	 

	imageMapColour(float _r, float _g, float _b, float _a) :r(_r), g(_g), b(_b), a(_a) {};
	const bool operator ==(const imageMapColour& colour)const {
		 
		bool re = colour.r == this->r;
		bool be = colour.b == this->b;
		bool ge = colour.g == this->g;
		bool ae = colour.a == this->a;
		   
		return (re + be + ge + ae);



	}
	 bool operator < (const imageMapColour &colour) const{
	
		float colourSumLh = r + g + b + a ; 
		float colourSumRh = colour.r + colour.g + colour.b + colour.a; 

		if(colourSumLh == colourSumRh && !(colour == *this) )
		{
			return true;
		}


		return colourSumLh < colourSumRh;


	
	}



	


};