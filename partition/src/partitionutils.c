#include "partitioninc.h"
VOID printPartitionMetadata(struct disk_mbr* mbr) 
{
	INT4 i;
   
	fprintf(stdout, "\n\n" );

	fprintf(stdout, "Number of partitions = %d\n\n", get_partition_count(mbr));
	for ( i = 0; i < MAXNUM_OF_PARTITIONS; i++ ) 
	{
		if ( mbr->pt[i].sector_count  > 0 ) 
		{
			fprintf(stdout, "Starting CHS head = 0x%.2"PRIx8"\n", get_head(mbr->pt[i].start_chs));
			fprintf(stdout, "Starting CHS sector = 0x%.2"PRIx8"\n", get_sector(mbr->pt[i].start_chs));
			fprintf(stdout, "Starting CHS Cylinder = 0x%.3"PRIx16"\n", get_cylinder(mbr->pt[i].start_chs));
         
			fprintf(stdout, "Ending CHS head = 0x%.2"PRIx8"\n", get_head(mbr->pt[i].end_chs));
			fprintf(stdout, "Ending CHS sector = 0x%.2"PRIx8"\n", get_sector(mbr->pt[i].end_chs));
			fprintf(stdout, "Ending CHS Cylinder = 0x%.3"PRIx16"\n", get_cylinder(mbr->pt[i].end_chs));
         
			fprintf(stdout, "LBA Begin/Starting Sector = 0x%.2"PRIx32"\n", mbr->pt[i].first_sector_lba);
			fprintf(stdout, "Starting address = 0x%.2"PRIx32"\n", get_partition_start_addr(mbr->pt[i].first_sector_lba));
			fprintf(stdout, "Partition Size = %llu bytes\n", get_partition_size(mbr->pt[i].sector_count));
	 
			fprintf(stdout, "** The following formula will only output correct value for a hard-drive **\n");
			fprintf(stdout, "LBA calculated from CHS to LBA translation formula = 0x%.2"PRIx32"\n", calculate_LBA(mbr->pt[i].start_chs, geometry.heads, geometry.sectors));
			fprintf(stdout, "\n\n");
      }
   }
}

/*
* Gets the MBR from the drive and returns the mbr struct
*/
struct disk_mbr* getMBR(INT4 fd)
{
        UINT1 b[BLK_SIZE];
        INT4 retVal;
        struct disk_mbr* mbr;

        retVal = read(fd, b , BLK_SIZE);
        if ( retVal <=0 )
        {
                fprintf(stderr, "unable to read disk, retVal = %d\n", retVal );
                exit(1);
        }

        mbr = (struct disk_mbr*) b;
        return mbr;
}

/*
* Verifies that magic values in the MBR are correct
*/
INT4 verify_magic_values(UINT1 magic_value[2])
{
	if ( (magic_value[0] == MAGIC_VAL1) && (magic_value[1] == MAGIC_VAL2) )
	{
		return 1;
	}
	return 0;
}

/*
* Gets starting address for a partition from the partition's starting sector (LBA)
*/
UINT4 get_partition_start_addr(UINT4 lba)
{
	return lba * SECTOR_SIZE;
}

/*
* Gets partition size. [Partition size = number of sectors * sector size]
*/
UINT8 get_partition_size(UINT4 num_sectors) 
{
	return (UINT8)num_sectors * SECTOR_SIZE;
}

/*
* Gets the CHS head value from the 3 byte CHS array, which is the first byte
*/
UINT1 get_head(UINT1 chs[3])
{
	return chs[0];
}

/*
* Gets the CHS sector. This is the 6 most significant bits in the second byte
* in the CHS begin/end. 
*/
UINT1 get_sector(UINT1 chs[3]) 
{
	return 0x3f & chs[1]; // we want bits 5-0, so we do bitwise operation to get these
}

/*
* Gets the CHS cylinder. This is bits 6-7 in second byte and bits 0-7 in third byte
* of CHS begin/end. 
*/
UINT2 get_cylinder(UINT1 chs[3]) 
{
	UINT2 cylinder = (chs[1] & 0xc0) << 2;
	return cylinder | chs[2];
}

/*
* Calculates LBA from CHS using predefined formula
*/
UINT4 calculate_LBA(UINT1 chs[3], UINT4 num_heads, UINT4 num_sectors) 
{
	return ((get_cylinder(chs) * num_heads + get_head(chs)) * num_sectors + (get_sector(chs) - 1));
}

/*
* Gets number of partitions on drive (maximum 4)
*/
INT4 get_partition_count(struct disk_mbr* mbr) {
	INT4 count = 0;
	for(INT4 i = 0; i < MAXNUM_OF_PARTITIONS; i++)
        {
		if(mbr->pt[i].sector_count > 0)
		{
			count++;
		}
        }
	return count;
}
