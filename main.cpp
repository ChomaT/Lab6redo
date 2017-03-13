//============================================================================
// Name        : Lab6.cpp
// Author      : Theo Choma
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

class Signal{
	private:
		int *data;
		int length;
		int max;
		double avg;
	public:
		Signal();		// default constructor.
		Signal(int);            // parametric constructor file number
                Signal(string);         //parametric constructor file name
		~Signal();		// destructor
                void Offset();
                void Scale();
                void Center();
                void Normalize();
                void Statistics();
                void Sig_info();
                void Save_file(string);
};



Signal::Signal(){
	length = 0;
	max = 0;
	avg = 0;
        
        int i = 0, sum = 0;


	ifstream fpointer;
	fpointer.open("Raw_data_01.txt", ios::in);
	if (fpointer.is_open())
	{
            fpointer >> length >> max;
            data = new int[length];
            while(!fpointer.eof())
                    {

                        fpointer >> data[i];
                        i++;
                    }
                    fpointer.close();
	}

	//Define avg
	for (i = 0; i < length; i++)
	{
		sum = sum + data[i];
	}
	avg = (double) sum / (double) length;

}



Signal::Signal(int L){
	int i = 0, sum = 0;
	length = 0;
        max = 0;
        avg = 0;
        string fname;
        char str[25] = {'\0'};

	ifstream fpointer;
	if ( L < 10)
        {
            sprintf(str,"Raw_data_0%d.txt",L);
            fname = str;
            
            fpointer.open(fname.c_str(), ios::in);
	}
        else
        {
            sprintf(str,"Raw_data_%d.txt",L);
            fname = str;
            fpointer.open(fname.c_str(), ios::in);
        }
        
        if (fpointer.is_open())
	{
            fpointer >> length >> max;
            data = new int[length];
            
                while(!fpointer.eof())
		{
                    
                    fpointer >> data[i];
                    i++;
		}

                fpointer.close();
	}

	//Define avg
	for (i = 0; i < length; i++)
	{
		sum = sum + data[i];
	}
	avg = (double) sum / (double) length;

}



Signal::Signal(string instr){
	int i = 0, sum = 0;
	length = 0;
        max = 0;
        avg = 0;
        string fname = instr + ".txt";

	ifstream fpointer;
            fpointer.open(fname.c_str(), ios::in);
        
        
        if (fpointer.is_open())
	{
            fpointer >> length >> max;
            data = new int[length];
                while(!fpointer.eof())
		{
                    
			fpointer >> data[i];
                        i++;
		}
                fpointer.close();
	}

	//Define avg
	for (i = 0; i < length; i++)
	{
		sum = sum + data[i];
	}
	avg = (double) sum / (double) length;

}
Signal::~Signal(){
	delete[] data;	// instead of 'free'
}



void Signal::Offset()
{
	int i, factor;

        cout << "Input an offset factor: ";
        cin >> factor;
        
	for(i = 0; i < length; i++)
	{
		data[i] = (double)data[i] + factor;
	}
}





void Signal::Scale()
{
	int i, factor;

	cout << "Input a scaling factor: ";
	cin >> factor;

	for(i = 0; i < length; i++)
	{
		data[i] = (double)data[i] * factor;
	}

}


void Signal::Center()
{
	int i;

	for(i = 0; i < length; i++)
	{
		data[i] = (double)data[i] - avg;
	}
}





void Signal::Normalize()
{
	int i;

	for(i = 0; i < length; i++)
	{
			data[i] = (double)data[i] / (double) max;
	}

}


void Signal::Sig_info()
{
	cout<<"Length: " << length << endl << "Max: " << max << endl << "Average: " << avg << endl;
}

void Signal::Save_file(string outstr)
{
	fstream outstream;
        string fname = outstr + ".txt";
	outstream.open (fname.c_str(), ios::out);
        if(outstream.is_open())
        {
            outstream << length << " "<< max << endl;
            for(int i = 0; i < length; i++)
            {
                    outstream << data[i] << endl;
            }
            outstream.close();
        }
        else{
            cout<<"File stream output error"<<endl;
        }
}





int main(int argc, char *argv[]) {
	int fnum, choice = 0;
	string fname, outname;
	Signal *sig2;

	if(argv[1][1] == 'n')
		{
			fnum = atoi(argv[2]);
			sig2 = new Signal(fnum);
		}
	else if(argv[1][1] == 'f')
		{
			fname = argv[2];
			sig2 = new Signal(fname);
		}
	else
		{
			sig2 = new Signal();
		}

	while(choice != 7)
	{
		cout << "\nMake an operation choice: "
				"\n1. Offset"
				"\n2. Scale"
				"\n3. Center"
				"\n4. Normalize"
				"\n5. Print Info"
				"\n6. Save Data"
				"\n7. Quit" << endl;
		cin >> choice;

		if(choice == 1)
		{
			sig2->Offset();
		}
		else if(choice == 2)
		{
			sig2->Scale();
		}
		else if(choice == 3)
		{
			sig2->Center();
		}
		else if(choice == 4)
		{
			sig2->Normalize();
		}
		else if(choice == 5)
		{
			sig2->Sig_info();
		}
		else if(choice == 6)
		{
			cout << "Please input desired output name without extension: ";
			cin >> outname;
			sig2->Save_file(outname);
		}
	}

	delete sig2;
}
