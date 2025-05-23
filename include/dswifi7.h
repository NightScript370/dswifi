// SPDX-License-Identifier: MIT
//
// Copyright (C) 2005-2006 Stephen Stair - sgstair@akkit.org - http://www.akkit.org

// DSWifi Project - Arm7 Library Header file (dswifi7.h)

#ifndef DSWIFI7_H
#define DSWIFI7_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dswifi_version.h"

// Wifi Sync Handler function: Callback function that is called when the arm9 needs to be told to synchronize with new fifo data.
// If this callback is used (see Wifi_SetSyncHandler()), it should send a message via the fifo to the arm9, which will call Wifi_Sync() on arm9.
typedef void (*WifiSyncHandler)();

// Read_Flash: Reads an arbitrary amount of data from the firmware flash chip
//  int address:        Offset to start reading from in the flash chip
//  char * destination: Pointer to a memory buffer to hold incoming data
//  int length:         The number of bytes to read
extern void Read_Flash(int address, char * destination, int length);

// PowerChip_ReadWrite: Reads or writes a value to the DS's power chip
//  int cmp:	The byte-long command to send to the chip (top bit 1=read, 0=write - other bits = register ID to read/write)
//  int data:	The data to write to the chip (if sending a read command, this should be zero)
//  Returns:	The data read returned by the serial connection; only really useful when reading.
extern int PowerChip_ReadWrite(int cmd, int data);

// Wifi_Interrupt: Handler for the arm7 wifi interrupt. Should be called by the
//   interrupt handler on arm7, and should *not* have multiple interrupts enabled.
extern void Wifi_Interrupt();

// Wifi_Update: Sync function to ensure data continues to flow between the two
//   CPUs smoothly.  Should be called at a periodic interval, such as in vblank.
extern void Wifi_Update();

// Wifi_Init: Requires the data returned by the arm9 wifi init call. The arm9
//   init call's returned data must be passed to the arm7 and then given to this
//   function. (or else very bad things happen)
//   This function also enables power to the wifi system, which will shorten
//   battery life.
//  unsigned long WifiData: You must pass the 32bit value returned by the call to
//                           Wifi_Init on the ARM9.
extern void Wifi_Init(unsigned long WifiData);

// Wifi_Deinit: In the case that it is necessary, this function cuts power to
//   the wifi system.  After this the wifi will be unusable until Wifi_Init is
//   called again.
extern void Wifi_Deinit();

// Wifi_Sync: Call this function when requested to sync by the arm9 side of the 
//   wifi lib
extern void Wifi_Sync();

// Wifi_SetSyncHandler: Call this function to request notification of when the
//   ARM9-side Wifi_Sync function should be called.
//  WifiSyncHandler sh:    Pointer to the function to be called for notification.
extern void Wifi_SetSyncHandler(WifiSyncHandler sh);

extern void installWifiFIFO();

#ifdef __cplusplus
}
#endif

#endif // DSWIFI7_H
