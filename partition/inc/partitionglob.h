/********************************************************************
 *
 * File         : partitionglob.h
 * Author       : Group 1
 * Date created : September 16, 2018
 * Description  : This file contains all the global variables used 
 *                by partition functions
 *
 *******************************************************************/

#ifndef GRAPHICAL
extern struct hd_geometry geometry;
#endif
#define SIZE_OF_MBR 512
#define SECTOR_SIZE 512
#define BLK_SIZE 4096
#define MAGIC_VAL1 0x55
#define MAGIC_VAL2 0xAA
#define MAXNUM_OF_PARTITIONS 4
