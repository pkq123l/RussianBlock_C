#include <easyx.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <graphics.h>


#define True 1 
#define False 0
typedef int BOOL;
//typedef int BOOLEAN;
/* 下落的方块 */
extern int ges[20][10];

/* 落实不动的方块 */
extern int shiKuais[20][10] ;

/* 下落方块的颜色 */
extern int color;
/* 消掉行的得分 */
extern int fen ;



void xinKuai()
{
	int fk = rand()%5;
	color = rand()%11 + 1;//随机颜色
	switch (fk)
	{
	case 0:
			ges[0][3] =  ges[0][4]  = color;
			ges[1][3] = color;	 ges[1][4] = color;
		break;
	case 1:
		ges[0][5] = ges[0][3] =  ges[0][4]  = color;
		ges[1][5] =color;
		break;
	case 2:
			ges[0][3] =  ges[0][4]  = color;
			ges[1][4] = ges[1][5] =color;
		break;
	case 3:
		ges[0][5] = ges[1][5] =  ges[2][5]  = ges[3][5]  = color;
		break;
	case 4:
		ges[0][3] = ges[0][4] =  ges[0][5]  = ges[0][6]  = color;
		break;

	}
}

void showBG()
{
	IMAGE imgbg;
	loadimage(&imgbg, ".\\images\\2\\bg-1.png") ; 
	putimage(0,0,&imgbg);
}

void showXiaLuo()
{
	IMAGE imgfk;
	TCHAR imgPath[100];

	_stprintf (imgPath, ".\\images\\2\\%d.png", color); 
	loadimage(&imgfk,imgPath ) ; 
	int h,l;
	for(h=0;h<20;h++)
	{
		for(l=0;l<10;l++)
		{
			if (ges[h][l]!=0)
			{
				putimage(30+l*30,5+h*30,&imgfk);
			}
		}
	}
}

void showLuoShi()
{
	int h,l;
	IMAGE imgfk;
	TCHAR imgPath[100];
	for( h=0 ;h<20 ; h++)
	{
		for(l=0;l<10;l++)
		{
			if(shiKuais[h][l])
			{
				_stprintf (imgPath, ".\\images\\2\\%d.png", shiKuais[h][l]); 
				loadimage(&imgfk,imgPath ) ; 
				putimage(30+l*30,5+h*30,&imgfk);
			}
		}
	}
}

void showFen()
{
	settextstyle(18, 0, _T("黑体"));
	settextcolor(0xffffff);
	TCHAR str[100];
	_stprintf (str,  "%d分", fen);
	outtextxy(390,228,str );
	_stprintf (str,  "Level %d", 1);
	outtextxy(390,294,str );
}

BOOL nengZuo()
{
	int i;
	for( i=0;i<20;i++ )
	{
		if( ges[i][0]!=0 )
		{
			return False;
		}
	}
	return True;
}

 BOOL nengZuoBuDang()
{
	/*int zuoBuDang=1;*/
	int h,l;
	for( l=1;l<=9;l++)
	{
		for(h=0;h<20;h++)
		{
			if(ges[h][l] && shiKuais[h][l-1] )
			{
				/*zuoBuDang=0;
				break;*/
				return False;
			}
		}
	}
	return True;
}

void zuoYi()
{
	int h,l;
	for(l=1;l<=9;l++)
	{
		for(h=0;h<20;h++)
		{
			ges[h][l-1]=ges[h][l];
			ges[h][l]=0;
		}
	}
}

BOOL nengYou()
{
	int i;
	for( i=0;i<20;i++ )
	{
		if( ges[i][9]!=0 )
		{
			/*youBuChuJie=0;
			break;*/
			return False;
		}
	}
	return True;
}

BOOL nengYouBuDang()
{
	int h,l;
	for( l=8; l>=0 ; l-- )
	{
		for(h=0  ; h<20 ; h++ )
		{
			if(ges[h][l]&&shiKuais[h][l+1] )
			{
				return False;
			}
		}
	}
	return True;
}

void youYi()
{
	int h,l;
	for( l=8; l>=0 ; l-- )
	{
		for(h=0  ; h<20 ; h++ )
		{
			ges[h][l+1]=ges[h][l];
			ges[h][l]=0;
		}
	}
}

void heBing()
{
	int h,l;
	for( h=0;h<20 ; h++)
	{
		for(l=0 ;l<10 ; l++ )
		{
			if(ges[h][l]!=0)
			{
				shiKuais[h][l]=ges[h][l];
				ges[h][l]=0;
			}
		}
	}
}

int nengXiao(int hang[])
{
	int kl;// 看列
	for( kl=0;kl<10;kl++ )
	{
		if(hang[kl]==0 )
		{
			return 0;
		}
	}
	return 1;
}

int xiaoHang()
{
	int kh,kl;//看行 看列
	int xh,xl;//下落消掉
	int xhs=0;//消掉的行数
	for(kh=0;kh<20;kh++)
	{
		//看看此行能否消掉
		if( nengXiao(shiKuais[kh]))
		{
			xhs++;
			//消掉此行
			for(  xh= kh-1;xh>=0 ;xh--  )
			{
				for( xl=0;xl<10;xl++)
				{
					shiKuais[xh+1][xl]=shiKuais[xh][xl];
					shiKuais[xh][xl]=0;
				}
			}
		}
	}
	return xhs;
}

void deFen(const int xhs ) 
{
	switch(xhs)
	{
	case 1:
		fen+=20;
		break;
	case 2:
		fen+=60;
		break;
	case 3:
		fen+=180;
		break;
	case 4:
		fen+=360;
		break;
	case 5:
		fen+=1000;
		break;
	}
}
//review
int nengXia()
{
	int i;
	for(i=0;i<10;i++)
	{
		if(ges[19][i]!=0)
		{
			/*xiaBuChuJie=0;
			break;*/
			return 0;
		}
	}
	return 1;
}

int nengXiaBuDang()
{
	int h,l;
	for( h=18;h>=0;h--)
	{
		for( l=0;l<10;l++ )
		{
			if( ges[h][l] && shiKuais[h+1][l])
			{
			/*	xiaBuDang=0;
				break;*/
				return 0;
			}
		}
	}
	return 1;
}

void xiaYi()
{
	int h,l;
	//---------方块下落------------//
	for(h=18 ;h>=0 ; h--)
	{
		for( l=0; l<10;l++ )
		{
			ges[h+1][l]=ges[h][l];
			ges[h][l]=0;
		}
	}
}

int nengShu()
{
	int cl;//查第0行的所有列
	for( cl=0  ;  cl<10; cl++  )
	{
		if( shiKuais[0][cl] )
		{
			return 1;
		}
	}
	return 0;
}