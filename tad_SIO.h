#ifndef _SIO_
#define _SIO_

void initSIO(void);

char SiCharAvail(void);
//Post: returns the number of available characters that are in the reception queue.
//Retorna -1 if there are no available characters.

char SiGetChar(void);
//Pre: SiCharAvail() returns a number greater than zero.
//Post: returns and removes the first element from the reception queue.

char SiIsAvailable(void);
//Post: returns 1 if the SIO module is available for sending.

void SiSendChar(char c);
//Pre: SiIsAvailable().
//Post: starts sending the specified character.

void startRecording (void);

void SIOmotor (void);

unsigned char actionOngoing(void);

void startReproducing(void);

void setIndexToSend (unsigned char *newIndexToSend);

#endif