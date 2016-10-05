#ifndef __SD_H__
#define __SD_H__

#define SD_START_BLOCK	45
#define SD_BLOCK_CNT    (1024*1024/512*2)
#define DDR_START_ADDR	0x23e00000

void copy_bl2_to_ddr();
#endif
