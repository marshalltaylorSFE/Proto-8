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

//Define MICROLL_DEBUG to get serial debug info regarding notes in lists
#define MICROLL_DEBUG

//Includes
#include "MicroLL.h"
#include "stdint.h"
#include "Arduino.h"

//**********************************************************************//
//  MicroLL Class
//
//  Creates link list
//
//  Construct with passed max depth or use default
//
MicroLL::MicroLL( listIdemNumber_t inputNumber )
{
  startObjectPtr = &nullObject;  //start pointed to null note
  currentPosition = 0 ;  //Size 0
  maxLength = inputNumber;  //set max size
  nullObject.eventType = 0xAA;  //define null note
  nullObject.nextObject = &nullObject;  //Points to self.
  nullObject.voice = -1;

}
MicroLL::MicroLL( void )
{
  startObjectPtr = &nullObject;
  currentPosition = 0;
  maxLength = 1000;
  nullObject.eventType = 0xAA;
  nullObject.nextObject = &nullObject;  //Points to self.
  nullObject.voice = -1;

}

//Pass listObject_t to be pushed to the stack (top)
void MicroLL::pushObject( listObject_t & objectToPush )
{
  //This creates a new object, but then forgets the name
  //and doesn't delete the object.
  //
  //If the stack size is too big, new object won't be accepted
  if ( currentPosition < maxLength )
  {
    //Make a new object to the list
    listObject_t *newObject = new listObject_t;
#ifdef MICROLL_DEBUG
    Serial.print("\nMADE A NEW LIST ITEM\n");
#endif

    //Point the start to the new note if this is the first one
	if( currentPosition == 0 )
	{
	  startObjectPtr = newObject;
	}
	else
	{
	  //Otherwise set the previous note to this new address
	  listObject_t * previousObjectPtr = readObject( currentPosition - 1 );
	  previousObjectPtr->nextObject = newObject;
	}

    //grow list size
    currentPosition++;
	
	//****CUSTOM OBJECT TYPE CODE****//
    //Set the new note's params
    newObject->eventType = objectToPush.eventType;
    newObject->value = objectToPush.value;
	newObject->data = objectToPush.data;
	newObject->channel = objectToPush.channel;
	newObject->timeStamp = objectToPush.timeStamp;
	newObject->voice = objectToPush.voice;
    newObject->nextObject = &nullObject;
    
  }

}

//Pass position, returns void
void MicroLL::dropObject( listIdemNumber_t positionToDrop )
{
  //pointer for object to drop
  listObject_t * objectToDrop;
  listObject_t * tempObjectPtr;

  if ( positionToDrop >= currentPosition )
  {
    //Too deep!  Do nothing.
  }
  else
  {
    //Ok, good to do it.
	//Go to the object before positionToDrop
    if ( positionToDrop == 0 )
    {
		//Save the start object
		objectToDrop = startObjectPtr;
  	
		//Move startObjectPtr
		startObjectPtr = startObjectPtr->nextObject;
		
		//if( startObjectPtr->nextObject == &nullObject )
		//{
		//	//If the start object is the null object, we are empty
		//	startObjectPtr = &nullObject;
		//}
    }
    else
	{
		//go to the position before the one to drop
		tempObjectPtr = startObjectPtr;
		for (uint8_t i = 0; i < (positionToDrop - 1); i++ )
		{
			tempObjectPtr = tempObjectPtr->nextObject;
		}
		//Point out the drop target
		objectToDrop = tempObjectPtr->nextObject;
		//move the older object to skip
		tempObjectPtr->nextObject = objectToDrop->nextObject;
	}
    //Drop it like it's not
    delete objectToDrop;
#ifdef MICROLL_DEBUG
    Serial.println("\nDROPPED AN ITEM\n");
#endif
    currentPosition--;
  }

}

//Pass listObject_t and position
void MicroLL::insertObject( listObject_t & objectToInsert, listIdemNumber_t positionToBe )
{
	//pointer for object to drop
	listObject_t * tempObjectPtr;
	
	if(( currentPosition < maxLength ) && ( positionToBe <= currentPosition ))
	{
		//If position is 0, do it a different way
		if( positionToBe == 0 )
		{
			//pushObject( objectToInsert );
			//Make a new object
			listObject_t *newObject = new listObject_t;
#ifdef MICROLL_DEBUG
			Serial.print("\nINSERTING AN OBJECT AT 0, MADE A NEW LIST ITEM\n");
#endif
			
			
			//Point the new object at the previous target
			newObject->nextObject = startObjectPtr;
			
			//Point the one above to the new one
			startObjectPtr = newObject;
			
			//Apply the values
			newObject->eventType = objectToInsert.eventType;
			newObject->value = objectToInsert.value;
			newObject->data = objectToInsert.data;
			newObject->channel = objectToInsert.channel;
			newObject->timeStamp = objectToInsert.timeStamp;
			
			//grow list size
			currentPosition++;
		}
		else
		{
			//Make a new object
			listObject_t *newObject = new listObject_t;
#ifdef MICROLL_DEBUG
			Serial.print("\nINSERTING AN OBJECT, MADE A NEW LIST ITEM\n");
#endif
			
			//Go to the position above, save pointer
			tempObjectPtr = startObjectPtr;
			for (uint8_t i = 0; i < ( (int32_t)positionToBe - 1 ); i++ )
			{
				tempObjectPtr = tempObjectPtr->nextObject;
			}
			
			//Point the new object at the previous target
			newObject->nextObject = tempObjectPtr->nextObject;
			
			//Point the one above to the new one
			tempObjectPtr->nextObject = newObject;
			
			//Apply the values
			newObject->eventType = objectToInsert.eventType;
			newObject->value = objectToInsert.value;
			newObject->data = objectToInsert.data;
			newObject->channel = objectToInsert.channel;
			newObject->timeStamp = objectToInsert.timeStamp;
			
			//grow list size
			currentPosition++;
		}
	}
}

//Pass listObject_t, sorts by time, after tied
void MicroLL::insertObjectByTime( listObject_t & objectToInsert )
{
	//Find where to put the new object
	listIdemNumber_t positionToBe;
	if( currentPosition == 0 )
	{
		//List empty, target 0
		positionToBe = 0;
	}
	else
	{
		positionToBe = seekNextAfter( objectToInsert.timeStamp );
	}
	if( positionToBe == maxLength )
	{
		//We have no notes after the requested
		positionToBe = currentPosition;
	}

#ifdef MICROLL_DEBUG
	Serial.print("\nINSERTING AT POSITION: \n");
	Serial.println(positionToBe);
#endif


	//Put it in there
	insertObject( objectToInsert, positionToBe );
	
	printfMicroLL();
}

// //returns listObject_t
// listObject_t MicroLL::popObject( void )
// {
  // //Target note variable
  // listObject_t * objectToDestroy;

  // if (currentPosition > 0) //If there are any objects in the list, go on
  // {
    // objectToDestroy = nextObject;
    // //move top pointer
    // nextObject = objectToDestroy->nextObject;
    // //destruct nextObject by topStack
    // delete objectToDestroy;
    // Serial.println("\nDESTROYED A NOTE\n");
    // currentPosition--;

    // //If depth now == 0, point top to null
    // if (currentPosition == 0)
    // {
      // nextObject = &nullObject;
    // }
  // }

  // return *nextObject;
// }

// //returns listObject_t
// listObject_t MicroLL::readObject( void )
// {
  // listObject_t * objectToReturn;
  // objectToReturn = nextObject;
  // return *objectToReturn;
// }

//Clear out the list, point afresh
void MicroLL::clear( void )
{
	//Drop it like it's NOT
	while( currentPosition > 0 )
	{
		dropObject( 0 );
	}
	
	//Account for all initial conditions
	
	//This is controlled by the drop and clear functions:
	//	startObjectPtr = &nullObject;
	//	currentPosition = 0;

	//Don't change this:
	//	maxLength = 1000;
	//	nullObject.eventType = 0xAA;
	//	nullObject.nextObject = nullObject;  //Points to self.
	
}


//returns listObject_t
listObject_t * MicroLL::readObject( listIdemNumber_t inputNumber ) //position 0 = top
{
  listObject_t * objectToReturn;

  if (inputNumber < maxLength) //Prevent out of range peeks
  {
    objectToReturn = startObjectPtr;
    //Iterate to the depth
    for ( uint8_t i = 0; i < inputNumber; i++ )
    {
      objectToReturn = objectToReturn->nextObject;
    }
  }
  else
  {
    objectToReturn = &nullObject;
  }
  return objectToReturn;
}

listIdemNumber_t MicroLL::seekNextAfter( uint32_t targetTicks )
{
	listObject_t * tempObject = startObjectPtr;
	listIdemNumber_t returnVar;
	int i = 0;
	while( (tempObject->timeStamp < targetTicks)&&(tempObject != &nullObject) )
	{
		tempObject = tempObject->nextObject;
		i++;
	}
	//If we found the end, return the nullObject
	if( tempObject == &nullObject )
	{
		returnVar = maxLength;
	}
	else
	{
		returnVar = i;
	}
	return returnVar;
}

int8_t MicroLL::seekObjectbyTimeStamp( listObject_t & ) //pass listObject_t, returns position
{
	return 0;
}

int8_t MicroLL::seekObjectbyNoteValue( listObject_t & noteToSeek ) //pass listObject_t, returns position
{
  //Create temporary note to use for comparison
  listObject_t * tempObject;
  tempObject = startObjectPtr;
  int8_t returnVar = -1;

  for (uint8_t i = 0; i < currentPosition; i++)
  {
    //****CUSTOM OBJECT TYPE CODE****//
    //For now, only use the value
    if ( tempObject->value == noteToSeek.value )
    {
      returnVar = i;
    }
    //Walk down the list
    tempObject = tempObject->nextObject;
  }
  return returnVar;
}

//returns depth of stack.
listIdemNumber_t MicroLL::listLength( void )
{
  return currentPosition;
}

//printfs the stack
void MicroLL::printfMicroLL( void )
{

  listObject_t * tempObject;
  long output;
  tempObject = startObjectPtr;
  Serial.println("\n Pos, timeStamp, type, channel, value, data, address, nextObjectAddress, voice");
  Serial.println(  "-------------------------");
  //Iterate to the depth
  for ( uint8_t i = 0; i < currentPosition; i++ )
  {
    Serial.print(" ");
    Serial.print(i);
    Serial.print(", ");
    Serial.print(tempObject->timeStamp);
    Serial.print(", 0x");
    Serial.print(tempObject->eventType, HEX);
    Serial.print(", ");
    Serial.print(tempObject->channel);
    Serial.print(", ");
    Serial.print(tempObject->value);
    Serial.print(", ");
    Serial.print(tempObject->data);
    Serial.print(", ");
    output = (long)tempObject;
    Serial.print(output, HEX);
    Serial.print(", ");
    output = (long)tempObject->nextObject;
    Serial.print(output, HEX);
    Serial.print(", ");
    Serial.println(tempObject->voice);	
    //move note
    tempObject = tempObject->nextObject;
  }
  Serial.print("\ncurrentPosition:");
  Serial.println(currentPosition);

}
