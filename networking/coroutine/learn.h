/*
 * learn.h
 *
 *  Created on: Nov 30, 2016
 *      Author: vikumar
 */

#ifndef COROUTINE_LEARN_H_
#define COROUTINE_LEARN_H_

#include <iostream>
#include <boost/coroutine2/all.hpp>
void printFib(int count){
	using coro_t = boost::coroutines2::asymmetric_coroutine<int>;
	using namespace std;
	coro_t::pull_type source(
			[&](coro_t::push_type& sink){
		int first = 1;
		int second = 1;
		sink(first);
		sink(second);
		for(int i = 0; i < count; ++i){
			auto third = first + second;
			first = second;
			second = third;
			sink(third);
		}
	}
	);

	for(auto i : source){
		cout << i << " ";
	}
	cout << "\n";
}


#endif /* COROUTINE_LEARN_H_ */
