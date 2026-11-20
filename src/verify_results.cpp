// Independent CSV summary for the research project. C++17; no dependencies.
// Created with AI assistance; each author should inspect/execute the code personally.
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
struct Group { vector<double> times; set<int> repeats; int model_bytes = -1; };
int main(int argc, char** argv) {
    const string path = argc > 1 ? argv[1] : "results.csv";
    ifstream in(path);
    if (!in) { cerr << "Cannot open " << path << "\n"; return 1; }
    string line; getline(in, line);
    if (line != "precision,hidden_neurons,repeat,iterations,latency_us,model_bytes") {
        cerr << "Unexpected CSV header\n"; return 1;
    }
    map<pair<int,string>,Group> groups;
    int row_count=0;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line); string precision, h, r, it, us, bytes;
        if (!getline(ss,precision,',') || !getline(ss,h,',') || !getline(ss,r,',') ||
            !getline(ss,it,',') || !getline(ss,us,',') || !getline(ss,bytes,',')) {
            cerr << "Malformed row\n"; return 1;
        }
        int width = stoi(h), rep = stoi(r), runs=stoi(it), size=stoi(bytes);
        double latency=stod(us);
        if ((width!=32 && width!=128 && width!=512) ||
            (precision!="float32" && precision!="float64") || runs!=10000 ||
            !isfinite(latency) || latency<=0 ||
            size!=(73*width+8)*(precision=="float32"?4:8)) {
            cerr << "Invalid value in row " << row_count+1 << "\n";return 1;
        }
        auto& g=groups[{width,precision}];
        if (g.repeats.count(rep) || (g.model_bytes>=0 && g.model_bytes!=size)) {
            cerr << "Duplicate or inconsistent row\n";return 1;
        }
        g.repeats.insert(rep); g.model_bytes=size;g.times.push_back(latency);++row_count;
    }
    if (row_count!=30 || groups.size()!=6) {cerr<<"Expected 30 rows and 6 groups\n";return 1;}
    cout << "width precision n mean_us sample_sd_us bytes\n";
    cout<<fixed<<setprecision(6);
    for (auto& entry:groups) {
        auto key=entry.first; auto& g=entry.second;
        if (g.times.size()!=5 || g.repeats!=set<int>({1,2,3,4,5})) {
            cerr<<"Invalid repetition set\n";return 1;
        }
        double mean=0; for(double v:g.times)mean+=v;mean/=g.times.size();
        double sum=0;for(double v:g.times)sum+=(v-mean)*(v-mean);
        cout<<key.first<<' '<<key.second<<' '<<g.times.size()<<' '
            <<mean<<' '<<sqrt(sum/(g.times.size()-1))<<' '<<g.model_bytes<<'\n';
    }
    cout << "PASS: validated 30 original measurements\n";
}
