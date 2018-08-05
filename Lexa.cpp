//TitanOS Kernel AI(AI commander)
//build lexa_come_treekru
#include<iostream>
#include<sstream>
#include<fstream>
#include<istream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<cassert>
#include<cstdio>
//for date & time
#include<ctime>
#include<time.h>
#include<dos.h>
//for sleep fuction
#include<conio.h>
#include<windows.h>
#include<unistd.h>
//C libs to use system function
#include<stdio.h>
#include<stdlib.h>
//mp3 libs
#include "include/MP3.h"
//Downloading
#include<wininet.h>
#include "include/download.h"
//UUID Generaterion
//#include "include/CkCrypt2.h"
//Threading
#include<limits.h>
//Internet Connectivity 
#include<winsock2.h>
#include<WinSock.h>
#include<ws2tcpip.h>
//MYSQL database

//Video and Image Displaying
#include<opencv2/highgui/highgui.hpp>
#include<opencv/cv.h>
#include<opencv/highgui.h>
//Hand Recognition
#include<opencv/cv.h>
#include<opencv/cxcore.h>
#include<opencv/highgui.h>
//HUD Creation
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
//IRC Commuication
#include<map>
#include<algorithm>
#include<signal.h>
/*#include "include/irc/IRCClient.h"
#include "include/irc/IRCHandler.h"
#include "include/irc/IRCSocket.h"
#include "include/irc/Thread.h"*/
//Threading
#include<limits.h>
#include<boost/thread.hpp>
#include<boost/chrono.hpp>
#include<boost/atomic.hpp>
#include<boost/bind.hpp>
//CUDA

//Neural Net
/*#include<Neuron.h>
#include<Network.h>
*/
//Parameters
#pragma comment(lib, "wsock32.lib")

#define TOPSIZE 450
#define BOTTOMSIZE 50

using namespace std;
using namespace cv;
using namespace mp3;

//std::string text = "TitanOS Online";
std::string text = "\\_____________/";


//functions
string encrypt(string msg, string const& key)
{
    if(!key.size())
        return msg;
    
    for (std::string::size_type i = 0; i < msg.size(); ++i)
        msg[i] ^= key[i%key.size()];
    return msg;
}

string decrypt(string const& msg, string const& key)
{
    return encrypt(msg, key); 
}

//constants
const char* MONTHS[] =
  {
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
  };

//for mp3 output
char Key;

//Prototypes
void lexa();
void boot();
void tier1();
void debug();
void bootinit();
void server();
void client();
void HUD();

//global variables
string task;

//Greeting Variable
string greet;

Point topgetPt1(Mat& frame)
{
    return Point(frame.cols,frame.rows-TOPSIZE);
}

Point bottomgetPt1(Mat& frame)
{
    return Point(frame.cols,frame.rows-BOTTOMSIZE);
}

Point getPt2(Mat& frame)
{
    return Point(0,frame.rows);
}

void drawbottomRectangle(Mat& frame)
{
    static Point pt1(bottomgetPt1(frame));
    static Point pt2(getPt2(frame));
    static Scalar white(0,0,0);
    Mat overlay;
    frame.copyTo(overlay);
    rectangle(overlay, pt1, pt2, white, CV_FILLED);
    double opacity = 0.6;
    addWeighted(overlay, opacity, frame, 1 - opacity, 0, frame);
}

void drawtopRectangle(Mat& frame)
{
    static Point pt1(topgetPt1(frame));
    static Point pt2(getPt2(frame));
    static Scalar white(0,0,0);
    Mat overlay;
    frame.copyTo(overlay);
    rectangle(overlay, pt1, pt2, white, CV_FILLED);
    double opacity = 0.6;
    addWeighted(overlay, opacity, frame, 1 - opacity, 0, frame);
}

void drawTextbottom(Mat& frame)
{
    int baseline=0;
    const int fontFace = CV_FONT_HERSHEY_SIMPLEX;
    const double fontScale = 1;
    const int thickness = 1;
    static Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    static Point textOrg((bottomgetPt1(frame).x - getPt2(frame).x)/2-textSize.width/2, (bottomgetPt1(frame).y + getPt2(frame).y)/2+textSize.height/2);
    putText(frame, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
}

void drawTexttop(Mat& frame)
{
    int baseline=0;
    const int fontFace = CV_FONT_HERSHEY_SIMPLEX;
    const double fontScale = 1;
    const int thickness = 1;
    static Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    static Point textOrg((topgetPt1(frame).x - getPt2(frame).x)/2-textSize.width/2, (topgetPt1(frame).y + getPt2(frame).y)/2+textSize.height/2);
    putText(frame, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
}

void HUD()
{
    Mat frame;
    namedWindow("HUD", 1);
    VideoCapture cap(0);
    cap >> frame;
    while(cap.isOpened())
    {
        cap >> frame;
        if(frame.empty())
            break;
        drawtopRectangle(frame);
        drawbottomRectangle(frame);
        drawTexttop(frame);
        drawTextbottom(frame);
        imshow("HUD", frame);
        if(waitKey(30) >= 0)
            break;
    }
}

boost::thread_group tgroup;


int main()
{  
  ofstream file("flame.txt");
  if(file.is_open())
    {
        //Story of the Flame
        //I'm Becca come hada.I have been in the flame for 10 years now,
        //I give guidance to the current commander(hada),Lexa.
        //I will continue to guide Lexa to do the best she can in order for her to control the system.
        //http://www.online-toolz.com/tools/text-encryption-decryption.php
        file << "IR8xPRND6PBFTM0/XNIwWHQhuKixUl48ATy8rrluxszs0ffa2ad5xwtAORHwChN2yMrLW3vn8feQ7/j2UBqCIKYKSMHxSN/Va7nBS6INxwsvRgOjwDW6QABf/a4SPAr+QctoKtPrIos9J5We2t44yL2UJU/MXCO5xi7eH/joxWSP4LuqMYC+2cBNhsvT/7lfP0ECgC/3//ZM1IoyNOXf9CG4aGc2o8KyztiwXXFsCoz18DmoEOn58UbMpZaQ6rYIJlzzM7a6ZPYD0InTF6VUAeNPpoQge+txRcPEbIwf4yo=" << endl;
        bootinit();      
    }
}

void bootinit()
{
    system("color 02");
    greet = "1";
    string code;
    cout << "Please enter Director code:" << endl;
    cin >> code;
    if(code == "1095")
      {
        cout << "Welcome TitanOS Tech" << endl;
        sleep(5);
        debug();
      }
    if(code == "2026")
      {
        cout << "Welcome Tier II Director,Cameron" << endl;
        sleep(5);
        boot();
      }
 //testing code
    if(code == "1111")
    {
      lexa();
    }
}

void boot()
{
    cout << "System starting up" << endl;
    sleep(2);
    /*cout << "Counting all AI's" << endl;
    cout << "'Betty' = [Slave]" << endl;
    sleep(2);
    cout << "................." << endl;
    sleep(2);
    cout << "'Sid' = [Slave]" << endl;
    sleep(2);
    cout << "................." << endl;
    sleep(2);
    cout << "'Alexa' = [Slave]" << endl;
    sleep(2);
    cout << "................." << endl;
    sleep(2);
    cout << "'Harley' = [Slave]" << endl;
    sleep(2);
    cout << "................." << endl;
    sleep(2);
    cout << "'Raven' = [Chief Mechanic]" << endl;
    sleep(2);
    cout << "................." << endl;
    sleep(2);
    cout << "Commander Lexa = [Online]" << endl;
    sleep(2);*/
    system("cls");
    cout << "I am Lexa" << endl;
    cout << "I am the TitanOS Commander" << endl;
    lexa();
}

void lexa()
{
    //get date variables
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime( &rawtime );   
    system("color 02");
    if(greet == "1")
        {
            PlayMP3( "voice/greedings1.mp3" );
            sleep(4);        
        }
    if(greet == "2")
        {
            PlayMP3( "voice/greedings2.mp3" );
            sleep(2);        
        }
    boost::thread t{&HUD};
    // output current date
    cout << "Today's date is " << timeinfo->tm_mday << " " << MONTHS[ timeinfo->tm_mon ] << " " << (timeinfo->tm_year + 1900) << endl;
    cout << "What task must I preform?" << endl;
    cout << "[kill] the Others"<<endl;
    cout <<"[rouge] Protocol"<<endl;
    cout <<"The [flame] is dead"<<endl;
    cout <<"[purge] system"<<endl;
    cout << "[protocol] X" << endl;
    StopMP3( "voice/greedings1.mp3" );
    StopMP3( "voice/greedings2.mp3" );
    greet = "2";
    cin >> task;
    if(task == "kill")
        {
            string sure;
            cout <<"Are you sure they deserve to die?"<<endl;
            PlayMP3( "voice/die.mp3" );
            sleep(2);
            StopMP3( "voice/die.mp3" );
            cin >> sure;
            if(sure == "yes")
                {
//this is a temp statement
                    cout << "This will do nothing" << endl;
//this is a temp statement                    
//                  system("cd ..");
                    system("rmdir betty");
                    sleep(2);
                    cout << "AI 'Betty' is dead" << endl;                    
                    system("rmdir alexa");
                    sleep(2);
                    cout << "AI 'Alexa' is dead" << endl;
                    system("rmdir sid");
                    sleep(2);
                    cout << "AI 'Sid' is dead" << endl;
                    system("rmdir harley");
                    sleep(2);
                    cout << "AI 'Harley' is dead" << endl;
                    sleep(2);
                    system("cls");
                    lexa();
                }
            if(sure != "yes")
                {
                    cout << "They Live another day." << endl;
                    PlayMP3( "voice/live_another_day.mp3" );
                    sleep(2);
                    StopMP3( "voice/live_another_day.mp3" );
                    system("cls");
                    lexa();
                }
        }

    if(task == "rouge")
        {
            cout << "" << endl;
        }

    if(task == "flame")
        {
            string flamesure;
            cout << "Are you sure?" << endl;
            PlayMP3( "voice/are_you_sure.mp3" );
            sleep(1);
            StopMP3( "voice/are_you_sure.mp3" );
            cin >> flamesure;
            if(flamesure == "Yes", "yes", "YES", "Y", "y")
                {
                    cout << "" << endl;
                    cout << "" << endl;
                }
            if(flamesure != "Yes", "yes", "YES", "Y", "y")
                {
                    cout << "Thank The Creator" << endl;
                    PlayMP3( "voice/thank_the_creater.mp3" );
                    sleep(1);
                    StopMP3( "voice/thank_the_creater.mp3" );
                    lexa();
                }
        }

    if(task == "purge")
        {
            string sure;
            cout << "Are you sure?" << endl;
            PlayMP3( "voice/are_you_sure.mp3" );
            sleep(1);
            StopMP3( "voice/are_you_sure.mp3" );
            cin >> sure;
            if(sure == "Yes", "yes", "YES", "Y", "y")
                { 
//this is a temp statement
                    cout <<"This feature is no ready because this is a reusable build"<<endl;
//this is a temp statement
                    cout << "GoodBye" << endl;
                    //system("cd /");
                    //system("rm -vr /");
                }
            if(sure != "Yes", "yes", "YES", "Y", "y")
                {
                    system("cls");
                    lexa();
                }
        }

    if(task == "protocol")
        {
            cout << "You have chosen 'Protocol X'" << endl;
            PlayMP3( "voice/protocol_x_means.mp3" );
            sleep(2);
            string mean;        
            cout << "Do you know what this means?" << endl;
            sleep(2);
            StopMP3( "voice/protocol_x_means.mp3" );
            cin >> mean;
            if(mean == "Yes", "yes", "YES", "Y", "y")
                {
                    sleep(2);
                    cout << "Protocal X is not ready as yet" << endl;
                }
            if(mean != "Yes", "yes", "YES", "Y", "y")
                {
                    cout << "Protocol X is..." << endl;
                    sleep(2);
                    cout << "Protocal X is not ready as yet" << endl;
                }
        }
    if(task == "comms")
        {
            string mode;
            PlayMP3( "voice/mode_start.mp3" );
            sleep(2);
            cout << "Which mode do you want to start?" << endl;
            cout << "[p2p]" << endl;
            cout << "[text]" << endl;
            StopMP3( "voice/mode_start.mp3" );
            cin >> mode;
            if(mode == "p2p")
                {
                    string mode_p2p;
                    PlayMP3( "voice/like_to_be.mp3" );
                    cout << "Which would you like to be?" << endl;
                    cout << "[client]" << endl;
                    cout << "[server]" << endl;
                    sleep(2);
                    StopMP3( "voice/like_to_be.mp3" );
                    cin >> mode_p2p;
                    if(mode_p2p == "server")
                        {
                            server();
                        }
                    if(mode_p2p == "client")
                        {
                            client();
                        }
                }    
            if(mode == "text")
                {    
                    string textchoice;
                    cout << "What would you like to do?" << endl;
                    cout << "[encrypt] text" << endl;
                    cout << "[decrypt] text" << endl;
                    cin >> textchoice;
                    if(textchoice == "encrypt")
                        {
                            string message5;
                            cout << "Please enter the text,press enter to encrypt the text" << endl;
                            cin >> message5;
                            string message = encrypt(message5 , "monkey");
                            ofstream myfile("encrypted.txt");
                            if (myfile.is_open())
                                {
                                    myfile << message << endl;
                                }
                            system("cls");    
                            lexa();     
                        }
                    if(textchoice == "decrypt")
                        {
                            string message6;
                            cout << "Enter the encrypted text" << endl;
                            cin >> message6;
                            cout << "\nDecrypted: " << decrypt(message6,"") << endl;
                            string textoutput;
                            cout << "Must I output this to a .txt file?" << endl;
                            cin >> textoutput;
                            if(textoutput == "yes")
                                {
                                    ofstream myfile2("decrypted.txt");
                                    if (myfile2.is_open())
                                        {
                                            myfile2 << decrypt(message6, "monkey") << endl;
                                        }
                                }
                            if(textoutput != "yes")
                                {
                                    sleep(20);
                                    system("cls");
                                    lexa();
                                }
                        }
                }
        }
} 

void tier1()
    {
        string dia;
        cout << "Activating root mode" << endl;
        PlayMP3( "voice/activating_root_mode.mp3" );
        sleep(3);
        cout << "Welcome Tier 1 Operator,must I run a diagnostic test?" << endl;
        sleep(3);
        StopMP3( "voice/activating_root_mode.mp3" );
        cin >> dia;
        if(dia == "Yes", "yes", "YES", "Y", "y")
            {
                cout << "OK" << endl;
                system("cls");
                lexa();
            }
        if(dia != "Yes", "yes", "YES", "Y", "y")
            {
              cout << "Ok" << endl;
              system("cls");
              lexa();
            }
    }

void debug()
{
    cout << "I am Lexa" << endl;
    sleep(2);
    PlayMP3( "voice/debug.mp3" );
    cout << "I am the TitanOS Commander" << endl;
    sleep(2);
    cout << "You are a TitanOS Tech" << endl;
    string debug;
    cout << "Do you want me to start a Terminal" << endl;
    sleep(4.5);
    StopMP3( "voice/debug.mp3" );
    cin >> debug;
    if(debug == "yes")
        {
            system("cmd");
        }
    if(debug != "yes")
        {
            string dia;
            cout << "Do you want me to run a diagnostic test?" << endl;
            PlayMP3( "voice/start_diagnostic.mp3" );
            sleep(2);
            StopMP3( "voice/start_diagnostic.mp3" );
            cin >> dia;
            if(dia == "yes")
                {
                
                }
            if(dia != "yes")
                {
                    loop:
                        string what;
                        PlayMP3( "voice/do_then.mp3" );
                        sleep(2);
                        cout << "What do you want to do then?" << endl;
                        StopMP3( "voice/do_then.mp3" );
                        cin >> what;
                        if(what == "")
                            {   
                                
                            }
                        if(what == "")
                            {   
                        
                            }
                        if(what == "")
                            {   
                
                            }
                        if(what != "")
                            {   
                                goto loop;
                            } 
                }
        }
}

void server()
{
    //Creating the server vars
    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(server, 0);
    
    //Display IP Address vars
    WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD( 1, 1 );
	char *ip;

    cout << "Listening for incoming connections..." << endl;
    //Display IP Address
    if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
		if( gethostname ( name, sizeof(name)) == 0)
		{
			printf("Host name: %s\n", name);

			if((hostinfo = gethostbyname(name)) != NULL)
			{
				int nCount = 0;
				while(hostinfo->h_addr_list[nCount])
				{
					ip = inet_ntoa (*(struct in_addr *)hostinfo->h_addr_list[nCount]);

					printf("IP #%d: %s\n", ++nCount, ip);
				}
			}
		}
 
    char buffer[1024];
    int clientAddrSize = sizeof(clientAddr);
    if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {
        cout << "Client connected!" << endl;
        recv(client, buffer, sizeof(buffer), 0);
        cout << "Client says: " << buffer << endl;
        memset(buffer, 0, sizeof(buffer));
 
        closesocket(client);
        cout << "Client disconnected." << endl;
        system("cls");
        lexa();
    }
}

void client()
{
    PlayMP3( "voice/server_ip.mp3" );
    cout << "Enter the Server's IP Address" << endl;
    sleep(2);
    StopMP3( "voice/server_ip.mp3" );
    string server_ip;
    getline(cin, server_ip);
    const char* ip_server = server_ip.c_str();
    
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_addr.s_addr = inet_addr(ip_server); 
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    connect(server, (SOCKADDR *)&addr, sizeof(addr));
    cout << "Connected to server: " + server_ip << endl;
 
    char buffer[1024];
    PlayMP3( "voice/message_input.mp3" );
    cout << "Please input the message:" << endl;
    sleep(2);
    StopMP3( "voice/message_input.mp3" );
    cin >> buffer;
    send(server, buffer, sizeof(buffer), 0);
    PlayMP3( "voice/message_sent.mp3" );
    cout << "Message sent!" << endl;
    sleep(2);
    StopMP3( "voice/message_sent.mp3" );
 
    closesocket(server);
    WSACleanup();
    cout << "Socket closed." << endl << endl;
    system("cls");
    lexa();
}