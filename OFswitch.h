#ifndef OF_SWITCH_H
#define OF_SWITCH_H

#include "stdafx.h"
#include "Rule.hpp"
#include "lru_cache.hpp"
#include "RuleList.h"
#include "BucketTree.h"
#include "MicRuleTree.h"
#include <unordered_map>
#include <boost/unordered_set.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/filesystem.hpp>
#include <set>

class OFswitch{
	public:
	const double offset;
	rule_list * rList;
	bucket_tree * bTree;
	
	public:
	size_t mode; // mode 0: CAB, mode 1: CEM, mode 2: CMR, mode 3: CDR
	double simuT; 
	double syn_load;
	size_t TCAMcap;
	std::string tracefile_str;

	public:
	OFswitch();
	OFswitch(double);

	void set_para(std::string, rule_list * = NULL, bucket_tree * = NULL);
	void run_test();
	void load_measure();

	private:
	void CABtest_rt_TCAM();
	void CEMtest_rt_id();
	void CDRtest_rt();
	void CMRtest_rt();
};

#endif
