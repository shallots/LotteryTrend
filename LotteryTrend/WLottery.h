#include <iostream>
#include <vector>

#define NOTHING	-1
#define INIT	0
#define SAVED	1
#define MODIFY	2

using namespace std; 
typedef struct{
	int num;
	int b;
	int s;
	int g;
}WelfareLot;

class WLottery{
private:
	int count;
	int status;
public:
	WLottery();
	~WLottery(); 
	
	vector<WelfareLot> samples;
	int specialnum;
	int historysum;
	
	int addSample(WelfareLot sample);
	bool delSample(int num); 	
	int importSamples(char *);
	int saveSamples();
	void printSamples();

	int getCount();
	WelfareLot* getSample(int num);
	int getSampleIndex(int num);
	int getSampleIndex(WelfareLot w); 

	bool setStatus(int istatus);
	int getStatus();
	int getMax();

	int uniqueSamples();
	int checkForcast(); 
	bool forcastTrend(vector<int*>&);

};
