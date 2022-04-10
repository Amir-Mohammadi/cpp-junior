#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<iostream.h>
#include<dos.h>
#include<process.h>
#include<ctype.h>
#include<fstream.h>

#define HL 2
#define TC 7
#define BK 5

//**************************************************************************//
char *dialog(int,int,int);
void cursor(int);
void menu(int,int,int,int,char *str);
void bk(int);
void tc(int);
void mod(int);
//**************************************************************************//
void mod(int a)
{
 REGS reg;
 reg.h.ah=0;
 reg.h.al=a;
 int86(0x10,&reg,&reg);
}
//**************************************************************************//
void cursor(int a)
{
 union REGS reg;
 reg.h.ah=0x1;
 reg.h.ch=0x9;
 reg.h.cl=a;
 int86(0x10,&reg,&reg);
}
//**************************************************************************//
void bk(int n)
{
 textbackground(n);
}
//**************************************************************************//
void tc(int n)
{
 textcolor(n);
}
//Menu**********************************************************************//
void menu(int j/*TxtBckCo*/,int k/*TxtCo*/,int x/*Column*/,int y/*Line*/,char *str/*TextMess*/)
{
	tc(k);
	bk(j);
	gotoxy(x,y);
	cprintf("%s",str);
	bk(2);
	tc(0);
}
//**************************************************************************//
void main()
{
	mod(0x3);
	char xy[24];
	int menc=0,q=0,bs;
	char s[65],fls[1817];
	char ch,chf,chf1=NULL;
	ifstream in;
	ofstream out;
	bk(5);
	clrscr();
	bk(2);
	strcpy(fls,NULL);
	int i,j;
	for (i=1;i<=80;i++)
	   for (j=2;j<25;j++)
		{
		 gotoxy(i,j);
		 cprintf(" ");
		}
	tc(1);
	for (i=2;i<=24;i++)
		{
		 gotoxy(80,i);
		 cprintf("%c",177);
		}
	tc(3);
	bk(1);
	gotoxy(80,2);
	cprintf("%c",30);
	gotoxy(80,24);
	cprintf("%c",31);
	menu(BK,TC,1,1," Open ");
	menu(BK,TC,7,1," Save ");
	menu(BK,TC+1,13,1," Save as ");
	menu(BK,TC,22,1," Exit ");
	menu(BK,TC+8,1,25," Menu = Alt+F1 ");
	int y=2,x=1;
	while(1)
	{
		gotoxy(x,y);
		ch=getch();
		if (ch==0)
		   {
			chf1=getch();
		   }
		if (chf1==104)
		   { //1
			switch (menc){//2
				 case 0:menu(BK-2,TC+8,1,1," Open ");break;
				 case 1:menu(BK-2,TC+8,7,1," Save ");break;
				 case 2:menu(BK-2,TC+1,13,1," Save as ");break;
				 case 3:menu(BK-2,TC+8,22,1," Exit ");break;
			   }//2
			while(1)
			{//3
			cursor(0x0);
			menu(BK,TC,1,25," Menu = Alt+F1 ");
	 l1:    chf=getch();
			if (chf==27)
				{//4
				   chf1=NULL;
				   switch (menc){ //5
					 case 0:menu(BK-4,TC,1,1," Open ");break;
					 case 1:menu(BK-4,TC,7,1," Save ");break;
					 case 2:menu(BK-4,TC+1,13,1," Save as ");break;
					 case 3:menu(BK-4,TC,22,1," Exit ");break;
				   }//5
				   cursor(0x10);
				   menu(BK,TC+8,1,25," Menu = Alt+F1 ");
				   gotoxy(x,y);
				   break;
				}//4
			else if (chf=='\r')
				{ //6
				 switch (menc){//7
					 case 0:menu(BK,15,1,25,"Path to open:                                                                  ");
							gotoxy(14,25);
							cursor(0x10);
							strcpy(s,dialog(15,80,25));
							menu(BK,TC,1,25," Menu = Alt+F1                                                                 ");
							bs=0;
							gotoxy(1,2);
							in.open(s);
							while (!(in.eof()))
							{//8
								in.get(fls[bs]);
								x++;
								cprintf("%c",fls[bs]);
								if (fls[bs]=='\n')
									{
									 cprintf("\r");
									 xy[y++]=x-1;
									 x=1;
									}
								bs++;
							}//8
							in.close();
							y=wherey();
							x=wherex();
							strcpy(s,NULL);
							break;
					 case 1:menu(BK,15,1,25,"Path to save:                                                                  ");
							gotoxy(14,25);
							cursor(0x10);
							strcpy(s,dialog(15,80,25));
							menu(BK,TC,1,25," Menu = Alt+F1                                                                 ");
							strcat(s,".txt");
							out.open(s);
							for (bs=0;bs<q;bs++)
							   out<<fls[bs];
							out.close();
							strcpy(s,NULL);
							break;
					 case 2:break;
					 case 3:return;
				 }//7
				} //6
			else if (chf==0)
				{ //9
				 chf=getch();
				 if (chf==77)
					{//10
					 menc++;
					 if (menc>3) menc=0;
					}//10
				 else if (chf==75)
					{//11
					 menc--;
					 if (menc<0) menc=3;
					}  //11
				 else goto l1;
				 switch (menc)
				   {//12
					 case 0:menu(BK-2,TC+8,1,1," Open ");
							menu(BK,TC,7,1," Save ");
							menu(BK,TC,22,1," Exit ");
							break;
					 case 1:menu(BK-2,TC+8,7,1," Save ");
							menu(BK,TC,1,1," Open ");
							menu(BK,TC+1,13,1," Save as ");
							break;
					 case 2:menu(BK-2,TC+1,13,1," Save as ");
							menu(BK,TC,22,1," Exit ");
							menu(BK,TC,7,1," Save ");
							break;
					 case 3:menu(BK-2,TC+8,22,1," Exit ");
							menu(BK,TC,1,1," Open ");
							menu(BK,TC+1,13,1," Save as ");
							break;
				   }   //12
				} //9
			}//3
		   }//1
		if ( (chf1!=104) && (chf1!=NULL) )
			{
			 chf1=NULL;
			 continue;
			}
		/*else if (chf1==77)    //Right Arrow
			{
			 if (x<79)
				  x++;
			 gotoxy(x,y);
			 chf1=NULL;
			 continue;
			}
		else if (chf1==75)    //Left Arrow
			{
			 if (x>1)
				x--;
			 gotoxy(x,y);
			 chf1=NULL;
			 continue;
			}
		else if (chf1==72)    //Up Arrow
			{
			 if (y>2)
			   gotoxy(x,--y);
			 chf1=NULL;
			 continue;
			}
		else if (chf1==80)    //Down Arrow
			{
			 if (y<24)
			   gotoxy(x,++y);
			 chf1=NULL;
			 continue;
			}*/
		if (ch==27)
			 continue;
		else if (ch=='\r')
			 {
			  if (y==24) continue;
			  if ((y==24)&&(x==79)) continue;
			  fls[q++]='\n';
			  xy[y]=x;
			  y++; x=1;
			 }
		else if (ch==8)
			 {
			  if ((x==1)&&(y>2))
				  {
				   y--;
				   x=xy[y];
				  }
			  if ((x==1)&&(y==2))
				   continue;
			  if (x<1)
				   x=1;
			  if (x==1)
				 {
				  gotoxy(x,y);
				 }
			  else
				  {
				   gotoxy((x--)-1,y);
				   printf(" ");
				   gotoxy(x,y);
				  }
			  fls[q--]='\0';
			 }
		else
			{
			 if ((y==24)&&(x==79)) continue;
			 cprintf("%c",ch);
			 fls[q++]=ch;
			 x++;
			 if (x==80)
				{
				 xy[y]=x;
				 fls[q++]='\n';
				 y++;
				 x=1;
				}
			}
	}
}
/*==========================================================================*/
char *dialog(int x1,int x2,int y)
{
	char ch;
	char *word;
	int i=x1,c=0,bb;
	for (bb=0;bb<strlen(word);bb++)
		word[bb]=0;
	gotoxy(x1,y);
	while ((i<x2) || (ch==27))
	{
		ch=getch();
		if (i==x2-1)
		{
			if (ch==8)
				goto l1;
			else if (ch==13)
				break;
			else if (ch==27) goto l2;
			else continue;
		}
		if (ch==27)
		l2:
		{
			for (bb=0;bb<strlen(word);bb++)
				word[bb]=NULL;
			break;
		}
		if ((i==x1) && (ch==13)) continue;
		if ((ch==' ') && (i==x1)) continue;
		if ((ch!=0) && (ch!=27) && (ch!=13) && (ch!=8))
		{
			bk(5);
			cprintf("%c",ch);
			word[c]=ch;
			i++;
			c++;
		}
		else if ((ch==8) && (i>x1))
		l1:
		{
			word[c-1]=0;
			i--;
			c--;
			gotoxy(x1,y);
			cprintf("                                                                               ");
			gotoxy(x1,y);
			for (int ii=0;ii<strlen(word);ii++)
				cprintf("%c",word[ii]);
		}
		else if ((ch==8) && (i==x1))
		{
			for (bb=0;bb<strlen(word);bb++)
			word[bb]=0;
		}
		else if (ch==27) goto l2;
		else if (ch==13) break;
		else if (ch==0)
		{
			getch();
			continue;
		}
	}
	word[c]=NULL;
	return word;
}
