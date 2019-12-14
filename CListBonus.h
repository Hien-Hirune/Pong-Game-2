#pragma once
#include "CBonus.h"
#include "CBar.h"
#include "BrickMatrix.h"
#include <vector>

class CListBonus
{
private:
	vector<CBonus> List;
public:
	void setList(vector<CBonus> a)
	{
		List = a;
	}
	vector<CBonus> getList() {
		return List;
	}
	int getSize() {
		return List.size();
	}
	void addBonus(CBonus);
	void Erase();
	void Move();
	void Delete(int);
	void draw();
	void logic(CBar&, int&, BrickMatrix&, int&);
	void checkBonus(int, int&, BrickMatrix&, int&);
	CListBonus();
	~CListBonus();
};

