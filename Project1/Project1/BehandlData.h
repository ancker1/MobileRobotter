#pragma once
class BehandlData
{
public:
	BehandlData();
	float goertzelFilter(int,int,int,float*);
	void hammingWindow(int, float*);
	~BehandlData();
};

