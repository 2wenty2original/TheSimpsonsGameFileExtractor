#include "Bytes.h"



struct Display {

	Uint8_C UEight;
	int8_C Eight;
	Uint16_C USixteen;
	int16_C Sixteen;
	Uint32_C UThirtyTwo;
	int32_C ThirtyTwo;
	Uint64_C USixtyFour;
	int64_C SixtyFour;
};



class DisplayByte {
	public:


		

		DisplayByte() {}

		void CreateStruct(int position, std::vector<char>::iterator begin, std::vector<char>::iterator end) {
			Char_Byte Temp = Char_Byte(0);
			
			Temp.clear_And_Assign(begin, end - 3);

			display_bytes.Eight = Temp.Char_Bytes[0];
			display_bytes.UEight = (unsigned char)Temp.Char_Bytes[0];

			Temp.clear_And_Assign(begin, end - 2);

			display_bytes.Sixteen = Temp.CastToint16_BE();
			display_bytes.USixteen = Temp.CastToUint16_BE();

			Temp.clear_And_Assign(begin, end);

			display_bytes.ThirtyTwo = Temp.CastToint32_BE();
			display_bytes.UThirtyTwo = Temp.CastToUint32_BE();

		}
	
		Display display_bytes;
		
		
	};


	

	
