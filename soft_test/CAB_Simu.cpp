#include "stdafx.h"
#include "Address.hpp"
#include "Rule.hpp"
#include "RuleList.h"
#include "BucketTree.h"
#include "OFswitch.h"

using std::cout;
using std::endl;
using std::ofstream;

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace fs = boost::filesystem;

void logging_init() {
    fs::create_directory("./log");
    logging::add_file_log
    (
        keywords::file_name = "./log/sample_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%]: %Message%"
    );
}

int main() {
    srand (time(NULL));
    logging_init();
    //string rulefile = "../para_src/ruleset/rule8000-sp";
    string rulefile = "../para_src/ruleset/rule8000-rgg";
    rule_list rList(rulefile);
    rList.obtain_dep();
    
    //fs::path dir("./Trace_Generate_blk/spec/");
    fs::path dir("./Trace_Generate_blk/final/");
    vector<fs::path> pvec;
    std::copy(fs::directory_iterator(dir), fs::directory_iterator(), std::back_inserter(pvec));
    std::sort(pvec.begin(), pvec.end());
    bucket_tree bTree(rList, 15, false, 400);
    bTree.pre_alloc();

    /*
    for (size_t i = 1; i<20; ++i){
	cout << "percentage " << i*0.025 << endl;
    	bucket_tree bTree(rList, 15, false, i*100);
	cout << "finished tree" <<endl;
	bTree.pre_alloc();
    	OFswitch ofswitch;
    	ofswitch.set_para("../para_src/mode_file", &rList, &bTree);
    	ofswitch.simuT = 600;
	ofswitch.TCAMcap = 4000 - 100*i;
    	ofswitch.tracefile_str = pvec[0].string() + "/GENtrace/ref_trace.gz";
    	cout << "Processing: "<< pvec[0].string()<<endl;
	ofswitch.run_test();
    }*/

    OFswitch ofswitch;
    ofswitch.set_para("../para_src/mode_file", &rList, &bTree);

    for (auto it = pvec.begin(); it != pvec.end(); ++it){
	    ofswitch.tracefile_str = it->string() + "/GENtrace/ref_trace.gz";
	    ofswitch.simuT = 600;
	    cout << " Processing trace: " << it->string() << endl;
	    cout << "CDR: processing" << endl;
    	    ofswitch.mode = 2;
	    ofswitch.run_test();
	    //ofswitch.simuT = 200;
	    //cout << "CMR: processing" << endl;
    	    //ofswitch.mode = 3;
	    //ofswitch.run_test();
    }

    return 0;
}
