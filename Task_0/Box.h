#pragma once
#include<iostream>
#include<algorithm>
namespace Task0 {
	class Box {
	private:
		int length;
		int width;
		int height;
		double weight;
		int value;
	public:
		Box();
		Box(int, int, int, double, int);
		static int valueSum(Box[], int);
		static bool correctBoxes(Box[], int, int);
		static double maxCertainBoxesWeight(Box[], int, double);
		static bool boxesCanBeInserted(Box[], int);
		int getLength();
		int getWidth();
		int getHeight();
		double getWeight();
		int getValue();
		void setLength(int);
		void setWidth(int);
		void setHeight(int);
		void setWeight(double);
		void setValue(int);
		friend bool operator== (Box, Box);
		friend std::ostream& operator<< (std::ostream&, const Box&);
		friend std::istream& operator>> (std::istream&, Box&);
	};
}