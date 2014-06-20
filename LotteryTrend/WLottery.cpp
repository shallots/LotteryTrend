#include "stdafx.h"
#include"WLottery.h"

WLottery::WLottery(){
	count = 0;
	specialnum = 0;
	historysum = 0;
	status = NOTHING;
}

WLottery::~WLottery(){
	count = 0;
	specialnum = 0;
	historysum = 0;
	status = NOTHING;
	if(status == MODIFY){
		saveSamples();
	}
	samples.clear();	
}

int WLottery::getCount(){
	return samples.size();
}

WelfareLot* WLottery::getSample(int num){ 
	WelfareLot *ptr = new WelfareLot;
	ptr->num = -1;
	int flag = 0;
	for(vector<WelfareLot>::iterator it=samples.begin(); it!=samples.end();it++){
		if(num == it->num){
			ptr->num = it->num;
			ptr->b = it->b;
			ptr->s = it->s;
			ptr->g = it->g;
			flag = 1;
			break;
		}
	}
	if(flag == 1){
		return ptr;
	}
	delete ptr;
	return NULL;
}
int WLottery::getMax(){
	int index = getCount()-1;
	if(index>0)
		return (samples.begin()+index)->num;
	return 0;
}

int WLottery::getSampleIndex(int num){
	if(num<1)
		return -1;
	int n=0;
	for(vector<WelfareLot>::iterator it=samples.begin(); it!=samples.end();it++){
		if(num == it->num)
			break;
		n++;
	}
	if(n >= getCount())
		return -2;
	return n;
}

int WLottery::getSampleIndex(WelfareLot sample){
	return getSampleIndex(sample.num);
}

int WLottery::addSample(WelfareLot sample){
	int index = 0;
	int flag = 0;
	for(vector<WelfareLot>::iterator it=samples.begin(); it!=samples.end();it++){
		if(sample.num == it->num){
			return -1;
		}
		if(sample.num < it->num){
			samples.insert(it,sample);
			status = MODIFY;
			flag = 1;
			break;
		}
		index++;
	}
	if(!flag){
		samples.push_back(sample);
		status = MODIFY;
	}
	// 存数据
	saveSamples();
	return index;	 
}

bool WLottery::delSample(int num){
	int flag = 0;
	for(vector<WelfareLot>::iterator it=samples.begin(); it!=samples.end();it++){
		if(num == it->num){
			samples.erase(it);
			status = MODIFY;
			flag = 1;
			break;
		}
	}
	if(1 == flag)
		return true;
	return false;
}

int WLottery::importSamples(char *path){
	FILE *fp;
	fopen_s(&fp,path,"r");
	if(NULL == fp){
		//printf("open file failed.\n");
		return -1;
	}
	samples.clear();
	int count = 0;
	while(!feof(fp)){
		WelfareLot tmp;
		memset(&tmp,0,sizeof(tmp));
		fscanf_s(fp,"%d%d%d%d",&tmp.num,&tmp.b,&tmp.s,&tmp.g);
		if(tmp.num!=0){
			if(addSample(tmp)!=-1){
				status = MODIFY;
				count++;
			}
		}
	}
	fclose(fp);
	//printf("IMPORT TOTAL: %d\n",count);
	return count;
} 

int WLottery::saveSamples(){
	if(status == SAVED)
		return 0;
	FILE *fp;
	fopen_s(&fp,"3Ddata.txt","w");
	if(NULL == fp){
		//printf("open file failed.\n");
		return -1;
	}
	int count = 0;	
	for(vector<WelfareLot>::iterator it=samples.begin(); it!=samples.end(); it++){
		fprintf_s(fp,"%d %d %d %d\n",it->num,it->b,it->s,it->g);
		count++;
	}
	status = SAVED;
	fclose(fp);
	return count;
}

int WLottery::checkForcast(){
	int index = getSampleIndex(specialnum);
	if(index < 0)
		return -1;				// 没有找到指定的3d彩票期号 
	if((index+1)<historysum)
		return 0;				// 往期数据不足 
	return 1; 
}

bool WLottery::setStatus(int istatus){
	if(istatus>=-1&&istatus<=2){
		status = istatus;
		return true;
	}
	return false;
}
int WLottery::getStatus(){
	return status;
}
bool addUnit(int* &arr, int unit){
	int flag = 0;
	int i = 0;
	for(i=0; i<10;i++){
		if((arr[i])==unit){
			break;
		}
		if(arr[i]>unit){
			for(int j=9; j>i;j--)
				arr[j]=arr[j-1];
			flag = 1;
			break;
		}
		if(-1 == arr[i]){
			flag = 1;
			break;
		}
	} 
	if(flag){
		arr[i]=unit;
		return true;
	}
	return false;
}

void initIntArray(int* &arr,int length = 10){
	for(int i = 0; i<length; i++)
		arr[i] = -1;
}

bool WLottery::forcastTrend(vector<int*>& trends){
	WelfareLot *ptr = getSample(specialnum);
	if(NULL == ptr)
		return false;
	trends.clear();

	int end = getSampleIndex(specialnum);
	int start = end>historysum?(end-historysum):0;	
	
	if(end<1)
		return false;
	int *pb = new int[10];
	initIntArray(pb);
	
	int *ps = new int[10];
	initIntArray(ps);

	int *pg = new int[10];
	initIntArray(pg);
	
	int ge = ptr->g;
	int si = ptr->s;
	int bi = ptr->b;  
	
	vector<WelfareLot>::iterator it=samples.begin(); 
	for(int i=start; i<end; i++){
		vector<WelfareLot>::iterator tmp = it+i;
		// 百位 
		if(bi == tmp->b){
			if(i>0)
				addUnit(pb,(tmp-1)->b);
			addUnit(pb,(tmp+1)->b);
		}
		if(bi == tmp->s){
			if(i>0)
				addUnit(pb,(tmp-1)->s);
			addUnit(pb,(tmp+1)->s);
		}
		// 十位
		if(si == tmp->b){
			if(i>0)
				addUnit(ps,(tmp-1)->b);
			addUnit(ps,(tmp+1)->b);
		}
		if(si == tmp->s){
			if(i>0)
				addUnit(ps,(tmp-1)->s);
			addUnit(ps,(tmp+1)->s);
		}
		// 个位 
		if(ge == tmp->s){
			if(i>0)
				addUnit(pg,(tmp-1)->s);
			addUnit(pg,(tmp+1)->s);
		}
		if(ge == tmp->g){
			if(i>0)
				addUnit(pg,(tmp-1)->g);
			addUnit(pg,(tmp+1)->g);
		}
	}
	addUnit(pb,(it+end-1)->b);
	addUnit(ps,(it+end-1)->s);
	addUnit(pg,(it+end-1)->g);

	addUnit(pb,bi);
	addUnit(ps,si);
	addUnit(pg,ge);

	trends.push_back(pb);
	trends.push_back(ps);
	trends.push_back(pg);
	
	return true;	
}
int WLottery::uniqueSamples(){
	int count = 0;
	for(vector<WelfareLot>::iterator it = samples.begin(); it!=samples.end(); it++)
		for(vector<WelfareLot>::iterator ita = samples.begin(); ita!=samples.end();){
			if(it == ita){
				ita++;
				continue;
			}
			if(it->num == ita->num)
			{
				ita = samples.erase(ita);
				count++;
				continue;
			}
			ita++;
		}
	return count;
}
void WLottery::printSamples(){
	printf("\nSAMPLES:\n");
	for(vector<WelfareLot>::iterator it = samples.begin(); it!=samples.end(); it++)
	{
		printf("%d --- %d%d%d\n",it->num,it->b,it->s,it->g);
	}
	printf("\n");
}