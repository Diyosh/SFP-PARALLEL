//PARALLEL AND DISTRIBUTED COMPUTING SEMIFINAL PROJECT
//JOSHUA B. MENDOZA
//KIM DELA CRUZ TAPIA
//BSCS2A
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<sstream>

using namespace std;

double Total_Lane_Queue_Time;

struct Customer {
	int items;
	string pref_pack;
	int num_pack;
	string pref_pay;
	string cash_type;
	int i = 0;
};

 Customer getData(string line)
{
	size_t pos = 0;
	size_t npos = -1;
	string delimiter = " ";
	string data[5] = {" "};
	int data_index = 0;

	while ((pos = line.find(delimiter)) != npos) {
	    data[data_index] = line.substr(0, pos);
	    line.erase(0, pos + delimiter.length());
	    data_index++;
	}
	data[data_index] = line;

	stringstream ss;

	Customer temp;

	for (int i = 0; i < 5; i++) {
		string d = *(data + i);
		if (i == 0 || i == 2) {
			ss << d;
			if (i == 0) {
				ss >> temp.items;
			} else if (i == 2) {
				ss >> temp.num_pack;
			}
			ss.clear();
			ss.str("");
		} else if (i == 1) {
			temp.pref_pack = d;
		} else if (i == 3) {
			temp.pref_pay = d;
		} else if (i == 4) {
			temp.cash_type = d;
		}
	}
	return temp;
}

void print_input(Customer n, int index)
{

	float Total_Decarting_Time;
	float Total_Scanning_Time;
	float Total_Packing_Time;
	float Total_Paying_Time;
	float Total_Reciept_Printing_Time;
	int Idle_Time;
	float Total_Customer_Queue_Time;


	int cust_num;

	cust_num = index + 1;

	cout << "Customer #" << cust_num<< endl;
	cout << "No. of Cart Items: " << n.items << endl;
	cout << "Preferred Packaging: " << n.pref_pack << endl;
	cout << "Number of Box: " << n.num_pack << endl;

	if(n.cash_type == "e"){
		cout << "Preferred Payment Method: " << n.pref_pay << " (exact) " << endl;
	}
	else if(n.cash_type == "ne"){
		cout << "Preferred Payment Method: " << n.pref_pay << " (not exact) " << endl;
	}
	else {
		cout << "Preferred Payment Method: " << n.pref_pay << endl;
	}

	cout << "***********************************************\n";

	Total_Decarting_Time = n.items * 0.5;
	cout << "Total De-Carting Time: " <<  Total_Decarting_Time << endl;

	Total_Scanning_Time =  n.items * 0.5;
	cout << "Total Scanning Time: " <<  Total_Scanning_Time << endl;

	if(n.pref_pack == "box"){
		Total_Packing_Time = (n.items * 0.50) + (n.num_pack * 10);
		cout << "Total Packing Time: " <<  Total_Packing_Time << endl;
	}
	else if (n.pref_pack == "bag") {
		Total_Packing_Time = (n.items * 0.50) + (n.num_pack * 5);
		cout << "Total Packing Time: " <<Total_Packing_Time << endl;
	}

	if(n.pref_pay == "cash"){
		if(n.cash_type == "e"){
			Total_Paying_Time = 15;
			cout << "Total Paying Time: " << Total_Paying_Time << endl;
		}
		else if(n.cash_type == "ne"){
			Total_Paying_Time = 20;
			cout << "Total Paying Time: " << Total_Paying_Time << endl;
		}
	}
	if(n.pref_pay == "digital"){
		Total_Paying_Time = 15;
		cout << "Total Paying Time: " << Total_Paying_Time << endl;
	}

	Total_Reciept_Printing_Time = (n.items * 0.3) + 2;
	cout << "Total Receipt Printing Time: " << Total_Reciept_Printing_Time << endl;

	if(index == 0){
		Idle_Time = 0;
		cout << "Idle Time: " <<  Idle_Time << endl;
	} else if(index > 0){
		Idle_Time = 3;
		cout << "Idle Time: " <<  Idle_Time << endl;
	}
	Total_Customer_Queue_Time = Total_Decarting_Time + Total_Scanning_Time + Total_Packing_Time + Total_Paying_Time + Total_Reciept_Printing_Time + Idle_Time;
	cout << "Total Customer-Queue Time: " << Total_Customer_Queue_Time << endl;

	cout << "==============================================" << endl;

    Total_Lane_Queue_Time += Total_Customer_Queue_Time;

}

int main()
{
	ifstream in_stream;

	in_stream.open("Sheesh.in");

	if(in_stream.fail())
    {
        cout<<"Input file opening failed.\n";
        exit(1);
    }

	int customer_number;

	in_stream >> customer_number;
    cout << "-----------------------------------------------\n";
	cout << "No. of Customers:: " << customer_number << endl;
	cout << "-----------------------------------------------\n";

	Customer queue[customer_number];

	string line;

	int index = 0;
	while (getline(in_stream, line)) {
		if (line.length() > 0) {
			queue[index] = getData(line);
			print_input(queue[index], index);
			index++;
		}

}
    cout << "Total Lane Queue Time: " << Total_Lane_Queue_Time;
	return 0;
}
