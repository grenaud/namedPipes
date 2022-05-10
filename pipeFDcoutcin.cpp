/*
 * testFD
 * Date: May-04-2022 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>

using namespace std;



int writeNumbers(){
    //ofstream oFile;
    //cerr<<"writeNumbers "<<filename<<endl;
    //oFile.open(filename, ios::out);
    cerr<<"opened"<<endl;
    // if (oFile.is_open()){
    for(int i=1;i<11;i++){
	cout<<i<<endl;
	cerr<<"writing "<<(i*2)<<endl;
    }
    //oFile.close();
    return 0;
    // }else{
    // 	cerr << "Unable to write to file "<<filename<<endl;
    // 	return 1;
    // }



}

int rwDoubleNumbers(){
    string line;
    // ifstream iFile;
    // ofstream oFile;
    // cerr<<"rwDoubleNumbers "<<filenamein<<" "<<filenameout<<endl;
    // iFile.open(filenamein.c_str(),  ios::in);
    // oFile.open(filenameout.c_str(), ios::out);

    // if (!iFile.is_open()){
    // 	cerr << "Unable to open file "<<filenamein<<endl;
    // 	return 1;
    // }
    // if (!oFile.is_open()){
    // 	cerr << "Unable to write to file "<<filenameout<<endl;
    // 	return 1;
    // }


    while(getline (cin,line)){
	int i=stoi(line);
	cerr<<"read "<<i<<" writing "<<(i*2)<<endl;
	cout<<(i*2)<<endl;
    }

    // iFile.close();
    // oFile.close();

    return 0;
}



int main (int argc, char *argv[]) {

    char * myfifo = "fifo0";

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);


    pid_t pid1 = fork();
    if (pid1 == -1) {
        cerr<<"error in fork"<<endl;
        exit(1);
    }else{

	if(pid1 == 0) {
	    cerr<<"child "<<endl;
	    pid_t pid2 = fork();
	    
	    if (pid2 == -1) {
	        cerr<<"error in fork"<<endl;
		exit(1);
	    }else{

		if(pid2 == 0) {
		    cerr<<"child of child "<<endl;

		    fstream fout;
		    fout.open("output.txt", ios::out);
		    fstream fin;
		    fin.open(myfifo, ios::in);

		    streambuf* sbcin   = cin.rdbuf();
		    streambuf* sbcout  = cout.rdbuf(); 

		    streambuf* sbfilei = fin.rdbuf();
		    streambuf* sbfileo = fout.rdbuf();

		    cin.rdbuf(sbfilei); //sending file to cin
		    cout.rdbuf(sbfileo);//sending cout to file
		    
		    rwDoubleNumbers();
		    
		    cin.rdbuf(sbcin); //cin is now the normal cin again
		    cout.rdbuf(sbcout); //cout is now the normal cout again

		    
		    fin.close();
		    fout.close();

		    exit(0);
		}else{
		    cerr<<"child#1 "<<endl;
		    //send stdout to fifo
		    fstream fout;
		    fout.open(myfifo, ios::out);		    
		    streambuf* sbcout = cout.rdbuf(); 
		    streambuf* sbfile = fout.rdbuf();
		    
		    cout.rdbuf(sbfile);
		   
		    writeNumbers();

		    cout.rdbuf(sbcout);
		    fout.close();

		    pid_t wpid;
		    int status = 0;
		    while ((wpid = wait(&status)) > 0); 
		    exit(0);
		}
	    }
	}else{
	    cerr<<"parent "<<endl;
		
	}

	
    }
    pid_t wpid;
    int status = 0;
    
    while ((wpid = wait(&status)) > 0); 

    
    //wait for the 
    remove(myfifo);

}

