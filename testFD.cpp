/*
 * testFD
 * Date: May-04-2022 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>


using namespace std;



int writeNumbers(const string & filename){
    ofstream oFile;
    oFile.open(filename.c_str(), ios::out);

    if (oFile.is_open()){
	for(int i=1;i<11;i++)
	    oFile<<i<<endl;
	
	oFile.close();
	return 0;
    }else{
	cerr << "Unable to write to file "<<filename<<endl;
	return 1;
    }



}

int rwDoubleNumbers(const string & filenamein,const string & filenameout){
    string line;
    ifstream iFile;
    ofstream oFile;

    iFile.open(filenamein.c_str(),  ios::in);
    oFile.open(filenameout.c_str(), ios::out);

    if (!iFile.is_open()){
	cerr << "Unable to open file "<<filenamein<<endl;
	return 1;
    }
    if (!oFile.is_open()){
	cerr << "Unable to write to file "<<filenameout<<endl;
	return 1;
    }


    while(getline (iFile,line)){
	int i=stoi(line);
	oFile<<(i*2)<<endl;
    }

    iFile.close();
    oFile.close();

    return 0;
}


int main (int argc, char *argv[]) {
    writeNumbers("numbers.txt");
    rwDoubleNumbers("numbers.txt","double.txt");
    return 0;
}

