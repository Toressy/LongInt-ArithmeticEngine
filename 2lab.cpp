#include<iostream>

using namespace std;

const int minN = 4;

class longNumber
{
	struct number
	{
		number* left;
		int num;
		number* right;
	};

	number* head = nullptr;
	number* tail = nullptr;

public:

	int length;s
	bool isNeg;
	int nSystem;

	void insertLeft(int data)
	{
		if (head == nullptr)
		{
			head = new number;
			head->num = data;
			head->left = head->right = nullptr;
			tail = head;
			length = 1;
			return;
		}
		number* temp = new number;
		temp->num = data;
		temp->right = head;
		temp->left = nullptr;
		head->left = temp;
		head = temp;
		length++;
	}

	void insertRight(int data)
	{
		if (head == nullptr)
		{
			head = new number;
			head->num = data;
			head->left = head->right = nullptr;
			tail = head;
			length = 1;
			return;
		}
		number* temp = new number;
		temp->left = tail;
		temp->right = nullptr;
		temp->num = data;
		tail->right = temp;
		tail = temp;
		length++;
	}

	void reInsert(string s)
	{
		if (head == nullptr) return;
		length--;
		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
		}
		if (s == "l")
		{
			head = head->right;
			delete head->left;
			head->left = nullptr;
		}
		else
		{
			tail = tail->left;
			delete tail->right;
			tail->right = nullptr;
		}

	}

	void setNumber()
	{
		del();
		head = tail = nullptr;
		length = 0;
		isNeg = false;
		nSystem = 10;
	}

	void setNumber(string data, int nSystem)
	{
		del();
		this->nSystem = nSystem;
		isNeg = data[0] == '-';
		for (int i = 0 + isNeg; i < data.size(); i++) insertRight(data[i] - '0');
	}

	void setNumber(longNumber& other)
	{
		del();
		this->nSystem = nSystem;
		if (other.length == 0)
		{
			head = tail = nullptr;
			length = 0;
			isNeg = false;
			return;
		}
		isNeg = other.isNeg;
		number* temp = other.head;
		for (int i = 0; i < other.length; i++)
		{
			insertRight(temp->num);
			temp = temp->right;
		}
	}

	void setNumber(long long num, int nSystem)
	{
		del();
		this->nSystem = nSystem;
		if (num == 0)
		{
			head = new number;
			length = 1;
			head->num = 0;
			head->left = head->right = nullptr;
			tail = head;
			isNeg = false;
			return;
		}

		if (num < 0)
		{
			isNeg = true;
			num *= -1;
		}

		while (num > 0)
		{
			insertLeft(num % nSystem);
			num /= nSystem;
		}
	}

	longNumber()
	{
		setNumber();
	}

	longNumber(string data, int nSystem)
	{
		setNumber(data, nSystem);
	}

	longNumber(const longNumber& other)
	{
		this->nSystem = other.nSystem;
		isNeg = other.isNeg;
		number* temp = other.head;
		for (int i = 0; i < other.length; i++)
		{
			insertRight(temp->num);
			temp = temp->right;
		}
	}

	longNumber(long long number, int nSystem)
	{
		setNumber(number, nSystem);
	}

	void toNSystem(int nSystem)
	{

	}

	longNumber operator-()
	{
		longNumber res(*this);
		res.isNeg = !res.isNeg;
		return longNumber(res);
	}

	bool operator >(longNumber n)
	{
		if (isNeg && !n.isNeg) return false;
		if (!isNeg && n.isNeg) return true;
		if (isNeg && n.isNeg) return -n > -(*this);

		if (length != n.length) return length > n.length;

		for (int i = 0; i < length; i++)
		{
			if ((*this)[i] != n[i]) return (*this)[i] > n[i];
		}
		return false;
	}

	bool operator!=(longNumber& n)
	{
		if (length != n.length) return true;
		for (int i = 0; i < length; i++)
		{
			if ((*this)[i] != n[i]) return true;
		}
		return false;
	}

	bool operator==(longNumber& n)
	{
		return !(*this != n);
	}

	bool operator<(longNumber& n)
	{
		return n > *this;
	}

	friend ostream& operator<< (ostream& out, longNumber& n);
	friend istream& operator>> (istream& in, longNumber& n);

	void print()
	{
		if (isNeg) cout << "-";
		number* temp = head;
		for (int i = 0; i < length; i++)
		{
			cout << temp->num;
			temp = temp->right;
		}
	}

	int& operator[](const int index)
	{
		if (index < length)
		{
			number* temp = head;
			for (int i = 0; i < index; i++)
			{
				temp = temp->right;
			}
			return temp->num;
		}
	}

	longNumber& operator=(longNumber n)
	{
		setNumber(n);
		return (*this);
	}

	longNumber operator-(longNumber n)
	{
		if (n.isNeg) return *this + (-n);
		if (nSystem != n.nSystem) n.toNSystem(nSystem);
		if (n > *this) return -(n - *this);
		longNumber res;
		res.setNumber();
		number* tempL = tail;
		number* tempR = n.tail;
		int over = 0;
		while (tempR != nullptr || tempL != nullptr)
		{
			if ((tempL != nullptr ? tempL->num : 0) - over >= (tempR != nullptr ? tempR->num : 0))
			{
				res.insertLeft((tempL != nullptr ? tempL->num : 0) - over - (tempR != nullptr ? tempR->num : 0));
				over = 0;
			}
			else
			{
				res.insertLeft((tempL != nullptr ? tempL->num : 0) - over + nSystem - (tempR != nullptr ? tempR->num : 0));
				over = 1;
			}
			tempL = tempL != nullptr ? tempL->left : nullptr;
			tempR = tempR != nullptr ? tempR->left : nullptr;
		}

		while (res[0] == 0 && res.length > 1) res.reInsert("l");

		return longNumber(res);
	}

	longNumber operator+(longNumber n)
	{
		if (nSystem != n.nSystem) n.toNSystem(nSystem);
		if (!isNeg && n.isNeg) return ((*this) - (-n));
		if (isNeg && !n.isNeg) return (n - (-(*this)));
		longNumber res;
		res.isNeg = n.isNeg;
		number* tempL = tail;
		number* tempR = n.tail;
		int over = 0;
		while (tempL != nullptr || tempR != nullptr)
		{
			res.insertLeft(((tempL != nullptr ? tempL->num : 0) + (tempR != nullptr ? tempR->num : 0)) % nSystem + over);
			over = ((tempL != nullptr ? tempL->num : 0) + (tempR != nullptr ? tempR->num : 0)) / nSystem;
			tempL = tempL != nullptr ? tempL->left : nullptr;
			tempR = tempR != nullptr ? tempR->left : nullptr;
		}

		if (over > 0) res.insertLeft(over);

		return longNumber(res);
	}



	int toInt()
	{
		int num = 0;
		int d = 1;

		number* temp = tail;

		for (int i = 0; i < length; i++)
		{
			num += temp->num * d;
			d *= nSystem;
			temp = temp->left;
		}
		if (isNeg) num *= -1;
		return num;
	}

	longNumber createPart(int pos1, int pos2)
	{
		longNumber res;
		for (int i = pos1; i <= pos2; i++) res.insertRight((*this)[i]);
		return longNumber(res);
	}

	void addZeros(int n)
	{
		for (int i = 0; i < n; i++) insertRight(0);
	}

	void demZeros(int n)
	{
		for (int i = 0; i < n; i++) reInsert("r");
	}

	longNumber karatsyba(longNumber n)
	{
		if (nSystem != n.nSystem) n.toNSystem(nSystem);
		if (n > *this) return n.karatsyba(*this);

		if (length <= minN && n.length <= minN)
		{
			longNumber res(toInt() * n.toInt(), nSystem);
			return longNumber(res);
		}

		int nZeros = this->length % 2;
		int end = nZeros;
		addZeros(nZeros);
		nZeros += length - n.length;
		n.addZeros(length - n.length);

		longNumber a = createPart(0, length / 2 - 1);
		longNumber b = createPart(length / 2, length - 1);

		longNumber c = n.createPart(0, length / 2 - 1);
		longNumber d = n.createPart(length / 2, length - 1);

		longNumber ac = a.karatsyba(c);

		longNumber bd = b.karatsyba(d);

		longNumber abcd = ((a + b).karatsyba(c + d) - ac - bd);

		abcd.addZeros(length / 2);
		ac.addZeros(length);

		longNumber res = ac + abcd + bd;

		res.demZeros(nZeros);
		demZeros(end);

		res.isNeg = (isNeg != n.isNeg);

		return longNumber(res);
	}

	longNumber tomKyk(longNumber n)
	{
		if (nSystem != n.nSystem) n.toNSystem(nSystem);
		if (n > *this) return n.tomKyk(*this);

		if (length <= minN && n.length <= minN)
		{
			longNumber res(toInt() * n.toInt(), nSystem);
			return longNumber(res);
		}

		int nZeros = 3 - this->length % 3;
		int end = nZeros;
		addZeros(nZeros);
		nZeros += length - n.length;
		n.addZeros(length - n.length);

		longNumber a = createPart(0, length / 3 - 1);
		longNumber b = createPart(length / 3, (length / 3) * 2 - 1);
		longNumber c = createPart((length / 3) * 2, length - 1);

		longNumber d = n.createPart(0, length / 3 - 1);
		longNumber l = n.createPart(length / 3, (length / 3) * 2 - 1);
		longNumber m = n.createPart((length / 3) * 2, length - 1);


		longNumber ad = a.tomKyk(d);
		longNumber bl = b.tomKyk(l);
		longNumber am = a.tomKyk(m);
		longNumber dc = d.tomKyk(c);
		longNumber mc = m.tomKyk(c);

		longNumber abdl = (a + b).tomKyk(l + d) - ad - bl;
		abdl.addZeros(length);

		longNumber ambldc = am + bl + dc;
		ambldc.addZeros(2 * length / 3);

		longNumber bmlc = (m + l).tomKyk(b + c) - mc - bl;
		bmlc.addZeros(length / 3);

		ad.addZeros(4 * length / 3);

		longNumber res = ad + abdl + ambldc + bmlc + mc;

		res.demZeros(nZeros);
		demZeros(end);

		res.isNeg = (isNeg != n.isNeg);

		return longNumber(res);
	}

	void del()
	{
		number* temp = head;
		while (head != nullptr)
		{
			head = head->right;
			delete temp;
			temp = head;
		}
		tail = nullptr;
	}

	~longNumber()
	{
		del();
	}
};

ostream& operator<< (ostream& out, longNumber& n)
{
	n.print();
	return out;
}

istream& operator>> (istream& in, longNumber& n)
{
	string s;
	in >> s;
	n.setNumber(s, 10);
	return in;
}

int main()
{
	cout << "a= ";
	longNumber n1;
	cin >> n1;
	cout << endl;

	cout << "b= ";
	longNumber n2;
	cin >> n2;
	cout << endl;

	longNumber n3;

	n3 = n1 + n2;
	cout << "a+b= " << n3 << endl;

	n3 = n1 - n2;
	cout << "a-b= " << n3 << endl;

	cout << "a>b: " << (n1 > n2) << endl;
	cout << "a<b: " << (n1 < n2) << endl;
	cout << "a=b: " << (n1 == n2) << endl;
	cout << "a!=b: " << (n1 != n2) << endl;

	n3 = n1.karatsyba(n2);
	cout << "karatsyba " << n3 << endl;

	n3 = n1.tomKyk(n2);
	cout << "tomKyk " << n3 << endl;

	return 0;
}