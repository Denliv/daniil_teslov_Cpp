#include "pch.h"
#include "Container.h"
namespace Task0 {
	Container::Container() {
		this->length = 0;
		this->width = 0;
		this->height = 0;
		this->maxWeight = 0;
	}

	Container::Container(int length, int width, int height, double maxWeight) {
		this->length = length;
		this->width = width;
		this->height = height;
		this->maxWeight = maxWeight;
	}

	int Container::numberOfBoxes() {
		return this->boxes.size();
	}

	double Container::getWeight() {
		double weight = 0;
		for (Box i : this->boxes) {
			weight += i.getWeight();
		}
		return weight;
	}

	int Container::getValue() {
		int value = 0;
		for (Box i : this->boxes) {
			value += i.getValue();
		}
		return value;
	}

	Box Container::getBox(int x) {
		return this->boxes[x];
	}

	void Container::addBox(Box box) {
		Box* boxes = new Box[numberOfBoxes() + 2];
		for (int i = 0; i < numberOfBoxes(); i++) {
			boxes[i] = this->boxes[i];
		}
		boxes[numberOfBoxes()] = Box(this->length, this->width, this->height, 0.0, 0);
		boxes[numberOfBoxes() + 1] = box;
		if (box.getWeight() + this->getWeight() <= maxWeight
			&& Box::boxesCanBeInserted(boxes, numberOfBoxes() + 2)) {
			this->boxes.push_back(box);
			delete[] boxes;
		}
		else {
			delete[] boxes;
			throw std::overflow_error("The box exceed the container's max weight\n");
		}
	}

	void Container::deleteBox(int x) {
		x < numberOfBoxes() && x >= 0
			? boxes.erase(boxes.begin() + x)
			: throw std::overflow_error("The container don't have box with such number\n");
	}

	Box& Container::operator[] (int x) {
		return boxes[x];
	}

	std::ostream& operator<< (std::ostream& out, const Container& container) {
		return out
			<< container.length << " "
			<< container.width << " "
			<< container.height << " "
			<< container.maxWeight;
	}

	std::istream& operator>> (std::istream& in, Container& container) {
		return in
			>> container.length
			>> container.width
			>> container.height
			>> container.maxWeight;
	}
}