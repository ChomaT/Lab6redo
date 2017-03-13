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
		double *data;
		int length;
		double max;
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

    int i = 0;
    double sum = 0;


	ifstream fpointer;
	fpointer.open("Raw_data_01.txt", ios::in);
	if (fpointer.is_open())
	{
            fpointer >> length >> max;
            data = new double[length];
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
	avg = sum / (double) length;

}



Signal::Signal(int L){
	int i = 0;
	double sum = 0;
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
            data = new double[length];

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
	avg = sum / (double) length;

}



Signal::Signal(string instr){
	int i = 0;
	double sum = 0;
	length = 0;
        max = 0;
        avg = 0;
        string fname = instr + ".txt";

	ifstream fpointer;
            fpointer.open(fname.c_str(), ios::in);


        if (fpointer.is_open())
	{
            fpointer >> length >> max;
            data = new double[length];
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
	avg = sum / (double) length;

}
Signal::~Signal(){
	delete[] data;	// instead of 'free'
}



void Signal::Offset()
{
	int i, factor;
	double sum;

        cout << "Input an offset factor: ";
        cin >> factor;
        if(factor <= 1000 && factor >= -1000)
        {
        	for(i = 0; i < length; i++)
        		{
        			data[i] = data[i] + factor;
        		}

        		//Redefine avg
        		for (i = 0; i < length; i++)
        		{
        			sum = sum + data[i];
        		}
        		avg = sum / (double) length;

        		//Redefine max
        		max = max + factor;

        }
        else
        {
        		cout<<"Input error: please choose a value between -1000 and 1000."<<endl;
        }
}





void Signal::Scale()
{
	int i, factor;
	double sum;

	cout << "Input a scaling factor: ";
	cin >> factor;

    if(factor <= 1000 && factor >= -1000)
    {
    	for(i = 0; i < length; i++)
    		{
    			data[i] = data[i] * factor;
    		}

    		//Redefine avg
    		for (i = 0; i < length; i++)
    		{
    			sum = sum + data[i];
    		}
    		avg = sum / (double) length;

    		//Redefine max
    		max = max * factor;
    }
    else
    {
    		cout<<"Input error: please choose a value between -1000 and 1000."<<endl;
    }
}


void Signal::Center()
{
	int i;
	double sum = 0;

	for(i = 0; i < length; i++)
	{
		data[i] = data[i] - avg;
	}

	//Redefine avg
	for (i = 0; i < length; i++)
	{
		sum = sum + data[i];
	}
	avg = sum / (double) length;

	//Redefine max
	max = data[0];

	for (i = 0; i < length; i++)
	{
		if (data[i] > max)
			max = data[i];
	}
}





void Signal::Normalize()
{
	int i;
	double sum;

	for(i = 0; i < length; i++)
	{
			data[i] = data[i] / max;
	}

	//Redefine avg
	for (i = 0; i < length; i++)
	{
		sum = sum + data[i];
	}
	avg = sum / (double) length;

	//Redefine max
	max = 1;
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

	if(argc == 1)
		{
			sig2 = new Signal();
		}
	else if(argv[1][1] == 'n')
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
			cout<<"ERROR: NO INPUT CASE"<<endl;
			//cout<<"test"<<endl;
			//sig2 = new Signal();

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
		else if(choice != 7)
		{
			cout<<"Improper choice"<<endl;
		}
	}

	delete sig2;
}
