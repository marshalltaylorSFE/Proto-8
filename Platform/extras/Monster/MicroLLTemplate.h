//**********************************************************************//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
//
//  Written by:  Marshall Taylor
//  Created:  March 21, 2015
//
//**********************************************************************//
#ifndef MICROLLTEMPLATE_H_INCLUDED
#define MICROLLTEMPLATE_H_INCLUDED

#include "stdint.h"

//Depth into the stack variable
typedef uint16_t listIdemNumber_t;

//basic wrapper
struct genericLinkedObject
{

  //A pointer to the newer object
  MidiEvent * nextObject;

};

//Point ListObject_t to custom object type

#define NULLNOTE -1

template <class listObject_t>
class GenericLinkedList
{
    listIdemNumber_t maxLength;
    listIdemNumber_t currentPosition;

  public:
    //A pointer to the next object, list items enumerate from this
    listObject_t * startObjectPtr;
	
	//A empty note to point to when the list is empty
    listObject_t nullObject;

  public:
    GenericLinkedList( listIdemNumber_t ); //Construct with passed max depth
    GenericLinkedList( void );

    //Item manipulation
    void pushObject( listObject_t & ); //Pass listObject_t
    void dropObject( listIdemNumber_t ); //Pass position, returns listObject_t
	void insertObject( listObject_t &, listIdemNumber_t ); //Pass listObject_t and position
	//void insertObjectByTime( listObject_t & ); //Pass listObject_t
    //listObject_t popObject( void ); //returns listObject_t
	void clear( void );

	//List query tools
    listObject_t readObject( void );
    listObject_t * readObject( listIdemNumber_t );
	//listIdemNumber_t seekNextAfter( uint32_t );//Search by tick value
	//int8_t seekObjectbyTimeStamp( listObject_t & ); //pass listObject_t, returns position
	//int8_t seekObjectbyNoteValue( listObject_t & ); //pass listObject_t, returns position
    listIdemNumber_t listLength( void ); //returns depth of stack.
	
	//Debug
	void printDebug( void );
	


};

#endif // FILE_H_INCLUDED

