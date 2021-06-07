#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

class TrafficRecord
{
private:
	int year, month, day, hour, minute;
	char* m_strCarNum;// ����
	int m_fSpeed;//���٣�km/h��
public:
	TrafficRecord(int year, int month, int day, int hour, int minute, string m_strCarNum = NULL, int m_fSpeed = 0)
	{
		this->year = year;
		this->month = month;
		this->day = day;
		this->hour = hour;
		this->minute = minute;
		this->m_strCarNum = new char[m_strCarNum.length() + 1];
		strcpy(this->m_strCarNum, m_strCarNum.c_str());
		this->m_fSpeed = m_fSpeed;
	}
	TrafficRecord(){}
	void showTime()
	{
		cout << year << "/" << month << "/" << day << " " << hour << ":" << minute << "\t";
	}
	void showTraffic()
	{
		cout << m_fSpeed << "\t" << m_strCarNum << endl;
	}
	friend class TrafficFlowDetectionSystem;
};
class Traffic {
protected:
	char* station, * location;//׮��	�ص�
};
class TrafficFlowDetectionSystem : protected Traffic{
private:
	vector<TrafficRecord> trd;
public:
	TrafficFlowDetectionSystem(string station, string location)
	{
		this->station = new char[station.length() + 1];
		strcpy(this->station, station.c_str());
		this->location = new char[location.length() + 1];
		strcpy(this->location, location.c_str());
	}
	TrafficFlowDetectionSystem(){}
	void TFDSbyStationAndLocation (string station,string location)
	{
		this->station = new char[station.length() + 1];
		strcpy(this->station, station.c_str());
		this->location = new char[location.length() + 1];
		strcpy(this->location, location.c_str());
	}
	void TFDSbyTrafficRecord(int year, int month, int day, int hour, int minute, string m_strCarNum = NULL, int m_fSpeed = 0)
	{
		TrafficRecord temp(year, month, day, hour, minute, m_strCarNum, m_fSpeed);
		trd.push_back(temp);
	}
	void show()
	{
		cout << "ʱ��\t׮��\t�ص�\t���٣�km/h��\t����" << endl;
		cout << "time\tstation\tlocation\tm_fSpeed\tm_strCarNum" << endl;
		vector<TrafficRecord>::iterator it;
		for (it = trd.begin(); it != trd.end(); it++)
		{
			it->showTime();
			cout << station << "\t" << location << "\t";
			it->showTraffic();
		}
	}
	char* getStation()
	{
		return station;
	}
	char* getLocation()
	{
		return location;
	}
	friend void updataTFDByStation(string station);
	friend void updataTFDBylocation(string location);
	friend void importInformation(string filename);
};


vector<TrafficFlowDetectionSystem> TFD;
void importInformation(string filename)
{
	ifstream ipt;
	int year, month, day,hour,minute, m_fSpeed;
	string station,location,m_strCarNum;
	string temp1,temp2;//��ȡ2021/4/25��15:25�ٷ�������������ӿ��ȡ�ٶ�
	TrafficFlowDetectionSystem t;
	ipt.open(filename, ios::in);
	if (ipt.is_open())
	{
		getline(ipt, temp1);
		getline(ipt, temp1);
		if(!ipt.eof())
		{
			ipt >> temp1 >> temp2 >> station >> location >> m_fSpeed >> m_strCarNum;
			istringstream iss(temp1);
			getline(iss ,temp1, '/');
			year=stoi(temp1);
			getline(iss, temp1, '/');
			month=stoi(temp1);
			getline(iss, temp1, '/');
			day=stoi(temp1);
			istringstream isss(temp2);
			getline(isss, temp2, ':');
			hour=stoi(temp2);
			getline(isss, temp2, ':');
			minute=stoi(temp2);
			t.TFDSbyStationAndLocation(station, location);
			t.TFDSbyTrafficRecord(year, month, day, hour, minute, m_strCarNum, m_fSpeed);
		}
		while (!ipt.eof())
		{
			ipt >> temp1 >> temp2 >> station >> location >> m_fSpeed >> m_strCarNum;
			istringstream iss(temp1);
			getline(iss, temp1, '/');
			year = stoi(temp1);
			getline(iss, temp1, '/');
			month = stoi(temp1);
			getline(iss, temp1, '/');
			day = stoi(temp1);
			istringstream isss(temp2);
			getline(isss, temp2, ':');
			hour = stoi(temp2);
			getline(isss, temp2, ':');
			minute = stoi(temp2);
			t.TFDSbyTrafficRecord(year, month, day, hour, minute, m_strCarNum, m_fSpeed);
		}
		TFD.push_back(t);
		ipt.close();
	}
	else
	{
		cout << "û����������ļ���" << endl;
	}
}

int searchTFDByStation(string station)
{
	for (int i = 0; i < TFD.size(); i++)
	{
		if (TFD[i].getStation() == station)
		{
			return i;
			break;
		}
	}
	return -1;
}
int searchTFDByLocation(string location)
{
	for (int i = 0; i < TFD.size(); i++)
	{
		if (TFD[i].getLocation() == location)
		{
			return i;
			break;
		}
	}
	return -1;
}
void addTFD(string station,string location)
{

	//cout << "������׮�ţ�" << endl;
	//cin >> station;
	//cout << "������ص㣺" << endl;
	//cin >> location;
	TrafficFlowDetectionSystem temp(station,location);
	cout << "�Ƿ��������ļ�����1���ǣ�2����" << endl;
	int flag;
	cin >> flag;
	if (flag)
	{
		string filename = location + "����.txt";
		importInformation(filename);
	}
}
void deleteTFDByStation(string station)
{
	vector<TrafficFlowDetectionSystem>::iterator it;
	for (it = TFD.begin(); it != TFD.end(); it++)
	{
		if (it->getStation() == station)
		{
			TFD.erase(it);
			break;
		}
	}
}
void deleteTFDBylocation(string location)
{
	vector<TrafficFlowDetectionSystem>::iterator it;
	for (it = TFD.begin(); it != TFD.end(); it++)
	{
		if (it->getLocation() == location)
		{
			TFD.erase(it);
			break;
		}
	}
}
void updataTFDByStation(string station)
{
	vector<TrafficFlowDetectionSystem>::iterator it;
	for (it = TFD.begin(); it != TFD.end(); it++)
	{
		if (it->station == station)
		{
			//Ҫ�ĵ�����
			break;
		}
	}
}
void updataTFDBylocation(string location)
{
	vector<TrafficFlowDetectionSystem>::iterator it;
	for (it = TFD.begin(); it != TFD.end(); it++)
	{
		if (it->location == location)
		{
			//Ҫ�ĵ�����
			break;
		}
	}
}
int main()
{
	importInformation("������������.txt");

	return 0;
}