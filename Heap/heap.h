#pragma once
#include<algorithm>
#include<memory>
#include<vector>
using std::swap;
using std::vector;
using std::shared_ptr;
using std::make_shared;

template<typename T>
class Heap
{
public:
	typedef Heap<T> CurrentClass;

public:
	Heap()
	{
		data_ = make_shared<vector<T>>();
	}
	Heap(const vector<T>& vec) :Heap()
	{
		for (auto item : vec)
			Insert(item);
	}
	Heap(const CurrentClass& instance) :Heap()
	{
		data_->assign(instance.data_->begin(), instance.data_->end());
	}

	Heap(CurrentClass&& instance)
	{
		data_ = instance.data_;
	}

public:
	bool Empty()
	{
		return data_->empty();
	}

	bool Size()
	{
		return data_->size();
	}

	//向堆中插入一个数字
	void Insert(const T& arg)
	{
		data_->push_back(arg);
		Upward(data_->size() - 1);
	}

	//获取堆顶元素
	T& Top()
	{
		if (!Empty())
			return data_->at(0);
		else return nullptr;
	}

	//删除堆顶元素
	void Pop()
	{
		if (Empty())return;
		swap(data_->at(0), data_->at(data_->size() - 1));
		data_->pop_back();
		Downward(0);
	}

	/*
	* Erase:删除编号为index的元素
	* 注意：编号从0开始，index非法则不操作
	*/
	void Erase(int index)
	{
		if (Empty() || index > data_->size() - 1)return;
		swap(data_->at(index), data_->at(data_->size() - 1));
		data_->pop_back();
		Downward(index);
		Upward(index);
	}

	/*
	* Change:更改编号为index的元素的值为arg
	* 注意：编号从0开始，index非法则不操作
	*/
	void Change(int index, const T& arg)
	{
		if (Empty() || index > data_->size() - 1)return;
		data_->at(index) = arg;
		Upward(index);
		Downward(index);
	}

private:

	/*
	* Upward: 将第index个元素向上调整
	* 注意: 元素编号从0开始，index非法则不进行操作
	*/
	void Upward(int index)
	{
		if (Empty())return();
		if (index <= 0 || index > data_->size() - 1)return;
		auto father = data_->at(index / 2);
		if (data_->at(index) < father)
		{
			swap(data_->at(index), father);
			Upward(index / 2);
		}
	}

	/*
	* Downward: 将第index个元素向下调整
	* 注意: 元素编号从0开始，index非法则不进行操作
	*/
	void Downward(int index)
	{
		if (Empty())return;
		if (index < 0 || index >= data_->size() - 1)return;
		int next = 0;
		if (index * 2 <= data_->size() - 1 && data_->at(index) > data_->at(index * 2))next = index * 2;
		if (index * 2 + 1 <= data_->size() - 1 &&
			data_->at(index) > data_->at(index * 2 + 1) &&
			data_->at(index * 2) > data_->at(index * 2 + 1))
			next = index * 2;
		if (next == 0)return;
		swap(data_->at(next), data_->at(index));
		Downward(next);
	}

private:
	shared_ptr<vector<T>> data_;
};