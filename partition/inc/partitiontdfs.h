/********************************************************************
 *
 * File         : partitiontdfs.h
 * Author       : Team 1
 * Date         : September 16, 2018
 * Description  : This file contains type definitions        
 *                related to partition module
 *
 *******************************************************************/

struct mbr_partition_table_entry
{
    UINT1 status;
    UINT1 start_chs[3];
    UINT1 partition_type;
    UINT1 end_chs[3];
    UINT4 first_sector_lba;
    UINT4 sector_count;
}__attribute__((packed));

struct disk_mbr
{
    UINT1 code[440];
    UINT4 disk_signature;
    UINT2 reserved;
    struct mbr_partition_table_entry pt[4];
    UINT1 signature[2];
}__attribute__((packed));

