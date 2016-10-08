//2016年10月4日17:47:26
/*
*notes:
*1.虚拟显示：LCD为了增加显示效率,采用了虚拟显示的做法，即显存大小可以大于真实的屏幕尺寸。
*			当要显示大图像时，直接将大图像全部一次性加载入显示缓存区，
*           然后每次移动的时候就不需要重新刷新加载图片了。
*
*2.显示空间：在显存中取的空间即显示空间，改变显示空间就可以看大图的看不到部分
*		   （因为使用了虚拟显示，所以此时不需要重新刷新加载图片）。
*
*3.虚拟屏幕叠加：实际上LCD支持多个window，在显示的时候可以进行叠加，
*				利用透明度的不同，可以把多个图形叠在一起来显示一定的特效。
*
*/
#include "lcd.h"
//#include "ascii.h"

static u32 *pfb = (u32*)FB_ADDR;

void lcd_init()
{
	//配置LCD引脚
	GPF0CON = 0x22222222;
	GPF1CON = 0x22222222;
	GPF2CON = 0x22222222;
	GPF3CON = 0x22222222;

	//开背光
	GPD0CON &= ~(0xf << 0);
	GPD0CON |= (0x1 << 0);
	GPD0DAT &= ~(0x1 << 0);

	//select display path
	DISPLAY_CONTROL = (0x2 << 0);

	// bit[26~28]:使用RGB接口
	// bit[18]:RGB 并行
	// bit[2]:选择时钟源为HCLK_DSYS=166MHz
	VIDCON0 &= ~( (3<<26)|(1<<18)|(1<<2) );

	// bit[1]:使能lcd控制器
	// bit[0]:当前帧结束后使能lcd控制器
	VIDCON0 |= ( (1<<0)|(1<<1) );

	// bit[4]:选择需要分频
	// bit[6~13]:分频系数为5，即VCLK = 166M/(4+1) = 33M
	VIDCON0 |= 4<<6 | 1<<4;

	// H43-HSD043I9W1.pdf(p13) 时序图：VSYNC和HSYNC都是低脉冲
	// s5pv210芯片手册(p1207) 时序图：VSYNC和HSYNC都是高脉冲有效，所以需要反转
	VIDCON1 |= 1<<5 | 1<<6;

	// 设置时序
	VIDTCON0 = VBPD<<16 | VFPD<<8 | VSPW<<0;
	VIDTCON1 = HBPD<<16 | HFPD<<8 | HSPW<<0;

	// 设置长宽(物理屏幕尺寸)
	VIDTCON2 = (LINEVAL << 11) | (HOZVAL << 0);

	// 设置window0
	// bit[0]:使能
	// bit[2~5]:24bpp（RGB888）
	WINCON0 |= 1<<0;
	WINCON0 &= ~(0xf << 2);
	WINCON0 |= (0xB<<2) | (1<<15);

	// 设置window0
	// 设置显示空间的大小(这里指的是虚拟显示的大小，可以大于屏幕的物理大小)
	VIDOSD0A = (LeftTopX<<11) | (LeftTopY << 0);
	VIDOSD0B = (RightBotX<<11) | (RightBotY << 0);
	VIDOSD0C = (LINEVAL + 1) * (HOZVAL + 1);
	
	VIDW00ADD0B0 = FB_ADDR;// 设置显存首地址
	//设置显存大小，实际上用的是24bpp,用3个字节存储，但是为了字节对齐，这里采用了*4
	VIDW00ADD1B0 = (((HOZVAL + 1)*4 + 0) * (LINEVAL + 1)) & (0xffffff);

	// 使能window 0传输数据
	SHODOWCON = 0x1;
}

inline void lcd_draw_pixel(u32 x, u32 y, u32 color)
{
	*(pfb + y * ROW + x) = color;
}

void lcd_set_bkcolor(u32 color)
{
	for(u32 j=0;j<COL;j++)
	{
		for(u32 i=0;i<ROW;i++)
		{
			lcd_draw_pixel(i, j, color);
		}
	}
}

void lcd_draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;  
				while(x1<=x2)
				{
					lcd_draw_pixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					lcd_draw_pixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					lcd_draw_pixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else	 // 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					lcd_draw_pixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else //dx<0
	{
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					lcd_draw_pixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					lcd_draw_pixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					lcd_draw_pixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					lcd_draw_pixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}

void lcd_draw_circle(u32 centerX, u32 centerY, u32 radius, u32 color)
{
	int x,y ;
	int tempX,tempY;;
    int SquareOfR = radius*radius;

	for(y=0; y<XSIZE; y++)
	{
		for(x=0; x<YSIZE; x++)
		{
			if(y<=centerY && x<=centerX)
			{
				tempY=centerY-y;
				tempX=centerX-x;                        
			}
			else if(y<=centerY&& x>=centerX)
			{
				tempY=centerY-y;
				tempX=x-centerX;                        
			}
			else if(y>=centerY&& x<=centerX)
			{
				tempY=y-centerY;
				tempX=centerX-x;                        
			}
			else
			{
				tempY = y-centerY;
				tempX = x-centerX;
			}
			if ((tempY*tempY+tempX*tempX)<=SquareOfR)
				lcd_draw_pixel(x, y, color);
		}
	}
}
#if 0
void lcd_write_ch(u32 x, u32 y, char ch, u32 color)
{
	for(u32 j=y;j<y+16;j++)
	{
		for(u32 i=x, count=0;i<x+8;i++, count++)
		{
			//将一个字节的数据按位依次取出，并进行判断是否需要画像素
			//ascii_8_16参考ascii.h
			if(ascii_8_16[ch-0x20][j-y] & (0x1 << count))
			{
				lcd_draw_pixel(i, j, color);
			}
		}
	}
}

void lcd_write_str(u32 x, u32 y, char *str, u32 color)
{
	while(*str)
	{
		if(x >= XSIZE)//对将写到屏幕外的字符的处理
		{
			x -= XSIZE;
			y += 16;//将位置转到下一行
		}
		lcd_write_ch(x, y, *str, color);
		str++;
		x += 8;
	}
}
#endif