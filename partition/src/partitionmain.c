#include "partitioninc.h"
struct hd_geometry geometry;

VOID main(int argc, char** argv) {
	FILE *hd;
	INT4 fd;
	struct disk_mbr* mbr;
	INT4 i;

	if(argc < 2) 
	{
		fprintf(stderr, "USAGE: %s /dev/sdx [all/partition_count/partition_size/partition_address]\n", argv[0]);
		return;
	}
	
	fd = open(argv[1], O_RDONLY);
	if ( fd <= 0 )
	{
		fprintf(stderr, "File not opened = %x %s\n", hd , strerror(errno));
		return;
	}
	ioctl(fd, HDIO_GETGEO, &geometry); // initialize the geometry struct
	mbr = getMBR(fd); // initialize the mbr struct
	if(verify_magic_values(mbr->signature) == 0)
        {
                fprintf(stderr, "Error...MBR is corrupted");
                return;
        }
	
	//default prints all if no optional parameters are supplied
	if(argc == 2 || strcmp("all",argv[2]) == 0)
	{
		printPartitionMetadata(mbr);
	}
	else if(strcmp("partition_count", argv[2]) == 0)
	{
		//print number of partitions
		fprintf(stdout, "Number of partitions = %d\n\n", get_partition_count(mbr));
	}
	else if(strcmp("partition_size", argv[2]) == 0)
	{
		//print partition sizes
		for(i = 0; i < MAXNUM_OF_PARTITIONS; i++)
		{
			fprintf(stdout, "Partition %d Size = %llu bytes\n", i + 1, get_partition_size(mbr->pt[i].sector_count));

		}
	}
	else if(strcmp("partition_address", argv[2]) == 0)
	{
		//print partition addresses
		for(i = 0; i < MAXNUM_OF_PARTITIONS; i++)
		{
			fprintf(stdout, "Partition %d starting address = 0x%.2"PRIx32"\n", i + 1, get_partition_start_addr(mbr->pt[i].first_sector_lba));
		}
	}
	close(fd);
}
