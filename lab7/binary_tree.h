#pragma once
#include <iostream>

template <typename T>
class binary_tree {

private:
	class FunctorHolderBase 
	{
	public:
		virtual bool CallFunctor(const T& left, const T& right) = 0;
		virtual ~FunctorHolderBase() {}
	};

	template<typename U>
	class FunctorHolder : public FunctorHolderBase
	{
	public:
		FunctorHolder(U functor)
			: m_functor(functor)
		{}
		bool CallFunctor(const T& left, const T& right) override
		{
			return m_functor(left, right);
		}

	private:
		U m_functor;
	};


public: 
	template <typename U>
	binary_tree(U functor)  {
		m_functor = new FunctorHolder<U>(functor);
	};

	virtual ~binary_tree()
	{
		delete m_functor;
	}

	virtual void Add(T x) = 0;
	virtual void Remove(T x) = 0;
	virtual T* Find(T x) = 0;

protected:
	FunctorHolderBase* m_functor;
};