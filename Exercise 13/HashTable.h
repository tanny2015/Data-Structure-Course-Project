#pragma once

class HashTable
{
public:
	// Constructors etc.
	HashTable();
	HashTable(int expectedn);
	HashTable(const HashTable & ht);
	HashTable & operator=(const HashTable & ht);
	~HashTable();

	// Insert, does not insert duplicate keys
	void insert(int key);

	// Accessors
	int size() const;
	int* dump(int & resultn) const; // for testing

private:
	int* arr;
	int n;
	int maxn;

	void copyTable(const HashTable & ht);
	void deleteTable();
	int hash(int key) const;
	int nextPrime(int x) const;
	bool checkPrime(int x) const;
};

