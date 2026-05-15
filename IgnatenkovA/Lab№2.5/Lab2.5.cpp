#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::cerr;

class Darray {
private:
	int size;
	double* data;

public:
	Darray() : size(0), data(nullptr) {}
	Darray(int sz) : size(0), data(nullptr) {
		if (sz < 0) {
			cerr << "size cannot be negative.\n";
			return;
		}
		if (sz == 0) return;
		size = sz;
		data = new double[sz];
		for (int i = 0; i < sz; ++i) {
			data[i] = 0.0;
		}
	}
	~Darray() {
		delete[] data;
	}
	Darray(const Darray& other) : size(other.size), data(nullptr) {
		if (size == 0) return;
		data = new double[size];
		for (int i = 0; i < size; ++i) {
			data[i] = other.data[i];
		}
	}
	Darray& operator=(const Darray& other) {
		if (this != &other) {
			delete[] data;
			size = other.size;
			data = nullptr;
			if (size == 0) return *this;

			data = new double[size];
			for (int i = 0; i < size; ++i) {
				data[i] = other.data[i];
			}
		}
		return *this;
	}
	int getSize() const {
		return size;
	}
	void setSize(int newSize) {
		if (newSize < 0) {
			cerr << "Error: size cannot be negative.\n";
			return;
		}
		if (newSize == size) return;
		if (newSize == 0) {
			delete[] data;
			data = nullptr;
			size = 0;
			return;
		}
		double* newData = new double[newSize];
		int limit = (size < newSize) ? size : newSize;
		for (int i = 0; i < limit; ++i) {
			newData[i] = data[i];
		}
		for (int i = limit; i < newSize; ++i) {
			newData[i] = 0.0;
		}
		delete[] data;
		data = newData;
		size = newSize;
	}
	double getElement(int index) const {
		if (index < 0 || index >= size) {
			cerr << "Error: index out of range.\n";
			return NAN;
		}
		return data[index];
	}
	void setElement(int index, double value) {
		if (index < 0 || index >= size) {
			cerr << "Error: index out of range.\n";
			return;
		}
		data[index] = value;
	}
	double getMin() const {
		if (size == 0) {
			cerr << "Error: cannot find min in empty array.\n";
			return NAN;
		}
		double minVal = data[0];
		for (int i = 1; i < size; ++i) {
			if (data[i] < minVal) {
				minVal = data[i];
			}
		}
		return minVal;
	}
	bool isSorted() const {
		if (size <= 1) return true;
		for (int i = 0; i < size - 1; ++i) {
			if (data[i] > data[i + 1]) {
				return false;
			}
		}
		return true;
	}
	Darray getSubarray() const {
		int newSize = size / 2;
		Darray result(newSize);
		for (int i = 0, j = 1; j < size; ++i, j += 2) {
			result.data[i] = data[j];
		}
		return result;
	}
	void print() const {
		if (size == 0) {
			cout << "[empty array]\n";
			return;
		}
		cout << "[";
		for (int i = 0; i < size; ++i) {
			cout << data[i];
			if (i < size - 1) {
				cout << ", ";
			}
		}
		cout << "]\n";
	}
};

int main() {
	Darray arr(0);
	int choice;
	while (true) {
		cout << "1. Set array size\n";
		cout << "2. Get array size\n";
		cout << "3. Set element by index\n";
		cout << "4. Get element by index\n";
		cout << "5. Find minimum element\n";
		cout << "6. Check if array is sorted\n";
		cout << "7. Extract subarray with odd index\n";
		cout << "8. Print array\n";
		cout << "9. Exit\n";
		cout << "Choice: ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Invalid input. Please enter a number.\n";
			continue;
		}
		switch (choice) {
		case 1: {
			int sz;
			cout << "Enter new size: ";
			if (cin >> sz) arr.setSize(sz);
			else { cin.clear(); cin.ignore(32767, '\n'); }
			break;
		}
		case 2: {
			cout << "Current size: " << arr.getSize() << "\n";
			break;
		}
		case 3: {
			int idx; double val;
			cout << "Enter index and value: ";
			if (cin >> idx >> val) arr.setElement(idx, val);
			else { cin.clear(); cin.ignore(32767, '\n'); }
			break;
		}
		case 4: {
			int idx;
			cout << "Enter index: ";
			if (cin >> idx) cout << "Value at index " << idx << ": " << arr.getElement(idx) << "\n";
			else { cin.clear(); cin.ignore(32767, '\n'); }
			break;
		}
		case 5: {
			double m = arr.getMin();
			if (std::isnan(m)) cout << "Array is empty.\n";
			else cout << "Minimum element: " << m << "\n";
			break;
		}
		case 6: {
			cout << "Is the array sorted? " << (arr.isSorted() ? "Yes" : "No") << "\n";
			break;
		}
		case 7: {
			Darray oddSub = arr.getSubarray();
			cout << "Subarray with odd index: ";
			oddSub.print();
			break;
		}
		case 8: {
			cout << "Array contents: ";
			arr.print();
			break;
		}
		case 9: {
			cout << "Exiting program.\n";
			return 0;
		}
		default: {
			cout << "Invalid menu option. Try again.\n";
			break;
		}
		}
	}
}