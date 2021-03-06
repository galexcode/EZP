/*-------------------------------------------------------------------
* Name: cursorc.c
* compiler :  Watcom C 10.0
* Copyright (c) 1994,1995 REDTEK BUSINESS TECHNOLOGY LTD.
-------------------------------------------------------------------*/
#include "ezpHead.h"

static char TextCursorCount;
static int TextCursorHeight;
static int OldSize=-1,OldFont=-1;
static int NewSize,NewFont;
static int OldPosition=-1;
char CFontsName[][8]={
    "�����",
    "�����",
    "�����",
    "���μ�",
    "С���μ�",
    "ϸԲ��",
    "�����",
    "κ����",
    "Ҧ���",
    "�κڼ�",
    "׼Բ��",
    "���μ�",
    "�����",
    "��Բ��",
    "׼Բ��",
    "���䷱",
    "ϸԲ��",
    "��ڼ�",
    "�п���",
    "���շ�",
    "���귱",
    "׼Բ��",
    "�ֿ˷�",
    "����",
    "���己",
    "���η�",
    "���己",
    "���己",
    "κ����",
    "����",
    "ϸ�ڷ�",
    "���߷�",
    "ӡ��",
    "ά��",
    "�����",
    "���己",
    "Բ�ڼ�",
    "Բ�ڷ�",
    "���ռ�",
    "���ֺ�",
    "ϸ�ڼ�",
    "�кڷ�",
    "ƽ�ڷ�",
    "���ĺ�",
    "�󿬷�",
    "����",
    "�����",
    "�п���",
    "���μ�",
    "����μ�",
    "ϸ���߼�",
    "�е��߼�",
    "ˮע��",
    "������",
    "���Ʒ�",
 /*----------------- Extended CFont (from 101) -----------------*/
    "�����",
    "�����",
    "�����",
    "���μ�",
    "���μ�",
    "С���μ�",
    "�ֺڼ�",
    "�п���",
    "��Բ��",
    "��Բ��",
    "���μ�",
    "�����",
    "�����",
    "��κ����",
    "���μ�",
    "�����",
    "���߼�",
    "ϸԲ��",
    "ƽ�ڼ�",
    "ϸ�μ�",
    "�п���",
    "���μ�",
    "�е��߼�",
    "ϸ���߼�",
    "���ռ�",
/**************************************/
    "ϸ�η�",
    "���η�",
    "���η�",
    "�����η�",
    "���η�",
    "���η�",
    "�ش��η�",
    "�����η�",
    "ϸ�ڷ�",
    "�кڷ�",
    "�ֺڷ�",
    "�غڷ�",
    "�شֺڷ�",
    "���غڷ�",
    "ϸԲ��",
    "��Բ��",
    "��Բ��",
    "��Բ��",
    "�ش�Բ��",
    "���䷱",
    "������",
    "������",
    "ƽ����",
    "������",
    "������",
    "������",
    "������",
    "�п���",
    "�¿���",
    "�ֿ���",
    "�ؿ���",
    "���η�",
    "�ַ·�",
    "��ӡ��",
    "���ŷ�",
    "���·�",
    "Բ�·�",
    "���鷱",
    "���з�",
    "���з�",
    "���Ʒ�",
    "�ֿ���",
    "ϸ����",
    "���շ�",
    "���귱",
    "���ڷ�",
    "κ����",
    "�տ���",
    "�ڱ䷱",
    "������",
    "���深",
    "׾����",
    "���鷱",
    "���η�",
    "ƽ�ڷ�",
    "���η�"
};


static int GetFontParamter()
{
  // int ii;
  if (GlobalTextPosition==OldPosition) return 0;
  return ToolBarHasToolBar();
}
#define GAP1  4
void DispFontWindow(int tt)
{
  int SaveColor,x,y,ii;
  struct viewporttype SaveViewPort;
  char tmpstr[100];

  MouseHidden();
  getviewsettings(&SaveViewPort);
  SaveColor=getcolor();

  setwritemode(COPY_PUT);
  setcolor(EGA_WHITE);
  setviewport(0,0,639,300,0);

  NewSize=TextSearchAttribute(GlobalBoxHeadHandle,GlobalTextPosition,CHARSIZE,&ii);
  ii=NewTextSearchAttribute(GlobalBoxHeadHandle,GlobalTextPosition-1);
  switch(ii)
  {
    case 1:   NewFont=TextSearchCFont(GlobalBoxHeadHandle,GlobalTextPosition-1,&ii);  break;
    case 2:   NewFont=TextSearchEFont(GlobalBoxHeadHandle,GlobalTextPosition-1,&ii);  break;
    default:  NewFont=TextSearchAttribute(GlobalBoxHeadHandle,GlobalTextPosition-1,CHARFONT,&ii);
  }

  x=5*TOOLBARWIDTH+GAP1+LINESPACE+6;
  y=50;
//  if (tt==1)
        {
            switch(NewFont)
             {
                case 0x400: strcpy(tmpstr,"����"); break;
                case 0x401: strcpy(tmpstr,"��б"); break;
                case 0x402: strcpy(tmpstr,"����"); break;
                case 0x403: strcpy(tmpstr,"��б"); break;
                default:
                   memset(tmpstr,0,10);
                   if(NewFont<MAXVECFONT)
                     strncpy(tmpstr,CFontsName[NewFont],4);
                   else
                   if(NewFont>=100 && NewFont<MAXTTFONTJ )
                     strncpy(tmpstr,CFontsName[NewFont-100+MAXVECFONT],4);
                   else
                   if(NewFont>=200&&NewFont<MAXTTFONTF)
                     strncpy(tmpstr,CFontsName[NewFont-200+MAXVECFONT+MAXTTFONTJ-100],4);
                   else
                     strcpy(tmpstr,"��չ");
                   break;
             }

            DisplayString(tmpstr,x+2,53,EGA_BLACK,EGA_WHITE);
            OldFont=NewFont;
        }
// if (tt==2)
        {
            x=x+TOOLBARWIDTH+40;
            sprintf(tmpstr,"%04d",NewSize);
            if (abs(NewSize-583)<4) {strcpy(tmpstr,"����"); goto disp_size_str; }
            if (abs(NewSize-361)<4) {strcpy(tmpstr,"һ��"); goto disp_size_str; }
            if (abs(NewSize-305)<4) {strcpy(tmpstr,"����"); goto disp_size_str; }
            if (abs(NewSize-222)<4) {strcpy(tmpstr,"����"); goto disp_size_str; }
            if (abs(NewSize-187)<4) {strcpy(tmpstr,"�ĺ�"); goto disp_size_str; }
            if (abs(NewSize-166)<4) {strcpy(tmpstr,"С��"); goto disp_size_str; }
            if (abs(NewSize-145)<4) {strcpy(tmpstr,"���"); goto disp_size_str; }
            if (abs(NewSize-125)<4) {strcpy(tmpstr,"С��"); goto disp_size_str; }
            if (abs(NewSize-111)<4) {strcpy(tmpstr,"����"); goto disp_size_str; }
            if (abs(NewSize-76)<4) {strcpy(tmpstr,"�ߺ�"); goto disp_size_str; }
            if (abs(NewSize-69)<4) {strcpy(tmpstr,"�˺�"); goto disp_size_str; }
            sprintf(tmpstr,"%f",(float)(NewSize/39.3f+0.009f));
            tmpstr[4]=0;
            disp_size_str:
            DisplayString(tmpstr,x+3,53,EGA_BLACK,EGA_WHITE);
            OldSize=NewSize;
        }

  setcolor(SaveColor);
  setviewport(SaveViewPort.left,SaveViewPort.top,SaveViewPort.right,
              SaveViewPort.bottom,SaveViewPort.clip);
  MouseShow();
//  CreatStatusWindow();
}

void TextCursorDisplay(void)
{
  int SaveColor;
  int x,y;
  short XY[2*4];
  int Left,Top,Right,Bottom;
  struct viewporttype SaveViewPort;


  if (GlobalBoxTool!=IDX_INPUTBOX || (GlobalBoxHeadHandle<=0)
      || CursorBlankSign<=0 || fInZoom    // ByHance, 97,5.4
      || (ItemGetFather(GlobalBoxHeadHandle)!=GlobalCurrentPage)
      || (ActiveMenu>0)||(ActiveWindow!=1)
      || GlobalTextBlockEnd>GlobalTextBlockStart
      || GlobalTableBlockStart!=GlobalTableBlockEnd
      ||!CurrentBoxEditable()||IsInGlobalBrowser())
     return;

  if (TextCursorCount)
     TextCursorCount=0;
  else
     TextCursorCount=1;

  getviewsettings(&SaveViewPort);
  SaveColor=getcolor();
  setcolor(EGA_WHITE);
  setwritemode(XOR_PUT);
  MouseHidden();
  WindowGetRect(1,&Left,&Top,&Right,&Bottom);
  setviewport(Left,Top,Right,Bottom,1);

  XY[0]=TextCursorPosX;  XY[1]=TextCursorPosY-TextCursorHeight;
  XY[6]=TextCursorPosX;  XY[7]=TextCursorPosY;
  XY[2]=XY[4]=XY[0]+5;  XY[3]=XY[1];
  XY[5]=XY[7];

  if (TextCursorRotateAngle)
  {
     RotatePoint(&x,&y,XY[0],XY[1],
           TextCursorRotateAxisX,TextCursorRotateAxisY,TextCursorRotateAngle);
     XY[0]=x; XY[1]=y;
     RotatePoint(&x,&y,XY[6],XY[7],
           TextCursorRotateAxisX,TextCursorRotateAxisY,TextCursorRotateAngle);
     XY[6]=x; XY[7]=y;
  }

  if (TextIsOverwrite())                // ByHance, 96,1.10
  {
     if (TextCursorRotateAngle)
     {
        RotatePoint(&x,&y,XY[2],XY[3],
              TextCursorRotateAxisX,TextCursorRotateAxisY,TextCursorRotateAngle);
        XY[2]=x; XY[3]=y;
        RotatePoint(&x,&y,XY[4],XY[5],
              TextCursorRotateAxisX,TextCursorRotateAxisY,TextCursorRotateAngle);
        XY[4]=x; XY[5]=y;
     }
     fillpoly(4,XY);
  }
  else
  {
     line(XY[0],XY[1],XY[6],XY[7]);
     if (TextCursorRotateAngle%180==90)
     {
        line(XY[0],XY[1]+1,XY[6]+1,XY[7]+1);
     } else {
        line(XY[0]+1,XY[1],XY[6]+1,XY[7]);
     }
  }
  setwritemode(COPY_PUT);

  setcolor(SaveColor);
  setviewport(SaveViewPort.left,SaveViewPort.top,SaveViewPort.right,
              SaveViewPort.bottom,SaveViewPort.clip);
  MouseShow();


  //    By zjh 96.6
  if (GetFontParamter()&&TextCursorCount==1)
  {
    DispFontWindow(2);
    OldPosition=GlobalTextPosition;
  }
}



void CreatFontWindow(int x1,int x2)
{
  int SaveColor;
  struct viewporttype SaveViewPort;

  MouseHidden();
  getviewsettings(&SaveViewPort);
  SaveColor=getcolor();

  setwritemode(COPY_PUT);

  //setcolor(EGA_WHITE);
  //setcolor(EGA_DARKGRAY);
  setcolor(EGA_LIGHTGRAY);      //DarkBlack
  setviewport(0,0,639,200,0);
  bar(x1,50,x2,50+20);

  setcolor(EGA_DARKGRAY);
  line(x1,50,x2,50);
  line(x1,51,x2-1,51);
  line(x1,50,x1,50+20);
  line(x1+1,50,x1+1,50+19);

  setcolor(EGA_WHITE);
  line(x1,50+20,x2,50+20);
  line(x2,50,x2,50+20);

  //DisplayString("�ַ�",x1+3,54,0,15);

  setcolor(SaveColor);
  setviewport(SaveViewPort.left,SaveViewPort.top,SaveViewPort.right,
              SaveViewPort.bottom,SaveViewPort.clip);
  MouseShow();
  CreatStatusWindow();
}



void CreatStatusWindow()
{
  int SaveColor;
  struct viewporttype SaveViewPort;
  int maxx,maxy,use;
  use=0;
  if (use)
  {
  maxx=getmaxx();
  maxy=getmaxy();

  MouseHidden();
  getviewsettings(&SaveViewPort);
  SaveColor=getcolor();

  setwritemode(COPY_PUT);
  setcolor(EGA_DARKGRAY);       //gray
  setviewport(0,0,maxx,maxy,1);
  #define Left_Bottom   28
  #define SPAC  4
  #define WID1  130
  #define WID2  240

  bar(1,maxy-Left_Bottom,maxx,maxy-1);

  setcolor(EGA_DARKGRAY);      //DarkBlack

  bar(5,maxy-Left_Bottom+SPAC,WID1,maxy-SPAC);
  bar(WID1+SPAC,maxy-Left_Bottom+SPAC,WID2+SPAC,maxy-SPAC);
  bar(WID2+SPAC*2,maxy-Left_Bottom+SPAC,maxx-SPAC,maxy-SPAC);

  setcolor(EGA_LIGHTGRAY);

  line(SPAC,maxy-Left_Bottom+SPAC,WID1,maxy-Left_Bottom+SPAC);
  line(SPAC,maxy-Left_Bottom+SPAC+1,WID1-1,maxy-Left_Bottom+SPAC+1);
  line(SPAC,maxy-Left_Bottom+SPAC,SPAC,maxy-SPAC);
  line(SPAC+1,maxy-Left_Bottom+SPAC,SPAC+1,maxy-SPAC-1);

  line(WID1+SPAC,maxy-Left_Bottom+SPAC,WID2+SPAC,maxy-Left_Bottom+SPAC);
  line(WID1+SPAC,maxy-Left_Bottom+SPAC+1,WID2+SPAC-1,maxy-Left_Bottom+SPAC+1);
  line(WID1+SPAC,maxy-Left_Bottom+SPAC,WID1+SPAC,maxy-SPAC);
  line(WID1+SPAC+1,maxy-Left_Bottom+SPAC,WID1+SPAC+1,maxy-SPAC-1);

  line(WID2+SPAC*2,maxy-Left_Bottom+SPAC,maxx-SPAC,maxy-Left_Bottom+SPAC);
  line(WID2+SPAC*2,maxy-Left_Bottom+SPAC+1,maxx-SPAC-1,maxy-Left_Bottom+SPAC+1);
  line(WID2+SPAC*2,maxy-Left_Bottom+SPAC,WID2+SPAC*2,maxy-SPAC);
  line(WID2+SPAC*2+1,maxy-Left_Bottom+SPAC,WID2+SPAC*2+1,maxy-SPAC-1);

  setcolor(EGA_WHITE);
  line(SPAC,maxy-SPAC,WID1,maxy-SPAC);
  line(SPAC+WID1,maxy-SPAC,WID2+SPAC,maxy-SPAC);
  line(SPAC*2+WID2,maxy-SPAC,maxx-SPAC,maxy-SPAC);


  setcolor(SaveColor);
  setviewport(SaveViewPort.left,SaveViewPort.top,SaveViewPort.right,
              SaveViewPort.bottom,SaveViewPort.clip);
  MouseShow();
 }
}

int TextCreatCursor(HWND Window,int Height,int RotateAxisX,int RotateAxisY,
                    int RotateAngle)
{
  TextCursorHeight=Height;
  TextCursorCount=0;
  TextCursorRotateAxisX=RotateAxisX;
  TextCursorRotateAxisY=RotateAxisY;
  TextCursorRotateAngle=RotateAngle;
  return(TimerInsert(CURSORBLINKTIME,Window));
}

void TextCursorOff(void)
{
  if (TextCursorCount)
  {
     TextCursorDisplay();
     TextCursorCount=0;
  }
}

/*-----------
void TextCursorMoveXTo(int MovetoX)
{
  TextCursorOff();
  TextCursorPosX=MovetoX;
}
---------*/
void TextCursorMoveTo(int MovetoX,int MovetoY)
{
//  TextCursorMoveXTo(MovetoX);
  TextCursorOff();
  TextCursorPosX=MovetoX;
  TextCursorPosY=MovetoY;
}

void TextCursorSetHeight(int Height)
{
  TextCursorOff();
  TextCursorHeight=Height;
}

void TextDestroyCursor(int *Cursor)
{
  TextCursorOff();
  TimerDelete(*Cursor);
  *Cursor=-1;
}

void TextCursorSetRotate(int RotateAxisX,int RotateAxisY,int RotateAngle)
{
  TextCursorOff();
  TextCursorRotateAxisX=RotateAxisX;
  TextCursorRotateAxisY=RotateAxisY;
  TextCursorRotateAngle=RotateAngle;
}

void CloseTextCursor(void)
{
  if (CursorBlankSign==1)
     TextCursorOff();
  CursorBlankSign=0;
}

void OpenTextCursor(void)
{
  CursorBlankSign=1;
}

/*------ not used -----
int TextCursorIsOn(void)
{
  return(CursorBlankSign>0);
}
--------------*/
