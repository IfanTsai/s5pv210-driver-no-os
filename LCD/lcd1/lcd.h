#ifndef __LCD_H__
#define __LCD_H__

//显存首地址
#define FB_ADDR			(0x23000000)

//屏幕尺寸
#define ROW				(1024)
#define COL				(600)
#define HOZVAL			(ROW - 1)
#define LINEVAL			(COL - 1)
#define XSIZE			ROW
#define YSIZE			COL

//时序中的时间参数
#define HSPW 			(40)				// 1~40 DCLK  //20
#define HBPD			(10 - 1)			// 46         //140
#define HFPD 			(240 - 1)			// 16 210 354 //160
#define VSPW			(20)				// 1~20 DCLK  //3
#define VBPD 			(10 - 1)			// 23         //20
#define VFPD 			(30 - 1)			// 7 22 147   //12

//显示空间坐标参数
#define LeftTopX        0
#define LeftTopY        0
#define RightBotX       (1024 - 1) 
#define RightBotY       (600 - 1) 

#define GPF0CON         (*((volatile unsigned int *)0xe0200120))
#define GPF1CON         (*((volatile unsigned int *)0xe0200140))
#define GPF2CON         (*((volatile unsigned int *)0xe0200160))
#define GPF3CON         (*((volatile unsigned int *)0xe0200180))

#define GPD0CON         (*((volatile unsigned int *)0xe02000a0))
#define GPD0DAT         (*((volatile unsigned int *)0xe02000a4))

#define DISPLAY_CONTROL (*((volatile unsigned int *)0xe0107008))

#define VIDCON0         (*((volatile unsigned int *)0xf8000000))
#define VIDCON1         (*((volatile unsigned int *)0xf8000004))
#define VIDTCON0        (*((volatile unsigned int *)0xf8000010))
#define VIDTCON1        (*((volatile unsigned int *)0xf8000014))
#define VIDTCON2        (*((volatile unsigned int *)0xf8000018))
#define WINCON0         (*((volatile unsigned int *)0xf8000020))
#define VIDOSD0A        (*((volatile unsigned int *)0xf8000040))
#define VIDOSD0B        (*((volatile unsigned int *)0xf8000044))
#define VIDOSD0C        (*((volatile unsigned int *)0xf8000048))

#define VIDW00ADD0B0    (*((volatile unsigned int *)0xf80000a0))
#define VIDW00ADD1B0    (*((volatile unsigned int *)0xf80000d0))
#define SHODOWCON       (*((volatile unsigned int *)0xf8000034))   

/*绘图相关*/
#define RED    0xff0000
#define GREEN  0x00ff00
#define BLUE   0x0000ff
#define WHITE  0xffffff

typedef unsigned int u32;

void lcd_init();
void lcd_draw_pixel(u32 x, u32 y, u32 color);
void lcd_set_bkcolor(u32 color);
void lcd_draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color);
void lcd_draw_circle(u32 centerX, u32 centerY, u32 radius, u32 color);
void lcd_write_ch(u32 x, u32 y, char ch, u32 color);
void lcd_write_str(u32 x, u32 y, char *str, u32 color);

#endif