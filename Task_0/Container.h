#pragma once
#include<iostream>
#include"Box.h"
#include<vector>
namespace Task0 {
	class Container {
	private:
		std::vector<Box> boxes;
		int length;
		int width;
		int height;
		double maxWeight;
	public:
		Container();
		Container(int, int, int, double);
		int numberOfBoxes();
		double getWeight();
		int getValue();
		Box getBox(int);
		void addBox(Box);
		void deleteBox(int);
		Box& operator[] (int);
		friend std::ostream& operator<< (std::ostream&, const Container&);
		friend std::istream& operator>> (std::istream&, Container&);
	};
}
