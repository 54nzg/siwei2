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
	char* m_strCarNum;// 车牌
	int m_fSpeed;//车速（km/h）
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
	char* station, * location;//桩号	地点
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
		cout << "时间\t桩号\t地点\t车速（km/h）\t车牌" << endl;
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
	string temp1,temp2;//存取2021/4/25和15:25再分配给各变量，加快读取速度
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
		cout << "没有相关数据文件！" << endl;
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

	//cout << "请输入桩号：" << endl;
	//cin >> station;
	//cout << "请输入地点：" << endl;
	//cin >> location;
	TrafficFlowDetectionSystem temp(station,location);
	cout << "是否导入数据文件？（1：是，2：否）" << endl;
	int flag;
	cin >> flag;
	if (flag)
	{
		string filename = location + "车流.txt";
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
			//要改的内容
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
			//要改的内容
			break;
		}
	}
}
int main()
{
	importInformation("青龙立交车流.txt");

	return 0;
}