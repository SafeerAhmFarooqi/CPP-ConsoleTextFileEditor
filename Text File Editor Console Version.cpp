#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<unistd.h>
using namespace std;
class edittextfileapp
{
	private:
			string filelocationname;
			int filestate;
			int slotnumber;
	public:
			edittextfileapp()
			{
				filelocationname='\0';
				filestate=0;
				slotnumber=0;
				}	
			static void mainpage();
			static void historyofopenedfilespage();
			static void currentopenedfiles();
			static void openfilepage();
			static void edittextfilepage(edittextfileapp &);
			static void createobject(char []);
			static int noofopenedfiles();
			static void writetohistory(const edittextfileapp &);
			static int checkfile(edittextfileapp &);
			static int checkfilereturn(edittextfileapp &);
			static void stringtochararray(char [],const string &);
			static void resetslot(edittextfileapp &);
			static void searchandreplacetextpage(edittextfileapp &,bool);
			static int searchtext(char *,edittextfileapp &,bool);
			static bool comparestringcasesensitive(const char *,const char *);
			static bool comparestringnoncasesensitive(const char *,const char *);
			static bool comparestringnoncasesensitive(const string,const char *);
			static bool checkstring(char *);
			static void replacetextouter(char *,edittextfileapp &,bool);
			static void printtext(edittextfileapp &);
			static void newblankfile();
			static int newblankfilereturnslotnumber();
			static bool filenamecheck(char *);
			static void addtext(edittextfileapp &);
			static void deletealltext(edittextfileapp &);
			static void copyfile();
			static int returnfilenumber(int [][2],int);
}e[1000];
long stringsize(const string &obj)
{
	long i=0;
	while(obj[i]!='\0')
	{
		i++;
	}
	return (i);
}
int edittextfileapp::returnfilenumber(int fileaccess[][2],int srno)
{
	int i=0;
	for (i=0;i<1000;i++)
	{
		if(fileaccess[i][0]==srno)
		{
			return (i);
		}
	}
	return(-1);
} 
void edittextfileapp::stringtochararray(char destinationarray[],const string &sourceobject)
{
	int i=0;
	for (i=0;i<stringsize(sourceobject);i++)
	{
		destinationarray[i]=sourceobject[i];
	}
	destinationarray[stringsize(sourceobject)]='\0';
}
bool edittextfileapp::checkstring(char inputstring[])
{
	int nonspacecharacter=0,i=0;
	for (i=0;i<strlen(inputstring);i++)
	{
		if(inputstring[i]!=char(32))
		{
			nonspacecharacter=i;
			break;	
		}
	}
	if(nonspacecharacter>0)
	{
		return (false);
	}
	if(inputstring[(strlen(inputstring))-1]==char(32))
	{
		return (false);
	}
	return(true);
}
bool edittextfileapp::filenamecheck(char inputfilename[])
{
	int i=0;
	for (i=0;i<strlen(inputfilename);i++)
	{
		if(!isalpha(inputfilename[i])&&!isdigit(inputfilename[i]))
		{
			return (false);
		}
	}
	return(true);
}
void edittextfileapp::historyofopenedfilespage()
{
	fstream historyfile;
	char read='\0';
	int lengthoffile=0,i=0,a=0,brackets=0;
	historyfile.open("edittextfileapp.history",ios::in|ios::out);
	if(!historyfile)
	{
		cout<<"\nCurrently There is no History to Show.";
		edittextfileapp::mainpage();
	}
	if(historyfile)
	{
		cout<<"\n-----------History of Opened Files-----------";
		cout<<"\n\tFile Name and Location With Date And Time.";
		historyfile.seekg(0,ios::end);
		lengthoffile=historyfile.tellg();
		historyfile.seekg(0,ios::beg);
		for (i=0;i<lengthoffile;i++)
		{
			historyfile.seekg(i,ios::beg);
			historyfile.get(read);
			if(read=='\n')
			{
				i++;
			}
			if(read=='(')
			{
			read='\0';
			cout<<"\n";
				for(a=i+1;read!='&';a++)
				{
					historyfile.seekg(a,ios::beg);
					historyfile.get(read);
					if(read=='&')
					{
						break;
							}	
					cout<<read;	
				}
			}
		}	
	}
	edittextfileapp::mainpage();
}
void edittextfileapp::writetohistory(const edittextfileapp &obj)
{
	int brackets=0,i=0,exit=0,srno=0;
	char read='\0',srnochar[1000];
	for(i=0;i<1000;i++)
	{
		srnochar[i]='\0';
	}
	time_t currenttime;
	time(&currenttime);
	tm *telltime;
	telltime=localtime(&currenttime);
	fstream existingfile;
	existingfile.open("edittextfileapp.history",ios::in|ios::out);
	if(!existingfile)
	{
		fstream newhistoryfile;
		newhistoryfile.open("edittextfileapp.history",ios::in|ios::out|ios::trunc);
		newhistoryfile.seekg(0,ios::beg);
		newhistoryfile<<"(1)"<<" "<<obj.filelocationname<<"["<<telltime->tm_mday<<"-"<<telltime->tm_mon+1<<"-"<<telltime->tm_year+1900<<","<<telltime->tm_hour<<":"<<telltime->tm_min<<":"<<telltime->tm_sec<<"]"<<"&";
		newhistoryfile.close();
	}
	if(existingfile)
	{
		i=0;
		existingfile.seekg(-1,ios::end);
		while(1>0)
		{
					existingfile.get(read);
					if(read=='(')
					{
						while(1>0)
						{
							existingfile.get(read);
							if(read==')')
							{
								exit=1;
								break;
							}
							srnochar[i]=read;
							i++;
						}
					}
	    if(exit==1)
	    {
	    	break;
		}
		existingfile.seekg(-2,ios::cur);
		}	
	srno=atoi(srnochar);
	srno++;
	time(&currenttime);
	telltime=localtime(&currenttime);
	existingfile.seekg(0,ios::end);
	existingfile<<"\n"<<"("<<srno<<") "<<obj.filelocationname<<"["<<telltime->tm_mday<<"-"<<telltime->tm_mon+1<<"-"<<telltime->tm_year+1900<<","<<telltime->tm_hour<<":"<<telltime->tm_min<<":"<<telltime->tm_sec<<"]"<<"&";
	existingfile.close();
	}
}
void edittextfileapp::currentopenedfiles()
{
	int i=0,a=0,srno=1,fileaccess[1000][2],correction=0,filenumber=0;
	char choice[10000];
	while(1>0)
	{	
	correction=0;
	srno=1;
	cout<<"\nCurrent Opened Files Menu";
	cout<<"\nFollowing Are the Currently Opened Files.";
	for(i=0;i<1000;i++)
	{
		for (a=0;a<2;a++)
		{
			fileaccess[i][a]=0;
		}
	}
	for (i=0;i<edittextfileapp::noofopenedfiles();i++)
	{
		if(e[i].filestate==1)
		{
			cout<<"\n"<<srno<<") "<<e[i].filelocationname;
			fileaccess[srno-1][0]=srno;
			fileaccess[srno-1][1]=i;
			srno++;
		}
	}
	for(i=0;i<10000;i++)
	{
		choice[i]='\0';
	}
	cout<<"\nWhich of the above file do you want to Edit?";
	cout<<"\nEnter its serial number. Or";
	cout<<"\nEnter --1 To return to main menu";
	cout<<"\nSerial Number :";
	cin.getline(choice,1000);
	if(choice[0]=='-'&&choice[1]=='-'&&choice[2]=='1')
	{
		edittextfileapp::mainpage();	
		}	
	for(i=0;i<strlen(choice);i++)
	{
		if(!isdigit(choice[i]))
		{
			cout<<"\nPlease Enter Correct Serial Number.";
			correction=1;
			}	
	}
	if(correction==1)
	{
		continue;
	}
	filenumber=atoi(choice);
	if(filenumber<1||filenumber>=srno)
	{
		cout<<"\nYou Have Entered an Invalid Serial Number.";
		continue;
	}
	break;
	}
	edittextfileapp::edittextfilepage(e[edittextfileapp::returnfilenumber(fileaccess,filenumber)]);
}
void edittextfileapp::copyfile()
{
	cout<<"\n-----List of currently opened Files-----";
	char choice[1000],openfiletocopyin[10000],sourcefilechar[100000],destfilechar[100000],filename[10000],read[100000];
	fstream sourcefile,destinationfile;
	int i=0,a=0,srno=1,fileaccess[1000][2],filenumber=0,filenumbertocopyto=0,correction=0,sourcefilelength=0,remainingfilelength=0,slotnumber=0;
	for(i=0;i<1000;i++)
	{
		for (a=0;a<2;a++)
		{
			fileaccess[i][a]=0;
		}
	}
	for (i=0;i<edittextfileapp::noofopenedfiles();i++)
	{
		if(e[i].filestate==1)
		{
			cout<<"\n"<<srno<<") "<<e[i].filelocationname;
			fileaccess[srno-1][0]=srno;
			fileaccess[srno-1][1]=i;
			srno++;
		}
	}
	while(1>0)
	{
	for(i=0;i<1000;i++)
	{
		choice[i]='\0';
	}
	cout<<"\nPress\n\t\t1) Copy One of the Current Opened Files.\n\t\t2) Copy some other file.\n\t\t3) Main Menu.";
	cout<<"\nChoice :";
	cin.getline(choice,1000);
	if(choice[0]!='1'&&choice[0]!='2'&&choice[0]!='3')
	{
		cout<<"\nPlease Enter correct choice.";
		continue;
		}	
		break;
	}
	if(choice[0]=='1')
	{
	if(edittextfileapp::noofopenedfiles()==0)
	{
		cout<<"\nSorry There are no Currently opened files.";
		edittextfileapp::copyfile();	
	}
	while(1>0)
	{	
	correction=0;
	srno=1;
	for (i=0;i<edittextfileapp::noofopenedfiles();i++)
	{
		if(e[i].filestate==1)
		{
			cout<<"\n"<<srno<<") "<<e[i].filelocationname;
			fileaccess[srno-1][0]=srno;
			fileaccess[srno-1][1]=i;
			srno++;
		}
	}
	for(i=0;i<1000;i++)
	{
		choice[i]='\0';
	}
	cout<<"\nWhich of the above file do you want to copy?";
	cout<<"\nEnter its serial number.";
	cout<<"\nSerial Number :";
	cin.getline(choice,1000);	
	for(i=0;i<strlen(choice);i++)
	{
		if(!isdigit(choice[i]))
		{
			cout<<"\nPlease Enter Correct Serial Number.";
			correction=1;
			}	
	}
	if(correction==1)
	{
		continue;
	}
	filenumber=atoi(choice);
	if(filenumber<1||filenumber>=srno)
	{
		cout<<"\nYou Have Entered an Invalid Serial Number.";
		continue;
	}
	break;
	}
	while(1>0)
	{
		while(1>0)
	{
		for(i=0;i<1000;i++)
	{
		choice[i]='\0';
	}
	cout<<"\nPress\n\t\t1) Copy file to Current Opened Files.\n\t\t2) Open Another Existing File To Copy In.\n\t\t3) Open New File to Copy In.\n\t\t4) Return to Main Page.";
	cout<<"\nChoice : ";
	cin.getline(choice,1000);
	if(choice[0]!='1'&&choice[0]!='2'&&choice[0]!='3'&&choice[0]!='4')
	{
		cout<<"\nPlease Enter Correct Choice.";
		continue;	
	}
	break;
	}
	if(choice[0]=='1')
	{
	if(edittextfileapp::noofopenedfiles()==0)
	{
		cout<<"\nSorry There are no Currently opened files.";
		continue;	
	}
	while(1>0)
	{
	correction=0;
	srno=1;
	for (i=0;i<edittextfileapp::noofopenedfiles();i++)
	{
		if(e[i].filestate==1)
		{
			cout<<"\n"<<srno<<") "<<e[i].filelocationname;
			fileaccess[srno-1][0]=srno;
			fileaccess[srno-1][1]=i;
			srno++;
		}
	}
	for(i=0;i<1000;i++)
	{
		choice[i]='\0';
	}
	cout<<"\nWhich of the above file do you want to copy to?";
	cout<<"\nEnter its serial number.";
	cout<<"\nSerial Number :";
	cin.getline(choice,1000);	
	for(i=0;i<strlen(choice);i++)
	{
		if(!isdigit(choice[i]))
		{
			cout<<"\nPlease Enter Correct Serial Number.";
			correction=1;
			}	
	}
	if(correction==1)
	{
		continue;
	}
	filenumbertocopyto=atoi(choice);
	if(filenumbertocopyto<1||filenumbertocopyto>=srno)
	{
		cout<<"\nYou Have Entered an Invalid Serial Number.";
		continue;
	}
	break;
	}
		sourcefilelength=0;
		remainingfilelength=0;
		for(i=0;i<100000;i++)
		{
			sourcefilechar[i]='\0';
			destfilechar[i]='\0';
		}
		edittextfileapp::stringtochararray(sourcefilechar,e[fileaccess[edittextfileapp::returnfilenumber(fileaccess,filenumber)][1]].filelocationname);
		edittextfileapp::stringtochararray(destfilechar,e[fileaccess[edittextfileapp::returnfilenumber(fileaccess,filenumbertocopyto)][1]].filelocationname);
		sourcefile.open(sourcefilechar,ios::in|ios::out);
		destinationfile.open(destfilechar,ios::in|ios::out);
		sourcefile.seekg(0,ios::end);
		sourcefilelength=sourcefile.tellg();
		sourcefile.seekg(0,ios::beg);
		destinationfile.seekg(0,ios::end);
		while(!sourcefile.eof())
		{
			remainingfilelength=sourcefilelength-sourcefile.tellg();
			for(i=0;i<100000;i++)
			{
				read[i]='\0';
			}
			if(remainingfilelength<100000-5)
			{
				sourcefile.read(read,remainingfilelength);
				destinationfile<<read;
				break;
			}
			if(remainingfilelength>100000-5)
			{
				sourcefile.read(read,100000-5);
				destinationfile<<read;
			}
		}
		sourcefile.close();
		destinationfile.close();
		edittextfileapp::mainpage();
	}
	if(choice[0]=='2')
	{
		for(i=0;i<10000;i++)
		{
			filename[i]='\0';
		}
		cout<<"\nEnter File Name with Location And Extension.";
		cout<<"\nFile Name :";
		cin.getline(filename,10000);
		destinationfile.open(filename,ios::in|ios::out);
		if(!destinationfile)
		{
			cout<<"\nEither File Name or Location is incorrect or You do not have administrative Authority to open the file.";
			edittextfileapp::copyfile();	
		}
		for(i=0;i<100000;i++)
		{
			sourcefilechar[i]='\0';
		}
		edittextfileapp::stringtochararray(sourcefilechar,e[fileaccess[edittextfileapp::returnfilenumber(fileaccess,filenumber)][1]].filelocationname);
		sourcefile.open(sourcefilechar,ios::in|ios::out);
		sourcefile.seekg(0,ios::end);
		sourcefilelength=sourcefile.tellg();
		sourcefile.seekg(0,ios::beg);
		destinationfile.seekg(0,ios::end);
		while(!sourcefile.eof())
		{
			remainingfilelength=sourcefilelength-sourcefile.tellg();
			for(i=0;i<100000;i++)
			{
				read[i]='\0';
			}
			if(remainingfilelength<100000-5)
			{
				sourcefile.read(read,remainingfilelength);
				destinationfile<<read;
				break;
			}
			if(remainingfilelength>100000-5)
			{
				sourcefile.read(read,100000-5);
				destinationfile<<read;
			}
		}
		sourcefile.close();
		destinationfile.close();
		edittextfileapp::mainpage();
	}
	if(choice[0]=='3')
	{
		slotnumber=edittextfileapp::newblankfilereturnslotnumber();
		sourcefilelength=0;
		remainingfilelength=0;
		for(i=0;i<100000;i++)
		{
			sourcefilechar[i]='\0';
			destfilechar[i]='\0';
		}
		edittextfileapp::stringtochararray(sourcefilechar,e[fileaccess[edittextfileapp::returnfilenumber(fileaccess,filenumber)][1]].filelocationname);
		edittextfileapp::stringtochararray(destfilechar,e[slotnumber].filelocationname);
		sourcefile.open(sourcefilechar,ios::in|ios::out);
		destinationfile.open(destfilechar,ios::in|ios::out);
		sourcefile.seekg(0,ios::end);
		sourcefilelength=sourcefile.tellg();
		sourcefile.seekg(0,ios::beg);
		destinationfile.seekg(0,ios::end);
		while(!sourcefile.eof())
		{
			remainingfilelength=sourcefilelength-sourcefile.tellg();
			for(i=0;i<100000;i++)
			{
				read[i]='\0';
			}
			if(remainingfilelength<100000-5)
			{
				sourcefile.read(read,remainingfilelength);
				destinationfile<<read;
				break;
			}
			if(remainingfilelength>100000-5)
			{
				sourcefile.read(read,100000-5);
				destinationfile<<read;
			}
		}
		sourcefile.close();
		destinationfile.close();
		edittextfileapp::mainpage();
	}
	if(choice[0]=='4')
	{
		edittextfileapp::mainpage();
	}
	break;	
	}
	
	}
	if(choice[0]=='2')
	{
		for(i=0;i<100000;i++)
		{
			sourcefilechar[i]='\0';
		}
		cout<<"\nEnter File Name with Location And Extension.";
		cout<<"\nFile Name :";
		cin.getline(sourcefilechar,100000);
		sourcefile.open(sourcefilechar,ios::in|ios::out);
		if(!sourcefile)
		{
			cout<<"\nEither File Name or Location is incorrect or You do not have administrative Authority to open the file.";
			edittextfileapp::copyfile();	
		}
		while(1>0)
		{
			while(1>0)
		{
		for(i=0;i<1000;i++)
		{
		choice[i]='\0';
		}
		cout<<"\nPress\n\t\t1) Copy file to Current Opened Files.\n\t\t2) Open Another Existing File To Copy In.\n\t\t3) Open New File to Copy In.\n\t\t4) Return to Main Page.";
		cout<<"\nChoice : ";
		cin.getline(choice,1000);
		if(choice[0]!='1'&&choice[0]!='2'&&choice[0]!='3'&&choice[0]!='4')
		{
		cout<<"\nPlease Enter Correct Choice.";
		continue;	
		}
		break;
		}
		if(choice[0]=='1')
		{
		if(edittextfileapp::noofopenedfiles()==0)
		{	
		cout<<"\nSorry There are no Currently opened files.";
		continue;	
		}
		while(1>0)
		{
		correction=0;
		srno=1;
		for (i=0;i<edittextfileapp::noofopenedfiles();i++)
		{
		if(e[i].filestate==1)
		{
			cout<<"\n"<<srno<<") "<<e[i].filelocationname;
			fileaccess[srno-1][0]=srno;
			fileaccess[srno-1][1]=i;
			srno++;
		}
		}
		for(i=0;i<1000;i++)
		{
		choice[i]='\0';
		}
		cout<<"\nWhich of the above file do you want to copy to?";
		cout<<"\nEnter its serial number.";
		cout<<"\nSerial Number :";
		cin.getline(choice,1000);	
		for(i=0;i<strlen(choice);i++)
		{
		if(!isdigit(choice[i]))
		{
			cout<<"\nPlease Enter Correct Serial Number.";
			correction=1;
			}	
		}
		if(correction==1)
		{
		continue;
		}
		filenumbertocopyto=atoi(choice);
		if(filenumbertocopyto<1||filenumbertocopyto>=srno)
		{
		cout<<"\nYou Have Entered an Invalid Serial Number.";
		continue;
		}
		break;
		}
		sourcefilelength=0;
		remainingfilelength=0;
		for(i=0;i<100000;i++)
		{
			destfilechar[i]='\0';
		}
		edittextfileapp::stringtochararray(destfilechar,e[fileaccess[edittextfileapp::returnfilenumber(fileaccess,filenumbertocopyto)][1]].filelocationname);
		destinationfile.open(destfilechar,ios::in|ios::out);
		sourcefile.seekg(0,ios::end);
		sourcefilelength=sourcefile.tellg();
		sourcefile.seekg(0,ios::beg);
		destinationfile.seekg(0,ios::end);
		while(!sourcefile.eof())
		{
			remainingfilelength=sourcefilelength-sourcefile.tellg();
			for(i=0;i<100000;i++)
			{
				read[i]='\0';
			}
			if(remainingfilelength<100000-5)
			{
				sourcefile.read(read,remainingfilelength);
				destinationfile<<read;
				break;
			}
			if(remainingfilelength>100000-5)
			{
				sourcefile.read(read,100000-5);
				destinationfile<<read;
			}
		}
		sourcefile.close();
		destinationfile.close();
		edittextfileapp::mainpage();
		}
		if(choice[0]=='2')
		{
		for(i=0;i<10000;i++)
		{
			filename[i]='\0';
		}
		cout<<"\nEnter File Name with Location And Extension.";
		cout<<"\nFile Name :";
		cin.getline(filename,10000);
		destinationfile.open(filename,ios::in|ios::out);
		if(!destinationfile)
		{
			cout<<"\nEither File Name or Location is incorrect or You do not have administrative Authority to open the file.";
			edittextfileapp::copyfile();	
		}
		sourcefile.seekg(0,ios::end);
		sourcefilelength=sourcefile.tellg();
		sourcefile.seekg(0,ios::beg);
		destinationfile.seekg(0,ios::end);
		while(!sourcefile.eof())
		{
			remainingfilelength=sourcefilelength-sourcefile.tellg();
			for(i=0;i<100000;i++)
			{
				read[i]='\0';
			}
			if(remainingfilelength<100000-5)
			{
				sourcefile.read(read,remainingfilelength);
				destinationfile<<read;
				break;
			}
			if(remainingfilelength>100000-5)
			{
				sourcefile.read(read,100000-5);
				destinationfile<<read;
			}
		}
		sourcefile.close();
		destinationfile.close();
		edittextfileapp::mainpage();
	}
	if(choice[0]=='3')
	{
		slotnumber=edittextfileapp::newblankfilereturnslotnumber();
		sourcefilelength=0;
		remainingfilelength=0;
		for(i=0;i<100000;i++)
		{
			destfilechar[i]='\0';
		}
		edittextfileapp::stringtochararray(destfilechar,e[slotnumber].filelocationname);
		destinationfile.open(destfilechar,ios::in|ios::out);
		sourcefile.seekg(0,ios::end);
		sourcefilelength=sourcefile.tellg();
		sourcefile.seekg(0,ios::beg);
		destinationfile.seekg(0,ios::end);
		while(!sourcefile.eof())
		{
			remainingfilelength=sourcefilelength-sourcefile.tellg();
			for(i=0;i<100000;i++)
			{
				read[i]='\0';
			}
			if(remainingfilelength<100000-5)
			{
				sourcefile.read(read,remainingfilelength);
				destinationfile<<read;
				break;
			}
			if(remainingfilelength>100000-5)
			{
				sourcefile.read(read,100000-5);
				destinationfile<<read;
			}
		}
		sourcefile.close();
		destinationfile.close();
		edittextfileapp::mainpage();
	}
	if(choice[0]=='4')
	{
		edittextfileapp::mainpage();
	}
	break;
	}	
	}
	if(choice[0]=='3')
	{
		edittextfileapp::mainpage();
	}
}
void edittextfileapp::deletealltext(edittextfileapp &obj)
{
	edittextfileapp::checkfile(obj);
	char choice[1000],filename[stringsize(obj.filelocationname)+1];
	fstream currentfile;
	edittextfileapp::stringtochararray(filename,obj.filelocationname);
	int i=0;
	for (i=0;i<1000;i++)
	{
		choice[i]='\0';
	}
	while(1>0)
	{
		edittextfileapp::checkfile(obj);
		for (i=0;i<1000;i++)
		{
		choice[i]='\0';
		}
		cout<<"\nAre you sure you want to delete all contents of this file.";
		cout<<"\nPress 'y' for Yes or 'n' for No.\n";
		cin.getline(choice,1000);
		if(choice[0]!='y'&&choice[0]!='n')
		{
			cout<<"\nPlease enter correct choice.";
			continue;
			}
		if(choice[0]=='y')
		{
			currentfile.open(filename,ios::in|ios::out|ios::trunc);
			currentfile.close();
			currentfile.open(filename,ios::in|ios::out);
			currentfile.seekg(0,ios::beg);
			currentfile.close();
			edittextfileapp::edittextfilepage(obj);			
		}	
		if(choice[0]=='n')
		{
			edittextfileapp::edittextfilepage(obj);			
		}
	}
}
void edittextfileapp::addtext(edittextfileapp &obj)
{
	edittextfileapp::checkfile(obj);
	fstream currentfile;
	int i=0,a=0,stringlength=0;
	char inputstring[100000],filename[stringsize(obj.filelocationname)+1];
	edittextfileapp::stringtochararray(filename,obj.filelocationname);
	currentfile.open(filename,ios::in|ios::out);
	currentfile.seekg(0,ios::end);
	cout<<"\nCurrent file name and location : "<<obj.filelocationname;
	while(1>0)
	{
		if(edittextfileapp::checkfilereturn(obj)==0)
		{
			cout<<"\nError Working with this File.";
			cout<<"\nThe File Has been removed,renamed or security settings have been modified.";
			cout<<"\nClosing file and returning to main menu.";
			edittextfileapp::resetslot(obj);
			edittextfileapp::mainpage();
		}
		for (i=0;i<100000;i++)
		{
		inputstring[i]='\0';
		}
		currentfile.seekg(0,ios::end);
		cout<<"\n--1 at the begining of the text to Return to Main Menu";
		cout<<"\n--2 at the begining of the text to Return to Edit Menu";
		cout<<"\nWrite '+n' anywhere in the text to put next line in the text.";
		cout<<"\nEnter Text >";
		cin.getline(inputstring,100000);
		if(inputstring[0]=='-'&&inputstring[1]=='-'&&inputstring[2]=='1')
		{
			currentfile.close();
			edittextfileapp::mainpage();
			}	
		if(inputstring[0]=='-'&&inputstring[1]=='-'&&inputstring[2]=='2')
		{
			currentfile.close();
			edittextfileapp::edittextfilepage(obj);
			}
		stringlength=strlen(inputstring);
		for (i=0;i<stringlength;i++)
		{
			if(inputstring[i]=='+')
			{
				if(i+1==stringlength)
				{
					break;
				}
				if(inputstring[i+1]=='n')
				{
					inputstring[i]='\n';
					if(i+2==stringlength)
					{
						inputstring[i+1]='\0';
						break;
					}
					for (a=i+1;a<stringlength;a++)
					{
						inputstring[a]=inputstring[a+1];
					}
					inputstring[a]='\0';
					stringlength=strlen(inputstring);
				}
			}
		}
		currentfile<<inputstring;
	}
}
void edittextfileapp::newblankfile()
{
	int i=0,emptyslotstate=0;
	char newfilename[10000],currentworkingdirectory[10000],choice[1000],savefilelocation[10000];
	for (i=0;i<10000;i++)
	{
		newfilename[i]='\0';
		currentworkingdirectory[i]='\0';
		savefilelocation[i]='\0';
	}
	cout<<"\n<--------New Blank File-------->";
	while(1>0)
	{
	for (i=0;i<10000;i++)
	{
		newfilename[i]='\0';
	}
	cout<<"\nSpaces are not allowed.Only Alphabets and Numbers Are Allowed";
	cout<<"\nEnter --1 to return to main menu.";
	cout<<"\nEnter File Name :";
	cin.getline(newfilename,10000);
	if(newfilename[0]=='-'&&newfilename[1]=='-'&&newfilename[2]=='1')
	{
		edittextfileapp::mainpage();
	}
	if(newfilename[0]=='\0')
	{
		cout<<"\nPlease Enter the name of File or --1 to return too main menu.";
		continue;
	}
	if(!edittextfileapp::filenamecheck(newfilename))
	{
		cout<<"\nYou have Entered an invalid file name.";
		continue;
	}
	break;	
	}
	while(1>0)
	{
	cout<<"\nCurrent Location : "<<getcwd(currentworkingdirectory,10000);
	cout<<"\n\t\t1) Save to Current Location.\n\t\t2) Save to new Location\n\nChoice :";
	for (i=0;i<1000;i++)
	{
		choice[i]='\0';
	}
	cin.getline(choice,1000);
	if(choice[0]!='1'&&choice[0]!='2')
	{
		cout<<"\nPleae Enter Correct choice.";
		continue;
	}
	break;
	}
	if(choice[0]=='1')
	{
		strcpy(savefilelocation,currentworkingdirectory);
		if(savefilelocation[strlen(savefilelocation)-1]=='\\')
		{
			strcat(savefilelocation,newfilename);
			strcat(savefilelocation,".txt");
			ifstream checkfile;
			checkfile.open(savefilelocation);
			if(checkfile)
			{
				cout<<"\nA Text file with this name,in this location already exist.";
				cout<<"\nTry a different name or location.";
				edittextfileapp::newblankfile();
			}
			fstream newfile;
			newfile.open(savefilelocation,ios::in|ios::out|ios::trunc);
			newfile.seekg(0,ios::beg);
			newfile.close();
			for (i=0;i<1000;i++)
			{
				if(e[i].filestate==0)
				{
					e[i].filelocationname=savefilelocation;
					e[i].filestate=1;
					e[i].slotnumber=i;
					edittextfileapp::writetohistory(e[i]);
					edittextfileapp::edittextfilepage(e[i]);
				}
				emptyslotstate++;
			}
			if(emptyslotstate==1000)
			{
				cout<<"\nCurrent Limit of Opening Files has been reached.";
				cout<<"\nTo open further files please close some of the files in 'See Current Opened Files' Option Listed in the main menu.";
				cout<<"\nReturning to main menu.";
				edittextfileapp::mainpage();				
			}
		}	
		if(savefilelocation[strlen(savefilelocation)-1]!='\\')
		{
			strcat(savefilelocation,"\\");
			strcat(savefilelocation,newfilename);
			strcat(savefilelocation,".txt");
			ifstream checkfile;
			checkfile.open(savefilelocation);
			if(checkfile)
			{
				cout<<"\nA Text file with this name,in this location already exist.";
				cout<<"\nTry a different name or location.";
				edittextfileapp::newblankfile();
			}
			fstream newfile;
			newfile.open(savefilelocation,ios::in|ios::out|ios::trunc);
			newfile.seekg(0,ios::beg);
			newfile.close();
			for (i=0;i<1000;i++)
			{
				if(e[i].filestate==0)
				{
					e[i].filelocationname=savefilelocation;
					e[i].filestate=1;
					e[i].slotnumber=i;
					edittextfileapp::writetohistory(e[i]);
					edittextfileapp::edittextfilepage(e[i]);
				}
				emptyslotstate++;
			}
			if(emptyslotstate==1000)
			{
				cout<<"\nCurrent Limit of Opening Files has been reached.";
				cout<<"\nTo open further files please close some of the files in 'See Current Opened Files' Option Listed in the main menu.";
				cout<<"\nReturning to main menu.";
				edittextfileapp::mainpage();				
			}
		}
	}
	if(choice[0]=='2')
	{
		cout<<"\nEnter Location : ";
		cin.getline(savefilelocation,10000);
		if(savefilelocation[strlen(savefilelocation)-1]!='\\')
		{
			strcat(savefilelocation,"\\");
		}
		strcat(savefilelocation,newfilename);
		strcat(savefilelocation,".txt");
		ifstream checkfile;
		checkfile.open(savefilelocation);
		if(checkfile)
		{
			cout<<"\nA Text file with this name,in this location already exist.";
			cout<<"\nTry a different name or location.";
			edittextfileapp::newblankfile();
		}
		fstream newfile;
		newfile.open(savefilelocation,ios::in|ios::out|ios::trunc);
		if(!newfile)
		{
			cout<<"\nError Creating new file.Possibly The disk does not have enough space\nor This App Does not Have Administrative Authority in this Location.";
			cout<<"\nRun this program As an administrator to avoid this error.";
			edittextfileapp::newblankfile();
		}
		newfile.seekg(0,ios::beg);
		newfile.close();
		for (i=0;i<1000;i++)
			{
			if(e[i].filestate==0)
			{
				e[i].filelocationname=savefilelocation;
				e[i].filestate=1;
				e[i].slotnumber=i;
				edittextfileapp::writetohistory(e[i]);
				edittextfileapp::edittextfilepage(e[i]);
			}
				emptyslotstate++;
			}
			if(emptyslotstate==1000)
			{
				cout<<"\nCurrent Limit of Opening Files has been reached.";
				cout<<"\nTo open further files please close some of the files in 'See Current Opened Files' Option Listed in the main menu.";
				cout<<"\nReturning to main menu.";
				edittextfileapp::mainpage();				
			}
	}
}
int edittextfileapp::newblankfilereturnslotnumber()
{
	while(1>0)
	{
	int i=0,emptyslotstate=0;
	char newfilename[10000],currentworkingdirectory[10000],choice[1000],savefilelocation[10000];
	for (i=0;i<10000;i++)
	{
		newfilename[i]='\0';
		currentworkingdirectory[i]='\0';
		savefilelocation[i]='\0';
	}
	cout<<"\n<--------New Blank File-------->";
	while(1>0)
	{
	cout<<"\nSpaces are not allowed.Only Alphabets and Numbers Are Allowed,Write File Name without Extension";
	cout<<"\nEnter File Name :";
	cin.getline(newfilename,10000);
	if(!edittextfileapp::filenamecheck(newfilename))
	{
		cout<<"\nYou have Entered an invalid file name.";
		continue;
	}
	break;	
	}
	while(1>0)
	{
	cout<<"\nCurrent Location : "<<getcwd(currentworkingdirectory,10000);
	cout<<"\n\t\t1) Save to Current Location.\n\t\t2) Save to new Location\n\nChoice :";
	for (i=0;i<1000;i++)
	{
		choice[i]='\0';
	}
	cin.getline(choice,1000);
	if(choice[0]!='1'&&choice[0]!='2')
	{
		cout<<"\nPleae Enter Correct choice.";
		continue;
	}
	break;
	}
	if(choice[0]=='1')
	{
		strcpy(savefilelocation,currentworkingdirectory);
		if(savefilelocation[strlen(savefilelocation)-1]=='\\')
		{
			strcat(savefilelocation,newfilename);
			strcat(savefilelocation,".txt");
			ifstream checkfile;
			checkfile.open(savefilelocation);
			if(checkfile)
			{
				cout<<"\nA Text file with this name,in this location already exist.";
				cout<<"\nTry a different name or location.";
				continue;
			}
			fstream newfile;
			newfile.open(savefilelocation,ios::in|ios::out|ios::trunc);
			newfile.seekg(0,ios::beg);
			newfile.close();
			for (i=0;i<1000;i++)
			{
				if(e[i].filestate==0)
				{
					e[i].filelocationname=savefilelocation;
					e[i].filestate=1;
					e[i].slotnumber=i;
					return(i);
				}
				emptyslotstate++;
			}
			if(emptyslotstate==1000)
			{
				cout<<"\nCurrent Limit of Opening Files has been reached.";
				cout<<"\nTo open further files please close some of the files in 'See Current Opened Files' Option Listed in the main menu.";
				cout<<"\nReturning to main menu.";
				edittextfileapp::mainpage();				
			}
		}	
		if(savefilelocation[strlen(savefilelocation)-1]!='\\')
		{
			strcat(savefilelocation,"\\");
			strcat(savefilelocation,newfilename);
			strcat(savefilelocation,".txt");
			ifstream checkfile;
			checkfile.open(savefilelocation);
			if(checkfile)
			{
				cout<<"\nA Text file with this name,in this location already exist.";
				cout<<"\nTry a different name or location.";
				continue;
			}
			fstream newfile;
			newfile.open(savefilelocation,ios::in|ios::out|ios::trunc);
			newfile.seekg(0,ios::beg);
			newfile.close();
			for (i=0;i<1000;i++)
			{
				if(e[i].filestate==0)
				{
					e[i].filelocationname=savefilelocation;
					e[i].filestate=1;
					e[i].slotnumber=i;
					return(i);
				}
				emptyslotstate++;
			}
			if(emptyslotstate==1000)
			{
				cout<<"\nCurrent Limit of Opening Files has been reached.";
				cout<<"\nTo open further files please close some of the files in 'See Current Opened Files' Option Listed in the main menu.";
				cout<<"\nReturning to main menu.";
				edittextfileapp::mainpage();				
			}
		}
	}
	if(choice[0]=='2')
	{
		cout<<"\nEnter Location : ";
		cin.getline(savefilelocation,10000);
		if(savefilelocation[strlen(savefilelocation)-1]!='\\')
		{
			strcat(savefilelocation,"\\");
		}
		strcat(savefilelocation,newfilename);
		strcat(savefilelocation,".txt");
		ifstream checkfile;
		checkfile.open(savefilelocation);
		if(checkfile)
		{
			cout<<"\nA Text file with this name,in this location already exist.";
			cout<<"\nTry a different name or location.";
			continue;;
		}
		fstream newfile;
		newfile.open(savefilelocation,ios::in|ios::out|ios::trunc);
		if(!newfile)
		{
			cout<<"\nError Creating new file.Possibly The disk does not have enough space\nor This App Does not Have Administrative Authority in this Location.";
			cout<<"\nRun this program As an administrator to avoid this error.";
			continue;
		}
		newfile.seekg(0,ios::beg);
		newfile.close();
		for (i=0;i<1000;i++)
			{
			if(e[i].filestate==0)
			{
				e[i].filelocationname=savefilelocation;
				e[i].filestate=1;
				e[i].slotnumber=i;
				return(i);
			}
				emptyslotstate++;
			}
			if(emptyslotstate==1000)
			{
				cout<<"\nCurrent Limit of Opening Files has been reached.";
				cout<<"\nTo open further files please close some of the files in 'See Current Opened Files' Option Listed in the main menu.";
				cout<<"\nReturning to main menu.";
				edittextfileapp::mainpage();				
			}
	}	
	}
}
bool edittextfileapp::comparestringnoncasesensitive(const char searchfor[],const char searchin[])
{
	int i,a,x,exit=0;
	char searchforstring[strlen(searchfor)+1];
	char searchinstring[strlen(searchin)+1];
	strcpy(searchforstring,searchfor);
	strcpy(searchinstring,searchin);
	for (i=0;i<strlen(searchforstring);i++)
	{
		if(isalpha(searchforstring[i]))
		{
			searchforstring[i]=tolower(searchfor[i]);	
		}
	}
	for (i=0;i<strlen(searchin);i++)
	{
		if(isalpha(searchinstring[i]))
		{
			searchinstring[i]=tolower(searchin[i]);	
		}
	}
	if (strlen(searchforstring)>strlen(searchinstring))
	return(false);
	for (a=0;a<strlen(searchinstring);a++)
	{
		exit=0;
		if(searchforstring[0]==searchinstring[a])
		{
			x=a;
			x++;
			for (i=1;i<strlen(searchforstring);i++)
			{
				if(searchforstring[i]!=searchinstring[x])
				{
					exit=1;
					break;
				}
			x++;
			}
		if (exit==0)
		{
			return(true);
		}
		}
	}	
	return(false);
}
bool edittextfileapp::comparestringnoncasesensitive(const string inputstring,const char searchin[])
{
	int i,a,x,exit=0;
	char searchforstring[stringsize(inputstring)+1];
	char searchinstring[strlen(searchin)+1];
	edittextfileapp::stringtochararray(searchforstring,inputstring);
	strcpy(searchinstring,searchin);
	for (i=0;i<strlen(searchforstring);i++)
	{
		if(isalpha(searchforstring[i]))
		{
			searchforstring[i]=tolower(searchforstring[i]);	
		}
	}
	for (i=0;i<strlen(searchin);i++)
	{
		if(isalpha(searchinstring[i]))
		{
			searchinstring[i]=tolower(searchin[i]);	
		}
	}
	if (strlen(searchforstring)>strlen(searchinstring))
	return(false);
	for (a=0;a<strlen(searchinstring);a++)
	{
		exit=0;
		if(searchforstring[0]==searchinstring[a])
		{
			x=a;
			x++;
			for (i=1;i<strlen(searchforstring);i++)
			{
				if(searchforstring[i]!=searchinstring[x])
				{
					exit=1;
					break;
				}
			x++;
			}
		if (exit==0)
		{
			return(true);
		}
		}
	}	
	return(false);
}
bool edittextfileapp::comparestringcasesensitive(const char searchfor[],const char searchin[])
{
	int i,a,x,exit=0;
	char searchforstring[strlen(searchfor)+1];
	char searchinstring[strlen(searchin)+1];
	strcpy(searchforstring,searchfor);
	strcpy(searchinstring,searchin);
	if (strlen(searchforstring)>strlen(searchinstring))
	return(false);
	for (a=0;a<strlen(searchinstring);a++)
	{
		exit=0;
		if(searchforstring[0]==searchinstring[a])
		{
			x=a;
			x++;
			for (i=1;i<strlen(searchforstring);i++)
			{
				if(searchforstring[i]!=searchinstring[x])
				{
					exit=1;
					break;
				}
			x++;
			}
		if (exit==0)
		{
			return(true);
		}
		}
	}	
	return(false);
}
void edittextfileapp::printtext(edittextfileapp &obj)
{
	edittextfileapp::checkfile(obj);
	fstream currentfile;
	int i=0,filelength=0,newline=0;
	char read='\0',filename[stringsize(obj.filelocationname)+1];
	edittextfileapp::stringtochararray(filename,obj.filelocationname);
	currentfile.open(filename,ios::in|ios::out);
	currentfile.seekg(0,ios::beg);
	currentfile.seekg(0,ios::end);
	filelength=currentfile.tellg();
	currentfile.seekg(0,ios::beg);
	cout<<"\nFile Name And Location : "<<obj.filelocationname<<"\n\n";
	for (i=0;i<filelength;i++)
	{
		currentfile.seekg(i,ios::beg);	
		read=char(currentfile.get());
		if(read=='\n')
		{
			i++;
		}
		cout<<read;	
	}
	currentfile.close();
	edittextfileapp::edittextfilepage(obj);
}
void edittextfileapp::replacetextouter(char searchstring[],edittextfileapp &obj,bool condition)
{
	edittextfileapp::checkfile(obj);
	char inputreplacetext[1000];
	int found=0,searchstringlength=strlen(searchstring),currentfilepointer=0,filelength=0,i=0,a=0,x=0,y=0,difference=0,currentpointer=0;
	while(1>0)
	{
		for(i=0;i<1000;i++)
	{
		inputreplacetext[i]='\0';
	}
	cout<<"\nEnter Text To Replace "<<searchstring<<" with : ";
	cout<<"\nOr --1 to return to main menu :";
	cin.getline(inputreplacetext,1000);	
	if(inputreplacetext[0]=='-'&&inputreplacetext[1]=='-'&&inputreplacetext[2]=='1')
		{
			edittextfileapp::mainpage();
		}
	if(!edittextfileapp::checkstring(inputreplacetext))
		{
			cout<<"\nPlease Enter Valid Replace String.";
			continue;
		}	
			break;
	}
	fstream currentfile;
	char read='\0',filename[stringsize(obj.filelocationname)+1];
	edittextfileapp::stringtochararray(filename,obj.filelocationname);
	currentfile.open(filename,ios::in|ios::out);
	currentfile.seekg(0,ios::end);
	filelength=currentfile.tellg();
	currentfile.close();
	currentfile.open(filename,ios::in|ios::out);
	currentfile.seekg(0,ios::beg);
	fstream tempfile;
	tempfile.open("temp.tmp",ios::in|ios::out|ios::trunc);
	tempfile.seekg(0,ios::beg);
	for(i=0;i<filelength;i++)
	{
		currentfile.seekg(i,ios::beg);
		read=char(currentfile.get());
		if(read=='\n')
		{
			i++;
		}
		if(read==searchstring[0])
		{
			char searchin[searchstringlength+1];
			for (x=0;x<strlen(searchin);x++)
			{
				searchin[x]='\0';
			}
			searchin[0]=read;
			for (a=1;a<searchstringlength;a++)
			{
				searchin[a]=char(currentfile.get());
			}
			if(condition==true)
			{
				if(edittextfileapp::comparestringcasesensitive(searchstring,searchin))
				{
					tempfile<<inputreplacetext;
					i+=(strlen(searchstring)-1);
					continue;
				}
			}
			if(condition==false)
			{
				if(edittextfileapp::comparestringnoncasesensitive(searchstring,searchin))
				{
					tempfile<<inputreplacetext;
					i+=(strlen(searchstring)-1);
					continue;
				}
			}
		}
		tempfile<<read;
	}
	currentfile.close();
	currentfile.open(filename,ios::in|ios::out|ios::trunc);
	currentfile.seekg(0,ios::beg);
	tempfile.close();
	tempfile.open("temp.tmp",ios::in|ios::out);
	tempfile.seekg(0,ios::beg);
	tempfile.seekg(0,ios::end);
	filelength=tempfile.tellg();
	tempfile.seekg(0,ios::beg);
	for(i=0;i<filelength;i++)
	{
		currentfile.seekg(i,ios::beg);
		tempfile.seekg(i,ios::beg);	
		read=char(tempfile.get());
		if(read=='\n')
		{
			i++;
		}
		currentfile<<read;
	}
	currentfile.close();
	tempfile.close();
	tempfile.open("temp.tmp",ios::in|ios::out|ios::trunc);
	tempfile.close();
	edittextfileapp::searchandreplacetextpage(obj,condition);
}
int edittextfileapp::searchtext(char searchstring[],edittextfileapp &obj,bool condition)
{
	edittextfileapp::checkfile(obj);
	int found=0,searchstringlength=strlen(searchstring),currentfilepointer=0,filelength=0,i=0,a=0,x=0,difference=0;
	fstream currentfile;
	char read='\0',filename[stringsize(obj.filelocationname)+1];
	edittextfileapp::stringtochararray(filename,obj.filelocationname);
	currentfile.open(filename,ios::in|ios::out);
	currentfile.seekg(0,ios::end);
	filelength=currentfile.tellg();
	currentfile.close();
	currentfile.open(filename,ios::in|ios::out);
	currentfile.seekg(0,ios::beg);
	for(i=0;i<filelength;i++)
	{
		currentfile.seekg(i,ios::beg);
		read=char(currentfile.get());
		currentfilepointer=currentfile.tellg();
		difference=filelength-currentfilepointer;
		if(read==searchstring[0])
		{
			char searchin[searchstringlength+1];
			for (x=0;x<strlen(searchin);x++)
			{
				searchin[x]='\0';
			}
			searchin[0]=read;
			for (a=1;a<searchstringlength;a++)
			{
				searchin[a]=char(currentfile.get());
			}
			if(condition==true)
			{
				found+=edittextfileapp::comparestringcasesensitive(searchstring,searchin);
			}
			if(condition==false)
			{
				found+=edittextfileapp::comparestringnoncasesensitive(searchstring,searchin);
			}
		}
	}
	return(found);
}
void edittextfileapp::searchandreplacetextpage(edittextfileapp &obj,bool condition)
{
	edittextfileapp::checkfile(obj);
	char searchtext[10000],choice[100];
	int i=0,found=0;;	 
	for(i=0;i<10000;i++)
	{
		searchtext[i]='\0';
	}
	for(i=0;i<100;i++)
	{
		choice[i]='\0';
	}
	cout<<"\n<-------------Search And Replace------------->";
	cout<<"\nCurrent File Location And Name : "<<obj.filelocationname;
	while(1>0)
	{
		cout<<"\nEnter Text For";if(condition==true){cout<<" Case Sensitive Search :";}if(condition==false){cout<<" Non Case Sensitive Search :";}
		cout<<"\nOr --1 To Return To Main Menu :";
		cin.getline(searchtext,10000);
		if(searchtext[0]=='-'&&searchtext[1]=='-'&&searchtext[2]=='1')
		{
			edittextfileapp::mainpage();
		}
		if(!edittextfileapp::checkstring(searchtext))
		{
			cout<<"\nPlease Enter Valid Search String.";
			continue;
		}	
			break;
	}
	found=edittextfileapp::searchtext(searchtext,obj,condition);
	cout<<"\nSearching for : "<<searchtext<<"\t\tTotal No of Finds : "<<found;
	while(1>0)
	{
		if(found==0)
		{
			for(i=0;i<100;i++)
			{
				choice[i]='\0';
			}
			cout<<"\nPress\n\t\t1) New Search\n\t\t2) Delete All Text\n\t\t3) Add Text\n\t\t4) Return To Edit Menu\n\t\t5) Return To Main Menu\nChoice : ";
			cin.getline(choice,100);
			if(choice[0]!='1'&&choice[0]!='2'&&choice[0]!='3'&&choice[0]!='4'&&choice[0]!='5')
			{
			cout<<"\nPlease Enter Correct Choice.";
			continue;
			}
		}
		if(found>0)
		{
			for(i=0;i<100;i++)
			{
				choice[i]='\0';
			}
			cout<<"\nPress\n\t\t1) Replace Text\n\t\t2) New Search\n\t\t3) Delete All Text\n\t\t4) Add Text\n\t\t5) Return To Edit Menu\n\t\t6) Return To Main Menu\nChoice : ";
			cin.getline(choice,100);
			if(choice[0]!='1'&&choice[0]!='2'&&choice[0]!='3'&&choice[0]!='4'&&choice[0]!='5'&&choice[0]!='6')
			{
			cout<<"\nPlease Enter Correct Choice.";
			continue;
			}
		}	
		break;
	}
	if(choice[0]=='1')
	{
		if(found==0)
		{
			
		}
		if(found>0)
		{
			edittextfileapp::replacetextouter(searchtext,obj,condition);	
		}
	}
}
void edittextfileapp::resetslot(edittextfileapp &obj)
{
	obj.filelocationname='\0';
	obj.filestate=0;
}
int edittextfileapp::checkfilereturn(edittextfileapp &obj)
{
	fstream currentfile;
	char filename[stringsize(obj.filelocationname)+1];
	edittextfileapp::stringtochararray(filename,obj.filelocationname);
	currentfile.open(filename,ios::in|ios::out);
	if(currentfile)
	{
		currentfile.close();
		return(1);
	}
	if(!currentfile)
	{
		return (0);
	}
}
int edittextfileapp::checkfile(edittextfileapp &obj)
{
	fstream currentfile;
	char filename[stringsize(obj.filelocationname)+1];
	edittextfileapp::stringtochararray(filename,obj.filelocationname);
	currentfile.open(filename,ios::in|ios::out);
	if(currentfile)
	{
		currentfile.close();
	}
	if(!currentfile)
	{
		cout<<"\nError Opening File\nThe file possibily has been removed,renamed or corrupted.";
		cout<<"\nRun this app as an administrator to avoid such errors.";
		cout<<"Closing File And Returning to Main Menu";
		edittextfileapp::resetslot(obj);
		edittextfileapp::mainpage();
	}
}
int edittextfileapp::noofopenedfiles()
{
	int i=0,openedfiles=0;
	for (i=0;i<1000;i++)
	{
		if(e[i].filestate==1)
		{
			openedfiles++;
		}
	}
	return(openedfiles);
}
void edittextfileapp::createobject(char inputfilelocationname[])
{
	int i=0;
	for (i=0;i<1000;i++)
	{
		if(e[i].filestate==0)
		{
			break;
		}
	}
	e[i].filelocationname=inputfilelocationname;
	e[i].filestate=1;
	e[i].slotnumber=i;
	edittextfileapp::writetohistory(e[i]);
	edittextfileapp::edittextfilepage(e[i]);
}
void edittextfileapp::edittextfilepage(edittextfileapp &obj)
{
	edittextfileapp::checkfile(obj);
	char choice[100];
	int i=0;
	for(i=0;i<100;i++)
	{
		choice[i]='\0';
	}
	cout<<"\n---------Edit Text File Page---------------------------";
	cout<<"\nCurrent File Name And Location.";
	cout<<"\nLocation : "<<obj.filelocationname;
	cout<<"\nPress\n\t\t1) View All Text\n\t\t2) Add Text\n\t\t3) Search and Replace Text Case Sensitive\n\t\t4) Search and Replace Text Non Case Sensetive\n\t\t5) Delete All Text\n\t\t6) Copy All Text\n\t\t7) Close Current File\n\t\t8) Main Menu";
	cout<<"\nChoice : ";
	cin.getline(choice,100);
	if(choice[0]!='1'&&choice[0]!='2'&&choice[0]!='3'&&choice[0]!='4'&&choice[0]!='5'&&choice[0]!='6'&&choice[0]!='7'&&choice[0]!='8')
	{
		cout<<"\nPlease enter correct choice.";
		edittextfileapp::edittextfilepage(e[obj.slotnumber]);
	}
	if(choice[0]=='1')
	{
		edittextfileapp::printtext(obj);
	}
	if(choice[0]=='2')
	{
		edittextfileapp::addtext(obj);
	}
	if(choice[0]=='3')
	{
		edittextfileapp::searchandreplacetextpage(e[obj.slotnumber],true);
	}
	if(choice[0]=='4')
	{
		edittextfileapp::searchandreplacetextpage(e[obj.slotnumber],false);
	}
	if(choice[0]=='5')
	{
		edittextfileapp::deletealltext(obj);
	}
	if(choice[0]=='6')
	{
		edittextfileapp::copyfile();
	}
	if(choice[0]=='7')
	{
		edittextfileapp::resetslot(obj);
		edittextfileapp::mainpage();
	}
	if(choice[0]=='8')
	{
		edittextfileapp::mainpage();
	}
}	
void edittextfileapp::mainpage()
{
	char choice[100];
	int i=0;
	for(i=0;i<100;i++)
	{
		choice[i]='\0';
	}
	cout<<"\n----------Welcome To Text File Editor App------------------";
	cout<<"\nPress\t\t\t\t\t\tCurrent Opened Files Are : "<<edittextfileapp::noofopenedfiles()<<"\n\t\t1) Open Existing File.\n\t\t2) Open New Blank File.\n\t\t3) Copy Files.\n\t\t4) See Current Opened Files.\n\t\t5) History Of Opened Files.\n";
	cout<<"\nChoice : ";
	cin.getline(choice,100);
	if(choice[0]!='1'&&choice[0]!='2'&&choice[0]!='3'&&choice[0]!='4'&&choice[0]!='5')
	{
		cout<<"\nPlease enter correct choice.";
		edittextfileapp::mainpage();
	}
	if(choice[0]=='1')
	{
		edittextfileapp::openfilepage();
	}
	if(choice[0]=='2')
	{
		edittextfileapp::newblankfile();
	}
	if(choice[0]=='3')
	{
		edittextfileapp::copyfile();
	}
	if(choice[0]=='4')
	{
		if(edittextfileapp::noofopenedfiles()==0)
		{
		cout<<"\nSorry There are no Currently opened files.";
		edittextfileapp::mainpage();	
		}
		edittextfileapp::currentopenedfiles();
	}
	if(choice[0]=='5')
	{
		edittextfileapp::historyofopenedfilespage();
	}
}
void edittextfileapp::openfilepage()
{
	char filename[100000];
	fstream openfile;
	int i=0;
	for(i=0;i<100000;i++)
	{
		filename[i]='\0';
	}
	cout<<"\n---------------------------------------------------------";
	cout<<"\nEnter Text File Location including Dot Extension Or Zero To Return to Main Page\nEnter Location : ";
	cin.getline(filename,100000);
	if(filename[0]=='\0')
	{
		edittextfileapp::mainpage();
	}
	for(i=0;i<1000;i++)
	{
		if(edittextfileapp::comparestringnoncasesensitive(e[i].filelocationname,filename))
		{
			cout<<"\nThis Location And File Has Already Being Opened";
			cout<<"\nReturning to main menu";
			edittextfileapp::mainpage();		
		}
	}
	openfile.open(filename,ios::in|ios::out);
	if(openfile)
	{
		cout<<"\nFile Was Successfully Opened.";
		openfile.close();
		edittextfileapp::createobject(filename);
	}
	if(!openfile)
	{
		cout<<"\nError Opening File.";
		cout<<"\nPossibly The file Does not exist or\nYou need to run this program 'As an Administrator' to avoid this error.";
		edittextfileapp::mainpage();
	}
}
main()
{
	edittextfileapp::mainpage();
}


