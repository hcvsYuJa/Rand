//=======宣告函式庫=========================================================================================
#include<iostream>//基本輸出入
#include<cstdlib>//亂數取得
#include<ctime>//時間函數
#include<fstream>//讀檔案
#include<windows.h>//延時 
#define MA3 3 
using namespace std;//使用命名空間std。
//=========宣告副程式=======================================================================================
void Ra_setting(int*);//讀取基礎設定 
int not_likely(void);//亂數取得
void List_one(void);//名單讀取1
void List_two(char LA[][100]);//名單讀取2
void set_mode(char LA[][100],int*);//系統設置介面 
void set_mode_funList(void);//系統設置介面功能清單
void set_mode_YN(void);//系統設置功能指令讀取
void Modify_settings(char LA[][100],int*);//編輯設定檔
//============全域宣告======================================================================================
int NofP=0,X=1,i=0,Leave_i=0;//NofP(Number of people)。X為抽X人。i迴圈用
bool SyIn=false;//是否進入系統模式
//=============主程式=======================================================================================
int main()
{
	List_one();//呼叫副程式List_one，得以取得NofP(要抽的筆數)。
	int Leave[NofP+1]={-1},Nw=0;//Nw亂數抽取狀態。 
	Ra_setting(Leave);//呼叫副程式Ra_setting，得以讀取Basic_setting.txt。
	char LA[NofP][100]={'\0'};//宣告一個叫LA的二維字元陣列，元素量為NofP*100，整個陣列初始值為'\0'。
	List_two(LA);//呼叫副程式List_two並且將二維字元陣列LA傳入，得以將名單資料全部輸入至LA內。 
	if(SyIn==true)set_mode(LA,Leave);
	//===============
	int N=0;//N為最後結果輸出
	srand((int)time(NULL));
	for(;X>0;X--)//X為抽取之筆數，將X輸出一次減一，得以做到輸出至輸入之次數。 
	{
		N=not_likely();//取得亂數。
		Nw=0; 
		for(i=0;i<Leave_i;i++)
		{
			if(Leave[i]==N)
			{
				X+=1;
				Nw=1;
				break;
			}
		}
		if(i==Leave_i)
		{
			Leave[Leave_i]=N;
			Leave_i+=1;
		}
		if(Nw==1)continue;
		cout << LA[N] << endl;//輸出將亂數作為索引值的陣列內容。 
	}
	system("pause");//使用執行檔時，結尾所需。
}
//========================================亂數取得========================================================
int not_likely(void)//亂數取得
{	int n=0;//宣告一個叫n，資料型態為int，初始為0。 
	n=rand()%NofP;//以時間為亂數種子，而後取得亂數再將其取NofP的餘數。 
	return n;//回傳n(亂數計算完之結果)。 
}
//=============================讀取基礎設定檔=============================================================
void Ra_setting(int*L)//讀取基礎設定檔案 
{
	int Rsi=0;//讀檔部分記錄0未進入讀檔。 
	char SI[150]={'\0'};//宣告一個叫SI的字元陣列，元素量為150，整個陣列初始值為'\0'。 
	fstream setting;//以fstream建立檔案輸出、物件setting
	if(setting.is_open()==true)//檔案如果開啟即關檔
		setting.close();//關閉Basic_setting.txt檔，物件setting 
	else
		setting.open("Basic_setting.txt",ios::in);//開啟Basic_setting.txt以讀取的方式(ios::in)打開
	if(!setting)//是否開檔失敗
		cout << "Basic_setting.txt => Error" << endl;//讓使用者知道Basic_setting.txt有問題，此時還不需離開程式因還需判定List.txt是否可以。 

	do
	{setting.getline(SI,150);//從Basic_setting.txt讀取一行至SI這個字元陣列內，後面的150是元素量。 
	if(SI[0]=='#')Rsi+=1;//第一個井字號讀第一部分。 
	} 
	while(SI[0]=='#');//「#」字開頭為註解行，不讀取 
	//====讀取抽取量預設值======。 
	if(SI[0]!='0')
	{	for(i=0;'0'<=SI[i]&&SI[i]<='9'&&i<sizeof(SI)&&Rsi==1;i++)//如果該行開頭讀到字元'1'~'9'就進入迴圈，而後i重複加一判定到SI陣列的最後。 
		{
			if(i==0)X=0;//如果成功進入該迴圈，一開始i=0，所以此時將X=0。 
			X+=(int)SI[i]-48;//將SI陣列，索引i，強制轉型為整數型態再減48即可得到該數值，而後加進X內。 
			if('0'<=SI[i+1]&&SI[i+1]<='9')X*=10;//如果該迴圈目前判定的下一位還是為數字就
			else break;
		}
	}
	else X=0;
	//=========讀取不被抽的筆數====== 
	do
	{setting.getline(SI,150);//從Basic_setting.txt讀取一行至SI這個字元陣列內，後面的150是元素量。 
	if(SI[0]=='#'&&Rsi<=MA3)Rsi+=1;//第一個井字號讀第一部分。 
	} 
	while(SI[0]=='#'&&Rsi<=MA3);//「#」字開頭為註解行，不讀取。 
	for(Leave_i=0;Leave_i<NofP&&Rsi==2;Leave_i++)
	{
		for(i=0;'0'<=SI[i]&&SI[i]<='9'&&i<sizeof(SI);i++)//如果該行開頭讀到字元'1'~'9'就進入迴圈，而後i重複加一判定到SI陣列的最後。 
		{
			if(i==0)
			L[Leave_i]=(int)SI[i]-48;//將SI陣列，索引i，強制轉型為整數型態再減48即可得到該數值，而後加進X內。 
			else
			L[Leave_i]+=(int)SI[i]-48;//將SI陣列，索引i，強制轉型為整數型態再減48即可得到該數值，而後加進X內。
			if('0'<=SI[i+1]&&SI[i+1]<='9')L[Leave_i]*=10;//如果該迴圈目前判定的下一位還是為數字就
			else
			{
				L[Leave_i]-=1;//陣列索引從0開始。 
				break;
			}
		}
		do
		setting.getline(SI,150);//從Basic_setting.txt讀取一行至SI這個字元陣列內，後面的150是元素量。
		while(0<=SI[0]&&SI[0]<=31||SI[0]==127);//確保跳過空行 
		if(SI[0]=='#')
		{
			Leave_i++;
			break;
		}
	}
	char CX[100]={'\0'};
	while(X<=0||X>(NofP-Leave_i))
	{
		cout << "忽略掉的筆數有:" << Leave_i  << "筆" << endl << "因而最多抽:" << NofP-Leave_i << "筆" <<endl << "請輸入一個大於0的數值:";  
		X=0;
		cin >> CX;//如果輸入需抽之人數(X)小於1就再重新輸入。
		for(i=0;i<sizeof(CX);i++)
		{
			if('0'<=CX[i]&&CX[i]<='9')X+=(int)CX[i]-48;
			if('0'<=CX[i+1]&&CX[i+1]<='9')X*=10;
		}
		for(i=0;i<4;i++)//判定是否可進入系統設定介面 
		{
			if(CX[i]=='S'&&i==0&&SyIn==false)SyIn=true;
			else if(CX[i]=='y'&&i==1&&SyIn==true)SyIn=true;
			else if(CX[i]=='I'&&i==2&&SyIn==true)SyIn=true;
			else if(CX[i]=='n'&&i==3&&SyIn==true)SyIn=true;
			else SyIn=false;
		}
		if(SyIn==true)break;
	}
	setting.close();//關閉Basic_setting.txt檔，物件setting 
}
//=================系統模式=============================================================================== 
void set_mode(char LA[][100],int*Leave)//系統設置 
{
	system("cls");//X=1,i=0;
	X=0;
	while(1)
	{
		if(X==1)cout << "指令輸入錯誤" << endl;
		else if(X==-1)
		{
			system("cls");
			for(i=0;i<NofP;i++)
			{
				cout << LA[i] << endl;
			}
			system("pause");system("cls");
		}
		else if(X==-2)
		{
			system("cls");
			for(i=0;i<Leave_i;i++)
			{
				cout << LA[Leave[i]] << endl;
			}
			system("pause");system("cls");
		}
		else if(X==-3)Modify_settings(LA,Leave);
		set_mode_funList();
		set_mode_YN();
		
		
	}
	exit(0); 
}
void set_mode_funList(void)//系統設置功能表
{
	cout << endl <<"歡迎使用系統設置模式" <<endl;
	cout <<endl<< "=======指令=======" << endl;
	cout << "離開程序:0" << endl;
	cout << "印出名單:list" <<endl;
	cout << "印出不被抽到的名單:unlist" << endl; 
	cout << "編輯設定檔:setting" << endl; 
}
void set_mode_YN(void)//系統設置功能指令讀取
{
		char UseSet[100]={0};
		X=0;
		cin >> UseSet;
		if(UseSet[0]=='0')exit(0);
		if(UseSet[0]=='l')
		{
			for(i=1;i<4;i++)//判定指令是否為list
			{
				if(UseSet[i]=='i'&&i==1)X=-1;
				else if(UseSet[i]=='s'&&i==2&&X==-1)X=-1;
				else if(UseSet[i]=='t'&&i==3&&X==-1)X=-1;
				else {X=1;break;}
			}
		}
		else if(UseSet[0]=='u')
		{
			for(i=1;i<4;i++)//判定指令是否為unlist 
			{
				if(UseSet[i]=='n'&&i==1)X=-2;
				else if(UseSet[i]=='l'&&i==2&&X==-2)X=-2;
				else if(UseSet[i]=='i'&&i==3&&X==-2)X=-2;
				else if(UseSet[i]=='s'&&i==2&&X==-2)X=-2;
				else if(UseSet[i]=='t'&&i==3&&X==-2)X=-2;
				else {X=1;break;}
			}
		}
		else if(UseSet[0]=='s')
		{
			for(i=1;i<7;i++)//判定指令是否為unlist 
			{
				if(UseSet[i]=='e'&&i==1)X=-3;
				else if(UseSet[i]=='t'&&i==2&&X==-3)X=-3;
				else if(UseSet[i]=='t'&&i==3&&X==-3)X=-3;
				else if(UseSet[i]=='i'&&i==4&&X==-3)X=-3;
				else if(UseSet[i]=='n'&&i==5&&X==-3)X=-3;
				else if(UseSet[i]=='g'&&i==6&&X==-3)X=-3;
				else {X=1;break;}
			}
		}
		else X=1;
}
void Modify_settings(char LA[][100],int*Leave)
{
	system("cls");
	cout << "此指令還未製作完成" <<endl;system("pause");system("cls");return; 
	cout << "=====編輯設定檔=====" << endl;
	fstream setting;//以fstream建立檔案輸出、物件setting
	if(setting.is_open()==true)//檔案如果開啟即關檔
		setting.close();//關閉Basic_setting.txt檔，物件setting 
	else
		setting.open("Basic_setting.txt",ios::out);//開啟Basic_setting.txt以寫入的方式(ios::out)打開
	if(!setting)//是否開檔失敗
		cout << "Basic_setting.txt => Error" << endl;//讓使用者知道Basic_setting.txt有問題。
		setting.close();//關閉Basic_setting.txt檔，物件setting  
	
}
//=========================名單讀取========================================================================
void List_one(void)//名單檔案讀取1(確認抽獎筆數)
{
	fstream List;//以fstream建立檔案輸出、物件List
	if(List.is_open()==true)//檔案如果開啟即關檔
		List.close();//關閉List.txt檔 
	else
		List.open("List.txt",ios::in);//開啟List.txt以讀取的方式(ios::in)打開
	if(!List)//是否開檔失敗
	{
		cout << "List.txt => Error" << endl;//讓使用者知道List.txt有問題。 
		system("pause");//使用執行檔時，結尾所需 。 
		exit(0);//讓使用者看完哪裡錯誤後離開程式。 
	}
	char T[100]={'\0'};//宣告一個叫T的字元陣列，元素量為100，整個陣列初始值為'\0'。 
	while(!List.eof())//取得需抽的個數，eof()是否為檔案結尾 
	{
		List.getline(T,100);//從List.txt讀取一行至T這個字元陣列內，後面的100是元素量。 
		if(0<=T[0]&&T[0]<=31||T[0]==127)NofP-=1;//如果輸入的第一個字為不可顯示之字元，將NofP減一。 
		NofP++;//讀過一行後將NofP加一。 
	} 
	List.close();//關閉List.txt檔
}
void List_two(char LA[][100])//名單檔案讀取2(將資料讀取進陣列)
{
	fstream List;//以fstream建立檔案輸出、物件List
	if(List.is_open()==true)//檔案如果開啟即關檔
		List.close();//關閉List.txt檔
	else
		List.open("List.txt",ios::in);//開啟List.txt以讀取的方式(ios::in)打開
	if(!List)//是否開檔失敗 
	{
		cout << "List.txt => Error" << endl;//讓使用者知道List.txt有問題。 
		system("pause");//使用執行檔時，結尾所需 。 
		exit(0);//讓使用者看完哪裡錯誤後離開程式。
	}
	for(i=0;i<NofP;i++)//將名單資料讀入陣列 
	{
		List.getline(LA[i],100);//從List.txt讀取一行至LA[i]這個字元陣列內，後面的100是元素量。(LA是二維陣列)。
		if(0<=LA[i][0]&&LA[i][0]<=31||LA[i][0]==127)i-=1;//如果該行為多餘行數，將i減一，以便換一行讀入可用行數。
	}
	List.close();//關閉List.txt檔
}
//======================================END=================================================================
