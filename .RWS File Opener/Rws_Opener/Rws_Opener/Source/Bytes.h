#pragma once
#include <vector>
#include "FileOpen.h"

//Custom data types







template <typename T>
class C_Byte {

   

public:
	C_Byte() : variable(0) {

    }

	C_Byte(T Value) : variable(Value) {

    }


    C_Byte operator +(const C_Byte& Value) const {   
        return C_Byte(Value.variable + variable);  
    }

    C_Byte operator -(const C_Byte& Value) const { 
        return C_Byte(Value.variable - variable);
    }

    C_Byte operator *(const C_Byte& Value) const { 
        return C_Byte(Value.variable * variable);
    }

    C_Byte operator /(const C_Byte& Value) const { 
        return C_Byte(Value.variable / variable); 
    }

    C_Byte operator +(const T& Value) const { return C_Byte(Value + variable); }
    C_Byte operator -(const T& Value) const { return C_Byte(Value - variable); }

    C_Byte operator *(const T& Value) const { return C_Byte(Value * variable); }
    C_Byte operator /(const T& Value) const { return C_Byte(Value / variable); }

    C_Byte operator |(const T& Value) const { return C_Byte(Value | variable); }
    C_Byte operator &(const T& Value) const { return C_Byte(Value & variable); }

    C_Byte& operator += (const T& Value) { variable += Value; return *this; }
    C_Byte& operator -= (const T& Value) { variable -= Value; return *this; }

    C_Byte& operator /= (const T& Value) { variable /= Value; return *this; }
    C_Byte& operator *= (const T& Value) { variable *= Value; return *this; }

    C_Byte& operator |= (const T& Value) { variable |= Value; return *this; }
    C_Byte& operator &= (const T& Value) { variable &= Value; return *this; }

    C_Byte Reverse_Byte_Order() {
        if (typeid(variable) == typeid(int short)) {

            unsigned int short temp = static_cast<unsigned int short>(variable);

            temp = (temp >> 8 | temp << 8);

            variable = static_cast<int short>(temp);

            return *this;
        }

        else if (typeid(variable) == typeid(int)) {

            unsigned int temp = static_cast<unsigned int>(variable);

            temp = ((temp >> 24) & 0x000000FF) | ((temp >> 8) & 0x0000FF00) | ((temp << 8) & 0x00FF0000) | ((temp << 24) & 0xFF000000);
           
            variable = static_cast<int>(temp);

            return *this;
        }

        else if (typeid(variable) == typeid(long long)) {

            unsigned __int64 temp = static_cast<unsigned __int64>(variable);

            temp = ((temp >> 56) & 0x00000000000000FF) | ((temp >> 40) & 0x000000000000FF00) | ((temp >> 24) & 0x0000000000FF0000) | ((temp >> 8) & 0x00000000FF000000) |
                ((temp << 8) & 0x000000FF00000000) | ((temp << 24) & 0x0000FF0000000000) | ((temp << 40) & 0x00FF000000000000) | ((temp << 56) & 0xFF00000000000000);

            variable = static_cast<__int64>(temp);

            return *this;
        }

        else if (typeid(variable) == typeid(unsigned int short)) {

            variable = (variable >> 8 | variable << 8);
            return *this;
        }

        else if (typeid(variable) == typeid(unsigned int)) {
            variable = ((variable >> 24) & 0x000000FF) | ((variable >> 8) & 0x0000FF00) | ((variable << 8) & 0x00FF0000) | ((variable << 24) & 0xFF000000);
            return *this;
        }

        else if (typeid(variable) == typeid(unsigned long long)) {

            variable = ((variable >> 56) & 0x00000000000000FF) | ((variable >> 40) & 0x000000000000FF00) | ((variable >> 24) & 0x0000000000FF0000) | ((variable >> 8) & 0x00000000FF000000) |
                ((variable << 8) & 0x000000FF00000000) | ((variable << 24) & 0x0000FF0000000000) | ((variable << 40) & 0x00FF000000000000) | ((variable << 56) & 0xFF00000000000000);
            return *this;
        }

        else {
            
            return *this;
        }

        
    }

    

	T variable;
};



typedef C_Byte<unsigned char> UByte_C; 
typedef C_Byte<signed char> Byte_C;

typedef C_Byte<unsigned char> Uint8_C;
typedef C_Byte<signed char> int8_C;

typedef C_Byte<unsigned int short> Uint16_C;
typedef C_Byte<signed int short> int16_C;


typedef C_Byte<unsigned int> Uint32_C;
typedef C_Byte<signed int> int32_C;

typedef C_Byte<unsigned long long> Uint64_C;
typedef C_Byte<signed long long> int64_C;



class Char_Byte {
    public:
        Char_Byte(std::vector<unsigned char> &_Bytes) : Char_Bytes(_Bytes)
        {
            amountOfBytes = _Bytes.size();
        }
            
        Char_Byte(int _amountOfBytes) : Char_Bytes(){
           Char_Bytes.resize(0, _amountOfBytes);
                
           for (int i = 0; i < amountOfBytes; i++) {
               Char_Bytes[i] = 0;
           }

           amountOfBytes = _amountOfBytes;
        }

       

        Char_Byte(std::vector<char>::iterator start, std::vector<char>::iterator end) {
            Char_Bytes.insert(Char_Bytes.begin(), start, end);

            amountOfBytes = Char_Bytes.size();
        }

        Char_Byte(std::vector<unsigned char>::iterator start, std::vector<unsigned char>::iterator end) {
            Char_Bytes.insert(Char_Bytes.begin(), start, end);

            amountOfBytes = Char_Bytes.size();
        }

        Char_Byte(std::vector<unsigned char>::iterator start, int& Offset, int size) {
            Char_Bytes.insert(Char_Bytes.begin(), start + Offset, start + Offset + size);

            Offset += size;

            amountOfBytes = Char_Bytes.size();
        }

        void assign(char Byte) {
            Char_Bytes.push_back(Byte);
            amountOfBytes = Char_Bytes.size();
        }

        void clear_And_Assign(std::vector<char>::iterator begin, std::vector<char>::iterator end) {

            Char_Bytes.clear();

            Char_Bytes.insert(Char_Bytes.begin(), begin, end);

            amountOfBytes = Char_Bytes.size();
        }

        void assign(int position, std::vector<char>::iterator begin, std::vector<char>::iterator end) {

            

            Char_Bytes.insert(Char_Bytes.begin() + position, begin, end);

            amountOfBytes = Char_Bytes.size();
        }

            

        void ReOrderBytes() {
            std::vector<unsigned char> TempBytes;

            for (int i = amountOfBytes; i > 0; i--) {
                TempBytes.push_back(Char_Bytes[i]);
            }

            Char_Bytes = TempBytes;
        }

        void EndianCheck() {

            char FirstByte = Char_Bytes[0];
            char LastByte = Char_Bytes[amountOfBytes - 1];


            if (amountOfBytes < 2) {
                return;
            }

            if (FirstByte > LastByte) {
                IsBigEndian = false;
            }

            else {
                IsBigEndian = true;
            }
                
        }

        Vector3 CastToVector3_BE() {

            if (Char_Bytes.size() == 12) {
                int Offset = 0;
                Vector3 Output = Vector3();

                Output.X = Char_Byte(Char_Bytes.begin(), Offset, 4).CastToint32_BE().variable;
                Output.Y = Char_Byte(Char_Bytes.begin(), Offset, 4).CastToint32_BE().variable;
                Output.Z = Char_Byte(Char_Bytes.begin(), Offset, 4).CastToint32_BE().variable;

                return Output;
            }

            return Vector3();
        }


        Uint16_C CastToUint16_BE() {
            if (Char_Bytes.size() == 2) {
                Uint16_C Byte = 0;

                Byte |= Char_Bytes[0] << 8; // big endian
                Byte |= Char_Bytes[1];

                    

                return Byte;
            }

            return Uint16_C(0);
                
        }

        int16_C CastToint16_BE() {
            if (Char_Bytes.size() == 2) {
                int16_C Byte = 0;

                Byte |= Char_Bytes[0] << 8; // big endian
                Byte |= Char_Bytes[1];



                return Byte;
            }

            return int16_C(0);

        }


        Uint16_C CastToUint24_BE() {
            if (Char_Bytes.size() == 3) {
                Uint16_C Byte = 0;

                Byte |= Char_Bytes[0] << 16;
                Byte |= Char_Bytes[1] << 8; // big endian
                Byte |= Char_Bytes[2];



                return Byte;
            }

            return Uint16_C(0);

        }

        int16_C CastToint24_BE() {
            if (Char_Bytes.size() == 3) {
                int16_C Byte = 0;

                Byte |= Char_Bytes[0] << 16;
                Byte |= Char_Bytes[1] << 8; // big endian
                Byte |= Char_Bytes[2];



                return Byte;
            }

            return int16_C(0);

        }


        Uint32_C CastToUint32_BE() {
            if (Char_Bytes.size() == 4) {
                Uint32_C Byte = 0;

                Byte |= Char_Bytes[0] << 24; // big endian
                Byte |= Char_Bytes[1] << 16;
                Byte |= Char_Bytes[2] << 8;
                Byte |= Char_Bytes[3];



                return Byte;
            }

            return Uint32_C(0);

        }

        int32_C CastToint32_BE() {
            if (Char_Bytes.size() == 4) {
                int32_C Byte = 0;

                Byte |= Char_Bytes[0] << 24; // big endian
                Byte |= Char_Bytes[1] << 16;
                Byte |= Char_Bytes[2] << 8;
                Byte |= Char_Bytes[3];



                return Byte;
            }

            return int32_C(0);

        }


        Uint16_C CastToUint16_LE() {
            if (Char_Bytes.size() == 2) {
                Uint16_C Byte = 0;

                Byte |= Char_Bytes[1] << 8; // big endian
                Byte |= Char_Bytes[0];



                return Byte;
            }

            return Uint16_C(0);

        }

        int16_C CastToint16_LE() {
            if (Char_Bytes.size() == 2) {
                int16_C Byte = 0;

                Byte |= Char_Bytes[1] << 8; // big endian
                Byte |= Char_Bytes[0];



                return Byte;
            }

            return int16_C(0);

        }


        Uint16_C CastToUint24_LE() {
            if (Char_Bytes.size() == 3) {
                Uint16_C Byte = 0;

                Byte |= Char_Bytes[2] << 16;
                Byte |= Char_Bytes[1] << 8; // big endian
                Byte |= Char_Bytes[0];



                return Byte;
            }

            return Uint16_C(0);

        }

        int16_C CastToint24_LE() {
            if (Char_Bytes.size() == 3) {
                int16_C Byte = 0;

                Byte |= Char_Bytes[2] << 16;
                Byte |= Char_Bytes[1] << 8; // big endian
                Byte |= Char_Bytes[0];



                return Byte;
            }

            return int16_C(0);

        }


        Uint32_C CastToUint32_LE() {
            if (Char_Bytes.size() == 4) {
                Uint32_C Byte = 0;

                Byte |= Char_Bytes[3] << 24; // big endian
                Byte |= Char_Bytes[2] << 16;
                Byte |= Char_Bytes[1] << 8;
                Byte |= Char_Bytes[0];



                return Byte;
            }

            return Uint32_C(0);

        }

        int32_C CastToint32_LE() {
            if (Char_Bytes.size() == 4) {
                int32_C Byte = 0;

                Byte |= Char_Bytes[3] << 24; // big endian
                Byte |= Char_Bytes[2] << 16;
                Byte |= Char_Bytes[1] << 8;
                Byte |= Char_Bytes[0];



                return Byte;
            }

            return int32_C(0);

        }
    

    
    
        bool IsBigEndian = false;
        std::vector<unsigned char> Char_Bytes;
        int amountOfBytes;
};



    