/*
 * Made by Ermelber
 * Essential Endian Binary Reader/Writer made for my Mario Kart Tools.
 * Give credits if used.
 */

/* 
 * File:   EndianBinaryIO.cpp
 * Author: Ermelber
 * 
 * Created on 19 september 2016, 17.15
 */
#ifndef ENDIANBINARYIO_H
#define ENDIANBINARYIO_H

#define _LITTLE_ENDIAN 0
#define _BIG_ENDIAN 1

#define POS_SET SEEK_SET
#define POS_CURRENT SEEK_CUR
#define POS_END SEEK_END

#define SWAP_CONSTANT_32(a) ((uint32_t)((((a) >> 24) & 0x00FF) | (((a) >>  8) & 0xFF00) | (((a) & 0xFF00) <<  8) | (((a) & 0x00FF) << 24) ))
#define SWAP_CONSTANT_16(a) ((uint16_t)((((a) >>  8) & 0x00FF) | (((a) <<  8) & 0xFF00) ))


#include <iostream>
#include <string>

using namespace std;

class EndianTools {
public:
    static bool isSystemLittleEndian();
};

class EndianBinaryIO {
protected:
    FILE* base_stream;
    uint8_t endianness;
    uint8_t system_endianness;
public:
    EndianBinaryIO(FILE*);
    EndianBinaryIO(FILE*,char);
    void Seek(uint32_t,int);
    void Close();
};

class EndianBinaryReader : public EndianBinaryIO {
public:
    uint8_t ReadByte();
    int8_t ReadSByte();
    uint16_t ReadUInt16();
    int16_t ReadInt16();
    uint32_t ReadUInt32();
    int32_t ReadInt32();
    float ReadSingle();
    float ReadFx16();
    float ReadFx32();
    string ReadString(uint32_t);
    uint8_t* ReadBytes(size_t);
    //ONLY WORKS ON LITTLE ENDIAN SYSTEMS!!!!
    template <typename T> 
    T* ReadObject()
    {
        T* result = new T;
        fread(result, 1, sizeof(T), base_stream);
        return result;
    }
    
    EndianBinaryReader(FILE*);
    EndianBinaryReader(FILE*,char);
};

class EndianBinaryWriter : public EndianBinaryIO {
public:
    void Write(uint8_t);
    void Write(int8_t);
    void Write(uint16_t);
    void Write(int16_t);
    void Write(uint32_t);
    void Write(int32_t);
    void Write(float);
    void Write(string);
    void WriteFx16(float);
    void WriteFx32(float);
    //ONLY WORKS ON LITTLE ENDIAN SYSTEMS!!!!
    template <typename T> 
    void WriteObject(T* source)
    {
        fwrite(source,sizeof(T),1,base_stream);
    }
    
    EndianBinaryWriter(FILE*);
    EndianBinaryWriter(FILE*,char);
};

#endif /* ENDIANBINARYIO_H */

