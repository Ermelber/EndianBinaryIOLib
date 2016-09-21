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

#include "EndianBinaryIO.h"
#include <stdio.h>

bool EndianTools::isSystemLittleEndian()
{
    uint16_t test = 1;
    return ((uint8_t*)&test)[0]==1;
}

void EndianBinaryIO::Seek(uint32_t position,int origin)
{
    fseek(base_stream,position,origin);
}


/**
 * Endian Binary Constructor
 * @param base_stream => file pointer
 */
EndianBinaryIO::EndianBinaryIO(FILE* base_stream){
    this->endianness = _LITTLE_ENDIAN;
    this->base_stream = base_stream;
    this->system_endianness = (EndianTools::isSystemLittleEndian() ? _LITTLE_ENDIAN : _BIG_ENDIAN);
}

/**
 * Endian Binary Constructor
 * @param base_stream => A pointer to the file.
 * @param endianness => Defines the endianness.
 */
EndianBinaryIO::EndianBinaryIO(FILE* base_stream, char endianness){
    this->endianness = endianness;
    this->base_stream = base_stream;
    this->system_endianness = (EndianTools::isSystemLittleEndian() ? _LITTLE_ENDIAN : _BIG_ENDIAN);
}

EndianBinaryReader::EndianBinaryReader(FILE* base_stream):EndianBinaryIO(base_stream){}
EndianBinaryReader::EndianBinaryReader(FILE* base_stream,char endianness):EndianBinaryIO(base_stream,endianness){}

EndianBinaryWriter::EndianBinaryWriter(FILE* base_stream):EndianBinaryIO(base_stream){}
EndianBinaryWriter::EndianBinaryWriter(FILE* base_stream,char endianness):EndianBinaryIO(base_stream,endianness){}

uint8_t EndianBinaryReader::ReadByte()
{
    uint8_t buffer;
    fread(&buffer,sizeof(uint8_t),1,base_stream);
    return buffer;
}

int8_t EndianBinaryReader::ReadSByte()
{
    int8_t buffer;
    fread(&buffer,sizeof(int8_t),1,base_stream);
    return buffer;
}

uint16_t EndianBinaryReader::ReadUInt16()
{
    uint16_t buffer;
    fread(&buffer,sizeof(uint16_t),1,base_stream);
    if (system_endianness!=endianness) SWAP_CONSTANT_16(buffer);
    return buffer;
}

int16_t EndianBinaryReader::ReadInt16()
{
    int16_t buffer;
    fread(&buffer,sizeof(int16_t),1,base_stream);
    if (system_endianness!=endianness) SWAP_CONSTANT_16(buffer);
    return buffer;
}

uint32_t EndianBinaryReader::ReadUInt32()
{
    uint32_t buffer;
    fread(&buffer,sizeof(uint32_t),1,base_stream);
    if (system_endianness!=endianness) SWAP_CONSTANT_32(buffer);
    return buffer;
}

int32_t EndianBinaryReader::ReadInt32()
{
    int32_t buffer;
    fread(&buffer,sizeof(int32_t),1,base_stream);
    if (system_endianness!=endianness) SWAP_CONSTANT_32(buffer);
    return buffer;
}

float EndianBinaryReader::ReadSingle()
{
    float buffer;
    fread(&buffer,sizeof(float),1,base_stream);
    if (system_endianness!=endianness) SWAP_CONSTANT_32((uint32_t)buffer);
    return buffer;
}

float EndianBinaryReader::ReadFx16()
{
    return ((float)this->ReadInt16())/4096.0;
}

float EndianBinaryReader::ReadFx32()
{
    return ((float)this->ReadInt32())/4096.0;
}

string EndianBinaryReader::ReadString(uint32_t length)
{
    string test = "";
    for (int i=0;i<length;i++)
    {
        test += (char)this->ReadByte();
    }
    return test;
}

void EndianBinaryWriter::Write(uint8_t source)
{
    fwrite(&source,sizeof(uint8_t),1,base_stream);
}

void EndianBinaryWriter::Write(int8_t source)
{
    fwrite(&source,sizeof(int8_t),1,base_stream);
}

void EndianBinaryWriter::Write(int16_t source)
{
    if (system_endianness!=endianness) SWAP_CONSTANT_16(source);
    fwrite(&source,sizeof(int16_t),1,base_stream);
}

void EndianBinaryWriter::Write(uint16_t source)
{
    if (system_endianness!=endianness) SWAP_CONSTANT_16(source);
    fwrite(&source,sizeof(uint16_t),1,base_stream);
}

void EndianBinaryWriter::Write(int32_t source)
{
    if (system_endianness!=endianness) SWAP_CONSTANT_32(source);
    fwrite(&source,sizeof(int32_t),1,base_stream);
}

void EndianBinaryWriter::Write(uint32_t source)
{
    if (system_endianness!=endianness) SWAP_CONSTANT_32(source);
    fwrite(&source,sizeof(uint32_t),1,base_stream);
}

void EndianBinaryWriter::Write(string source)
{
    for (int i=0;i<source.length();i++)
        fwrite(&source[i],sizeof(char),1,base_stream);
}

void EndianBinaryWriter::Write(float source)
{
    if (system_endianness!=endianness) SWAP_CONSTANT_32((uint32_t)source);
    fwrite(&source,sizeof(float),1,base_stream);
}

void EndianBinaryWriter::WriteFx16(float source)
{
    source *= 4096;
    if (system_endianness!=endianness) SWAP_CONSTANT_16((uint16_t)source);
    fwrite(&source,sizeof(uint16_t),1,base_stream);
}

void EndianBinaryWriter::WriteFx32(float source)
{
    source *= 4096;
    if (system_endianness!=endianness) SWAP_CONSTANT_32((uint32_t)source);
    fwrite(&source,sizeof(uint32_t),1,base_stream);
}

void EndianBinaryWriter::Close()
{
    fclose(base_stream);
}

void EndianBinaryReader::Close()
{
    fclose(base_stream);
}