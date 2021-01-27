#include <fstream.h>
#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
//using namespace std;

struct cell
  {
      int x;
      int y;
      int lif;
      int col;

  };

  struct race
    {
        cell c[20];
        int col;
    };

cell grid[29][35];
int up=29;
int low=35;
class store
{ public:
	int x;
	int y;
	int z;
	int lif;
	char name[30];
	store();
};

store::store()
  {
     x=0;
	 y=0;
	 z=0;
	 lif=0;
	 strcpy(name,"untitled");
  }
	cell newgrid[29][35];
//mouse in

int mousegetxy(unsigned char *left,

unsigned char *middle,

unsigned char *right,

unsigned int *x,

unsigned int *y

)

{

union REGS inregs, outregs;

struct SREGS segregs;

inregs.x.ax=0x3;

int86x(0x33, &inregs, &outregs, &segregs);

*left = outregs.x.bx & 1;

*right = outregs.x.bx & 2;

*middle = outregs.x.bx & 4;

*x = outregs.x.cx>>3;

*y = outregs.x.dx>>3;

return (*left|*middle|*right);

}

void mouseunhide(void)

{

union REGS inregs, outregs;

struct SREGS segregs;

inregs.x.ax=0x1;

int86x(0x33, &inregs, &outregs, &segregs);

}

void mousehide(void)

{

union REGS inregs, outregs;

struct SREGS segregs;

inregs.x.ax=0x2;

int86x(0x33, &inregs, &outregs, &segregs);

}







void mousesetsens( unsigned int x,

unsigned int y,

unsigned int speed

)

{

union REGS inregs, outregs;

struct SREGS segregs;

inregs.x.ax=0xF;

inregs.x.cx= x;

inregs.x.dx= y;





int86x(0x33, &inregs, &outregs, &segregs);

inregs.x.ax=0x13;

inregs.x.dx= speed;





int86x(0x33, &inregs, &outregs, &segregs);



}







void mousesetmaxxy( unsigned int minx,

unsigned int maxx,

unsigned int miny,

unsigned int maxy

)

{

union REGS inregs, outregs;

struct SREGS segregs;

inregs.x.ax=0x7;

inregs.x.cx= minx<<3;

inregs.x.dx= maxx<<3;





int86x(0x33, &inregs, &outregs, &segregs);

inregs.x.ax=0x8;

inregs.x.cx= miny<<3;

inregs.x.dx= maxy<<3;





int86x(0x33, &inregs, &outregs, &segregs);



}


int mousehit(void)

{

union REGS inregs, outregs;

struct SREGS segregs;

inregs.x.ax=0x3;

int86x(0x33, &inregs, &outregs, &segregs);

return outregs.x.bx & 7;



}


//mouse in


void creategrid()
{
	int x=1, y=1;
	for(x=50;x<619;x=x+16)  //vertical ||||||
	   for(y=7;y<471;y++)
	 {
		  float W = 0.25;
		  setcolor(GREEN);
		  rectangle(x-W,y-W,x+W,y+W);

	 }
 for(y=7;y<507;y=y+16)        //horizontal _________
	 {
	 for( x=50; x<609;x++)
	   {
		 float W = 0.25;
		  setcolor(GREEN);
		  rectangle(x-W,y-W,x+W,y+W);

		 // setfillstyle(SOLID_FILL,FC);
		 // floodfill(x,y,FC);
	  }
	}


}
void mapongrid(int x , int y, int v)
{
	int i=0;
	//while(i<ent)
	{

		int xcoor=x+1,ycoor=y+1;
		/*cout<<"Enter x coordinate: ";
		cin>>xcoor;
		cout<<"Enter y coordinate: ";
		cin>>ycoor;
		cout<<endl;*/

		int nxcoor = xcoor+57;         // brings new var
		int nycoor= ycoor+14;          // to (1,1) (n denotes new)

		xcoor--; ycoor--;               //allows index to begin at (0,0)

		nxcoor = nxcoor+(15*xcoor);    //puts the var at
		nycoor = nycoor+(15*ycoor);    //required co-ordinate
		int FM=BLUE;
		if(v==2)FM=BLACK;
		else if(v==3)FM=GREEN;
		else if(v==4)FM=RED;
		else if(v==5)FM=WHITE;

		setcolor(FM);
		rectangle(nxcoor-7,nycoor-7,nxcoor+6,nycoor+6);//thickness ofthe block determined here
	 //	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
		setfillstyle(SOLID_FILL, FM);
		floodfill(nxcoor,nycoor,FM);
		i++;
	}
}


void initialise()
  {

      for(int i=0;i<up;i++)
      {
	  for(int j=0;j<low;j++)
	  {
	      grid[i][j].x=i;
	      grid[i][j].y=j;
	      grid[i][j].lif=0;
	      grid[i][j].col=0;
	  }
      }
  }

  void input()
    {
		ifstream ifile("inp.txt");
	int n=0;
	ifile>>n;
	for(int i=0;i<n;i++)
	{
	    int x=0;
	    int y=0;
	    ifile>>x;
	    ifile>>y;
	    grid[x-1][y-1].lif=1;
	    grid[x-1][y-1].col=1;
	}
		ifile.close();
    }

void inputal(int val)
  {
      int n;
	  cout<<"now"<<endl;
      //cout<<"race "<<val<<" : "<<endl;
	  ifstream ifile;
	  if(val==2)ifile.open("inp2.txt");
	  else if(val==3)ifile.open("inp3.txt");
	  else ifile.open("inp4.txt");
      ifile>>n;
      for(int i=0;i<n;i++)
      {
	  int x=0;
	  int y=0;
	  ifile>>x>>y;
	  grid[x-1][y-1].lif=(val);
      }
	  ifile.close();
  }

  void inputtot(int v)
     {

			cleardevice();
			creategrid();
			setcolor(GREEN);
			rectangle(0,0,45,20);
			//gotoxy(0,0);
			//gotoxy(20,30);
		    //cout<<"\n  next";
				gotoxy(1,1);
				cout<<"PRESS";
		 //printf("next");
			unsigned int x,y, r;
			unsigned char a,b,c;
				int i=0;
				int count=0;
				getch();
				getch();

		       //	cin>>i;
			while(1){
			getch();
				mouseunhide();
				getch();
				r = mousegetxy(&a,&b,&c,&x,&y);
				//getch();
				//printf("%d %d %d %c %c\n",x, y ,r ,a, b);
				int lk=0,kl=0;
				if(r==2)
				  {  mousehide();
				     return;
				  }
				if(r!=0)
					{
						count++;
					      //	cout<<((x-7)/2)<<"   "<<((y-1)/2)<<"    "<<count<<endl;
						for(int u=0;u<30000;u++)
							{
								for(int h=0;h<300;h++)
								  {
								     for(int yu=0;yu<7;yu++);
								  }
							}
						lk=(x-7)/2;
						kl=(y-1)/2;
						if(lk<36 && kl<=30){
						    if(grid[kl][lk].lif==0){grid[kl][lk].lif=v;
						    if(v!=2)mapongrid(lk,kl,v);
						    else mapongrid(lk,kl,5);
						    }
						    else{
						      grid[kl][lk].lif=0;
						      mapongrid(lk,kl,2);
						      }
						    }
						/*if(lk==12 && kl==39)
						  {
						     cout<<"hello"<<endl;
						     return;
						  }*/
						if((x>=0 && x<=5) && (y>=0 && y<=5))
						   {
						     // cout<<"hello-------------------------------"<<endl;
						     //cout<<"next";
							 mousehide();
							  return;
							}
					}
					//i++;
					for(int yu=0;yu<3000;yu++)
					  {
					     for(int tu=0;tu<300;tu++);
						 }
			}

			//cout<<"done!!!";
			//getch();
			getch();
			mousehide();
	 }


 void cleargrid()
{
	for(int i=1;i<30;i++)
	  {
	      for(int j=1;j<36;j++)
		    {
			    int xcoor=j,ycoor=i;
		/*cout<<"Enter x coordinate: ";
		cin>>xcoor;
		cout<<"Enter y coordinate: ";
		cin>>ycoor;
		cout<<endl;*/

		int nxcoor = xcoor+57;         // brings new var
		int nycoor= ycoor+14;          // to (1,1) (n denotes new)

		xcoor--; ycoor--;               //allows index to begin at (0,0)

		nxcoor = nxcoor+(15*xcoor);    //puts the var at
		nycoor = nycoor+(15*ycoor);    //required co-ordinate
		int FM=WHITE;
		setcolor(FM);
		rectangle(nxcoor-7,nycoor-7,nxcoor+6,nycoor+6);//thickness ofthe block determined here
	 //	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
		setfillstyle(SOLID_FILL, FM);
		floodfill(nxcoor,nycoor,FM);
			}
	  }
}

void disp()
{
    //system("cls");
	//clrscr();
	cleargrid();
    for(int i=0;i<up;i++)
    {
	for(int j=0;j<low;j++)
	{
			if(grid[i][j].lif!=0)
			  {
			     int v=grid[i][j].lif;
				 mapongrid(j,i,v);
			  }
	    //(grid[i][j].lif==0)?cout<<" . ":cout<<" 0 ";
	    //if(grid[i][j].lif!=0)cout<<" "<<(grid[i][j].lif-1)<<" ";
	    //else cout<<" . ";
	}
	//cout<<endl;
    }
 //	mapongrid(-2,12,1);

}

int decliv(int i , int j , int val)
  {

     int neigh=0;
	for(int a = -1; a <= 1; a++)
	    {
		for(int b = -1; b <= 1; b++)
		{
		    if (!(a==0 && b==0) && (i+a)>=0 && (i+a) <= (up-1) && (j+b)>=0 && (j+b) <= (low-1) && grid[i+a][j+b].lif==val)
		    {
			neigh++;
		    }
		}
	    }
	    //neigh++;

	//getch();
	//cout<<i<<"      "<<j<<"      "<<neigh<<endl;
	if(grid[i][j].lif==val)
	{
	   if(neigh==3 || neigh==2)return(1);
	   else return(0);
	}
	else
	{
	    if(neigh==3)return(1);
	    return 0;
	}


  }

void play()
  {
      disp();
      for(int mn=0;mn<1000;mn++)
      {
	  for(int u=0;u<1000;u++)
	  {
	      for(int t=0;t<10;t++);
	  }
      }
      //getch();
      //system("cls");
	 // clrscr();
      cell g1[29][35];
      int b=0,c=0,d=0;
      for(int i=0;i<up;i++)
      {
	  for(int j=0;j<low;j++)
	  {
	      //int v=grid[i][j].lif;
	     int a = decliv(i,j,1);
	     g1[i][j].lif=a;
	     if(a!=0)continue;
	     //if(a==0)
	     {b=decliv(i,j,2);
	      g1[i][j].lif=(b==0)?0:2;

	     }
	    if(b!=0)continue;

	     //if(b==0)
	     {c=decliv(i,j,3);
	      g1[i][j].lif=(c==0)?0:3;

	     }
	    if(c!=0)continue;
	     //else if(c==0)
	     {d=decliv(i,j,4);
	      g1[i][j].lif=(d==0)?0:4;

	    }

	  }
      }

      for(int k=0;k<up;k++)
      {
	  for(int u=0;u<low;u++)
	  {
	      grid[k][u]=g1[k][u];
	  }
      }

  }
  int z=0;
  void enddet()
	{

		for(int i=0;i<up; i++)
		{
		for(int j=0; j<low; j++)
			{
			if(grid[i][j].lif >0)
				{
			  newgrid[i][j].x=1;
			  newgrid[i][j].y=1;
			  newgrid[i][j].lif=grid[i][j].lif;
				}
			  else
			  {
				newgrid[i][j].x=0;
				newgrid[i][j].y=0;
				newgrid[i][j].lif=0;
			  }
			}

		 }

	}
void livedet()
{
  for(int i=0;i<up;i++)
    {
	for(int j=0;j<low;j++)
	{
	    //(grid[i][j].lif==0)?cout<<" . ":cout<<" 0 ";
	    if(grid[i][j].lif>0)/*cout<<" "<<(grid[i][j].lif-1)<<" ";*/
			  // mapongrid(i,j);
			 { z++;
			 }

	    //else cout<<" . ";

	}
       //	cout<<endl;
    }
//    cout<<z;

}

void mapfinal()
{

    //system("cls");
    int p=0;
  // cleargrid();  //prints white squares over everything
   cleardevice();
   char nm[30];
   cout<<"Enter name for our simulation : ";
   cin>>nm;
  // store instance[z];
   store* obj=new store[z];
   for(int i=0;i<up;i++)
    {
	for(int j=0;j<low;j++)
	{
	    //(grid[i][j].lif==0)?cout<<" . ":cout<<" 0 ";
	    if(newgrid[i][j].lif>0)/*cout<<" "<<(grid[i][j].lif-1)<<" ";*/
			  // mapongrid(i,j);
			 {// cout<<" "<<i<<" "<<j;
			   obj[p].x=i;
			   obj[p].y=j;
			   obj[p].z=z;
			   //if(newgrid[i][j].lif==2)obj[p].lif=5;
			   obj[p].lif=newgrid[i][j].lif;
			   strcpy(obj[p].name,nm);
			   p++;
			   }

	    //else cout<<" . ";

	}
       //	cout<<endl;
    }
 //   cell obj;

  ofstream ofile;
   ofile.open("temp.dat",ios::ate|ios::binary);

   // while(i<(35*29)
   // {
    //	ffile.write((char*)&obj,sizeof(cell));
   // }

    /*for(int k=0;k<up;k++)
      { cout<<endl;
	ofile<<endl;
	for(int m=0;m<low;m++)
	       {    //	cout<<newgrid[k][m].x;
	       //	cout<<newgrid[k][m].y;}
	       ofile<<newgrid[k][m].lif;
		 ofile<<" ";
		  }
	     }
      ofile<<endl;
      ofile.close();*/
	   for(int l=0; l<z;l++)
	  ofile.write((char*)&obj[l],sizeof(store));


// for(int m=0;m<z;m++)
// { cout<<obj[m].x<<" ";
//   cout<<obj[m].y<<" ";
// }

 ofile.close();
      getch();
}

void read()
{
  int d=0;
  ifstream ifile;
  store st;
  int ij=1;
  int ch=1;
  while(ch!=0)
  {
	ij=1;
	ifile.open("temp.dat",ios::binary);
	setcolor(YELLOW);
	 settextstyle(7,HORIZ_DIR,5);
	 outtextxy(25,25,"PREVIOUS ITERATIONS");
	 gotoxy(1,8);
	 while(ifile.read((char*)&st,sizeof(store)))
	  {
			z=st.z;
			//store *rd = new store[z];
			//rd[0]=st;
			for(d=1;d<z;d++)
			{
			ifile.read((char*)&st,sizeof(store));
				}

			//cleardevice();
			//creategrid();
			///for(int o=0;o<z;o++)
			//{//cout<<rd[o].x;
			//cout<<rd[o].y;
			//cleardevice();
	 
			//mapongrid(rd[o].x,rd[o].y);
		    //getch();
			cout<<ij<<" . "<<st.name<<endl;
			ij++;
		}
		cout<<"0 . CLOSE MODE"<<endl;
		//int ch=0;
	  cout<<"Enter choice : ";
	  cin>>ch;
	 // ch--;
	 //if(ch==0)return 0;
	  ij=0;
	  ifile.close();
	  ifile.open("temp.dat",ios::binary);
	 // int d=0;
	 //ifile.seekg(0,ios::beg);
	  while(ifile.read((char*)&st,sizeof(store)))
	  {		z=st.z;
			store *rd = new store[z];
			rd[0]=st;
			for(d=1;d<z;d++)
			{
				ifile.read((char*)&rd[d],sizeof(store));
			}
		  ij++;
		  if(ij==ch)
		   {
			cleardevice();
			creategrid();
			for(int o=0;o<z;o++)
			{//cout<<rd[o].x;
			//cout<<rd[o].y;

			if(rd[o].lif!=2)mapongrid(rd[o].y,rd[o].x,rd[o].lif);
			else mapongrid(rd[o].y,rd[o].x,5);
			} getch();
		       //	break;
		   }

		}
		clrscr();
		cleardevice();
		ifile.close();
	  }
	ifile.close();
       //return 1;
}

void insruc(int a)
 {
    ifstream ifile("instruc.txt");
	while(ifile)
	{
	   char str[1800];
	   ifile.getline(str,1800);
	   cout<<str<<endl;
	  }
	  ifile.close();
 }

int main()
{

     int driver, mode;
	 driver = DETECT;
	 initgraph(&driver, &mode, "C:\\turboc3\\bgi");
	 cleardevice();
	 setcolor(WHITE);          // paints the town
		floodfill(0,0,WHITE);     // white


		initialise();
    //input();
    //inputal(2);
    //inputal(3);
    //inputal(4);
		clrscr();
	 while(1)
	 {
	 cleardevice();
	 setcolor(YELLOW);
	 settextstyle(7,HORIZ_DIR,5);
	 outtextxy(25,25,"GAME OF LIFE");
	 gotoxy(1,8);
	 getch();
	 //cout<<endl;
	 int ch=0;
	 cout<<"1 . PLAY\n2 . INSTRUCTIONS\n3 . PREVIOUS ITERATIONS\n4 . EXIT : ";
	// getch();
	 cin>>ch;
	 switch(ch)
	 {
	   case 1 :
		/*setcolor(WHITE);          // paints the town
		floodfill(0,0,WHITE);     // white


		initialise();
    //input();
    //inputal(2);
    //inputal(3);
    //inputal(4);
		clrscr();*/
       //	cleardevice();
	//creategrid();
		//getch();
		//getch();
		//inputal(2);
		inputtot(1);
		//cleardevice();
		clrscr();
		//creategrid();
		inputtot(2);
		clrscr();
		inputtot(3);
		clrscr();
		inputtot(4);
		cleardevice();
		//clrscr();
		creategrid();
		getch();
		for(int i=0;i<40;i++)
		{
		play();
		}
		getch();
	       //	cout << "Hello world!" << endl;
			clrscr();
			cleardevice();
			livedet();
			enddet();
			mapfinal();
		       //	cout<<"lol"<<endl;
			getch();
		    break;
		case 2 ://cout<<"here"<<endl;
			//instruc(2);
			clrscr();
			cleardevice();
	 setcolor(YELLOW);
	 settextstyle(7,HORIZ_DIR,5);
	 outtextxy(25,25,"INSTRUCTIONS");
	 gotoxy(1,8);
				ifstream ifile("instruc.txt");
				char str[1800];
				while(ifile.getline(str,1800,'\n'))
				{

				       if(str[0]=='`')break;
					cout<<str<<endl;
				       //	getch();
					if(str[0]=='`')break;
				}
				ifile.close();
				getch(); //do something
		    break;
		case 3 ://cout<<"\ninto\n\n";
			//getch();
			/*cout << "Hello world!" << endl;
			clrscr();
			cleardevice();
			livedet();
			enddet();
			mapfinal();*/
		       //	cout<<"lol"<<endl;
			//getch();

			cleardevice();
	 setcolor(YELLOW);
	 settextstyle(7,HORIZ_DIR,5);
	 outtextxy(25,25,"PREVIOUS ITERATIONS");
	 gotoxy(1,8);
		// rawcoor();
			read();
			//getch();
			//getch();
			break;
		case 4 :exit(0);
		default : break;
		}
		clrscr();
		cleardevice();
	}
			return 0;
	}
