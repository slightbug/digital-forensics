/********************************************************************
 *
 * File         : partitionproto.h
 * Author       : Team 1
 * Date created : September 16, 2018
 * Description  : This file contains all function prototypes 
 *
 *******************************************************************/

/*****************************************************************************/
/*                          partitionutils.c                                  */
/*****************************************************************************/
VOID printPartitionMetadata(struct disk_mbr* mbr);
UINT1 get_head(UINT1 chs[3]);
UINT1 get_sector(UINT1 chs[3]);
UINT2 get_cylinder(UINT1 chs[3]);
UINT4 calculate_LBA(UINT1 chs[3], UINT4 num_heads, UINT4 num_sectors);
INT4 get_partition_count(struct disk_mbr* mbr);
UINT4 get_partition_start_addr(UINT4 lba);
UINT8 get_partition_size(UINT4 num_sectors);
INT4 verify_magic_values(UINT1 magic_value[2]);
struct disk_mbr* getMBR(INT4 fd);
