// clang++-4.0 -std=c++14 

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <iomanip>
#include <fstream>
#include <cassert>

using namespace std;

class running_median {
    std::vector<int> max_lower, min_upper;
    
    int lower() const { return max_lower.front(); }
    void push_lower(int v) {
        max_lower.push_back(v);
        push_heap(max_lower.begin(),max_lower.end());
    }
    void pop_lower() {
        pop_heap(max_lower.begin(),max_lower.end());
        max_lower.resize(max_lower.size()-1);
    }
    
    int upper() const { return min_upper.front(); }
    void push_upper(int v) {
        min_upper.push_back(v);
        push_heap(min_upper.begin(),min_upper.end(), greater<int>());
    }
    void pop_upper() {
        pop_heap(min_upper.begin(),min_upper.end(), greater<int>());
        min_upper.resize(min_upper.size()-1);
    }
    
public:    
    void push(int v) {
		if(max_lower.empty()) {
			max_lower.push_back(v);
			return;
		}
		if(min_upper.empty()) {
			min_upper.push_back(v);
			if(max_lower.front() > min_upper.front()) // NOTE! must rebalance here
				swap(max_lower,min_upper);
			return;
		}
		
        if(v <= (lower()+upper())/2) {//TODO optimize for == case
            push_lower(v);
        } else {
            push_upper(v);
        } 
        auto const lsize = max_lower.size();
        auto const rsize = min_upper.size();
        if(lsize>rsize+1 ) {//restore balance
            push_upper(max_lower.front());
            pop_lower();
        } else if(rsize>lsize+1) {
            push_lower(min_upper.front());
            pop_upper();
        }
    }
    void dump(vector<int> const & v) const { 
		for(auto i : v)
			cout << " " << i; 
		cout << "| "; 
	}
    double
    median() const {
        auto const lsize = max_lower.size(); //dump(max_lower);
        auto const rsize = min_upper.size(); //dump(min_upper);
        assert(lsize==rsize or lsize==rsize+1 or lsize+1==rsize);
        if(lsize==rsize) {
            return (max_lower.front()+min_upper.front())/2.0;
        } else {
            return (lsize>rsize)? max_lower.front(): min_upper.front();
        }
    }
};

int main(int argn, char const * argv[]){
    if(argn>1) {
        static ifstream ifs{argv[1]};
        cin.rdbuf(ifs.rdbuf());
    }

    int n;
    cin >> n;
    vector<int> a(n);
    
    running_median running_median;
        
    for(int a_i = 0;a_i < n;a_i++){
       cin >> a[a_i];
        
        running_median.push(a[a_i]);
        cout << fixed << setprecision(1) << running_median.median() << "\n";
        
    }
    return 0;
}
